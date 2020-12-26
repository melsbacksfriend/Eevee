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

#ifndef RIBBONS_HPP
#define RIBBONS_HPP

#include "enums/Language.hpp"
#include "utils/coretypes.h"
#include <limits>
#include <type_traits>

namespace pksm
{
    class Ribbon;
    namespace internal
    {
        class Ribbon_impl
        {
            friend class pksm::Ribbon;

        private:
            enum class RibbonEnum : u32
            {
                ChampionKalos,
                ChampionG3Hoenn,
                ChampionSinnoh,
                BestFriends,
                Training,
                BattlerSkillful,
                BattlerExpert,
                Effort,
                Alert,
                Shock,
                Downcast,
                Careless,
                Relax,
                Snooze,
                Smile,
                Gorgeous,
                Royal,
                GorgeousRoyal,
                Artist,
                Footprint,
                Record,
                Legend,
                Country,
                National,
                Earth,
                World,
                Classic,
                Premier,
                Event,
                Birthday,
                Special,
                Souvenir,
                Wishing,
                ChampionBattle,
                ChampionRegional,
                ChampionNational,
                ChampionWorld,
                MemoryContest,
                MemoryBattle,
                ChampionG6Hoenn,
                ContestStar,
                MasterCoolness,
                MasterBeauty,
                MasterCuteness,
                MasterCleverness,
                MasterToughness,

                G3Cool,
                G3CoolSuper,
                G3CoolHyper,
                G3CoolMaster,
                G3Beauty,
                G3BeautySuper,
                G3BeautyHyper,
                G3BeautyMaster,
                G3Cute,
                G3CuteSuper,
                G3CuteHyper,
                G3CuteMaster,
                G3Smart,
                G3SmartSuper,
                G3SmartHyper,
                G3SmartMaster,
                G3Tough,
                G3ToughSuper,
                G3ToughHyper,
                G3ToughMaster,
                G4Cool,
                G4CoolSuper,
                G4CoolHyper,
                G4CoolMaster,
                G4Beauty,
                G4BeautySuper,
                G4BeautyHyper,
                G4BeautyMaster,
                G4Cute,
                G4CuteSuper,
                G4CuteHyper,
                G4CuteMaster,
                G4Smart,
                G4SmartSuper,
                G4SmartHyper,
                G4SmartMaster,
                G4Tough,
                G4ToughSuper,
                G4ToughHyper,
                G4ToughMaster,
                Winning,
                Victory,
                Ability,
                AbilityGreat,
                AbilityDouble,
                AbilityMulti,
                AbilityPair,
                AbilityWorld,

                ChampionAlola,
                BattleRoyale,
                BattleTreeGreat,
                BattleTreeMaster,
                ChampionGalar,
                TowerMaster,
                MasterRank,

                MarkLunchtime,
                MarkSleepyTime,
                MarkDusk,
                MarkDawn,
                MarkCloudy,
                MarkRainy,
                MarkStormy,
                MarkSnowy,
                MarkBlizzard,
                MarkDry,
                MarkSandstorm,
                MarkMisty,
                MarkDestiny,
                MarkFishing,
                MarkCurry,
                MarkUncommon,
                MarkRare,
                MarkRowdy,
                MarkAbsentMinded,
                MarkJittery,
                MarkExcited,
                MarkCharismatic,
                MarkCalmness,
                MarkIntense,
                MarkZonedOut,
                MarkJoyful,
                MarkAngry,
                MarkSmiley,
                MarkTeary,
                MarkUpbeat,
                MarkPeeved,
                MarkIntellectual,
                MarkFerocious,
                MarkCrafty,
                MarkScowling,
                MarkKindly,
                MarkFlustered,
                MarkPumpedUp,
                MarkZeroEnergy,
                MarkPrideful,
                MarkUnsure,
                MarkHumble,
                MarkThorny,
                MarkVigor,
                MarkSlump,

                INVALID [[maybe_unused]] =
                    std::numeric_limits<std::underlying_type_t<RibbonEnum>>::max()
            } v;

            constexpr explicit Ribbon_impl(RibbonEnum v) : v(v) {}
            constexpr Ribbon_impl(const Ribbon_impl&) = default;
            constexpr Ribbon_impl(Ribbon_impl&&)      = default;
            constexpr Ribbon_impl& operator=(const Ribbon_impl&) = default;
            constexpr Ribbon_impl& operator=(Ribbon_impl&&) = default;

        public:
            template <typename T>
            constexpr explicit operator T() const noexcept
            {
                static_assert(std::is_integral_v<T>);
                return T(v);
            }
            constexpr operator RibbonEnum() const noexcept { return v; }

            constexpr bool operator<(const Ribbon_impl& other) const noexcept
            {
                return v < other.v;
            }
            constexpr bool operator<=(const Ribbon_impl& other) const noexcept
            {
                return v <= other.v;
            }

            constexpr bool operator>(const Ribbon_impl& other) const noexcept
            {
                return v > other.v;
            }
            constexpr bool operator>=(const Ribbon_impl& other) const noexcept
            {
                return v >= other.v;
            }

            constexpr bool operator==(const Ribbon_impl& other) const noexcept
            {
                return v == other.v;
            }
            constexpr bool operator!=(const Ribbon_impl& other) const noexcept
            {
                return v != other.v;
            }

            const std::string& localize(Language lang) const;
        };
    }

    class Ribbon
    {
    private:
        internal::Ribbon_impl impl;

    public:
        using EnumType = internal::Ribbon_impl::RibbonEnum;
        constexpr Ribbon() noexcept : impl(EnumType{0}) {}
        constexpr Ribbon(const internal::Ribbon_impl& impl) noexcept : impl(impl) {}
        constexpr explicit Ribbon(std::underlying_type_t<EnumType> v) noexcept : impl(EnumType{v})
        {
        }
        template <typename T>
        constexpr explicit operator T() const noexcept
        {
            static_assert(std::is_integral_v<T>);
            return T(impl);
        }
        constexpr operator EnumType() const noexcept { return static_cast<EnumType>(impl); }

        constexpr bool operator<(const Ribbon& other) const noexcept { return impl < other.impl; }
        constexpr bool operator<=(const Ribbon& other) const noexcept { return impl <= other.impl; }

        constexpr bool operator>(const Ribbon& other) const noexcept { return impl > other.impl; }
        constexpr bool operator>=(const Ribbon& other) const noexcept { return impl >= other.impl; }

        constexpr bool operator==(const Ribbon& other) const noexcept { return impl == other.impl; }
        constexpr bool operator!=(const Ribbon& other) const noexcept { return impl != other.impl; }

        constexpr bool operator<(const internal::Ribbon_impl& other) const noexcept
        {
            return impl < other;
        }
        constexpr bool operator<=(const internal::Ribbon_impl& other) const noexcept
        {
            return impl <= other;
        }

        constexpr bool operator>(const internal::Ribbon_impl& other) const noexcept
        {
            return impl > other;
        }
        constexpr bool operator>=(const internal::Ribbon_impl& other) const noexcept
        {
            return impl >= other;
        }

        constexpr bool operator==(const internal::Ribbon_impl& other) const noexcept
        {
            return impl == other;
        }
        constexpr bool operator!=(const internal::Ribbon_impl& other) const noexcept
        {
            return impl != other;
        }

        const std::string& localize(Language lang) const { return impl.localize(lang); }

        static constexpr internal::Ribbon_impl ChampionKalos{EnumType::ChampionKalos};
        static constexpr internal::Ribbon_impl ChampionG3Hoenn{EnumType::ChampionG3Hoenn};
        static constexpr internal::Ribbon_impl ChampionSinnoh{EnumType::ChampionSinnoh};
        static constexpr internal::Ribbon_impl BestFriends{EnumType::BestFriends};
        static constexpr internal::Ribbon_impl Training{EnumType::Training};
        static constexpr internal::Ribbon_impl BattlerSkillful{EnumType::BattlerSkillful};
        static constexpr internal::Ribbon_impl BattlerExpert{EnumType::BattlerExpert};
        static constexpr internal::Ribbon_impl Effort{EnumType::Effort};
        static constexpr internal::Ribbon_impl Alert{EnumType::Alert};
        static constexpr internal::Ribbon_impl Shock{EnumType::Shock};
        static constexpr internal::Ribbon_impl Downcast{EnumType::Downcast};
        static constexpr internal::Ribbon_impl Careless{EnumType::Careless};
        static constexpr internal::Ribbon_impl Relax{EnumType::Relax};
        static constexpr internal::Ribbon_impl Snooze{EnumType::Snooze};
        static constexpr internal::Ribbon_impl Smile{EnumType::Smile};
        static constexpr internal::Ribbon_impl Gorgeous{EnumType::Gorgeous};
        static constexpr internal::Ribbon_impl Royal{EnumType::Royal};
        static constexpr internal::Ribbon_impl GorgeousRoyal{EnumType::GorgeousRoyal};
        static constexpr internal::Ribbon_impl Artist{EnumType::Artist};
        static constexpr internal::Ribbon_impl Footprint{EnumType::Footprint};
        static constexpr internal::Ribbon_impl Record{EnumType::Record};
        static constexpr internal::Ribbon_impl Legend{EnumType::Legend};
        static constexpr internal::Ribbon_impl Country{EnumType::Country};
        static constexpr internal::Ribbon_impl National{EnumType::National};
        static constexpr internal::Ribbon_impl Earth{EnumType::Earth};
        static constexpr internal::Ribbon_impl World{EnumType::World};
        static constexpr internal::Ribbon_impl Classic{EnumType::Classic};
        static constexpr internal::Ribbon_impl Premier{EnumType::Premier};
        static constexpr internal::Ribbon_impl Event{EnumType::Event};
        static constexpr internal::Ribbon_impl Birthday{EnumType::Birthday};
        static constexpr internal::Ribbon_impl Special{EnumType::Special};
        static constexpr internal::Ribbon_impl Souvenir{EnumType::Souvenir};
        static constexpr internal::Ribbon_impl Wishing{EnumType::Wishing};
        static constexpr internal::Ribbon_impl ChampionBattle{EnumType::ChampionBattle};
        static constexpr internal::Ribbon_impl ChampionRegional{EnumType::ChampionRegional};
        static constexpr internal::Ribbon_impl ChampionNational{EnumType::ChampionNational};
        static constexpr internal::Ribbon_impl ChampionWorld{EnumType::ChampionWorld};
        static constexpr internal::Ribbon_impl MemoryContest{EnumType::MemoryContest};
        static constexpr internal::Ribbon_impl MemoryBattle{EnumType::MemoryBattle};
        static constexpr internal::Ribbon_impl ChampionG6Hoenn{EnumType::ChampionG6Hoenn};
        static constexpr internal::Ribbon_impl ContestStar{EnumType::ContestStar};
        static constexpr internal::Ribbon_impl MasterCoolness{EnumType::MasterCoolness};
        static constexpr internal::Ribbon_impl MasterBeauty{EnumType::MasterBeauty};
        static constexpr internal::Ribbon_impl MasterCuteness{EnumType::MasterCuteness};
        static constexpr internal::Ribbon_impl MasterCleverness{EnumType::MasterCleverness};
        static constexpr internal::Ribbon_impl MasterToughness{EnumType::MasterToughness};
        static constexpr internal::Ribbon_impl G3Cool{EnumType::G3Cool};
        static constexpr internal::Ribbon_impl G3CoolSuper{EnumType::G3CoolSuper};
        static constexpr internal::Ribbon_impl G3CoolHyper{EnumType::G3CoolHyper};
        static constexpr internal::Ribbon_impl G3CoolMaster{EnumType::G3CoolMaster};
        static constexpr internal::Ribbon_impl G3Beauty{EnumType::G3Beauty};
        static constexpr internal::Ribbon_impl G3BeautySuper{EnumType::G3BeautySuper};
        static constexpr internal::Ribbon_impl G3BeautyHyper{EnumType::G3BeautyHyper};
        static constexpr internal::Ribbon_impl G3BeautyMaster{EnumType::G3BeautyMaster};
        static constexpr internal::Ribbon_impl G3Cute{EnumType::G3Cute};
        static constexpr internal::Ribbon_impl G3CuteSuper{EnumType::G3CuteSuper};
        static constexpr internal::Ribbon_impl G3CuteHyper{EnumType::G3CuteHyper};
        static constexpr internal::Ribbon_impl G3CuteMaster{EnumType::G3CuteMaster};
        static constexpr internal::Ribbon_impl G3Smart{EnumType::G3Smart};
        static constexpr internal::Ribbon_impl G3SmartSuper{EnumType::G3SmartSuper};
        static constexpr internal::Ribbon_impl G3SmartHyper{EnumType::G3SmartHyper};
        static constexpr internal::Ribbon_impl G3SmartMaster{EnumType::G3SmartMaster};
        static constexpr internal::Ribbon_impl G3Tough{EnumType::G3Tough};
        static constexpr internal::Ribbon_impl G3ToughSuper{EnumType::G3ToughSuper};
        static constexpr internal::Ribbon_impl G3ToughHyper{EnumType::G3ToughHyper};
        static constexpr internal::Ribbon_impl G3ToughMaster{EnumType::G3ToughMaster};
        static constexpr internal::Ribbon_impl G4Cool{EnumType::G4Cool};
        static constexpr internal::Ribbon_impl G4CoolSuper{EnumType::G4CoolSuper};
        static constexpr internal::Ribbon_impl G4CoolHyper{EnumType::G4CoolHyper};
        static constexpr internal::Ribbon_impl G4CoolMaster{EnumType::G4CoolMaster};
        static constexpr internal::Ribbon_impl G4Beauty{EnumType::G4Beauty};
        static constexpr internal::Ribbon_impl G4BeautySuper{EnumType::G4BeautySuper};
        static constexpr internal::Ribbon_impl G4BeautyHyper{EnumType::G4BeautyHyper};
        static constexpr internal::Ribbon_impl G4BeautyMaster{EnumType::G4BeautyMaster};
        static constexpr internal::Ribbon_impl G4Cute{EnumType::G4Cute};
        static constexpr internal::Ribbon_impl G4CuteSuper{EnumType::G4CuteSuper};
        static constexpr internal::Ribbon_impl G4CuteHyper{EnumType::G4CuteHyper};
        static constexpr internal::Ribbon_impl G4CuteMaster{EnumType::G4CuteMaster};
        static constexpr internal::Ribbon_impl G4Smart{EnumType::G4Smart};
        static constexpr internal::Ribbon_impl G4SmartSuper{EnumType::G4SmartSuper};
        static constexpr internal::Ribbon_impl G4SmartHyper{EnumType::G4SmartHyper};
        static constexpr internal::Ribbon_impl G4SmartMaster{EnumType::G4SmartMaster};
        static constexpr internal::Ribbon_impl G4Tough{EnumType::G4Tough};
        static constexpr internal::Ribbon_impl G4ToughSuper{EnumType::G4ToughSuper};
        static constexpr internal::Ribbon_impl G4ToughHyper{EnumType::G4ToughHyper};
        static constexpr internal::Ribbon_impl G4ToughMaster{EnumType::G4ToughMaster};
        static constexpr internal::Ribbon_impl Winning{EnumType::Winning};
        static constexpr internal::Ribbon_impl Victory{EnumType::Victory};
        static constexpr internal::Ribbon_impl Ability{EnumType::Ability};
        static constexpr internal::Ribbon_impl AbilityGreat{EnumType::AbilityGreat};
        static constexpr internal::Ribbon_impl AbilityDouble{EnumType::AbilityDouble};
        static constexpr internal::Ribbon_impl AbilityMulti{EnumType::AbilityMulti};
        static constexpr internal::Ribbon_impl AbilityPair{EnumType::AbilityPair};
        static constexpr internal::Ribbon_impl AbilityWorld{EnumType::AbilityWorld};
        static constexpr internal::Ribbon_impl ChampionAlola{EnumType::ChampionAlola};
        static constexpr internal::Ribbon_impl BattleRoyale{EnumType::BattleRoyale};
        static constexpr internal::Ribbon_impl BattleTreeGreat{EnumType::BattleTreeGreat};
        static constexpr internal::Ribbon_impl BattleTreeMaster{EnumType::BattleTreeMaster};
        static constexpr internal::Ribbon_impl ChampionGalar{EnumType::ChampionGalar};
        static constexpr internal::Ribbon_impl TowerMaster{EnumType::TowerMaster};
        static constexpr internal::Ribbon_impl MasterRank{EnumType::MasterRank};
        static constexpr internal::Ribbon_impl MarkLunchtime{EnumType::MarkLunchtime};
        static constexpr internal::Ribbon_impl MarkSleepyTime{EnumType::MarkSleepyTime};
        static constexpr internal::Ribbon_impl MarkDusk{EnumType::MarkDusk};
        static constexpr internal::Ribbon_impl MarkDawn{EnumType::MarkDawn};
        static constexpr internal::Ribbon_impl MarkCloudy{EnumType::MarkCloudy};
        static constexpr internal::Ribbon_impl MarkRainy{EnumType::MarkRainy};
        static constexpr internal::Ribbon_impl MarkStormy{EnumType::MarkStormy};
        static constexpr internal::Ribbon_impl MarkSnowy{EnumType::MarkSnowy};
        static constexpr internal::Ribbon_impl MarkBlizzard{EnumType::MarkBlizzard};
        static constexpr internal::Ribbon_impl MarkDry{EnumType::MarkDry};
        static constexpr internal::Ribbon_impl MarkSandstorm{EnumType::MarkSandstorm};
        static constexpr internal::Ribbon_impl MarkMisty{EnumType::MarkMisty};
        static constexpr internal::Ribbon_impl MarkDestiny{EnumType::MarkDestiny};
        static constexpr internal::Ribbon_impl MarkFishing{EnumType::MarkFishing};
        static constexpr internal::Ribbon_impl MarkCurry{EnumType::MarkCurry};
        static constexpr internal::Ribbon_impl MarkUncommon{EnumType::MarkUncommon};
        static constexpr internal::Ribbon_impl MarkRare{EnumType::MarkRare};
        static constexpr internal::Ribbon_impl MarkRowdy{EnumType::MarkRowdy};
        static constexpr internal::Ribbon_impl MarkAbsentMinded{EnumType::MarkAbsentMinded};
        static constexpr internal::Ribbon_impl MarkJittery{EnumType::MarkJittery};
        static constexpr internal::Ribbon_impl MarkExcited{EnumType::MarkExcited};
        static constexpr internal::Ribbon_impl MarkCharismatic{EnumType::MarkCharismatic};
        static constexpr internal::Ribbon_impl MarkCalmness{EnumType::MarkCalmness};
        static constexpr internal::Ribbon_impl MarkIntense{EnumType::MarkIntense};
        static constexpr internal::Ribbon_impl MarkZonedOut{EnumType::MarkZonedOut};
        static constexpr internal::Ribbon_impl MarkJoyful{EnumType::MarkJoyful};
        static constexpr internal::Ribbon_impl MarkAngry{EnumType::MarkAngry};
        static constexpr internal::Ribbon_impl MarkSmiley{EnumType::MarkSmiley};
        static constexpr internal::Ribbon_impl MarkTeary{EnumType::MarkTeary};
        static constexpr internal::Ribbon_impl MarkUpbeat{EnumType::MarkUpbeat};
        static constexpr internal::Ribbon_impl MarkPeeved{EnumType::MarkPeeved};
        static constexpr internal::Ribbon_impl MarkIntellectual{EnumType::MarkIntellectual};
        static constexpr internal::Ribbon_impl MarkFerocious{EnumType::MarkFerocious};
        static constexpr internal::Ribbon_impl MarkCrafty{EnumType::MarkCrafty};
        static constexpr internal::Ribbon_impl MarkScowling{EnumType::MarkScowling};
        static constexpr internal::Ribbon_impl MarkKindly{EnumType::MarkKindly};
        static constexpr internal::Ribbon_impl MarkFlustered{EnumType::MarkFlustered};
        static constexpr internal::Ribbon_impl MarkPumpedUp{EnumType::MarkPumpedUp};
        static constexpr internal::Ribbon_impl MarkZeroEnergy{EnumType::MarkZeroEnergy};
        static constexpr internal::Ribbon_impl MarkPrideful{EnumType::MarkPrideful};
        static constexpr internal::Ribbon_impl MarkUnsure{EnumType::MarkUnsure};
        static constexpr internal::Ribbon_impl MarkHumble{EnumType::MarkHumble};
        static constexpr internal::Ribbon_impl MarkThorny{EnumType::MarkThorny};
        static constexpr internal::Ribbon_impl MarkVigor{EnumType::MarkVigor};
        static constexpr internal::Ribbon_impl MarkSlump{EnumType::MarkSlump};

        // G4 aliases
        static constexpr internal::Ribbon_impl G4CoolGreat{EnumType::G4CoolSuper};
        static constexpr internal::Ribbon_impl G4CoolUltra{EnumType::G4CoolHyper};
        static constexpr internal::Ribbon_impl G4BeautyGreat{EnumType::G4BeautySuper};
        static constexpr internal::Ribbon_impl G4BeautyUltra{EnumType::G4BeautyHyper};
        static constexpr internal::Ribbon_impl G4CuteGreat{EnumType::G4CuteSuper};
        static constexpr internal::Ribbon_impl G4CuteUltra{EnumType::G4CuteHyper};
        static constexpr internal::Ribbon_impl G4SmartGreat{EnumType::G4SmartSuper};
        static constexpr internal::Ribbon_impl G4SmartUltra{EnumType::G4SmartHyper};
        static constexpr internal::Ribbon_impl G4ToughGreat{EnumType::G4ToughSuper};
        static constexpr internal::Ribbon_impl G4ToughUltra{EnumType::G4ToughHyper};

        static constexpr internal::Ribbon_impl INVALID{EnumType::INVALID};
    };
}

#endif
