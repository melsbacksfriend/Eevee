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

#ifndef GENERATION_HPP
#define GENERATION_HPP

#include "utils/coretypes.h"
#include <string>
#include <type_traits>

namespace pksm
{
    class Generation;
    namespace internal
    {
        class Generation_impl
        {
            friend class pksm::Generation;

        private:
            // values MUST remain consistent
            // ONE and TWO to have maybe_unused removed in the future
            enum class GenerationEnum : u32
            {
                ONE [[maybe_unused]] = 7,
                TWO [[maybe_unused]] = 8,
                THREE                = 6,
                FOUR                 = 0,
                FIVE                 = 1,
                SIX                  = 2,
                SEVEN                = 3,
                LGPE                 = 4,
                EIGHT                = 5,

                UNUSED [[maybe_unused]] = 0xFFFFFFFF
            } v;

            constexpr explicit Generation_impl(GenerationEnum v) : v(v) {}
            constexpr Generation_impl(const Generation_impl&) = default;
            constexpr Generation_impl(Generation_impl&&)      = default;
            constexpr Generation_impl& operator=(const Generation_impl&) = default;
            constexpr Generation_impl& operator=(Generation_impl&&) = default;

        public:
            template <typename T>
            constexpr explicit operator T() const noexcept
            {
                static_assert(std::is_integral_v<T>);
                return T(v);
            }
            constexpr explicit operator const char*() const noexcept
            {
                switch (v)
                {
                    case GenerationEnum::LGPE:
                        return "LGPE";
                    case GenerationEnum::ONE:
                        return "1";
                    case GenerationEnum::TWO:
                        return "2";
                    case GenerationEnum::THREE:
                        return "3";
                    case GenerationEnum::FOUR:
                        return "4";
                    case GenerationEnum::FIVE:
                        return "5";
                    case GenerationEnum::SIX:
                        return "6";
                    case GenerationEnum::SEVEN:
                        return "7";
                    case GenerationEnum::EIGHT:
                        return "8";
                    case GenerationEnum::UNUSED:
                        return "INVALID";
                }
                return "INVALID";
            }
            constexpr explicit operator std::string_view() const
            {
                return std::string_view{static_cast<const char*>(*this)};
            }
            explicit operator std::string() const
            {
                return std::string{static_cast<const char*>(*this)};
            }
            constexpr operator GenerationEnum() const noexcept { return v; }

            constexpr bool operator<(const Generation_impl& other) const noexcept
            {
                switch (v)
                {
                    case GenerationEnum::ONE:
                        if (other.v == GenerationEnum::TWO)
                        {
                            return true;
                        }
                        // falls through
                    case GenerationEnum::TWO:
                        if (other.v == GenerationEnum::THREE)
                        {
                            return true;
                        }
                        // falls through
                    case GenerationEnum::THREE:
                        if (other.v == GenerationEnum::FOUR)
                        {
                            return true;
                        }
                        // falls through
                    case GenerationEnum::FOUR:
                        if (other.v == GenerationEnum::FIVE)
                        {
                            return true;
                        }
                        // falls through
                    case GenerationEnum::FIVE:
                        if (other.v == GenerationEnum::SIX)
                        {
                            return true;
                        }
                        // falls through
                    case GenerationEnum::SIX:
                        if (other.v == GenerationEnum::SEVEN)
                        {
                            return true;
                        }
                        // falls through
                    case GenerationEnum::SEVEN:
                        if (other.v == GenerationEnum::LGPE)
                        {
                            return true;
                        }
                        // falls through
                    case GenerationEnum::LGPE:
                        if (other.v == GenerationEnum::EIGHT)
                        {
                            return true;
                        }
                        // falls through
                    case GenerationEnum::EIGHT:
                        if (other.v == GenerationEnum::UNUSED)
                        {
                            return true;
                        }
                        // falls through
                    case GenerationEnum::UNUSED:
                    default:
                        return false;
                }
            }
            constexpr bool operator>(const Generation_impl& other) const noexcept
            {
                if (*this == other)
                {
                    return false;
                }
                return !(*this < other);
            }

            constexpr bool operator<=(const Generation_impl& other) const noexcept
            {
                return *this < other || *this == other;
            }
            constexpr bool operator>=(const Generation_impl& other) const noexcept
            {
                return *this > other || *this == other;
            }

            constexpr bool operator==(const Generation_impl& other) const noexcept
            {
                return v == other.v;
            }
            constexpr bool operator!=(const Generation_impl& other) const noexcept
            {
                return v != other.v;
            }
        };
    }

    class Generation
    {
    private:
        internal::Generation_impl impl;

    public:
        using EnumType = internal::Generation_impl::GenerationEnum;
        constexpr Generation() noexcept : impl(EnumType::UNUSED) {}
        constexpr Generation(const internal::Generation_impl& impl) noexcept : impl(impl) {}
        constexpr explicit Generation(std::underlying_type_t<EnumType> v) noexcept
            : impl(EnumType{v})
        {
        }
        template <typename T>
        constexpr explicit operator T() const noexcept
        {
            return T(impl);
        }
        constexpr operator EnumType() const noexcept { return static_cast<EnumType>(impl); }

        constexpr explicit operator const char*() const noexcept
        {
            return static_cast<const char*>(impl);
        }
        constexpr explicit operator std::string_view() const
        {
            return static_cast<std::string_view>(impl);
        }
        explicit operator std::string() const { return static_cast<std::string>(impl); }

        static constexpr Generation fromString(const std::string_view& str)
        {
            if (str == "3")
            {
                return Generation::THREE;
            }
            else if (str == "4")
            {
                return Generation::FOUR;
            }
            else if (str == "5")
            {
                return Generation::FIVE;
            }
            else if (str == "6")
            {
                return Generation::SIX;
            }
            else if (str == "7")
            {
                return Generation::SEVEN;
            }
            else if (str == "LGPE")
            {
                return Generation::LGPE;
            }
            else if (str == "8")
            {
                return Generation::EIGHT;
            }
            return Generation::UNUSED;
        }

        constexpr bool operator<(const Generation& other) const noexcept
        {
            return impl < other.impl;
        }
        constexpr bool operator<=(const Generation& other) const noexcept
        {
            return impl <= other.impl;
        }

        constexpr bool operator>(const Generation& other) const noexcept
        {
            return impl > other.impl;
        }
        constexpr bool operator>=(const Generation& other) const noexcept
        {
            return impl >= other.impl;
        }

        constexpr bool operator==(const Generation& other) const noexcept
        {
            return impl == other.impl;
        }
        constexpr bool operator!=(const Generation& other) const noexcept
        {
            return impl != other.impl;
        }

        constexpr bool operator<(const internal::Generation_impl& other) const noexcept
        {
            return impl < other;
        }
        constexpr bool operator<=(const internal::Generation_impl& other) const noexcept
        {
            return impl <= other;
        }

        constexpr bool operator>(const internal::Generation_impl& other) const noexcept
        {
            return impl > other;
        }
        constexpr bool operator>=(const internal::Generation_impl& other) const noexcept
        {
            return impl >= other;
        }

        constexpr bool operator==(const internal::Generation_impl& other) const noexcept
        {
            return impl == other;
        }
        constexpr bool operator!=(const internal::Generation_impl& other) const noexcept
        {
            return impl != other;
        }

        static constexpr internal::Generation_impl ONE{EnumType::ONE};
        static constexpr internal::Generation_impl TWO{EnumType::TWO};
        static constexpr internal::Generation_impl THREE{EnumType::THREE};
        static constexpr internal::Generation_impl FOUR{EnumType::FOUR};
        static constexpr internal::Generation_impl FIVE{EnumType::FIVE};
        static constexpr internal::Generation_impl SIX{EnumType::SIX};
        static constexpr internal::Generation_impl SEVEN{EnumType::SEVEN};
        static constexpr internal::Generation_impl LGPE{EnumType::LGPE};
        static constexpr internal::Generation_impl EIGHT{EnumType::EIGHT};
        static constexpr internal::Generation_impl UNUSED{EnumType::UNUSED};
    };
}

#endif
