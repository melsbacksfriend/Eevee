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

#include "pkx/PK7.hpp"
#include "pkx/PK3.hpp"
#include "pkx/PK4.hpp"
#include "pkx/PK5.hpp"
#include "pkx/PK6.hpp"
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
            case pksm::Ribbon::ChampionAlola:
                return {0x35, 6};
            case pksm::Ribbon::BattleRoyale:
                return {0x35, 7};
            case pksm::Ribbon::BattleTreeGreat:
                return {0x36, 0};
            case pksm::Ribbon::BattleTreeMaster:
                return {0x36, 1};

            default:
                return {RIBBON_ABSENT, 0};
        }
    }
}

namespace pksm
{
    void PK7::encrypt(void)
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

    void PK7::decrypt(void)
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

    bool PK7::isEncrypted() const
    {
        return LittleEndian::convertTo<u16>(data + 0xC8) != 0 &&
               LittleEndian::convertTo<u16>(data + 0x58) != 0;
    }

    PK7::PK7(PrivateConstructor, u8* dt, bool party, bool direct)
        : PKX(dt, party ? PARTY_LENGTH : BOX_LENGTH, direct)
    {
        if (isEncrypted())
        {
            decrypt();
        }
    }

    std::unique_ptr<PKX> PK7::clone(void) const
    {
        return PKX::getPKM<Generation::SEVEN>(const_cast<u8*>(data), isParty());
    }

    Generation PK7::generation(void) const { return Generation::SEVEN; }

    u32 PK7::encryptionConstant(void) const { return LittleEndian::convertTo<u32>(data); }
    void PK7::encryptionConstant(u32 v) { LittleEndian::convertFrom<u32>(data, v); }

    u16 PK7::sanity(void) const { return LittleEndian::convertTo<u16>(data + 0x04); }
    void PK7::sanity(u16 v) { LittleEndian::convertFrom<u16>(data + 0x04, v); }

    u16 PK7::checksum(void) const { return LittleEndian::convertTo<u16>(data + 0x06); }
    void PK7::checksum(u16 v) { LittleEndian::convertFrom<u16>(data + 0x06, v); }

    Species PK7::species(void) const { return Species{LittleEndian::convertTo<u16>(data + 0x08)}; }
    void PK7::species(Species v) { LittleEndian::convertFrom<u16>(data + 0x08, u16(v)); }

    u16 PK7::heldItem(void) const { return LittleEndian::convertTo<u16>(data + 0x0A); }
    void PK7::heldItem(u16 v) { LittleEndian::convertFrom<u16>(data + 0x0A, v); }

    u16 PK7::TID(void) const { return LittleEndian::convertTo<u16>(data + 0x0C); }
    void PK7::TID(u16 v) { LittleEndian::convertFrom<u16>(data + 0x0C, v); }

    u16 PK7::SID(void) const { return LittleEndian::convertTo<u16>(data + 0x0E); }
    void PK7::SID(u16 v) { LittleEndian::convertFrom<u16>(data + 0x0E, v); }

    u32 PK7::experience(void) const { return LittleEndian::convertTo<u32>(data + 0x10); }
    void PK7::experience(u32 v) { LittleEndian::convertFrom<u32>(data + 0x10, v); }

    Ability PK7::ability(void) const { return Ability{data[0x14]}; }
    void PK7::ability(Ability v) { data[0x14] = u8(v); }

    void PK7::setAbility(u8 v)
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

    u8 PK7::abilityNumber(void) const { return data[0x15]; }
    void PK7::abilityNumber(u8 v) { data[0x15] = v; }

    u16 PK7::markValue(void) const { return LittleEndian::convertTo<u16>(data + 0x16); }
    void PK7::markValue(u16 v) { LittleEndian::convertFrom<u16>(data + 0x16, v); }

    u32 PK7::PID(void) const { return LittleEndian::convertTo<u32>(data + 0x18); }
    void PK7::PID(u32 v) { LittleEndian::convertFrom<u32>(data + 0x18, v); }

    Nature PK7::nature(void) const { return Nature{data[0x1C]}; }
    void PK7::nature(Nature v) { data[0x1C] = u8(v); }

    bool PK7::fatefulEncounter(void) const { return (data[0x1D] & 1) == 1; }
    void PK7::fatefulEncounter(bool v) { data[0x1D] = (u8)((data[0x1D] & ~0x01) | (v ? 1 : 0)); }

    Gender PK7::gender(void) const { return Gender{u8((data[0x1D] >> 1) & 0x3)}; }
    void PK7::gender(Gender v) { data[0x1D] = (data[0x1D] & ~0x06) | (u8(v) << 1); }

    u16 PK7::alternativeForm(void) const { return data[0x1D] >> 3; }
    void PK7::alternativeForm(u16 v) { data[0x1D] = (data[0x1D] & 0x07) | (v << 3); }

    u8 PK7::ev(Stat ev) const { return data[0x1E + u8(ev)]; }
    void PK7::ev(Stat ev, u8 v) { data[0x1E + u8(ev)] = v; }

    u8 PK7::contest(u8 contest) const { return data[0x24 + contest]; }
    void PK7::contest(u8 contest, u8 v) { data[0x24 + contest] = v; }

    u8 PK7::pelagoEventStatus(void) const { return data[0x2A]; }
    void PK7::pelagoEventStatus(u8 v) { data[0x2A] = v; }

    u8 PK7::pkrs(void) const { return data[0x2B]; }
    void PK7::pkrs(u8 v) { data[0x2B] = v; }

    u8 PK7::pkrsDays(void) const { return data[0x2B] & 0xF; };
    void PK7::pkrsDays(u8 v) { data[0x2B] = (u8)((data[0x2B] & ~0xF) | v); }

    u8 PK7::pkrsStrain(void) const { return data[0x2B] >> 4; };
    void PK7::pkrsStrain(u8 v) { data[0x2B] = (u8)((data[0x2B] & 0xF) | v << 4); }

    bool PK7::hasRibbon(Ribbon ribbon) const { return OFFSET_OF(ribbon).first != RIBBON_ABSENT; }
    bool PK7::ribbon(Ribbon ribbon) const
    {
        auto offset = OFFSET_OF(ribbon);
        if (offset.first != RIBBON_ABSENT)
        {
            return FlagUtil::getFlag(data, offset.first, offset.second);
        }
        return false;
    }
    void PK7::ribbon(Ribbon ribbon, bool v)
    {
        auto offset = OFFSET_OF(ribbon);
        if (offset.first != RIBBON_ABSENT)
        {
            FlagUtil::setFlag(data, offset.first, offset.second, v);
        }
    }

    u8 PK7::ribbonContestCount(void) const { return data[0x38]; }
    void PK7::ribbonContestCount(u8 v) { data[0x38] = v; }

    u8 PK7::ribbonBattleCount(void) const { return data[0x39]; }
    void PK7::ribbonBattleCount(u8 v) { data[0x39] = v; }

    std::string PK7::nickname(void) const
    {
        return StringUtils::transString67(StringUtils::getString(data, 0x40, 13));
    }
    void PK7::nickname(const std::string_view& v)
    {
        StringUtils::setString(data, StringUtils::transString67(v), 0x40, 13);
    }

    Move PK7::move(u8 m) const { return Move{LittleEndian::convertTo<u16>(data + 0x5A + m * 2)}; }
    void PK7::move(u8 m, Move v) { LittleEndian::convertFrom<u16>(data + 0x5A + m * 2, u16(v)); }

    u8 PK7::PP(u8 m) const { return data[0x62 + m]; }
    void PK7::PP(u8 m, u8 v) { data[0x62 + m] = v; }

    u8 PK7::PPUp(u8 m) const { return data[0x66 + m]; }
    void PK7::PPUp(u8 m, u8 v) { data[0x66 + m] = v; }

    Move PK7::relearnMove(u8 m) const
    {
        return Move{LittleEndian::convertTo<u16>(data + 0x6A + m * 2)};
    }
    void PK7::relearnMove(u8 m, Move v)
    {
        LittleEndian::convertFrom<u16>(data + 0x6A + m * 2, u16(v));
    }

    u8 PK7::iv(Stat stat) const
    {
        u32 buffer = LittleEndian::convertTo<u32>(data + 0x74);
        return (u8)((buffer >> 5 * u8(stat)) & 0x1F);
    }

    void PK7::iv(Stat stat, u8 v)
    {
        u32 buffer = LittleEndian::convertTo<u32>(data + 0x74);
        buffer &= ~(0x1F << 5 * u8(stat));
        buffer |= v << (5 * u8(stat));
        LittleEndian::convertFrom<u32>(data + 0x74, buffer);
    }

    bool PK7::egg(void) const
    {
        return ((LittleEndian::convertTo<u32>(data + 0x74) >> 30) & 0x1) == 1;
    }
    void PK7::egg(bool v)
    {
        LittleEndian::convertFrom<u32>(
            data + 0x74, (u32)((LittleEndian::convertTo<u32>(data + 0x74) & ~0x40000000) |
                               (u32)(v ? 0x40000000 : 0)));
    }

    bool PK7::nicknamed(void) const
    {
        return ((LittleEndian::convertTo<u32>(data + 0x74) >> 31) & 0x1) == 1;
    }
    void PK7::nicknamed(bool v)
    {
        LittleEndian::convertFrom<u32>(data + 0x74,
            (LittleEndian::convertTo<u32>(data + 0x74) & 0x7FFFFFFF) | (v ? 0x80000000 : 0));
    }

    std::string PK7::htName(void) const
    {
        return StringUtils::transString67(StringUtils::getString(data, 0x78, 13));
    }
    void PK7::htName(const std::string_view& v)
    {
        StringUtils::setString(data, StringUtils::transString67(v), 0x78, 13);
    }

    Gender PK7::htGender(void) const { return Gender{data[0x92]}; }
    void PK7::htGender(Gender v) { data[0x92] = u8(v); }

    u8 PK7::currentHandler(void) const { return data[0x93]; }
    void PK7::currentHandler(u8 v) { data[0x93] = v; }

    u8 PK7::geoRegion(u8 region) const { return data[0x94 + region * 2]; }
    void PK7::geoRegion(u8 region, u8 v) { data[0x94 + region * 2] = v; }

    u8 PK7::geoCountry(u8 country) const { return data[0x95 + country * 2]; }
    void PK7::geoCountry(u8 country, u8 v) { data[0x95 + country * 2] = v; }

    u8 PK7::htFriendship(void) const { return data[0xA2]; }
    void PK7::htFriendship(u8 v) { data[0xA2] = v; }

    u8 PK7::htAffection(void) const { return data[0xA3]; }
    void PK7::htAffection(u8 v) { data[0xA3] = v; }

    u8 PK7::htIntensity(void) const { return data[0xA4]; }
    void PK7::htIntensity(u8 v) { data[0xA4] = v; }

    u8 PK7::htMemory(void) const { return data[0xA5]; }
    void PK7::htMemory(u8 v) { data[0xA5] = v; }

    u8 PK7::htFeeling(void) const { return data[0xA6]; }
    void PK7::htFeeling(u8 v) { data[0xA6] = v; }

    u16 PK7::htTextVar(void) const { return LittleEndian::convertTo<u16>(data + 0xA8); }
    void PK7::htTextVar(u16 v) { LittleEndian::convertFrom<u16>(data + 0xA8, v); }

    u8 PK7::fullness(void) const { return data[0xAE]; }
    void PK7::fullness(u8 v) { data[0xAE] = v; }

    u8 PK7::enjoyment(void) const { return data[0xAF]; }
    void PK7::enjoyment(u8 v) { data[0xAF] = v; }

    std::string PK7::otName(void) const
    {
        return StringUtils::transString67(StringUtils::getString(data, 0xB0, 13));
    }
    void PK7::otName(const std::string_view& v)
    {
        StringUtils::setString(data, StringUtils::transString67(v), 0xB0, 13);
    }

    u8 PK7::otFriendship(void) const { return data[0xCA]; }
    void PK7::otFriendship(u8 v) { data[0xCA] = v; }

    u8 PK7::otAffection(void) const { return data[0xCB]; }
    void PK7::otAffection(u8 v) { data[0xCB] = v; }

    u8 PK7::otIntensity(void) const { return data[0xCC]; }
    void PK7::otIntensity(u8 v) { data[0xCC] = v; }

    u8 PK7::otMemory(void) const { return data[0xCD]; }
    void PK7::otMemory(u8 v) { data[0xCD] = v; }

    u16 PK7::otTextVar(void) const { return LittleEndian::convertTo<u16>(data + 0xCE); }
    void PK7::otTextVar(u16 v) { LittleEndian::convertFrom<u16>(data + 0xCE, v); }

    u8 PK7::otFeeling(void) const { return data[0xD0]; }
    void PK7::otFeeling(u8 v) { data[0xD0] = v; }

    int PK7::eggYear(void) const { return 2000 + data[0xD1]; }
    void PK7::eggYear(int v) { data[0xD1] = v - 2000; }

    int PK7::eggMonth(void) const { return data[0xD2]; }
    void PK7::eggMonth(int v) { data[0xD2] = v; }

    int PK7::eggDay(void) const { return data[0xD3]; }
    void PK7::eggDay(int v) { data[0xD3] = v; }

    int PK7::metYear(void) const { return 2000 + data[0xD4]; }
    void PK7::metYear(int v) { data[0xD4] = v - 2000; }

    int PK7::metMonth(void) const { return data[0xD5]; }
    void PK7::metMonth(int v) { data[0xD5] = v; }

    int PK7::metDay(void) const { return data[0xD6]; }
    void PK7::metDay(int v) { data[0xD6] = v; }

    u16 PK7::eggLocation(void) const { return LittleEndian::convertTo<u16>(data + 0xD8); }
    void PK7::eggLocation(u16 v) { LittleEndian::convertFrom<u16>(data + 0xD8, v); }

    u16 PK7::metLocation(void) const { return LittleEndian::convertTo<u16>(data + 0xDA); }
    void PK7::metLocation(u16 v) { LittleEndian::convertFrom<u16>(data + 0xDA, v); }

    Ball PK7::ball(void) const { return Ball{data[0xDC]}; }
    void PK7::ball(Ball v) { data[0xDC] = u8(v); }

    u8 PK7::metLevel(void) const { return data[0xDD] & ~0x80; }
    void PK7::metLevel(u8 v) { data[0xDD] = (data[0xDD] & 0x80) | v; }

    Gender PK7::otGender(void) const { return Gender{u8(data[0xDD] >> 7)}; }
    void PK7::otGender(Gender v) { data[0xDD] = (data[0xDD] & ~0x80) | (u8(v) << 7); }

    bool PK7::hyperTrain(Stat stat) const
    {
        return (data[0xDE] & (1 << hyperTrainLookup[size_t(stat)])) ==
               1 << hyperTrainLookup[size_t(stat)];
    }
    void PK7::hyperTrain(Stat stat, bool v)
    {
        data[0xDE] = (u8)((data[0xDE] & ~(1 << hyperTrainLookup[size_t(stat)])) |
                          (v ? 1 << hyperTrainLookup[size_t(stat)] : 0));
    }

    GameVersion PK7::version(void) const { return GameVersion(data[0xDF]); }
    void PK7::version(GameVersion v) { data[0xDF] = u8(v); }

    u8 PK7::country(void) const { return data[0xE0]; }
    void PK7::country(u8 v) { data[0xE0] = v; }

    u8 PK7::region(void) const { return data[0xE1]; }
    void PK7::region(u8 v) { data[0xE1] = v; }

    u8 PK7::consoleRegion(void) const { return data[0xE2]; }
    void PK7::consoleRegion(u8 v) { data[0xE2] = v; }

    Language PK7::language(void) const { return Language(data[0xE3]); }
    void PK7::language(Language v) { data[0xE3] = u8(v); }

    u8 PK7::currentFriendship(void) const
    {
        return currentHandler() == 0 ? otFriendship() : htFriendship();
    }
    void PK7::currentFriendship(u8 v)
    {
        if (currentHandler() == 0)
            otFriendship(v);
        else
            htFriendship(v);
    }

    u8 PK7::oppositeFriendship(void) const
    {
        return currentHandler() == 1 ? otFriendship() : htFriendship();
    }
    void PK7::oppositeFriendship(u8 v)
    {
        if (currentHandler() == 1)
            otFriendship(v);
        else
            htFriendship(v);
    }

    void PK7::refreshChecksum(void)
    {
        u16 chk = 0;
        for (u8 i = 8; i < BOX_LENGTH; i += 2)
        {
            chk += LittleEndian::convertTo<u16>(data + i);
        }
        checksum(chk);
    }

    Type PK7::hpType(void) const
    {
        return Type{u8((15 *
                           ((iv(Stat::HP) & 1) + 2 * (iv(Stat::ATK) & 1) + 4 * (iv(Stat::DEF) & 1) +
                               8 * (iv(Stat::SPD) & 1) + 16 * (iv(Stat::SPATK) & 1) +
                               32 * (iv(Stat::SPDEF) & 1)) /
                           63) +
                       1)};
    }
    void PK7::hpType(Type v)
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
            iv(Stat(i), (iv(Stat(i)) & 0x1E) + hpivs[u8(v) - 1][i]);
        }
    }

    u16 PK7::TSV(void) const { return (TID() ^ SID()) >> 4; }
    u16 PK7::PSV(void) const { return ((PID() >> 16) ^ (PID() & 0xFFFF)) >> 4; }

    u8 PK7::level(void) const
    {
        u8 i      = 1;
        u8 xpType = expType();
        while (experience() >= expTable(i, xpType) && ++i < 100)
            ;
        return i;
    }

    void PK7::level(u8 v) { experience(expTable(v - 1, expType())); }

    bool PK7::shiny(void) const { return TSV() == PSV(); }
    void PK7::shiny(bool v)
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

    u16 PK7::formSpecies(void) const
    {
        u16 tmpSpecies = u16(species());
        u8 form        = alternativeForm();
        u8 formcount   = PersonalSMUSUM::formCount(tmpSpecies);

        if (form && form < formcount)
        {
            u16 backSpecies = tmpSpecies;
            tmpSpecies      = PersonalSMUSUM::formStatIndex(tmpSpecies);
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

    u16 PK7::stat(Stat stat) const
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
            calc =
                10 + ((2 * basestat) +
                         ((((data[0xDE] >> hyperTrainLookup[u8(stat)]) & 1) == 1) ? 31 : iv(stat)) +
                         ev(stat) / 4 + 100) *
                         level() / 100;
        else
            calc =
                5 + (2 * basestat +
                        ((((data[0xDE] >> hyperTrainLookup[u8(stat)]) & 1) == 1) ? 31 : iv(stat)) +
                        ev(stat) / 4) *
                        level() / 100;
        if (u8(nature()) / 5 + 1 == u8(stat))
            mult++;
        if (u8(nature()) % 5 + 1 == u8(stat))
            mult--;
        return calc * mult / 10;
    }

    std::unique_ptr<PK3> PK7::convertToG3(Sav& save) const
    {
        if (auto pk6 = convertToG6(save))
        {
            if (auto pk5 = pk6->convertToG5(save))
            {
                if (auto pk4 = pk5->convertToG4(save))
                {
                    return pk4->convertToG3(save);
                }
            }
        }
        return nullptr;
    }

    std::unique_ptr<PK4> PK7::convertToG4(Sav& save) const
    {
        if (auto pk6 = convertToG6(save))
        {
            if (auto pk5 = pk6->convertToG5(save))
            {
                return pk5->convertToG4(save);
            }
        }
        return nullptr;
    }

    std::unique_ptr<PK5> PK7::convertToG5(Sav& save) const
    {
        if (auto pk6 = convertToG6(save))
        {
            return pk6->convertToG5(save);
        }
        return nullptr;
    }

    std::unique_ptr<PK6> PK7::convertToG6(Sav& save) const
    {
        auto pk6 = PKX::getPKM<Generation::SIX>(const_cast<u8*>(data));

        // markvalue field moved, clear old gen 7 data
        LittleEndian::convertFrom<u16>(pk6->rawData() + 0x16, 0);

        pk6->markValue(markValue());

        switch (abilityNumber())
        {
            case 1:
            case 2:
            case 4:
                u8 index = abilityNumber() >> 1;
                if (abilities(index) == ability())
                {
                    pk6->ability(pk6->abilities(index));
                }
        }

        pk6->htMemory(4);
        pk6->htTextVar(0);
        pk6->htIntensity(1);
        pk6->htFeeling(pksm::randomNumber(0, 9));
        pk6->geoCountry(0, save.country());
        pk6->geoRegion(0, save.subRegion());

        for (int i = 0; i < 4; i++)
        {
            if (pk6->move(i) > save.maxMove())
            {
                pk6->move(i, Move::None);
            }
            if (pk6->relearnMove(i) > save.maxMove())
            {
                pk6->relearnMove(i, Move::None);
            }
        }
        pk6->fixMoves();

        pk6->refreshChecksum();
        return pk6;
    }

    std::unique_ptr<PK8> PK7::convertToG8(Sav& save) const
    {
        auto pk8 = PKX::getPKM<Generation::EIGHT>(nullptr, false);

        // Note: Locale stuff does not transfer
        pk8->encryptionConstant(encryptionConstant());
        pk8->species(species());
        pk8->TID(TID());
        pk8->SID(SID());
        pk8->experience(experience());
        pk8->PID(PID());
        if (ability() == PersonalSMUSUM::ability(formSpecies(), abilityNumber() >> 1))
        {
            pk8->setAbility(abilityNumber() >> 1);
        }
        else
        {
            pk8->ability(ability());
            pk8->abilityNumber(abilityNumber());
        }
        pk8->language(language());
        for (Stat stat : {Stat::HP, Stat::ATK, Stat::DEF, Stat::SPATK, Stat::SPDEF, Stat::SPD})
        {
            pk8->ev(stat, ev(stat));
            pk8->iv(stat, iv(stat));
            pk8->hyperTrain(stat, hyperTrain(stat));
        }
        for (size_t i = 0; i < 4; i++)
        {
            pk8->move(i, move(i));
            pk8->PPUp(i, PPUp(i));
            pk8->PP(i, PP(i));
            pk8->relearnMove(i, relearnMove(i));
        }
        pk8->egg(egg());
        pk8->nicknamed(nicknamed());
        pk8->nickname(nickname());
        pk8->fatefulEncounter(fatefulEncounter());
        pk8->gender(gender());
        pk8->otGender(otGender());
        pk8->alternativeForm(alternativeForm());
        pk8->nature(nature());
        pk8->version(version());
        pk8->otName(otName());
        pk8->metDate(metDate());
        pk8->eggDate(eggDate());
        pk8->metLocation(metLocation());
        pk8->eggLocation(eggLocation());
        pk8->ball(ball());
        pk8->metLevel(metLevel());

        // TODO from PKHeX: set proper memories
        pk8->otMemory(otMemory());
        pk8->otTextVar(otTextVar());
        pk8->otFeeling(otFeeling());
        pk8->otIntensity(otIntensity());

        pk8->pkrsStrain(pkrsStrain());
        pk8->pkrsDays(pkrsDays());

        for (size_t i = 0; i < 6; i++)
        {
            pk8->contest(i, contest(i));
        }

        pk8->ribbon(Ribbon::ChampionG3Hoenn, ribbon(Ribbon::ChampionG3Hoenn));
        pk8->ribbon(Ribbon::ChampionSinnoh, ribbon(Ribbon::ChampionSinnoh));
        pk8->ribbon(Ribbon::Effort, ribbon(Ribbon::Effort));
        pk8->ribbon(Ribbon::Alert, ribbon(Ribbon::Alert));
        pk8->ribbon(Ribbon::Shock, ribbon(Ribbon::Shock));
        pk8->ribbon(Ribbon::Downcast, ribbon(Ribbon::Downcast));
        pk8->ribbon(Ribbon::Careless, ribbon(Ribbon::Careless));
        pk8->ribbon(Ribbon::Relax, ribbon(Ribbon::Relax));
        pk8->ribbon(Ribbon::Snooze, ribbon(Ribbon::Snooze));
        pk8->ribbon(Ribbon::Smile, ribbon(Ribbon::Smile));
        pk8->ribbon(Ribbon::Gorgeous, ribbon(Ribbon::Gorgeous));
        pk8->ribbon(Ribbon::Royal, ribbon(Ribbon::Royal));
        pk8->ribbon(Ribbon::GorgeousRoyal, ribbon(Ribbon::GorgeousRoyal));
        pk8->ribbon(Ribbon::Artist, ribbon(Ribbon::Artist));
        pk8->ribbon(Ribbon::Footprint, ribbon(Ribbon::Footprint));
        pk8->ribbon(Ribbon::Record, ribbon(Ribbon::Record));
        pk8->ribbon(Ribbon::Legend, ribbon(Ribbon::Legend));
        pk8->ribbon(Ribbon::Country, ribbon(Ribbon::Country));
        pk8->ribbon(Ribbon::National, ribbon(Ribbon::National));
        pk8->ribbon(Ribbon::Earth, ribbon(Ribbon::Earth));
        pk8->ribbon(Ribbon::World, ribbon(Ribbon::World));
        pk8->ribbon(Ribbon::Classic, ribbon(Ribbon::Classic));
        pk8->ribbon(Ribbon::Premier, ribbon(Ribbon::Premier));
        pk8->ribbon(Ribbon::Event, ribbon(Ribbon::Event));
        pk8->ribbon(Ribbon::Birthday, ribbon(Ribbon::Birthday));
        pk8->ribbon(Ribbon::Special, ribbon(Ribbon::Special));
        pk8->ribbon(Ribbon::Souvenir, ribbon(Ribbon::Souvenir));
        pk8->ribbon(Ribbon::Wishing, ribbon(Ribbon::Wishing));
        pk8->ribbon(Ribbon::ChampionBattle, ribbon(Ribbon::ChampionBattle));
        pk8->ribbon(Ribbon::ChampionRegional, ribbon(Ribbon::ChampionRegional));
        pk8->ribbon(Ribbon::ChampionNational, ribbon(Ribbon::ChampionNational));
        pk8->ribbon(Ribbon::ChampionWorld, ribbon(Ribbon::ChampionWorld));
        pk8->ribbon(Ribbon::ChampionKalos, ribbon(Ribbon::ChampionKalos));
        pk8->ribbon(Ribbon::ChampionG6Hoenn, ribbon(Ribbon::ChampionG6Hoenn));
        pk8->ribbon(Ribbon::BestFriends, ribbon(Ribbon::BestFriends));
        pk8->ribbon(Ribbon::Training, ribbon(Ribbon::Training));
        pk8->ribbon(Ribbon::BattlerSkillful, ribbon(Ribbon::BattlerSkillful));
        pk8->ribbon(Ribbon::BattlerExpert, ribbon(Ribbon::BattlerExpert));
        pk8->ribbon(Ribbon::ContestStar, ribbon(Ribbon::ContestStar));
        pk8->ribbon(Ribbon::MasterCoolness, ribbon(Ribbon::MasterCoolness));
        pk8->ribbon(Ribbon::MasterBeauty, ribbon(Ribbon::MasterBeauty));
        pk8->ribbon(Ribbon::MasterCuteness, ribbon(Ribbon::MasterCuteness));
        pk8->ribbon(Ribbon::MasterCleverness, ribbon(Ribbon::MasterCleverness));
        pk8->ribbon(Ribbon::MasterToughness, ribbon(Ribbon::MasterToughness));
        pk8->ribbon(Ribbon::ChampionAlola, ribbon(Ribbon::ChampionAlola));
        pk8->ribbon(Ribbon::BattleRoyale, ribbon(Ribbon::BattleRoyale));
        pk8->ribbon(Ribbon::BattleTreeGreat, ribbon(Ribbon::BattleTreeGreat));
        pk8->ribbon(Ribbon::BattleTreeMaster, ribbon(Ribbon::BattleTreeMaster));

        pk8->ribbonContestCount(ribbonContestCount());
        pk8->ribbonBattleCount(ribbonBattleCount());

        pk8->otFriendship(otFriendship());
        pk8->origNature(nature());

        // TODO: remove totem forms

        pk8->refreshChecksum();

        return pk8;
    }

    int PK7::partyCurrHP(void) const
    {
        if (!isParty())
        {
            return -1;
        }
        return LittleEndian::convertTo<u16>(data + 0xF0);
    }

    void PK7::partyCurrHP(u16 v)
    {
        if (isParty())
        {
            LittleEndian::convertFrom<u16>(data + 0xF0, v);
        }
    }

    int PK7::partyStat(Stat stat) const
    {
        if (!isParty())
        {
            return -1;
        }
        return LittleEndian::convertTo<u16>(data + 0xF2 + u8(stat) * 2);
    }

    void PK7::partyStat(Stat stat, u16 v)
    {
        if (isParty())
        {
            LittleEndian::convertFrom<u16>(data + 0xF2 + u8(stat) * 2, v);
        }
    }

    int PK7::partyLevel() const
    {
        if (!isParty())
        {
            return -1;
        }
        return *(data + 0xEC);
    }

    void PK7::partyLevel(u8 v)
    {
        if (isParty())
        {
            *(data + 0xEC) = v;
        }
    }

    void PK7::updatePartyData()
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
