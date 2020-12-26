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

#include "sav/Sav5.hpp"
#include "pkx/PK5.hpp"
#include "utils/crypto.hpp"
#include "utils/endian.hpp"
#include "utils/i18n.hpp"
#include "utils/utils.hpp"
#include "wcx/PGF.hpp"

namespace pksm
{
    u16 Sav5::TID(void) const { return LittleEndian::convertTo<u16>(&data[Trainer1 + 0x14]); }
    void Sav5::TID(u16 v) { LittleEndian::convertFrom<u16>(&data[Trainer1 + 0x14], v); }

    u16 Sav5::SID(void) const { return LittleEndian::convertTo<u16>(&data[Trainer1 + 0x16]); }
    void Sav5::SID(u16 v) { LittleEndian::convertFrom<u16>(&data[Trainer1 + 0x16], v); }

    GameVersion Sav5::version(void) const { return GameVersion(data[Trainer1 + 0x1F]); }
    void Sav5::version(GameVersion v) { data[Trainer1 + 0x1F] = u8(v); }

    Gender Sav5::gender(void) const { return Gender{data[Trainer1 + 0x21]}; }
    void Sav5::gender(Gender v) { data[Trainer1 + 0x21] = u8(v); }

    Language Sav5::language(void) const { return Language(data[Trainer1 + 0x1E]); }
    void Sav5::language(Language v) { data[Trainer1 + 0x1E] = u8(v); }

    std::string Sav5::otName(void) const
    {
        return StringUtils::transString45(
            StringUtils::getString(data.get(), Trainer1 + 0x4, 8, u'\uFFFF'));
    }
    void Sav5::otName(const std::string_view& v)
    {
        StringUtils::setString(
            data.get(), StringUtils::transString45(v), Trainer1 + 0x4, 8, u'\uFFFF', 0);
    }

    u32 Sav5::money(void) const { return LittleEndian::convertTo<u32>(&data[Trainer2]); }
    void Sav5::money(u32 v) { LittleEndian::convertFrom<u32>(&data[Trainer2], v); }

    u32 Sav5::BP(void) const { return LittleEndian::convertTo<u16>(&data[BattleSubway]); }
    void Sav5::BP(u32 v) { LittleEndian::convertFrom<u32>(&data[BattleSubway], v); }

    u8 Sav5::badges(void) const
    {
        u8& badgeBits = data[Trainer2 + 0x4];
        u8 ret        = 0;
        for (size_t i = 0; i < sizeof(badgeBits) * 8; i++)
        {
            ret += (badgeBits & (1 << i)) ? 1 : 0;
        }
        return ret;
    }

    u16 Sav5::playedHours(void) const
    {
        return LittleEndian::convertTo<u16>(&data[Trainer1 + 0x24]);
    }
    void Sav5::playedHours(u16 v) { LittleEndian::convertFrom<u16>(&data[Trainer1 + 0x24], v); }

    u8 Sav5::playedMinutes(void) const { return data[Trainer1 + 0x26]; }
    void Sav5::playedMinutes(u8 v) { data[Trainer1 + 0x26] = v; }

    u8 Sav5::playedSeconds(void) const { return data[Trainer1 + 0x27]; }
    void Sav5::playedSeconds(u8 v) { data[Trainer1 + 0x27] = v; }

    u8 Sav5::currentBox(void) const { return data[PCLayout]; }
    void Sav5::currentBox(u8 v) { data[PCLayout] = v; }

    u8 Sav5::unlockedBoxes(void) const { return data[PCLayout + 0x3DD]; }
    void Sav5::unlockedBoxes(u8 v) { data[PCLayout + 0x3DD] = v; }

    u32 Sav5::boxOffset(u8 box, u8 slot) const
    {
        return Box + PK5::BOX_LENGTH * box * 30 + 0x10 * box + PK5::BOX_LENGTH * slot;
    }
    u32 Sav5::partyOffset(u8 slot) const { return Party + 8 + PK5::PARTY_LENGTH * slot; }

    std::unique_ptr<PKX> Sav5::pkm(u8 slot) const
    {
        return PKX::getPKM<Generation::FIVE>(&data[partyOffset(slot)], true);
    }

    void Sav5::pkm(const PKX& pk, u8 slot)
    {
        if (pk.generation() == Generation::FIVE)
        {
            auto pk5 = pk.partyClone();
            pk5->encrypt();
            std::copy(pk5->rawData(), pk5->rawData() + pk5->getLength(), &data[partyOffset(slot)]);
        }
    }

    std::unique_ptr<PKX> Sav5::pkm(u8 box, u8 slot) const
    {
        return PKX::getPKM<Generation::FIVE>(&data[boxOffset(box, slot)]);
    }

    void Sav5::pkm(const PKX& pk, u8 box, u8 slot, bool applyTrade)
    {
        if (pk.generation() == Generation::FIVE)
        {
            auto pk5 = pk.clone();
            if (applyTrade)
            {
                trade(*pk5);
            }

            std::copy(
                pk5->rawData(), pk5->rawData() + PK5::BOX_LENGTH, &data[boxOffset(box, slot)]);
        }
    }

    void Sav5::trade(PKX& pk, const Date& date) const
    {
        if (pk.generation() == Generation::FIVE && pk.egg() &&
            (otName() != pk.otName() || TID() != pk.TID() || SID() != pk.SID() ||
                gender() != pk.otGender()))
        {
            pk.metLocation(30003);
            pk.metDate(date);
        }
    }

    void Sav5::cryptBoxData(bool crypted)
    {
        for (u8 box = 0; box < maxBoxes(); box++)
        {
            for (u8 slot = 0; slot < 30; slot++)
            {
                std::unique_ptr<PKX> pk5 =
                    PKX::getPKM<Generation::FIVE>(&data[boxOffset(box, slot)], false, true);
                if (!crypted)
                {
                    pk5->encrypt();
                }
            }
        }
    }

    int Sav5::dexFormIndex(int species, int formct) const
    {
        if (formct < 1 || species < 0)
            return -1; // invalid

        if (game == Game::B2W2)
        {
            switch (species)
            {
                case 646:
                    return 72; // 3 Kyurem
                case 647:
                    return 75; // 2 Keldeo
                case 642:
                    return 77; // 2 Thundurus
                case 641:
                    return 79; // 2 Tornadus
                case 645:
                    return 81; // 2 Landorus
            }
        }

        switch (species)
        {
            case 201:
                return 0; // 28 Unown
            case 386:
                return 28; // 4 Deoxys
            case 492:
                return 32; // 2 Shaymin
            case 487:
                return 34; // 2 Giratina
            case 479:
                return 36; // 6 Rotom
            case 422:
                return 42; // 2 Shellos
            case 423:
                return 44; // 2 Gastrodon
            case 412:
                return 46; // 3 Burmy
            case 413:
                return 49; // 3 Wormadam
            case 351:
                return 52; // 4 Castform
            case 421:
                return 56; // 2 Cherrim
            case 585:
                return 58; // 4 Deerling
            case 586:
                return 62; // 4 Sawsbuck
            case 648:
                return 66; // 2 Meloetta
            case 555:
                return 68; // 2 Darmanitan
            case 550:
                return 70; // 2 Basculin
            default:
                return -1;
        }
    }

    void Sav5::dex(const PKX& pk)
    {
        if (!(availableSpecies().count(pk.species()) > 0) || pk.egg())
            return;

        const int brSize = 0x54;
        int bit          = u16(pk.species()) - 1;
        int gender       = u8(pk.gender()) % 2; // genderless -> male
        int shiny        = pk.shiny() ? 1 : 0;
        int shift        = shiny * 2 + gender + 1;
        int shiftoff     = shiny * brSize * 2 + gender * brSize + brSize;
        int ofs          = PokeDex + 0x8 + (bit >> 3);

        // Set the Species Owned Flag
        data[ofs + brSize * 0] |= (1 << (bit % 8));

        // Set the [Species/Gender/Shiny] Seen Flag
        data[PokeDex + 0x8 + shiftoff + bit / 8] |= (1 << (bit & 7));

        // Set the Display flag if none are set
        bool displayed = false;
        displayed |= (data[ofs + brSize * 5] & (1 << (bit & 7))) != 0;
        displayed |= (data[ofs + brSize * 6] & (1 << (bit & 7))) != 0;
        displayed |= (data[ofs + brSize * 7] & (1 << (bit & 7))) != 0;
        displayed |= (data[ofs + brSize * 8] & (1 << (bit & 7))) != 0;
        if (!displayed) // offset is already biased by brSize, reuse shiftoff but for the display
                        // flags.
            data[ofs + brSize * (shift + 4)] |= (1 << (bit & 7));

        // Set the Language
        if (bit < 493) // shifted by 1, Gen5 species do not have international language bits
        {
            int lang = u8(pk.language()) - 1;
            if (lang > 5)
                lang--; // 0-6 language vals
            if (lang < 0)
                lang = 1;
            data[PokeDexLanguageFlags + ((bit * 7 + lang) >> 3)] |= (1 << ((bit * 7 + lang) & 7));
        }

        // Formes
        int fc = PersonalBWB2W2::formCount(u16(pk.species()));
        int f  = dexFormIndex(u16(pk.species()), fc);
        if (f < 0)
            return;

        int formLen = game == Game::BW ? 0x9 : 0xB;
        int formDex = PokeDex + 0x8 + brSize * 9;
        bit         = f + pk.alternativeForm();

        // Set Form Seen Flag
        data[formDex + formLen * shiny + (bit >> 3)] |= (1 << (bit & 7));

        // Set displayed Flag if necessary, check all flags
        for (int i = 0; i < fc; i++)
        {
            bit = f + i;
            if ((data[formDex + formLen * 2 + (bit >> 3)] & (1 << (bit & 7))) != 0) // Nonshiny
                return;                                                             // already set
            if ((data[formDex + formLen * 3 + (bit >> 3)] & (1 << (bit & 7))) != 0) // Shiny
                return;                                                             // already set
        }
        bit = f + pk.alternativeForm();
        data[formDex + formLen * (2 + shiny) + (bit >> 3)] |= (1 << (bit & 7));
    }

    int Sav5::dexSeen(void) const
    {
        int ret = 0;
        for (const auto& spec : availableSpecies())
        {
            u16 i        = u16(spec);
            int bitIndex = (i - 1) & 7;
            for (int j = 0; j < 4; j++) // All seen flags: gender & shinies
            {
                int ofs = PokeDex + (0x5C + (j * 0x54)) + ((i - 1) >> 3);
                if ((data[ofs] >> bitIndex & 1) != 0)
                {
                    ret++;
                    break;
                }
            }
        }
        return ret;
    }

    int Sav5::dexCaught(void) const
    {
        int ret = 0;
        for (const auto& spec : availableSpecies())
        {
            u16 i        = u16(spec);
            int bitIndex = (i - 1) & 7;
            int ofs      = PokeDex + 0x8 + ((i - 1) >> 3);
            if ((data[ofs] >> bitIndex & 1) != 0)
            {
                ret++;
            }
        }
        return ret;
    }

    void Sav5::mysteryGift(const WCX& wc, int& pos)
    {
        if (wc.generation() == Generation::FIVE)
        {
            data[WondercardFlags + (wc.ID() / 8)] |= 0x1 << (wc.ID() & 7);
            std::copy(wc.rawData(), wc.rawData() + PGF::length,
                &data[WondercardData + pos * PGF::length]);
            pos = (pos + 1) % 12;
        }
    }

    std::string Sav5::boxName(u8 box) const
    {
        return StringUtils::transString45(
            StringUtils::getString(data.get(), PCLayout + 0x28 * box + 4, 9, u'\uFFFF'));
    }
    void Sav5::boxName(u8 box, const std::string_view& name)
    {
        StringUtils::setString(data.get(), StringUtils::transString45(name),
            PCLayout + 0x28 * box + 4, 9, u'\uFFFF', 0);
    }

    u8 Sav5::boxWallpaper(u8 box) const { return data[PCLayout + 0x3C4 + box]; }
    void Sav5::boxWallpaper(u8 box, u8 v) { data[PCLayout + 0x3C4 + box] = v; }

    u8 Sav5::partyCount(void) const { return data[Party + 4]; }
    void Sav5::partyCount(u8 v) { data[Party + 4] = v; }

    std::unique_ptr<PKX> Sav5::emptyPkm() const { return PKX::getPKM<Generation::FIVE>(nullptr); }

    int Sav5::currentGiftAmount(void) const
    {
        u8 t;
        // 12 max wonder cards
        for (t = 0; t < 12; t++)
        {
            bool empty = true;
            for (u32 j = 0; j < PGF::length; j++)
            {
                if (data[WondercardData + t * PGF::length + j] != 0)
                {
                    empty = false;
                    break;
                }
            }

            if (empty)
            {
                break;
            }
        }

        return t;
    }

    void Sav5::cryptMysteryGiftData()
    {
        u32 seed = LittleEndian::convertTo<u32>(&data[0x1D290]);
        pksm::crypto::pkm::crypt<0xA90>(&data[WondercardFlags], seed);
    }

    std::unique_ptr<WCX> Sav5::mysteryGift(int pos) const
    {
        return std::make_unique<PGF>(&data[WondercardData + pos * PGF::length]);
    }

    void Sav5::item(const Item& item, Pouch pouch, u16 slot)
    {
        Item5 inject = static_cast<Item5>(item);
        auto write   = inject.bytes();
        switch (pouch)
        {
            case Pouch::NormalItem:
                std::copy(write.begin(), write.end(), &data[PouchHeldItem + slot * 4]);
                break;
            case Pouch::KeyItem:
                std::copy(write.begin(), write.end(), &data[PouchKeyItem + slot * 4]);
                break;
            case Pouch::TM:
                std::copy(write.begin(), write.end(), &data[PouchTMHM + slot * 4]);
                break;
            case Pouch::Medicine:
                std::copy(write.begin(), write.end(), &data[PouchMedicine + slot * 4]);
                break;
            case Pouch::Berry:
                std::copy(write.begin(), write.end(), &data[PouchBerry + slot * 4]);
                break;
            default:
                return;
        }
    }

    std::unique_ptr<Item> Sav5::item(Pouch pouch, u16 slot) const
    {
        switch (pouch)
        {
            case Pouch::NormalItem:
                return std::make_unique<Item5>(&data[PouchHeldItem + slot * 4]);
            case Pouch::KeyItem:
                return std::make_unique<Item5>(&data[PouchKeyItem + slot * 4]);
            case Pouch::TM:
                return std::make_unique<Item5>(&data[PouchTMHM + slot * 4]);
            case Pouch::Medicine:
                return std::make_unique<Item5>(&data[PouchMedicine + slot * 4]);
            case Pouch::Berry:
                return std::make_unique<Item5>(&data[PouchBerry + slot * 4]);
            default:
                return nullptr;
        }
    }

    std::vector<std::pair<Sav::Pouch, int>> Sav5::pouches() const
    {
        return {{Pouch::NormalItem, 261}, {Pouch::KeyItem, game == Game::BW ? 19 : 27},
            {Pouch::TM, 101}, {Pouch::Medicine, 47}, {Pouch::Berry, 64}};
    }
}
