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

#ifndef PGT_HPP
#define PGT_HPP

#include "pkx/PK4.hpp"
#include "wcx/WCX.hpp"
#include <memory>

namespace pksm
{
    class PGT : public WCX
    {
    private:
        int year(void) const override;
        int month(void) const override;
        int day(void) const override;
        void year(int v) override;
        void month(int v) override;
        void day(int v) override;

    protected:
        u8 data[260];
        std::unique_ptr<PK4> pokemonData;

    public:
        static constexpr u16 length = 260;

        explicit PGT(u8* pgt);

        virtual std::string extension() const override { return ".pgt"; }

        Generation generation() const override;
        bool bean(void) const override;
        bool BP(void) const override;
        bool item(void) const override;
        bool pokemon(void) const override;
        bool power(void) const override;
        virtual std::string title(void) const override;
        u8 type(void) const override;
        u16 ID(void) const override;
        u16 object(void) const override;
        u8 flags(void) const override;
        bool multiObtainable(void) const override;
        // Stubbed functions
        u8 cardLocation(void) const override;
        bool used(void) const override;

        // Pokemon properties
        Ball ball(void) const override;
        u16 heldItem(void) const override;
        bool shiny(void) const override;
        u8 PIDType(void) const override;
        u16 TID(void) const override;
        u16 SID(void) const override;
        Move move(u8 index) const override;
        Species species(void) const override;
        Gender gender(void) const override;
        std::string otName(void) const override;
        u8 level(void) const override;
        u32 PID(void) const override;
        bool hasRibbon(Ribbon rib) const override;
        bool ribbon(Ribbon rib) const override;
        u8 alternativeForm(void) const override;
        Language language(void) const override;
        std::string nickname(void) const override;
        Nature nature(void) const override;
        u8 abilityType(void) const override;
        Ability ability(void) const override;
        u16 eggLocation(void) const override;
        u16 metLocation(void) const override;
        u8 metLevel(void) const override;
        u8 contest(u8 index) const override;
        u8 iv(Stat index) const override;
        bool egg(void) const override;

        u16 formSpecies(void) const override;

        int size(void) const override { return length; }
        const u8* rawData(void) const override { return data; }
    };
}

#endif
