/*
 *   This file is part of PKSM-Core
 *   Copyright (C) 2016-2020 Bernardo Giordano, Admiral Fish, piepie62, Pk11
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

#ifndef SAV3_HPP
#define SAV3_HPP

#include "personal/personal.hpp"
#include "sav/Sav.hpp"
#include <array>

namespace pksm
{
    class Sav3 : public Sav
    {
    protected:
        bool japanese;
        int OFS_PCItem, OFS_PouchHeldItem, OFS_PouchKeyItem, OFS_PouchBalls, OFS_PouchTMHM,
            OFS_PouchBerry, eventFlag;

        void initialize();

        static u16 calculateChecksum(const u8* data, size_t len);

        static constexpr int BLOCK_COUNT = 14;
        static constexpr int SIZE_RESERVED =
            0x10000; // unpacked box data will start after the save data
        static constexpr int SIZE_BLOCK_USED = 0xF80;

        std::array<int, BLOCK_COUNT> blockOrder, blockOfs;
        std::vector<int> seenFlagOffsets;

        void loadBlocks();
        static std::array<int, BLOCK_COUNT> getBlockOrder(std::shared_ptr<u8[]> dt, int ofs);
        static int getActiveSaveIndex(std::shared_ptr<u8[]> dt,
            std::array<int, BLOCK_COUNT>& blockOrder1, std::array<int, BLOCK_COUNT>& blockOrder2);

        static constexpr u16 chunkLength[BLOCK_COUNT] = {
            0xf2c, // 0 | Small Block (Trainer Info)
            0xf80, // 1 | Large Block Part 1
            0xf80, // 2 | Large Block Part 2
            0xf80, // 3 | Large Block Part 3
            0xf08, // 4 | Large Block Part 4
            0xf80, // 5 | PC Block 0
            0xf80, // 6 | PC Block 1
            0xf80, // 7 | PC Block 2
            0xf80, // 8 | PC Block 3
            0xf80, // 9 | PC Block 4
            0xf80, // A | PC Block 5
            0xf80, // B | PC Block 6
            0xf80, // C | PC Block 7
            0x7d0  // D | PC Block 8
        };

        int ABO() const { return activeSAV * SIZE_BLOCK * BLOCK_COUNT; };

        int activeSAV;

        u32 securityKey() const;

        bool getEventFlag(int flagNumber) const;
        void setEventFlag(int flagNumber, bool value);

        bool canSetDex(Species species);

        u32 dexPIDUnown(void);
        void dexPIDUnown(u32 v);
        u32 dexPIDSpinda(void);
        void dexPIDSpinda(u32 v);

        bool getCaught(Species species) const;
        void setCaught(Species species, bool caught);
        bool getSeen(Species species) const;
        void setSeen(Species species, bool seen);

        Sav3(std::shared_ptr<u8[]> data, const std::vector<int>& seenFlagOffsets);

    public:
        static constexpr int SIZE_BLOCK = 0x1000;
        static Game getVersion(std::shared_ptr<u8[]> dt);

        void resign(void);
        void finishEditing(void) override { resign(); }
        void beginEditing(void) override {}

        u8* getBlock(size_t blockNum) { return &data[blockOfs[blockNum]]; }

        u16 TID(void) const override;
        void TID(u16 v) override;
        u16 SID(void) const override;
        void SID(u16 v) override;
        GameVersion version(void) const override;
        void version(GameVersion v) override;
        Gender gender(void) const override;
        void gender(Gender v) override;
        u8 subRegion(void) const override { return 0; }
        void subRegion(u8) override {}
        u8 country(void) const override { return 0; }
        void country(u8) override {}
        u8 consoleRegion(void) const override { return 0; }
        void consoleRegion(u8) override {}
        Language language(void) const override;
        void language(Language v) override;
        std::string otName(void) const override;
        void otName(const std::string_view& v) override;
        u32 money(void) const override;
        void money(u32 v) override;
        u32 BP(void) const override;
        void BP(u32 v) override;
        u8 badges(void) const override;
        u16 playedHours(void) const override;
        void playedHours(u16 v) override;
        u8 playedMinutes(void) const override;
        void playedMinutes(u8 v) override;
        u8 playedSeconds(void) const override;
        void playedSeconds(u8 v) override;

        u8 currentBox(void) const override;
        void currentBox(u8 v) override;
        u8 unlockedBoxes(void) const override { return maxBoxes(); }
        void unlockedBoxes(u8) override {}
        u8 legendBoxUnlockSize(void) const override { return 0; }
        // Note: a Pokemon may be split up into two pieces! That will happen if RETURNVALUE % 0x1000
        // + PK3::BOX_LENGTH > 0xF80 In this case, the first 0xF80 - RETURNVALUE bytes of a Pokemon
        // should be written to the returned offset, with the remainder written to offset
        // boxOffset(box + (slot + 1) / 30, (slot + 1) % 30) & 0xFFFFF000
        u32 boxOffset(u8 box, u8 slot) const override;
        u32 partyOffset(u8 slot) const override;

        std::unique_ptr<PKX> pkm(u8 slot) const override;
        std::unique_ptr<PKX> pkm(u8 box, u8 slot) const override;

        // NOTICE: this sets a pkx into the savefile, not a ekx
        // that's because PKSM works with decrypted boxes and
        // crypts them back during resigning
        void pkm(const PKX& pk, u8 slot) override;
        void pkm(const PKX& pk, u8 box, u8 slot, bool applyTrade) override;

        void trade(PKX& pk, const Date& date = Date::today()) const override;
        std::unique_ptr<PKX> emptyPkm() const override;

        void dex(const PKX& pk) override;
        int dexSeen(void) const override;
        int dexCaught(void) const override;
        int currentGiftAmount(void) const override { return 0; }
        void mysteryGift(const WCX&, int&) override {}
        std::unique_ptr<WCX> mysteryGift(int pos) const override;
        void cryptBoxData(bool crypted) override;
        std::string boxName(u8 box) const override;
        void boxName(u8 box, const std::string_view& name) override;
        u8 boxWallpaper(u8 box) const override;
        void boxWallpaper(u8 box, u8 v) override;
        u8 partyCount(void) const override;
        void partyCount(u8 count) override;

        int maxBoxes(void) const override { return 14; }
        size_t maxWondercards(void) const override { return 0; }
        Generation generation(void) const override { return Generation::THREE; }

        void item(const Item& item, Pouch pouch, u16 slot) override;
        std::unique_ptr<Item> item(Pouch pouch, u16 slot) const override;
        std::vector<std::pair<Pouch, int>> pouches(void) const override;
        // G3 item IDs
        virtual std::map<Pouch, std::vector<int>> validItems3(void) const = 0;

        u16 rtcInitialDay(void) const;
        void rtcInitialDay(u16 v);
        u8 rtcInitialHour(void) const;
        void rtcInitialHour(u8 v);
        u8 rtcInitialMinute(void) const;
        void rtcInitialMinute(u8 v);
        u8 rtcInitialSecond(void) const;
        void rtcInitialSecond(u8 v);

        u16 rtcElapsedDay(void) const;
        void rtcElapsedDay(u16 v);
        u8 rtcElapsedHour(void) const;
        void rtcElapsedHour(u8 v);
        u8 rtcElapsedMinute(void) const;
        void rtcElapsedMinute(u8 v);
        u8 rtcElapsedSecond(void) const;
        void rtcElapsedSecond(u8 v);
    };
}

#endif
