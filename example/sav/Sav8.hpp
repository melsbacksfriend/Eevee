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

#ifndef SAV8_HPP
#define SAV8_HPP

#include "personal/personal.hpp"
#include "sav/Sav.hpp"
#include "utils/crypto.hpp"

namespace pksm
{
    class Sav8 : public Sav
    {
    protected:
        std::vector<std::shared_ptr<pksm::crypto::swsh::SCBlock>> blocks;

        int Items, BoxLayout, Misc, TrainerCard, PlayTime, Status;

        bool encrypted = false;

    public:
        Sav8(std::shared_ptr<u8[]> dt, size_t length);

        std::shared_ptr<pksm::crypto::swsh::SCBlock> getBlock(u32 key) const;

        void finishEditing(void) override;
        void beginEditing(void) override;

        void trade(PKX& pk, const Date& date = Date::today()) const override;
        std::unique_ptr<PKX> emptyPkm() const override;

        int maxBoxes(void) const override { return 32; }
        size_t maxWondercards(void) const override { return 1; } // Data not stored
        int currentGiftAmount(void) const override { return 0; } // Data not stored
        Generation generation(void) const override { return Generation::EIGHT; }
    };
}

#endif
