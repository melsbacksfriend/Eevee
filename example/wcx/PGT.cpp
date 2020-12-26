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

#include "wcx/PGT.hpp"
#include "enums/Language.hpp"
#include "pkx/PK4.hpp"
#include "utils/endian.hpp"

namespace pksm
{
    PGT::PGT(u8* pgt)
    {
        std::copy(pgt, pgt + length, data);
        pokemonData = PKX::getPKM<Generation::FOUR>(pgt + 0x8, true);
        if (type() == 7)
        {
            pokemonData->species(Species::Manaphy);
            pokemonData->alternativeForm(0);
            pokemonData->egg(true);
            pokemonData->shiny(false);
            pokemonData->gender(Gender::Genderless);
            pokemonData->level(1);
            pokemonData->setAbility(0);
            pokemonData->move(0, Move::TailGlow);
            pokemonData->move(1, Move::Bubble);
            pokemonData->move(2, Move::WaterSport);
            pokemonData->move(3, Move::None);
            pokemonData->heldItem(0);
            pokemonData->fatefulEncounter(true);
            pokemonData->ball(Ball::Poke);
            pokemonData->version(GameVersion::D); // Diamond
            pokemonData->language(Language::ENG);
            pokemonData->nickname("MANAPHY");
            pokemonData->nicknamed(false);
            pokemonData->eggLocation(1);
        }
        pokemonData->refreshChecksum();
        pokemonData->encrypt();
        std::copy(pokemonData->rawData(), pokemonData->rawData() + PK4::PARTY_LENGTH, data + 0x8);
        pokemonData->decrypt(); // encrypt Pokemon data if it isn't already
    }

    u16 PGT::ID(void) const { return 0; }

    std::string PGT::title(void) const { return "Wondercard"; }

    bool PGT::power(void) const { return false; }

    Generation PGT::generation(void) const { return Generation::FOUR; }

    u8 PGT::type(void) const { return data[0]; }

    bool PGT::bean(void) const { return false; }

    bool PGT::BP(void) const { return false; }

    bool PGT::item(void) const
    {
        return type() == 3 || type() == 8 || type() == 9 || type() == 10 || type() == 12;
    }

    // Pokemon, egg, or Manaphy egg
    bool PGT::pokemon(void) const { return type() == 1 || type() == 2 || type() == 7; }

    u16 PGT::object(void) const
    {
        if (type() == 8)
        {
            return 454;
        }
        else if (type() == 9)
        {
            return 452;
        }
        else if (type() == 10)
        {
            return 455;
        }
        else if (type() == 12)
        {
            return 467;
        }
        return LittleEndian::convertTo<u16>(data + 0x4);
    }

    u8 PGT::flags(void) const { return data[3]; }

    bool PGT::multiObtainable(void) const { return false; }

    int PGT::year(void) const
    {
        return (pokemonData->egg() ? pokemonData->eggDate() : pokemonData->metDate()).year();
    }

    int PGT::month(void) const
    {
        return (pokemonData->egg() ? pokemonData->eggDate() : pokemonData->metDate()).month();
    }

    int PGT::day(void) const
    {
        return (pokemonData->egg() ? pokemonData->eggDate() : pokemonData->metDate()).day();
    }

    void PGT::year(int v)
    {
        Date newDate = date();
        newDate.year(v);
        pokemonData->egg() ? pokemonData->eggDate(newDate) : pokemonData->metDate(newDate);
        pokemonData->refreshChecksum();
        pokemonData->encrypt();
        std::copy(pokemonData->rawData(), pokemonData->rawData() + 236,
            data + 0x8); // Actually set the data
        pokemonData->decrypt();
    }

    void PGT::month(int v)
    {
        Date newDate = date();
        newDate.month(v);
        pokemonData->egg() ? pokemonData->eggDate(newDate) : pokemonData->metDate(newDate);
        pokemonData->refreshChecksum();
        pokemonData->encrypt();
        std::copy(pokemonData->rawData(), pokemonData->rawData() + 236,
            data + 0x8); // Actually set the data
        pokemonData->decrypt();
    }

    void PGT::day(int v)
    {
        Date newDate = date();
        newDate.day(v);
        pokemonData->egg() ? pokemonData->eggDate(newDate) : pokemonData->metDate(newDate);
        pokemonData->refreshChecksum();
        pokemonData->encrypt();
        std::copy(pokemonData->rawData(), pokemonData->rawData() + 236,
            data + 0x8); // Actually set the data
        pokemonData->decrypt();
    }

    u8 PGT::cardLocation(void) const { return 0; }

    bool PGT::used(void) const { return false; }

    Ball PGT::ball(void) const { return pokemonData->ball(); }

    u16 PGT::heldItem(void) const { return pokemonData->heldItem(); }

    bool PGT::shiny(void) const { return pokemonData->shiny(); }

    u8 PGT::PIDType(void) const { return pokemonData->shiny() ? 2 : 0; }

    u16 PGT::TID(void) const { return pokemonData->TID(); }

    u16 PGT::SID(void) const { return pokemonData->SID(); }

    Move PGT::move(u8 index) const { return pokemonData->move(index); }

    Species PGT::species(void) const { return pokemonData->species(); }

    Gender PGT::gender(void) const { return pokemonData->gender(); }

    std::string PGT::otName(void) const
    {
        return !(flags() == 0 && type() != 1) ? pokemonData->otName() : "";
    }

    u8 PGT::level(void) const { return pokemonData->level(); }

    u32 PGT::PID(void) const { return pokemonData->PID(); }

    bool PGT::hasRibbon(Ribbon rib) const { return pokemonData->hasRibbon(rib); }

    bool PGT::ribbon(Ribbon rib) const { return pokemonData->ribbon(rib); }

    u8 PGT::alternativeForm(void) const { return pokemonData->alternativeForm(); }

    Language PGT::language(void) const { return pokemonData->language(); }

    std::string PGT::nickname(void) const { return pokemonData->nickname(); }

    Nature PGT::nature(void) const { return pokemonData->nature(); }

    u8 PGT::abilityType(void) const { return pokemonData->abilityNumber(); }

    Ability PGT::ability(void) const { return pokemonData->ability(); }

    u16 PGT::eggLocation(void) const { return pokemonData->eggLocation(); }

    u16 PGT::metLocation(void) const { return pokemonData->metLocation(); }

    u8 PGT::metLevel(void) const { return pokemonData->metLevel(); }

    u8 PGT::contest(u8 index) const { return pokemonData->contest(index); }

    u8 PGT::iv(Stat index) const { return pokemonData->iv(index); }

    bool PGT::egg(void) const { return pokemonData->egg(); }

    u16 PGT::formSpecies(void) const { return pokemonData->formSpecies(); }
}
