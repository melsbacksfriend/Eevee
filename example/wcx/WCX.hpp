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

#ifndef PKSM_WCX
#define PKSM_WCX

#include "enums/Ability.hpp"
#include "enums/Ball.hpp"
#include "enums/Gender.hpp"
#include "enums/Generation.hpp"
#include "enums/Language.hpp"
#include "enums/Move.hpp"
#include "enums/Nature.hpp"
#include "enums/Ribbon.hpp"
#include "enums/Species.hpp"
#include "enums/Stat.hpp"
#include "utils/DateTime.hpp"
#include "utils/coretypes.h"
#include <string>

namespace pksm
{
    class WCX
    {
    private:
        virtual int year(void) const  = 0;
        virtual int month(void) const = 0;
        virtual int day(void) const   = 0;
        virtual void year(int v)      = 0;
        virtual void month(int v)     = 0;
        virtual void day(int v)       = 0;

    public:
        WCX() {}
        WCX(const WCX&) = delete;
        WCX& operator=(const WCX&) = delete;
        virtual ~WCX(void)         = default;

        virtual std::string extension() const { return ".wc" + (std::string)generation(); }

        virtual Generation generation(void) const = 0;
        virtual bool bean(void) const             = 0;
        virtual bool BP(void) const               = 0;
        virtual bool item(void) const             = 0;
        virtual bool pokemon(void) const          = 0;
        virtual bool power(void) const            = 0;
        virtual std::string title(void) const     = 0;
        virtual u8 type(void) const               = 0;
        Date date(void) const { return Date{(u8)day(), (u8)month(), (u32)year()}; }
        void date(const Date& v)
        {
            day(v.day());
            month(v.month());
            year(v.year());
        }
        virtual u16 ID(void) const               = 0;
        virtual u16 object(void) const           = 0;
        virtual bool multiObtainable(void) const = 0;
        virtual u8 flags(void) const             = 0;
        virtual u8 cardLocation(void) const      = 0;
        virtual bool used(void) const            = 0;

        // Pokemon properties
        virtual bool shiny(void) const           = 0;
        virtual Ability ability(void) const      = 0;
        virtual u8 abilityType(void) const       = 0;
        virtual Ball ball(void) const            = 0;
        virtual bool egg(void) const             = 0;
        virtual u8 alternativeForm(void) const   = 0;
        virtual Gender gender(void) const        = 0;
        virtual u16 heldItem(void) const         = 0;
        virtual Language language(void) const    = 0;
        virtual u8 level(void) const             = 0;
        virtual u8 metLevel(void) const          = 0;
        virtual Move move(u8 index) const        = 0;
        virtual Nature nature(void) const        = 0;
        virtual std::string nickname(void) const = 0;
        virtual std::string otName(void) const   = 0;
        virtual u8 PIDType(void) const           = 0;
        virtual u16 SID(void) const              = 0;
        virtual Species species(void) const      = 0;
        virtual u16 TID(void) const              = 0;
        virtual u16 eggLocation(void) const      = 0;
        virtual u16 metLocation(void) const      = 0;
        virtual u8 contest(u8 index) const       = 0;
        virtual u8 iv(Stat index) const          = 0;
        virtual u32 PID(void) const              = 0;
        virtual bool hasRibbon(Ribbon rib) const = 0;
        virtual bool ribbon(Ribbon rib) const    = 0;

        virtual u16 formSpecies(void) const = 0;

        virtual int size(void) const          = 0;
        virtual const u8* rawData(void) const = 0;

        u32 formatTID(void) const;
        u32 formatSID(void) const;
    };
}

#endif
