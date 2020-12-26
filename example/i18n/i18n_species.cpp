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

#include "enums/Species.hpp"
#include "i18n_internal.hpp"

namespace i18n
{
    std::unordered_map<pksm::Language, std::vector<std::string>> speciess;

    void initSpecies(pksm::Language lang)
    {
        std::vector<std::string> vec;
        load(lang, "/species.txt", vec);
        speciess.insert_or_assign(lang, std::move(vec));
    }

    void exitSpecies(pksm::Language lang) { speciess.erase(lang); }

    const std::string& species(pksm::Language lang, pksm::Species val)
    {
        checkInitialized(lang);
        if (speciess.count(lang) > 0)
        {
            if (size_t(val) < speciess[lang].size())
            {
                return speciess[lang][size_t(val)];
            }
        }
        return emptyString;
    }

    const std::vector<std::string>& rawSpecies(pksm::Language lang)
    {
        checkInitialized(lang);
        if (speciess.count(lang) > 0)
        {
            return speciess[lang];
        }
        return emptyVector;
    }
}

const std::string& pksm::internal::Species_impl::localize(pksm::Language lang) const
{
    return i18n::species(lang, *this);
}
