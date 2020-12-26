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

#ifndef I18N_INTERNAL_HPP
#define I18N_INTERNAL_HPP

#include "enums/Language.hpp"
#include "utils/coretypes.h"
#include "utils/i18n.hpp"
#include "utils/io.hpp"
#include <atomic>
#include <time.h>
#include <unordered_map>

#ifndef _PKSMCORE_CONFIGURED
#include "PKSMCORE_CONFIG.h"
#endif

#ifndef _PKSMCORE_GETLINE_FUNC
#define _PKSMCORE_GETLINE_FUNC getline
#endif

namespace i18n
{
    enum class LangState : u8
    {
        UNINITIALIZED,
        INITIALIZING,
        INITIALIZED
    };

    inline const std::string emptyString                = "";
    inline const std::vector<std::string> emptyVector   = {};
    inline const std::map<u16, std::string> emptyU16Map = {};
    inline const std::map<u8, std::string> emptyU8Map   = {};

#ifdef _PKSMCORE_DISABLE_THREAD_SAFETY
    extern std::unordered_map<pksm::Language, LangState> languages;
#else
    extern std::unordered_map<pksm::Language, std::atomic<LangState>> languages;
#endif

    inline void checkInitialized(pksm::Language lang)
    {
        auto found = languages.find(lang);
        if (found == languages.end())
        {
            found = languages.find(pksm::Language::ENG);
        }
        if (found->second == LangState::UNINITIALIZED)
        {
            i18n::init(found->first);
        }
#ifndef _PKSMCORE_DISABLE_THREAD_SAFETY
        while (found->second != LangState::INITIALIZED)
        {
            timespec time = {0, 100000};
            nanosleep(&time, nullptr);
        }
#endif
    }

    std::string folder(pksm::Language lang);

    void load(pksm::Language lang, const std::string& name, std::vector<std::string>& array);
    template <typename T>
    void load(pksm::Language lang, const std::string& name, std::map<T, std::string>& map)
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
                    // 0 automatically deduces the base: 0x prefix makes it hexadecimal, 0 prefix
                    // makes it octal
                    T val    = std::stoi(tmp.substr(0, tmp.find('|')), 0, 0);
                    map[val] = tmp.substr(0, tmp.find('\r')).substr(tmp.find('|') + 1);
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
}

#endif
