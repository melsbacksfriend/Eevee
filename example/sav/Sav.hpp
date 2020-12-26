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

#ifndef SAV_HPP
#define SAV_HPP

#include "enums/Ability.hpp"
#include "enums/Ball.hpp"
#include "enums/GameVersion.hpp"
#include "enums/Gender.hpp"
#include "enums/Generation.hpp"
#include "enums/Language.hpp"
#include "enums/Species.hpp"
#include "pkx/PKX.hpp"
#include "sav/Item.hpp"
#include "utils/DateTime.hpp"
#include "utils/VersionTables.hpp"
#include "utils/coretypes.h"
#include "wcx/WCX.hpp"
#include <map>
#include <memory>
#include <set>
#include <type_traits>
#include <vector>

namespace pksm
{
    class Sav
    {
    protected:
        enum class Game
        {
            DP,
            Pt,
            HGSS,
            BW,
            B2W2,
            XY,
            ORAS,
            SM,
            USUM,
            LGPE,
            SWSH,
            RS,
            E,
            FRLG
        } game;

        int Box, Party, PokeDex, WondercardData, WondercardFlags;
        int PouchHeldItem, PouchKeyItem, PouchTMHM, PouchMedicine, PouchBerry;

        const std::shared_ptr<u8[]> data;
        const u32 length;
        static std::unique_ptr<Sav> checkGBAType(std::shared_ptr<u8[]> dt);
        static std::unique_ptr<Sav> checkDSType(std::shared_ptr<u8[]> dt);
        static bool validSequence(std::shared_ptr<u8[]> dt, size_t offset);

    public:
        enum class Pouch
        {
            NormalItem,
            KeyItem,
            TM,
            Mail,
            Medicine,
            Berry,
            Ball,
            Battle,
            Candy,
            ZCrystals,
            Treasure,
            Ingredient,
            PCItem,
            RotomPower,
            CatchingItem
        };
        enum class BadTransferReason
        {
            OKAY, // Indicates a transfer that should be successful
            MOVE,
            SPECIES,
            FORM,
            ABILITY,
            ITEM,
            BALL
        };

        virtual ~Sav() = default;
        Sav(std::shared_ptr<u8[]> data, u32 length) : data(data), length(length) {}
        Sav(const Sav& save) = delete;
        Sav& operator=(const Sav& save) = delete;
        // Readies the save for serialization in signed/encrypted form
        virtual void finishEditing(void) = 0;
        // Must be called to continue editing after calling finishEditing.
        // Not necessary directly after construction
        virtual void beginEditing(void) = 0;

        BadTransferReason invalidTransferReason(const PKX& pk) const;
        std::unique_ptr<PKX> transfer(const PKX& pk);
        static bool isValidDSSave(std::shared_ptr<u8[]> dt);
        static std::unique_ptr<Sav> getSave(std::shared_ptr<u8[]> dt, size_t length);

        virtual u16 TID(void) const                    = 0;
        virtual void TID(u16 v)                        = 0;
        virtual u16 SID(void) const                    = 0;
        virtual void SID(u16 v)                        = 0;
        virtual GameVersion version(void) const        = 0;
        virtual void version(GameVersion v)            = 0;
        virtual Gender gender(void) const              = 0;
        virtual void gender(Gender v)                  = 0;
        virtual u8 subRegion(void) const               = 0;
        virtual void subRegion(u8 v)                   = 0;
        virtual u8 country(void) const                 = 0;
        virtual void country(u8 v)                     = 0;
        virtual u8 consoleRegion(void) const           = 0;
        virtual void consoleRegion(u8 v)               = 0;
        virtual Language language(void) const          = 0;
        virtual void language(Language v)              = 0;
        virtual std::string otName(void) const         = 0;
        virtual void otName(const std::string_view& v) = 0;
        virtual u32 money(void) const                  = 0;
        virtual void money(u32 v)                      = 0;
        virtual u32 BP(void) const                     = 0;
        virtual void BP(u32 v)                         = 0;
        virtual u8 badges(void) const                  = 0;
        virtual u16 playedHours(void) const            = 0;
        virtual void playedHours(u16 v)                = 0;
        virtual u8 playedMinutes(void) const           = 0;
        virtual void playedMinutes(u8 v)               = 0;
        virtual u8 playedSeconds(void) const           = 0;
        virtual void playedSeconds(u8 v)               = 0;

        u32 displayTID(void) const;
        u32 displaySID(void) const;

        virtual u8 currentBox(void) const            = 0;
        virtual void currentBox(u8 v)                = 0;
        virtual u8 unlockedBoxes(void) const         = 0;
        virtual void unlockedBoxes(u8 v)             = 0;
        virtual u8 legendBoxUnlockSize(void) const   = 0;
        virtual u32 boxOffset(u8 box, u8 slot) const = 0;
        virtual u32 partyOffset(u8 slot) const       = 0;

        virtual std::unique_ptr<PKX> pkm(u8 slot) const                   = 0;
        virtual void pkm(const PKX& pk, u8 slot)                          = 0;
        virtual std::unique_ptr<PKX> pkm(u8 box, u8 slot) const           = 0;
        virtual void pkm(const PKX& pk, u8 box, u8 slot, bool applyTrade) = 0;
        virtual void trade(PKX& pk,
            const Date& date = Date::today()) const   = 0; // Look into bank boolean parameter
        virtual std::unique_ptr<PKX> emptyPkm() const = 0;

        virtual void dex(const PKX& pk)                            = 0;
        virtual int dexSeen(void) const                            = 0;
        virtual int dexCaught(void) const                          = 0;
        virtual int currentGiftAmount(void) const                  = 0;
        virtual std::unique_ptr<WCX> mysteryGift(int pos) const    = 0;
        virtual void mysteryGift(const WCX& wc, int& pos)          = 0;
        virtual void cryptBoxData(bool crypted)                    = 0;
        virtual std::string boxName(u8 box) const                  = 0;
        virtual void boxName(u8 box, const std::string_view& name) = 0;
        virtual u8 boxWallpaper(u8 box) const                      = 0;
        virtual void boxWallpaper(u8 box, const u8 v)              = 0;
        virtual u8 partyCount(void) const                          = 0;
        virtual void partyCount(u8 count)                          = 0;
        virtual void fixParty(void); // Has to be overridden by SavLGPE because it works stupidly

        virtual int maxSlot(void) const { return maxBoxes() * 30; }
        virtual int maxBoxes(void) const          = 0;
        virtual size_t maxWondercards(void) const = 0;
        virtual Generation generation(void) const = 0;
        const std::set<int>& availableItems(void) const
        {
            return VersionTables::availableItems(version());
        }
        const std::set<Move>& availableMoves(void) const
        {
            return VersionTables::availableMoves(version());
        }
        const std::set<Species>& availableSpecies(void) const
        {
            return VersionTables::availableSpecies(version());
        }
        const std::set<Ability>& availableAbilities(void) const
        {
            return VersionTables::availableAbilities(version());
        }
        const std::set<Ball>& availableBalls(void) const
        {
            return VersionTables::availableBalls(version());
        }
        // Not guaranteed to be useful
        int maxItem() const { return VersionTables::maxItem(version()); }
        Move maxMove() const { return VersionTables::maxMove(version()); }
        Species maxSpecies() const { return VersionTables::maxSpecies(version()); }
        Ability maxAbility() const { return VersionTables::maxAbility(version()); }
        Ball maxBall() const { return VersionTables::maxBall(version()); }
        u8 formCount(Species s) const { return VersionTables::formCount(version(), s); }

        virtual void item(const Item& item, Pouch pouch, u16 slot)       = 0;
        virtual std::unique_ptr<Item> item(Pouch pouch, u16 slot) const  = 0;
        virtual std::vector<std::pair<Pouch, int>> pouches(void) const   = 0;
        virtual std::map<Pouch, std::vector<int>> validItems(void) const = 0;

        u32 getLength() const { return length; }
        std::shared_ptr<u8[]> rawData() const { return data; }
    };
}

#endif
