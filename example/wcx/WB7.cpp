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

#include "wcx/WB7.hpp"
#include "personal/personal.hpp"
#include "utils/endian.hpp"
#include "utils/utils.hpp"

namespace
{
    int langIndex(pksm::Language lang)
    {
        if (lang > pksm::Language::UNUSED)
        {
            return u8(lang) - 2;
        }
        else if (lang == pksm::Language::UNUSED)
        {
            return 2 - 1; // English
        }
        else
        {
            return u8(lang) - 1;
        }
    }
}

namespace pksm
{
    WB7::WB7(u8* dt, bool full)
    {
        u16 ofs = full ? 0x208 : 0;
        std::copy(dt + ofs, dt + ofs + length, data);
        for (int i = 0; i < 6; i++)
        {
            if (object(i) != 0)
            {
                numItems++;
            }
            else
                break;
        }
    }

    Generation WB7::generation() const { return Generation::LGPE; }

    u16 WB7::ID() const { return LittleEndian::convertTo<u16>(data); }

    std::string WB7::title() const { return StringUtils::getString(data, 2, 36); }

    u32 WB7::rawDate() const { return LittleEndian::convertTo<u32>(data + 0x4C); }
    void WB7::rawDate(u32 date) { LittleEndian::convertFrom<u32>(data + 0x4C, date); }

    int WB7::year() const { return rawDate() / 10000 + 2000; }

    int WB7::month() const { return rawDate() % 10000 / 100; }

    int WB7::day() const { return rawDate() % 100; }

    void WB7::year(int v)
    {
        u32 newVal = std::max(0, v - 2000);
        newVal *= 10000;
        newVal += rawDate() % 10000;
        rawDate(newVal);
    }

    void WB7::month(int v)
    {
        u32 newVal = rawDate() / 10000;
        newVal *= 100;
        newVal += v;
        newVal *= 100;
        newVal += rawDate() % 100;
        rawDate(newVal);
    }

    void WB7::day(int v)
    {
        u32 newVal = rawDate() / 100;
        newVal *= 100;
        newVal += v;
        rawDate(newVal);
    }

    u8 WB7::cardLocation() const { return data[0x50]; }

    u8 WB7::type() const { return data[0x51]; }

    u8 WB7::flags() const { return data[0x52]; }

    bool WB7::multiObtainable() const { return data[0x53] == 1; }

    bool WB7::BP(void) const { return type() == 3; }

    bool WB7::bean(void) const { return type() == 2; }

    bool WB7::item(void) const { return type() == 1; }

    bool WB7::power(void) const { return false; }

    u16 WB7::object(void) const { return object(0); }

    u16 WB7::object(int index) const
    {
        return LittleEndian::convertTo<u16>(data + 0x68 + index * 4);
    }

    int WB7::items(void) const { return numItems; }

    u16 WB7::objectQuantity(void) const { return objectQuantity(0); }

    u16 WB7::objectQuantity(int index) const
    {
        return LittleEndian::convertTo<u16>(data + 0x6A + index * 4);
    }

    bool WB7::pokemon(void) const { return type() == 0; }

    u8 WB7::PIDType(void) const { return data[0xA3]; }

    bool WB7::shiny(void) const { return PIDType() == 2; }

    u16 WB7::TID(void) const { return LittleEndian::convertTo<u16>(data + 0x68); }

    u16 WB7::SID(void) const { return LittleEndian::convertTo<u16>(data + 0x6A); }

    GameVersion WB7::version(void) const { return GameVersion(data[0x6C]); }

    u32 WB7::encryptionConstant(void) const { return LittleEndian::convertTo<u32>(data + 0x70); }

    Ball WB7::ball(void) const { return Ball{data[0x76]}; }

    u16 WB7::heldItem(void) const { return LittleEndian::convertTo<u16>(data + 0x78); }

    Move WB7::move(u8 m) const { return Move{LittleEndian::convertTo<u16>(data + 0x7A + m * 2)}; }

    Species WB7::species(void) const { return Species{LittleEndian::convertTo<u16>(data + 0x82)}; }

    u8 WB7::alternativeForm(void) const { return data[0x84]; }

    Nature WB7::nature(void) const { return Nature{data[0xA0]}; }

    Gender WB7::gender(void) const { return Gender{data[0xA1]}; }

    Ability WB7::ability(void) const
    {
        u8 abilitynum, type = abilityType();

        if (type == 2)
            abilitynum = 2;
        else if (type == 4)
            abilitynum = 2;
        else
            abilitynum = 0;

        return PersonalLGPE::ability(u16(species()), abilitynum);
    }

    u8 WB7::abilityType(void) const { return data[0xA2]; }

    u8 WB7::metLevel(void) const { return data[0xA8]; }

    u8 WB7::level(void) const { return data[0xD0]; }

    bool WB7::egg(void) const { return data[0xD1] == 1; }

    u16 WB7::eggLocation(void) const { return LittleEndian::convertTo<u16>(data + 0xA4); }

    u16 WB7::metLocation(void) const { return LittleEndian::convertTo<u16>(data + 0xA6); }

    u8 WB7::awakened(Stat index) const { return data[0xA9 + u8(index)]; }

    u8 WB7::iv(Stat index) const { return data[0xAF + u8(index)]; }

    Gender WB7::otGender(void) const { return Gender{data[0xB5]}; }

    u16 WB7::additionalItem(void) const { return LittleEndian::convertTo<u16>(data + 0xD2); }

    u32 WB7::PID(void) const { return LittleEndian::convertTo<u32>(data + 0xD4); }

    Move WB7::relearnMove(u8 index) const
    {
        return Move{LittleEndian::convertTo<u16>(data + 0xD8 + index * 2)};
    }

    u8 WB7::otIntensity(void) const { return data[0xE0]; }

    u8 WB7::otMemory(void) const { return data[0xE1]; }

    u16 WB7::otTextvar(void) const { return data[0xE2]; }

    u8 WB7::otFeeling(void) const { return data[0xE4]; }

    u8 WB7::ev(Stat index) const { return data[0xE5 + u8(index)]; }

    std::string WB7::nickname(Language lang) const
    {
        return StringUtils::getString(data, 0x4 + langIndex(lang) * 0x1A, 13);
    }

    std::string WB7::otName(Language lang) const
    {
        return StringUtils::getString(data, 0xEE + langIndex(lang) * 0x1A, 13);
    }

    std::string WB7::nickname() const { return nickname(Language::ENG); }

    std::string WB7::otName() const { return otName(Language::ENG); }

    bool WB7::used() const { return (flags() & 2) == 2; }

    bool WB7::oncePerDay(void) const { return (flags() & 4) == 4; }

    u16 WB7::formSpecies(void) const
    {
        u16 tmpSpecies = u16(species());
        u8 form        = alternativeForm();
        u8 formcount   = PersonalLGPE::formCount(tmpSpecies);

        if (form && form < formcount)
        {
            u16 backSpecies = tmpSpecies;
            tmpSpecies      = PersonalLGPE::formStatIndex(tmpSpecies);
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
