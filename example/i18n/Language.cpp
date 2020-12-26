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

#include "enums/Language.hpp"
#include "enums/Generation.hpp"
#include <algorithm>
#include <array>

namespace pksm
{
    namespace internal
    {
        constexpr std::array<Language, 6> G3Langs = {Language::JPN, Language::ENG, Language::FRE,
            Language::GER, Language::SPA, Language::ITA};
        constexpr std::array<Language, 7> G4Langs = {Language::JPN, Language::ENG, Language::FRE,
            Language::GER, Language::SPA, Language::ITA, Language::KOR};
        constexpr std::array<Language, 9> G7Langs = {Language::JPN, Language::ENG, Language::FRE,
            Language::GER, Language::SPA, Language::ITA, Language::KOR, Language::CHS,
            Language::CHT};
    }

    Language getSafeLanguage(Generation gen, Language orig)
    {
        switch (gen)
        {
            // case Generation::ONE
            // case Generation::TWO
            case Generation::THREE:
                if (std::find(internal::G3Langs.begin(), internal::G3Langs.end(), orig) !=
                    internal::G3Langs.end())
                {
                    return orig;
                }
                return Language::ENG;
            case Generation::FOUR:
            case Generation::FIVE:
            case Generation::SIX:
                if (std::find(internal::G4Langs.begin(), internal::G4Langs.end(), orig) !=
                    internal::G4Langs.end())
                {
                    return orig;
                }
                return Language::ENG;

            case Generation::SEVEN:
            case Generation::LGPE:
            case Generation::EIGHT:
                if (std::find(internal::G7Langs.begin(), internal::G7Langs.end(), orig) !=
                    internal::G7Langs.end())
                {
                    return orig;
                }
                return Language::ENG;
            case Generation::UNUSED:
            case Generation::ONE:
            case Generation::TWO:
                break;
        }
        return Language::ENG;
    }
}
