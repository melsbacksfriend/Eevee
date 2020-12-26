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

#include "enums/Ribbon.hpp"
#include "i18n_internal.hpp"

namespace i18n
{
    std::unordered_map<pksm::Language, std::vector<std::string>> ribbons;

    void initRibbon(pksm::Language lang)
    {
        std::vector<std::string> vec;
        load(lang, "/ribbons.txt", vec);
        ribbons.insert_or_assign(lang, std::move(vec));
    }

    void exitRibbon(pksm::Language lang) { ribbons.erase(lang); }

    const std::string& ribbon(pksm::Language lang, pksm::Ribbon val)
    {
        checkInitialized(lang);
        if (ribbons.count(lang) > 0)
        {
            if (size_t(val) < ribbons[lang].size())
            {
                return ribbons[lang][size_t(val)];
            }
        }
        return emptyString;
    }

    const std::vector<std::string>& rawRibbons(pksm::Language lang)
    {
        checkInitialized(lang);
        if (ribbons.count(lang) > 0)
        {
            return ribbons[lang];
        }
        return emptyVector;
    }
}

const std::string& pksm::internal::Ribbon_impl::localize(pksm::Language lang) const
{
    return i18n::ribbon(lang, *this);
}
