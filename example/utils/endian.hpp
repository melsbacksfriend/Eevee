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

#ifndef ENDIAN_HPP
#define ENDIAN_HPP

#if __cplusplus > 201703L
#include "../../source/utils/cpp20endian.hpp"
#else

#include "utils/coretypes.h"
#include <array>
#include <cmath>
#include <string.h>
#include <type_traits>
#include <vector>

namespace pksm::internal
{
#if (defined(__BYTE_ORDER) && __BYTE_ORDER == __BIG_ENDIAN) ||                                     \
    (defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__) ||                         \
    defined(__BIG_ENDIAN__) || defined(__ARMEB__) || defined(__THUMBEB__) ||                       \
    defined(__AARCH64EB__) || defined(_MIBSEB) || defined(__MIBSEB) || defined(__MIBSEB__)
    constexpr bool ENDIAN_bigEndian    = true;
    constexpr bool ENDIAN_littleEndian = false;
#elif (defined(__BYTE_ORDER) && __BYTE_ORDER == __LITTLE_ENDIAN) ||                                \
    (defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__) ||                      \
    defined(__LITTLE_ENDIAN__) || defined(__ARMEL__) || defined(__THUMBEL__) ||                    \
    defined(__AARCH64EL__) || defined(_MIPSEL) || defined(__MIPSEL) || defined(__MIPSEL__)
    constexpr bool ENDIAN_bigEndian    = false;
    constexpr bool ENDIAN_littleEndian = true;
#else
    constexpr bool ENDIAN_bigEndian    = false;
    constexpr bool ENDIAN_littleEndian = false;
#endif
    constexpr bool ENDIAN_easyArch     = ENDIAN_bigEndian || ENDIAN_littleEndian;
}

namespace BigEndian
{
    // Endianness checking found in
    // https://stackoverflow.com/questions/4239993/determining-endianness-at-compile-time Converts
    // arithmetic types into big-endian byte representations. Integer types and IEEE 754 compliant
    // single and double-precision floating-point types are supported.
    template <typename T>
    void convertFrom(u8* dest, const T& orig)
    {
        static_assert(
            (std::is_same_v<T, float> && sizeof(float) == 4 && std::numeric_limits<T>::is_iec559) ||
            (std::is_same_v<T, double> && sizeof(double) == 8 &&
                std::numeric_limits<T>::is_iec559) ||
            std::is_integral_v<T>);

        if constexpr (pksm::internal::ENDIAN_easyArch)
        {
            memcpy(dest, &orig, sizeof(T));
            if constexpr (pksm::internal::ENDIAN_littleEndian)
            {
                for (size_t i = 0; i < sizeof(T) / 2; i++)
                {
                    std::swap(dest[i], dest[sizeof(T) - i - 1]);
                }
            }
        }
        else if constexpr (std::is_integral_v<T>)
        {
            std::make_unsigned_t<T> origVal = orig;
            for (size_t i = 0; i < sizeof(T); i++)
            {
                dest[sizeof(T) - i - 1] = u8(origVal);
                origVal >>= 8;
            }
        }
        else
        {
            bool negative = std::signbit(orig);
            int exponent;
            T normalized =
                std::frexp(orig, &exponent); // gets biased exponent, which isn't what I want
            if constexpr (std::is_same_v<T, float>)
            {
                u32 write = negative ? (1u << 31) : 0;
                switch (std::fpclassify(orig))
                {
                    case FP_INFINITE:
                        write |= u32(0xFF) << 23; // should be written as 0x7F800000 or 0xFF800000
                        break;
                    case FP_NAN:
                        write = 0xFFFFFFFF; // might as well just use a constant NaN number
                        break;
                    case FP_ZERO:
                        // do nothing; it should be written as either 0x80000000 or 0x00000000
                        break;
                    case FP_NORMAL:
                        write |= u32(exponent + 127) << 23;
                        // falls through
                    case FP_SUBNORMAL:
                        normalized *= 1u << 23;
                        write |= u32(normalized);
                        break;
                }
                convertFrom<u32>(dest, write);
            }
            else if constexpr (std::is_same_v<T, double>)
            {
                u64 write = negative ? (u64(1) << 63) : 0;
                switch (std::fpclassify(orig))
                {
                    case FP_INFINITE:
                        write |=
                            u64(0x7FF)
                            << 52; // should be written as 0x7FF0000000000000 or 0xFFF0000000000000
                        break;
                    case FP_NAN:
                        write = 0xFFFFFFFFFFFFFFFF; // might as well just use a constant NaN number
                        break;
                    case FP_ZERO:
                        // do nothing; it should be written as either 0x8000000000000000 or
                        // 0x0000000000000000
                        break;
                    case FP_NORMAL:
                        write |= u64(exponent + 1023) << 52;
                        // falls through
                    case FP_SUBNORMAL:
                        normalized *= u64(1) << 52;
                        write |= u64(normalized);
                        break;
                }
                convertFrom<u64>(dest, write);
            }
        }
    }

    // Array-based implementation
    template <typename T, size_t N>
    void convertFrom(u8* dest, const T (&array)[N])
    {
        for (size_t i = 0; i < N; i++)
        {
            convertFrom(dest, array[i]);
            dest += sizeof(T);
        }
    }

    // Another array-based implementation
    template <typename T, size_t N>
    void convertFrom(u8* dest, const std::array<T, N>& array)
    {
        for (size_t i = 0; i < N; i++)
        {
            convertFrom(dest, array[i]);
            dest += sizeof(T);
        }
    }

    // And now... vector
    template <typename T>
    void convertFrom(u8* dest, const std::vector<T>& vector)
    {
        for (size_t i = 0; i < vector.size(); i++)
        {
            convertFrom(dest, vector[i]);
            dest += sizeof(T);
        }
    }

    // Same as above, just with automatic handling of data lifetime
    template <typename T>
    auto convertFrom(const T& orig) -> std::array<u8, sizeof(T)>
    {
        std::array<u8, sizeof(T)> ret;
        convertFrom(ret.data(), orig);
        return ret;
    }

    template <typename T, size_t N>
    auto convertFrom(const T (&array)[N]) -> std::array<u8, sizeof(T) * N>
    {
        std::array<u8, sizeof(T) * N> ret;
        convertFrom(ret.data(), array);
        return ret;
    }

    template <typename T, size_t N>
    auto convertFrom(const std::array<T, N>& array) -> std::array<u8, sizeof(T) * N>
    {
        std::array<u8, sizeof(T) * N> ret;
        convertFrom(ret.data(), array);
        return ret;
    }

    template <typename T>
    std::vector<u8> convertFrom(const std::vector<T>& vector)
    {
        std::vector<u8> ret(vector.size() * sizeof(T));
        convertFrom(ret.data(), vector);
        return ret;
    }

    // Endianness checking found in
    // https://stackoverflow.com/questions/4239993/determining-endianness-at-compile-time Converts
    // big-endian byte representations into arithmetic types. Integer types and IEEE 754 compliant
    // single and double-precision floating-point types are supported.
    template <typename T>
    T convertTo(const u8* from)
    {
        static_assert(
            (std::is_same_v<T, float> && sizeof(float) == 4 && std::numeric_limits<T>::is_iec559) ||
            (std::is_same_v<T, double> && sizeof(double) == 8 &&
                std::numeric_limits<T>::is_iec559) ||
            std::is_integral_v<T>);

        if constexpr (pksm::internal::ENDIAN_easyArch)
        {
            T dest;
            if constexpr (pksm::internal::ENDIAN_littleEndian)
            {
                u8 data[sizeof(T)];
                memcpy(data, from, sizeof(T));
                for (size_t i = 0; i < sizeof(T) / 2; i++)
                {
                    std::swap(data[i], data[sizeof(T) - i - 1]);
                }
                memcpy(&dest, data, sizeof(T));
            }
            else
            {
                memcpy(&dest, from, sizeof(T));
            }
            return dest;
        }
        else if constexpr (std::is_integral_v<T>)
        {
            std::make_unsigned_t<T> dest = 0;
            for (size_t i = 0; i < sizeof(T); i++)
            {
                dest |= std::make_unsigned_t<T>(from[i]) << ((sizeof(T) - i - 1) * 8);
            }
            return dest;
        }
        else if constexpr (std::is_same_v<T, float>)
        {
            u32 data      = convertTo<u32>(from);
            bool negative = (data & 0x80000000) != 0;
            int exponent  = (data & 0x7F800000) >> 23;
            int fraction  = data & ~0xFF800000;
            if (exponent == 0 && fraction == 0)
            {
                return std::copysign(T(0), negative ? -1 : 1);
            }
            else if (exponent == 0xFF)
            {
                if (fraction == 0)
                {
                    return negative ? -std::numeric_limits<T>::infinity()
                                    : std::numeric_limits<T>::infinity();
                }
                else
                {
                    return std::numeric_limits<T>::signaling_NaN(); // Going to ignore the
                                                                    // difference between quiet and
                                                                    // signaling NaN
                }
            }
            else
            {
                // fraction is currently shifted 23 bits from where it should be, so fix that and
                // set the proper exponent
                T ret = std::ldexp(fraction, -23);
                if (exponent == 0) // Denormal number
                {
                    ret = std::ldexp(ret, -126);
                }
                else
                {
                    // Unbias the exponent & add the one necessary because it's not a denormal
                    // number
                    ret = std::ldexp(ret + 1, exponent - 127);
                }
                return std::copysign(ret, negative ? -1 : 1);
            }
        }
        else if constexpr (std::is_same_v<T, double>)
        {
            u64 data      = convertTo<u64>(from);
            bool negative = (data & 0x8000000000000000) != 0;
            int exponent  = (data & 0x7FF0000000000000) >> 52;
            int fraction  = data & ~0xFFF0000000000000;
            if (exponent == 0 && fraction == 0)
            {
                return std::copysign(T(0), negative ? -1 : 1);
            }
            else if (exponent == 0x7FF)
            {
                if (fraction == 0)
                {
                    return negative ? -std::numeric_limits<T>::infinity()
                                    : std::numeric_limits<T>::infinity();
                }
                else
                {
                    return std::numeric_limits<T>::signaling_NaN(); // Going to ignore the
                                                                    // difference between quiet and
                                                                    // signaling NaN
                }
            }
            else
            {
                // fraction is currently shifted 52 bits from where it should be, so fix that and
                // set the proper exponent
                T ret = std::ldexp(fraction, -52);
                if (exponent == 0) // Denormal number
                {
                    ret = std::ldexp(ret, -1022);
                }
                else
                {
                    // Unbias the exponent & add the one necessary because it's not a denormal
                    // number
                    ret = std::ldexp(ret + 1, exponent - 1023);
                }
                return std::copysign(ret, negative ? -1 : 1);
            }
        }
    }

    template <typename T, size_t N>
    std::array<T, N> convertTo(const u8* from)
    {
        std::array<T, N> ret;
        for (size_t i = 0; i < N; i++)
        {
            ret[i] = convertTo<T>(from + i * sizeof(T));
        }
        return ret;
    }
}

namespace LittleEndian
{
    // Endianness checking found in
    // https://stackoverflow.com/questions/4239993/determining-endianness-at-compile-time Converts
    // arithmetic types into little-endian byte representations. Integer types and IEEE 754
    // compliant single and double-precision floating-point types are supported.
    template <typename T>
    void convertFrom(u8* dest, const T& orig)
    {
        static_assert(
            (std::is_same_v<T, float> && sizeof(float) == 4 && std::numeric_limits<T>::is_iec559) ||
            (std::is_same_v<T, double> && sizeof(double) == 8 &&
                std::numeric_limits<T>::is_iec559) ||
            std::is_integral_v<T>);

        if constexpr (pksm::internal::ENDIAN_easyArch)
        {
            memcpy(dest, &orig, sizeof(T));
            if constexpr (pksm::internal::ENDIAN_bigEndian)
            {
                for (size_t i = 0; i < sizeof(T) / 2; i++)
                {
                    std::swap(dest[i], dest[sizeof(T) - i - 1]);
                }
            }
        }
        else if constexpr (std::is_integral_v<T>)
        {
            std::make_unsigned_t<T> origVal = orig;
            for (size_t i = 0; i < sizeof(T); i++)
            {
                dest[i] = u8(origVal);
                origVal >>= 8;
            }
        }
        else
        {
            bool negative = std::signbit(orig);
            int exponent;
            T normalized = std::frexp(orig, &exponent); // gets biased exponent
            if constexpr (std::is_same_v<T, float>)
            {
                u32 write = negative ? (1u << 31) : 0;
                switch (std::fpclassify(orig))
                {
                    case FP_INFINITE:
                        write |= u32(0xFF) << 23; // should be written as 0x7F800000 or 0xFF800000
                        break;
                    case FP_NAN:
                        write = 0xFFFFFFFF; // might as well just use a constant NaN number
                        break;
                    case FP_ZERO:
                        // do nothing; it should be written as either 0x80000000 or 0x00000000
                        break;
                    case FP_NORMAL:
                        write |= u32(exponent + 127) << 23; // Bias the exponent
                        // falls through
                    case FP_SUBNORMAL:
                        normalized *= 1u << 23; // Get the fraction value as an integer
                        write |= u32(normalized);
                        break;
                }
                convertFrom<u32>(dest, write);
            }
            else if constexpr (std::is_same_v<T, double>)
            {
                u64 write = negative ? (u64(1) << 63) : 0;
                switch (std::fpclassify(orig))
                {
                    case FP_INFINITE:
                        write |=
                            u64(0x7FF)
                            << 52; // should be written as 0x7FF0000000000000 or 0xFFF0000000000000
                        break;
                    case FP_NAN:
                        write = 0xFFFFFFFFFFFFFFFF; // might as well just use a constant NaN number
                        break;
                    case FP_ZERO:
                        // do nothing; it should be written as either 0x8000000000000000 or
                        // 0x0000000000000000
                        break;
                    case FP_NORMAL:
                        write |= u64(exponent + 1023) << 52; // Bias the exponent
                        // falls through
                    case FP_SUBNORMAL:
                        normalized *= u64(1) << 52; // Get the fraction value as an integer
                        write |= u64(normalized);
                        break;
                }
                convertFrom<u64>(dest, write);
            }
        }
    }

    // Array-based implementation
    template <typename T, size_t N>
    void convertFrom(u8* dest, const T (&array)[N])
    {
        for (size_t i = 0; i < N; i++)
        {
            convertFrom(dest, array[i]);
            dest += sizeof(T);
        }
    }

    // Another array-based implementation
    template <typename T, size_t N>
    void convertFrom(u8* dest, const std::array<T, N>& array)
    {
        for (size_t i = 0; i < N; i++)
        {
            convertFrom(dest, array[i]);
            dest += sizeof(T);
        }
    }

    // And now... vector
    template <typename T>
    void convertFrom(u8* dest, const std::vector<T>& vector)
    {
        for (size_t i = 0; i < vector.size(); i++)
        {
            convertFrom(dest, vector[i]);
            dest += sizeof(T);
        }
    }

    // Same as above, just with automatic handling of data lifetime
    template <typename T>
    auto convertFrom(const T& orig) -> std::array<u8, sizeof(T)>
    {
        std::array<u8, sizeof(T)> ret;
        convertFrom(ret.data(), orig);
        return ret;
    }

    template <typename T, size_t N>
    auto convertFrom(const T (&array)[N]) -> std::array<u8, sizeof(T) * N>
    {
        std::array<u8, sizeof(T) * N> ret;
        convertFrom(ret.data(), array);
        return ret;
    }

    template <typename T, size_t N>
    auto convertFrom(const std::array<T, N>& array) -> std::array<u8, sizeof(T) * N>
    {
        std::array<u8, sizeof(T) * N> ret;
        convertFrom(ret.data(), array);
        return ret;
    }

    template <typename T>
    std::vector<u8> convertFrom(const std::vector<T>& vector)
    {
        std::vector<u8> ret(vector.size() * sizeof(T));
        convertFrom(ret.data(), vector);
        return ret;
    }

    // Endianness checking found in
    // https://stackoverflow.com/questions/4239993/determining-endianness-at-compile-time Converts
    // little-endian byte representations into arithmetic types. Integer types and IEEE 754
    // compliant single and double-precision floating-point types are supported.
    template <typename T>
    T convertTo(const u8* from)
    {
        static_assert(
            (std::is_same_v<T, float> && sizeof(float) == 4 && std::numeric_limits<T>::is_iec559) ||
            (std::is_same_v<T, double> && sizeof(double) == 8 &&
                std::numeric_limits<T>::is_iec559) ||
            std::is_integral_v<T>);

        if constexpr (pksm::internal::ENDIAN_easyArch)
        {
            T dest;
            if constexpr (pksm::internal::ENDIAN_bigEndian)
            {
                u8 data[sizeof(T)];
                memcpy(data, from, sizeof(T));
                for (size_t i = 0; i < sizeof(T) / 2; i++)
                {
                    std::swap(data[i], data[sizeof(T) - i - 1]);
                }
                memcpy(&dest, data, sizeof(T));
            }
            else
            {
                memcpy(&dest, from, sizeof(T));
            }
            return dest;
        }
        else if constexpr (std::is_integral_v<T>)
        {
            std::make_unsigned_t<T> dest = 0;
            for (size_t i = 0; i < sizeof(T); i++)
            {
                dest |= std::make_unsigned_t<T>(from[i]) << (i * 8);
            }
            return dest;
        }
        else if constexpr (std::is_same_v<T, float>)
        {
            u32 data      = convertTo<u32>(from);
            bool negative = (data & 0x80000000) != 0;
            int exponent  = (data & 0x7F800000) >> 23;
            int fraction  = data & ~0xFF800000;
            if (exponent == 0 && fraction == 0)
            {
                return std::copysign(T(0), negative ? -1 : 1);
            }
            else if (exponent == 0xFF)
            {
                if (fraction == 0)
                {
                    return negative ? -std::numeric_limits<T>::infinity()
                                    : std::numeric_limits<T>::infinity();
                }
                else
                {
                    return std::numeric_limits<T>::signaling_NaN(); // Going to ignore the
                                                                    // difference between quiet and
                                                                    // signaling NaN
                }
            }
            else
            {
                // fraction is currently shifted 23 bits from where it should be, so fix that and
                // set the proper exponent
                T ret = std::ldexp(fraction, -23);
                if (exponent == 0) // Denormal number
                {
                    ret = std::ldexp(ret, -126);
                }
                else
                {
                    // Unbias the exponent & add the one necessary because it's not a denormal
                    // number
                    ret = std::ldexp(ret + 1, exponent - 127);
                }
                return std::copysign(ret, negative ? -1 : 1);
            }
        }
        else if constexpr (std::is_same_v<T, double>)
        {
            u64 data      = convertTo<u64>(from);
            bool negative = (data & 0x8000000000000000) != 0;
            int exponent  = (data & 0x7FF0000000000000) >> 52;
            int fraction  = data & ~0xFFF0000000000000;
            if (exponent == 0 && fraction == 0)
            {
                return std::copysign(T(0), negative ? -1 : 1);
            }
            else if (exponent == 0x7FF)
            {
                if (fraction == 0)
                {
                    return negative ? -std::numeric_limits<T>::infinity()
                                    : std::numeric_limits<T>::infinity();
                }
                else
                {
                    return std::numeric_limits<T>::signaling_NaN(); // Going to ignore the
                                                                    // difference between quiet and
                                                                    // signaling NaN
                }
            }
            else
            {
                // fraction is currently shifted 52 bits from where it should be, so fix that and
                // set the proper exponent
                T ret = std::ldexp(fraction, -52);
                if (exponent == 0) // Denormal number
                {
                    ret = std::ldexp(ret, -1022);
                }
                else
                {
                    // Unbias the exponent & add the one necessary because it's not a denormal
                    // number
                    ret = std::ldexp(ret + 1, exponent - 1023);
                }
                return std::copysign(ret, negative ? -1 : 1);
            }
        }
    }

    template <typename T, size_t N>
    std::array<T, N> convertTo(const u8* from)
    {
        std::array<T, N> ret;
        for (size_t i = 0; i < N; i++)
        {
            ret[i] = convertTo<T>(from + i * sizeof(T));
        }
        return ret;
    }
}

#endif

#endif
