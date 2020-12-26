/*
 *   This file is part of PKSM-Core
 *   Copyright (C) 2016-2020 Bernardo Giordano, Admiral Fish, piepie62
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *   Additional Terms 7.b and 7.c of GPLv3 apply to this file:
 *       * Requiring preservation of specified reasonable legal notices or
 *         author attributions in that material or in the Appropriate Legal
 *         Notices displayed by works containing it.
 *       * Prohibiting misrepresentation of the origin of that material,
 *         or requiring that modified versions of such material be marked in
 *         reasonable ways as different from the original version.
 */

#include "sav/Sav3.hpp"
#include "pkx/PK3.hpp"
#include "utils/crypto.hpp"
#include "utils/endian.hpp"
#include "utils/flagUtil.hpp"
#include "utils/i18n.hpp"
#include "utils/utils.hpp"
#include "wcx/WCX.hpp"
#include <algorithm>
#include <limits>
#include <stdlib.h>

namespace pksm
{
    void Sav3::loadBlocks()
    {
        std::array<int, BLOCK_COUNT> o1 = getBlockOrder(data, 0);
        // I removed a length > 0x10000, since length should always be 0x20000 I think that's fine?
        std::array<int, BLOCK_COUNT> o2 = getBlockOrder(data, 0xE000);
        activeSAV                       = getActiveSaveIndex(data, o1, o2);
        blockOrder                      = activeSAV == 0 ? o1 : o2;

        for (int i = 0; i < BLOCK_COUNT; i++)
        {
            unsigned int index = std::distance(
                blockOrder.begin(), std::find(blockOrder.begin(), blockOrder.end(), i));
            blockOfs[i] = index == blockOrder.size() ? std::numeric_limits<int>::min()
                                                     : (index * SIZE_BLOCK) + ABO();
        }
    }

    std::array<int, Sav3::BLOCK_COUNT> Sav3::getBlockOrder(std::shared_ptr<u8[]> dt, int ofs)
    {
        std::array<int, BLOCK_COUNT> order;
        for (int i = 0; i < BLOCK_COUNT; i++)
            order[i] = LittleEndian::convertTo<s16>(&dt[ofs + (i * SIZE_BLOCK) + 0xFF4]);
        return order;
    }

    int Sav3::getActiveSaveIndex(std::shared_ptr<u8[]> dt,
        std::array<int, BLOCK_COUNT>& blockOrder1, std::array<int, BLOCK_COUNT>& blockOrder2)
    {
        int zeroBlock1 = std::find(blockOrder1.begin(), blockOrder1.end(), 0) - blockOrder1.begin();
        int zeroBlock2 = std::find(blockOrder2.begin(), blockOrder2.end(), 0) - blockOrder2.begin();
        if (size_t(zeroBlock2) == blockOrder2.size())
            return 0;
        if (size_t(zeroBlock1) == blockOrder1.size())
            return 1;
        u32 count1 = LittleEndian::convertTo<u32>(&dt[(zeroBlock1 * SIZE_BLOCK) + 0x0FFC]);
        u32 count2 = LittleEndian::convertTo<u32>(&dt[(zeroBlock2 * SIZE_BLOCK) + 0xEFFC]);
        return count1 > count2 ? 0 : 1;
    }

    Sav::Game Sav3::getVersion(std::shared_ptr<u8[]> dt)
    {
        // Get block 0 offset
        std::array<int, BLOCK_COUNT> o1     = getBlockOrder(dt, 0);
        std::array<int, BLOCK_COUNT> o2     = getBlockOrder(dt, BLOCK_COUNT * SIZE_BLOCK);
        int activeSAV                       = getActiveSaveIndex(dt, o1, o2);
        std::array<int, BLOCK_COUNT>& order = activeSAV == 0 ? o1 : o2;

        int ABO = activeSAV * SIZE_BLOCK * BLOCK_COUNT;

        int blockOfs0 =
            ((std::find(order.begin(), order.end(), 0) - order.begin()) * SIZE_BLOCK) + ABO;

        // Get version
        u32 gameCode = LittleEndian::convertTo<u32>(&dt[blockOfs0 + 0xAC]);
        switch (gameCode)
        {
            case 1:
                return Game::FRLG; // fixed value
            case 0:
                return Game::RS; // no battle tower record data
            default:
                // Ruby doesn't set data as far down as Emerald.
                // 00 FF 00 00 00 00 00 00 00 FF 00 00 00 00 00 00
                // ^ byte pattern in Emerald saves, is all zero in Ruby/Sapphire as far as I can
                // tell. Some saves have had data @ 0x550
                if (LittleEndian::convertTo<u64>(&dt[blockOfs0 + 0xEE0]) != 0)
                    return Game::E;
                if (LittleEndian::convertTo<u64>(&dt[blockOfs0 + 0xEE8]) != 0)
                    return Game::E;
                return Game::RS;
        }
    }

    Sav3::Sav3(std::shared_ptr<u8[]> dt, const std::vector<int>& flagOffsets)
        : Sav(dt, 0x20000), seenFlagOffsets(flagOffsets)
    {
        loadBlocks();

        // Japanese games are limited to 5 character OT names; any unused characters are 0xFF.
        // 5 for JP, 7 for INT. There's always 1 terminator, thus we can check 0x6-0x7 being 0xFFFF
        // = INT OT name is stored at the top of the first block.
        japanese = LittleEndian::convertTo<s16>(&data[blockOfs[0] + 0x6]) == 0;

        PokeDex = blockOfs[0] + 0x18;

        seenFlagOffsets[0] += PokeDex;
        seenFlagOffsets[1] += blockOfs[1];
        seenFlagOffsets[2] += blockOfs[4];

        initialize();
    }

    void Sav3::initialize(void)
    {
        // LoadEReaderBerryData();

        // Sanity Check SeenFlagOffsets -- early saves may not have block 4 initialized yet
        std::vector<int> seenFlagOffsetsTemp;
        for (const auto& seenFlagOffset : seenFlagOffsets)
        {
            if (seenFlagOffset >= 0)
                seenFlagOffsetsTemp.push_back(seenFlagOffset);
        }
        seenFlagOffsets = seenFlagOffsetsTemp;
    }

    u16 Sav3::calculateChecksum(const u8* data, size_t len)
    {
        u32 sum = pksm::crypto::sum32(data, len);
        return sum + (sum >> 16);
    }

    void Sav3::resign(void)
    {
        for (int i = 0; i < BLOCK_COUNT; i++)
        {
            int ofs   = ABO() + (i * SIZE_BLOCK);
            int index = blockOrder[i];
            if (index == -1)
                continue;
            int len = chunkLength[index];
            u16 chk = calculateChecksum(&data[ofs], len);
            LittleEndian::convertFrom<u16>(&data[ofs + 0xFF6], chk);
        }

        // Hall of Fame Checksums
        {
            u16 chk = calculateChecksum(&data[0x1C000], SIZE_BLOCK_USED);
            LittleEndian::convertFrom<u16>(&data[0x1CFF4], chk);
        }
        {
            u16 chk = calculateChecksum(&data[0x1D000], SIZE_BLOCK_USED);
            LittleEndian::convertFrom<u16>(&data[0x1DFF4], chk);
        }
    }

    u32 Sav3::securityKey(void) const
    {
        switch (game)
        {
            case Game::E:
                return LittleEndian::convertTo<u32>(&data[blockOfs[0] + 0xAC]);
            case Game::FRLG:
                return LittleEndian::convertTo<u32>(&data[blockOfs[0] + 0xF20]);
            default:
                return 0u;
        }
    }

    u16 Sav3::TID(void) const { return LittleEndian::convertTo<u16>(&data[blockOfs[0] + 0xA]); }
    void Sav3::TID(u16 v) { LittleEndian::convertFrom<u16>(&data[blockOfs[0] + 0xA], v); }

    u16 Sav3::SID(void) const { return LittleEndian::convertTo<u16>(&data[blockOfs[0] + 0xC]); }
    void Sav3::SID(u16 v) { LittleEndian::convertFrom<u16>(&data[blockOfs[0] + 0xC], v); }

    GameVersion Sav3::version(void) const
    {
        return game == Game::RS ? GameVersion::S
                                : game == Game::E ? GameVersion::E : GameVersion::FR;
    }
    void Sav3::version(GameVersion) {}

    Gender Sav3::gender(void) const { return Gender{data[blockOfs[0] + 8]}; }
    void Sav3::gender(Gender v) { data[blockOfs[0] + 8] = u8(v); }

    Language Sav3::language(void) const
    {
        // TODO: Other languages? Is this unused?
        return japanese ? Language::JPN : Language::ENG;
    }
    void Sav3::language(Language)
    {
        // TODO: Unused?
    }

    std::string Sav3::otName(void) const
    {
        return StringUtils::getString3(data.get(), blockOfs[0], japanese ? 5 : 7, japanese);
    }
    void Sav3::otName(const std::string_view& v)
    {
        StringUtils::setString3(
            data.get(), v, blockOfs[0], japanese ? 5 : 7, japanese, japanese ? 5 : 7, 0xFF);
    }

    u32 Sav3::money(void) const
    {
        switch (game)
        {
            case Game::RS:
            case Game::E:
                return LittleEndian::convertTo<u32>(&data[blockOfs[1] + 0x490]) ^ securityKey();
            case Game::FRLG:
                return LittleEndian::convertTo<u32>(&data[blockOfs[1] + 0x290]) ^ securityKey();
            default:
                return int(game);
        }
    }
    void Sav3::money(u32 v)
    {
        switch (game)
        {
            case Game::RS:
            case Game::E:
                LittleEndian::convertFrom<u32>(&data[blockOfs[1] + 0x0490], v ^ securityKey());
                break;
            case Game::FRLG:
                LittleEndian::convertFrom<u32>(&data[blockOfs[1] + 0x0290], v ^ securityKey());
                break;
            default:
                break;
        }
    }

    // TODO:? Coins

    u32 Sav3::BP(void) const { return LittleEndian::convertTo<u16>(&data[blockOfs[0] + 0xEB8]); }
    void Sav3::BP(u32 v)
    {
        if (v > 9999)
        {
            v = 9999;
        }

        LittleEndian::convertFrom<u16>(&data[blockOfs[0] + 0xEB8], v);
    }

    // TODO:? BPEarned

    // TODO:? BerryPowder

    bool Sav3::getEventFlag(int flagNumber) const
    {
        if (flagNumber >= 8 * (game == Game::E ? 300 : 288))
            return 0;

        int start = eventFlag;
        if (game == Game::FRLG && flagNumber >= 0x500)
        {
            flagNumber -= 0x500;
            start = blockOfs[2];
        }
        return FlagUtil::getFlag(data.get(), start + (flagNumber >> 3), flagNumber & 7);
    }

    void Sav3::setEventFlag(int flagNumber, bool value)
    {
        if (flagNumber >= 8 * (game == Game::E ? 300 : 288))
            return;

        int start = eventFlag;
        if (game == Game::FRLG && flagNumber >= 0x500)
        {
            flagNumber -= 0x500;
            start = blockOfs[2];
        }
        FlagUtil::setFlag(data.get(), start + (flagNumber >> 3), flagNumber & 7, value);
    }

    u8 Sav3::badges(void) const
    {
        int startFlag = 0;
        switch (game)
        {
            case Game::FRLG:
                startFlag = 0x820;
                break;
            case Game::RS:
                startFlag = 0x807;
                break;
            case Game::E:
                startFlag = 0x867;
            default:
                break;
        }

        int ret = 0;
        for (int i = 0; i < 8; i++)
        {
            if (getEventFlag(startFlag + i))
                ret++;
        }

        return ret;
    }

    u16 Sav3::playedHours(void) const
    {
        return LittleEndian::convertTo<u16>(&data[blockOfs[0] + 0xE]);
    }
    void Sav3::playedHours(u16 v) { LittleEndian::convertFrom<u16>(&data[blockOfs[0] + 0xE], v); }

    u8 Sav3::playedMinutes(void) const { return data[blockOfs[0] + 0x10]; }
    void Sav3::playedMinutes(u8 v) { data[blockOfs[0] + 0x10] = v; }

    u8 Sav3::playedSeconds(void) const { return data[blockOfs[0] + 0x11]; }
    void Sav3::playedSeconds(u8 v) { data[blockOfs[0] + 0x11] = v; }

    // TODO:? playedFrames, u8 at 0x12

    u8 Sav3::currentBox(void) const { return data[blockOfs[5]]; }
    void Sav3::currentBox(u8 v) { data[blockOfs[5]] = v; }

    u32 Sav3::boxOffset(u8 box, u8 slot) const
    {
        // Offset = blockOfs[block this slot is in] + slot offset
        int fullOffset = 4 + (PK3::BOX_LENGTH * box * 30) + (PK3::BOX_LENGTH * slot);
        div_t d        = div(fullOffset, 0xF80);
        // Box blocks start at 5
        return blockOfs[d.quot + 5] + d.rem;
    }

    u32 Sav3::partyOffset(u8 slot) const
    {
        return blockOfs[1] + (game == Game::FRLG ? 0x38 : 0x238) + (PK3::PARTY_LENGTH * slot);
    }

    std::unique_ptr<PKX> Sav3::pkm(u8 slot) const
    {
        return PKX::getPKM<Generation::THREE>(&data[partyOffset(slot)], true);
    }
    std::unique_ptr<PKX> Sav3::pkm(u8 box, u8 slot) const
    {
        u32 offset = boxOffset(box, slot);
        // Is it split?
        if ((offset % 0x1000) + PK3::BOX_LENGTH > 0xF80)
        {
            // Concatenate the data if so
            u8 pkmData[PK3::BOX_LENGTH];
            auto nextOut = std::copy(&data[offset], &data[(offset & 0xFFFFF000) | 0xF80], pkmData);
            u32 nextOffset = boxOffset(box + (slot + 1) / 30, (slot + 1) % 30);
            std::copy(&data[nextOffset & 0xFFFFF000], &data[nextOffset], nextOut);
            return PKX::getPKM<Generation::THREE>(pkmData);
        }
        else
        {
            return PKX::getPKM<Generation::THREE>(&data[offset]);
        }
    }

    void Sav3::pkm(const PKX& pk, u8 slot)
    {
        if (pk.generation() == Generation::THREE)
        {
            auto pk3 = pk.partyClone();
            pk3->encrypt();
            std::copy(pk3->rawData(), pk3->rawData() + PK3::PARTY_LENGTH, &data[partyOffset(slot)]);
        }
    }
    void Sav3::pkm(const PKX& pk, u8 box, u8 slot, bool applyTrade)
    {
        if (pk.generation() == Generation::THREE)
        {
            auto pk3 = pk.clone();
            if (applyTrade)
            {
                trade(*pk3);
            }

            u32 offset = boxOffset(box, slot);
            // Is it split?
            if ((offset % 0x1000) + PK3::BOX_LENGTH > 0xF80)
            {
                // Copy into the correct positions if so
                u32 firstSize = 0xF80 - (offset % 0x1000);
                std::copy(pk3->rawData(), pk3->rawData() + firstSize, &data[offset]);
                u32 nextOffset = boxOffset(box + (slot + 1) / 30, (slot + 1) % 30);
                std::copy(pk3->rawData() + firstSize, pk3->rawData() + PK3::BOX_LENGTH,
                    &data[nextOffset & 0xFFFFF000]);
            }
            else
            {
                std::copy(pk3->rawData(), pk3->rawData() + PK3::BOX_LENGTH, &data[offset]);
            }
        }
    }

    void Sav3::trade(PKX&, const Date&) const {}

    std::unique_ptr<PKX> Sav3::emptyPkm() const { return PKX::getPKM<Generation::THREE>(nullptr); }

    bool Sav3::canSetDex(Species species)
    {
        if (species == Species::None)
            return false;
        if (species > Species::Deoxys)
            return false;
        if (std::find_if(blockOfs.begin(), blockOfs.end(),
                [](const int& val) { return val < 0; }) != blockOfs.end())
            return false;
        return true;
    }

    u32 Sav3::dexPIDUnown(void) { return LittleEndian::convertTo<u32>(&data[PokeDex + 0x4]); }
    void Sav3::dexPIDUnown(u32 v) { LittleEndian::convertFrom<u32>(&data[PokeDex + 0x4], v); }

    u32 Sav3::dexPIDSpinda(void) { return LittleEndian::convertTo<u32>(&data[PokeDex + 0x8]); }
    void Sav3::dexPIDSpinda(u32 v) { LittleEndian::convertFrom<u32>(&data[PokeDex + 0x8], v); }

    void Sav3::dex(const PKX& pk)
    {
        if (!canSetDex(pk.species()) || pk.egg())
            return;

        switch (pk.species())
        {
            case Species::Unown:
                if (!getSeen(pk.species()))
                    dexPIDUnown(pk.PID());
                break;
            case Species::Spinda: // Spinda
                if (!getSeen(pk.species()))
                    dexPIDSpinda(pk.PID());
                break;
            default:
                break;
        }
        setCaught(pk.species(), true);
        setSeen(pk.species(), true);
    }

    bool Sav3::getCaught(Species species) const
    {
        int bit          = u16(species) - 1;
        int ofs          = bit >> 3;
        int caughtOffset = PokeDex + 0x10;
        return FlagUtil::getFlag(data.get(), caughtOffset + ofs, bit & 7);
    }

    void Sav3::setCaught(Species species, bool caught)
    {
        int bit          = u16(species) - 1;
        int ofs          = bit >> 3;
        int caughtOffset = PokeDex + 0x10;
        FlagUtil::setFlag(data.get(), caughtOffset + ofs, bit & 7, caught);
    }

    bool Sav3::getSeen(Species species) const
    {
        int bit        = u16(species) - 1;
        int ofs        = bit >> 3;
        int seenOffset = PokeDex + 0x44;
        return FlagUtil::getFlag(data.get(), seenOffset + ofs, bit & 7);
    }

    void Sav3::setSeen(Species species, bool seen)
    {
        int bit = u16(species) - 1;
        int ofs = bit >> 3;

        for (int o : seenFlagOffsets)
            FlagUtil::setFlag(data.get(), o + ofs, bit & 7, seen);
    }

    int Sav3::dexSeen(void) const
    {
        return std::count_if(availableSpecies().begin(), availableSpecies().end(),
            [this](const auto& spec) { return getSeen(spec); });
    }

    int Sav3::dexCaught(void) const
    {
        return std::count_if(availableSpecies().begin(), availableSpecies().end(),
            [this](const auto& spec) { return getCaught(spec); });
    }

    // Unused
    std::unique_ptr<WCX> Sav3::mysteryGift(int) const { return nullptr; }

    void Sav3::cryptBoxData(bool crypted)
    {
        for (u8 box = 0; box < maxBoxes(); box++)
        {
            for (u8 slot = 0; slot < 30; slot++)
            {
                u32 offset = boxOffset(box, slot);
                bool split = (offset % 0x1000) + PK3::BOX_LENGTH > 0xF80;
                // If it's split, it needs to get fully copied out and re-set in
                // Otherwise, use the direct-modification constructor
                std::unique_ptr<PKX> pk3;
                if (split)
                {
                    pk3 = pkm(box, slot);
                }
                else
                {
                    pk3 = PKX::getPKM<Generation::THREE>(&data[offset], false, true);
                }
                if (!crypted)
                {
                    pk3->encrypt();
                }
                if (split)
                {
                    pkm(*pk3, box, slot, false);
                }
            }
        }
    }

    std::string Sav3::boxName(u8 box) const
    {
        return StringUtils::getString3(
            data.get(), boxOffset(maxBoxes(), 0) + (box * 9), 9, japanese);
    }
    void Sav3::boxName(u8 box, const std::string_view& v)
    {
        return StringUtils::setString3(
            data.get(), v, boxOffset(maxBoxes(), 0) + (box * 9), 8, japanese, 9);
    }

    u8 Sav3::boxWallpaper(u8 box) const
    {
        int offset = boxOffset(maxBoxes(), 0);
        offset += (maxBoxes() * 0x9) + box;
        return data[offset];
    }
    void Sav3::boxWallpaper(u8 box, u8 v)
    {
        int offset = boxOffset(maxBoxes(), 0);
        offset += (maxBoxes() * 0x9) + box;
        data[offset] = v;
    }

    u8 Sav3::partyCount(void) const
    {
        return data[blockOfs[1] + (game == Game::FRLG ? 0x34 : 0x234)];
    }
    void Sav3::partyCount(u8 v) { data[blockOfs[1] + (game == Game::FRLG ? 0x34 : 0x234)] = v; }

    void Sav3::item(const Item& tItem, Pouch pouch, u16 slot)
    {
        Item3 item = static_cast<Item3>(tItem);
        if (pouch == Pouch::PCItem)
        {
            item.securityKey(0);
        }
        else
        {
            item.securityKey(securityKey());
        }
        auto write = item.bytes();
        switch (pouch)
        {
            case Pouch::NormalItem:
                std::copy(write.begin(), write.end(), &data[OFS_PouchHeldItem + (slot * 4)]);
                break;
            case Pouch::KeyItem:
                std::copy(write.begin(), write.end(), &data[OFS_PouchKeyItem + (slot * 4)]);
                break;
            case Pouch::Ball:
                std::copy(write.begin(), write.end(), &data[OFS_PouchBalls + (slot * 4)]);
                break;
            case Pouch::TM:
                std::copy(write.begin(), write.end(), &data[OFS_PouchTMHM + (slot * 4)]);
                break;
            case Pouch::Berry:
                std::copy(write.begin(), write.end(), &data[OFS_PouchBerry + (slot * 4)]);
                break;
            case Pouch::PCItem:
                std::copy(write.begin(), write.end(), &data[OFS_PCItem + (slot * 4)]);
                break;
            default:
                return;
        }
    }
    std::unique_ptr<Item> Sav3::item(Pouch pouch, u16 slot) const
    {
        switch (pouch)
        {
            case Pouch::NormalItem:
                return std::make_unique<Item3>(
                    &data[OFS_PouchHeldItem + (slot * 4)], securityKey());
            case Pouch::KeyItem:
                return std::make_unique<Item3>(&data[OFS_PouchKeyItem + (slot * 4)], securityKey());
            case Pouch::Ball:
                return std::make_unique<Item3>(&data[OFS_PouchBalls + (slot * 4)], securityKey());
            case Pouch::TM:
                return std::make_unique<Item3>(&data[OFS_PouchTMHM + (slot * 4)], securityKey());
            case Pouch::Berry:
                return std::make_unique<Item3>(&data[OFS_PouchBerry + (slot * 4)], securityKey());
            case Pouch::PCItem:
                return std::make_unique<Item3>(&data[OFS_PCItem + (slot * 4)]);
            default:
                return nullptr;
        }
    }

    std::vector<std::pair<Sav::Pouch, int>> Sav3::pouches(void) const
    {
        return {{Pouch::NormalItem, (OFS_PouchKeyItem - OFS_PouchHeldItem) / 4},
            {Pouch::KeyItem, (OFS_PouchBalls - OFS_PouchKeyItem) / 4},
            {Pouch::Ball, (OFS_PouchTMHM - OFS_PouchBalls) / 4},
            {Pouch::TM, (OFS_PouchBerry - OFS_PouchTMHM) / 4},
            {Pouch::Berry, game == Game::FRLG ? 43 : 46},
            {Pouch::PCItem, (OFS_PouchHeldItem - OFS_PCItem) / 4}};
    }

    u16 Sav3::rtcInitialDay(void) const
    {
        if (game == Game::FRLG)
            return 0;
        return LittleEndian::convertTo<u16>(&data[blockOfs[0] + 0x98]);
    }
    void Sav3::rtcInitialDay(u16 v)
    {
        if (game == Game::FRLG)
            return;
        LittleEndian::convertFrom<u16>(&data[blockOfs[0] + 0x98], v);
    }

    u8 Sav3::rtcInitialHour(void) const
    {
        if (game == Game::FRLG)
            return 0;
        return data[blockOfs[0] + 0x98 + 2];
    }
    void Sav3::rtcInitialHour(u8 v)
    {
        if (game == Game::FRLG)
            return;
        data[blockOfs[0] + 0x98 + 2] = v;
    }

    u8 Sav3::rtcInitialMinute(void) const
    {
        if (game == Game::FRLG)
            return 0;
        return data[blockOfs[0] + 0x98 + 3];
    }
    void Sav3::rtcInitialMinute(u8 v)
    {
        if (game == Game::FRLG)
            return;
        data[blockOfs[0] + 0x98 + 3] = v;
    }

    u8 Sav3::rtcInitialSecond(void) const
    {
        if (game == Game::FRLG)
            return 0;
        return data[blockOfs[0] + 0x98 + 4];
    }
    void Sav3::rtcInitialSecond(u8 v)
    {
        if (game == Game::FRLG)
            return;
        data[blockOfs[0] + 0x98 + 4] = v;
    }

    u16 Sav3::rtcElapsedDay(void) const
    {
        if (game == Game::FRLG)
            return 0;
        return LittleEndian::convertTo<u16>(&data[blockOfs[0] + 0xA0]);
    }
    void Sav3::rtcElapsedDay(u16 v)
    {
        if (game == Game::FRLG)
            return;
        LittleEndian::convertFrom<u16>(&data[blockOfs[0] + 0xA0], v);
    }

    u8 Sav3::rtcElapsedHour(void) const
    {
        if (game == Game::FRLG)
            return 0;
        return data[blockOfs[0] + 0xA0 + 2];
    }
    void Sav3::rtcElapsedHour(u8 v)
    {
        if (game == Game::FRLG)
            return;
        data[blockOfs[0] + 0xA0 + 2] = v;
    }

    u8 Sav3::rtcElapsedMinute(void) const
    {
        if (game == Game::FRLG)
            return 0;
        return data[blockOfs[0] + 0xA0 + 3];
    }
    void Sav3::rtcElapsedMinute(u8 v)
    {
        if (game == Game::FRLG)
            return;
        data[blockOfs[0] + 0xA0 + 3] = v;
    }

    u8 Sav3::rtcElapsedSecond(void) const
    {
        if (game == Game::FRLG)
            return 0;
        return data[blockOfs[0] + 0xA0 + 4];
    }
    void Sav3::rtcElapsedSecond(u8 v)
    {
        if (game == Game::FRLG)
            return;
        data[blockOfs[0] + 0xA0 + 4] = v;
    }
}
