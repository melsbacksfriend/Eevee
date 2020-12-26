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

#include "utils/utils.hpp"
#include "g3text.hpp"
#include "g4text.hpp"
#include "utils/endian.hpp"
#include <algorithm>
#include <map>
#include <queue>
#include <vector>

namespace
{
    char32_t swapCodepoints45(char32_t codepoint)
    {
        switch (codepoint)
        {
            case u'\u2227':
                codepoint = u'\uE0A9';
                break;
            case u'\u2228':
                codepoint = u'\uE0AA';
                break;
            case u'\u2460':
                codepoint = u'\uE081';
                break;
            case u'\u2461':
                codepoint = u'\uE082';
                break;
            case u'\u2462':
                codepoint = u'\uE083';
                break;
            case u'\u2463':
                codepoint = u'\uE084';
                break;
            case u'\u2464':
                codepoint = u'\uE085';
                break;
            case u'\u2465':
                codepoint = u'\uE086';
                break;
            case u'\u2466':
                codepoint = u'\uE087';
                break;
            case u'\u2469':
                codepoint = u'\uE068';
                break;
            case u'\u246A':
                codepoint = u'\uE069';
                break;
            case u'\u246B':
                codepoint = u'\uE0AB';
                break;
            case u'\u246C':
                codepoint = u'\uE08D';
                break;
            case u'\u246D':
                codepoint = u'\uE08E';
                break;
            case u'\u246E':
                codepoint = u'\uE08F';
                break;
            case u'\u246F':
                codepoint = u'\uE090';
                break;
            case u'\u2470':
                codepoint = u'\uE091';
                break;
            case u'\u2471':
                codepoint = u'\uE092';
                break;
            case u'\u2472':
                codepoint = u'\uE093';
                break;
            case u'\u2473':
                codepoint = u'\uE094';
                break;
            case u'\u2474':
                codepoint = u'\uE095';
                break;
            case u'\u2475':
                codepoint = u'\uE096';
                break;
            case u'\u2476':
                codepoint = u'\uE097';
                break;
            case u'\u2477':
                codepoint = u'\uE098';
                break;
            case u'\u2478':
                codepoint = u'\uE099';
                break;
            case u'\u2479':
                codepoint = u'\uE09A';
                break;
            case u'\u247A':
                codepoint = u'\uE09B';
                break;
            case u'\u247B':
                codepoint = u'\uE09C';
                break;
            case u'\u247C':
                codepoint = u'\uE09D';
                break;
            case u'\u247D':
                codepoint = u'\uE09E';
                break;
            case u'\u247E':
                codepoint = u'\uE09F';
                break;
            case u'\u247F':
                codepoint = u'\uE0A0';
                break;
            case u'\u2480':
                codepoint = u'\uE0A1';
                break;
            case u'\u2481':
                codepoint = u'\uE0A2';
                break;
            case u'\u2482':
                codepoint = u'\uE0A3';
                break;
            case u'\u2483':
                codepoint = u'\uE0A4';
                break;
            case u'\u2484':
                codepoint = u'\uE0A5';
                break;
            case u'\u2485':
                codepoint = u'\uE06A';
                break;
            case u'\u2486':
                codepoint = u'\uE0A7';
                break;
            case u'\u2487':
                codepoint = u'\uE0A8';
                break;

            case u'\uE0A9':
                codepoint = u'\u2227';
                break;
            case u'\uE0AA':
                codepoint = u'\u2228';
                break;
            case u'\uE081':
                codepoint = u'\u2460';
                break;
            case u'\uE082':
                codepoint = u'\u2461';
                break;
            case u'\uE083':
                codepoint = u'\u2462';
                break;
            case u'\uE084':
                codepoint = u'\u2463';
                break;
            case u'\uE085':
                codepoint = u'\u2464';
                break;
            case u'\uE086':
                codepoint = u'\u2465';
                break;
            case u'\uE087':
                codepoint = u'\u2466';
                break;
            case u'\uE068':
                codepoint = u'\u2469';
                break;
            case u'\uE069':
                codepoint = u'\u246A';
                break;
            case u'\uE0AB':
                codepoint = u'\u246B';
                break;
            case u'\uE08D':
                codepoint = u'\u246C';
                break;
            case u'\uE08E':
                codepoint = u'\u246D';
                break;
            case u'\uE08F':
                codepoint = u'\u246E';
                break;
            case u'\uE090':
                codepoint = u'\u246F';
                break;
            case u'\uE091':
                codepoint = u'\u2470';
                break;
            case u'\uE092':
                codepoint = u'\u2471';
                break;
            case u'\uE093':
                codepoint = u'\u2472';
                break;
            case u'\uE094':
                codepoint = u'\u2473';
                break;
            case u'\uE095':
                codepoint = u'\u2474';
                break;
            case u'\uE096':
                codepoint = u'\u2475';
                break;
            case u'\uE097':
                codepoint = u'\u2476';
                break;
            case u'\uE098':
                codepoint = u'\u2477';
                break;
            case u'\uE099':
                codepoint = u'\u2478';
                break;
            case u'\uE09A':
                codepoint = u'\u2479';
                break;
            case u'\uE09B':
                codepoint = u'\u247A';
                break;
            case u'\uE09C':
                codepoint = u'\u247B';
                break;
            case u'\uE09D':
                codepoint = u'\u247C';
                break;
            case u'\uE09E':
                codepoint = u'\u247D';
                break;
            case u'\uE09F':
                codepoint = u'\u247E';
                break;
            case u'\uE0A0':
                codepoint = u'\u247F';
                break;
            case u'\uE0A1':
                codepoint = u'\u2480';
                break;
            case u'\uE0A2':
                codepoint = u'\u2481';
                break;
            case u'\uE0A3':
                codepoint = u'\u2482';
                break;
            case u'\uE0A4':
                codepoint = u'\u2483';
                break;
            case u'\uE0A5':
                codepoint = u'\u2484';
                break;
            case u'\uE06A':
                codepoint = u'\u2485';
                break;
            case u'\uE0A7':
                codepoint = u'\u2486';
                break;
            case u'\uE0A8':
                codepoint = u'\u2487';
                break;
            default:
                break;
        }
        return codepoint;
    }
    char32_t swapCodepoints67(char32_t codepoint)
    {
        switch (codepoint)
        {
            case u'\uE088':
                codepoint = u'\u00D7';
                break;
            case u'\uE089':
                codepoint = u'\u00F7';
                break;
            case u'\uE08A':
                codepoint = u'\uE068';
                break;
            case u'\uE08B':
                codepoint = u'\uE069';
                break;
            case u'\uE08C':
                codepoint = u'\uE0AB';
                break;
            case u'\uE0A6':
                codepoint = u'\uE06A';
                break;

            case u'\u00D7':
                codepoint = u'\uE088';
                break;
            case u'\u00F7':
                codepoint = u'\uE089';
                break;
            case u'\uE068':
                codepoint = u'\uE08A';
                break;
            case u'\uE069':
                codepoint = u'\uE08B';
                break;
            case u'\uE0AB':
                codepoint = u'\uE08C';
                break;
            case u'\uE06A':
                codepoint = u'\uE0A6';
                break;
        }
        return codepoint;
    }

    // Converts a single latin character from half-width to full-width
    char16_t tofullwidth(char16_t c)
    {
        if (c == ' ')
            c = u'　';
        else if (c >= '!' && c <= '~')
            c += 0xFEE0;
        return c;
    }
}

std::u16string StringUtils::UTF8toUTF16(const std::string_view& src)
{
    std::u16string ret;
    ret.reserve(src.size());
    for (size_t i = 0; i < src.size(); i++)
    {
        char32_t codepoint = 0xFFFD;
        int iMod           = 0;
        if ((src[i] & 0xF8) == 0xF0 && i + 3 < src.size() && (src[i + 1] & 0xC0) == 0x80 &&
            (src[i + 2] & 0xC0) == 0x80 && (src[i + 3] & 0xC0) == 0x80)
        {
            codepoint = src[i] & 0x07;
            codepoint = codepoint << 6 | (src[i + 1] & 0x3F);
            codepoint = codepoint << 6 | (src[i + 2] & 0x3F);
            codepoint = codepoint << 6 | (src[i + 3] & 0x3F);
            iMod      = 3;
        }
        else if ((src[i] & 0xF0) == 0xE0 && i + 2 < src.size() && (src[i + 1] & 0xC0) == 0x80 &&
                 (src[i + 2] & 0xC0) == 0x80)
        {
            codepoint = src[i] & 0x0F;
            codepoint = codepoint << 6 | (src[i + 1] & 0x3F);
            codepoint = codepoint << 6 | (src[i + 2] & 0x3F);
            iMod      = 2;
        }
        else if ((src[i] & 0xE0) == 0xC0 && i + 1 < src.size() && (src[i + 1] & 0xC0) == 0x80)
        {
            codepoint = src[i] & 0x1F;
            codepoint = codepoint << 6 | (src[i + 1] & 0x3F);
            iMod      = 1;
        }
        else if (!(src[i] & 0x80))
        {
            codepoint = src[i];
        }

        if (codepoint <= 0xD7FF || codepoint >= 0xE000)
        {
            ret.push_back(char16_t(codepoint));
        }
        else
        {
            codepoint -= 0x1'0000; // 21->20 bits
            ret.push_back(0xD800 | char16_t((codepoint >> 10) & 0x03FF));
            ret.push_back(0xDC00 | char16_t(codepoint & 0x03FF));
        }

        i += iMod;
    }
    return ret;
}

// Nearly identical, just without the 21-bit case
std::u16string StringUtils::UTF8toUCS2(const std::string_view& src)
{
    std::u16string ret;
    ret.reserve(src.size());
    for (size_t i = 0; i < src.size(); i++)
    {
        char16_t codepoint = 0xFFFD;
        int iMod           = 0;
        if ((src[i] & 0xF0) == 0xE0 && i + 2 < src.size() && (src[i + 1] & 0xC0) == 0x80 &&
            (src[i + 2] & 0xC0) == 0x80)
        {
            codepoint = src[i] & 0x0F;
            codepoint = codepoint << 6 | (src[i + 1] & 0x3F);
            codepoint = codepoint << 6 | (src[i + 2] & 0x3F);
            iMod      = 2;
        }
        else if ((src[i] & 0xE0) == 0xC0 && i + 1 < src.size() && (src[i + 1] & 0xC0) == 0x80)
        {
            codepoint = src[i] & 0x1F;
            codepoint = codepoint << 6 | (src[i + 1] & 0x3F);
            iMod      = 1;
        }
        else if (!(src[i] & 0x80))
        {
            codepoint = src[i];
        }

        ret.push_back(codepoint);

        i += iMod;
    }
    return ret;
}

std::u32string StringUtils::UTF8toUTF32(const std::string_view& src)
{
    std::u32string ret;
    ret.reserve(src.size());
    for (size_t i = 0; i < src.size(); i++)
    {
        char32_t codepoint = 0xFFFD;
        int iMod           = 0;
        if ((src[i] & 0xF8) == 0xF0 && i + 3 < src.size() && (src[i + 1] & 0xC0) == 0x80 &&
            (src[i + 2] & 0xC0) == 0x80 && (src[i + 3] & 0xC0) == 0x80)
        {
            codepoint = src[i] & 0x07;
            codepoint = codepoint << 6 | (src[i + 1] & 0x3F);
            codepoint = codepoint << 6 | (src[i + 2] & 0x3F);
            codepoint = codepoint << 6 | (src[i + 3] & 0x3F);
            iMod      = 3;
        }
        else if ((src[i] & 0xF0) == 0xE0 && i + 2 < src.size() && (src[i + 1] & 0xC0) == 0x80 &&
                 (src[i + 2] & 0xC0) == 0x80)
        {
            codepoint = src[i] & 0x0F;
            codepoint = codepoint << 6 | (src[i + 1] & 0x3F);
            codepoint = codepoint << 6 | (src[i + 2] & 0x3F);
            iMod      = 2;
        }
        else if ((src[i] & 0xE0) == 0xC0 && i + 1 < src.size() && (src[i + 1] & 0xC0) == 0x80)
        {
            codepoint = src[i] & 0x1F;
            codepoint = codepoint << 6 | (src[i + 1] & 0x3F);
            iMod      = 1;
        }
        else if (!(src[i] & 0x80))
        {
            codepoint = src[i];
        }

        ret.push_back(codepoint);

        i += iMod; // Skip continuation bytes
    }
    return ret;
}

std::string StringUtils::UTF16toUTF8(const std::u16string_view& src)
{
    std::string ret;
    ret.reserve(src.size()); // SIze must be greater than or equal to this
    char addChar[5] = {'\0'};
    for (size_t i = 0; i < src.size(); i++)
    {
        if (src[i] < 0x0080)
        {
            addChar[0] = src[i];
            addChar[1] = '\0';
        }
        else if (src[i] < 0x0800)
        {
            addChar[0] = 0xC0 | ((src[i] >> 6) & 0x1F);
            addChar[1] = 0x80 | (src[i] & 0x3F);
            addChar[2] = '\0';
        }
        else if (src[i] <= 0xD7FF || src[i] >= 0xE000)
        {
            addChar[0] = 0xE0 | ((src[i] >> 12) & 0x0F);
            addChar[1] = 0x80 | ((src[i] >> 6) & 0x3F);
            addChar[2] = 0x80 | (src[i] & 0x3F);
            addChar[3] = '\0';
        }
        else if (((src[i] & 0xFC00) == 0xD800) && i + 1 < src.size() &&
                 ((src[i + 1] & 0xFC00) == 0xDC00))
        {
            char32_t codepoint = (char32_t(src[i] & 0x03FF) << 10) | (src[i + 1] & 0x03FF);
            codepoint += 0x1'0000; // 20->21 bits
            addChar[0] = 0xF0 | ((codepoint >> 18) & 0x07);
            addChar[1] = 0x80 | ((codepoint >> 12) & 0x3F);
            addChar[2] = 0x80 | ((codepoint >> 6) & 0x3F);
            addChar[3] = 0x80 | (codepoint & 0x3F);
            addChar[4] = '\0';

            i += 1; // Advance past the first code unit
        }
        else
        {
            addChar[0] = 0xE0 | ((0xFFFD >> 12) & 0x0F);
            addChar[1] = 0x80 | ((0xFFFD >> 6) & 0x3F);
            addChar[2] = 0x80 | (0xFFFD & 0x3F);
            addChar[3] = '\0';
        }
        ret.append(addChar);
    }
    return ret;
}

std::u16string StringUtils::UTF16toUCS2(const std::u16string_view& src)
{
    std::u16string ret;
    ret.reserve(src.size());
    for (size_t i = 0; i < src.size(); i++)
    {
        if (src[i] <= 0xD7FF || src[i] >= 0xE000)
        {
            ret.push_back(src[i]);
        }
        else if (((src[i] & 0xFC00) == 0xD800) && i + 1 < src.size() &&
                 ((src[i + 1] & 0xFC00) == 0xDC00))
        {
            ret.push_back(0xFFFD);
            i += 1; // skip the continuation byte
        }
        else
        {
            ret.push_back(0xFFFD);
            // invalid character sequence, so there's no continuation byte to skip
        }
    }
    return ret;
}

std::u32string StringUtils::UTF16toUTF32(const std::u16string_view& src)
{
    std::u32string ret;
    ret.reserve(src.size());
    for (size_t i = 0; i < src.size(); i++)
    {
        char32_t codepoint = 0xFFFD;
        if (src[i] <= 0xD7FF || src[i] >= 0xE000)
        {
            codepoint = src[i];
        }
        else if (((src[i] & 0xFC00) == 0xD800) && i + 1 < src.size() &&
                 ((src[i + 1] & 0xFC00) == 0xDC00))
        {
            codepoint = (char32_t(src[i] & 0x03FF) << 10) | (src[i + 1] & 0x03FF);
            codepoint += 0x10000; // 20->21 bits
            i += 1;               // skip the continuation byte
        }
        ret.push_back(codepoint);
    }
    return ret;
}

std::string StringUtils::UTF32toUTF8(const std::u32string_view& src)
{
    std::string ret;
    ret.reserve(src.size()); // Length *must* be greater than or equal to this.
    char addChar[5] = {'\0'};
    for (const char32_t codepoint : src)
    {
        if (codepoint < 0x0000'0080)
        {
            addChar[0] = codepoint;
            addChar[1] = '\0';
        }
        else if (codepoint < 0x0000'0800)
        {
            addChar[0] = 0xC0 | ((codepoint >> 6) & 0x1F);
            addChar[1] = 0x80 | (codepoint & 0x3F);
            addChar[2] = '\0';
        }
        else if (codepoint < 0x0001'0000)
        {
            addChar[0] = 0xE0 | ((codepoint >> 12) & 0x0F);
            addChar[1] = 0x80 | ((codepoint >> 6) & 0x3F);
            addChar[2] = 0x80 | (codepoint & 0x3F);
            addChar[3] = '\0';
        }
        // Current maximum codepoint is defined to be U+10FFFF
        else if (codepoint < 0x0011'0000)
        {
            addChar[0] = 0xF0 | ((codepoint >> 18) & 0x07);
            addChar[1] = 0x80 | ((codepoint >> 12) & 0x3F);
            addChar[2] = 0x80 | ((codepoint >> 6) & 0x3F);
            addChar[3] = 0x80 | (codepoint & 0x3F);
            addChar[4] = '\0';
        }
        else
        {
            addChar[0] = 0xE0 | ((0xFFFD >> 12) & 0x1F);
            addChar[1] = 0x80 | ((0xFFFD >> 6) & 0x3F);
            addChar[2] = 0x80 | (0xFFFD & 0x3F);
            addChar[3] = '\0';
        }

        ret.append(addChar);
    }
    return ret;
}

std::u16string StringUtils::UTF32toUTF16(const std::u32string_view& src)
{
    std::u16string ret;
    ret.reserve(src.size());
    for (char32_t codepoint : src)
    {
        if (codepoint <= 0x0000'D7FF || (codepoint >= 0x0000'E000 && codepoint < 0x0001'0000))
        {
            ret.push_back(codepoint);
        }
        // Current maximum codepoint is defined to be U+10FFFF
        else if (codepoint >= 0x0001'0000 && codepoint < 0x0011'0000)
        {
            codepoint -= 0x10000; // Make it fit in 20 bits
            ret.push_back(0xD800 | ((codepoint >> 10) & 0x03FF));
            ret.push_back(0xDC00 | (codepoint & 0x03FF));
        }
        else
        {
            ret.push_back(0xFFFD);
        }
    }
    return ret;
}

std::u16string StringUtils::UTF32toUCS2(const std::u32string_view& src)
{
    std::u16string ret;
    for (const char32_t& codepoint : src)
    {
        if (codepoint <= 0x0000'D7FF || (codepoint >= 0x0000'E000 && codepoint < 0x0001'0000))
        {
            ret.push_back(codepoint);
        }
        else
        {
            ret.push_back(0xFFFD);
        }
    }
    return ret;
}

std::u32string StringUtils::getU32String(const u8* data, int ofs, int len, char16_t term)
{
    std::u32string ret;
    ret.reserve(len);
    for (int i = 0; i < len; i++)
    {
        char32_t chr = LittleEndian::convertTo<char16_t>(data + ofs + i * 2);
        if (chr == term)
        {
            return ret;
        }
        ret.push_back(chr);
    }
    return ret;
}

std::u16string StringUtils::getUCS2String(const u8* data, int ofs, int len, char16_t term)
{
    std::u16string ret;
    ret.reserve(len);
    for (int i = 0; i < len; i++)
    {
        char16_t chr = LittleEndian::convertTo<char16_t>(data + ofs + i * 2);
        if (chr == term)
        {
            return ret;
        }
        ret.push_back(chr);
    }
    return ret;
}

std::string StringUtils::getString(const u8* data, int ofs, int len, char16_t term)
{
    std::string ret;
    ret.reserve(len);
    char addChar[4] = {'\0'};
    for (int i = 0; i < len; i++)
    {
        char16_t codeunit = LittleEndian::convertTo<char16_t>(data + ofs + i * 2);
        if (codeunit == term)
        {
            return ret;
        }
        else if (codeunit < 0x0080)
        {
            addChar[0] = codeunit;
            addChar[1] = '\0';
        }
        else if (codeunit < 0x0800)
        {
            addChar[0] = 0xC0 | ((codeunit >> 6) & 0x1F);
            addChar[1] = 0x80 | (codeunit & 0x3F);
            addChar[2] = '\0';
        }
        else if (codeunit <= 0xD7FF || codeunit >= 0xE000)
        {
            addChar[0] = 0xE0 | ((codeunit >> 12) & 0x0F);
            addChar[1] = 0x80 | ((codeunit >> 6) & 0x3F);
            addChar[2] = 0x80 | (codeunit & 0x3F);
            addChar[3] = '\0';
        }
        else
        {
            addChar[0] = 0xE0 | ((0xFFFD >> 12) & 0x0F);
            addChar[1] = 0x80 | ((0xFFFD >> 6) & 0x3F);
            addChar[2] = 0x80 | (0xFFFD & 0x3F);
            addChar[3] = '\0';
        }
        ret.append(addChar);
    }
    return ret;
}

void StringUtils::setString(
    u8* data, const std::u32string_view& v, int ofs, int len, char16_t terminator, char16_t padding)
{
    int i = 0;
    for (; i < std::min(len - 1, (int)v.size()); i++)
    {
        if (v[i] <= 0x0000'FFFF)
        {
            LittleEndian::convertFrom<char16_t>(data + ofs + i * 2, v[i]);
        }
        else
        {
            LittleEndian::convertFrom<char16_t>(data + ofs + i * 2, 0xFFFD);
        }
    }
    LittleEndian::convertFrom<char16_t>(data + ofs + i++ * 2, terminator); // Set terminator
    for (; i < len; i++)
    {
        LittleEndian::convertFrom<char16_t>(data + ofs + i * 2, padding); // Set final padding bytes
    }
}

void StringUtils::setString(
    u8* data, const std::u16string_view& v, int ofs, int len, char16_t terminator, char16_t padding)
{
    int i    = 0;
    int iMod = 0;
    for (; i < std::min(len - 1, (int)v.size()); i++) // len includes terminator
    {
        if (v[i] <= 0xD7FF || v[i] >= 0xE000)
        {
            LittleEndian::convertFrom<char16_t>(data + ofs + (i + iMod) * 2, v[i]);
        }
        else if (((v[i] & 0xFC00) == 0xD800) && (size_t)i + 1 < v.size() &&
                 ((v[i + 1] & 0xFC00) == 0xDC00))
        {
            LittleEndian::convertFrom<char16_t>(data + ofs + (i + iMod) * 2, 0xFFFD);
            i += 1;
            iMod -= 1;
        }
        else
        {
            LittleEndian::convertFrom<char16_t>(data + ofs + (i + iMod) * 2, 0xFFFD);
        }
    }
    i += iMod;
    LittleEndian::convertFrom<char16_t>(data + ofs + i++ * 2, terminator); // Set terminator
    for (; i < len; i++)
    {
        LittleEndian::convertFrom<char16_t>(data + ofs + i * 2, padding); // Set final padding bytes
    }
}

void StringUtils::setString(
    u8* data, const std::string_view& v, int ofs, int len, char16_t terminator, char16_t padding)
{
    int outOfs = 0;
    for (size_t i = 0; i < v.size() && outOfs < len - 1; i++)
    {
        char16_t out = 0xFFFD;
        int iMod     = 0;
        if (v[i] & 0x80 && v[i] & 0x40 && v[i] & 0x20 && !(v[i] & 0x10) && i + 2 < v.size() &&
            v[i + 1] & 0x80 && !(v[i + 1] & 0x40) && v[i + 2] & 0x80 && !(v[i + 2] & 0x40))
        {
            out  = v[i] & 0x0F;
            out  = out << 6 | (v[i + 1] & 0x3F);
            out  = out << 6 | (v[i + 2] & 0x3F);
            iMod = 2;
        }
        else if (v[i] & 0x80 && v[i] & 0x40 && !(v[i] & 0x20) && i + 1 < v.size() &&
                 v[i + 1] & 0x80 && !(v[i + 1] & 0x40))
        {
            out  = v[i] & 0x1F;
            out  = out << 6 | (v[i + 1] & 0x3F);
            iMod = 1;
        }
        else if (!(v[i] & 0x80))
        {
            out = v[i];
        }

        LittleEndian::convertFrom<char16_t>(data + ofs + (outOfs++ * 2), out);

        i += iMod; // Skip continuation bytes
    }
    LittleEndian::convertFrom<char16_t>(data + ofs + (outOfs++ * 2), terminator); // Set terminator
    for (; outOfs < len; outOfs++)
    {
        LittleEndian::convertFrom<char16_t>(data + ofs + (outOfs * 2),
            padding); // Set final padding bytes
    }
}

std::string StringUtils::getString4(const u8* data, int ofs, int len)
{
    std::string output;
    len *= 2;
    char addChar[4];
    for (u8 i = 0; i < len; i += 2)
    {
        u16 temp = LittleEndian::convertTo<u16>(data + ofs + i);
        if (temp == 0xFFFF)
            break;
        auto found =
            std::find(pksm::internal::G4Values.begin(), pksm::internal::G4Values.end(), temp);
        // Treat an invalid value as a terminator
        if (found == pksm::internal::G4Values.end())
        {
            break;
        }
        u16 codepoint =
            pksm::internal::G4Chars[std::distance(pksm::internal::G4Values.begin(), found)];
        if (codepoint == 0xFFFF)
            break;
        if (codepoint < 0x0080)
        {
            addChar[0] = codepoint;
            addChar[1] = '\0';
        }
        else if (codepoint < 0x0800)
        {
            addChar[0] = 0xC0 | ((codepoint >> 6) & 0x1F);
            addChar[1] = 0x80 | (codepoint & 0x3F);
            addChar[2] = '\0';
        }
        else
        {
            addChar[0] = 0xE0 | ((codepoint >> 12) & 0x0F);
            addChar[1] = 0x80 | ((codepoint >> 6) & 0x3F);
            addChar[2] = 0x80 | (codepoint & 0x3F);
            addChar[3] = '\0';
        }
        output.append(addChar);
    }
    return output;
}

std::vector<u16> StringUtils::stringToG4(const std::string_view& v)
{
    std::vector<u16> ret;
    for (size_t charIndex = 0; charIndex < v.length(); charIndex++)
    {
        if (v[charIndex] & 0x80)
        {
            u16 codepoint = 0;
            if (v[charIndex] & 0x80 && v[charIndex] & 0x40 && v[charIndex] & 0x20)
            {
                codepoint = v[charIndex] & 0x0F;
                codepoint = codepoint << 6 | (v[charIndex + 1] & 0x3F);
                codepoint = codepoint << 6 | (v[charIndex + 2] & 0x3F);
                charIndex += 2;
            }
            else if (v[charIndex] & 0x80 && v[charIndex] & 0x40)
            {
                codepoint = v[charIndex] & 0x1F;
                codepoint = codepoint << 6 | (v[charIndex + 1] & 0x3F);
                charIndex += 1;
            }
            auto found = std::find(
                pksm::internal::G4Chars.begin(), pksm::internal::G4Chars.end(), codepoint);
            ret.push_back(found != pksm::internal::G4Chars.end()
                              ? pksm::internal::G4Values[std::distance(
                                    pksm::internal::G4Chars.begin(), found)]
                              : 0x0000);
        }
        else
        {
            auto found = std::find(
                pksm::internal::G4Chars.begin(), pksm::internal::G4Chars.end(), v[charIndex]);
            ret.push_back(found != pksm::internal::G4Chars.end()
                              ? pksm::internal::G4Values[std::distance(
                                    pksm::internal::G4Chars.begin(), found)]
                              : 0x0000);
        }
    }
    if (ret.back() != 0xFFFF)
    {
        ret.push_back(0xFFFF);
    }
    return ret;
}

void StringUtils::setString4(u8* data, const std::string_view& v, int ofs, int len)
{
    u16 output[len] = {0};
    u16 outIndex = 0, charIndex = 0;
    for (; outIndex < len && charIndex < v.length(); charIndex++, outIndex++)
    {
        if (v[charIndex] & 0x80)
        {
            u16 codepoint = 0;
            if (v[charIndex] & 0x80 && v[charIndex] & 0x40 && v[charIndex] & 0x20)
            {
                codepoint = v[charIndex] & 0x0F;
                codepoint = codepoint << 6 | (v[charIndex + 1] & 0x3F);
                codepoint = codepoint << 6 | (v[charIndex + 2] & 0x3F);
                charIndex += 2;
            }
            else if (v[charIndex] & 0x80 && v[charIndex] & 0x40)
            {
                codepoint = v[charIndex] & 0x1F;
                codepoint = codepoint << 6 | (v[charIndex + 1] & 0x3F);
                charIndex += 1;
            }
            auto found = std::find(
                pksm::internal::G4Chars.begin(), pksm::internal::G4Chars.end(), codepoint);
            output[outIndex] = found != pksm::internal::G4Chars.end()
                                   ? pksm::internal::G4Values[std::distance(
                                         pksm::internal::G4Chars.begin(), found)]
                                   : 0x0000;
        }
        else
        {
            auto found = std::find(
                pksm::internal::G4Chars.begin(), pksm::internal::G4Chars.end(), v[charIndex]);
            output[outIndex] = found != pksm::internal::G4Chars.end()
                                   ? pksm::internal::G4Values[std::distance(
                                         pksm::internal::G4Chars.begin(), found)]
                                   : 0x0000;
        }
    }
    output[outIndex >= len ? len - 1 : outIndex] = 0xFFFF;
    memcpy(data + ofs, output, len * 2);
}

std::string& StringUtils::toUpper(std::string& in)
{
    std::transform(in.begin(), in.end(), in.begin(), ::toupper);
    // Just saying, I have NO clue why two outer braces levels are necessary
    static constexpr std::array<std::pair<std::string_view, std::string_view>, 12> transStrings = {
        {{"í", "Í"}, {"ó", "Ó"}, {"ú", "Ú"}, {"é", "É"}, {"á", "Á"}, {"ì", "Ì"}, {"ò", "Ò"},
            {"ù", "Ù"}, {"è", "È"}, {"à", "À"}, {"ñ", "Ñ"}, {"æ", "Æ"}}};
    for (const auto& str : transStrings)
    {
        size_t found;
        while ((found = in.find(str.first)) != std::string::npos)
        {
            in.replace(found, str.first.size(), str.second);
        }
    }
    return in;
}

std::string StringUtils::toUpper(const std::string_view& in)
{
    std::string ret = std::string(in);
    return toUpper(ret);
}

std::string& StringUtils::toLower(std::string& in)
{
    std::transform(in.begin(), in.end(), in.begin(), ::tolower);
    // Just saying, I have NO clue why two outer braces levels are necessary
    static constexpr std::array<std::pair<std::string_view, std::string_view>, 12> transStrings = {
        {{"Í", "í"}, {"Ó", "ó"}, {"Ú", "ú"}, {"É", "é"}, {"Á", "á"}, {"Ì", "ì"}, {"Ò", "ò"},
            {"Ù", "ù"}, {"È", "è"}, {"À", "à"}, {"Ñ", "ñ"}, {"Æ", "æ"}}};
    for (const auto& str : transStrings)
    {
        size_t found;
        while ((found = in.find(str.first)) != std::string::npos)
        {
            in.replace(found, str.first.size(), str.second);
        }
    }
    return in;
}

std::string StringUtils::toLower(const std::string_view& in)
{
    std::string ret = std::string(in);
    return toLower(ret);
}

std::u16string& StringUtils::toFullWidth(std::u16string& in)
{
    std::transform(in.begin(), in.end(), in.begin(), tofullwidth);
    return in;
}

std::string StringUtils::transString45(const std::string_view& str)
{
    return UTF16toUTF8(transString45(UTF8toUTF16(str)));
}

std::u16string StringUtils::transString45(const std::u16string_view& str)
{
    std::u16string ret = std::u16string(str);
    std::transform(str.begin(), str.end(), ret.begin(),
        [](const char16_t& chr) { return (char16_t)swapCodepoints45(chr); });
    return ret;
}

std::string StringUtils::transString67(const std::string_view& str)
{
    return UTF16toUTF8(transString67(UTF8toUTF16(str)));
}

std::u16string StringUtils::transString67(const std::u16string_view& str)
{
    std::u16string ret = std::u16string(str);
    std::transform(str.begin(), str.end(), ret.begin(),
        [](const char16_t& chr) { return (char16_t)swapCodepoints67(chr); });
    return ret;
}

std::string StringUtils::getString3(const u8* data, int ofs, int len, bool jp)
{
    auto& characters = jp ? pksm::internal::G3_JP : pksm::internal::G3_EN;
    std::u16string outString;

    for (size_t i = 0; i < (size_t)len; i++)
    {
        if (data[ofs + i] < characters.size())
        {
            outString += characters[data[ofs + i]];
        }
        else
        {
            break;
        }
    }

    return StringUtils::UTF16toUTF8(outString);
}

void StringUtils::setString3(
    u8* data, const std::string_view& v, int ofs, int len, bool jp, int padTo, u8 padWith)
{
    auto& characters   = jp ? pksm::internal::G3_JP : pksm::internal::G3_EN;
    std::u16string str = StringUtils::UTF8toUTF16(v);
    if (jp)
        str = StringUtils::toFullWidth(str);

    size_t outPos;
    for (outPos = 0; outPos < std::min((size_t)len, str.size()); outPos++)
    {
        auto it = std::find(characters.begin(), characters.end(), str[outPos]);
        if (it != characters.end())
        {
            data[ofs + outPos] = (u8)std::distance(characters.begin(), it);
        }
        else
        {
            break;
        }
    }

    if (outPos < (size_t)len)
    {
        data[ofs + outPos] = 0xFF;
    }

    while (outPos < (size_t)padTo)
    {
        data[ofs + outPos] = padWith;
        outPos++;
    }
}
