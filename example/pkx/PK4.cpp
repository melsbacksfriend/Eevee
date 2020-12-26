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

#include "pkx/PK4.hpp"
#include "pkx/PK3.hpp"
#include "pkx/PK5.hpp"
#include "pkx/PK6.hpp"
#include "pkx/PK7.hpp"
#include "pkx/PK8.hpp"
#include "sav/Sav.hpp"
#include "utils/crypto.hpp"
#include "utils/endian.hpp"
#include "utils/flagUtil.hpp"
#include "utils/i18n.hpp"
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
                return {0x3C, 0};
            case pksm::Ribbon::G3CoolSuper:
                return {0x3C, 1};
            case pksm::Ribbon::G3CoolHyper:
                return {0x3C, 2};
            case pksm::Ribbon::G3CoolMaster:
                return {0x3C, 3};
            case pksm::Ribbon::G3Beauty:
                return {0x3C, 4};
            case pksm::Ribbon::G3BeautySuper:
                return {0x3C, 5};
            case pksm::Ribbon::G3BeautyHyper:
                return {0x3C, 6};
            case pksm::Ribbon::G3BeautyMaster:
                return {0x3C, 7};
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
}

namespace pksm
{
    void PK4::encrypt(void)
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

    void PK4::decrypt(void)
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

    bool PK4::isEncrypted() const { return LittleEndian::convertTo<u32>(data + 0x64) != 0; }

    PK4::PK4(PrivateConstructor, u8* dt, bool party, bool direct)
        : PKX(dt, party ? PARTY_LENGTH : BOX_LENGTH, direct)
    {
        if (isEncrypted())
        {
            decrypt();
        }
    }

    std::unique_ptr<PKX> PK4::clone(void) const
    {
        return PKX::getPKM<Generation::FOUR>(const_cast<u8*>(data), isParty());
    }

    Generation PK4::generation(void) const { return Generation::FOUR; }

    u32 PK4::encryptionConstant(void) const { return PID(); }
    void PK4::encryptionConstant(u32) {}

    u8 PK4::currentFriendship(void) const { return otFriendship(); }
    void PK4::currentFriendship(u8 v) { otFriendship(v); }

    u8 PK4::abilityNumber(void) const { return 1 << (PID() & 1); }
    void PK4::abilityNumber(u8 v)
    {
        if (shiny())
        {
            do
            {
                PID(PKX::getRandomPID(species(), gender(), version(), nature(), alternativeForm(),
                    v, PID(), generation()));
            } while (!shiny());
        }
        else
        {
            do
            {
                PID(PKX::getRandomPID(species(), gender(), version(), nature(), alternativeForm(),
                    v, PID(), generation()));
            } while (shiny());
        }
    }

    u32 PK4::PID(void) const { return LittleEndian::convertTo<u32>(data); }
    void PK4::PID(u32 v) { LittleEndian::convertFrom<u32>(data, v); }

    u16 PK4::sanity(void) const { return LittleEndian::convertTo<u16>(data + 0x04); }
    void PK4::sanity(u16 v) { LittleEndian::convertFrom<u16>(data + 0x04, v); }

    u16 PK4::checksum(void) const { return LittleEndian::convertTo<u16>(data + 0x06); }
    void PK4::checksum(u16 v) { LittleEndian::convertFrom<u16>(data + 0x06, v); }

    Species PK4::species(void) const { return Species{LittleEndian::convertTo<u16>(data + 0x08)}; }
    void PK4::species(Species v) { LittleEndian::convertFrom<u16>(data + 0x08, u16(v)); }

    u16 PK4::heldItem(void) const { return LittleEndian::convertTo<u16>(data + 0x0A); }
    void PK4::heldItem(u16 v) { LittleEndian::convertFrom<u16>(data + 0x0A, v); }

    u16 PK4::TID(void) const { return LittleEndian::convertTo<u16>(data + 0x0C); }
    void PK4::TID(u16 v) { LittleEndian::convertFrom<u16>(data + 0x0C, v); }

    u16 PK4::SID(void) const { return LittleEndian::convertTo<u16>(data + 0x0E); }
    void PK4::SID(u16 v) { LittleEndian::convertFrom<u16>(data + 0x0E, v); }

    u32 PK4::experience(void) const { return LittleEndian::convertTo<u32>(data + 0x10); }
    void PK4::experience(u32 v) { LittleEndian::convertFrom<u32>(data + 0x10, v); }

    u8 PK4::otFriendship(void) const { return data[0x14]; }
    void PK4::otFriendship(u8 v) { data[0x14] = v; }

    Ability PK4::ability(void) const { return Ability{data[0x15]}; }
    void PK4::ability(Ability v) { data[0x15] = u8(v); }

    void PK4::setAbility(u8 v)
    {
        u8 abilitynum;

        if (v == 0)
            abilitynum = 1;
        else
            abilitynum = 2;

        abilityNumber(abilitynum);
        ability(abilities(v));
    }

    u16 PK4::markValue(void) const { return data[0x16]; }
    void PK4::markValue(u16 v) { data[0x16] = v; }

    Language PK4::language(void) const { return Language(data[0x17]); }
    void PK4::language(Language v) { data[0x17] = u8(v); }

    u8 PK4::ev(Stat ev) const { return data[0x18 + u8(ev)]; }
    void PK4::ev(Stat ev, u8 v) { data[0x18 + u8(ev)] = v; }

    u8 PK4::contest(u8 contest) const { return data[0x1E + contest]; }
    void PK4::contest(u8 contest, u8 v) { data[0x1E + contest] = v; }

    bool PK4::hasRibbon(Ribbon ribbon) const { return OFFSET_OF(ribbon).first != RIBBON_ABSENT; }
    bool PK4::ribbon(Ribbon ribbon) const
    {
        auto offset = OFFSET_OF(ribbon);
        if (offset.first != RIBBON_ABSENT)
        {
            return FlagUtil::getFlag(data, offset.first, offset.second);
        }
        return false;
    }
    void PK4::ribbon(Ribbon ribbon, bool v)
    {
        auto offset = OFFSET_OF(ribbon);
        if (offset.first != RIBBON_ABSENT)
        {
            FlagUtil::setFlag(data, offset.first, offset.second, v);
        }
    }

    Move PK4::move(u8 m) const { return Move{LittleEndian::convertTo<u16>(data + 0x28 + m * 2)}; }
    void PK4::move(u8 m, Move v) { LittleEndian::convertFrom<u16>(data + 0x28 + m * 2, u16(v)); }

    u8 PK4::PP(u8 m) const { return data[0x30 + m]; }
    void PK4::PP(u8 m, u8 v) { data[0x30 + m] = v; }

    u8 PK4::PPUp(u8 m) const { return data[0x34 + m]; }
    void PK4::PPUp(u8 m, u8 v) { data[0x34 + m] = v; }

    u8 PK4::iv(Stat stat) const
    {
        u32 buffer = LittleEndian::convertTo<u32>(data + 0x38);
        return u8((buffer >> 5 * u8(stat)) & 0x1F);
    }

    void PK4::iv(Stat stat, u8 v)
    {
        u32 buffer = LittleEndian::convertTo<u32>(data + 0x38);
        buffer &= ~(0x1F << 5 * u8(stat));
        buffer |= v << (5 * u8(stat));
        LittleEndian::convertFrom<u32>(data + 0x38, buffer);
    }

    bool PK4::egg(void) const
    {
        return ((LittleEndian::convertTo<u32>(data + 0x38) >> 30) & 0x1) == 1;
    }
    void PK4::egg(bool v)
    {
        LittleEndian::convertFrom<u32>(
            data + 0x38, u32((LittleEndian::convertTo<u32>(data + 0x38) & ~0x40000000u) |
                             (v ? 0x40000000u : 0)));
    }

    bool PK4::nicknamed(void) const
    {
        return ((LittleEndian::convertTo<u32>(data + 0x38) >> 31) & 0x1) == 1;
    }
    void PK4::nicknamed(bool v)
    {
        LittleEndian::convertFrom<u32>(data + 0x38,
            (LittleEndian::convertTo<u32>(data + 0x38) & 0x7FFFFFFF) | (v ? 0x80000000 : 0));
    }

    bool PK4::fatefulEncounter(void) const { return (data[0x40] & 1) == 1; }
    void PK4::fatefulEncounter(bool v) { data[0x40] = (data[0x40] & ~0x01) | (v ? 1 : 0); }

    Gender PK4::gender(void) const { return Gender{u8((data[0x40] >> 1) & 0x3)}; }
    void PK4::gender(Gender g)
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

    u16 PK4::alternativeForm(void) const { return data[0x40] >> 3; }
    void PK4::alternativeForm(u16 v) { data[0x40] = (data[0x40] & 0x07) | (v << 3); }

    Nature PK4::nature(void) const { return Nature{u8(PID() % 25)}; }
    void PK4::nature(Nature v)
    {
        if (shiny())
        {
            do
            {
                PID(PKX::getRandomPID(species(), gender(), version(), v, alternativeForm(),
                    abilityNumber(), PID(), generation()));
            } while (!shiny());
        }
        else
        {
            do
            {
                PID(PKX::getRandomPID(species(), gender(), version(), v, alternativeForm(),
                    abilityNumber(), PID(), generation()));
            } while (shiny());
        }
    }

    u8 PK4::shinyLeaf(void) const { return data[0x41]; }
    void PK4::shinyLeaf(u8 v) { data[0x41] = v; }

    std::string PK4::nickname(void) const
    {
        return StringUtils::transString45(StringUtils::getString4(data, 0x48, 11));
    }
    void PK4::nickname(const std::string_view& v)
    {
        StringUtils::setString4(data, StringUtils::transString45(v), 0x48, 11);
    }

    GameVersion PK4::version(void) const { return GameVersion(data[0x5F]); }
    void PK4::version(GameVersion v) { data[0x5F] = u8(v); }

    std::string PK4::otName(void) const
    {
        return StringUtils::transString45(StringUtils::getString4(data, 0x68, 8));
    }
    void PK4::otName(const std::string_view& v)
    {
        StringUtils::setString4(data, StringUtils::transString45(v), 0x68, 8);
    }

    int PK4::eggYear(void) const { return 2000 + data[0x78]; }
    void PK4::eggYear(int v) { data[0x78] = v - 2000; }

    int PK4::eggMonth(void) const { return data[0x79]; }
    void PK4::eggMonth(int v) { data[0x79] = v; }

    int PK4::eggDay(void) const { return data[0x7A]; }
    void PK4::eggDay(int v) { data[0x7A] = v; }

    int PK4::metYear(void) const { return 2000 + data[0x7B]; }
    void PK4::metYear(int v) { data[0x7B] = v - 2000; }

    int PK4::metMonth(void) const { return data[0x7C]; }
    void PK4::metMonth(int v) { data[0x7C] = v; }

    int PK4::metDay(void) const { return data[0x7D]; }
    void PK4::metDay(int v) { data[0x7D] = v; }

    u16 PK4::eggLocation(void) const
    {
        u16 hgssLoc = LittleEndian::convertTo<u16>(data + 0x44);
        if (hgssLoc != 0)
            return hgssLoc;
        return LittleEndian::convertTo<u16>(data + 0x7E);
    }
    void PK4::eggLocation(u16 v)
    {
        if (v == 0)
        {
            LittleEndian::convertFrom<u16>(data + 0x44, v);
            LittleEndian::convertFrom<u16>(data + 0x7E, v);
        }
        else if ((v < 2000 && v > 111) || (v < 3000 && v > 2010))
        {
            LittleEndian::convertFrom<u16>(data + 0x44, v);
            LittleEndian::convertFrom<u16>(data + 0x7E, 0xBBA);
        }
        else
        {
            // If this pokemon is from Platinum, HeartGold, or SoulSilver
            LittleEndian::convertFrom<u16>(
                data + 0x44, (version() == GameVersion::Pt || version() == GameVersion::HG ||
                                 version() == GameVersion::SS)
                                 ? v
                                 : 0);
            LittleEndian::convertFrom<u16>(data + 0x7E, v);
        }
    }

    u16 PK4::metLocation(void) const
    {
        u16 hgssLoc = LittleEndian::convertTo<u16>(data + 0x46);
        if (hgssLoc != 0)
            return hgssLoc;
        return LittleEndian::convertTo<u16>(data + 0x80);
    }
    void PK4::metLocation(u16 v)
    {
        if (v == 0)
        {
            LittleEndian::convertFrom<u16>(data + 0x46, v);
            LittleEndian::convertFrom<u16>(data + 0x80, v);
        }
        else if ((v < 2000 && v > 111) || (v < 3000 && v > 2010))
        {
            LittleEndian::convertFrom<u16>(data + 0x46, v);
            LittleEndian::convertFrom<u16>(data + 0x80, 0xBBA);
        }
        else
        {
            // If this pokemon is from Platinum, HeartGold, or SoulSilver
            LittleEndian::convertFrom<u16>(
                data + 0x46, (version() == GameVersion::Pt || version() == GameVersion::HG ||
                                 version() == GameVersion::SS)
                                 ? v
                                 : 0);
            LittleEndian::convertFrom<u16>(data + 0x80, v);
        }
    }

    u8 PK4::pkrs(void) const { return data[0x82]; }
    void PK4::pkrs(u8 v) { data[0x82] = v; }

    u8 PK4::pkrsDays(void) const { return data[0x82] & 0xF; };
    void PK4::pkrsDays(u8 v) { data[0x82] = (u8)((data[0x82] & ~0xF) | v); }

    u8 PK4::pkrsStrain(void) const { return data[0x82] >> 4; };
    void PK4::pkrsStrain(u8 v) { data[0x82] = (u8)((data[0x82] & 0xF) | v << 4); }

    Ball PK4::ball(void) const
    {
        return data[0x83] > data[0x86] ? Ball{data[0x83]} : Ball{data[0x86]};
    }
    void PK4::ball(Ball v)
    {
        data[0x83] = u8(v <= Ball::Cherish ? v : Ball::Poke);
        if (v > Ball::Cherish ||
            ((version() == GameVersion::HG || version() == GameVersion::SS) && !fatefulEncounter()))
            data[0x86] = u8(v <= Ball::Sport ? v : Ball::Poke);
        else
            data[0x86] = 0;
    }

    u8 PK4::metLevel(void) const { return data[0x84] & ~0x80; }
    void PK4::metLevel(u8 v) { data[0x84] = (data[0x84] & 0x80) | v; }

    Gender PK4::otGender(void) const { return Gender{u8(data[0x84] >> 7)}; }
    void PK4::otGender(Gender v) { data[0x84] = (data[0x84] & ~0x80) | (u8(v) << 7); }

    u8 PK4::encounterType(void) const { return data[0x85]; }
    void PK4::encounterType(u8 v) { data[0x85] = v; }

    u8 PK4::characteristic(void) const
    {
        u8 maxIV = 0, pm6stat = 0, pm6 = PID() % 6;
        for (int i = 0; i < 6; i++)
            if (iv(Stat(i)) > maxIV)
                maxIV = iv(Stat(i));
        for (int i = 0; i < 6; i++)
        {
            pm6stat = (pm6 + i) % 6;
            if (iv(Stat(i)) == maxIV)
                break;
        }
        return pm6stat * 5 + maxIV % 5;
    }

    void PK4::refreshChecksum(void)
    {
        u16 chk = 0;
        for (u8 i = 8; i < BOX_LENGTH; i += 2)
        {
            chk += LittleEndian::convertTo<u16>(data + i);
        }
        checksum(chk);
    }

    Type PK4::hpType(void) const
    {
        return Type{u8((15 *
                           ((iv(Stat::HP) & 1) + 2 * (iv(Stat::ATK) & 1) + 4 * (iv(Stat::DEF) & 1) +
                               8 * (iv(Stat::SPD) & 1) + 16 * (iv(Stat::SPATK) & 1) +
                               32 * (iv(Stat::SPDEF) & 1)) /
                           63) +
                       1)};
    }
    void PK4::hpType(Type v)
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

    u16 PK4::TSV(void) const { return (TID() ^ SID()) >> 3; }
    u16 PK4::PSV(void) const { return ((PID() >> 16) ^ (PID() & 0xFFFF)) >> 3; }

    u8 PK4::level(void) const
    {
        u8 i      = 1;
        u8 xpType = expType();
        while (experience() >= expTable(i, xpType) && ++i < 100)
            ;
        return i;
    }

    void PK4::level(u8 v) { experience(expTable(v - 1, expType())); }

    bool PK4::shiny(void) const { return TSV() == PSV(); }
    void PK4::shiny(bool v)
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

    u16 PK4::formSpecies(void) const
    {
        u16 tmpSpecies = u16(species());
        u8 form        = alternativeForm();
        u8 formcount   = PersonalDPPtHGSS::formCount(tmpSpecies);

        if (form && form < formcount)
        {
            u16 backSpecies = tmpSpecies;
            tmpSpecies      = PersonalDPPtHGSS::formStatIndex(tmpSpecies);
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

    u16 PK4::stat(Stat stat) const
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

    int PK4::partyCurrHP(void) const
    {
        if (!isParty())
        {
            return -1;
        }
        return LittleEndian::convertTo<u16>(data + 0x8E);
    }

    void PK4::partyCurrHP(u16 v)
    {
        if (isParty())
        {
            LittleEndian::convertFrom<u16>(data + 0x8E, v);
        }
    }

    int PK4::partyStat(Stat stat) const
    {
        if (!isParty())
        {
            return -1;
        }
        return LittleEndian::convertTo<u16>(data + 0x90 + u8(stat) * 2);
    }

    void PK4::partyStat(Stat stat, u16 v)
    {
        if (isParty())
        {
            LittleEndian::convertFrom<u16>(data + 0x90 + u8(stat) * 2, v);
        }
    }

    int PK4::partyLevel() const
    {
        if (!isParty())
        {
            return -1;
        }
        return *(data + 0x8C);
    }

    void PK4::partyLevel(u8 v)
    {
        if (isParty())
        {
            *(data + 0x8C) = v;
        }
    }

    std::unique_ptr<PK3> PK4::convertToG3(Sav&) const
    {
        auto pk3 = PKX::getPKM<Generation::THREE>(nullptr);

        pk3->PID(PID());
        pk3->species(species());
        pk3->TID(TID());
        pk3->SID(SID());
        pk3->experience(egg() ? expTable(5, expType()) : experience());
        pk3->gender(gender());
        pk3->alternativeForm(alternativeForm());
        pk3->egg(false);
        pk3->otFriendship(70);
        pk3->markValue(markValue());
        pk3->language(language());
        pk3->ev(Stat::HP, ev(Stat::HP));
        pk3->ev(Stat::ATK, ev(Stat::ATK));
        pk3->ev(Stat::DEF, ev(Stat::DEF));
        pk3->ev(Stat::SPD, ev(Stat::SPD));
        pk3->ev(Stat::SPATK, ev(Stat::SPATK));
        pk3->ev(Stat::SPDEF, ev(Stat::SPDEF));
        pk3->contest(0, contest(0));
        pk3->contest(1, contest(1));
        pk3->contest(2, contest(2));
        pk3->contest(3, contest(3));
        pk3->contest(4, contest(4));
        pk3->contest(5, contest(5));
        pk3->move(0, move(0));
        pk3->move(1, move(1));
        pk3->move(2, move(2));
        pk3->move(3, move(3));
        pk3->PPUp(0, PPUp(0));
        pk3->PPUp(1, PPUp(1));
        pk3->PPUp(2, PPUp(2));
        pk3->PPUp(3, PPUp(3));
        pk3->PP(0, PP(0));
        pk3->PP(1, PP(1));
        pk3->PP(2, PP(2));
        pk3->PP(3, PP(3));
        pk3->iv(Stat::HP, iv(Stat::HP));
        pk3->iv(Stat::ATK, iv(Stat::ATK));
        pk3->iv(Stat::DEF, iv(Stat::DEF));
        pk3->iv(Stat::SPD, iv(Stat::SPD));
        pk3->iv(Stat::SPATK, iv(Stat::SPATK));
        pk3->iv(Stat::SPDEF, iv(Stat::SPDEF));
        pk3->ability(ability());
        pk3->version(version());
        pk3->ball(ball());
        pk3->pkrsStrain(pkrsStrain());
        pk3->pkrsDays(pkrsDays());
        pk3->otGender(otGender());
        // met date isn't a thing in PK3
        pk3->metLevel(level());
        pk3->metLocation(
            0xFD); // (gift egg) // Not sure if this is the best, it seemed the most generic
        pk3->fatefulEncounter(fatefulEncounter());

        pk3->ribbon(Ribbon::ChampionG3Hoenn, ribbon(Ribbon::ChampionG3Hoenn));
        pk3->ribbon(Ribbon::Winning, ribbon(Ribbon::Winning));
        pk3->ribbon(Ribbon::Victory, ribbon(Ribbon::Victory));
        pk3->ribbon(Ribbon::Artist, ribbon(Ribbon::Artist));
        pk3->ribbon(Ribbon::Effort, ribbon(Ribbon::Effort));
        pk3->ribbon(Ribbon::ChampionBattle, ribbon(Ribbon::ChampionBattle));
        pk3->ribbon(Ribbon::ChampionRegional, ribbon(Ribbon::ChampionRegional));
        pk3->ribbon(Ribbon::ChampionNational, ribbon(Ribbon::ChampionNational));
        pk3->ribbon(Ribbon::Country, ribbon(Ribbon::Country));
        pk3->ribbon(Ribbon::National, ribbon(Ribbon::National));
        pk3->ribbon(Ribbon::Earth, ribbon(Ribbon::Earth));
        pk3->ribbon(Ribbon::World, ribbon(Ribbon::World));

        // Contest ribbons
        constexpr std::array<Ribbon, 20> contestRibbons = {Ribbon::G3Cool, Ribbon::G3CoolSuper,
            Ribbon::G3CoolHyper, Ribbon::G3CoolMaster, Ribbon::G3Beauty, Ribbon::G3BeautySuper,
            Ribbon::G3BeautyHyper, Ribbon::G3BeautyMaster, Ribbon::G3Cute, Ribbon::G3CuteSuper,
            Ribbon::G3CuteHyper, Ribbon::G3CuteMaster, Ribbon::G3Smart, Ribbon::G3SmartSuper,
            Ribbon::G3SmartHyper, Ribbon::G3SmartMaster, Ribbon::G3Tough, Ribbon::G3ToughSuper,
            Ribbon::G3ToughHyper, Ribbon::G3ToughMaster};
        for (size_t i = 0; i < contestRibbons.size(); i++)
        {
            if (ribbon(contestRibbons[i]))
            {
                pk3->contestRibbonCount(i / 4, pk3->contestRibbonCount(i / 4) + 1);
            }
        }

        std::string name = species().localize(language());
        pk3->nickname((egg() || !nicknamed()) ? StringUtils::toUpper(name) : nickname());

        pk3->otName(otName());

        pk3->heldItem(heldItem());

        // Remove HM
        Move moves[4] = {move(0), move(1), move(2), move(3)};

        for (int i = 0; i < 4; i++)
        {
            if (std::find(std::begin(banned), std::end(banned), moves[i]) != std::end(banned))
            {
                moves[i] = Move::None;
            }
            pk3->move(i, moves[i]);
        }
        pk3->fixMoves();

        pk3->refreshChecksum();
        return pk3;
    }

    std::unique_ptr<PK5> PK4::convertToG5(Sav&) const
    {
        auto pk5 = PKX::getPKM<Generation::FIVE>(const_cast<u8*>(data));

        // Clear HGSS data
        LittleEndian::convertFrom<u16>(pk5->rawData() + 0x86, 0);

        // Clear PtHGSS met data
        LittleEndian::convertFrom<u32>(pk5->rawData() + 0x44, 0);

        pk5->otFriendship(70);
        pk5->metDate(Date::today());

        // Force normal Arceus form
        if (pk5->species() == Species::Arceus)
        {
            pk5->alternativeForm(0);
        }

        pk5->heldItem(0);

        pk5->nature(nature());

        // Check met location
        pk5->metLocation(pk5->originGen4() && pk5->fatefulEncounter() &&
                                 std::find(beasts, beasts + 4, pk5->species()) != beasts + 4
                             ? (pk5->species() == Species::Celebi ? 30010 : 30012) // Celebi : Beast
                             : 30001); // Pokétransfer (not Crown)

        pk5->ball(ball());

        pk5->nickname(nickname());
        pk5->otName(otName());

        // Check level
        pk5->metLevel(pk5->level());

        // Remove HM
        Move moves[4] = {move(0), move(1), move(2), move(3)};

        for (int i = 0; i < 4; i++)
        {
            if (std::find(banned, banned + 8, moves[i]) != banned + 8)
            {
                moves[i] = Move::None;
            }
            pk5->move(i, moves[i]);
        }
        pk5->fixMoves();

        pk5->refreshChecksum();
        return pk5;
    }

    std::unique_ptr<PK6> PK4::convertToG6(Sav& save) const
    {
        if (auto pk5 = convertToG5(save))
        {
            return pk5->convertToG6(save);
        }
        return nullptr;
    }

    std::unique_ptr<PK7> PK4::convertToG7(Sav& save) const
    {
        if (auto pk5 = convertToG5(save))
        {
            if (auto pk6 = pk5->convertToG6(save))
            {
                return pk6->convertToG7(save);
            }
        }
        return nullptr;
    }

    std::unique_ptr<PK8> PK4::convertToG8(Sav& save) const
    {
        auto pk5 = convertToG5(save);
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
        return nullptr;
    }

    void PK4::updatePartyData()
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
