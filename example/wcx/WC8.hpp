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

#ifndef WC8_HPP
#define WC8_HPP

#include "enums/GameVersion.hpp"
#include "wcx/WCX.hpp"

namespace pksm
{
    class WC8 : public WCX
    {
    private:
        int year(void) const override { return 1900; }
        int month(void) const override { return 1; }
        int day(void) const override { return 1; }
        void year(int) override {}
        void month(int) override {}
        void day(int) override {}

    protected:
        u8 data[0x2D0];
        int numItems = 0;

    public:
        static constexpr u16 length = 0x2D0;

        explicit WC8(u8* dt);

        Generation generation(void) const override;
        bool bean(void) const override { return false; }
        bool BP(void) const override;
        bool item(void) const override;
        bool pokemon(void) const override;
        bool clothing(void) const;
        bool power(void) const override { return false; }
        std::string title(void) const override;
        std::string title(Language lang) const;
        Language titleIndex(void) const;
        u8 type(void) const override;
        u16 ID(void) const override;
        u16 object(void) const override;
        u16 objectQuantity(void) const;
        // Multiple-item cards
        u16 object(int index) const;
        u16 objectQuantity(int index) const;
        int items(void) const;
        bool multiObtainable(void) const override;
        u8 flags(void) const override;
        u8 cardLocation(void) const override { return 0; }
        bool used(void) const override;

        // Pokemon properties
        Move move(u8 index) const override;
        Move relearnMove(u8 index) const;
        Species species(void) const override;
        u8 alternativeForm(void) const override;
        Gender gender(void) const override;
        u8 level(void) const override;
        bool egg(void) const override;
        Nature nature(void) const override;
        u8 abilityType(void) const override;
        u8 PIDType(void) const override;
        u8 metLevel(void) const override;
        u8 dynamaxLevel(void) const;
        bool canGigantamax(void) const;
        u8 ribbonValue(int index) const;
        u8 iv(Stat index) const override;
        Gender otGender(void) const;
        u8 ev(Stat index) const;
        bool shiny(void) const override;
        Ability ability(void) const override;
        Ball ball(void) const override;
        u32 encryptionConstant(void) const;
        u16 heldItem(void) const override;
        Language language(void) const override
        {
            return Language::UNUSED;
        } // Apparently all WCs are now multi-language?
        std::string nickname(void) const override;
        std::string nickname(Language lang) const;
        Language nicknameLanguage(Language orig) const;
        bool nicknamed(Language lang) const;
        GameVersion version(void) const;
        std::string otName(void) const override;
        std::string otName(Language lang) const;
        u8 otIntensity(void) const;
        u8 otMemory(void) const;
        u16 otTextvar(void) const;
        u8 otFeeling(void) const;
        u16 TID(void) const override;
        u16 SID(void) const override;
        u32 PID(void) const override;
        u16 eggLocation(void) const override;
        u16 metLocation(void) const override;
        u8 contest(u8) const override { return 0; }
        bool hasRibbon(Ribbon rib) const override;
        bool ribbon(Ribbon rib) const override;

        u16 formSpecies(void) const override;

        int size(void) const override { return length; }
        const u8* rawData(void) const override { return data; }
    };
}

#endif
