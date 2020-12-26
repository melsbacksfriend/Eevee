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

#include "sav/Sav8.hpp"
#include "pkx/PK8.hpp"
#include <algorithm>

namespace pksm
{
    Sav8::Sav8(std::shared_ptr<u8[]> dt, size_t length) : Sav(dt, length)
    {
        pksm::crypto::swsh::applyXor(dt, length);
        blocks = pksm::crypto::swsh::getBlockList(dt, length);
    }

    std::shared_ptr<pksm::crypto::swsh::SCBlock> Sav8::getBlock(u32 key) const
    {
        // binary search
        auto found = std::lower_bound(blocks.begin(), blocks.end(), key,
            [](const std::shared_ptr<pksm::crypto::swsh::SCBlock>& block, u32 key) {
                return block->key() < key;
            });
        if ((*found)->key() != key)
        {
            return nullptr;
        }
        return *found;
    }

    std::unique_ptr<PKX> Sav8::emptyPkm() const { return PKX::getPKM<Generation::EIGHT>(nullptr); }

    void Sav8::trade(PKX& pk, const Date& date) const
    {
        if (pk.generation() == Generation::EIGHT)
        {
            if (pk.egg())
            {
                if (pk.otName() != otName() || pk.TID() != TID() || pk.SID() != SID() ||
                    pk.gender() != gender())
                {
                    pk.metLocation(30002);
                    pk.metDate(date);
                }
            }
            else
            {
                if (pk.otName() != otName() || pk.TID() != TID() || pk.SID() != SID() ||
                    pk.gender() != gender())
                {
                    pk.currentHandler(0);
                }
                else
                {
                    pk.currentHandler(1);
                    PK8& pk8 = reinterpret_cast<PK8&>(pk);
                    pk8.htName(otName());
                    pk8.currentFriendship(pk.baseFriendship());
                    pk8.htGender(gender());
                    pk8.htLanguage(language());
                }
            }
        }
    }

    void Sav8::finishEditing()
    {
        if (!encrypted)
        {
            for (auto& block : blocks)
            {
                block->encrypt();
            }

            pksm::crypto::swsh::applyXor(data, length);
            pksm::crypto::swsh::sign(data, length);
        }
        encrypted = true;
    }

    void Sav8::beginEditing()
    {
        if (encrypted)
        {
            pksm::crypto::swsh::applyXor(data, length);
        }
        encrypted = false;

        // I could decrypt every block here, but why not just let them be done on the fly via the
        // functions that need them?
    }
}
