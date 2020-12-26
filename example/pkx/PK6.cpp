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

#include "pkx/PK6.hpp"
#include "pkx/PK3.hpp"
#include "pkx/PK4.hpp"
#include "pkx/PK5.hpp"
#include "pkx/PK7.hpp"
#include "pkx/PK8.hpp"
#include "sav/Sav.hpp"
#include "utils/crypto.hpp"
#include "utils/endian.hpp"
#include "utils/flagUtil.hpp"
#include "utils/random.hpp"
#include "utils/utils.hpp"

#define RIBBON_ABSENT 0xFFFFFFFF

namespace
{
    std::pair<size_t, size_t> OFFSET_OF(pksm::Ribbon rib)
    {
        switch (rib)
        {
            case pksm::Ribbon::ChampionKalos:
                return {0x30, 0};
            case pksm::Ribbon::ChampionG3Hoenn:
                return {0x30, 1};
            case pksm::Ribbon::ChampionSinnoh:
                return {0x30, 2};
            case pksm::Ribbon::BestFriends:
                return {0x30, 3};
            case pksm::Ribbon::Training:
                return {0x30, 4};
            case pksm::Ribbon::BattlerSkillful:
                return {0x30, 5};
            case pksm::Ribbon::BattlerExpert:
                return {0x30, 6};
            case pksm::Ribbon::Effort:
                return {0x30, 7};
            case pksm::Ribbon::Alert:
                return {0x31, 0};
            case pksm::Ribbon::Shock:
                return {0x31, 1};
            case pksm::Ribbon::Downcast:
                return {0x31, 2};
            case pksm::Ribbon::Careless:
                return {0x31, 3};
            case pksm::Ribbon::Relax:
                return {0x31, 4};
            case pksm::Ribbon::Snooze:
                return {0x31, 5};
            case pksm::Ribbon::Smile:
                return {0x31, 6};
            case pksm::Ribbon::Gorgeous:
                return {0x31, 7};
            case pksm::Ribbon::Royal:
                return {0x32, 0};
            case pksm::Ribbon::GorgeousRoyal:
                return {0x32, 1};
            case pksm::Ribbon::Artist:
                return {0x32, 2};
            case pksm::Ribbon::Footprint:
                return {0x32, 3};
            case pksm::Ribbon::Record:
                return {0x32, 4};
            case pksm::Ribbon::Legend:
                return {0x32, 5};
            case pksm::Ribbon::Country:
                return {0x32, 6};
            case pksm::Ribbon::National:
                return {0x32, 7};
            case pksm::Ribbon::Earth:
                return {0x33, 0};
            case pksm::Ribbon::World:
                return {0x33, 1};
            case pksm::Ribbon::Classic:
                return {0x33, 2};
            case pksm::Ribbon::Premier:
                return {0x33, 3};
            case pksm::Ribbon::Event:
                return {0x33, 4};
            case pksm::Ribbon::Birthday:
                return {0x33, 5};
            case pksm::Ribbon::Special:
                return {0x33, 6};
            case pksm::Ribbon::Souvenir:
                return {0x33, 7};
            case pksm::Ribbon::Wishing:
                return {0x34, 0};
            case pksm::Ribbon::ChampionBattle:
                return {0x34, 1};
            case pksm::Ribbon::ChampionRegional:
                return {0x34, 2};
            case pksm::Ribbon::ChampionNational:
                return {0x34, 3};
            case pksm::Ribbon::ChampionWorld:
                return {0x34, 4};
            case pksm::Ribbon::MemoryContest:
                return {0x34, 5};
            case pksm::Ribbon::MemoryBattle:
                return {0x34, 6};
            case pksm::Ribbon::ChampionG6Hoenn:
                return {0x34, 7};
            case pksm::Ribbon::ContestStar:
                return {0x35, 0};
            case pksm::Ribbon::MasterCoolness:
                return {0x35, 1};
            case pksm::Ribbon::MasterBeauty:
                return {0x35, 2};
            case pksm::Ribbon::MasterCuteness:
                return {0x35, 3};
            case pksm::Ribbon::MasterCleverness:
                return {0x35, 4};
            case pksm::Ribbon::MasterToughness:
                return {0x35, 5};

            default:
                return {RIBBON_ABSENT, 0};
        }
    }
}

namespace pksm
{
    // void PK6::shuffleArray(u8 sv)
    // {
    //     static constexpr int blockLength = 56;
    //     u8 index                         = sv * 4;

    //     u8 cdata[length];
    //     std::copy(data, data + length, cdata);

    //     for (u8 block = 0; block < 4; block++)
    //     {
    //         u8 ofs = blockPosition(index + block);
    //         std::copy(cdata + 8 + blockLength * ofs, cdata + 8 + blockLength * ofs + blockLength,
    //             data + 8 + blockLength * block);
    //     }
    // }

    // void PK6::crypt(void)
    // {
    //     u32 seed = encryptionConstant();
    //     for (size_t i = 0x08; i < BOX_LENGTH; i += 2)
    //     {
    //         u16 temp = LittleEndian::convertTo<u16>(data + i);
    //         seed     = seedStep(seed);
    //         temp ^= (seed >> 16);
    //         LittleEndian::convertFrom<u16>(data + i, temp);
    //     }
    //     seed = encryptionConstant();
    //     for (u32 i = BOX_LENGTH; i < length; i += 2)
    //     {
    //         u16 temp = LittleEndian::convertTo<u16>(data + i);
    //         seed     = seedStep(seed);
    //         temp ^= (seed >> 16);
    //         LittleEndian::convertFrom<u16>(data + i, temp);
    //     }
    // }

    void PK6::encrypt(void)
    {
        if (!isEncrypted())
        {
            u8 sv = (encryptionConstant() >> 13) & 31;
            refreshChecksum();
            pksm::crypto::pkm::blockShuffle<BLOCK_LENGTH>(
                data + ENCRYPTION_START, pksm::crypto::pkm::InvertedBlockPositions[sv]);
            pksm::crypto::pkm::crypt<BOX_LENGTH - ENCRYPTION_START>(
                data + ENCRYPTION_START, encryptionConstant());
            if (isParty())
            {
                pksm::crypto::pkm::crypt<PARTY_LENGTH - BOX_LENGTH>(
                    data + BOX_LENGTH, encryptionConstant());
            }
        }
    }

    void PK6::decrypt(void)
    {
        if (isEncrypted())
        {
            u8 sv = (encryptionConstant() >> 13) & 31;
            pksm::crypto::pkm::crypt<BOX_LENGTH - ENCRYPTION_START>(
                data + ENCRYPTION_START, encryptionConstant());
            if (isParty())
            {
                pksm::crypto::pkm::crypt<PARTY_LENGTH - BOX_LENGTH>(
                    data + BOX_LENGTH, encryptionConstant());
            }
            pksm::crypto::pkm::blockShuffle<BLOCK_LENGTH>(data + ENCRYPTION_START, sv);
        }
    }

    bool PK6::isEncrypted() const
    {
        return LittleEndian::convertTo<u16>(data + 0xC8) != 0 &&
               LittleEndian::convertTo<u16>(data + 0x58) != 0;
    }

    PK6::PK6(PrivateConstructor, u8* dt, bool party, bool direct)
        : PKX(dt, party ? PARTY_LENGTH : BOX_LENGTH, direct)
    {
        if (isEncrypted())
        {
            decrypt();
        }
    }

    std::unique_ptr<PKX> PK6::clone(void) const
    {
        return PKX::getPKM<Generation::SIX>(const_cast<u8*>(data), isParty());
    }

    Generation PK6::generation(void) const { return Generation::SIX; }

    bool PK6::untraded(void) const
    {
        return data[0x78] == 0 && data[0x79] == 0 && originGen() == Generation::SIX;
    }

    bool PK6::untradedEvent(void) const
    {
        return geoCountry(0) == 0 && geoRegion(0) == 0 && (metLocation() / 10000 == 4) &&
               originGen6();
    }

    u32 PK6::encryptionConstant(void) const { return LittleEndian::convertTo<u32>(data); }
    void PK6::encryptionConstant(u32 v) { LittleEndian::convertFrom<u32>(data, v); }

    u16 PK6::sanity(void) const { return LittleEndian::convertTo<u16>(data + 0x04); }
    void PK6::sanity(u16 v) { LittleEndian::convertFrom<u16>(data + 0x04, v); }

    u16 PK6::checksum(void) const { return LittleEndian::convertTo<u16>(data + 0x06); }
    void PK6::checksum(u16 v) { LittleEndian::convertFrom<u16>(data + 0x06, v); }

    Species PK6::species(void) const { return Species{LittleEndian::convertTo<u16>(data + 0x08)}; }
    void PK6::species(Species v) { LittleEndian::convertFrom<u16>(data + 0x08, u16(v)); }

    u16 PK6::heldItem(void) const { return LittleEndian::convertTo<u16>(data + 0x0A); }
    void PK6::heldItem(u16 v) { LittleEndian::convertFrom<u16>(data + 0x0A, v); }

    u16 PK6::TID(void) const { return LittleEndian::convertTo<u16>(data + 0x0C); }
    void PK6::TID(u16 v) { LittleEndian::convertFrom<u16>(data + 0x0C, v); }

    u16 PK6::SID(void) const { return LittleEndian::convertTo<u16>(data + 0x0E); }
    void PK6::SID(u16 v) { LittleEndian::convertFrom<u16>(data + 0x0E, v); }

    u32 PK6::experience(void) const { return LittleEndian::convertTo<u32>(data + 0x10); }
    void PK6::experience(u32 v) { LittleEndian::convertFrom<u32>(data + 0x10, v); }

    Ability PK6::ability(void) const { return Ability{data[0x14]}; }
    void PK6::ability(Ability v) { data[0x14] = u8(v); }

    void PK6::setAbility(u8 v)
    {
        u8 abilitynum;

        if (v == 0)
            abilitynum = 1;
        else if (v == 1)
            abilitynum = 2;
        else
            abilitynum = 4;

        abilityNumber(abilitynum);
        ability(abilities(v));
    }

    u8 PK6::abilityNumber(void) const { return data[0x15]; }
    void PK6::abilityNumber(u8 v) { data[0x15] = v; }

    u8 PK6::trainingBagHits(void) const { return data[0x16]; }
    void PK6::trainingBagHits(u8 v) { data[0x16] = v; }

    u8 PK6::trainingBag(void) const { return data[0x17]; }
    void PK6::trainingBag(u8 v) { data[0x17] = v; }

    u32 PK6::PID(void) const { return LittleEndian::convertTo<u32>(data + 0x18); }
    void PK6::PID(u32 v) { LittleEndian::convertFrom<u32>(data + 0x18, v); }

    Nature PK6::nature(void) const { return Nature{data[0x1C]}; }
    void PK6::nature(Nature v) { data[0x1C] = u8(v); }

    bool PK6::fatefulEncounter(void) const { return (data[0x1D] & 1) == 1; }
    void PK6::fatefulEncounter(bool v) { data[0x1D] = (u8)((data[0x1D] & ~0x01) | (v ? 1 : 0)); }

    Gender PK6::gender(void) const { return Gender{u8((data[0x1D] >> 1) & 0x3)}; }
    void PK6::gender(Gender v) { data[0x1D] = (data[0x1D] & ~0x06) | (u8(v) << 1); }

    u16 PK6::alternativeForm(void) const { return data[0x1D] >> 3; }
    void PK6::alternativeForm(u16 v) { data[0x1D] = (data[0x1D] & 0x07) | (v << 3); }

    u8 PK6::ev(Stat ev) const { return data[0x1E + u8(ev)]; }
    void PK6::ev(Stat ev, u8 v) { data[0x1E + u8(ev)] = v; }

    u8 PK6::contest(u8 contest) const { return data[0x24 + contest]; }
    void PK6::contest(u8 contest, u8 v) { data[0x24 + contest] = v; }

    u16 PK6::markValue(void) const { return data[0x2A]; }
    void PK6::markValue(u16 v) { data[0x2A] = v; }

    u8 PK6::pkrs(void) const { return data[0x2B]; }
    void PK6::pkrs(u8 v) { data[0x2B] = v; }

    u8 PK6::pkrsDays(void) const { return data[0x2B] & 0xF; };
    void PK6::pkrsDays(u8 v) { data[0x2B] = (u8)((data[0x2B] & ~0xF) | v); }

    u8 PK6::pkrsStrain(void) const { return data[0x2B] >> 4; };
    void PK6::pkrsStrain(u8 v) { data[0x2B] = (u8)((data[0x2B] & 0xF) | v << 4); }

    bool PK6::hasRibbon(Ribbon ribbon) const { return OFFSET_OF(ribbon).first != RIBBON_ABSENT; }
    bool PK6::ribbon(Ribbon ribbon) const
    {
        auto offset = OFFSET_OF(ribbon);
        if (offset.first != RIBBON_ABSENT)
        {
            return FlagUtil::getFlag(data, offset.first, offset.second);
        }
        return false;
    }
    void PK6::ribbon(Ribbon ribbon, bool v)
    {
        auto offset = OFFSET_OF(ribbon);
        if (offset.first != RIBBON_ABSENT)
        {
            FlagUtil::setFlag(data, offset.first, offset.second, v);
        }
    }

    u8 PK6::ribbonContestCount(void) const { return data[0x38]; }
    void PK6::ribbonContestCount(u8 v) { data[0x38] = v; }

    u8 PK6::ribbonBattleCount(void) const { return data[0x39]; }
    void PK6::ribbonBattleCount(u8 v) { data[0x39] = v; }

    std::string PK6::nickname(void) const
    {
        return StringUtils::transString67(StringUtils::getString(data, 0x40, 13));
    }
    void PK6::nickname(const std::string_view& v)
    {
        StringUtils::setString(data, StringUtils::transString67(v), 0x40, 13);
    }

    Move PK6::move(u8 m) const { return Move{LittleEndian::convertTo<u16>(data + 0x5A + m * 2)}; }
    void PK6::move(u8 m, Move v) { LittleEndian::convertFrom<u16>(data + 0x5A + m * 2, u16(v)); }

    u8 PK6::PP(u8 m) const { return data[0x62 + m]; }
    void PK6::PP(u8 m, u8 v) { data[0x62 + m] = v; }

    u8 PK6::PPUp(u8 m) const { return data[0x66 + m]; }
    void PK6::PPUp(u8 m, u8 v) { data[0x66 + m] = v; }

    Move PK6::relearnMove(u8 m) const
    {
        return Move{LittleEndian::convertTo<u16>(data + 0x6A + m * 2)};
    }
    void PK6::relearnMove(u8 m, Move v)
    {
        LittleEndian::convertFrom<u16>(data + 0x6A + m * 2, u16(v));
    }

    bool PK6::secretSuperTrainingUnlocked(void) const { return (data[0x72] & 1) == 1; }
    void PK6::secretSuperTrainingUnlocked(bool v) { data[0x72] = (data[0x72] & ~1) | (v ? 1 : 0); }

    bool PK6::secretSuperTrainingComplete(void) const { return (data[0x72] & 2) == 2; }
    void PK6::secretSuperTrainingComplete(bool v) { data[0x72] = (data[0x72] & ~2) | (v ? 2 : 0); }

    u8 PK6::iv(Stat stat) const
    {
        u32 buffer = LittleEndian::convertTo<u32>(data + 0x74);
        return (u8)((buffer >> 5 * u8(stat)) & 0x1F);
    }

    void PK6::iv(Stat stat, u8 v)
    {
        u32 buffer = LittleEndian::convertTo<u32>(data + 0x74);
        buffer &= ~(0x1F << 5 * u8(stat));
        buffer |= v << (5 * u8(stat));
        LittleEndian::convertFrom<u32>(data + 0x74, buffer);
    }

    bool PK6::egg(void) const
    {
        return ((LittleEndian::convertTo<u32>(data + 0x74) >> 30) & 0x1) == 1;
    }
    void PK6::egg(bool v)
    {
        LittleEndian::convertFrom<u32>(
            data + 0x74, (u32)((LittleEndian::convertTo<u32>(data + 0x74) & ~0x40000000) |
                               (u32)(v ? 0x40000000 : 0)));
    }

    bool PK6::nicknamed(void) const
    {
        return ((LittleEndian::convertTo<u32>(data + 0x74) >> 31) & 0x1) == 1;
    }
    void PK6::nicknamed(bool v)
    {
        LittleEndian::convertFrom<u32>(data + 0x74,
            (LittleEndian::convertTo<u32>(data + 0x74) & 0x7FFFFFFF) | (v ? 0x80000000 : 0));
    }

    std::string PK6::htName(void) const
    {
        return StringUtils::transString67(StringUtils::getString(data, 0x78, 13));
    }
    void PK6::htName(const std::string_view& v)
    {
        StringUtils::setString(data, StringUtils::transString67(v), 0x78, 13);
    }

    Gender PK6::htGender(void) const { return Gender{data[0x92]}; }
    void PK6::htGender(Gender v) { data[0x92] = u8(v); }

    u8 PK6::currentHandler(void) const { return data[0x93]; }
    void PK6::currentHandler(u8 v) { data[0x93] = v; }

    u8 PK6::geoRegion(u8 region) const { return data[0x94 + region * 2]; }
    void PK6::geoRegion(u8 region, u8 v) { data[0x94 + region * 2] = v; }

    u8 PK6::geoCountry(u8 country) const { return data[0x95 + country * 2]; }
    void PK6::geoCountry(u8 country, u8 v) { data[0x95 + country * 2] = v; }

    u8 PK6::htFriendship(void) const { return data[0xA2]; }
    void PK6::htFriendship(u8 v) { data[0xA2] = v; }

    u8 PK6::htAffection(void) const { return data[0xA3]; }
    void PK6::htAffection(u8 v) { data[0xA3] = v; }

    u8 PK6::htIntensity(void) const { return data[0xA4]; }
    void PK6::htIntensity(u8 v) { data[0xA4] = v; }

    u8 PK6::htMemory(void) const { return data[0xA5]; }
    void PK6::htMemory(u8 v) { data[0xA5] = v; }

    u8 PK6::htFeeling(void) const { return data[0xA6]; }
    void PK6::htFeeling(u8 v) { data[0xA6] = v; }

    u16 PK6::htTextVar(void) const { return LittleEndian::convertTo<u16>(data + 0xA8); }
    void PK6::htTextVar(u16 v) { LittleEndian::convertFrom<u16>(data + 0xA8, v); }

    u8 PK6::fullness(void) const { return data[0xAE]; }
    void PK6::fullness(u8 v) { data[0xAE] = v; }

    u8 PK6::enjoyment(void) const { return data[0xAF]; }
    void PK6::enjoyment(u8 v) { data[0xAF] = v; }

    std::string PK6::otName(void) const
    {
        return StringUtils::transString67(StringUtils::getString(data, 0xB0, 13));
    }
    void PK6::otName(const std::string_view& v)
    {
        StringUtils::setString(data, StringUtils::transString67(v), 0xB0, 13);
    }

    u8 PK6::otFriendship(void) const { return data[0xCA]; }
    void PK6::otFriendship(u8 v) { data[0xCA] = v; }

    u8 PK6::otAffection(void) const { return data[0xCB]; }
    void PK6::otAffection(u8 v) { data[0xCB] = v; }

    u8 PK6::otIntensity(void) const { return data[0xCC]; }
    void PK6::otIntensity(u8 v) { data[0xCC] = v; }

    u8 PK6::otMemory(void) const { return data[0xCD]; }
    void PK6::otMemory(u8 v) { data[0xCD] = v; }

    u16 PK6::otTextVar(void) const { return LittleEndian::convertTo<u16>(data + 0xCE); }
    void PK6::otTextVar(u16 v) { LittleEndian::convertFrom<u16>(data + 0xCE, v); }

    u8 PK6::otFeeling(void) const { return data[0xD0]; }
    void PK6::otFeeling(u8 v) { data[0xD0] = v; }

    int PK6::eggYear(void) const { return 2000 + data[0xD1]; }
    void PK6::eggYear(int v) { data[0xD1] = v - 2000; }

    int PK6::eggMonth(void) const { return data[0xD2]; }
    void PK6::eggMonth(int v) { data[0xD2] = v; }

    int PK6::eggDay(void) const { return data[0xD3]; }
    void PK6::eggDay(int v) { data[0xD3] = v; }

    int PK6::metYear(void) const { return 2000 + data[0xD4]; }
    void PK6::metYear(int v) { data[0xD4] = v - 2000; }

    int PK6::metMonth(void) const { return data[0xD5]; }
    void PK6::metMonth(int v) { data[0xD5] = v; }

    int PK6::metDay(void) const { return data[0xD6]; }
    void PK6::metDay(int v) { data[0xD6] = v; }

    u16 PK6::eggLocation(void) const { return LittleEndian::convertTo<u16>(data + 0xD8); }
    void PK6::eggLocation(u16 v) { LittleEndian::convertFrom<u16>(data + 0xD8, v); }

    u16 PK6::metLocation(void) const { return LittleEndian::convertTo<u16>(data + 0xDA); }
    void PK6::metLocation(u16 v) { LittleEndian::convertFrom<u16>(data + 0xDA, v); }

    Ball PK6::ball(void) const { return Ball{data[0xDC]}; }
    void PK6::ball(Ball v) { data[0xDC] = u8(v); }

    u8 PK6::metLevel(void) const { return data[0xDD] & ~0x80; }
    void PK6::metLevel(u8 v) { data[0xDD] = (data[0xDD] & 0x80) | v; }

    Gender PK6::otGender(void) const { return Gender{u8(data[0xDD] >> 7)}; }
    void PK6::otGender(Gender v) { data[0xDD] = (data[0xDD] & ~0x80) | (u8(v) << 7); }

    u8 PK6::encounterType(void) const { return data[0xDE]; }
    void PK6::encounterType(u8 v) { data[0xDE] = v; }

    GameVersion PK6::version(void) const { return GameVersion(data[0xDF]); }
    void PK6::version(GameVersion v) { data[0xDF] = u8(v); }

    u8 PK6::country(void) const { return data[0xE0]; }
    void PK6::country(u8 v) { data[0xE0] = v; }

    u8 PK6::region(void) const { return data[0xE1]; }
    void PK6::region(u8 v) { data[0xE1] = v; }

    u8 PK6::consoleRegion(void) const { return data[0xE2]; }
    void PK6::consoleRegion(u8 v) { data[0xE2] = v; }

    Language PK6::language(void) const { return Language(data[0xE3]); }
    void PK6::language(Language v) { data[0xE3] = u8(v); }

    u8 PK6::currentFriendship(void) const
    {
        return currentHandler() == 0 ? otFriendship() : htFriendship();
    }
    void PK6::currentFriendship(u8 v)
    {
        if (currentHandler() == 0)
            otFriendship(v);
        else
            htFriendship(v);
    }

    u8 PK6::oppositeFriendship(void) const
    {
        return currentHandler() == 1 ? otFriendship() : htFriendship();
    }
    void PK6::oppositeFriendship(u8 v)
    {
        if (currentHandler() == 1)
            otFriendship(v);
        else
            htFriendship(v);
    }

    void PK6::refreshChecksum(void)
    {
        u16 chk = 0;
        for (u8 i = 8; i < BOX_LENGTH; i += 2)
        {
            chk += LittleEndian::convertTo<u16>(data + i);
        }
        checksum(chk);
    }

    Type PK6::hpType(void) const
    {
        return Type{u8((15 *
                           ((iv(Stat::HP) & 1) + 2 * (iv(Stat::ATK) & 1) + 4 * (iv(Stat::DEF) & 1) +
                               8 * (iv(Stat::SPD) & 1) + 16 * (iv(Stat::SPATK) & 1) +
                               32 * (iv(Stat::SPDEF) & 1)) /
                           63) +
                       1)};
    }
    void PK6::hpType(Type v)
    {
        if (v <= Type::Normal || v >= Type::Fairy)
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
            iv(Stat(i), (iv(Stat(i)) & 0x1e) + hpivs[u8(v) - 1][i]);
        }
    }

    u16 PK6::TSV(void) const { return (TID() ^ SID()) >> 4; }
    u16 PK6::PSV(void) const { return ((PID() >> 16) ^ (PID() & 0xFFFF)) >> 4; }

    u8 PK6::level(void) const
    {
        u8 i      = 1;
        u8 xpType = expType();
        while (experience() >= expTable(i, xpType) && ++i < 100)
            ;
        return i;
    }

    void PK6::level(u8 v) { experience(expTable(v - 1, expType())); }

    bool PK6::shiny(void) const { return TSV() == PSV(); }
    void PK6::shiny(bool v)
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

    u16 PK6::formSpecies(void) const
    {
        u16 tmpSpecies = u16(species());
        u8 form        = alternativeForm();
        u8 formcount   = PersonalXYORAS::formCount(tmpSpecies);

        if (form && form < formcount)
        {
            u16 backSpecies = tmpSpecies;
            tmpSpecies      = PersonalXYORAS::formStatIndex(tmpSpecies);
            if (!tmpSpecies)
            {
                tmpSpecies = backSpecies;
            }
            else
            {
                tmpSpecies += form - 1;
            }
        }

        return tmpSpecies;
    }

    u16 PK6::stat(Stat stat) const
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

    int PK6::partyCurrHP(void) const
    {
        if (!isParty())
        {
            return -1;
        }
        return LittleEndian::convertTo<u16>(data + 0xF0);
    }

    void PK6::partyCurrHP(u16 v)
    {
        if (isParty())
        {
            LittleEndian::convertFrom<u16>(data + 0xF0, v);
        }
    }

    int PK6::partyStat(Stat stat) const
    {
        if (!isParty())
        {
            return -1;
        }
        return LittleEndian::convertTo<u16>(data + 0xF2 + u8(stat) * 2);
    }

    void PK6::partyStat(Stat stat, u16 v)
    {
        if (isParty())
        {
            LittleEndian::convertFrom<u16>(data + 0xF2 + u8(stat) * 2, v);
        }
    }

    int PK6::partyLevel() const
    {
        if (!isParty())
        {
            return -1;
        }
        return *(data + 0xEC);
    }

    void PK6::partyLevel(u8 v)
    {
        if (isParty())
        {
            *(data + 0xEC) = v;
        }
    }

    std::unique_ptr<PK3> PK6::convertToG3(Sav& save) const
    {
        if (auto pk5 = convertToG5(save))
        {
            if (auto pk4 = pk5->convertToG4(save))
            {
                return pk4->convertToG3(save);
            }
        }
        return nullptr;
    }

    std::unique_ptr<PK4> PK6::convertToG4(Sav& save) const
    {
        if (auto pk5 = convertToG5(save))
        {
            return pk5->convertToG4(save);
        }
        return nullptr;
    }

    std::unique_ptr<PK5> PK6::convertToG5(Sav& save) const
    {
        auto pk5 = PKX::getPKM<Generation::FIVE>(nullptr);

        pk5->species(species());
        pk5->TID(TID());
        pk5->SID(SID());
        pk5->experience(experience());
        pk5->PID(PID());
        pk5->ability(ability());

        pk5->markValue(markValue());
        pk5->language(language());

        for (int i = 0; i < 6; i++)
        {
            // EV Cap
            pk5->ev(Stat(i), ev(Stat(i)) > 252 ? 252 : ev(Stat(i)));
            pk5->iv(Stat(i), iv(Stat(i)));
            pk5->contest(i, contest(i));
        }

        for (int i = 0; i < 4; i++)
        {
            pk5->move(i, move(i));
            pk5->PPUp(i, PPUp(i));
            pk5->PP(i, PP(i));
        }

        pk5->egg(egg());
        pk5->nicknamed(nicknamed());

        pk5->fatefulEncounter(fatefulEncounter());
        pk5->gender(gender());
        pk5->alternativeForm(alternativeForm());
        pk5->nature(nature());

        pk5->version(version());

        pk5->nickname(nickname());
        pk5->otName(otName());

        pk5->metDate(metDate());
        pk5->eggDate(eggDate());

        pk5->metLocation(metLocation());
        pk5->eggLocation(eggLocation());

        pk5->pkrsStrain(pkrsStrain());
        pk5->pkrsDays(pkrsDays());
        pk5->ball(ball());

        pk5->metLevel(metLevel());
        pk5->otGender(otGender());
        pk5->encounterType(encounterType());

        pk5->ribbon(Ribbon::ChampionG6Hoenn, ribbon(Ribbon::ChampionG6Hoenn));
        pk5->ribbon(Ribbon::ChampionSinnoh, ribbon(Ribbon::ChampionSinnoh));
        pk5->ribbon(Ribbon::Effort, ribbon(Ribbon::Effort));

        pk5->ribbon(Ribbon::Alert, ribbon(Ribbon::Alert));
        pk5->ribbon(Ribbon::Shock, ribbon(Ribbon::Shock));
        pk5->ribbon(Ribbon::Downcast, ribbon(Ribbon::Downcast));
        pk5->ribbon(Ribbon::Careless, ribbon(Ribbon::Careless));
        pk5->ribbon(Ribbon::Relax, ribbon(Ribbon::Relax));
        pk5->ribbon(Ribbon::Snooze, ribbon(Ribbon::Snooze));
        pk5->ribbon(Ribbon::Smile, ribbon(Ribbon::Smile));
        pk5->ribbon(Ribbon::Gorgeous, ribbon(Ribbon::Gorgeous));

        pk5->ribbon(Ribbon::Royal, ribbon(Ribbon::Royal));
        pk5->ribbon(Ribbon::GorgeousRoyal, ribbon(Ribbon::GorgeousRoyal));
        pk5->ribbon(Ribbon::Artist, ribbon(Ribbon::Artist));
        pk5->ribbon(Ribbon::Footprint, ribbon(Ribbon::Footprint));
        pk5->ribbon(Ribbon::Record, ribbon(Ribbon::Record));
        pk5->ribbon(Ribbon::Legend, ribbon(Ribbon::Legend));
        pk5->ribbon(Ribbon::Country, ribbon(Ribbon::Country));
        pk5->ribbon(Ribbon::National, ribbon(Ribbon::National));

        pk5->ribbon(Ribbon::Earth, ribbon(Ribbon::Earth));
        pk5->ribbon(Ribbon::World, ribbon(Ribbon::World));
        pk5->ribbon(Ribbon::Classic, ribbon(Ribbon::Classic));
        pk5->ribbon(Ribbon::Premier, ribbon(Ribbon::Premier));
        pk5->ribbon(Ribbon::Event, ribbon(Ribbon::Event));
        pk5->ribbon(Ribbon::Birthday, ribbon(Ribbon::Birthday));
        pk5->ribbon(Ribbon::Special, ribbon(Ribbon::Special));
        pk5->ribbon(Ribbon::Souvenir, ribbon(Ribbon::Souvenir));

        pk5->ribbon(Ribbon::Wishing, ribbon(Ribbon::Wishing));
        pk5->ribbon(Ribbon::ChampionBattle, ribbon(Ribbon::ChampionBattle));
        pk5->ribbon(Ribbon::ChampionRegional, ribbon(Ribbon::ChampionRegional));
        pk5->ribbon(Ribbon::ChampionNational, ribbon(Ribbon::ChampionNational));
        pk5->ribbon(Ribbon::ChampionWorld, ribbon(Ribbon::ChampionWorld));

        pk5->otFriendship(pk5->baseFriendship());

        // Check if shiny pid needs to be modified
        u16 val = TID() ^ SID() ^ (PID() >> 16) ^ (PID() & 0xFFFF);
        if (shiny() && (val > 7) && (val < 16))
            pk5->PID(PID() ^ 0x80000000);

        for (int i = 0; i < 4; i++)
        {
            if (pk5->move(i) > save.maxMove())
            {
                pk5->move(i, Move::None);
            }
        }

        pk5->refreshChecksum();
        return pk5;
    }

    std::unique_ptr<PK7> PK6::convertToG7(Sav& save) const
    {
        auto pk7 = PKX::getPKM<Generation::SEVEN>(const_cast<u8*>(data));

        // markvalue field moved, clear old gen 6 data
        pk7->rawData()[0x2A] = 0;

        // Bank Data clearing
        for (int i = 0x94; i < 0x9E; i++)
            pk7->rawData()[i] = 0; // Geolocations
        for (int i = 0xAA; i < 0xB0; i++)
            pk7->rawData()[i] = 0; // Amie fullness/enjoyment
        for (int i = 0xE4; i < 0xE8; i++)
            pk7->rawData()[i] = 0;    // unused
        pk7->rawData()[0x72] &= 0xFC; // low 2 bits of super training
        pk7->rawData()[0xDE] = 0;     // gen 4 encounter type

        pk7->markValue(markValue());

        switch (abilityNumber())
        {
            case 1:
            case 2:
            case 4:
                u8 index = abilityNumber() >> 1;
                if (abilities(index) == ability())
                {
                    pk7->ability(pk7->abilities(index));
                }
        }

        pk7->htMemory(4);
        pk7->htTextVar(0);
        pk7->htIntensity(1);
        pk7->htFeeling(pksm::randomNumber(0, 9));
        pk7->geoCountry(0, save.country());
        pk7->geoRegion(0, save.subRegion());

        pk7->currentHandler(1);

        pk7->refreshChecksum();
        return pk7;
    }

    std::unique_ptr<PK8> PK6::convertToG8(Sav& save) const
    {
        auto pk7 = convertToG7(save);
        if (pk7)
        {
            return pk7->convertToG8(save);
        }
        return nullptr;
    }

    void PK6::updatePartyData()
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
