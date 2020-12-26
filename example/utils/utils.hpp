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

#ifndef UTILS_HPP
#define UTILS_HPP

#include "utils/coretypes.h"
#include <codecvt>
#include <locale>
#include <memory>
#include <optional>
#include <stdarg.h>
#include <string.h>
#include <string>
#include <vector>

namespace StringUtils
{
    // Standard UTF-8/16/32 conversions
    std::u16string UTF8toUTF16(const std::string_view& src); // done
    std::string UTF16toUTF8(const std::u16string_view& src); // done

    std::u32string UTF8toUTF32(const std::string_view& src); // done
    std::string UTF32toUTF8(const std::u32string_view& src); // done

    std::u32string UTF16toUTF32(const std::u16string_view& src); // done
    std::u16string UTF32toUTF16(const std::u32string_view& src); // done

    // UCS-2 is UTF-16 without the extended codepage(s). This is the format used in recent Pokémon
    // games. It can be seen as the valid UTF-16 codepoints between 0x0000 and 0xFFFF, inclusive.
    // Note that passing a UTF-8 string that contains only codepoints in that region to UTF8toUTF16
    // will also result in a UCS-2 string.
    std::u16string UTF8toUCS2(const std::string_view& src);     // done
    std::u16string UTF16toUCS2(const std::u16string_view& src); // done
    std::u16string UTF32toUCS2(const std::u32string_view& src); // done
    inline std::string UCS2toUTF8(const std::u16string_view& src) { return UTF16toUTF8(src); }
    inline std::u16string UCS2toUTF16(const std::u16string_view& src)
    {
        return std::u16string(src);
    }
    inline std::u32string UCS2toUTF32(const std::u16string_view& src) { return UTF16toUTF32(src); }

    // All of these take a pointer to a buffer with a UCS-2 little-endian char16_t array at data +
    // ofs, terminated by term, and turn them into the format indicated by the method name.
    std::u32string getU32String(const u8* data, int ofs, int len, char16_t term = u'\0');  // done
    std::u16string getUCS2String(const u8* data, int ofs, int len, char16_t term = u'\0'); // done
    inline std::u16string getU16String(const u8* data, int ofs, int len, char16_t term = u'\0')
    {
        return getUCS2String(data, ofs, len, term);
    }
    std::string getString(const u8* data, int ofs, int len, char16_t term = u'\0'); // done

    // All of these take a pointer to a buffer with a UCS-2 char16_t array at data + ofs and write
    // the given string to them, replacing unrepresentable codepoints with 0xFFFD, and using
    // terminator as the terminator and padding as the characters to set after the terminator.
    // Note that any codepoint >= 0x10000 will be converted to 0xFFFD
    // Note that the u16string_view overload takes a UTF-16 string
    void setString(u8* data, const std::u32string_view& v, int ofs, int len,
        char16_t terminator = u'\0', char16_t padding = u'\0');
    void setString(u8* data, const std::u16string_view& v, int ofs, int len,
        char16_t terminator = u'\0', char16_t padding = u'\0');
    void setString(u8* data, const std::string_view& v, int ofs, int len,
        char16_t terminator = u'\0', char16_t padding = u'\0');

    std::string getString4(const u8* data, int ofs, int len);
    void setString4(u8* data, const std::string_view& v, int ofs, int len);
    std::string getString3(const u8* data, int ofs, int len, bool jp);
    void setString3(u8* data, const std::string_view& v, int ofs, int len, bool jp, int padTo = 0,
        u8 padWith = 0xFF);
    std::vector<u16> stringToG4(const std::string_view& v);
    std::string& toLower(std::string& in);
    std::string toLower(const std::string_view& in);
    std::string& toUpper(std::string& in);
    std::string toUpper(const std::string_view& in);
    std::u16string& toFullWidth(std::u16string& in);
    /** Swaps and reswaps Pokemon specific characters, namely:
     * 0x2227, 0x2228, 0x2460, 0x2461, 0x2462,
     * 0x2463, 0x2464, 0x2465, 0x2466, 0x2469,
     * 0x246A, 0x246B, 0x246C, 0x246D, 0x246E,
     * 0x246F, 0x2470, 0x2471, 0x2472, 0x2473,
     * 0x2474, 0x2475, 0x2476, 0x2477, 0x2478,
     * 0x2479, 0x247A, 0x247B, 0x247C, 0x247D,
     * 0x247E, 0x247F, 0x2480, 0x2481, 0x2482,
     * 0x2483, 0x2484, 0x2485, 0x2486, and 0x2487
     */
    std::string transString45(const std::string_view& str);
    std::u16string transString45(const std::u16string_view& str);
    /** Swaps and reswaps Pokemon specific characters, namely:
     * 0xE088, 0xE089, 0xE08A, 0xE08B, 0xE08C, 0xE0A6
     */
    std::string transString67(const std::string_view& str);
    std::u16string transString67(const std::u16string_view& str);
}

#endif
