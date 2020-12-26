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

#ifndef LANGUAGE_HPP
#define LANGUAGE_HPP

#ifndef _PKSMCORE_CONFIGURED
#include "PKSMCORE_CONFIG.h"
#endif

#include "enums/Generation.hpp"
#include "utils/coretypes.h"
#include <limits>
#include <type_traits>

namespace pksm
{
    enum class Language : u8
    {
        None [[maybe_unused]] = 0,
        JPN                   = 1,
        ENG,
        FRE,
        ITA,
        GER,
        UNUSED [[maybe_unused]],
        SPA,
        KOR,
        CHS,
        CHT,
#ifdef _PKSMCORE_EXTRA_LANGUAGES
        _PKSMCORE_EXTRA_LANGUAGES,
#endif

        INVALID [[maybe_unused]] = std::numeric_limits<std::underlying_type_t<Language>>::max()
    };

    Language getSafeLanguage(Generation gen, Language originalLang);
}

#endif
