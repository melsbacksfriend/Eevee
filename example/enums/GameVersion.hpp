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

#ifndef GAMEVERSION_HPP
#define GAMEVERSION_HPP

#include "enums/Generation.hpp"
#include "utils/coretypes.h"
#include <limits>
#include <type_traits>

namespace pksm
{
    class GameVersion;
    namespace internal
    {
        class GameVersion_impl
        {
            friend class pksm::GameVersion;

        private:
            enum class GameVersionEnum : u8
            {
                None = 0,
                /// Pokémon Sapphire (GBA)
                S = 1,
                /// Pokémon Ruby (GBA)
                R = 2,
                /// Pokémon Emerald (GBA)
                E = 3,
                /// Pokémon FireRed (GBA)
                FR = 4,
                /// Pokémon LeafGreen (GBA)
                LG = 5,
                /// Pokémon Colosseum & Pokémon XD (GameCube)
                CXD = 15,
                /// Pokémon Diamond (NDS)
                D = 10,
                /// Pokémon Pearl (NDS)
                P = 11,
                /// Pokémon Platinum (NDS)
                Pt = 12,
                /// Pokémon Heart Gold (NDS)
                HG = 7,
                /// Pokémon Soul Silver (NDS)
                SS = 8,
                /// Pokémon White (NDS)
                W = 20,
                /// Pokémon Black (NDS)
                B = 21,
                /// Pokémon White 2 (NDS)
                W2 = 22,
                /// Pokémon Black 2 (NDS)
                B2 = 23,
                /// Pokémon X (3DS)
                X = 24,
                /// Pokémon Y (3DS)
                Y = 25,
                /// Pokémon Alpha Sapphire (3DS)
                AS = 26,
                /// Pokémon Omega Ruby (3DS)
                OR = 27,
                /// Pokémon Sun (3DS)
                SN = 30,
                /// Pokémon Moon (3DS)
                MN = 31,
                /// Pokémon Ultra Sun (3DS)
                US = 32,
                /// Pokémon Ultra Moon (3DS)
                UM = 33,
                /// Pokémon GO (GO -> Lets Go transfers)
                GO = 34,
                /// Pokémon Red (3DS Virtual Console)
                RD = 35,
                /// Pokémon Green[JP]/Blue[INT] (3DS Virtual Console)
                GN = 36,
                /// Pokémon Blue[JP] (3DS Virtual Console)
                BU = 37,
                /// Pokémon Yellow [JP] (3DS Virtual Console)
                YW = 38,
                /// Pokémon Gold (3DS Virtual Console)
                GD = 39,
                /// Pokémon Silver (3DS Virtual Console)
                SV = 40,
                /// Pokémon Crystal (3DS Virtual Console)
                C = 41,
                /// Pokémon Let's Go Pikachu (NX)
                GP = 42,
                /// Pokémon Let's Go Eevee (NX)
                GE = 43,
                /// Pokémon Sword (NX)
                SW = 44,
                /// Pokémon Shield (NX)
                SH = 45,

                INVALID [[maybe_unused]] =
                    std::numeric_limits<std::underlying_type_t<GameVersionEnum>>::max()
            } v;

            constexpr explicit GameVersion_impl(GameVersionEnum v) : v(v) {}
            constexpr GameVersion_impl(const GameVersion_impl&) = default;
            constexpr GameVersion_impl(GameVersion_impl&&)      = default;
            constexpr GameVersion_impl& operator=(const GameVersion_impl&) = default;
            constexpr GameVersion_impl& operator=(GameVersion_impl&&) = default;

        public:
            template <typename T>
            constexpr explicit operator T() const noexcept
            {
                static_assert(std::is_integral_v<T>);
                return T(v);
            }
            constexpr explicit operator pksm::Generation() const noexcept
            {
                switch (v)
                {
                    case GameVersionEnum::S:   // 1:
                    case GameVersionEnum::R:   // 2:
                    case GameVersionEnum::E:   // 3:
                    case GameVersionEnum::FR:  // 4:
                    case GameVersionEnum::LG:  // 5:
                    case GameVersionEnum::CXD: // 15:
                        return Generation::THREE;
                    case GameVersionEnum::D:  // 10:
                    case GameVersionEnum::P:  // 11:
                    case GameVersionEnum::Pt: // 12:
                    case GameVersionEnum::HG: // 7:
                    case GameVersionEnum::SS: // 8:
                        return Generation::FOUR;
                    case GameVersionEnum::W:  // 20:
                    case GameVersionEnum::B:  // 21:
                    case GameVersionEnum::W2: // 22:
                    case GameVersionEnum::B2: // 23:
                        return Generation::FIVE;
                    case GameVersionEnum::X:  // 24:
                    case GameVersionEnum::Y:  // 25:
                    case GameVersionEnum::AS: // 26:
                    case GameVersionEnum::OR: // 27:
                        return Generation::SIX;
                    case GameVersionEnum::SN: // 30:
                    case GameVersionEnum::MN: // 31:
                    case GameVersionEnum::US: // 32:
                    case GameVersionEnum::UM: // 33:
                        return Generation::SEVEN;
                    case GameVersionEnum::GP: // 42:
                    case GameVersionEnum::GE: // 43:
                        return Generation::LGPE;
                    case GameVersionEnum::SW: // 44:
                    case GameVersionEnum::SH: // 45:
                        return Generation::EIGHT;
                    case GameVersionEnum::RD: // 35:
                    case GameVersionEnum::GN: // 36:
                    case GameVersionEnum::BU: // 37:
                    case GameVersionEnum::YW: // 38:
                        return Generation::ONE;
                    case GameVersionEnum::GD: // 39:
                    case GameVersionEnum::SV: // 40:
                    case GameVersionEnum::C:  // 41:
                        return Generation::TWO;
                    case GameVersionEnum::None: // 0:
                    case GameVersionEnum::GO:   // 34:
                    case GameVersionEnum::INVALID:
                        return Generation::UNUSED;
                }
                return Generation::UNUSED;
            }
            constexpr operator GameVersionEnum() const noexcept { return v; }

            constexpr bool operator<(const GameVersion_impl& other) const noexcept
            {
                if (static_cast<Generation>(*this) == static_cast<Generation>(other))
                {
                    return v < other.v;
                }
                return static_cast<Generation>(*this) < static_cast<Generation>(other);
            }
            constexpr bool operator<=(const GameVersion_impl& other) const noexcept
            {
                if (static_cast<Generation>(*this) == static_cast<Generation>(other))
                {
                    return v <= other.v;
                }
                return static_cast<Generation>(*this) <= static_cast<Generation>(other);
            }

            constexpr bool operator>(const GameVersion_impl& other) const noexcept
            {
                if (static_cast<Generation>(*this) == static_cast<Generation>(other))
                {
                    return v > other.v;
                }
                return static_cast<Generation>(*this) > static_cast<Generation>(other);
            }
            constexpr bool operator>=(const GameVersion_impl& other) const noexcept
            {
                if (static_cast<Generation>(*this) == static_cast<Generation>(other))
                {
                    return v >= other.v;
                }
                return static_cast<Generation>(*this) >= static_cast<Generation>(other);
            }

            constexpr bool operator==(const GameVersion_impl& other) const noexcept
            {
                return v == other.v;
            }
            constexpr bool operator!=(const GameVersion_impl& other) const noexcept
            {
                return v != other.v;
            }
        };
    }

    class GameVersion
    {
    private:
        internal::GameVersion_impl impl;

    public:
        using EnumType = internal::GameVersion_impl::GameVersionEnum;
        constexpr GameVersion() noexcept : impl(EnumType::INVALID) {}
        constexpr GameVersion(const internal::GameVersion_impl& impl) noexcept : impl(impl) {}
        constexpr explicit GameVersion(std::underlying_type_t<EnumType> v) noexcept
            : impl(EnumType{v})
        {
        }
        template <typename T>
        constexpr explicit operator T() const noexcept
        {
            static_assert(std::is_integral_v<T>);
            return T(impl);
        }
        constexpr explicit operator pksm::Generation() const noexcept
        {
            return static_cast<Generation>(impl);
        }
        constexpr operator EnumType() const noexcept { return static_cast<EnumType>(impl); }

        static constexpr GameVersion newestVersion(const Generation& gen) noexcept
        {
            switch (gen)
            {
                case Generation::ONE:
                    return GameVersion::YW;
                case Generation::TWO:
                    return GameVersion::C;
                case Generation::THREE:
                    return GameVersion::LG;
                case Generation::FOUR:
                    return GameVersion::HG;
                case Generation::FIVE:
                    return GameVersion::B2;
                case Generation::SIX:
                    return GameVersion::OR;
                case Generation::SEVEN:
                    return GameVersion::UM;
                case Generation::EIGHT:
                    return GameVersion::SH;
                case Generation::LGPE:
                    return GameVersion::GE;
                default:
                    return GameVersion::INVALID;
            }
        }

        static constexpr GameVersion oldestVersion(const Generation& gen) noexcept
        {
            switch (gen)
            {
                case Generation::ONE:
                    return GameVersion::RD;
                case Generation::TWO:
                    return GameVersion::GD;
                case Generation::THREE:
                    return GameVersion::S;
                case Generation::FOUR:
                    return GameVersion::D;
                case Generation::FIVE:
                    return GameVersion::W;
                case Generation::SIX:
                    return GameVersion::X;
                case Generation::SEVEN:
                    return GameVersion::SN;
                case Generation::EIGHT:
                    return GameVersion::SW;
                case Generation::LGPE:
                    return GameVersion::GP;
                default:
                    return GameVersion::INVALID;
            }
        }

        constexpr bool operator<(const GameVersion& other) const noexcept
        {
            return impl < other.impl;
        }
        constexpr bool operator<=(const GameVersion& other) const noexcept
        {
            return impl <= other.impl;
        }

        constexpr bool operator>(const GameVersion& other) const noexcept
        {
            return impl > other.impl;
        }
        constexpr bool operator>=(const GameVersion& other) const noexcept
        {
            return impl >= other.impl;
        }

        constexpr bool operator==(const GameVersion& other) const noexcept
        {
            return impl == other.impl;
        }
        constexpr bool operator!=(const GameVersion& other) const noexcept
        {
            return impl != other.impl;
        }

        constexpr bool operator<(const internal::GameVersion_impl& other) const noexcept
        {
            return impl < other;
        }
        constexpr bool operator<=(const internal::GameVersion_impl& other) const noexcept
        {
            return impl <= other;
        }

        constexpr bool operator>(const internal::GameVersion_impl& other) const noexcept
        {
            return impl > other;
        }
        constexpr bool operator>=(const internal::GameVersion_impl& other) const noexcept
        {
            return impl >= other;
        }

        constexpr bool operator==(const internal::GameVersion_impl& other) const noexcept
        {
            return impl == other;
        }
        constexpr bool operator!=(const internal::GameVersion_impl& other) const noexcept
        {
            return impl != other;
        }

        static constexpr internal::GameVersion_impl None{EnumType::None};
        /// Pokémon Sapphire (GBA)
        static constexpr internal::GameVersion_impl S{EnumType::S};
        /// Pokémon Ruby (GBA)
        static constexpr internal::GameVersion_impl R{EnumType::R};
        /// Pokémon Emerald (GBA)
        static constexpr internal::GameVersion_impl E{EnumType::E};
        /// Pokémon FireRed (GBA)
        static constexpr internal::GameVersion_impl FR{EnumType::FR};
        /// Pokémon LeafGreen (GBA)
        static constexpr internal::GameVersion_impl LG{EnumType::LG};
        /// Pokémon Colosseum & Pokémon XD (GameCube)
        static constexpr internal::GameVersion_impl CXD{EnumType::CXD};
        /// Pokémon Diamond (NDS)
        static constexpr internal::GameVersion_impl D{EnumType::D};
        /// Pokémon Pearl (NDS)
        static constexpr internal::GameVersion_impl P{EnumType::P};
        /// Pokémon Platinum (NDS)
        static constexpr internal::GameVersion_impl Pt{EnumType::Pt};
        /// Pokémon Heart Gold (NDS)
        static constexpr internal::GameVersion_impl HG{EnumType::HG};
        /// Pokémon Soul Silver (NDS)
        static constexpr internal::GameVersion_impl SS{EnumType::SS};
        /// Pokémon White (NDS)
        static constexpr internal::GameVersion_impl W{EnumType::W};
        /// Pokémon Black (NDS)
        static constexpr internal::GameVersion_impl B{EnumType::B};
        /// Pokémon White 2 (NDS)
        static constexpr internal::GameVersion_impl W2{EnumType::W2};
        /// Pokémon Black 2 (NDS)
        static constexpr internal::GameVersion_impl B2{EnumType::B2};
        /// Pokémon X (3DS)
        static constexpr internal::GameVersion_impl X{EnumType::X};
        /// Pokémon Y (3DS)
        static constexpr internal::GameVersion_impl Y{EnumType::Y};
        /// Pokémon Alpha Sapphire (3DS)
        static constexpr internal::GameVersion_impl AS{EnumType::AS};
        /// Pokémon Omega Ruby (3DS)
        static constexpr internal::GameVersion_impl OR{EnumType::OR};
        /// Pokémon Sun (3DS)
        static constexpr internal::GameVersion_impl SN{EnumType::SN};
        /// Pokémon Moon (3DS)
        static constexpr internal::GameVersion_impl MN{EnumType::MN};
        /// Pokémon Ultra Sun (3DS)
        static constexpr internal::GameVersion_impl US{EnumType::US};
        /// Pokémon Ultra Moon (3DS)
        static constexpr internal::GameVersion_impl UM{EnumType::UM};
        /// Pokémon GO (GO -> Lets Go transfers)
        static constexpr internal::GameVersion_impl GO{EnumType::GO};
        /// Pokémon Red (3DS Virtual Console)
        static constexpr internal::GameVersion_impl RD{EnumType::RD};
        /// Pokémon Green[JP]/Blue[INT] (3DS Virtual Console)
        static constexpr internal::GameVersion_impl GN{EnumType::GN};
        /// Pokémon Blue[JP] (3DS Virtual Console)
        static constexpr internal::GameVersion_impl BU{EnumType::BU};
        /// Pokémon Yellow [JP] (3DS Virtual Console)
        static constexpr internal::GameVersion_impl YW{EnumType::YW};
        /// Pokémon Gold (3DS Virtual Console)
        static constexpr internal::GameVersion_impl GD{EnumType::GD};
        /// Pokémon Silver (3DS Virtual Console)
        static constexpr internal::GameVersion_impl SV{EnumType::SV};
        /// Pokémon Crystal (3DS Virtual Console)
        static constexpr internal::GameVersion_impl C{EnumType::C};
        /// Pokémon Let's Go Pikachu (NX)
        static constexpr internal::GameVersion_impl GP{EnumType::GP};
        /// Pokémon Let's Go Eevee (NX)
        static constexpr internal::GameVersion_impl GE{EnumType::GE};
        /// Pokémon Sword (NX)
        static constexpr internal::GameVersion_impl SW{EnumType::SW};
        /// Pokémon Shield (NX)
        static constexpr internal::GameVersion_impl SH{EnumType::SH};

        static constexpr internal::GameVersion_impl INVALID{EnumType::INVALID};
    };
}

#endif
