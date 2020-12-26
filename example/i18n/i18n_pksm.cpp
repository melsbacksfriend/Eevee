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
#include "utils/_map_macro.hpp"
#include "utils/utils.hpp"
#include <algorithm>
#include <functional>
#include <list>

#ifdef _PKSMCORE_EXTRA_LANGUAGES
#define LANGUAGES_TO_USE JPN, ENG, FRE, ITA, GER, SPA, KOR, CHS, CHT, _PKSMCORE_EXTRA_LANGUAGES
#else
#define LANGUAGES_TO_USE JPN, ENG, FRE, ITA, GER, SPA, KOR, CHS, CHT
#endif

#define MAKE_MAP(lang) ret.emplace(pksm::Language::lang, LangState::UNINITIALIZED);
#define TO_STRING_CASE(lang)                                                                       \
    case pksm::Language::lang:                                                                     \
    {                                                                                              \
        static const std::string str = #lang;                                                      \
        return str;                                                                                \
    }
#define TO_IF_STRING(lang)                                                                         \
    if (value == #lang)                                                                            \
        return pksm::Language::lang;
#define TO_FOLDER_CASE(lang)                                                                       \
    case pksm::Language::lang:                                                                     \
        return StringUtils::toLower(#lang);

namespace i18n
{
#ifdef _PKSMCORE_DISABLE_THREAD_SAFETY
    std::unordered_map<pksm::Language, LangState> languages = std::invoke([]() {
        std::unordered_map<pksm::Language, LangState> ret;
        MAP(MAKE_MAP, LANGUAGES_TO_USE);
        return ret;
    });
#else
    std::unordered_map<pksm::Language, std::atomic<LangState>> languages = std::invoke([]() {
        std::unordered_map<pksm::Language, std::atomic<LangState>> ret;
        MAP(MAKE_MAP, LANGUAGES_TO_USE);
        return ret;
    });
#endif

    std::list<initCallback> initCallbacks = {initAbility, initBall, initForm, initGame, initGeo,
        initType, initItem, initItem3, initLocation, initMove, initNature, initRibbon, initSpecies};
    std::list<exitCallback> exitCallbacks = {exitAbility, exitBall, exitForm, exitGame, exitGeo,
        exitType, exitItem, exitItem3, exitLocation, exitMove, exitNature, exitRibbon, exitSpecies};

    void init(pksm::Language lang)
    {
        auto found = languages.find(lang);
        // Should never happen, but might as well check
        if (found == languages.end())
        {
            found = languages.find(pksm::Language::ENG);
        }
#ifdef _PKSMCORE_DISABLE_THREAD_SAFETY
        if (found->second == LangState::UNINITIALIZED)
        {
            found->second = LangState::INITIALIZING;
#else
        LangState expected = LangState::UNINITIALIZED;
        if (found->second.compare_exchange_strong(expected, LangState::INITIALIZING))
        {
#endif
            for (const auto& callback : initCallbacks)
            {
                callback(lang);
            }
            found->second = LangState::INITIALIZED;
        }
    }

    void exit(void)
    {
        for (auto& lang : languages)
        {
            if (lang.second != LangState::UNINITIALIZED)
            {
#ifndef _PKSMCORE_DISABLE_THREAD_SAFETY
                while (lang.second != LangState::INITIALIZED)
                {
                    timespec time = {0, 100000};
                    nanosleep(&time, nullptr);
                }
#endif

                for (const auto& callback : exitCallbacks)
                {
                    callback(lang.first);
                }

                lang.second = LangState::UNINITIALIZED;
            }
        }
    }

    const std::string& langString(pksm::Language l)
    {
        static const std::string ENG = "ENG";
        switch (l)
        {
            MAP(TO_STRING_CASE, LANGUAGES_TO_USE)
            default:
                return ENG;
        }
    }

    pksm::Language langFromString(const std::string_view& value)
    {
        MAP(TO_IF_STRING, LANGUAGES_TO_USE)
        return pksm::Language::ENG;
    }

    std::string folder(pksm::Language lang)
    {
        switch (lang)
        {
            MAP(TO_FOLDER_CASE, LANGUAGES_TO_USE)
            default:
                return "eng";
        }

        return "eng";
    }

    void load(pksm::Language lang, const std::string& name, std::vector<std::string>& array)
    {
        std::string path = io::exists(_PKSMCORE_LANG_FOLDER + folder(lang) + name)
                               ? _PKSMCORE_LANG_FOLDER + folder(lang) + name
                               : _PKSMCORE_LANG_FOLDER + folder(pksm::Language::ENG) + name;

        std::string tmp;
        FILE* values = fopen(path.c_str(), "rt");
        if (values)
        {
            if (ferror(values))
            {
                fclose(values);
                return;
            }
            char* data  = static_cast<char*>(malloc(128));
            size_t size = 0;
            while (!feof(values) && !ferror(values))
            {
                size = std::max(size, (size_t)128);
                if (_PKSMCORE_GETLINE_FUNC(&data, &size, values) >= 0)
                {
                    tmp = std::string(data);
                    tmp = tmp.substr(0, tmp.find('\n'));
                    array.emplace_back(tmp.substr(0, tmp.find('\r')));
                }
                else
                {
                    break;
                }
            }
            fclose(values);
            free(data);
        }
    }

    void addInitCallback(initCallback callback)
    {
        auto i = std::find(initCallbacks.begin(), initCallbacks.end(), callback);
        if (i == initCallbacks.end())
        {
            initCallbacks.emplace_back(callback);
        }
    }

    void removeInitCallback(initCallback callback)
    {
        auto i = std::find(initCallbacks.begin(), initCallbacks.end(), callback);
        while (i != initCallbacks.end())
        {
            initCallbacks.erase(i);
            i = std::find(initCallbacks.begin(), initCallbacks.end(), callback);
        }
    }

    void addExitCallback(exitCallback callback)
    {
        auto i = std::find(exitCallbacks.begin(), exitCallbacks.end(), callback);
        if (i == exitCallbacks.end())
        {
            exitCallbacks.emplace_back(callback);
        }
    }

    void removeExitCallback(exitCallback callback)
    {
        auto i = std::find(exitCallbacks.begin(), exitCallbacks.end(), callback);
        while (i != exitCallbacks.end())
        {
            exitCallbacks.erase(i);
            i = std::find(exitCallbacks.begin(), exitCallbacks.end(), callback);
        }
    }
}
