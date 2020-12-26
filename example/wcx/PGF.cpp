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

#include "wcx/PGF.hpp"
#include "personal/personal.hpp"
#include "utils/endian.hpp"
#include "utils/flagUtil.hpp"
#include "utils/utils.hpp"

#define RIBBON_ABSENT 0xFFFFFFFF

namespace
{
    std::pair<size_t, size_t> OFFSET_OF(pksm::Ribbon rib)
    {
        switch (rib)
        {
            case pksm::Ribbon::Country:
                return {0xC, 0};
            case pksm::Ribbon::National:
                return {0xC, 1};
            case pksm::Ribbon::Earth:
                return {0xC, 2};
            case pksm::Ribbon::World:
                return {0xC, 3};
            case pksm::Ribbon::Classic:
                return {0xC, 4};
            case pksm::Ribbon::Premier:
                return {0xC, 5};
            case pksm::Ribbon::Event:
                return {0xC, 6};
            case pksm::Ribbon::Birthday:
                return {0xC, 7};
            case pksm::Ribbon::Special:
                return {0xD, 0};
            case pksm::Ribbon::Souvenir:
                return {0xD, 1};
            case pksm::Ribbon::Wishing:
                return {0xD, 2};
            case pksm::Ribbon::ChampionBattle:
                return {0xD, 3};
            case pksm::Ribbon::ChampionRegional:
                return {0xD, 4};
            case pksm::Ribbon::ChampionNational:
                return {0xD, 5};
            case pksm::Ribbon::ChampionWorld:
                return {0xD, 6};
            default:
                break;
        }

        return {RIBBON_ABSENT, 0};
    }
}

namespace pksm
{
    PGF::PGF(u8* dt) { std::copy(dt, dt + length, data); }

    Generation PGF::generation(void) const { return Generation::FIVE; }

    u16 PGF::ID(void) const { return LittleEndian::convertTo<u16>(data + 0xB0); }

    std::string PGF::title(void) const
    {
        return StringUtils::transString45(StringUtils::getString(data, 0x60, 37, u'\uFFFF'));
    }

    u8 PGF::type(void) const { return data[0xB3]; }

    int PGF::year(void) const { return LittleEndian::convertTo<u16>(data + 0xAE); }

    int PGF::month(void) const { return data[0xAD]; }

    int PGF::day(void) const { return data[0xAC]; }

    void PGF::year(int v) { LittleEndian::convertFrom<u16>(data + 0xAE, v); }

    void PGF::month(int v) { data[0xAD] = static_cast<u8>(v); }

    void PGF::day(int v) { data[0xAC] = static_cast<u8>(v); }

    bool PGF::item(void) const { return type() == 2; }

    u16 PGF::object(void) const { return LittleEndian::convertTo<u16>(data); }

    bool PGF::pokemon(void) const { return type() == 1; }

    bool PGF::power(void) const { return type() == 3; }

    bool PGF::bean(void) const { return false; }

    bool PGF::BP(void) const { return false; }

    u8 PGF::cardLocation(void) const { return data[0xB2]; }

    u8 PGF::flags(void) const { return data[0xB4]; }

    bool PGF::used(void) const { return (flags() >> 1) > 0; }

    bool PGF::multiObtainable(void) const { return flags() == 1; }

    Ball PGF::ball(void) const { return Ball{data[0x0E]}; }

    u16 PGF::heldItem(void) const { return LittleEndian::convertTo<u16>(data + 0x10); }

    bool PGF::shiny(void) const { return PIDType() == 2; }

    u8 PGF::PIDType(void) const { return data[0x37]; }

    u16 PGF::TID(void) const { return LittleEndian::convertTo<u16>(data); }

    u16 PGF::SID(void) const { return LittleEndian::convertTo<u16>(data + 0x02); }

    Move PGF::move(u8 index) const
    {
        return Move{LittleEndian::convertTo<u16>(data + 0x12 + index * 2)};
    }

    Species PGF::species(void) const { return Species{LittleEndian::convertTo<u16>(data + 0x1A)}; }

    Gender PGF::gender(void) const { return Gender{data[0x35]}; }

    std::string PGF::otName(void) const { return StringUtils::getString(data, 0x4A, 8, u'\uFFFF'); }

    u8 PGF::level(void) const { return data[0x5B]; }

    u32 PGF::PID(void) const { return LittleEndian::convertTo<u32>(data + 0x08); }

    bool PGF::hasRibbon(Ribbon rib) const { return OFFSET_OF(rib).first != RIBBON_ABSENT; }

    bool PGF::ribbon(Ribbon rib) const
    {
        auto offset = OFFSET_OF(rib);
        return offset.first != RIBBON_ABSENT ? FlagUtil::getFlag(data, offset.first, offset.second)
                                             : false;
    }

    u8 PGF::alternativeForm(void) const { return data[0x1C]; }

    Language PGF::language(void) const { return Language(data[0x1D]); }

    std::string PGF::nickname(void) const
    {
        char16_t firstChar = LittleEndian::convertTo<char16_t>(data + 0x1E);
        return firstChar != 0xFFFF ? StringUtils::getString(data, 0x1E, 11, u'\uFFFF')
                                   : "Pokemon Name";
    }

    Nature PGF::nature(void) const { return Nature{data[0x34]}; }

    u8 PGF::abilityType(void) const { return data[0x36]; }

    Ability PGF::ability(void) const
    {
        u8 abilitynum, type = abilityType();

        if (type == 2)
            abilitynum = 2;
        else if (type == 4)
            abilitynum = 2;
        else
            abilitynum = 0;

        return PersonalBWB2W2::ability(u16(species()), abilitynum);
    }

    u16 PGF::eggLocation(void) const { return LittleEndian::convertTo<u16>(data + 0x38); }

    u16 PGF::metLocation(void) const { return LittleEndian::convertTo<u16>(data + 0x3A); }

    u8 PGF::metLevel(void) const { return data[0x3C]; }

    u8 PGF::contest(u8 index) const { return data[0x3D + index]; }

    u8 PGF::iv(Stat index) const { return data[0x43 + u8(index)]; }

    bool PGF::egg(void) const { return data[0x5C] == 1; }

    u16 PGF::formSpecies(void) const
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
}
