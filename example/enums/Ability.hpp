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

#ifndef ABILITY_HPP
#define ABILITY_HPP

#include "enums/Language.hpp"
#include "utils/coretypes.h"
#include <limits>
#include <type_traits>

namespace pksm
{
    class Ability;

    namespace internal
    {
        class Ability_impl
        {
            friend class pksm::Ability;

        private:
            enum class AbilityEnum : u16
            {
                None,
                Stench,
                Drizzle,
                SpeedBoost,
                BattleArmor,
                Sturdy,
                Damp,
                Limber,
                SandVeil,
                Static,
                VoltAbsorb,
                WaterAbsorb,
                Oblivious,
                CloudNine,
                CompoundEyes,
                Insomnia,
                ColorChange,
                Immunity,
                FlashFire,
                ShieldDust,
                OwnTempo,
                SuctionCups,
                Intimidate,
                ShadowTag,
                RoughSkin,
                WonderGuard,
                Levitate,
                EffectSpore,
                Synchronize,
                ClearBody,
                NaturalCure,
                LightningRod,
                SereneGrace,
                SwiftSwim,
                Chlorophyll,
                Illuminate,
                Trace,
                HugePower,
                PoisonPoint,
                InnerFocus,
                MagmaArmor,
                WaterVeil,
                MagnetPull,
                Soundproof,
                RainDish,
                SandStream,
                Pressure,
                ThickFat,
                EarlyBird,
                FlameBody,
                RunAway,
                KeenEye,
                HyperCutter,
                Pickup,
                Truant,
                Hustle,
                CuteCharm,
                Plus,
                Minus,
                Forecast,
                StickyHold,
                ShedSkin,
                Guts,
                MarvelScale,
                LiquidOoze,
                Overgrow,
                Blaze,
                Torrent,
                Swarm,
                RockHead,
                Drought,
                ArenaTrap,
                VitalSpirit,
                WhiteSmoke,
                PurePower,
                ShellArmor,
                AirLock,
                TangledFeet,
                MotorDrive,
                Rivalry,
                Steadfast,
                SnowCloak,
                Gluttony,
                AngerPoint,
                Unburden,
                Heatproof,
                Simple,
                DrySkin,
                Download,
                IronFist,
                PoisonHeal,
                Adaptability,
                SkillLink,
                Hydration,
                SolarPower,
                QuickFeet,
                Normalize,
                Sniper,
                MagicGuard,
                NoGuard,
                Stall,
                Technician,
                LeafGuard,
                Klutz,
                MoldBreaker,
                SuperLuck,
                Aftermath,
                Anticipation,
                Forewarn,
                Unaware,
                TintedLens,
                Filter,
                SlowStart,
                Scrappy,
                StormDrain,
                IceBody,
                SolidRock,
                SnowWarning,
                HoneyGather,
                Frisk,
                Reckless,
                Multitype,
                FlowerGift,
                BadDreams,
                Pickpocket,
                SheerForce,
                Contrary,
                Unnerve,
                Defiant,
                Defeatist,
                CursedBody,
                Healer,
                FriendGuard,
                WeakArmor,
                HeavyMetal,
                LightMetal,
                Multiscale,
                ToxicBoost,
                FlareBoost,
                Harvest,
                Telepathy,
                Moody,
                Overcoat,
                PoisonTouch,
                Regenerator,
                BigPecks,
                SandRush,
                WonderSkin,
                Analytic,
                Illusion,
                Imposter,
                Infiltrator,
                Mummy,
                Moxie,
                Justified,
                Rattled,
                MagicBounce,
                SapSipper,
                Prankster,
                SandForce,
                IronBarbs,
                ZenMode,
                VictoryStar,
                Turboblaze,
                Teravolt,
                AromaVeil,
                FlowerVeil,
                CheekPouch,
                Protean,
                FurCoat,
                Magician,
                Bulletproof,
                Competitive,
                StrongJaw,
                Refrigerate,
                SweetVeil,
                StanceChange,
                GaleWings,
                MegaLauncher,
                GrassPelt,
                Symbiosis,
                ToughClaws,
                Pixilate,
                Gooey,
                Aerilate,
                ParentalBond,
                DarkAura,
                FairyAura,
                AuraBreak,
                PrimordialSea,
                DesolateLand,
                DeltaStream,
                Stamina,
                WimpOut,
                EmergencyExit,
                WaterCompaction,
                Merciless,
                ShieldsDown,
                Stakeout,
                WaterBubble,
                Steelworker,
                Berserk,
                SlushRush,
                LongReach,
                LiquidVoice,
                Triage,
                Galvanize,
                SurgeSurfer,
                Schooling,
                Disguise,
                BattleBond,
                PowerConstruct,
                Corrosion,
                Comatose,
                QueenlyMajesty,
                InnardsOut,
                Dancer,
                Battery,
                Fluffy,
                Dazzling,
                SoulHeart,
                TanglingHair,
                Receiver,
                PowerofAlchemy,
                BeastBoost,
                RKSSystem,
                ElectricSurge,
                PsychicSurge,
                MistySurge,
                GrassySurge,
                FullMetalBody,
                ShadowShield,
                PrismArmor,
                Neuroforce,
                IntrepidSword,
                DauntlessShield,
                Libero,
                BallFetch,
                CottonDown,
                PropellerTail,
                MirrorArmor,
                GulpMissile,
                Stalwart,
                SteamEngine,
                PunkRock,
                SandSpit,
                IceScales,
                Ripen,
                IceFace,
                PowerSpot,
                Mimicry,
                ScreenCleaner,
                SteelySpirit,
                PerishBody,
                WanderingSpirit,
                GorillaTactics,
                NeutralizingGas,
                PastelVeil,
                HungerSwitch,
                QuickDraw,
                UnseenFist,

                INVALID [[maybe_unused]] =
                    std::numeric_limits<std::underlying_type_t<AbilityEnum>>::max()
            } v;

            constexpr explicit Ability_impl(AbilityEnum v) : v(v) {}
            constexpr Ability_impl(const Ability_impl&) = default;
            constexpr Ability_impl(Ability_impl&&)      = default;
            constexpr Ability_impl& operator=(const Ability_impl&) = default;
            constexpr Ability_impl& operator=(Ability_impl&&) = default;

        public:
            template <typename T>
            constexpr explicit operator T() const noexcept
            {
                static_assert(std::is_integral_v<T>);
                return T(v);
            }
            constexpr operator AbilityEnum() const noexcept { return v; }

            constexpr bool operator<(const Ability_impl& other) const noexcept
            {
                return v < other.v;
            }
            constexpr bool operator<=(const Ability_impl& other) const noexcept
            {
                return v <= other.v;
            }

            constexpr bool operator>(const Ability_impl& other) const noexcept
            {
                return v > other.v;
            }
            constexpr bool operator>=(const Ability_impl& other) const noexcept
            {
                return v >= other.v;
            }

            constexpr bool operator==(const Ability_impl& other) const noexcept
            {
                return v == other.v;
            }
            constexpr bool operator!=(const Ability_impl& other) const noexcept
            {
                return v != other.v;
            }

            const std::string& localize(Language lang) const;
        };
    }

    class Ability
    {
    private:
        internal::Ability_impl impl;

    public:
        using EnumType = internal::Ability_impl::AbilityEnum;
        constexpr Ability() noexcept : impl(EnumType::INVALID) {}
        constexpr Ability(const internal::Ability_impl& impl) noexcept : impl(impl) {}
        constexpr explicit Ability(std::underlying_type_t<EnumType> v) noexcept : impl(EnumType{v})
        {
        }
        template <typename T>
        constexpr explicit operator T() const noexcept
        {
            static_assert(std::is_integral_v<T>);
            return T(impl);
        }
        constexpr operator EnumType() const noexcept { return static_cast<EnumType>(impl); }

        constexpr bool operator<(const Ability& other) const noexcept { return impl < other.impl; }
        constexpr bool operator<=(const Ability& other) const noexcept
        {
            return impl <= other.impl;
        }

        constexpr bool operator>(const Ability& other) const noexcept { return impl > other.impl; }
        constexpr bool operator>=(const Ability& other) const noexcept
        {
            return impl >= other.impl;
        }

        constexpr bool operator==(const Ability& other) const noexcept
        {
            return impl == other.impl;
        }
        constexpr bool operator!=(const Ability& other) const noexcept
        {
            return impl != other.impl;
        }

        constexpr bool operator<(const internal::Ability_impl& other) const noexcept
        {
            return impl < other;
        }
        constexpr bool operator<=(const internal::Ability_impl& other) const noexcept
        {
            return impl <= other;
        }

        constexpr bool operator>(const internal::Ability_impl& other) const noexcept
        {
            return impl > other;
        }
        constexpr bool operator>=(const internal::Ability_impl& other) const noexcept
        {
            return impl >= other;
        }

        constexpr bool operator==(const internal::Ability_impl& other) const noexcept
        {
            return impl == other;
        }
        constexpr bool operator!=(const internal::Ability_impl& other) const noexcept
        {
            return impl != other;
        }

        const std::string& localize(Language lang) const { return impl.localize(lang); }

        static constexpr internal::Ability_impl None{EnumType::None};
        static constexpr internal::Ability_impl Stench{EnumType::Stench};
        static constexpr internal::Ability_impl Drizzle{EnumType::Drizzle};
        static constexpr internal::Ability_impl SpeedBoost{EnumType::SpeedBoost};
        static constexpr internal::Ability_impl BattleArmor{EnumType::BattleArmor};
        static constexpr internal::Ability_impl Sturdy{EnumType::Sturdy};
        static constexpr internal::Ability_impl Damp{EnumType::Damp};
        static constexpr internal::Ability_impl Limber{EnumType::Limber};
        static constexpr internal::Ability_impl SandVeil{EnumType::SandVeil};
        static constexpr internal::Ability_impl Static{EnumType::Static};
        static constexpr internal::Ability_impl VoltAbsorb{EnumType::VoltAbsorb};
        static constexpr internal::Ability_impl WaterAbsorb{EnumType::WaterAbsorb};
        static constexpr internal::Ability_impl Oblivious{EnumType::Oblivious};
        static constexpr internal::Ability_impl CloudNine{EnumType::CloudNine};
        static constexpr internal::Ability_impl CompoundEyes{EnumType::CompoundEyes};
        static constexpr internal::Ability_impl Insomnia{EnumType::Insomnia};
        static constexpr internal::Ability_impl ColorChange{EnumType::ColorChange};
        static constexpr internal::Ability_impl Immunity{EnumType::Immunity};
        static constexpr internal::Ability_impl FlashFire{EnumType::FlashFire};
        static constexpr internal::Ability_impl ShieldDust{EnumType::ShieldDust};
        static constexpr internal::Ability_impl OwnTempo{EnumType::OwnTempo};
        static constexpr internal::Ability_impl SuctionCups{EnumType::SuctionCups};
        static constexpr internal::Ability_impl Intimidate{EnumType::Intimidate};
        static constexpr internal::Ability_impl ShadowTag{EnumType::ShadowTag};
        static constexpr internal::Ability_impl RoughSkin{EnumType::RoughSkin};
        static constexpr internal::Ability_impl WonderGuard{EnumType::WonderGuard};
        static constexpr internal::Ability_impl Levitate{EnumType::Levitate};
        static constexpr internal::Ability_impl EffectSpore{EnumType::EffectSpore};
        static constexpr internal::Ability_impl Synchronize{EnumType::Synchronize};
        static constexpr internal::Ability_impl ClearBody{EnumType::ClearBody};
        static constexpr internal::Ability_impl NaturalCure{EnumType::NaturalCure};
        static constexpr internal::Ability_impl LightningRod{EnumType::LightningRod};
        static constexpr internal::Ability_impl SereneGrace{EnumType::SereneGrace};
        static constexpr internal::Ability_impl SwiftSwim{EnumType::SwiftSwim};
        static constexpr internal::Ability_impl Chlorophyll{EnumType::Chlorophyll};
        static constexpr internal::Ability_impl Illuminate{EnumType::Illuminate};
        static constexpr internal::Ability_impl Trace{EnumType::Trace};
        static constexpr internal::Ability_impl HugePower{EnumType::HugePower};
        static constexpr internal::Ability_impl PoisonPoint{EnumType::PoisonPoint};
        static constexpr internal::Ability_impl InnerFocus{EnumType::InnerFocus};
        static constexpr internal::Ability_impl MagmaArmor{EnumType::MagmaArmor};
        static constexpr internal::Ability_impl WaterVeil{EnumType::WaterVeil};
        static constexpr internal::Ability_impl MagnetPull{EnumType::MagnetPull};
        static constexpr internal::Ability_impl Soundproof{EnumType::Soundproof};
        static constexpr internal::Ability_impl RainDish{EnumType::RainDish};
        static constexpr internal::Ability_impl SandStream{EnumType::SandStream};
        static constexpr internal::Ability_impl Pressure{EnumType::Pressure};
        static constexpr internal::Ability_impl ThickFat{EnumType::ThickFat};
        static constexpr internal::Ability_impl EarlyBird{EnumType::EarlyBird};
        static constexpr internal::Ability_impl FlameBody{EnumType::FlameBody};
        static constexpr internal::Ability_impl RunAway{EnumType::RunAway};
        static constexpr internal::Ability_impl KeenEye{EnumType::KeenEye};
        static constexpr internal::Ability_impl HyperCutter{EnumType::HyperCutter};
        static constexpr internal::Ability_impl Pickup{EnumType::Pickup};
        static constexpr internal::Ability_impl Truant{EnumType::Truant};
        static constexpr internal::Ability_impl Hustle{EnumType::Hustle};
        static constexpr internal::Ability_impl CuteCharm{EnumType::CuteCharm};
        static constexpr internal::Ability_impl Plus{EnumType::Plus};
        static constexpr internal::Ability_impl Minus{EnumType::Minus};
        static constexpr internal::Ability_impl Forecast{EnumType::Forecast};
        static constexpr internal::Ability_impl StickyHold{EnumType::StickyHold};
        static constexpr internal::Ability_impl ShedSkin{EnumType::ShedSkin};
        static constexpr internal::Ability_impl Guts{EnumType::Guts};
        static constexpr internal::Ability_impl MarvelScale{EnumType::MarvelScale};
        static constexpr internal::Ability_impl LiquidOoze{EnumType::LiquidOoze};
        static constexpr internal::Ability_impl Overgrow{EnumType::Overgrow};
        static constexpr internal::Ability_impl Blaze{EnumType::Blaze};
        static constexpr internal::Ability_impl Torrent{EnumType::Torrent};
        static constexpr internal::Ability_impl Swarm{EnumType::Swarm};
        static constexpr internal::Ability_impl RockHead{EnumType::RockHead};
        static constexpr internal::Ability_impl Drought{EnumType::Drought};
        static constexpr internal::Ability_impl ArenaTrap{EnumType::ArenaTrap};
        static constexpr internal::Ability_impl VitalSpirit{EnumType::VitalSpirit};
        static constexpr internal::Ability_impl WhiteSmoke{EnumType::WhiteSmoke};
        static constexpr internal::Ability_impl PurePower{EnumType::PurePower};
        static constexpr internal::Ability_impl ShellArmor{EnumType::ShellArmor};
        static constexpr internal::Ability_impl AirLock{EnumType::AirLock};
        static constexpr internal::Ability_impl TangledFeet{EnumType::TangledFeet};
        static constexpr internal::Ability_impl MotorDrive{EnumType::MotorDrive};
        static constexpr internal::Ability_impl Rivalry{EnumType::Rivalry};
        static constexpr internal::Ability_impl Steadfast{EnumType::Steadfast};
        static constexpr internal::Ability_impl SnowCloak{EnumType::SnowCloak};
        static constexpr internal::Ability_impl Gluttony{EnumType::Gluttony};
        static constexpr internal::Ability_impl AngerPoint{EnumType::AngerPoint};
        static constexpr internal::Ability_impl Unburden{EnumType::Unburden};
        static constexpr internal::Ability_impl Heatproof{EnumType::Heatproof};
        static constexpr internal::Ability_impl Simple{EnumType::Simple};
        static constexpr internal::Ability_impl DrySkin{EnumType::DrySkin};
        static constexpr internal::Ability_impl Download{EnumType::Download};
        static constexpr internal::Ability_impl IronFist{EnumType::IronFist};
        static constexpr internal::Ability_impl PoisonHeal{EnumType::PoisonHeal};
        static constexpr internal::Ability_impl Adaptability{EnumType::Adaptability};
        static constexpr internal::Ability_impl SkillLink{EnumType::SkillLink};
        static constexpr internal::Ability_impl Hydration{EnumType::Hydration};
        static constexpr internal::Ability_impl SolarPower{EnumType::SolarPower};
        static constexpr internal::Ability_impl QuickFeet{EnumType::QuickFeet};
        static constexpr internal::Ability_impl Normalize{EnumType::Normalize};
        static constexpr internal::Ability_impl Sniper{EnumType::Sniper};
        static constexpr internal::Ability_impl MagicGuard{EnumType::MagicGuard};
        static constexpr internal::Ability_impl NoGuard{EnumType::NoGuard};
        static constexpr internal::Ability_impl Stall{EnumType::Stall};
        static constexpr internal::Ability_impl Technician{EnumType::Technician};
        static constexpr internal::Ability_impl LeafGuard{EnumType::LeafGuard};
        static constexpr internal::Ability_impl Klutz{EnumType::Klutz};
        static constexpr internal::Ability_impl MoldBreaker{EnumType::MoldBreaker};
        static constexpr internal::Ability_impl SuperLuck{EnumType::SuperLuck};
        static constexpr internal::Ability_impl Aftermath{EnumType::Aftermath};
        static constexpr internal::Ability_impl Anticipation{EnumType::Anticipation};
        static constexpr internal::Ability_impl Forewarn{EnumType::Forewarn};
        static constexpr internal::Ability_impl Unaware{EnumType::Unaware};
        static constexpr internal::Ability_impl TintedLens{EnumType::TintedLens};
        static constexpr internal::Ability_impl Filter{EnumType::Filter};
        static constexpr internal::Ability_impl SlowStart{EnumType::SlowStart};
        static constexpr internal::Ability_impl Scrappy{EnumType::Scrappy};
        static constexpr internal::Ability_impl StormDrain{EnumType::StormDrain};
        static constexpr internal::Ability_impl IceBody{EnumType::IceBody};
        static constexpr internal::Ability_impl SolidRock{EnumType::SolidRock};
        static constexpr internal::Ability_impl SnowWarning{EnumType::SnowWarning};
        static constexpr internal::Ability_impl HoneyGather{EnumType::HoneyGather};
        static constexpr internal::Ability_impl Frisk{EnumType::Frisk};
        static constexpr internal::Ability_impl Reckless{EnumType::Reckless};
        static constexpr internal::Ability_impl Multitype{EnumType::Multitype};
        static constexpr internal::Ability_impl FlowerGift{EnumType::FlowerGift};
        static constexpr internal::Ability_impl BadDreams{EnumType::BadDreams};
        static constexpr internal::Ability_impl Pickpocket{EnumType::Pickpocket};
        static constexpr internal::Ability_impl SheerForce{EnumType::SheerForce};
        static constexpr internal::Ability_impl Contrary{EnumType::Contrary};
        static constexpr internal::Ability_impl Unnerve{EnumType::Unnerve};
        static constexpr internal::Ability_impl Defiant{EnumType::Defiant};
        static constexpr internal::Ability_impl Defeatist{EnumType::Defeatist};
        static constexpr internal::Ability_impl CursedBody{EnumType::CursedBody};
        static constexpr internal::Ability_impl Healer{EnumType::Healer};
        static constexpr internal::Ability_impl FriendGuard{EnumType::FriendGuard};
        static constexpr internal::Ability_impl WeakArmor{EnumType::WeakArmor};
        static constexpr internal::Ability_impl HeavyMetal{EnumType::HeavyMetal};
        static constexpr internal::Ability_impl LightMetal{EnumType::LightMetal};
        static constexpr internal::Ability_impl Multiscale{EnumType::Multiscale};
        static constexpr internal::Ability_impl ToxicBoost{EnumType::ToxicBoost};
        static constexpr internal::Ability_impl FlareBoost{EnumType::FlareBoost};
        static constexpr internal::Ability_impl Harvest{EnumType::Harvest};
        static constexpr internal::Ability_impl Telepathy{EnumType::Telepathy};
        static constexpr internal::Ability_impl Moody{EnumType::Moody};
        static constexpr internal::Ability_impl Overcoat{EnumType::Overcoat};
        static constexpr internal::Ability_impl PoisonTouch{EnumType::PoisonTouch};
        static constexpr internal::Ability_impl Regenerator{EnumType::Regenerator};
        static constexpr internal::Ability_impl BigPecks{EnumType::BigPecks};
        static constexpr internal::Ability_impl SandRush{EnumType::SandRush};
        static constexpr internal::Ability_impl WonderSkin{EnumType::WonderSkin};
        static constexpr internal::Ability_impl Analytic{EnumType::Analytic};
        static constexpr internal::Ability_impl Illusion{EnumType::Illusion};
        static constexpr internal::Ability_impl Imposter{EnumType::Imposter};
        static constexpr internal::Ability_impl Infiltrator{EnumType::Infiltrator};
        static constexpr internal::Ability_impl Mummy{EnumType::Mummy};
        static constexpr internal::Ability_impl Moxie{EnumType::Moxie};
        static constexpr internal::Ability_impl Justified{EnumType::Justified};
        static constexpr internal::Ability_impl Rattled{EnumType::Rattled};
        static constexpr internal::Ability_impl MagicBounce{EnumType::MagicBounce};
        static constexpr internal::Ability_impl SapSipper{EnumType::SapSipper};
        static constexpr internal::Ability_impl Prankster{EnumType::Prankster};
        static constexpr internal::Ability_impl SandForce{EnumType::SandForce};
        static constexpr internal::Ability_impl IronBarbs{EnumType::IronBarbs};
        static constexpr internal::Ability_impl ZenMode{EnumType::ZenMode};
        static constexpr internal::Ability_impl VictoryStar{EnumType::VictoryStar};
        static constexpr internal::Ability_impl Turboblaze{EnumType::Turboblaze};
        static constexpr internal::Ability_impl Teravolt{EnumType::Teravolt};
        static constexpr internal::Ability_impl AromaVeil{EnumType::AromaVeil};
        static constexpr internal::Ability_impl FlowerVeil{EnumType::FlowerVeil};
        static constexpr internal::Ability_impl CheekPouch{EnumType::CheekPouch};
        static constexpr internal::Ability_impl Protean{EnumType::Protean};
        static constexpr internal::Ability_impl FurCoat{EnumType::FurCoat};
        static constexpr internal::Ability_impl Magician{EnumType::Magician};
        static constexpr internal::Ability_impl Bulletproof{EnumType::Bulletproof};
        static constexpr internal::Ability_impl Competitive{EnumType::Competitive};
        static constexpr internal::Ability_impl StrongJaw{EnumType::StrongJaw};
        static constexpr internal::Ability_impl Refrigerate{EnumType::Refrigerate};
        static constexpr internal::Ability_impl SweetVeil{EnumType::SweetVeil};
        static constexpr internal::Ability_impl StanceChange{EnumType::StanceChange};
        static constexpr internal::Ability_impl GaleWings{EnumType::GaleWings};
        static constexpr internal::Ability_impl MegaLauncher{EnumType::MegaLauncher};
        static constexpr internal::Ability_impl GrassPelt{EnumType::GrassPelt};
        static constexpr internal::Ability_impl Symbiosis{EnumType::Symbiosis};
        static constexpr internal::Ability_impl ToughClaws{EnumType::ToughClaws};
        static constexpr internal::Ability_impl Pixilate{EnumType::Pixilate};
        static constexpr internal::Ability_impl Gooey{EnumType::Gooey};
        static constexpr internal::Ability_impl Aerilate{EnumType::Aerilate};
        static constexpr internal::Ability_impl ParentalBond{EnumType::ParentalBond};
        static constexpr internal::Ability_impl DarkAura{EnumType::DarkAura};
        static constexpr internal::Ability_impl FairyAura{EnumType::FairyAura};
        static constexpr internal::Ability_impl AuraBreak{EnumType::AuraBreak};
        static constexpr internal::Ability_impl PrimordialSea{EnumType::PrimordialSea};
        static constexpr internal::Ability_impl DesolateLand{EnumType::DesolateLand};
        static constexpr internal::Ability_impl DeltaStream{EnumType::DeltaStream};
        static constexpr internal::Ability_impl Stamina{EnumType::Stamina};
        static constexpr internal::Ability_impl WimpOut{EnumType::WimpOut};
        static constexpr internal::Ability_impl EmergencyExit{EnumType::EmergencyExit};
        static constexpr internal::Ability_impl WaterCompaction{EnumType::WaterCompaction};
        static constexpr internal::Ability_impl Merciless{EnumType::Merciless};
        static constexpr internal::Ability_impl ShieldsDown{EnumType::ShieldsDown};
        static constexpr internal::Ability_impl Stakeout{EnumType::Stakeout};
        static constexpr internal::Ability_impl WaterBubble{EnumType::WaterBubble};
        static constexpr internal::Ability_impl Steelworker{EnumType::Steelworker};
        static constexpr internal::Ability_impl Berserk{EnumType::Berserk};
        static constexpr internal::Ability_impl SlushRush{EnumType::SlushRush};
        static constexpr internal::Ability_impl LongReach{EnumType::LongReach};
        static constexpr internal::Ability_impl LiquidVoice{EnumType::LiquidVoice};
        static constexpr internal::Ability_impl Triage{EnumType::Triage};
        static constexpr internal::Ability_impl Galvanize{EnumType::Galvanize};
        static constexpr internal::Ability_impl SurgeSurfer{EnumType::SurgeSurfer};
        static constexpr internal::Ability_impl Schooling{EnumType::Schooling};
        static constexpr internal::Ability_impl Disguise{EnumType::Disguise};
        static constexpr internal::Ability_impl BattleBond{EnumType::BattleBond};
        static constexpr internal::Ability_impl PowerConstruct{EnumType::PowerConstruct};
        static constexpr internal::Ability_impl Corrosion{EnumType::Corrosion};
        static constexpr internal::Ability_impl Comatose{EnumType::Comatose};
        static constexpr internal::Ability_impl QueenlyMajesty{EnumType::QueenlyMajesty};
        static constexpr internal::Ability_impl InnardsOut{EnumType::InnardsOut};
        static constexpr internal::Ability_impl Dancer{EnumType::Dancer};
        static constexpr internal::Ability_impl Battery{EnumType::Battery};
        static constexpr internal::Ability_impl Fluffy{EnumType::Fluffy};
        static constexpr internal::Ability_impl Dazzling{EnumType::Dazzling};
        static constexpr internal::Ability_impl SoulHeart{EnumType::SoulHeart};
        static constexpr internal::Ability_impl TanglingHair{EnumType::TanglingHair};
        static constexpr internal::Ability_impl Receiver{EnumType::Receiver};
        static constexpr internal::Ability_impl PowerofAlchemy{EnumType::PowerofAlchemy};
        static constexpr internal::Ability_impl BeastBoost{EnumType::BeastBoost};
        static constexpr internal::Ability_impl RKSSystem{EnumType::RKSSystem};
        static constexpr internal::Ability_impl ElectricSurge{EnumType::ElectricSurge};
        static constexpr internal::Ability_impl PsychicSurge{EnumType::PsychicSurge};
        static constexpr internal::Ability_impl MistySurge{EnumType::MistySurge};
        static constexpr internal::Ability_impl GrassySurge{EnumType::GrassySurge};
        static constexpr internal::Ability_impl FullMetalBody{EnumType::FullMetalBody};
        static constexpr internal::Ability_impl ShadowShield{EnumType::ShadowShield};
        static constexpr internal::Ability_impl PrismArmor{EnumType::PrismArmor};
        static constexpr internal::Ability_impl Neuroforce{EnumType::Neuroforce};
        static constexpr internal::Ability_impl IntrepidSword{EnumType::IntrepidSword};
        static constexpr internal::Ability_impl DauntlessShield{EnumType::DauntlessShield};
        static constexpr internal::Ability_impl Libero{EnumType::Libero};
        static constexpr internal::Ability_impl BallFetch{EnumType::BallFetch};
        static constexpr internal::Ability_impl CottonDown{EnumType::CottonDown};
        static constexpr internal::Ability_impl PropellerTail{EnumType::PropellerTail};
        static constexpr internal::Ability_impl MirrorArmor{EnumType::MirrorArmor};
        static constexpr internal::Ability_impl GulpMissile{EnumType::GulpMissile};
        static constexpr internal::Ability_impl Stalwart{EnumType::Stalwart};
        static constexpr internal::Ability_impl SteamEngine{EnumType::SteamEngine};
        static constexpr internal::Ability_impl PunkRock{EnumType::PunkRock};
        static constexpr internal::Ability_impl SandSpit{EnumType::SandSpit};
        static constexpr internal::Ability_impl IceScales{EnumType::IceScales};
        static constexpr internal::Ability_impl Ripen{EnumType::Ripen};
        static constexpr internal::Ability_impl IceFace{EnumType::IceFace};
        static constexpr internal::Ability_impl PowerSpot{EnumType::PowerSpot};
        static constexpr internal::Ability_impl Mimicry{EnumType::Mimicry};
        static constexpr internal::Ability_impl ScreenCleaner{EnumType::ScreenCleaner};
        static constexpr internal::Ability_impl SteelySpirit{EnumType::SteelySpirit};
        static constexpr internal::Ability_impl PerishBody{EnumType::PerishBody};
        static constexpr internal::Ability_impl WanderingSpirit{EnumType::WanderingSpirit};
        static constexpr internal::Ability_impl GorillaTactics{EnumType::GorillaTactics};
        static constexpr internal::Ability_impl NeutralizingGas{EnumType::NeutralizingGas};
        static constexpr internal::Ability_impl PastelVeil{EnumType::PastelVeil};
        static constexpr internal::Ability_impl HungerSwitch{EnumType::HungerSwitch};
        static constexpr internal::Ability_impl QuickDraw{EnumType::QuickDraw};
        static constexpr internal::Ability_impl UnseenFist{EnumType::UnseenFist};

        static constexpr internal::Ability_impl INVALID{EnumType::INVALID};
    };
}

#endif
