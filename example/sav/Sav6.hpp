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

#ifndef SAV6_HPP
#define SAV6_HPP

#include "personal/personal.hpp"
#include "sav/Sav.hpp"

namespace pksm
{
    class Sav6 : public Sav
    {
    protected:
        int TrainerCard, Trainer2, PlayTime, LastViewedBox, PokeDexLanguageFlags, EncounterCount,
            PCLayout;

    private:
        int dexFormIndex(int species, int formct) const;

    public:
        Sav6(std::shared_ptr<u8[]> data, u32 length) : Sav(data, length) {}
        virtual void resign(void) = 0;
        void finishEditing(void) override { resign(); }
        void beginEditing(void) override {}

        u16 TID(void) const override;
        void TID(u16 v) override;
        u16 SID(void) const override;
        void SID(u16 v) override;
        GameVersion version(void) const override;
        void version(GameVersion v) override;
        Gender gender(void) const override;
        void gender(Gender v) override;
        u8 subRegion(void) const override;
        void subRegion(u8 v) override;
        u8 country(void) const override;
        void country(u8 v) override;
        u8 consoleRegion(void) const override;
        void consoleRegion(u8 v) override;
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
        u8 unlockedBoxes(void) const override;
        void unlockedBoxes(u8 v) override;
        u8 legendBoxUnlockSize(void) const override { return 1; }
        u32 boxOffset(u8 box, u8 slot) const override;
        u32 partyOffset(u8 slot) const override;

        std::unique_ptr<PKX> pkm(u8 slot) const override;
        std::unique_ptr<PKX> pkm(u8 box, u8 slot) const override;

        // NOTICE: this sets a pkx into the savefile, not a ekx
        // that's because PKSM works with decrypted boxes and
        // crypts them back during resigning
        void pkm(const PKX& pk, u8 box, u8 slot, bool applyTrade) override;
        void pkm(const PKX& pk, u8 slot) override;

        void trade(PKX& pk, const Date& date = Date::today()) const override;
        std::unique_ptr<PKX> emptyPkm() const override;

        void dex(const PKX& pk) override;
        int dexSeen(void) const override;
        int dexCaught(void) const override;
        int currentGiftAmount(void) const override;
        void mysteryGift(const WCX& wc, int& pos) override;
        std::unique_ptr<WCX> mysteryGift(int pos) const override;
        void cryptBoxData(bool crypted) override;
        std::string boxName(u8 box) const override;
        void boxName(u8 box, const std::string_view& name) override;
        u8 boxWallpaper(u8 box) const override;
        void boxWallpaper(u8 box, u8 v) override;
        u8 partyCount(void) const override;
        void partyCount(u8 count) override;

        int maxBoxes(void) const override { return 31; }
        size_t maxWondercards(void) const override { return 24; }
        Generation generation(void) const override { return Generation::SIX; }

        void item(const Item& item, Pouch pouch, u16 slot) override;
        std::unique_ptr<Item> item(Pouch pouch, u16 slot) const override;
        std::vector<std::pair<Pouch, int>> pouches(void) const override;
    };
}

#endif
