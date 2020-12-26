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

#include "enums/Generation.hpp"
#include "i18n_internal.hpp"

namespace i18n
{
    struct Locations
    {
        std::map<u16, std::string> locations3;
        std::map<u16, std::string> locations4;
        std::map<u16, std::string> locations5;
        std::map<u16, std::string> locations6;
        std::map<u16, std::string> locations7;
        std::map<u16, std::string> locationsLGPE;
        std::map<u16, std::string> locations8;
    };

    std::unordered_map<pksm::Language, Locations> locationss;

    void initLocation(pksm::Language lang)
    {
        Locations tmp;
        load(lang, "/locations3.txt", tmp.locations3);
        load(lang, "/locations4.txt", tmp.locations4);
        load(lang, "/locations5.txt", tmp.locations5);
        load(lang, "/locations6.txt", tmp.locations6);
        load(lang, "/locations7.txt", tmp.locations7);
        load(lang, "/locationsLGPE.txt", tmp.locationsLGPE);
        load(lang, "/locations8.txt", tmp.locations8);
        locationss.insert_or_assign(lang, std::move(tmp));
    }

    void exitLocation(pksm::Language lang) { locationss.erase(lang); }

    const std::string& location(pksm::Language lang, pksm::Generation gen, u16 v)
    {
        checkInitialized(lang);
        if (locationss.count(lang) > 0)
        {
            switch (gen)
            {
                case pksm::Generation::THREE:
                    if (locationss[lang].locations3.count(v) > 0)
                    {
                        return locationss[lang].locations3[v];
                    }
                    break;
                case pksm::Generation::FOUR:
                    if (locationss[lang].locations4.count(v) > 0)
                    {
                        return locationss[lang].locations4[v];
                    }
                    break;
                case pksm::Generation::FIVE:
                    if (locationss[lang].locations5.count(v) > 0)
                    {
                        return locationss[lang].locations5[v];
                    }
                    break;
                case pksm::Generation::SIX:
                    if (locationss[lang].locations6.count(v) > 0)
                    {
                        return locationss[lang].locations6[v];
                    }
                    break;
                case pksm::Generation::SEVEN:
                    if (locationss[lang].locations7.count(v) > 0)
                    {
                        return locationss[lang].locations7[v];
                    }
                    break;
                case pksm::Generation::LGPE:
                    if (locationss[lang].locationsLGPE.count(v) > 0)
                    {
                        return locationss[lang].locationsLGPE[v];
                    }
                    break;
                case pksm::Generation::EIGHT:
                    if (locationss[lang].locations8.count(v) > 0)
                    {
                        return locationss[lang].locations8[v];
                    }
                    break;
                case pksm::Generation::UNUSED:
                case pksm::Generation::ONE:
                case pksm::Generation::TWO:
                    break;
            }
        }
        return emptyString;
    }

    const std::map<u16, std::string>& rawLocations(pksm::Language lang, pksm::Generation g)
    {
        checkInitialized(lang);
        if (locationss.count(lang) > 0)
        {
            switch (g)
            {
                case pksm::Generation::THREE:
                    return locationss[lang].locations3;
                case pksm::Generation::FOUR:
                    return locationss[lang].locations4;
                case pksm::Generation::FIVE:
                    return locationss[lang].locations5;
                case pksm::Generation::SIX:
                    return locationss[lang].locations6;
                case pksm::Generation::SEVEN:
                    return locationss[lang].locations7;
                case pksm::Generation::LGPE:
                    return locationss[lang].locationsLGPE;
                case pksm::Generation::EIGHT:
                    return locationss[lang].locations8;
                case pksm::Generation::UNUSED:
                case pksm::Generation::ONE:
                case pksm::Generation::TWO:
                    break;
            }
        }
        return emptyU16Map;
    }
}
