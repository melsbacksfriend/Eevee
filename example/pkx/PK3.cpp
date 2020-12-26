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

#include "pkx/PK3.hpp"
#include "pkx/PK4.hpp"
#include "pkx/PK5.hpp"
#include "pkx/PK6.hpp"
#include "pkx/PK7.hpp"
#include "pkx/PK8.hpp"
#include "utils/ValueConverter.hpp"
#include "utils/crypto.hpp"
#include "utils/endian.hpp"
#include "utils/flagUtil.hpp"
#include "utils/i18n.hpp"
#include "utils/random.hpp"
#include "utils/utils.hpp"
#include <algorithm>

#define RIBBON_ABSENT 0xFFFFFFFF

namespace
{
    std::pair<size_t, size_t> OFFSET_OF(pksm::Ribbon rib)
    {
        switch (rib)
        {
            case pksm::Ribbon::ChampionG3Hoenn:
                return {0x4D, 7};
            case pksm::Ribbon::Winning:
                return {0x4E, 0};
            case pksm::Ribbon::Victory:
                return {0x4E, 1};
            case pksm::Ribbon::Artist:
                return {0x4E, 2};
            case pksm::Ribbon::Effort:
                return {0x4E, 3};
            case pksm::Ribbon::ChampionBattle:
                return {0x4E, 4};
            case pksm::Ribbon::ChampionRegional:
                return {0x4E, 5};
            case pksm::Ribbon::ChampionNational:
                return {0x4E, 6};
            case pksm::Ribbon::Country:
                return {0x4E, 7};
            case pksm::Ribbon::National:
                return {0x4F, 0};
            case pksm::Ribbon::Earth:
                return {0x4F, 1};
            case pksm::Ribbon::World:
                return {0x4F, 2};

            default:
                return {RIBBON_ABSENT, 0};
        }
    }
}

namespace pksm
{
    u8 PK3::getUnownForm(u32 pid)
    {
        u32 val =
            (pid & 0x3000000) >> 18 | (pid & 0x30000) >> 12 | (pid & 0x300) >> 6 | (pid & 0x3);
        return val % 28;
    }

    void PK3::encrypt()
    {
        if (!isEncrypted())
        {
            u8 sv = PID() % 24;
            refreshChecksum();
            pksm::crypto::pkm::blockShuffle<BlockDataLength>(
                data + BlockShuffleStart, pksm::crypto::pkm::InvertedBlockPositions[sv]);
            crypt();
        }
    }

    void PK3::decrypt()
    {
        if (isEncrypted())
        {
            u8 sv = PID() % 24;
            crypt();
            pksm::crypto::pkm::blockShuffle<BlockDataLength>(data + BlockShuffleStart, sv);
        }
    }

    void PK3::crypt(void)
    {
        u32 seed    = LittleEndian::convertTo<u32>(data) ^ LittleEndian::convertTo<u32>(data + 4);
        auto xorkey = LittleEndian::convertFrom<u32>(seed);

        for (size_t i = 32; i < BOX_LENGTH; i++)
        {
            data[i] ^= xorkey[i % xorkey.size()];
        }
    }

    int PK3::swapBits(int value, int p1, int p2)
    {
        int bit1 = (value >> p1) & 1;
        int bit2 = (value >> p2) & 1;
        int x    = bit1 ^ bit2;
        x        = (x << p1) | (x << p2);
        return value ^ x;
    }

    bool PK3::japanese(void) const { return flagIsEgg() || language() == Language::JPN; }

    u16 PK3::calcChecksum() const
    {
        u16 chk = 0;
        for (size_t i = 0x20; i < BOX_LENGTH; i += 2)
            chk += LittleEndian::convertTo<u16>(data + i);
        return chk;
    }

    void PK3::refreshChecksum() { checksum(calcChecksum()); }

    bool PK3::isEncrypted() const { return calcChecksum() != checksum(); }

    PK3::PK3(PrivateConstructor, u8* dt, bool party, bool directAccess)
        : PKX(dt, party ? PARTY_LENGTH : BOX_LENGTH, directAccess)
    {
        if (isEncrypted())
        {
            decrypt();
        }
    }

    std::unique_ptr<PKX> PK3::clone(void) const
    {
        // Can't use normal data constructor because of checksum encryption checks
        std::unique_ptr<PK3> ret = PKX::getPKM<Generation::THREE>(nullptr, isParty());
        std::copy(data, data + getLength(), ret->rawData());
        return ret;
    }

    Generation PK3::generation(void) const { return Generation::THREE; }

    u32 PK3::encryptionConstant(void) const { return PID(); }
    void PK3::encryptionConstant(u32) {}

    u8 PK3::currentFriendship(void) const { return otFriendship(); }
    void PK3::currentFriendship(u8 v) { otFriendship(v); }

    u8 PK3::abilityNumber(void) const { return abilityBit() ? 2 : 1; }
    void PK3::abilityNumber(u8 v) { abilityBit(v > 1); }

    u32 PK3::PID(void) const { return LittleEndian::convertTo<u32>(data); }
    void PK3::PID(u32 v) { LittleEndian::convertFrom<u32>(data, v); }

    u16 PK3::TID(void) const { return LittleEndian::convertTo<u16>(data + 0x04); }
    void PK3::TID(u16 v) { LittleEndian::convertFrom<u16>(data + 0x04, v); }

    u16 PK3::SID(void) const { return LittleEndian::convertTo<u16>(data + 0x06); }
    void PK3::SID(u16 v) { LittleEndian::convertFrom<u16>(data + 0x06, v); }

    std::string PK3::nickname(void) const
    {
        return StringUtils::getString3(data, 0x08, 10, japanese());
    }
    void PK3::nickname(const std::string_view& v)
    {
        StringUtils::setString3(data, v, 0x08, 10, japanese());
    }

    Language PK3::language(void) const { return Language(data[0x12]); }
    void PK3::language(Language v) { data[0x12] = u8(v); }

    bool PK3::flagIsBadEgg(void) const { return (data[0x13] & 1) == 1; }
    void PK3::flagIsBadEgg(bool v) { data[0x13] = (data[0x13] & ~2) | (v ? 1 : 0); }

    bool PK3::flagHasSpecies(void) const { return (data[0x13] & 2) == 2; }
    void PK3::flagHasSpecies(bool v) { data[0x13] = (data[0x13] & ~2) | (v ? 2 : 0); }

    bool PK3::flagIsEgg(void) const { return (data[0x13] & 4) == 4; }
    void PK3::flagIsEgg(bool v) { data[0x13] = (data[0x13] & ~4) | (v ? 4 : 0); }

    std::string PK3::otName(void) const
    {
        return StringUtils::getString3(data, 0x14, 7, japanese());
    }
    void PK3::otName(const std::string_view& v)
    {
        StringUtils::setString3(data, v, 0x14, 7, japanese());
    }

    u16 PK3::markValue(void) const { return swapBits(data[0x1B], 1, 2); }
    void PK3::markValue(u16 v) { data[0x1B] = swapBits(v, 1, 2); }

    u16 PK3::checksum(void) const { return LittleEndian::convertTo<u16>(data + 0x1C); }
    void PK3::checksum(u16 v) { LittleEndian::convertFrom<u16>(data + 0x1C, v); }

    u16 PK3::sanity(void) const { return LittleEndian::convertTo<u16>(data + 0x1E); }
    void PK3::sanity(u16 v) { LittleEndian::convertFrom<u16>(data + 0x1E, v); }

    u16 PK3::speciesID3(void) const { return LittleEndian::convertTo<u16>(data + 0x20); }
    void PK3::speciesID3(u16 v) { LittleEndian::convertFrom<u16>(data + 0x20, v); }

    Species PK3::species(void) const { return SpeciesConverter::g3ToNational(speciesID3()); }
    void PK3::species(Species v)
    {
        speciesID3(SpeciesConverter::nationalToG3(v));
        flagHasSpecies(species() != Species::None);
    }

    u16 PK3::heldItem3(void) const { return LittleEndian::convertTo<u16>(data + 0x22); }
    void PK3::heldItem3(u16 v) { LittleEndian::convertFrom<u16>(data + 0x22, v); }

    u16 PK3::heldItem(void) const { return ItemConverter::g3ToNational(heldItem3()); }
    void PK3::heldItem(u16 v) { heldItem3(ItemConverter::nationalToG3(v)); }

    void PK3::heldItem(const Item& item)
    {
        if (item.generation() == Generation::THREE)
        {
            heldItem3((reinterpret_cast<const Item3&>(item)).id3());
        }
        else
        {
            heldItem(item.id());
        }
    }

    u32 PK3::experience(void) const { return LittleEndian::convertTo<u32>(data + 0x24); }
    void PK3::experience(u32 v) { LittleEndian::convertFrom<u32>(data + 0x24, v); }

    u8 PK3::PPUp(u8 move) const { return (data[0x28] >> (move * 2) & 3); }
    void PK3::PPUp(u8 move, u8 v)
    {
        data[0x28] = (data[0x28] & ~(3 << (move * 2))) | ((v & 3) << (move * 2));
    }

    u8 PK3::otFriendship(void) const { return data[0x29]; }
    void PK3::otFriendship(u8 v) { data[0x29] = v; }

    Move PK3::move(u8 move) const
    {
        return Move{LittleEndian::convertTo<u16>(data + 0x2C + move * 2)};
    }
    void PK3::move(u8 move, Move v)
    {
        LittleEndian::convertFrom<u16>(data + 0x2C + move * 2, u16(v));
    }

    u8 PK3::PP(u8 move) const { return data[0x34 + move]; }
    void PK3::PP(u8 move, u8 v) { data[0x34 + move] = v; }

    u8 PK3::ev(Stat ev) const { return data[0x38 + u8(ev)]; }
    void PK3::ev(Stat ev, u8 v) { data[0x38 + u8(ev)] = v; }

    u8 PK3::contest(u8 contest) const { return data[0x3E + contest]; }
    void PK3::contest(u8 contest, u8 v) { data[0x3E + contest] = v; }

    u8 PK3::pkrs(void) const { return data[0x44]; }
    void PK3::pkrs(u8 v) { data[0x44] = v; }

    u8 PK3::pkrsDays(void) const { return data[0x44] & 0xF; }
    void PK3::pkrsDays(u8 v) { data[0x44] = (data[0x44] & ~0xF) | v; }

    u8 PK3::pkrsStrain(void) const { return data[0x44] >> 4; }
    void PK3::pkrsStrain(u8 v) { data[0x44] = (data[0x44] & 0xF) | (v << 4); }

    u16 PK3::metLocation(void) const { return data[0x45]; }
    void PK3::metLocation(u16 v) { data[0x45] = u8(v); }

    u8 PK3::metLevel(void) const { return LittleEndian::convertTo<u16>(data + 0x46) & 0x7F; }
    void PK3::metLevel(u8 v)
    {
        LittleEndian::convertFrom<u16>(
            data + 0x46, u16((LittleEndian::convertTo<u16>(data + 0x46) & ~0x7F) | v));
    }

    GameVersion PK3::version(void) const
    {
        return GameVersion((LittleEndian::convertTo<u16>(data + 0x46) >> 7) & 0xF);
    }
    void PK3::version(GameVersion v)
    {
        LittleEndian::convertFrom<u16>(data + 0x46,
            u16((LittleEndian::convertTo<u16>(data + 0x46) & ~0x780) | ((u8(v) & 0xF) << 7)));
    }

    Ball PK3::ball(void) const
    {
        return Ball{u8((LittleEndian::convertTo<u16>(data + 0x46) >> 11) & 0xF)};
    }
    void PK3::ball(Ball v)
    {
        LittleEndian::convertFrom<u16>(data + 0x46,
            u16((LittleEndian::convertTo<u16>(data + 0x46) & ~0x7800) | ((u16(v) & 0xF) << 11)));
    }

    Gender PK3::otGender(void) const
    {
        return Gender{u8((LittleEndian::convertTo<u16>(data + 0x46) >> 15) & 1)};
    }
    void PK3::otGender(Gender v)
    {
        LittleEndian::convertFrom<u16>(data + 0x46,
            u16((LittleEndian::convertTo<u16>(data + 0x46) & ~(1 << 15)) | ((u8(v) & 1) << 15)));
    }

    u8 PK3::iv(Stat stat) const
    {
        u32 buffer = LittleEndian::convertTo<u32>(data + 0x48);
        return u8((buffer >> 5 * u8(stat)) & 0x1F);
    }
    void PK3::iv(Stat stat, u8 v)
    {
        u32 buffer = LittleEndian::convertTo<u32>(data + 0x48);
        buffer &= ~(0x1F << 5 * u8(stat));
        buffer |= v << (5 * u8(stat));
        LittleEndian::convertFrom<u32>(data + 0x48, buffer);
    }

    bool PK3::egg() const { return ((LittleEndian::convertTo<u32>(data + 0x48) >> 30) & 1) == 1; }
    void PK3::egg(bool v)
    {
        LittleEndian::convertFrom<u32>(
            data + 0x48, u32((LittleEndian::convertTo<u32>(data + 0x48) & ~0x40000000) |
                             (u32)(v ? 0x40000000 : 0)));
        flagIsEgg(v);
        if (v)
        {
            nickname("タマゴ");
            language(Language::JPN);
        }
    }

    bool PK3::abilityBit(void) const
    {
        return (LittleEndian::convertTo<u32>(data + 0x48) >> 31) == 1;
    }
    void PK3::abilityBit(bool v)
    {
        LittleEndian::convertFrom<u32>(data + 0x48,
            (LittleEndian::convertTo<u32>(data + 0x48) & 0x7FFFFFFF) | (v ? 1u << 31 : 0u));
    }

    bool PK3::hasRibbon(Ribbon ribbon) const { return OFFSET_OF(ribbon).first != RIBBON_ABSENT; }
    bool PK3::ribbon(Ribbon ribbon) const
    {
        auto offset = OFFSET_OF(ribbon);
        if (offset.first != RIBBON_ABSENT)
        {
            return FlagUtil::getFlag(data, offset.first, offset.second);
        }
        return false;
    }
    void PK3::ribbon(Ribbon ribbon, bool v)
    {
        auto offset = OFFSET_OF(ribbon);
        if (offset.first != RIBBON_ABSENT)
        {
            FlagUtil::setFlag(data, offset.first, offset.second, v);
        }
    }
    u8 PK3::contestRibbonCount(u8 contest) const
    {
        u16 rawVal = LittleEndian::convertTo<u16>(data + 0x4C);
        return (rawVal >> (contest * 3)) & 7;
    }
    void PK3::contestRibbonCount(u8 contest, u8 count)
    {
        u16 rawVal = LittleEndian::convertTo<u16>(data + 0x4C);
        rawVal &= 0xFFFF ^ (0x7 << (contest * 3));
        rawVal |= (count & 0x7) << (contest * 3);
        LittleEndian::convertFrom<u16>(data + 0x4C, rawVal);
    }

    bool PK3::fatefulEncounter(void) const
    {
        return (LittleEndian::convertTo<u32>(data + 0x4C) >> 31) == 1;
    }
    void PK3::fatefulEncounter(bool v)
    {
        LittleEndian::convertFrom<u32>(data + 0x4C,
            (LittleEndian::convertTo<u32>(data + 0x4C) & ~(1u << 31)) | (v ? 1u << 31 : 0));
    }

    int PK3::partyLevel() const
    {
        if (!isParty())
        {
            return -1;
        }
        return data[0x54];
    }
    void PK3::partyLevel(u8 v)
    {
        if (isParty())
        {
            data[0x54] = v;
        }
    }

    int PK3::partyCurrHP(void) const
    {
        if (!isParty())
        {
            return -1;
        }
        return LittleEndian::convertTo<u16>(data + 0x56);
    }
    void PK3::partyCurrHP(u16 v)
    {
        if (isParty())
        {
            LittleEndian::convertFrom<u16>(data + 0x56, v);
        }
    }

    int PK3::partyStat(Stat stat) const
    {
        if (!isParty())
        {
            return -1;
        }
        return LittleEndian::convertTo<u16>(data + 0x58 + u8(stat) * 2);
    }
    void PK3::partyStat(Stat stat, u16 v)
    {
        if (isParty())
        {
            LittleEndian::convertFrom<u16>(data + 0x58 + u8(stat) * 2, v);
        }
    }

    std::unique_ptr<PK4> PK3::convertToG4(Sav&) const
    {
        static constexpr std::array<std::array<u8, 18>, 7> trashBytes = {{
            {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00},
            {0x18, 0x20, 0x0D, 0x02, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0xA1,
                0x0C, 0x02, 0xE0, 0xFF},
            {0x74, 0x20, 0x0D, 0x02, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA4, 0xA1,
                0x0C, 0x02, 0xE0, 0xFF},
            {0x54, 0x20, 0x0D, 0x02, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x84, 0xA1,
                0x0C, 0x02, 0xE0, 0xFF},
            {0x74, 0x20, 0x0D, 0x02, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA4, 0xA1,
                0x0C, 0x02, 0xE0, 0xFF},
            {}, // Unused
            {0x74, 0x20, 0x0D, 0x02, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA4, 0xA1,
                0x0C, 0x02, 0xE0, 0xFF},
        }};

        auto pk4 = PKX::getPKM<Generation::FOUR>(nullptr);

        pk4->species(species());
        pk4->TID(TID());
        pk4->SID(SID());
        pk4->experience(egg() ? expTable(5, expType()) : experience());
        pk4->gender(gender());
        pk4->alternativeForm(alternativeForm());
        pk4->egg(false);
        pk4->otFriendship(70);
        pk4->markValue(markValue());
        pk4->language(language());
        pk4->ev(Stat::HP, ev(Stat::HP));
        pk4->ev(Stat::ATK, ev(Stat::ATK));
        pk4->ev(Stat::DEF, ev(Stat::DEF));
        pk4->ev(Stat::SPD, ev(Stat::SPD));
        pk4->ev(Stat::SPATK, ev(Stat::SPATK));
        pk4->ev(Stat::SPDEF, ev(Stat::SPDEF));
        pk4->contest(0, contest(0));
        pk4->contest(1, contest(1));
        pk4->contest(2, contest(2));
        pk4->contest(3, contest(3));
        pk4->contest(4, contest(4));
        pk4->contest(5, contest(5));
        pk4->move(0, move(0));
        pk4->move(1, move(1));
        pk4->move(2, move(2));
        pk4->move(3, move(3));
        pk4->PPUp(0, PPUp(0));
        pk4->PPUp(1, PPUp(1));
        pk4->PPUp(2, PPUp(2));
        pk4->PPUp(3, PPUp(3));
        pk4->iv(Stat::HP, iv(Stat::HP));
        pk4->iv(Stat::ATK, iv(Stat::ATK));
        pk4->iv(Stat::DEF, iv(Stat::DEF));
        pk4->iv(Stat::SPD, iv(Stat::SPD));
        pk4->iv(Stat::SPATK, iv(Stat::SPATK));
        pk4->iv(Stat::SPDEF, iv(Stat::SPDEF));
        if (ability() == PersonalRSFRLGE::ability(formSpecies(), abilityNumber() >> 1))
        {
            pk4->setAbility(abilityNumber() >> 1);
        }
        else
        {
            pk4->ability(ability());
        }
        pk4->PID(PID());
        pk4->version(version());
        pk4->ball(ball());
        pk4->pkrsStrain(pkrsStrain());
        pk4->pkrsDays(pkrsDays());
        pk4->otGender(otGender());
        pk4->metDate(Date::today());
        pk4->metLevel(level());
        pk4->metLocation(0x37); // Pal Park
        pk4->fatefulEncounter(fatefulEncounter());

        pk4->ribbon(Ribbon::ChampionG3Hoenn, ribbon(Ribbon::ChampionG3Hoenn));
        pk4->ribbon(Ribbon::Winning, ribbon(Ribbon::Winning));
        pk4->ribbon(Ribbon::Victory, ribbon(Ribbon::Victory));
        pk4->ribbon(Ribbon::Artist, ribbon(Ribbon::Artist));
        pk4->ribbon(Ribbon::Effort, ribbon(Ribbon::Effort));
        pk4->ribbon(Ribbon::ChampionBattle, ribbon(Ribbon::ChampionBattle));
        pk4->ribbon(Ribbon::ChampionRegional, ribbon(Ribbon::ChampionRegional));
        pk4->ribbon(Ribbon::ChampionNational, ribbon(Ribbon::ChampionNational));
        pk4->ribbon(Ribbon::Country, ribbon(Ribbon::Country));
        pk4->ribbon(Ribbon::National, ribbon(Ribbon::National));
        pk4->ribbon(Ribbon::Earth, ribbon(Ribbon::Earth));
        pk4->ribbon(Ribbon::World, ribbon(Ribbon::World));

        // Contest ribbons
        pk4->ribbon(Ribbon::G3Cool, contestRibbonCount(0) > 0);
        pk4->ribbon(Ribbon::G3CoolSuper, contestRibbonCount(0) > 1);
        pk4->ribbon(Ribbon::G3CoolHyper, contestRibbonCount(0) > 2);
        pk4->ribbon(Ribbon::G3CoolMaster, contestRibbonCount(0) > 3);
        pk4->ribbon(Ribbon::G3Beauty, contestRibbonCount(1) > 0);
        pk4->ribbon(Ribbon::G3BeautySuper, contestRibbonCount(1) > 1);
        pk4->ribbon(Ribbon::G3BeautyHyper, contestRibbonCount(1) > 2);
        pk4->ribbon(Ribbon::G3BeautyMaster, contestRibbonCount(1) > 3);
        pk4->ribbon(Ribbon::G3Cute, contestRibbonCount(2) > 0);
        pk4->ribbon(Ribbon::G3CuteSuper, contestRibbonCount(2) > 1);
        pk4->ribbon(Ribbon::G3CuteHyper, contestRibbonCount(2) > 2);
        pk4->ribbon(Ribbon::G3CuteMaster, contestRibbonCount(2) > 3);
        pk4->ribbon(Ribbon::G3Smart, contestRibbonCount(3) > 0);
        pk4->ribbon(Ribbon::G3SmartSuper, contestRibbonCount(3) > 1);
        pk4->ribbon(Ribbon::G3SmartHyper, contestRibbonCount(3) > 2);
        pk4->ribbon(Ribbon::G3SmartMaster, contestRibbonCount(3) > 3);
        pk4->ribbon(Ribbon::G3Tough, contestRibbonCount(4) > 0);
        pk4->ribbon(Ribbon::G3ToughSuper, contestRibbonCount(4) > 1);
        pk4->ribbon(Ribbon::G3ToughHyper, contestRibbonCount(4) > 2);
        pk4->ribbon(Ribbon::G3ToughMaster, contestRibbonCount(4) > 3);

        // Yay trash bytes
        if ((size_t)(u8(language()) - 1) < trashBytes.size())
        {
            auto& trash = trashBytes[u8(language()) - 1];
            std::copy(trash.begin(), trash.end(), pk4->rawData() + 0x48 + 4);
        }

        std::string name = species().localize(language());
        pk4->nickname(egg() ? StringUtils::toUpper(name) : nickname());
        pk4->nicknamed(!egg() && nicknamed());

        // Copy nickname trash into OT name
        std::copy(pk4->rawData() + 0x48, pk4->rawData() + 0x48 + 0x10, pk4->rawData() + 0x68);
        pk4->otName(otName());

        // I use 0 for invalid items
        pk4->heldItem(heldItem() == ItemConverter::G3_NOT_CONVERTIBLE ? 0 : heldItem());

        // Remove HM moves
        for (int i = 0; i < 4; i++)
        {
            static constexpr std::array<Move, 8> hms = {Move::Cut, Move::Fly, Move::Surf,
                Move::Strength, Move::Flash, Move::RockSmash, Move::Waterfall, Move::Dive};
            if (std::find(hms.begin(), hms.end(), pk4->move(i)) != hms.end())
            {
                pk4->move(i, Move::None);
            }
            else
            {
                pk4->move(i, move(i));
            }
        }
        pk4->fixMoves();

        pk4->refreshChecksum();
        return pk4;
    }

    std::unique_ptr<PK5> PK3::convertToG5(Sav& save) const
    {
        auto pk4 = convertToG4(save);
        if (pk4)
        {
            return pk4->convertToG5(save);
        }
        return nullptr;
    }
    std::unique_ptr<PK6> PK3::convertToG6(Sav& save) const
    {
        auto pk4 = convertToG4(save);
        if (pk4)
        {
            auto pk5 = pk4->convertToG5(save);
            if (pk5)
            {
                return pk5->convertToG6(save);
            }
        }
        return nullptr;
    }
    std::unique_ptr<PK7> PK3::convertToG7(Sav& save) const
    {
        auto pk4 = convertToG4(save);
        if (pk4)
        {
            auto pk5 = pk4->convertToG5(save);
            if (pk5)
            {
                auto pk6 = pk5->convertToG6(save);
                if (pk6)
                {
                    return pk6->convertToG7(save);
                }
            }
        }
        return nullptr;
    }
    std::unique_ptr<PK8> PK3::convertToG8(Sav& save) const
    {
        auto pk4 = convertToG4(save);
        if (pk4)
        {
            auto pk5 = pk4->convertToG5(save);
            if (pk5)
            {
                auto pk6 = pk5->convertToG6(save);
                if (pk6)
                {
                    auto pk7 = pk6->convertToG7(save);
                    if (pk7)
                    {
                        return pk7->convertToG8(save);
                    }
                }
            }
        }
        return nullptr;
    }

    u8 PK3::level() const
    {
        u8 i      = 1;
        u8 xpType = expType();
        while (experience() >= expTable(i, xpType) && ++i < 100)
            ;
        return i;
    }
    void PK3::level(u8 v) { experience(expTable(v - 1, expType())); }

    Ability PK3::ability() const { return abilityBit() ? abilities(1) : abilities(0); }
    void PK3::ability(Ability v)
    {
        if (v == abilities(0))
        {
            abilityBit(false);
        }
        else if (v == abilities(1))
        {
            abilityBit(true);
        }
    }
    void PK3::setAbility(u8 num)
    {
        if (num < 2)
        {
            ability(abilities(num));
        }
    }

    Nature PK3::nature() const { return Nature{u8(PID() % 25)}; }
    void PK3::nature(Nature v)
    {
        PID(PKX::getRandomPID(species(), gender(), version(), v, alternativeForm(),
            abilityBit() ? 2 : 1, PID(), Generation::THREE));
    }

    Gender PK3::gender() const
    {
        switch (genderType())
        {
            case 0:
                return Gender::Male;
            case 254:
                return Gender::Female;
            case 255:
                return Gender::Genderless;
            default:
                return (PID() & 0xFF) < genderType() ? Gender::Female : Gender::Male;
        }
    }
    void PK3::gender(Gender v)
    {
        PID(PKX::getRandomPID(species(), v, version(), nature(), alternativeForm(),
            abilityBit() ? 2 : 1, PID(), Generation::THREE));
    }

    u16 PK3::alternativeForm() const
    {
        if (species() == Species::Unown)
        {
            return getUnownForm(PID());
        }
        return 0;
    }
    void PK3::alternativeForm(u16 v)
    {
        if (species() == Species::Unown)
        {
            PID(PKX::getRandomPID(species(), gender(), version(), nature(), v, abilityBit() ? 2 : 1,
                PID(), Generation::THREE));
        }
    }

    bool PK3::nicknamed() const
    {
        std::string target = species().localize(language());
        return nickname() != StringUtils::toUpper(target);
    }
    void PK3::nicknamed(bool) {}

    Type PK3::hpType(void) const
    {
        return Type{u8((15 *
                           ((iv(Stat::HP) & 1) + 2 * (iv(Stat::ATK) & 1) + 4 * (iv(Stat::DEF) & 1) +
                               8 * (iv(Stat::SPD) & 1) + 16 * (iv(Stat::SPATK) & 1) +
                               32 * (iv(Stat::SPDEF) & 1)) /
                           63) +
                       1)};
    }
    void PK3::hpType(Type v)
    {
        if (v <= Type::Normal && v >= Type::Fairy)
        {
            return;
        }
        static constexpr u16 hpivs[16][6] = {
            {1, 1, 0, 0, 0, 0}, // Fighting
            {0, 0, 0, 1, 0, 0}, // Flying
            {1, 1, 0, 1, 0, 0}, // Poison
            {1, 1, 1, 1, 0, 0}, // Ground
            {1, 1, 0, 0, 1, 0}, // Rock
            {1, 0, 0, 1, 1, 0}, // Bug
            {1, 0, 1, 1, 1, 0}, // Ghost
            {1, 1, 1, 1, 1, 0}, // Steel
            {1, 0, 1, 0, 0, 1}, // Fire
            {1, 0, 0, 1, 0, 1}, // Water
            {1, 0, 1, 1, 0, 1}, // Grass
            {1, 1, 1, 1, 0, 1}, // Electric
            {1, 0, 1, 0, 1, 1}, // Psychic
            {1, 0, 0, 1, 1, 1}, // Ice
            {1, 0, 1, 1, 1, 1}, // Dragon
            {1, 1, 1, 1, 1, 1}, // Dark
        };

        for (u8 i = 0; i < 6; i++)
        {
            iv(Stat(i), (iv(Stat(i)) & 0x1E) + hpivs[u8(v) - 1][i]);
        }
    }

    u16 PK3::TSV() const { return (TID() ^ SID()) >> 3; }

    u16 PK3::PSV() const { return (PID() >> 16 ^ (PID() & 0xFFFF)) >> 3; }

    bool PK3::shiny(void) const { return TSV() == PSV(); }
    void PK3::shiny(bool v)
    {
        if (v)
        {
            while (!shiny())
            {
                PID(PKX::getRandomPID(species(), gender(), version(), nature(), alternativeForm(),
                    abilityNumber(), PID(), generation()));
            }
        }
        else
        {
            while (shiny())
            {
                PID(PKX::getRandomPID(species(), gender(), version(), nature(), alternativeForm(),
                    abilityNumber(), PID(), generation()));
            }
        }
    }

    u16 PK3::formSpecies() const { return u16(species()); }

    u16 PK3::stat(Stat stat) const
    {
        u16 calc;
        u8 mult = 10, basestat = 0;

        switch (stat)
        {
            case Stat::HP:
                basestat = baseHP();
                break;
            case Stat::ATK:
                basestat = baseAtk();
                break;
            case Stat::DEF:
                basestat = baseDef();
                break;
            case Stat::SPD:
                basestat = baseSpe();
                break;
            case Stat::SPATK:
                basestat = baseSpa();
                break;
            case Stat::SPDEF:
                basestat = baseSpd();
                break;
        }

        if (stat == Stat::HP)
            calc = 10 + (2 * basestat + iv(stat) + ev(stat) / 4 + 100) * level() / 100;
        else
            calc = 5 + (2 * basestat + iv(stat) + ev(stat) / 4) * level() / 100;

        if (u8(nature()) / 5 + 1 == u8(stat))
            mult++;
        if (u8(nature()) % 5 + 1 == u8(stat))
            mult--;
        return calc * mult / 10;
    }

    void PK3::updatePartyData()
    {
        constexpr Stat stats[] = {
            Stat::HP, Stat::ATK, Stat::DEF, Stat::SPD, Stat::SPATK, Stat::SPDEF};
        for (size_t i = 0; i < 6; i++)
        {
            partyStat(stats[i], stat(stats[i]));
        }
        partyLevel(level());
        partyCurrHP(stat(Stat::HP));
    }
}
