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
 *   along with this program.  If not, see <http://www.&gnu[g/licenses/]>.
 *
 *   Additional Terms 7.b and 7.c of GPLv3 apply to this file:
 *       * Requiring preservation of specified reasonable legal notices or
 *         author attributions in that material or in the Appropriate Legal
 *         Notices displayed by works containing it.
 *       * Prohibiting misrepresentation of the origin of that material,
 *         or requiring that modified versions of such material be marked in
 *         reasonable ways as different from the original version.
 */

#include "sav/Sav7.hpp"
#include "pkx/PK7.hpp"
#include "utils/endian.hpp"
#include "utils/i18n.hpp"
#include "utils/utils.hpp"
#include "wcx/WC7.hpp"

namespace pksm
{
    u16 Sav7::TID(void) const { return LittleEndian::convertTo<u16>(&data[TrainerCard]); }
    void Sav7::TID(u16 v) { LittleEndian::convertFrom<u16>(&data[TrainerCard], v); }

    u16 Sav7::SID(void) const { return LittleEndian::convertTo<u16>(&data[TrainerCard + 2]); }
    void Sav7::SID(u16 v) { LittleEndian::convertFrom<u16>(&data[TrainerCard + 2], v); }

    GameVersion Sav7::version(void) const { return GameVersion(data[TrainerCard + 4]); }
    void Sav7::version(GameVersion v) { data[TrainerCard + 4] = u8(v); }

    Gender Sav7::gender(void) const { return Gender{data[TrainerCard + 5]}; }
    void Sav7::gender(Gender v) { data[TrainerCard + 5] = u8(v); }

    u8 Sav7::subRegion(void) const { return data[TrainerCard + 0x2E]; }
    void Sav7::subRegion(u8 v) { data[TrainerCard + 0x2E] = v; }

    u8 Sav7::country(void) const { return data[TrainerCard + 0x2F]; }
    void Sav7::country(u8 v) { data[TrainerCard + 0x2F] = v; }

    u8 Sav7::consoleRegion(void) const { return data[TrainerCard + 0x34]; }
    void Sav7::consoleRegion(u8 v) { data[TrainerCard + 0x34] = v; }

    Language Sav7::language(void) const { return Language(data[TrainerCard + 0x35]); }
    void Sav7::language(Language v) { data[TrainerCard + 0x35] = u8(v); }

    std::string Sav7::otName(void) const
    {
        return StringUtils::transString67(
            StringUtils::getString(data.get(), TrainerCard + 0x38, 13));
    }
    void Sav7::otName(const std::string_view& v)
    {
        return StringUtils::setString(
            data.get(), StringUtils::transString67(v), TrainerCard + 0x38, 13);
    }

    u32 Sav7::money(void) const { return LittleEndian::convertTo<u32>(&data[Misc + 0x4]); }
    void Sav7::money(u32 v)
    {
        LittleEndian::convertFrom<u32>(&data[Misc + 0x4], v > 9999999 ? 9999999 : v);
    }

    u32 Sav7::BP(void) const { return LittleEndian::convertTo<u32>(&data[Misc + 0x11C]); }
    void Sav7::BP(u32 v)
    {
        LittleEndian::convertFrom<u32>(&data[Misc + 0x11C], v > 9999 ? 9999 : v);
    }

    u8 Sav7::badges(void) const
    {
        u32 badgeBits = (LittleEndian::convertTo<u32>(&data[Misc + 0x8]) << 13) >> 17;
        u8 ret        = 0;
        for (size_t i = 0; i < sizeof(badgeBits) * 8; i++)
        {
            ret += (badgeBits & (u32(1) << i)) ? 1 : 0;
        }
        return ret;
    }

    u16 Sav7::playedHours(void) const { return LittleEndian::convertTo<u16>(&data[PlayTime]); }
    void Sav7::playedHours(u16 v) { LittleEndian::convertFrom<u16>(&data[PlayTime], v); }

    u8 Sav7::playedMinutes(void) const { return data[PlayTime + 2]; }
    void Sav7::playedMinutes(u8 v) { data[PlayTime + 2] = v; }

    u8 Sav7::playedSeconds(void) const { return data[PlayTime + 3]; }
    void Sav7::playedSeconds(u8 v) { data[PlayTime + 3] = v; }

    u8 Sav7::currentBox(void) const { return data[LastViewedBox]; }
    void Sav7::currentBox(u8 v) { data[LastViewedBox] = v; }

    u8 Sav7::unlockedBoxes(void) const { return data[LastViewedBox - 2]; }
    void Sav7::unlockedBoxes(u8 v) { data[LastViewedBox - 2] = v; }

    u32 Sav7::boxOffset(u8 box, u8 slot) const
    {
        return Box + PK7::BOX_LENGTH * 30 * box + PK7::BOX_LENGTH * slot;
    }

    u32 Sav7::partyOffset(u8 slot) const { return Party + PK7::PARTY_LENGTH * slot; }

    std::unique_ptr<PKX> Sav7::pkm(u8 slot) const
    {
        return PKX::getPKM<Generation::SEVEN>(&data[partyOffset(slot)], true);
    }

    void Sav7::pkm(const PKX& pk, u8 slot)
    {
        if (pk.generation() == Generation::SEVEN)
        {
            auto pk7 = pk.partyClone();
            pk7->encrypt();
            std::copy(pk7->rawData(), pk7->rawData() + pk7->getLength(), &data[partyOffset(slot)]);
        }
    }

    std::unique_ptr<PKX> Sav7::pkm(u8 box, u8 slot) const
    {
        return PKX::getPKM<Generation::SEVEN>(&data[boxOffset(box, slot)]);
    }

    void Sav7::pkm(const PKX& pk, u8 box, u8 slot, bool applyTrade)
    {
        if (pk.generation() == Generation::SEVEN)
        {
            auto pkm = pk.clone();
            if (applyTrade)
            {
                trade(*pkm);
            }

            std::copy(
                pkm->rawData(), pkm->rawData() + PK7::BOX_LENGTH, &data[boxOffset(box, slot)]);
        }
    }

    void Sav7::trade(PKX& pk, const Date& date) const
    {
        if (pk.generation() == Generation::SEVEN)
        {
            PK7& pk7 = reinterpret_cast<PK7&>(pk);
            if (pk7.egg())
            {
                if (otName() != pk7.otName() || TID() != pk7.TID() || SID() != pk7.SID() ||
                    gender() != pk7.otGender())
                {
                    pk7.metLocation(30002);
                    pk7.metDate(date);
                }
            }
            else if (otName() == pk7.otName() && TID() == pk7.TID() && SID() == pk7.SID() &&
                     gender() == pk7.otGender())
            {
                pk7.currentHandler(0);
            }
            else
            {
                if (pk7.htName() != otName())
                {
                    pk7.htFriendship(pk7.baseFriendship());
                    pk7.htAffection(0);
                    pk7.htName(otName());
                }
                pk7.currentHandler(1);
                pk7.htGender(gender());
            }
        }
    }

    void Sav7::cryptBoxData(bool crypted)
    {
        for (u8 box = 0; box < maxBoxes(); box++)
        {
            for (u8 slot = 0; slot < 30; slot++)
            {
                std::unique_ptr<PKX> pk7 =
                    PKX::getPKM<Generation::SEVEN>(&data[boxOffset(box, slot)], false, true);
                if (!crypted)
                {
                    pk7->encrypt();
                }
            }
        }
    }

    void Sav7::setDexFlags(int index, int gender, int shiny, int baseSpecies)
    {
        const int brSize = 0x8C;
        int shift        = gender | (shiny << 1);
        int ofs          = PokeDex + 0x08 + 0x80 + 0x68;
        int bd           = index >> 3;
        int bm           = index & 7;
        int bd1          = baseSpecies >> 3;
        int bm1          = baseSpecies & 7;

        int brSeen = shift * brSize;
        data[ofs + brSeen + bd] |= 1 << bm;

        bool displayed = false;
        for (u8 i = 0; i < 4; i++)
        {
            int brDisplayed = (4 + i) * brSize;
            displayed |= (data[ofs + brDisplayed + bd1] & (1 << bm1)) != 0;
        }

        if (!displayed && baseSpecies != index)
        {
            for (u8 i = 0; i < 4; i++)
            {
                int brDisplayed = (4 + i) * brSize;
                displayed |= (data[ofs + brDisplayed + bd] & (1 << bm)) != 0;
            }
        }
        if (displayed)
            return;

        data[ofs + (4 + shift) * brSize + bd] |= (1 << bm);
    }

    int Sav7::getDexFlags(int index, int baseSpecies) const
    {
        int ret          = 0;
        const int brSize = 0x8C;
        int ofs          = PokeDex + 0x08 + 0x80 + 0x68;
        int bd           = index >> 3;
        int bm           = index & 7;
        int bd1          = baseSpecies >> 3;
        int bm1          = baseSpecies & 7;

        for (u8 i = 0; i < 4; i++)
        {
            if (data[ofs + i * brSize + bd] & (1 << bm))
            {
                ret++;
            }
            if (data[ofs + i * brSize + bd1] & (1 << bm1))
            {
                ret++;
            }
        }

        return ret;
    }

    bool Sav7::sanitizeFormsToIterate(Species species, int& fs, int& fe, int formIn) const
    {
        switch (species)
        {
            case Species::Castform: // Castform
                fs = 0;
                fe = 3;
                return true;

            case Species::Cherrim:    // 421:
            case Species::Darmanitan: // 555:
            case Species::Meloetta:   // 648:
            case Species::Wishiwashi: // 746:
            case Species::Mimikyu:    // 778:
                                      // Alolans
            case Species::Raticate:   // 020:
            case Species::Marowak:    // 105:
                fs = 0;
                fe = 1;
                return true;

            case Species::Gumshoos:   // 735:
            case Species::Salazzle:   // 758:
            case Species::Lurantis:   // 754:
            case Species::Vikavolt:   // 738:
            case Species::Kommoo:     // 784:
            case Species::Araquanid:  // 752:
            case Species::Togedemaru: // 777:
            case Species::Ribombee:   // 743:
            case Species::Rockruff:   // 744:
                break;

            case Species::Minior: // 774:
                if (formIn <= 6)
                    break;
                else
                {
                    int count = dexFormCount(u16(species));
                    fs        = 0;
                    fe        = 0;
                    return count < formIn;
                }
            case Species::Zygarde: // 718:
                if (formIn > 1)
                    break;
                else
                {
                    int count = dexFormCount(u16(species));
                    fs        = 0;
                    fe        = 0;
                    return count < formIn;
                }
            default:
                break;
        }

        fs = 0;
        fe = 0;
        return true;
    }

    void Sav7::dex(const PKX& pk)
    {
        if (!(availableSpecies().count(pk.species()) > 0) || pk.egg())
            return;

        int bit    = u16(pk.species()) - 1;
        int bd     = bit >> 3;
        int bm     = bit & 7;
        int gender = u8(pk.gender()) % 2;
        int shiny  = pk.shiny() ? 1 : 0;
        if (pk.species() == Species::Castform)
            shiny = 0;
        int shift = gender | (shiny << 1);

        if (pk.species() == Species::Spinda)
        {
            if ((data[PokeDex + 0x84] & (1 << (shift + 4))) != 0)
            { // Already 2
                LittleEndian::convertFrom<u32>(
                    &data[PokeDex + 0x8E8 + shift * 4], pk.encryptionConstant());
                data[PokeDex + 0x84] |= (u8)(1 << shift);
            }
            else if ((data[PokeDex + 0x84] & (1 << shift)) == 0)
            {                                             // Not yet 1
                data[PokeDex + 0x84] |= (u8)(1 << shift); // 1
            }
        }

        int off = PokeDex + 0x08 + 0x80;
        data[off + bd] |= 1 << bm;

        int formstart = pk.alternativeForm();
        int formend   = formstart;

        int fs = 0, fe = 0;
        if (sanitizeFormsToIterate(pk.species(), fs, fe, formstart))
        {
            formstart = fs;
            formend   = fe;
        }

        for (int form = formstart; form <= formend; form++)
        {
            int bitIndex = bit;
            if (form > 0)
            {
                u8 fc = PersonalSMUSUM::formCount(u16(pk.species()));
                if (fc > 1)
                { // actually has forms
                    int f = dexFormIndex(
                        u16(pk.species()), fc, u16(VersionTables::maxSpecies(version())) - 1);
                    if (f >= 0) // bit index valid
                        bitIndex = f + form;
                }
            }
            setDexFlags(bitIndex, gender, shiny, u16(pk.species()) - 1);
        }

        int lang            = u8(pk.language());
        const int langCount = 9;
        if (lang <= 10 && lang != 6 && lang != 0)
        {
            if (lang >= 7)
                lang--;
            lang--;
            if (lang < 0)
                lang = 1;
            int lbit = bit * langCount + lang;
            if (lbit >> 3 < 920)
                data[PokeDexLanguageFlags + (lbit >> 3)] |= (1 << (lbit & 7));
        }
    }

    int Sav7::dexSeen(void) const
    {
        int ret = 0;
        for (const auto& spec : availableSpecies())
        {
            u16 species = u16(spec);
            int forms   = formCount(spec);
            for (int form = 0; form < forms; form++)
            {
                int dexForms = form == 0 ? -1
                                         : dexFormIndex(species, forms,
                                               u16(VersionTables::maxSpecies(version())) - 1);

                int index = species - 1;
                if (dexForms >= 0)
                {
                    index = dexForms + form;
                }

                if (getDexFlags(index, species) > 0)
                {
                    ret++;
                    break;
                }
            }
        }
        return ret;
    }

    int Sav7::dexCaught(void) const
    {
        int ret = 0;
        for (const auto& spec : availableSpecies())
        {
            u16 i        = u16(spec);
            int bitIndex = (i - 1) & 7;
            int ofs      = PokeDex + 0x88 + ((i - 1) >> 3);
            if ((data[ofs] >> bitIndex & 1) != 0)
            {
                ret++;
            }
        }
        return ret;
    }

    void Sav7::mysteryGift(const WCX& wc, int& pos)
    {
        if (wc.generation() == Generation::SEVEN)
        {
            data[WondercardFlags + wc.ID() / 8] |= 0x1 << (wc.ID() % 8);
            std::copy(wc.rawData(), wc.rawData() + WC7::length,
                &data[WondercardData + WC7::length * pos]);
            pos = (pos + 1) % maxWondercards();
        }
    }

    std::string Sav7::boxName(u8 box) const
    {
        return StringUtils::transString67(
            StringUtils::getString(data.get(), PCLayout + 0x22 * box, 17));
    }
    void Sav7::boxName(u8 box, const std::string_view& name)
    {
        StringUtils::setString(
            data.get(), StringUtils::transString67(name), PCLayout + 0x22 * box, 17);
    }

    u8 Sav7::boxWallpaper(u8 box) const { return data[PCLayout + 1472 + box]; }
    void Sav7::boxWallpaper(u8 box, u8 v) { data[PCLayout + 1472 + box] = v; }

    u8 Sav7::partyCount(void) const { return data[Party + 6 * PK7::PARTY_LENGTH]; }
    void Sav7::partyCount(u8 v) { data[Party + 6 * PK7::PARTY_LENGTH] = v; }

    std::unique_ptr<PKX> Sav7::emptyPkm() const { return PKX::getPKM<Generation::SEVEN>(nullptr); }

    int Sav7::currentGiftAmount(void) const
    {
        u8 t;
        // 48 max wonder cards
        for (t = 0; t < 48; t++)
        {
            bool empty = true;
            for (u32 j = 0; j < WC7::length; j++)
            {
                if (data[WondercardData + t * WC7::length + j] != 0)
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

    std::unique_ptr<WCX> Sav7::mysteryGift(int pos) const
    {
        return std::make_unique<WC7>(&data[WondercardData + pos * WC7::length]);
    }

    void Sav7::item(const Item& item, Pouch pouch, u16 slot)
    {
        Item7 inject = static_cast<Item7>(item);
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
            case Pouch::ZCrystals:
                std::copy(write.begin(), write.end(), &data[PouchZCrystals + slot * 4]);
                break;
            case Pouch::RotomPower:
                std::copy(write.begin(), write.end(), &data[BattleItems + slot * 4]);
                break;
            default:
                return;
        }
    }

    std::unique_ptr<Item> Sav7::item(Pouch pouch, u16 slot) const
    {
        switch (pouch)
        {
            case Pouch::NormalItem:
                return std::make_unique<Item7>(&data[PouchHeldItem + slot * 4]);
            case Pouch::KeyItem:
                return std::make_unique<Item7>(&data[PouchKeyItem + slot * 4]);
            case Pouch::TM:
                return std::make_unique<Item7>(&data[PouchTMHM + slot * 4]);
            case Pouch::Medicine:
                return std::make_unique<Item7>(&data[PouchMedicine + slot * 4]);
            case Pouch::Berry:
                return std::make_unique<Item7>(&data[PouchBerry + slot * 4]);
            case Pouch::ZCrystals:
                return std::make_unique<Item7>(&data[PouchZCrystals + slot * 4]);
            case Pouch::RotomPower:
                return std::make_unique<Item7>(&data[BattleItems + slot * 4]);
            default:
                return nullptr;
        }
    }

    std::vector<std::pair<Sav::Pouch, int>> Sav7::pouches(void) const
    {
        std::vector<std::pair<Pouch, int>> pouches = {
            {Pouch::NormalItem, game == Game::SM ? 430 : 427},
            {Pouch::KeyItem, game == Game::SM ? 184 : 198}, {Pouch::TM, 108},
            {Pouch::Medicine, game == Game::SM ? 64 : 60},
            {Pouch::Berry, game == Game::SM ? 72 : 67},
            {Pouch::ZCrystals, game == Game::SM ? 30 : 35}};

        if (game == Game::USUM)
            pouches.push_back({Pouch::RotomPower, 11});

        return pouches;
    }
}
