/*
 *   This file is part of PKSM-Core
 *   Copyright (C) 2016-2020 Bernardo Giordano, Admiral Fish, piepie62, Pk11
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

#ifndef GENDER_HPP
#define GENDER_HPP

#include "utils/coretypes.h"
#include <limits>
#include <type_traits>

namespace pksm
{
    class Gender;
    namespace internal
    {
        class Gender_impl
        {
            friend class pksm::Gender;

        private:
            enum class GenderEnum : u8
            {
                Male       = 0,
                Female     = 1,
                Genderless = 2,

                INVALID [[maybe_unused]] =
                    std::numeric_limits<std::underlying_type_t<GenderEnum>>::max()
            } v;

            constexpr explicit Gender_impl(GenderEnum v) : v(v) {}
            constexpr Gender_impl(const Gender_impl&) = default;
            constexpr Gender_impl(Gender_impl&&)      = default;
            constexpr Gender_impl& operator=(const Gender_impl&) = default;
            constexpr Gender_impl& operator=(Gender_impl&&) = default;

        public:
            template <typename T>
            constexpr explicit operator T() const noexcept
            {
                static_assert(std::is_integral_v<T>);
                return T(v);
            }
            constexpr operator GenderEnum() const noexcept { return v; }

            constexpr bool operator<(const Gender_impl& other) const noexcept
            {
                return v < other.v;
            }
            constexpr bool operator<=(const Gender_impl& other) const noexcept
            {
                return v <= other.v;
            }

            constexpr bool operator>(const Gender_impl& other) const noexcept
            {
                return v > other.v;
            }
            constexpr bool operator>=(const Gender_impl& other) const noexcept
            {
                return v >= other.v;
            }

            constexpr bool operator==(const Gender_impl& other) const noexcept
            {
                return v == other.v;
            }
            constexpr bool operator!=(const Gender_impl& other) const noexcept
            {
                return v != other.v;
            }
        };
    }

    class Gender
    {
    private:
        internal::Gender_impl impl;

    public:
        using EnumType = internal::Gender_impl::GenderEnum;
        constexpr Gender() noexcept : impl(EnumType::INVALID) {}
        constexpr Gender(const internal::Gender_impl& impl) noexcept : impl(impl) {}
        constexpr explicit Gender(std::underlying_type_t<EnumType> v) noexcept : impl(EnumType{v})
        {
        }
        template <typename T>
        constexpr explicit operator T() const noexcept
        {
            static_assert(std::is_integral_v<T>);
            return T(impl);
        }
        constexpr operator EnumType() const noexcept { return static_cast<EnumType>(impl); }

        constexpr bool operator<(const Gender& other) const noexcept { return impl < other.impl; }
        constexpr bool operator<=(const Gender& other) const noexcept { return impl <= other.impl; }

        constexpr bool operator>(const Gender& other) const noexcept { return impl > other.impl; }
        constexpr bool operator>=(const Gender& other) const noexcept { return impl >= other.impl; }

        constexpr bool operator==(const Gender& other) const noexcept { return impl == other.impl; }
        constexpr bool operator!=(const Gender& other) const noexcept { return impl != other.impl; }

        constexpr bool operator<(const internal::Gender_impl& other) const noexcept
        {
            return impl < other;
        }
        constexpr bool operator<=(const internal::Gender_impl& other) const noexcept
        {
            return impl <= other;
        }

        constexpr bool operator>(const internal::Gender_impl& other) const noexcept
        {
            return impl > other;
        }
        constexpr bool operator>=(const internal::Gender_impl& other) const noexcept
        {
            return impl >= other;
        }

        constexpr bool operator==(const internal::Gender_impl& other) const noexcept
        {
            return impl == other;
        }
        constexpr bool operator!=(const internal::Gender_impl& other) const noexcept
        {
            return impl != other;
        }

        static constexpr internal::Gender_impl Male{EnumType::Male};
        static constexpr internal::Gender_impl Female{EnumType::Female};
        static constexpr internal::Gender_impl Genderless{EnumType::Genderless};

        static constexpr internal::Gender_impl INVALID{EnumType::INVALID};
    };
}

#endif
