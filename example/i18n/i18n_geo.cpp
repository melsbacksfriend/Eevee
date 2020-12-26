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

#include "i18n_internal.hpp"

namespace i18n
{
    std::unordered_map<pksm::Language, std::map<u8, std::string>> countries;
    std::unordered_map<pksm::Language, std::map<u8, std::map<u8, std::string>>> subregions;

    std::string subregionFileName(u8 region)
    {
        std::string ret = "/subregions/000.txt";
        for (int pos = 0; pos < 3; pos++)
        {
            char setMe                = '0' + (region % 10);
            ret[ret.size() - 5 - pos] = setMe;
            region /= 10;
        }
        return ret;
    }

    void initGeo(pksm::Language lang)
    {
        std::map<u8, std::string> tmp;
        load(lang, "/countries.txt", tmp);
        countries.insert_or_assign(lang, std::move(tmp));

        std::map<u8, std::map<u8, std::string>> tmp2;
        for (auto i = tmp.begin(); i != tmp.end(); i++)
        {
            tmp2[i->first] = {};
            load(lang, subregionFileName(i->first), tmp2[i->first]);
        }
        subregions.insert_or_assign(lang, std::move(tmp2));
    }

    void exitGeo(pksm::Language lang)
    {
        countries.erase(lang);
        subregions.erase(lang);
    }

    const std::string& subregion(pksm::Language lang, u8 country, u8 v)
    {
        checkInitialized(lang);
        if (subregions.count(lang) > 0)
        {
            if (subregions[lang].count(country) > 0)
            {
                if (subregions[lang][country].count(v) > 0)
                {
                    return subregions[lang][country][v];
                }
            }
        }
        return emptyString;
    }

    const std::string& country(pksm::Language lang, u8 v)
    {
        checkInitialized(lang);
        if (countries.count(lang) > 0)
        {
            if (countries[lang].count(v) > 0)
            {
                return countries[lang][v];
            }
        }
        return emptyString;
    }

    const std::map<u8, std::string>& rawCountries(pksm::Language lang)
    {
        checkInitialized(lang);
        if (countries.count(lang) > 0)
        {
            return countries[lang];
        }
        return emptyU8Map;
    }

    const std::map<u8, std::string>& rawSubregions(pksm::Language lang, u8 country)
    {
        checkInitialized(lang);
        if (subregions.count(lang) > 0)
        {
            if (subregions[lang].count(country) > 0)
            {
                return subregions[lang][country];
            }
        }
        return emptyU8Map;
    }
}
