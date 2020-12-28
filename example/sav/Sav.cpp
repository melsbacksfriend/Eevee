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

#include "sav/Sav.hpp"
#include "pkx/PB7.hpp"
#include "pkx/PK3.hpp"
#include "pkx/PK4.hpp"
#include "pkx/PK5.hpp"
#include "pkx/PK6.hpp"
#include "pkx/PK7.hpp"
#include "pkx/PK8.hpp"
#include "pkx/PKX.hpp"
#include "sav/SavB2W2.hpp"
#include "sav/SavBW.hpp"
#include "sav/SavDP.hpp"
#include "sav/SavE.hpp"
#include "sav/SavFRLG.hpp"
#include "sav/SavHGSS.hpp"
#include "sav/SavLGPE.hpp"
#include "sav/SavORAS.hpp"
#include "sav/SavPT.hpp"
#include "sav/SavRS.hpp"
#include "sav/SavSUMO.hpp"
#include "sav/SavSWSH.hpp"
#include "sav/SavUSUM.hpp"
#include "sav/SavXY.hpp"
#include "utils/crypto.hpp"
#include "utils/endian.hpp"

namespace pksm
{
    std::unique_ptr<Sav> Sav::getSave(std::shared_ptr<u8[]> dt, size_t length)
    {
        switch (length)
        {
            case 0x6CC00:
                return std::make_unique<SavUSUM>(dt);
            case 0x6BE00:
                return std::make_unique<SavSUMO>(dt);
            case 0x76000:
                return std::make_unique<SavORAS>(dt);
            case 0x65600:
                return std::make_unique<SavXY>(dt);
            case 0x80000:
                return checkDSType(dt);
            case 0x20000:
                return checkGBAType(dt);
            case 0xB8800:
            case 0x100000:
                return std::make_unique<SavLGPE>(dt, length);
            case 0x1716B3: // base
            case 0x17195E: // base->wañel
            case 0x180B19: // base->wañel->armor
            case 0x180AD0: // base->armor
            case 0x18764A: // base->crown
            case 0x187668: // base->armor->crown
            case 0x187693: // base->wañel->crown
            case 0x1876B1: // base->wañel->armor->crown
                return std::make_unique<SavSWSH>(dt, length);
            default:
                return std::unique_ptr<Sav>(nullptr);
        }
    }

    std::unique_ptr<Sav> Sav::checkGBAType(std::shared_ptr<u8[]> dt)
    {
        switch (Sav3::getVersion(dt))
        {
            case Game::RS:
                return std::make_unique<SavRS>(dt);
            case Game::E:
                return std::make_unique<SavE>(dt);
            case Game::FRLG:
                return std::make_unique<SavFRLG>(dt);
            default:
                return std::unique_ptr<Sav>(nullptr);
        }
    }

    bool Sav::isValidDSSave(std::shared_ptr<u8[]> dt)
    {
        u16 chk1    = LittleEndian::convertTo<u16>(&dt[0x24000 - 0x100 + 0x8C + 0xE]);
        u16 actual1 = pksm::crypto::ccitt16(&dt[0x24000 - 0x100], 0x8C);
        if (chk1 == actual1)
        {
            return true;
        }
        u16 chk2    = LittleEndian::convertTo<u16>(&dt[0x26000 - 0x100 + 0x94 + 0xE]);
        u16 actual2 = pksm::crypto::ccitt16(&dt[0x26000 - 0x100], 0x94);
        if (chk2 == actual2)
        {
            return true;
        }

        // Check for block identifiers
        static constexpr size_t DP_OFFSET   = 0xC100;
        static constexpr size_t PT_OFFSET   = 0xCF2C;
        static constexpr size_t HGSS_OFFSET = 0xF628;
        if (validSequence(dt, DP_OFFSET))
            return true;
        if (validSequence(dt, PT_OFFSET))
            return true;
        if (validSequence(dt, HGSS_OFFSET))
            return true;

        // Check the other save
        if (validSequence(dt, DP_OFFSET + 0x40000))
            return true;
        if (validSequence(dt, PT_OFFSET + 0x40000))
            return true;
        if (validSequence(dt, HGSS_OFFSET + 0x40000))
            return true;
        return false;
    }

    std::unique_ptr<Sav> Sav::checkDSType(std::shared_ptr<u8[]> dt)
    {
        // Check for block identifiers
        static constexpr size_t DP_OFFSET   = 0xC100;
        static constexpr size_t PT_OFFSET   = 0xCF2C;
        static constexpr size_t HGSS_OFFSET = 0xF628;
        if (validSequence(dt, DP_OFFSET))
            return std::make_unique<SavDP>(dt);
        if (validSequence(dt, PT_OFFSET))
            return std::make_unique<SavPT>(dt);
        if (validSequence(dt, HGSS_OFFSET))
            return std::make_unique<SavHGSS>(dt);

        // Check the other save
        if (validSequence(dt, DP_OFFSET + 0x40000))
            return std::make_unique<SavDP>(dt);
        if (validSequence(dt, PT_OFFSET + 0x40000))
            return std::make_unique<SavPT>(dt);
        if (validSequence(dt, HGSS_OFFSET + 0x40000))
            return std::make_unique<SavHGSS>(dt);

        // Check for BW/B2W2 checksums
        u16 chk1    = LittleEndian::convertTo<u16>(&dt[0x24000 - 0x100 + 0x8C + 0xE]);
        u16 actual1 = pksm::crypto::ccitt16(&dt[0x24000 - 0x100], 0x8C);
        if (chk1 == actual1)
        {
            return std::make_unique<SavBW>(dt);
        }
        u16 chk2    = LittleEndian::convertTo<u16>(&dt[0x26000 - 0x100 + 0x94 + 0xE]);
        u16 actual2 = pksm::crypto::ccitt16(&dt[0x26000 - 0x100], 0x94);
        if (chk2 == actual2)
        {
            return std::make_unique<SavB2W2>(dt);
        }
        return nullptr;
    }

    bool Sav::validSequence(std::shared_ptr<u8[]> dt, size_t offset)
    {
        static constexpr u32 DATE_INTERNATIONAL = 0x20060623;
        static constexpr u32 DATE_KOREAN        = 0x20070903;

        if (LittleEndian::convertTo<u32>(&dt[offset - 0xC]) != (offset & 0xFFFF))
        {
            return false;
        }

        return LittleEndian::convertTo<u32>(&dt[offset - 0x8]) == DATE_INTERNATIONAL ||
               LittleEndian::convertTo<u32>(&dt[offset - 0x8]) == DATE_KOREAN;
    }

    std::unique_ptr<PKX> Sav::transfer(const PKX& pk)
    {
        switch (generation())
        {
            case Generation::THREE:
                return pk.convertToG3(*this);
            case Generation::FOUR:
                return pk.convertToG4(*this);
            case Generation::FIVE:
                return pk.convertToG5(*this);
            case Generation::SIX:
                return pk.convertToG6(*this);
            case Generation::SEVEN:
                return pk.convertToG7(*this);
            case Generation::LGPE:
                return pk.convertToLGPE(*this);
            case Generation::EIGHT:
                return pk.convertToG8(*this);
            case Generation::UNUSED:
            case Generation::ONE:
            case Generation::TWO:
                return nullptr;
        }
        return nullptr;
    }

    void Sav::fixParty()
    {
        // Poor man's bubble sort-like thing
        int numPkm = 6;
        for (int i = 5; i > 0; i--)
        {
            auto checkPKM = pkm(i);
            if (checkPKM->species() == Species::None)
            {
                numPkm--;
                continue;
            }
            auto prevPKM = pkm(i - 1);
            if (checkPKM->species() != Species::None && prevPKM->species() == Species::None)
            {
                pkm(*checkPKM, i - 1);
                pkm(*prevPKM, i);
                numPkm = 6;
                i      = 6; // reset loop
            }
        }
        partyCount(numPkm);
    }

    u32 Sav::displayTID() const
    {
        switch (generation())
        {
            case Generation::THREE:
            case Generation::FOUR:
            case Generation::FIVE:
            case Generation::SIX:
                return TID();
            case Generation::SEVEN:
            case Generation::LGPE:
            case Generation::EIGHT:
                return u32(SID() << 16 | TID()) % 1000000;
            case Generation::UNUSED:
            case Generation::ONE:
            case Generation::TWO:
                return 0;
        }
        return 0;
    }

    u32 Sav::displaySID() const
    {
        switch (generation())
        {
            case Generation::THREE:
            case Generation::FOUR:
            case Generation::FIVE:
            case Generation::SIX:
                return SID();
            case Generation::SEVEN:
            case Generation::LGPE:
            case Generation::EIGHT:
                return u32(SID() << 16 | TID()) / 1000000;
            case Generation::UNUSED:
            case Generation::ONE:
            case Generation::TWO:
                return 0;
        }
        return 0;
    }

    Sav::BadTransferReason Sav::invalidTransferReason(const PKX& pk) const
    {
        bool moveBad = false;
        for (int i = 0; i < 4; i++)
        {
            if (availableMoves().count(pk.move(i)) == 0)
            {
                moveBad = true;
                break;
            }
            if (availableMoves().count(pk.relearnMove(i)) == 0)
            {
                moveBad = true;
                break;
            }
        }
        if (moveBad)
        {
            return BadTransferReason::MOVE;
        }
        else if (availableSpecies().count(pk.species()) == 0)
        {
            return BadTransferReason::SPECIES;
        }
        else if (pk.alternativeForm() >= formCount(pk.species()) &&
                 !((pk.species() == Species::Scatterbug || pk.species() == Species::Spewpa) &&
                     pk.alternativeForm() <= formCount(Species::Vivillon)))
        {
            return BadTransferReason::FORM;
        }
        else if (availableAbilities().count(pk.ability()) == 0)
        {
            return BadTransferReason::ABILITY;
        }
        else if (availableItems().count((int)pk.heldItem()) == 0)
        {
            return BadTransferReason::ITEM;
        }
        else if (availableBalls().count(pk.ball()) == 0)
        {
            return BadTransferReason::BALL;
        }
        return BadTransferReason::OKAY;
    }
}
