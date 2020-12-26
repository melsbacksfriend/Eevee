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

#include "pkx/PK5.hpp"
#include "pkx/PK3.hpp"
#include "pkx/PK4.hpp"
#include "pkx/PK6.hpp"
#include "pkx/PK7.hpp"
#include "pkx/PK8.hpp"
#include "sav/Sav.hpp"
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
            case pksm::Ribbon::ChampionSinnoh:
                return {0x24, 0};
            case pksm::Ribbon::Ability:
                return {0x24, 1};
            case pksm::Ribbon::AbilityGreat:
                return {0x24, 2};
            case pksm::Ribbon::AbilityDouble:
                return {0x24, 3};
            case pksm::Ribbon::AbilityMulti:
                return {0x24, 4};
            case pksm::Ribbon::AbilityPair:
                return {0x24, 5};
            case pksm::Ribbon::AbilityWorld:
                return {0x24, 6};
            case pksm::Ribbon::Alert:
                return {0x24, 7};
            case pksm::Ribbon::Shock:
                return {0x25, 0};
            case pksm::Ribbon::Downcast:
                return {0x25, 1};
            case pksm::Ribbon::Careless:
                return {0x25, 2};
            case pksm::Ribbon::Relax:
                return {0x25, 3};
            case pksm::Ribbon::Snooze:
                return {0x25, 4};
            case pksm::Ribbon::Smile:
                return {0x25, 5};
            case pksm::Ribbon::Gorgeous:
                return {0x25, 6};
            case pksm::Ribbon::Royal:
                return {0x25, 7};
            case pksm::Ribbon::GorgeousRoyal:
                return {0x26, 0};
            case pksm::Ribbon::Footprint:
                return {0x26, 1};
            case pksm::Ribbon::Record:
                return {0x26, 2};
            case pksm::Ribbon::Event:
                return {0x26, 3};
            case pksm::Ribbon::Legend:
                return {0x26, 4};
            case pksm::Ribbon::ChampionWorld:
                return {0x26, 5};
            case pksm::Ribbon::Birthday:
                return {0x26, 6};
            case pksm::Ribbon::Special:
                return {0x26, 7};
            case pksm::Ribbon::Souvenir:
                return {0x27, 0};
            case pksm::Ribbon::Wishing:
                return {0x27, 1};
            case pksm::Ribbon::Classic:
                return {0x27, 2};
            case pksm::Ribbon::Premier:
                return {0x27, 3};
            case pksm::Ribbon::G3Cool:
                return {0X3C, 0};
            case pksm::Ribbon::G3CoolSuper:
                return {0X3C, 1};
            case pksm::Ribbon::G3CoolHyper:
                return {0X3C, 2};
            case pksm::Ribbon::G3CoolMaster:
                return {0X3C, 3};
            case pksm::Ribbon::G3Beauty:
                return {0X3C, 4};
            case pksm::Ribbon::G3BeautySuper:
                return {0X3C, 5};
            case pksm::Ribbon::G3BeautyHyper:
                return {0X3C, 6};
            case pksm::Ribbon::G3BeautyMaster:
                return {0X3C, 7};
            case pksm::Ribbon::G3Cute:
                return {0x3D, 0};
            case pksm::Ribbon::G3CuteSuper:
                return {0x3D, 1};
            case pksm::Ribbon::G3CuteHyper:
                return {0x3D, 2};
            case pksm::Ribbon::G3CuteMaster:
                return {0x3D, 3};
            case pksm::Ribbon::G3Smart:
                return {0x3D, 4};
            case pksm::Ribbon::G3SmartSuper:
                return {0x3D, 5};
            case pksm::Ribbon::G3SmartHyper:
                return {0x3D, 6};
            case pksm::Ribbon::G3SmartMaster:
                return {0x3D, 7};
            case pksm::Ribbon::G3Tough:
                return {0x3E, 0};
            case pksm::Ribbon::G3ToughSuper:
                return {0x3E, 1};
            case pksm::Ribbon::G3ToughHyper:
                return {0x3E, 2};
            case pksm::Ribbon::G3ToughMaster:
                return {0x3E, 3};
            case pksm::Ribbon::ChampionG3Hoenn:
                return {0x3E, 4};
            case pksm::Ribbon::Winning:
                return {0x3E, 5};
            case pksm::Ribbon::Victory:
                return {0x3E, 6};
            case pksm::Ribbon::Artist:
                return {0x3E, 7};
            case pksm::Ribbon::Effort:
                return {0x3F, 0};
            case pksm::Ribbon::ChampionBattle:
                return {0x3F, 1};
            case pksm::Ribbon::ChampionRegional:
                return {0x3F, 2};
            case pksm::Ribbon::ChampionNational:
                return {0x3F, 3};
            case pksm::Ribbon::Country:
                return {0x3F, 4};
            case pksm::Ribbon::National:
                return {0x3F, 5};
            case pksm::Ribbon::Earth:
                return {0x3F, 6};
            case pksm::Ribbon::World:
                return {0x3F, 7};
            case pksm::Ribbon::G4Cool:
                return {0x60, 0};
            case pksm::Ribbon::G4CoolGreat:
                return {0x60, 1};
            case pksm::Ribbon::G4CoolUltra:
                return {0x60, 2};
            case pksm::Ribbon::G4CoolMaster:
                return {0x60, 3};
            case pksm::Ribbon::G4Beauty:
                return {0x60, 4};
            case pksm::Ribbon::G4BeautyGreat:
                return {0x60, 5};
            case pksm::Ribbon::G4BeautyUltra:
                return {0x60, 6};
            case pksm::Ribbon::G4BeautyMaster:
                return {0x60, 7};
            case pksm::Ribbon::G4Cute:
                return {0x61, 0};
            case pksm::Ribbon::G4CuteGreat:
                return {0x61, 1};
            case pksm::Ribbon::G4CuteUltra:
                return {0x61, 2};
            case pksm::Ribbon::G4CuteMaster:
                return {0x61, 3};
            case pksm::Ribbon::G4Smart:
                return {0x61, 4};
            case pksm::Ribbon::G4SmartGreat:
                return {0x61, 5};
            case pksm::Ribbon::G4SmartUltra:
                return {0x61, 6};
            case pksm::Ribbon::G4SmartMaster:
                return {0x61, 7};
            case pksm::Ribbon::G4Tough:
                return {0x62, 0};
            case pksm::Ribbon::G4ToughGreat:
                return {0x62, 1};
            case pksm::Ribbon::G4ToughUltra:
                return {0x62, 2};
            case pksm::Ribbon::G4ToughMaster:
                return {0x62, 3};

            default:
                return {RIBBON_ABSENT, 0};
        }
    }

    void fixString(std::u16string& fixString)
    {
        for (size_t i = 0; i < fixString.size(); i++)
        {
            if (fixString[i] == u'\u2467')
            {
                fixString[i] = u'\u00d7';
            }
            else if (fixString[i] == u'\u2468')
            {
                fixString[i] = u'\u00f7';
            }
            else if (fixString[i] == u'\u246c')
            {
                fixString[i] = u'\u2026';
            }
            else if (fixString[i] == u'\u246d')
            {
                fixString[i] = u'\uE08E';
            }
            else if (fixString[i] == u'\u246e')
            {
                fixString[i] = u'\uE08F';
            }
            else if (fixString[i] == u'\u246f')
            {
                fixString[i] = u'\uE090';
            }
            else if (fixString[i] == u'\u2470')
            {
                fixString[i] = u'\uE091';
            }
            else if (fixString[i] == u'\u2471')
            {
                fixString[i] = u'\uE092';
            }
            else if (fixString[i] == u'\u2472')
            {
                fixString[i] = u'\uE093';
            }
            else if (fixString[i] == u'\u2473')
            {
                fixString[i] = u'\uE094';
            }
            else if (fixString[i] == u'\u2474')
            {
                fixString[i] = u'\uE095';
            }
            else if (fixString[i] == u'\u2475')
            {
                fixString[i] = u'\uE096';
            }
            else if (fixString[i] == u'\u2476')
            {
                fixString[i] = u'\uE097';
            }
            else if (fixString[i] == u'\u2477')
            {
                fixString[i] = u'\uE098';
            }
            else if (fixString[i] == u'\u2478')
            {
                fixString[i] = u'\uE099';
            }
            else if (fixString[i] == u'\u2479')
            {
                fixString[i] = u'\uE09A';
            }
            else if (fixString[i] == u'\u247a')
            {
                fixString[i] = u'\uE09B';
            }
            else if (fixString[i] == u'\u247b')
            {
                fixString[i] = u'\uE09C';
            }
            else if (fixString[i] == u'\u247d')
            {
                fixString[i] = u'\uE09D';
            }
        }
    }
}

namespace pksm
{
    void PK5::encrypt(void)
    {
        if (!isEncrypted())
        {
            u8 sv = (encryptionConstant() >> 13) & 31;
            refreshChecksum();
            pksm::crypto::pkm::blockShuffle<BLOCK_LENGTH>(
                data + ENCRYPTION_START, pksm::crypto::pkm::InvertedBlockPositions[sv]);
            pksm::crypto::pkm::crypt<BOX_LENGTH - ENCRYPTION_START>(
                data + ENCRYPTION_START, checksum());
            if (isParty())
            {
                pksm::crypto::pkm::crypt<PARTY_LENGTH - BOX_LENGTH>(data + BOX_LENGTH, PID());
            }
        }
    }

    void PK5::decrypt(void)
    {
        if (isEncrypted())
        {
            u8 sv = (encryptionConstant() >> 13) & 31;
            pksm::crypto::pkm::crypt<BOX_LENGTH - ENCRYPTION_START>(
                data + ENCRYPTION_START, checksum());
            if (isParty())
            {
                pksm::crypto::pkm::crypt<PARTY_LENGTH - BOX_LENGTH>(data + BOX_LENGTH, PID());
            }
            pksm::crypto::pkm::blockShuffle<BLOCK_LENGTH>(data + ENCRYPTION_START, sv);
        }
    }

    bool PK5::isEncrypted() const { return LittleEndian::convertTo<u32>(data + 0x64) != 0; }

    PK5::PK5(PrivateConstructor, u8* dt, bool party, bool direct)
        : PKX(dt, party ? PARTY_LENGTH : BOX_LENGTH, direct)
    {
        if (isEncrypted())
        {
            decrypt();
        }
    }

    std::unique_ptr<PKX> PK5::clone(void) const
    {
        return PKX::getPKM<Generation::FIVE>(const_cast<u8*>(data), isParty());
    }

    Generation PK5::generation(void) const { return Generation::FIVE; }

    u32 PK5::encryptionConstant(void) const { return PID(); }
    void PK5::encryptionConstant(u32) {}

    u8 PK5::currentFriendship(void) const { return otFriendship(); }
    void PK5::currentFriendship(u8 v) { otFriendship(v); }

    u8 PK5::abilityNumber(void) const { return hiddenAbility() ? 4 : 1 << ((PID() >> 16) & 1); }
    void PK5::abilityNumber(u8 v)
    {
        if (v == 1 || v == 2)
        {
            if (shiny())
            {
                do
                {
                    PID(PKX::getRandomPID(species(), gender(), version(), nature(),
                        alternativeForm(), v, PID(), generation()));
                } while (!shiny());
            }
            else
            {
                do
                {
                    PID(PKX::getRandomPID(species(), gender(), version(), nature(),
                        alternativeForm(), v, PID(), generation()));
                } while (shiny());
            }
            hiddenAbility(false);
        }
        else // Hidden ability
        {
            hiddenAbility(true);
        }
    }

    u32 PK5::PID(void) const { return LittleEndian::convertTo<u32>(data); }
    void PK5::PID(u32 v) { LittleEndian::convertFrom<u32>(data, v); }

    u16 PK5::sanity(void) const { return LittleEndian::convertTo<u16>(data + 0x04); }
    void PK5::sanity(u16 v) { LittleEndian::convertFrom<u16>(data + 0x04, v); }

    u16 PK5::checksum(void) const { return LittleEndian::convertTo<u16>(data + 0x06); }
    void PK5::checksum(u16 v) { LittleEndian::convertFrom<u16>(data + 0x06, v); }

    Species PK5::species(void) const { return Species{LittleEndian::convertTo<u16>(data + 0x08)}; }
    void PK5::species(Species v) { LittleEndian::convertFrom<u16>(data + 0x08, u16(v)); }

    u16 PK5::heldItem(void) const { return LittleEndian::convertTo<u16>(data + 0x0A); }
    void PK5::heldItem(u16 v) { LittleEndian::convertFrom<u16>(data + 0x0A, v); }

    u16 PK5::TID(void) const { return LittleEndian::convertTo<u16>(data + 0x0C); }
    void PK5::TID(u16 v) { LittleEndian::convertFrom<u16>(data + 0x0C, v); }

    u16 PK5::SID(void) const { return LittleEndian::convertTo<u16>(data + 0x0E); }
    void PK5::SID(u16 v) { LittleEndian::convertFrom<u16>(data + 0x0E, v); }

    u32 PK5::experience(void) const { return LittleEndian::convertTo<u32>(data + 0x10); }
    void PK5::experience(u32 v) { LittleEndian::convertFrom<u32>(data + 0x10, v); }

    u8 PK5::otFriendship(void) const { return data[0x14]; }
    void PK5::otFriendship(u8 v) { data[0x14] = v; }

    Ability PK5::ability(void) const { return Ability{data[0x15]}; }
    void PK5::ability(Ability v) { data[0x15] = u8(v); }

    void PK5::setAbility(u8 v)
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

    u16 PK5::markValue(void) const { return data[0x16]; }
    void PK5::markValue(u16 v) { data[0x16] = v; }

    Language PK5::language(void) const { return Language(data[0x17]); }
    void PK5::language(Language v) { data[0x17] = u8(v); }

    u8 PK5::ev(Stat ev) const { return data[0x18 + u8(ev)]; }
    void PK5::ev(Stat ev, u8 v) { data[0x18 + u8(ev)] = v; }

    u8 PK5::contest(u8 contest) const { return data[0x1E + contest]; }
    void PK5::contest(u8 contest, u8 v) { data[0x1E + contest] = v; }

    bool PK5::hasRibbon(Ribbon ribbon) const { return OFFSET_OF(ribbon).first != RIBBON_ABSENT; }
    bool PK5::ribbon(Ribbon ribbon) const
    {
        auto offset = OFFSET_OF(ribbon);
        if (offset.first != RIBBON_ABSENT)
        {
            return FlagUtil::getFlag(data, offset.first, offset.second);
        }
        return false;
    }
    void PK5::ribbon(Ribbon ribbon, bool v)
    {
        auto offset = OFFSET_OF(ribbon);
        if (offset.first != RIBBON_ABSENT)
        {
            FlagUtil::setFlag(data, offset.first, offset.second, v);
        }
    }

    Move PK5::move(u8 m) const { return Move{LittleEndian::convertTo<u16>(data + 0x28 + m * 2)}; }
    void PK5::move(u8 m, Move v) { LittleEndian::convertFrom<u16>(data + 0x28 + m * 2, u16(v)); }

    u8 PK5::PP(u8 m) const { return data[0x30 + m]; }
    void PK5::PP(u8 m, u8 v) { data[0x30 + m] = v; }

    u8 PK5::PPUp(u8 m) const { return data[0x34 + m]; }
    void PK5::PPUp(u8 m, u8 v) { data[0x34 + m] = v; }

    u8 PK5::iv(Stat stat) const
    {
        u32 buffer = LittleEndian::convertTo<u32>(data + 0x38);
        return (u8)((buffer >> 5 * u8(stat)) & 0x1F);
    }

    void PK5::iv(Stat stat, u8 v)
    {
        u32 buffer = LittleEndian::convertTo<u32>(data + 0x38);
        buffer &= ~(0x1F << 5 * u8(stat));
        buffer |= v << (5 * u8(stat));
        LittleEndian::convertFrom<u32>(data + 0x38, buffer);
    }

    bool PK5::egg(void) const
    {
        return ((LittleEndian::convertTo<u32>(data + 0x38) >> 30) & 0x1) == 1;
    }
    void PK5::egg(bool v)
    {
        LittleEndian::convertFrom<u32>(
            data + 0x38, (u32)((LittleEndian::convertTo<u32>(data + 0x38) & ~0x40000000) |
                               (u32)(v ? 0x40000000 : 0)));
    }

    bool PK5::nicknamed(void) const
    {
        return ((LittleEndian::convertTo<u32>(data + 0x38) >> 31) & 0x1) == 1;
    }
    void PK5::nicknamed(bool v)
    {
        LittleEndian::convertFrom<u32>(data + 0x38,
            (LittleEndian::convertTo<u32>(data + 0x38) & 0x7FFFFFFF) | (v ? 0x80000000 : 0));
    }

    bool PK5::fatefulEncounter(void) const { return (data[0x40] & 1) == 1; }
    void PK5::fatefulEncounter(bool v) { data[0x40] = (u8)((data[0x40] & ~0x01) | (v ? 1 : 0)); }

    Gender PK5::gender(void) const { return Gender{u8((data[0x40] >> 1) & 0x3)}; }
    void PK5::gender(Gender g)
    {
        data[0x40] = (data[0x40] & ~0x06) | (u8(g) << 1);
        if (shiny())
        {
            do
            {
                PID(PKX::getRandomPID(species(), g, version(), nature(), alternativeForm(),
                    abilityNumber(), PID(), generation()));
            } while (!shiny());
        }
        else
        {
            do
            {
                PID(PKX::getRandomPID(species(), g, version(), nature(), alternativeForm(),
                    abilityNumber(), PID(), generation()));
            } while (shiny());
        }
    }

    u16 PK5::alternativeForm(void) const { return data[0x40] >> 3; }
    void PK5::alternativeForm(u16 v) { data[0x40] = (data[0x40] & 0x07) | (v << 3); }

    Nature PK5::nature(void) const { return Nature{data[0x41]}; }
    void PK5::nature(Nature v) { data[0x41] = u8(v); }

    bool PK5::hiddenAbility(void) const { return (data[0x42] & 1) == 1; }
    void PK5::hiddenAbility(bool v) { data[0x42] = (u8)((data[0x42] & ~0x01) | (v ? 1 : 0)); }

    bool PK5::nPokemon(void) const { return (data[0x42] & 2) == 2; }
    void PK5::nPokemon(bool v) { data[0x42] = (u8)((data[0x42] & ~0x02) | (v ? 2 : 0)); }

    std::string PK5::nickname(void) const
    {
        return StringUtils::transString45(StringUtils::getString(data, 0x48, 11, u'\uFFFF'));
    }
    void PK5::nickname(const std::string_view& v)
    {
        StringUtils::setString(data, StringUtils::transString45(v), 0x48, 11, u'\uFFFF', 0);
    }

    GameVersion PK5::version(void) const { return GameVersion(data[0x5F]); }
    void PK5::version(GameVersion v) { data[0x5F] = u8(v); }

    std::string PK5::otName(void) const
    {
        return StringUtils::transString45(StringUtils::getString(data, 0x68, 8, u'\uFFFF'));
    }
    void PK5::otName(const std::string_view& v)
    {
        StringUtils::setString(data, StringUtils::transString45(v), 0x68, 8, u'\uFFFF', 0);
    }

    int PK5::eggYear(void) const { return 2000 + data[0x78]; }
    void PK5::eggYear(int v) { data[0x78] = v - 2000; }

    int PK5::eggMonth(void) const { return data[0x79]; }
    void PK5::eggMonth(int v) { data[0x79] = v; }

    int PK5::eggDay(void) const { return data[0x7A]; }
    void PK5::eggDay(int v) { data[0x7A] = v; }

    int PK5::metYear(void) const { return 2000 + data[0x7B]; }
    void PK5::metYear(int v) { data[0x7B] = v - 2000; }

    int PK5::metMonth(void) const { return data[0x7C]; }
    void PK5::metMonth(int v) { data[0x7C] = v; }

    int PK5::metDay(void) const { return data[0x7D]; }
    void PK5::metDay(int v) { data[0x7D] = v; }

    u16 PK5::eggLocation(void) const { return LittleEndian::convertTo<u16>(data + 0x7E); }
    void PK5::eggLocation(u16 v) { LittleEndian::convertFrom<u16>(data + 0x7E, v); }

    u16 PK5::metLocation(void) const { return LittleEndian::convertTo<u16>(data + 0x80); }
    void PK5::metLocation(u16 v) { LittleEndian::convertFrom<u16>(data + 0x80, v); }

    u8 PK5::pkrs(void) const { return data[0x82]; }
    void PK5::pkrs(u8 v) { data[0x82] = v; }

    u8 PK5::pkrsDays(void) const { return data[0x82] & 0xF; };
    void PK5::pkrsDays(u8 v) { data[0x82] = (u8)((data[0x82] & ~0xF) | v); }

    u8 PK5::pkrsStrain(void) const { return data[0x82] >> 4; };
    void PK5::pkrsStrain(u8 v) { data[0x82] = (u8)((data[0x82] & 0xF) | v << 4); }

    Ball PK5::ball(void) const { return Ball{data[0x83]}; }
    void PK5::ball(Ball v) { data[0x83] = u8(v); }

    u8 PK5::metLevel(void) const { return data[0x84] & ~0x80; }
    void PK5::metLevel(u8 v) { data[0x84] = (data[0x84] & 0x80) | v; }

    Gender PK5::otGender(void) const { return Gender{u8(data[0x84] >> 7)}; }
    void PK5::otGender(Gender v) { data[0x84] = (data[0x84] & ~0x80) | (u8(v) << 7); }

    u8 PK5::encounterType(void) const { return data[0x85]; }
    void PK5::encounterType(u8 v) { data[0x85] = v; }

    void PK5::refreshChecksum(void)
    {
        u16 chk = 0;
        for (u8 i = 8; i < BOX_LENGTH; i += 2)
        {
            chk += LittleEndian::convertTo<u16>(data + i);
        }
        checksum(chk);
    }

    Type PK5::hpType(void) const
    {
        return Type{u8((15 *
                           ((iv(Stat::HP) & 1) + 2 * (iv(Stat::ATK) & 1) + 4 * (iv(Stat::DEF) & 1) +
                               8 * (iv(Stat::SPD) & 1) + 16 * (iv(Stat::SPATK) & 1) +
                               32 * (iv(Stat::SPDEF) & 1)) /
                           63) +
                       1)};
    }
    void PK5::hpType(Type v)
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

    u16 PK5::TSV(void) const { return (TID() ^ SID()) >> 3; }
    u16 PK5::PSV(void) const { return ((PID() >> 16) ^ (PID() & 0xFFFF)) >> 3; }

    u8 PK5::level(void) const
    {
        u8 i      = 1;
        u8 xpType = expType();
        while (experience() >= expTable(i, xpType) && ++i < 100)
            ;
        return i;
    }

    void PK5::level(u8 v) { experience(expTable(v - 1, expType())); }

    bool PK5::shiny(void) const { return TSV() == PSV(); }
    void PK5::shiny(bool v)
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

    u16 PK5::formSpecies(void) const
    {
        u16 tmpSpecies = u16(species());
        u8 form        = alternativeForm();
        u8 formcount   = PersonalBWB2W2::formCount(tmpSpecies);

        if (form && form < formcount)
        {
            u16 backSpecies = tmpSpecies;
            tmpSpecies      = PersonalBWB2W2::formStatIndex(tmpSpecies);
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

    u16 PK5::stat(Stat stat) const
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

    int PK5::partyCurrHP(void) const
    {
        if (!isParty())
        {
            return -1;
        }
        return LittleEndian::convertTo<u16>(data + 0x8E);
    }

    void PK5::partyCurrHP(u16 v)
    {
        if (isParty())
        {
            LittleEndian::convertFrom<u16>(data + 0x8E, v);
        }
    }

    int PK5::partyStat(Stat stat) const
    {
        if (!isParty())
        {
            return -1;
        }
        return LittleEndian::convertTo<u16>(data + 0x90 + u8(stat) * 2);
    }

    void PK5::partyStat(Stat stat, u16 v)
    {
        if (isParty())
        {
            LittleEndian::convertFrom<u16>(data + 0x90 + u8(stat) * 2, v);
        }
    }

    int PK5::partyLevel() const
    {
        if (!isParty())
        {
            return -1;
        }
        return *(data + 0x8C);
    }

    void PK5::partyLevel(u8 v)
    {
        if (isParty())
        {
            *(data + 0x8C) = v;
        }
    }

    std::unique_ptr<PK4> PK5::convertToG4(Sav& save) const
    {
        auto pk4 = PKX::getPKM<Generation::FOUR>(const_cast<u8*>(data));

        // Clear nature field
        pk4->rawData()[0x41] = 0;
        pk4->nature(nature());

        // Force normal Arceus form
        if (pk4->species() == Species::Arceus)
        {
            pk4->alternativeForm(0);
        }

        pk4->nickname(nickname());
        pk4->otName(otName());
        pk4->heldItem(0);
        pk4->otFriendship(70);
        pk4->ball(ball());
        // met location ???
        for (int i = 0; i < 4; i++)
        {
            if (pk4->move(i) > save.maxMove())
            {
                pk4->move(i, Move::None);
            }
        }
        pk4->fixMoves();

        pk4->refreshChecksum();
        return pk4;
    }

    std::unique_ptr<PK6> PK5::convertToG6(Sav& save) const
    {
        auto pk6 = PKX::getPKM<Generation::SIX>(nullptr);

        pk6->encryptionConstant(PID());
        pk6->species(species());
        pk6->TID(TID());
        pk6->SID(SID());
        pk6->experience(experience());
        pk6->PID(PID());
        pk6->ability(ability());

        Ability pkmAbilities[3] = {abilities(0), abilities(1), abilities(2)};
        u8 abilVal =
            std::distance(pkmAbilities, std::find(pkmAbilities, pkmAbilities + 3, ability()));
        if (abilVal < 3 && pkmAbilities[abilVal] == pkmAbilities[2] && hiddenAbility())
        {
            abilVal = 2; // HA shared by normal ability
        }
        if (abilVal < 3)
        {
            pk6->abilityNumber(1 << abilVal);
        }
        else // Shouldn't happen
        {
            if (hiddenAbility())
            {
                pk6->abilityNumber(4);
            }
            else
            {
                pk6->abilityNumber(originGen5() ? ((PID() >> 16) & 1) : 1 << (PID() & 1));
            }
        }

        pk6->markValue(markValue());
        pk6->language(language());

        for (int i = 0; i < 6; i++)
        {
            // EV Cap
            pk6->ev(Stat(i), ev(Stat(i)) > 252 ? 252 : ev(Stat(i)));
            pk6->iv(Stat(i), iv(Stat(i)));
            pk6->contest(i, contest(i));
        }

        for (int i = 0; i < 4; i++)
        {
            pk6->move(i, move(i));
            pk6->PPUp(i, PPUp(i));
            pk6->PP(i, PP(i));
        }

        pk6->egg(egg());
        pk6->nicknamed(nicknamed());

        pk6->fatefulEncounter(fatefulEncounter());
        pk6->gender(gender());
        pk6->alternativeForm(alternativeForm());
        pk6->nature(nature());

        pk6->nickname(pk6->species().localize(pk6->language()));
        if (nicknamed())
            pk6->nickname(nickname());

        pk6->version(version());

        pk6->otName(otName());

        pk6->metDate(metDate());
        pk6->eggDate(eggDate());

        pk6->metLocation(metLocation());
        pk6->eggLocation(eggLocation());

        pk6->pkrsStrain(pkrsStrain());
        pk6->pkrsDays(pkrsDays());
        pk6->ball(ball());

        pk6->metLevel(metLevel());
        pk6->otGender(otGender());
        pk6->encounterType(encounterType());

        // Ribbon
        u8 contestRibbon = 0;
        u8 battleRibbon  = 0;

        for (int i = 0; i < 8; i++) // Sinnoh 3, Hoenn 1
        {
            if (((data[0x60] >> i) & 1) == 1)
                contestRibbon++;
            if (((data[0x61] >> i) & 1) == 1)
                contestRibbon++;
            if (((data[0x3C] >> i) & 1) == 1)
                contestRibbon++;
            if (((data[0x3D] >> i) & 1) == 1)
                contestRibbon++;
        }
        for (int i = 0; i < 4; i++) // Sinnoh 4, Hoenn 2
        {
            if (((data[0x62] >> i) & 1) == 1)
                contestRibbon++;
            if (((data[0x3E] >> i) & 1) == 1)
                contestRibbon++;
        }

        // Winning Ribbon
        if (((data[0x3E] & 0x20) >> 5) == 1)
            battleRibbon++;
        // Victory Ribbon
        if (((data[0x3E] & 0x40) >> 6) == 1)
            battleRibbon++;
        for (int i = 1; i < 7; i++) // Sinnoh Battle Ribbons
            if (((data[0x24] >> i) & 1) == 1)
                battleRibbon++;

        pk6->ribbonContestCount(contestRibbon);
        pk6->ribbonBattleCount(battleRibbon);

        pk6->ribbon(Ribbon::ChampionG3Hoenn, ribbon(Ribbon::ChampionG3Hoenn));
        pk6->ribbon(Ribbon::ChampionSinnoh, ribbon(Ribbon::ChampionSinnoh));
        pk6->ribbon(Ribbon::Effort, ribbon(Ribbon::Effort));

        pk6->ribbon(Ribbon::Alert, ribbon(Ribbon::Alert));
        pk6->ribbon(Ribbon::Shock, ribbon(Ribbon::Shock));
        pk6->ribbon(Ribbon::Downcast, ribbon(Ribbon::Downcast));
        pk6->ribbon(Ribbon::Careless, ribbon(Ribbon::Careless));
        pk6->ribbon(Ribbon::Relax, ribbon(Ribbon::Relax));
        pk6->ribbon(Ribbon::Snooze, ribbon(Ribbon::Snooze));
        pk6->ribbon(Ribbon::Smile, ribbon(Ribbon::Smile));
        pk6->ribbon(Ribbon::Gorgeous, ribbon(Ribbon::Gorgeous));

        pk6->ribbon(Ribbon::Royal, ribbon(Ribbon::Royal));
        pk6->ribbon(Ribbon::GorgeousRoyal, ribbon(Ribbon::GorgeousRoyal));
        pk6->ribbon(Ribbon::Artist, ribbon(Ribbon::Artist));
        pk6->ribbon(Ribbon::Footprint, ribbon(Ribbon::Footprint));
        pk6->ribbon(Ribbon::Record, ribbon(Ribbon::Record));
        pk6->ribbon(Ribbon::Legend, ribbon(Ribbon::Legend));
        pk6->ribbon(Ribbon::Country, ribbon(Ribbon::Country));
        pk6->ribbon(Ribbon::National, ribbon(Ribbon::National));

        pk6->ribbon(Ribbon::Earth, ribbon(Ribbon::Earth));
        pk6->ribbon(Ribbon::World, ribbon(Ribbon::World));
        pk6->ribbon(Ribbon::Classic, ribbon(Ribbon::Classic));
        pk6->ribbon(Ribbon::Premier, ribbon(Ribbon::Premier));
        pk6->ribbon(Ribbon::Event, ribbon(Ribbon::Event));
        pk6->ribbon(Ribbon::Birthday, ribbon(Ribbon::Birthday));
        pk6->ribbon(Ribbon::Special, ribbon(Ribbon::Special));
        pk6->ribbon(Ribbon::Souvenir, ribbon(Ribbon::Souvenir));

        pk6->ribbon(Ribbon::Wishing, ribbon(Ribbon::Wishing));
        pk6->ribbon(Ribbon::ChampionBattle, ribbon(Ribbon::ChampionBattle));
        pk6->ribbon(Ribbon::ChampionRegional, ribbon(Ribbon::ChampionRegional));
        pk6->ribbon(Ribbon::ChampionNational, ribbon(Ribbon::ChampionNational));
        pk6->ribbon(Ribbon::ChampionWorld, ribbon(Ribbon::ChampionWorld));

        pk6->region(save.subRegion());
        pk6->country(save.country());
        pk6->consoleRegion(save.consoleRegion());

        pk6->currentHandler(1);
        pk6->htName(save.otName());
        pk6->htGender(save.gender());
        pk6->geoRegion(0, save.subRegion());
        pk6->geoCountry(0, save.country());
        pk6->htIntensity(1);
        pk6->htMemory(4);
        pk6->htFeeling(pksm::randomNumber(0, 9));
        pk6->otFriendship(pk6->baseFriendship());
        pk6->htFriendship(pk6->baseFriendship());

        u32 shiny = 0;
        shiny     = (PID() >> 16) ^ (PID() & 0xFFFF) ^ TID() ^ SID();
        if (shiny >= 8 && shiny < 16) // Illegal shiny transfer
            pk6->PID(pk6->PID() ^ 0x80000000);

        pk6->fixMoves();

        std::u16string toFix = StringUtils::UTF8toUCS2(pk6->otName());
        fixString(toFix);
        pk6->otName(StringUtils::UCS2toUTF8(toFix));

        toFix = StringUtils::UTF8toUCS2(pk6->nickname());
        fixString(toFix);
        pk6->nickname(StringUtils::UCS2toUTF8(toFix));

        pk6->refreshChecksum();
        return pk6;
    }

    std::unique_ptr<PK3> PK5::convertToG3(Sav& save) const
    {
        if (auto pk4 = convertToG4(save))
        {
            return pk4->convertToG3(save);
        }
        return nullptr;
    }

    std::unique_ptr<PK7> PK5::convertToG7(Sav& save) const
    {
        if (auto pk6 = convertToG6(save))
        {
            return pk6->convertToG7(save);
        }
        return nullptr;
    }

    std::unique_ptr<PK8> PK5::convertToG8(Sav& save) const
    {
        auto pk6 = convertToG6(save);
        if (pk6)
        {
            auto pk7 = pk6->convertToG7(save);
            if (pk7)
            {
                return pk7->convertToG8(save);
            }
        }
        return nullptr;
    }

    void PK5::updatePartyData()
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
