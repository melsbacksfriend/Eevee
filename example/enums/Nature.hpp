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

#ifndef NATURE_HPP
#define NATURE_HPP

#include "enums/Language.hpp"
#include "utils/coretypes.h"
#include <limits>
#include <type_traits>

namespace pksm
{
    class Nature;
    namespace internal
    {
        class Nature_impl
        {
            friend class pksm::Nature;

        private:
            enum class NatureEnum : u8
            {
                Hardy,
                Lonely,
                Brave,
                Adamant,
                Naughty,
                Bold,
                Docile,
                Relaxed,
                Impish,
                Lax,
                Timid,
                Hasty,
                Serious,
                Jolly,
                Naive,
                Modest,
                Mild,
                Quiet,
                Bashful,
                Rash,
                Calm,
                Gentle,
                Sassy,
                Careful,
                Quirky,

                INVALID [[maybe_unused]] =
                    std::numeric_limits<std::underlying_type_t<NatureEnum>>::max()
            } v;

            constexpr explicit Nature_impl(NatureEnum v) : v(v) {}
            constexpr Nature_impl(const Nature_impl&) = default;
            constexpr Nature_impl(Nature_impl&&)      = default;
            constexpr Nature_impl& operator=(const Nature_impl&) = default;
            constexpr Nature_impl& operator=(Nature_impl&&) = default;

        public:
            template <typename T>
            constexpr explicit operator T() const noexcept
            {
                static_assert(std::is_integral_v<T>);
                return T(v);
            }
            constexpr operator NatureEnum() const noexcept { return v; }

            constexpr bool operator<(const Nature_impl& other) const noexcept
            {
                return v < other.v;
            }
            constexpr bool operator<=(const Nature_impl& other) const noexcept
            {
                return v <= other.v;
            }

            constexpr bool operator>(const Nature_impl& other) const noexcept
            {
                return v > other.v;
            }
            constexpr bool operator>=(const Nature_impl& other) const noexcept
            {
                return v >= other.v;
            }

            constexpr bool operator==(const Nature_impl& other) const noexcept
            {
                return v == other.v;
            }
            constexpr bool operator!=(const Nature_impl& other) const noexcept
            {
                return v != other.v;
            }

            const std::string& localize(Language lang) const;
        };
    }

    class Nature
    {
    private:
        internal::Nature_impl impl;

    public:
        using EnumType = internal::Nature_impl::NatureEnum;
        constexpr Nature() noexcept : impl(EnumType{0}) {}
        constexpr Nature(const internal::Nature_impl& impl) noexcept : impl(impl) {}
        constexpr explicit Nature(std::underlying_type_t<EnumType> v) noexcept : impl(EnumType{v})
        {
        }
        template <typename T>
        constexpr explicit operator T() const noexcept
        {
            static_assert(std::is_integral_v<T>);
            return T(impl);
        }
        constexpr operator EnumType() const noexcept { return static_cast<EnumType>(impl); }

        constexpr bool operator<(const Nature& other) const noexcept { return impl < other.impl; }
        constexpr bool operator<=(const Nature& other) const noexcept { return impl <= other.impl; }

        constexpr bool operator>(const Nature& other) const noexcept { return impl > other.impl; }
        constexpr bool operator>=(const Nature& other) const noexcept { return impl >= other.impl; }

        constexpr bool operator==(const Nature& other) const noexcept { return impl == other.impl; }
        constexpr bool operator!=(const Nature& other) const noexcept { return impl != other.impl; }

        constexpr bool operator<(const internal::Nature_impl& other) const noexcept
        {
            return impl < other;
        }
        constexpr bool operator<=(const internal::Nature_impl& other) const noexcept
        {
            return impl <= other;
        }

        constexpr bool operator>(const internal::Nature_impl& other) const noexcept
        {
            return impl > other;
        }
        constexpr bool operator>=(const internal::Nature_impl& other) const noexcept
        {
            return impl >= other;
        }

        constexpr bool operator==(const internal::Nature_impl& other) const noexcept
        {
            return impl == other;
        }
        constexpr bool operator!=(const internal::Nature_impl& other) const noexcept
        {
            return impl != other;
        }

        const std::string& localize(Language lang) const { return impl.localize(lang); }

        static constexpr internal::Nature_impl Hardy{EnumType::Hardy};
        static constexpr internal::Nature_impl Lonely{EnumType::Lonely};
        static constexpr internal::Nature_impl Brave{EnumType::Brave};
        static constexpr internal::Nature_impl Adamant{EnumType::Adamant};
        static constexpr internal::Nature_impl Naughty{EnumType::Naughty};
        static constexpr internal::Nature_impl Bold{EnumType::Bold};
        static constexpr internal::Nature_impl Docile{EnumType::Docile};
        static constexpr internal::Nature_impl Relaxed{EnumType::Relaxed};
        static constexpr internal::Nature_impl Impish{EnumType::Impish};
        static constexpr internal::Nature_impl Lax{EnumType::Lax};
        static constexpr internal::Nature_impl Timid{EnumType::Timid};
        static constexpr internal::Nature_impl Hasty{EnumType::Hasty};
        static constexpr internal::Nature_impl Serious{EnumType::Serious};
        static constexpr internal::Nature_impl Jolly{EnumType::Jolly};
        static constexpr internal::Nature_impl Naive{EnumType::Naive};
        static constexpr internal::Nature_impl Modest{EnumType::Modest};
        static constexpr internal::Nature_impl Mild{EnumType::Mild};
        static constexpr internal::Nature_impl Quiet{EnumType::Quiet};
        static constexpr internal::Nature_impl Bashful{EnumType::Bashful};
        static constexpr internal::Nature_impl Rash{EnumType::Rash};
        static constexpr internal::Nature_impl Calm{EnumType::Calm};
        static constexpr internal::Nature_impl Gentle{EnumType::Gentle};
        static constexpr internal::Nature_impl Sassy{EnumType::Sassy};
        static constexpr internal::Nature_impl Careful{EnumType::Careful};
        static constexpr internal::Nature_impl Quirky{EnumType::Quirky};

        static constexpr internal::Nature_impl INVALID{EnumType::INVALID};
    };
}

#endif
