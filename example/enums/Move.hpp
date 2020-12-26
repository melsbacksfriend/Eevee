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

#ifndef MOVE_HPP
#define MOVE_HPP

#include "enums/Language.hpp"
#include "utils/coretypes.h"
#include <limits>
#include <type_traits>

namespace pksm
{
    class Move;

    namespace internal
    {
        class Move_impl
        {
            friend class pksm::Move;

        private:
            enum class MoveEnum : u16
            {
                None,
                Pound,
                KarateChop,
                DoubleSlap,
                CometPunch,
                MegaPunch,
                PayDay,
                FirePunch,
                IcePunch,
                ThunderPunch,
                Scratch,
                ViseGrip,
                Guillotine,
                RazorWind,
                SwordsDance,
                Cut,
                Gust,
                WingAttack,
                Whirlwind,
                Fly,
                Bind,
                Slam,
                VineWhip,
                Stomp,
                DoubleKick,
                MegaKick,
                JumpKick,
                RollingKick,
                SandAttack,
                Headbutt,
                HornAttack,
                FuryAttack,
                HornDrill,
                Tackle,
                BodySlam,
                Wrap,
                TakeDown,
                Thrash,
                DoubleEdge,
                TailWhip,
                PoisonSting,
                Twineedle,
                PinMissile,
                Leer,
                Bite,
                Growl,
                Roar,
                Sing,
                Supersonic,
                SonicBoom,
                Disable,
                Acid,
                Ember,
                Flamethrower,
                Mist,
                WaterGun,
                HydroPump,
                Surf,
                IceBeam,
                Blizzard,
                Psybeam,
                BubbleBeam,
                AuroraBeam,
                HyperBeam,
                Peck,
                DrillPeck,
                Submission,
                LowKick,
                Counter,
                SeismicToss,
                Strength,
                Absorb,
                MegaDrain,
                LeechSeed,
                Growth,
                RazorLeaf,
                SolarBeam,
                PoisonPowder,
                StunSpore,
                SleepPowder,
                PetalDance,
                StringShot,
                DragonRage,
                FireSpin,
                ThunderShock,
                Thunderbolt,
                ThunderWave,
                Thunder,
                RockThrow,
                Earthquake,
                Fissure,
                Dig,
                Toxic,
                Confusion,
                Psychic,
                Hypnosis,
                Meditate,
                Agility,
                QuickAttack,
                Rage,
                Teleport,
                NightShade,
                Mimic,
                Screech,
                DoubleTeam,
                Recover,
                Harden,
                Minimize,
                Smokescreen,
                ConfuseRay,
                Withdraw,
                DefenseCurl,
                Barrier,
                LightScreen,
                Haze,
                Reflect,
                FocusEnergy,
                Bide,
                Metronome,
                MirrorMove,
                SelfDestruct,
                EggBomb,
                Lick,
                Smog,
                Sludge,
                BoneClub,
                FireBlast,
                Waterfall,
                Clamp,
                Swift,
                SkullBash,
                SpikeCannon,
                Constrict,
                Amnesia,
                Kinesis,
                SoftBoiled,
                HighJumpKick,
                Glare,
                DreamEater,
                PoisonGas,
                Barrage,
                LeechLife,
                LovelyKiss,
                SkyAttack,
                Transform,
                Bubble,
                DizzyPunch,
                Spore,
                Flash,
                Psywave,
                Splash,
                AcidArmor,
                Crabhammer,
                Explosion,
                FurySwipes,
                Bonemerang,
                Rest,
                RockSlide,
                HyperFang,
                Sharpen,
                Conversion,
                TriAttack,
                SuperFang,
                Slash,
                Substitute,
                Struggle,
                Sketch,
                TripleKick,
                Thief,
                SpiderWeb,
                MindReader,
                Nightmare,
                FlameWheel,
                Snore,
                Curse,
                Flail,
                Conversion2,
                Aeroblast,
                CottonSpore,
                Reversal,
                Spite,
                PowderSnow,
                Protect,
                MachPunch,
                ScaryFace,
                FeintAttack,
                SweetKiss,
                BellyDrum,
                SludgeBomb,
                MudSlap,
                Octazooka,
                Spikes,
                ZapCannon,
                Foresight,
                DestinyBond,
                PerishSong,
                IcyWind,
                Detect,
                BoneRush,
                LockOn,
                Outrage,
                Sandstorm,
                GigaDrain,
                Endure,
                Charm,
                Rollout,
                FalseSwipe,
                Swagger,
                MilkDrink,
                Spark,
                FuryCutter,
                SteelWing,
                MeanLook,
                Attract,
                SleepTalk,
                HealBell,
                Return,
                Present,
                Frustration,
                Safeguard,
                PainSplit,
                SacredFire,
                Magnitude,
                DynamicPunch,
                Megahorn,
                DragonBreath,
                BatonPass,
                Encore,
                Pursuit,
                RapidSpin,
                SweetScent,
                IronTail,
                MetalClaw,
                VitalThrow,
                MorningSun,
                Synthesis,
                Moonlight,
                HiddenPower,
                CrossChop,
                Twister,
                RainDance,
                SunnyDay,
                Crunch,
                MirrorCoat,
                PsychUp,
                ExtremeSpeed,
                AncientPower,
                ShadowBall,
                FutureSight,
                RockSmash,
                Whirlpool,
                BeatUp,
                FakeOut,
                Uproar,
                Stockpile,
                SpitUp,
                Swallow,
                HeatWave,
                Hail,
                Torment,
                Flatter,
                WillOWisp,
                Memento,
                Facade,
                FocusPunch,
                SmellingSalts,
                FollowMe,
                NaturePower,
                Charge,
                Taunt,
                HelpingHand,
                Trick,
                RolePlay,
                Wish,
                Assist,
                Ingrain,
                Superpower,
                MagicCoat,
                Recycle,
                Revenge,
                BrickBreak,
                Yawn,
                KnockOff,
                Endeavor,
                Eruption,
                SkillSwap,
                Imprison,
                Refresh,
                Grudge,
                Snatch,
                SecretPower,
                Dive,
                ArmThrust,
                Camouflage,
                TailGlow,
                LusterPurge,
                MistBall,
                FeatherDance,
                TeeterDance,
                BlazeKick,
                MudSport,
                IceBall,
                NeedleArm,
                SlackOff,
                HyperVoice,
                PoisonFang,
                CrushClaw,
                BlastBurn,
                HydroCannon,
                MeteorMash,
                Astonish,
                WeatherBall,
                Aromatherapy,
                FakeTears,
                AirCutter,
                Overheat,
                OdorSleuth,
                RockTomb,
                SilverWind,
                MetalSound,
                GrassWhistle,
                Tickle,
                CosmicPower,
                WaterSpout,
                SignalBeam,
                ShadowPunch,
                Extrasensory,
                SkyUppercut,
                SandTomb,
                SheerCold,
                MuddyWater,
                BulletSeed,
                AerialAce,
                IcicleSpear,
                IronDefense,
                Block,
                Howl,
                DragonClaw,
                FrenzyPlant,
                BulkUp,
                Bounce,
                MudShot,
                PoisonTail,
                Covet,
                VoltTackle,
                MagicalLeaf,
                WaterSport,
                CalmMind,
                LeafBlade,
                DragonDance,
                RockBlast,
                ShockWave,
                WaterPulse,
                DoomDesire,
                PsychoBoost,
                Roost,
                Gravity,
                MiracleEye,
                WakeUpSlap,
                HammerArm,
                GyroBall,
                HealingWish,
                Brine,
                NaturalGift,
                Feint,
                Pluck,
                Tailwind,
                Acupressure,
                MetalBurst,
                Uturn,
                CloseCombat,
                Payback,
                Assurance,
                Embargo,
                Fling,
                PsychoShift,
                TrumpCard,
                HealBlock,
                WringOut,
                PowerTrick,
                GastroAcid,
                LuckyChant,
                MeFirst,
                Copycat,
                PowerSwap,
                GuardSwap,
                Punishment,
                LastResort,
                WorrySeed,
                SuckerPunch,
                ToxicSpikes,
                HeartSwap,
                AquaRing,
                MagnetRise,
                FlareBlitz,
                ForcePalm,
                AuraSphere,
                RockPolish,
                PoisonJab,
                DarkPulse,
                NightSlash,
                AquaTail,
                SeedBomb,
                AirSlash,
                XScissor,
                BugBuzz,
                DragonPulse,
                DragonRush,
                PowerGem,
                DrainPunch,
                VacuumWave,
                FocusBlast,
                EnergyBall,
                BraveBird,
                EarthPower,
                Switcheroo,
                GigaImpact,
                NastyPlot,
                BulletPunch,
                Avalanche,
                IceShard,
                ShadowClaw,
                ThunderFang,
                IceFang,
                FireFang,
                ShadowSneak,
                MudBomb,
                PsychoCut,
                ZenHeadbutt,
                MirrorShot,
                FlashCannon,
                RockClimb,
                Defog,
                TrickRoom,
                DracoMeteor,
                Discharge,
                LavaPlume,
                LeafStorm,
                PowerWhip,
                RockWrecker,
                CrossPoison,
                GunkShot,
                IronHead,
                MagnetBomb,
                StoneEdge,
                Captivate,
                StealthRock,
                GrassKnot,
                Chatter,
                Judgment,
                BugBite,
                ChargeBeam,
                WoodHammer,
                AquaJet,
                AttackOrder,
                DefendOrder,
                HealOrder,
                HeadSmash,
                DoubleHit,
                RoarofTime,
                SpacialRend,
                LunarDance,
                CrushGrip,
                MagmaStorm,
                DarkVoid,
                SeedFlare,
                OminousWind,
                ShadowForce,
                HoneClaws,
                WideGuard,
                GuardSplit,
                PowerSplit,
                WonderRoom,
                Psyshock,
                Venoshock,
                Autotomize,
                RagePowder,
                Telekinesis,
                MagicRoom,
                SmackDown,
                StormThrow,
                FlameBurst,
                SludgeWave,
                QuiverDance,
                HeavySlam,
                Synchronoise,
                ElectroBall,
                Soak,
                FlameCharge,
                Coil,
                LowSweep,
                AcidSpray,
                FoulPlay,
                SimpleBeam,
                Entrainment,
                AfterYou,
                Round,
                EchoedVoice,
                ChipAway,
                ClearSmog,
                StoredPower,
                QuickGuard,
                AllySwitch,
                Scald,
                ShellSmash,
                HealPulse,
                Hex,
                SkyDrop,
                ShiftGear,
                CircleThrow,
                Incinerate,
                Quash,
                Acrobatics,
                ReflectType,
                Retaliate,
                FinalGambit,
                Bestow,
                Inferno,
                WaterPledge,
                FirePledge,
                GrassPledge,
                VoltSwitch,
                StruggleBug,
                Bulldoze,
                FrostBreath,
                DragonTail,
                WorkUp,
                Electroweb,
                WildCharge,
                DrillRun,
                DualChop,
                HeartStamp,
                HornLeech,
                SacredSword,
                RazorShell,
                HeatCrash,
                LeafTornado,
                Steamroller,
                CottonGuard,
                NightDaze,
                Psystrike,
                TailSlap,
                Hurricane,
                HeadCharge,
                GearGrind,
                SearingShot,
                TechnoBlast,
                RelicSong,
                SecretSword,
                Glaciate,
                BoltStrike,
                BlueFlare,
                FieryDance,
                FreezeShock,
                IceBurn,
                Snarl,
                IcicleCrash,
                Vcreate,
                FusionFlare,
                FusionBolt,
                FlyingPress,
                MatBlock,
                Belch,
                Rototiller,
                StickyWeb,
                FellStinger,
                PhantomForce,
                TrickorTreat,
                NobleRoar,
                IonDeluge,
                ParabolicCharge,
                ForestsCurse,
                PetalBlizzard,
                FreezeDry,
                DisarmingVoice,
                PartingShot,
                TopsyTurvy,
                DrainingKiss,
                CraftyShield,
                FlowerShield,
                GrassyTerrain,
                MistyTerrain,
                Electrify,
                PlayRough,
                FairyWind,
                Moonblast,
                Boomburst,
                FairyLock,
                KingsShield,
                PlayNice,
                Confide,
                DiamondStorm,
                SteamEruption,
                HyperspaceHole,
                WaterShuriken,
                MysticalFire,
                SpikyShield,
                AromaticMist,
                EerieImpulse,
                VenomDrench,
                Powder,
                Geomancy,
                MagneticFlux,
                HappyHour,
                ElectricTerrain,
                DazzlingGleam,
                Celebrate,
                HoldHands,
                BabyDollEyes,
                Nuzzle,
                HoldBack,
                Infestation,
                PowerUpPunch,
                OblivionWing,
                ThousandArrows,
                ThousandWaves,
                LandsWrath,
                LightofRuin,
                OriginPulse,
                PrecipiceBlades,
                DragonAscent,
                HyperspaceFury,
                BreakneckBlitzA,
                BreakneckBlitzB,
                AllOutPummelingA,
                AllOutPummelingB,
                SupersonicSkystrikeA,
                SupersonicSkystrikeB,
                AcidDownpourA,
                AcidDownpourB,
                TectonicRageA,
                TectonicRageB,
                ContinentalCrushA,
                ContinentalCrushB,
                SavageSpinOutA,
                SavageSpinOutB,
                NeverEndingNightmareA,
                NeverEndingNightmareB,
                CorkscrewCrashA,
                CorkscrewCrashB,
                InfernoOverdriveA,
                InfernoOverdriveB,
                HydroVortexA,
                HydroVortexB,
                BloomDoomA,
                BloomDoomB,
                GigavoltHavocA,
                GigavoltHavocB,
                ShatteredPsycheA,
                ShatteredPsycheB,
                SubzeroSlammerA,
                SubzeroSlammerB,
                DevastatingDrakeA,
                DevastatingDrakeB,
                BlackHoleEclipseA,
                BlackHoleEclipseB,
                TwinkleTackleA,
                TwinkleTackleB,
                Catastropika,
                ShoreUp,
                FirstImpression,
                BanefulBunker,
                SpiritShackle,
                DarkestLariat,
                SparklingAria,
                IceHammer,
                FloralHealing,
                HighHorsepower,
                StrengthSap,
                SolarBlade,
                Leafage,
                Spotlight,
                ToxicThread,
                LaserFocus,
                GearUp,
                ThroatChop,
                PollenPuff,
                AnchorShot,
                PsychicTerrain,
                Lunge,
                FireLash,
                PowerTrip,
                BurnUp,
                SpeedSwap,
                SmartStrike,
                Purify,
                RevelationDance,
                CoreEnforcer,
                TropKick,
                Instruct,
                BeakBlast,
                ClangingScales,
                DragonHammer,
                BrutalSwing,
                AuroraVeil,
                SinisterArrowRaid,
                MaliciousMoonsault,
                OceanicOperetta,
                GuardianofAlola,
                SoulStealing7StarStrike,
                StokedSparksurfer,
                PulverizingPancake,
                ExtremeEvoboost,
                GenesisSupernova,
                ShellTrap,
                FleurCannon,
                PsychicFangs,
                StompingTantrum,
                ShadowBone,
                Accelerock,
                Liquidation,
                PrismaticLaser,
                SpectralThief,
                SunsteelStrike,
                MoongeistBeam,
                TearfulLook,
                ZingZap,
                NaturesMadness,
                MultiAttack,
                TenMillionVoltThunderbolt,
                MindBlown,
                PlasmaFists,
                PhotonGeyser,
                LightThatBurnstheSky,
                SearingSunrazeSmash,
                MenacingMoonrazeMaelstrom,
                LetsSnuggleForever,
                SplinteredStormshards,
                ClangorousSoulblaze,
                ZippyZap,
                SplishySplash,
                FloatyFall,
                PikaPapow,
                BouncyBubble,
                BuzzyBuzz,
                SizzlySlide,
                GlitzyGlow,
                BaddyBad,
                SappySeed,
                FreezyFrost,
                SparklySwirl,
                VeeveeVolley,
                DoubleIronBash,
                MaxGuard,
                DynamaxCannon,
                SnipeShot,
                JawLock,
                StuffCheeks,
                NoRetreat,
                TarShot,
                MagicPowder,
                DragonDarts,
                Teatime,
                Octolock,
                BoltBeak,
                FishiousRend,
                CourtChange,
                MaxFlare,
                MaxFlutterby,
                MaxLightning,
                MaxStrike,
                MaxKnuckle,
                MaxPhantasm,
                MaxHailstorm,
                MaxOoze,
                MaxGeyser,
                MaxAirstream,
                MaxStarfall,
                MaxWyrmwind,
                MaxMindstorm,
                MaxRockfall,
                MaxQuake,
                MaxDarkness,
                MaxOvergrowth,
                MaxSteelspike,
                ClangorousSoul,
                BodyPress,
                Decorate,
                DrumBeating,
                SnapTrap,
                PyroBall,
                BehemothBlade,
                BehemothBash,
                AuraWheel,
                BreakingSwipe,
                BranchPoke,
                Overdrive,
                AppleAcid,
                GravApple,
                SpiritBreak,
                StrangeSteam,
                LifeDew,
                Obstruct,
                FalseSurrender,
                MeteorAssault,
                Eternabeam,
                SteelBeam,
                ExpandingForce,
                SteelRoller,
                ScaleShot,
                MeteorBeam,
                ShellSideArm,
                MistyExplosion,
                GrassyGlide,
                RisingVoltage,
                TerrainPulse,
                SkitterSmack,
                BurningJealousy,
                LashOut,
                Poltergeist,
                CorrosiveGas,
                Coaching,
                FlipTurn,
                TripleAxel,
                DualWingbeat,
                ScorchingSands,
                JungleHealing,
                WickedBlow,
                SurgingStrikes,

                INVALID [[maybe_unused]] =
                    std::numeric_limits<std::underlying_type_t<MoveEnum>>::max()
            } v;

            constexpr explicit Move_impl(MoveEnum v) : v(v) {}
            constexpr Move_impl(const Move_impl&) = default;
            constexpr Move_impl(Move_impl&&)      = default;
            constexpr Move_impl& operator=(const Move_impl&) = default;
            constexpr Move_impl& operator=(Move_impl&&) = default;

        public:
            template <typename T>
            constexpr explicit operator T() const noexcept
            {
                static_assert(std::is_integral_v<T>);
                return T(v);
            }
            constexpr operator MoveEnum() const noexcept { return v; }

            constexpr bool operator<(const Move_impl& other) const noexcept { return v < other.v; }
            constexpr bool operator<=(const Move_impl& other) const noexcept
            {
                return v <= other.v;
            }

            constexpr bool operator>(const Move_impl& other) const noexcept { return v > other.v; }
            constexpr bool operator>=(const Move_impl& other) const noexcept
            {
                return v >= other.v;
            }

            constexpr bool operator==(const Move_impl& other) const noexcept
            {
                return v == other.v;
            }
            constexpr bool operator!=(const Move_impl& other) const noexcept
            {
                return v != other.v;
            }

            const std::string& localize(Language lang) const;
        };
    }

    class Move
    {
    private:
        internal::Move_impl impl;

    public:
        using EnumType = internal::Move_impl::MoveEnum;
        constexpr Move() noexcept : impl(EnumType::INVALID) {}
        constexpr Move(const internal::Move_impl& impl) noexcept : impl(impl) {}
        constexpr explicit Move(std::underlying_type_t<EnumType> v) noexcept : impl(EnumType{v}) {}
        template <typename T>
        constexpr explicit operator T() const noexcept
        {
            static_assert(std::is_integral_v<T>);
            return T(impl);
        }
        constexpr operator EnumType() const noexcept { return static_cast<EnumType>(impl); }

        constexpr bool operator<(const Move& other) const noexcept { return impl < other.impl; }
        constexpr bool operator<=(const Move& other) const noexcept { return impl <= other.impl; }

        constexpr bool operator>(const Move& other) const noexcept { return impl > other.impl; }
        constexpr bool operator>=(const Move& other) const noexcept { return impl >= other.impl; }

        constexpr bool operator==(const Move& other) const noexcept { return impl == other.impl; }
        constexpr bool operator!=(const Move& other) const noexcept { return impl != other.impl; }

        constexpr bool operator<(const internal::Move_impl& other) const noexcept
        {
            return impl < other;
        }
        constexpr bool operator<=(const internal::Move_impl& other) const noexcept
        {
            return impl <= other;
        }

        constexpr bool operator>(const internal::Move_impl& other) const noexcept
        {
            return impl > other;
        }
        constexpr bool operator>=(const internal::Move_impl& other) const noexcept
        {
            return impl >= other;
        }

        constexpr bool operator==(const internal::Move_impl& other) const noexcept
        {
            return impl == other;
        }
        constexpr bool operator!=(const internal::Move_impl& other) const noexcept
        {
            return impl != other;
        }

        const std::string& localize(Language lang) const { return impl.localize(lang); }

        static constexpr internal::Move_impl None{EnumType::None};
        static constexpr internal::Move_impl Pound{EnumType::Pound};
        static constexpr internal::Move_impl KarateChop{EnumType::KarateChop};
        static constexpr internal::Move_impl DoubleSlap{EnumType::DoubleSlap};
        static constexpr internal::Move_impl CometPunch{EnumType::CometPunch};
        static constexpr internal::Move_impl MegaPunch{EnumType::MegaPunch};
        static constexpr internal::Move_impl PayDay{EnumType::PayDay};
        static constexpr internal::Move_impl FirePunch{EnumType::FirePunch};
        static constexpr internal::Move_impl IcePunch{EnumType::IcePunch};
        static constexpr internal::Move_impl ThunderPunch{EnumType::ThunderPunch};
        static constexpr internal::Move_impl Scratch{EnumType::Scratch};
        static constexpr internal::Move_impl ViseGrip{EnumType::ViseGrip};
        static constexpr internal::Move_impl Guillotine{EnumType::Guillotine};
        static constexpr internal::Move_impl RazorWind{EnumType::RazorWind};
        static constexpr internal::Move_impl SwordsDance{EnumType::SwordsDance};
        static constexpr internal::Move_impl Cut{EnumType::Cut};
        static constexpr internal::Move_impl Gust{EnumType::Gust};
        static constexpr internal::Move_impl WingAttack{EnumType::WingAttack};
        static constexpr internal::Move_impl Whirlwind{EnumType::Whirlwind};
        static constexpr internal::Move_impl Fly{EnumType::Fly};
        static constexpr internal::Move_impl Bind{EnumType::Bind};
        static constexpr internal::Move_impl Slam{EnumType::Slam};
        static constexpr internal::Move_impl VineWhip{EnumType::VineWhip};
        static constexpr internal::Move_impl Stomp{EnumType::Stomp};
        static constexpr internal::Move_impl DoubleKick{EnumType::DoubleKick};
        static constexpr internal::Move_impl MegaKick{EnumType::MegaKick};
        static constexpr internal::Move_impl JumpKick{EnumType::JumpKick};
        static constexpr internal::Move_impl RollingKick{EnumType::RollingKick};
        static constexpr internal::Move_impl SandAttack{EnumType::SandAttack};
        static constexpr internal::Move_impl Headbutt{EnumType::Headbutt};
        static constexpr internal::Move_impl HornAttack{EnumType::HornAttack};
        static constexpr internal::Move_impl FuryAttack{EnumType::FuryAttack};
        static constexpr internal::Move_impl HornDrill{EnumType::HornDrill};
        static constexpr internal::Move_impl Tackle{EnumType::Tackle};
        static constexpr internal::Move_impl BodySlam{EnumType::BodySlam};
        static constexpr internal::Move_impl Wrap{EnumType::Wrap};
        static constexpr internal::Move_impl TakeDown{EnumType::TakeDown};
        static constexpr internal::Move_impl Thrash{EnumType::Thrash};
        static constexpr internal::Move_impl DoubleEdge{EnumType::DoubleEdge};
        static constexpr internal::Move_impl TailWhip{EnumType::TailWhip};
        static constexpr internal::Move_impl PoisonSting{EnumType::PoisonSting};
        static constexpr internal::Move_impl Twineedle{EnumType::Twineedle};
        static constexpr internal::Move_impl PinMissile{EnumType::PinMissile};
        static constexpr internal::Move_impl Leer{EnumType::Leer};
        static constexpr internal::Move_impl Bite{EnumType::Bite};
        static constexpr internal::Move_impl Growl{EnumType::Growl};
        static constexpr internal::Move_impl Roar{EnumType::Roar};
        static constexpr internal::Move_impl Sing{EnumType::Sing};
        static constexpr internal::Move_impl Supersonic{EnumType::Supersonic};
        static constexpr internal::Move_impl SonicBoom{EnumType::SonicBoom};
        static constexpr internal::Move_impl Disable{EnumType::Disable};
        static constexpr internal::Move_impl Acid{EnumType::Acid};
        static constexpr internal::Move_impl Ember{EnumType::Ember};
        static constexpr internal::Move_impl Flamethrower{EnumType::Flamethrower};
        static constexpr internal::Move_impl Mist{EnumType::Mist};
        static constexpr internal::Move_impl WaterGun{EnumType::WaterGun};
        static constexpr internal::Move_impl HydroPump{EnumType::HydroPump};
        static constexpr internal::Move_impl Surf{EnumType::Surf};
        static constexpr internal::Move_impl IceBeam{EnumType::IceBeam};
        static constexpr internal::Move_impl Blizzard{EnumType::Blizzard};
        static constexpr internal::Move_impl Psybeam{EnumType::Psybeam};
        static constexpr internal::Move_impl BubbleBeam{EnumType::BubbleBeam};
        static constexpr internal::Move_impl AuroraBeam{EnumType::AuroraBeam};
        static constexpr internal::Move_impl HyperBeam{EnumType::HyperBeam};
        static constexpr internal::Move_impl Peck{EnumType::Peck};
        static constexpr internal::Move_impl DrillPeck{EnumType::DrillPeck};
        static constexpr internal::Move_impl Submission{EnumType::Submission};
        static constexpr internal::Move_impl LowKick{EnumType::LowKick};
        static constexpr internal::Move_impl Counter{EnumType::Counter};
        static constexpr internal::Move_impl SeismicToss{EnumType::SeismicToss};
        static constexpr internal::Move_impl Strength{EnumType::Strength};
        static constexpr internal::Move_impl Absorb{EnumType::Absorb};
        static constexpr internal::Move_impl MegaDrain{EnumType::MegaDrain};
        static constexpr internal::Move_impl LeechSeed{EnumType::LeechSeed};
        static constexpr internal::Move_impl Growth{EnumType::Growth};
        static constexpr internal::Move_impl RazorLeaf{EnumType::RazorLeaf};
        static constexpr internal::Move_impl SolarBeam{EnumType::SolarBeam};
        static constexpr internal::Move_impl PoisonPowder{EnumType::PoisonPowder};
        static constexpr internal::Move_impl StunSpore{EnumType::StunSpore};
        static constexpr internal::Move_impl SleepPowder{EnumType::SleepPowder};
        static constexpr internal::Move_impl PetalDance{EnumType::PetalDance};
        static constexpr internal::Move_impl StringShot{EnumType::StringShot};
        static constexpr internal::Move_impl DragonRage{EnumType::DragonRage};
        static constexpr internal::Move_impl FireSpin{EnumType::FireSpin};
        static constexpr internal::Move_impl ThunderShock{EnumType::ThunderShock};
        static constexpr internal::Move_impl Thunderbolt{EnumType::Thunderbolt};
        static constexpr internal::Move_impl ThunderWave{EnumType::ThunderWave};
        static constexpr internal::Move_impl Thunder{EnumType::Thunder};
        static constexpr internal::Move_impl RockThrow{EnumType::RockThrow};
        static constexpr internal::Move_impl Earthquake{EnumType::Earthquake};
        static constexpr internal::Move_impl Fissure{EnumType::Fissure};
        static constexpr internal::Move_impl Dig{EnumType::Dig};
        static constexpr internal::Move_impl Toxic{EnumType::Toxic};
        static constexpr internal::Move_impl Confusion{EnumType::Confusion};
        static constexpr internal::Move_impl Psychic{EnumType::Psychic};
        static constexpr internal::Move_impl Hypnosis{EnumType::Hypnosis};
        static constexpr internal::Move_impl Meditate{EnumType::Meditate};
        static constexpr internal::Move_impl Agility{EnumType::Agility};
        static constexpr internal::Move_impl QuickAttack{EnumType::QuickAttack};
        static constexpr internal::Move_impl Rage{EnumType::Rage};
        static constexpr internal::Move_impl Teleport{EnumType::Teleport};
        static constexpr internal::Move_impl NightShade{EnumType::NightShade};
        static constexpr internal::Move_impl Mimic{EnumType::Mimic};
        static constexpr internal::Move_impl Screech{EnumType::Screech};
        static constexpr internal::Move_impl DoubleTeam{EnumType::DoubleTeam};
        static constexpr internal::Move_impl Recover{EnumType::Recover};
        static constexpr internal::Move_impl Harden{EnumType::Harden};
        static constexpr internal::Move_impl Minimize{EnumType::Minimize};
        static constexpr internal::Move_impl Smokescreen{EnumType::Smokescreen};
        static constexpr internal::Move_impl ConfuseRay{EnumType::ConfuseRay};
        static constexpr internal::Move_impl Withdraw{EnumType::Withdraw};
        static constexpr internal::Move_impl DefenseCurl{EnumType::DefenseCurl};
        static constexpr internal::Move_impl Barrier{EnumType::Barrier};
        static constexpr internal::Move_impl LightScreen{EnumType::LightScreen};
        static constexpr internal::Move_impl Haze{EnumType::Haze};
        static constexpr internal::Move_impl Reflect{EnumType::Reflect};
        static constexpr internal::Move_impl FocusEnergy{EnumType::FocusEnergy};
        static constexpr internal::Move_impl Bide{EnumType::Bide};
        static constexpr internal::Move_impl Metronome{EnumType::Metronome};
        static constexpr internal::Move_impl MirrorMove{EnumType::MirrorMove};
        static constexpr internal::Move_impl SelfDestruct{EnumType::SelfDestruct};
        static constexpr internal::Move_impl EggBomb{EnumType::EggBomb};
        static constexpr internal::Move_impl Lick{EnumType::Lick};
        static constexpr internal::Move_impl Smog{EnumType::Smog};
        static constexpr internal::Move_impl Sludge{EnumType::Sludge};
        static constexpr internal::Move_impl BoneClub{EnumType::BoneClub};
        static constexpr internal::Move_impl FireBlast{EnumType::FireBlast};
        static constexpr internal::Move_impl Waterfall{EnumType::Waterfall};
        static constexpr internal::Move_impl Clamp{EnumType::Clamp};
        static constexpr internal::Move_impl Swift{EnumType::Swift};
        static constexpr internal::Move_impl SkullBash{EnumType::SkullBash};
        static constexpr internal::Move_impl SpikeCannon{EnumType::SpikeCannon};
        static constexpr internal::Move_impl Constrict{EnumType::Constrict};
        static constexpr internal::Move_impl Amnesia{EnumType::Amnesia};
        static constexpr internal::Move_impl Kinesis{EnumType::Kinesis};
        static constexpr internal::Move_impl SoftBoiled{EnumType::SoftBoiled};
        static constexpr internal::Move_impl HighJumpKick{EnumType::HighJumpKick};
        static constexpr internal::Move_impl Glare{EnumType::Glare};
        static constexpr internal::Move_impl DreamEater{EnumType::DreamEater};
        static constexpr internal::Move_impl PoisonGas{EnumType::PoisonGas};
        static constexpr internal::Move_impl Barrage{EnumType::Barrage};
        static constexpr internal::Move_impl LeechLife{EnumType::LeechLife};
        static constexpr internal::Move_impl LovelyKiss{EnumType::LovelyKiss};
        static constexpr internal::Move_impl SkyAttack{EnumType::SkyAttack};
        static constexpr internal::Move_impl Transform{EnumType::Transform};
        static constexpr internal::Move_impl Bubble{EnumType::Bubble};
        static constexpr internal::Move_impl DizzyPunch{EnumType::DizzyPunch};
        static constexpr internal::Move_impl Spore{EnumType::Spore};
        static constexpr internal::Move_impl Flash{EnumType::Flash};
        static constexpr internal::Move_impl Psywave{EnumType::Psywave};
        static constexpr internal::Move_impl Splash{EnumType::Splash};
        static constexpr internal::Move_impl AcidArmor{EnumType::AcidArmor};
        static constexpr internal::Move_impl Crabhammer{EnumType::Crabhammer};
        static constexpr internal::Move_impl Explosion{EnumType::Explosion};
        static constexpr internal::Move_impl FurySwipes{EnumType::FurySwipes};
        static constexpr internal::Move_impl Bonemerang{EnumType::Bonemerang};
        static constexpr internal::Move_impl Rest{EnumType::Rest};
        static constexpr internal::Move_impl RockSlide{EnumType::RockSlide};
        static constexpr internal::Move_impl HyperFang{EnumType::HyperFang};
        static constexpr internal::Move_impl Sharpen{EnumType::Sharpen};
        static constexpr internal::Move_impl Conversion{EnumType::Conversion};
        static constexpr internal::Move_impl TriAttack{EnumType::TriAttack};
        static constexpr internal::Move_impl SuperFang{EnumType::SuperFang};
        static constexpr internal::Move_impl Slash{EnumType::Slash};
        static constexpr internal::Move_impl Substitute{EnumType::Substitute};
        static constexpr internal::Move_impl Struggle{EnumType::Struggle};
        static constexpr internal::Move_impl Sketch{EnumType::Sketch};
        static constexpr internal::Move_impl TripleKick{EnumType::TripleKick};
        static constexpr internal::Move_impl Thief{EnumType::Thief};
        static constexpr internal::Move_impl SpiderWeb{EnumType::SpiderWeb};
        static constexpr internal::Move_impl MindReader{EnumType::MindReader};
        static constexpr internal::Move_impl Nightmare{EnumType::Nightmare};
        static constexpr internal::Move_impl FlameWheel{EnumType::FlameWheel};
        static constexpr internal::Move_impl Snore{EnumType::Snore};
        static constexpr internal::Move_impl Curse{EnumType::Curse};
        static constexpr internal::Move_impl Flail{EnumType::Flail};
        static constexpr internal::Move_impl Conversion2{EnumType::Conversion2};
        static constexpr internal::Move_impl Aeroblast{EnumType::Aeroblast};
        static constexpr internal::Move_impl CottonSpore{EnumType::CottonSpore};
        static constexpr internal::Move_impl Reversal{EnumType::Reversal};
        static constexpr internal::Move_impl Spite{EnumType::Spite};
        static constexpr internal::Move_impl PowderSnow{EnumType::PowderSnow};
        static constexpr internal::Move_impl Protect{EnumType::Protect};
        static constexpr internal::Move_impl MachPunch{EnumType::MachPunch};
        static constexpr internal::Move_impl ScaryFace{EnumType::ScaryFace};
        static constexpr internal::Move_impl FeintAttack{EnumType::FeintAttack};
        static constexpr internal::Move_impl SweetKiss{EnumType::SweetKiss};
        static constexpr internal::Move_impl BellyDrum{EnumType::BellyDrum};
        static constexpr internal::Move_impl SludgeBomb{EnumType::SludgeBomb};
        static constexpr internal::Move_impl MudSlap{EnumType::MudSlap};
        static constexpr internal::Move_impl Octazooka{EnumType::Octazooka};
        static constexpr internal::Move_impl Spikes{EnumType::Spikes};
        static constexpr internal::Move_impl ZapCannon{EnumType::ZapCannon};
        static constexpr internal::Move_impl Foresight{EnumType::Foresight};
        static constexpr internal::Move_impl DestinyBond{EnumType::DestinyBond};
        static constexpr internal::Move_impl PerishSong{EnumType::PerishSong};
        static constexpr internal::Move_impl IcyWind{EnumType::IcyWind};
        static constexpr internal::Move_impl Detect{EnumType::Detect};
        static constexpr internal::Move_impl BoneRush{EnumType::BoneRush};
        static constexpr internal::Move_impl LockOn{EnumType::LockOn};
        static constexpr internal::Move_impl Outrage{EnumType::Outrage};
        static constexpr internal::Move_impl Sandstorm{EnumType::Sandstorm};
        static constexpr internal::Move_impl GigaDrain{EnumType::GigaDrain};
        static constexpr internal::Move_impl Endure{EnumType::Endure};
        static constexpr internal::Move_impl Charm{EnumType::Charm};
        static constexpr internal::Move_impl Rollout{EnumType::Rollout};
        static constexpr internal::Move_impl FalseSwipe{EnumType::FalseSwipe};
        static constexpr internal::Move_impl Swagger{EnumType::Swagger};
        static constexpr internal::Move_impl MilkDrink{EnumType::MilkDrink};
        static constexpr internal::Move_impl Spark{EnumType::Spark};
        static constexpr internal::Move_impl FuryCutter{EnumType::FuryCutter};
        static constexpr internal::Move_impl SteelWing{EnumType::SteelWing};
        static constexpr internal::Move_impl MeanLook{EnumType::MeanLook};
        static constexpr internal::Move_impl Attract{EnumType::Attract};
        static constexpr internal::Move_impl SleepTalk{EnumType::SleepTalk};
        static constexpr internal::Move_impl HealBell{EnumType::HealBell};
        static constexpr internal::Move_impl Return{EnumType::Return};
        static constexpr internal::Move_impl Present{EnumType::Present};
        static constexpr internal::Move_impl Frustration{EnumType::Frustration};
        static constexpr internal::Move_impl Safeguard{EnumType::Safeguard};
        static constexpr internal::Move_impl PainSplit{EnumType::PainSplit};
        static constexpr internal::Move_impl SacredFire{EnumType::SacredFire};
        static constexpr internal::Move_impl Magnitude{EnumType::Magnitude};
        static constexpr internal::Move_impl DynamicPunch{EnumType::DynamicPunch};
        static constexpr internal::Move_impl Megahorn{EnumType::Megahorn};
        static constexpr internal::Move_impl DragonBreath{EnumType::DragonBreath};
        static constexpr internal::Move_impl BatonPass{EnumType::BatonPass};
        static constexpr internal::Move_impl Encore{EnumType::Encore};
        static constexpr internal::Move_impl Pursuit{EnumType::Pursuit};
        static constexpr internal::Move_impl RapidSpin{EnumType::RapidSpin};
        static constexpr internal::Move_impl SweetScent{EnumType::SweetScent};
        static constexpr internal::Move_impl IronTail{EnumType::IronTail};
        static constexpr internal::Move_impl MetalClaw{EnumType::MetalClaw};
        static constexpr internal::Move_impl VitalThrow{EnumType::VitalThrow};
        static constexpr internal::Move_impl MorningSun{EnumType::MorningSun};
        static constexpr internal::Move_impl Synthesis{EnumType::Synthesis};
        static constexpr internal::Move_impl Moonlight{EnumType::Moonlight};
        static constexpr internal::Move_impl HiddenPower{EnumType::HiddenPower};
        static constexpr internal::Move_impl CrossChop{EnumType::CrossChop};
        static constexpr internal::Move_impl Twister{EnumType::Twister};
        static constexpr internal::Move_impl RainDance{EnumType::RainDance};
        static constexpr internal::Move_impl SunnyDay{EnumType::SunnyDay};
        static constexpr internal::Move_impl Crunch{EnumType::Crunch};
        static constexpr internal::Move_impl MirrorCoat{EnumType::MirrorCoat};
        static constexpr internal::Move_impl PsychUp{EnumType::PsychUp};
        static constexpr internal::Move_impl ExtremeSpeed{EnumType::ExtremeSpeed};
        static constexpr internal::Move_impl AncientPower{EnumType::AncientPower};
        static constexpr internal::Move_impl ShadowBall{EnumType::ShadowBall};
        static constexpr internal::Move_impl FutureSight{EnumType::FutureSight};
        static constexpr internal::Move_impl RockSmash{EnumType::RockSmash};
        static constexpr internal::Move_impl Whirlpool{EnumType::Whirlpool};
        static constexpr internal::Move_impl BeatUp{EnumType::BeatUp};
        static constexpr internal::Move_impl FakeOut{EnumType::FakeOut};
        static constexpr internal::Move_impl Uproar{EnumType::Uproar};
        static constexpr internal::Move_impl Stockpile{EnumType::Stockpile};
        static constexpr internal::Move_impl SpitUp{EnumType::SpitUp};
        static constexpr internal::Move_impl Swallow{EnumType::Swallow};
        static constexpr internal::Move_impl HeatWave{EnumType::HeatWave};
        static constexpr internal::Move_impl Hail{EnumType::Hail};
        static constexpr internal::Move_impl Torment{EnumType::Torment};
        static constexpr internal::Move_impl Flatter{EnumType::Flatter};
        static constexpr internal::Move_impl WillOWisp{EnumType::WillOWisp};
        static constexpr internal::Move_impl Memento{EnumType::Memento};
        static constexpr internal::Move_impl Facade{EnumType::Facade};
        static constexpr internal::Move_impl FocusPunch{EnumType::FocusPunch};
        static constexpr internal::Move_impl SmellingSalts{EnumType::SmellingSalts};
        static constexpr internal::Move_impl FollowMe{EnumType::FollowMe};
        static constexpr internal::Move_impl NaturePower{EnumType::NaturePower};
        static constexpr internal::Move_impl Charge{EnumType::Charge};
        static constexpr internal::Move_impl Taunt{EnumType::Taunt};
        static constexpr internal::Move_impl HelpingHand{EnumType::HelpingHand};
        static constexpr internal::Move_impl Trick{EnumType::Trick};
        static constexpr internal::Move_impl RolePlay{EnumType::RolePlay};
        static constexpr internal::Move_impl Wish{EnumType::Wish};
        static constexpr internal::Move_impl Assist{EnumType::Assist};
        static constexpr internal::Move_impl Ingrain{EnumType::Ingrain};
        static constexpr internal::Move_impl Superpower{EnumType::Superpower};
        static constexpr internal::Move_impl MagicCoat{EnumType::MagicCoat};
        static constexpr internal::Move_impl Recycle{EnumType::Recycle};
        static constexpr internal::Move_impl Revenge{EnumType::Revenge};
        static constexpr internal::Move_impl BrickBreak{EnumType::BrickBreak};
        static constexpr internal::Move_impl Yawn{EnumType::Yawn};
        static constexpr internal::Move_impl KnockOff{EnumType::KnockOff};
        static constexpr internal::Move_impl Endeavor{EnumType::Endeavor};
        static constexpr internal::Move_impl Eruption{EnumType::Eruption};
        static constexpr internal::Move_impl SkillSwap{EnumType::SkillSwap};
        static constexpr internal::Move_impl Imprison{EnumType::Imprison};
        static constexpr internal::Move_impl Refresh{EnumType::Refresh};
        static constexpr internal::Move_impl Grudge{EnumType::Grudge};
        static constexpr internal::Move_impl Snatch{EnumType::Snatch};
        static constexpr internal::Move_impl SecretPower{EnumType::SecretPower};
        static constexpr internal::Move_impl Dive{EnumType::Dive};
        static constexpr internal::Move_impl ArmThrust{EnumType::ArmThrust};
        static constexpr internal::Move_impl Camouflage{EnumType::Camouflage};
        static constexpr internal::Move_impl TailGlow{EnumType::TailGlow};
        static constexpr internal::Move_impl LusterPurge{EnumType::LusterPurge};
        static constexpr internal::Move_impl MistBall{EnumType::MistBall};
        static constexpr internal::Move_impl FeatherDance{EnumType::FeatherDance};
        static constexpr internal::Move_impl TeeterDance{EnumType::TeeterDance};
        static constexpr internal::Move_impl BlazeKick{EnumType::BlazeKick};
        static constexpr internal::Move_impl MudSport{EnumType::MudSport};
        static constexpr internal::Move_impl IceBall{EnumType::IceBall};
        static constexpr internal::Move_impl NeedleArm{EnumType::NeedleArm};
        static constexpr internal::Move_impl SlackOff{EnumType::SlackOff};
        static constexpr internal::Move_impl HyperVoice{EnumType::HyperVoice};
        static constexpr internal::Move_impl PoisonFang{EnumType::PoisonFang};
        static constexpr internal::Move_impl CrushClaw{EnumType::CrushClaw};
        static constexpr internal::Move_impl BlastBurn{EnumType::BlastBurn};
        static constexpr internal::Move_impl HydroCannon{EnumType::HydroCannon};
        static constexpr internal::Move_impl MeteorMash{EnumType::MeteorMash};
        static constexpr internal::Move_impl Astonish{EnumType::Astonish};
        static constexpr internal::Move_impl WeatherBall{EnumType::WeatherBall};
        static constexpr internal::Move_impl Aromatherapy{EnumType::Aromatherapy};
        static constexpr internal::Move_impl FakeTears{EnumType::FakeTears};
        static constexpr internal::Move_impl AirCutter{EnumType::AirCutter};
        static constexpr internal::Move_impl Overheat{EnumType::Overheat};
        static constexpr internal::Move_impl OdorSleuth{EnumType::OdorSleuth};
        static constexpr internal::Move_impl RockTomb{EnumType::RockTomb};
        static constexpr internal::Move_impl SilverWind{EnumType::SilverWind};
        static constexpr internal::Move_impl MetalSound{EnumType::MetalSound};
        static constexpr internal::Move_impl GrassWhistle{EnumType::GrassWhistle};
        static constexpr internal::Move_impl Tickle{EnumType::Tickle};
        static constexpr internal::Move_impl CosmicPower{EnumType::CosmicPower};
        static constexpr internal::Move_impl WaterSpout{EnumType::WaterSpout};
        static constexpr internal::Move_impl SignalBeam{EnumType::SignalBeam};
        static constexpr internal::Move_impl ShadowPunch{EnumType::ShadowPunch};
        static constexpr internal::Move_impl Extrasensory{EnumType::Extrasensory};
        static constexpr internal::Move_impl SkyUppercut{EnumType::SkyUppercut};
        static constexpr internal::Move_impl SandTomb{EnumType::SandTomb};
        static constexpr internal::Move_impl SheerCold{EnumType::SheerCold};
        static constexpr internal::Move_impl MuddyWater{EnumType::MuddyWater};
        static constexpr internal::Move_impl BulletSeed{EnumType::BulletSeed};
        static constexpr internal::Move_impl AerialAce{EnumType::AerialAce};
        static constexpr internal::Move_impl IcicleSpear{EnumType::IcicleSpear};
        static constexpr internal::Move_impl IronDefense{EnumType::IronDefense};
        static constexpr internal::Move_impl Block{EnumType::Block};
        static constexpr internal::Move_impl Howl{EnumType::Howl};
        static constexpr internal::Move_impl DragonClaw{EnumType::DragonClaw};
        static constexpr internal::Move_impl FrenzyPlant{EnumType::FrenzyPlant};
        static constexpr internal::Move_impl BulkUp{EnumType::BulkUp};
        static constexpr internal::Move_impl Bounce{EnumType::Bounce};
        static constexpr internal::Move_impl MudShot{EnumType::MudShot};
        static constexpr internal::Move_impl PoisonTail{EnumType::PoisonTail};
        static constexpr internal::Move_impl Covet{EnumType::Covet};
        static constexpr internal::Move_impl VoltTackle{EnumType::VoltTackle};
        static constexpr internal::Move_impl MagicalLeaf{EnumType::MagicalLeaf};
        static constexpr internal::Move_impl WaterSport{EnumType::WaterSport};
        static constexpr internal::Move_impl CalmMind{EnumType::CalmMind};
        static constexpr internal::Move_impl LeafBlade{EnumType::LeafBlade};
        static constexpr internal::Move_impl DragonDance{EnumType::DragonDance};
        static constexpr internal::Move_impl RockBlast{EnumType::RockBlast};
        static constexpr internal::Move_impl ShockWave{EnumType::ShockWave};
        static constexpr internal::Move_impl WaterPulse{EnumType::WaterPulse};
        static constexpr internal::Move_impl DoomDesire{EnumType::DoomDesire};
        static constexpr internal::Move_impl PsychoBoost{EnumType::PsychoBoost};
        static constexpr internal::Move_impl Roost{EnumType::Roost};
        static constexpr internal::Move_impl Gravity{EnumType::Gravity};
        static constexpr internal::Move_impl MiracleEye{EnumType::MiracleEye};
        static constexpr internal::Move_impl WakeUpSlap{EnumType::WakeUpSlap};
        static constexpr internal::Move_impl HammerArm{EnumType::HammerArm};
        static constexpr internal::Move_impl GyroBall{EnumType::GyroBall};
        static constexpr internal::Move_impl HealingWish{EnumType::HealingWish};
        static constexpr internal::Move_impl Brine{EnumType::Brine};
        static constexpr internal::Move_impl NaturalGift{EnumType::NaturalGift};
        static constexpr internal::Move_impl Feint{EnumType::Feint};
        static constexpr internal::Move_impl Pluck{EnumType::Pluck};
        static constexpr internal::Move_impl Tailwind{EnumType::Tailwind};
        static constexpr internal::Move_impl Acupressure{EnumType::Acupressure};
        static constexpr internal::Move_impl MetalBurst{EnumType::MetalBurst};
        static constexpr internal::Move_impl Uturn{EnumType::Uturn};
        static constexpr internal::Move_impl CloseCombat{EnumType::CloseCombat};
        static constexpr internal::Move_impl Payback{EnumType::Payback};
        static constexpr internal::Move_impl Assurance{EnumType::Assurance};
        static constexpr internal::Move_impl Embargo{EnumType::Embargo};
        static constexpr internal::Move_impl Fling{EnumType::Fling};
        static constexpr internal::Move_impl PsychoShift{EnumType::PsychoShift};
        static constexpr internal::Move_impl TrumpCard{EnumType::TrumpCard};
        static constexpr internal::Move_impl HealBlock{EnumType::HealBlock};
        static constexpr internal::Move_impl WringOut{EnumType::WringOut};
        static constexpr internal::Move_impl PowerTrick{EnumType::PowerTrick};
        static constexpr internal::Move_impl GastroAcid{EnumType::GastroAcid};
        static constexpr internal::Move_impl LuckyChant{EnumType::LuckyChant};
        static constexpr internal::Move_impl MeFirst{EnumType::MeFirst};
        static constexpr internal::Move_impl Copycat{EnumType::Copycat};
        static constexpr internal::Move_impl PowerSwap{EnumType::PowerSwap};
        static constexpr internal::Move_impl GuardSwap{EnumType::GuardSwap};
        static constexpr internal::Move_impl Punishment{EnumType::Punishment};
        static constexpr internal::Move_impl LastResort{EnumType::LastResort};
        static constexpr internal::Move_impl WorrySeed{EnumType::WorrySeed};
        static constexpr internal::Move_impl SuckerPunch{EnumType::SuckerPunch};
        static constexpr internal::Move_impl ToxicSpikes{EnumType::ToxicSpikes};
        static constexpr internal::Move_impl HeartSwap{EnumType::HeartSwap};
        static constexpr internal::Move_impl AquaRing{EnumType::AquaRing};
        static constexpr internal::Move_impl MagnetRise{EnumType::MagnetRise};
        static constexpr internal::Move_impl FlareBlitz{EnumType::FlareBlitz};
        static constexpr internal::Move_impl ForcePalm{EnumType::ForcePalm};
        static constexpr internal::Move_impl AuraSphere{EnumType::AuraSphere};
        static constexpr internal::Move_impl RockPolish{EnumType::RockPolish};
        static constexpr internal::Move_impl PoisonJab{EnumType::PoisonJab};
        static constexpr internal::Move_impl DarkPulse{EnumType::DarkPulse};
        static constexpr internal::Move_impl NightSlash{EnumType::NightSlash};
        static constexpr internal::Move_impl AquaTail{EnumType::AquaTail};
        static constexpr internal::Move_impl SeedBomb{EnumType::SeedBomb};
        static constexpr internal::Move_impl AirSlash{EnumType::AirSlash};
        static constexpr internal::Move_impl XScissor{EnumType::XScissor};
        static constexpr internal::Move_impl BugBuzz{EnumType::BugBuzz};
        static constexpr internal::Move_impl DragonPulse{EnumType::DragonPulse};
        static constexpr internal::Move_impl DragonRush{EnumType::DragonRush};
        static constexpr internal::Move_impl PowerGem{EnumType::PowerGem};
        static constexpr internal::Move_impl DrainPunch{EnumType::DrainPunch};
        static constexpr internal::Move_impl VacuumWave{EnumType::VacuumWave};
        static constexpr internal::Move_impl FocusBlast{EnumType::FocusBlast};
        static constexpr internal::Move_impl EnergyBall{EnumType::EnergyBall};
        static constexpr internal::Move_impl BraveBird{EnumType::BraveBird};
        static constexpr internal::Move_impl EarthPower{EnumType::EarthPower};
        static constexpr internal::Move_impl Switcheroo{EnumType::Switcheroo};
        static constexpr internal::Move_impl GigaImpact{EnumType::GigaImpact};
        static constexpr internal::Move_impl NastyPlot{EnumType::NastyPlot};
        static constexpr internal::Move_impl BulletPunch{EnumType::BulletPunch};
        static constexpr internal::Move_impl Avalanche{EnumType::Avalanche};
        static constexpr internal::Move_impl IceShard{EnumType::IceShard};
        static constexpr internal::Move_impl ShadowClaw{EnumType::ShadowClaw};
        static constexpr internal::Move_impl ThunderFang{EnumType::ThunderFang};
        static constexpr internal::Move_impl IceFang{EnumType::IceFang};
        static constexpr internal::Move_impl FireFang{EnumType::FireFang};
        static constexpr internal::Move_impl ShadowSneak{EnumType::ShadowSneak};
        static constexpr internal::Move_impl MudBomb{EnumType::MudBomb};
        static constexpr internal::Move_impl PsychoCut{EnumType::PsychoCut};
        static constexpr internal::Move_impl ZenHeadbutt{EnumType::ZenHeadbutt};
        static constexpr internal::Move_impl MirrorShot{EnumType::MirrorShot};
        static constexpr internal::Move_impl FlashCannon{EnumType::FlashCannon};
        static constexpr internal::Move_impl RockClimb{EnumType::RockClimb};
        static constexpr internal::Move_impl Defog{EnumType::Defog};
        static constexpr internal::Move_impl TrickRoom{EnumType::TrickRoom};
        static constexpr internal::Move_impl DracoMeteor{EnumType::DracoMeteor};
        static constexpr internal::Move_impl Discharge{EnumType::Discharge};
        static constexpr internal::Move_impl LavaPlume{EnumType::LavaPlume};
        static constexpr internal::Move_impl LeafStorm{EnumType::LeafStorm};
        static constexpr internal::Move_impl PowerWhip{EnumType::PowerWhip};
        static constexpr internal::Move_impl RockWrecker{EnumType::RockWrecker};
        static constexpr internal::Move_impl CrossPoison{EnumType::CrossPoison};
        static constexpr internal::Move_impl GunkShot{EnumType::GunkShot};
        static constexpr internal::Move_impl IronHead{EnumType::IronHead};
        static constexpr internal::Move_impl MagnetBomb{EnumType::MagnetBomb};
        static constexpr internal::Move_impl StoneEdge{EnumType::StoneEdge};
        static constexpr internal::Move_impl Captivate{EnumType::Captivate};
        static constexpr internal::Move_impl StealthRock{EnumType::StealthRock};
        static constexpr internal::Move_impl GrassKnot{EnumType::GrassKnot};
        static constexpr internal::Move_impl Chatter{EnumType::Chatter};
        static constexpr internal::Move_impl Judgment{EnumType::Judgment};
        static constexpr internal::Move_impl BugBite{EnumType::BugBite};
        static constexpr internal::Move_impl ChargeBeam{EnumType::ChargeBeam};
        static constexpr internal::Move_impl WoodHammer{EnumType::WoodHammer};
        static constexpr internal::Move_impl AquaJet{EnumType::AquaJet};
        static constexpr internal::Move_impl AttackOrder{EnumType::AttackOrder};
        static constexpr internal::Move_impl DefendOrder{EnumType::DefendOrder};
        static constexpr internal::Move_impl HealOrder{EnumType::HealOrder};
        static constexpr internal::Move_impl HeadSmash{EnumType::HeadSmash};
        static constexpr internal::Move_impl DoubleHit{EnumType::DoubleHit};
        static constexpr internal::Move_impl RoarofTime{EnumType::RoarofTime};
        static constexpr internal::Move_impl SpacialRend{EnumType::SpacialRend};
        static constexpr internal::Move_impl LunarDance{EnumType::LunarDance};
        static constexpr internal::Move_impl CrushGrip{EnumType::CrushGrip};
        static constexpr internal::Move_impl MagmaStorm{EnumType::MagmaStorm};
        static constexpr internal::Move_impl DarkVoid{EnumType::DarkVoid};
        static constexpr internal::Move_impl SeedFlare{EnumType::SeedFlare};
        static constexpr internal::Move_impl OminousWind{EnumType::OminousWind};
        static constexpr internal::Move_impl ShadowForce{EnumType::ShadowForce};
        static constexpr internal::Move_impl HoneClaws{EnumType::HoneClaws};
        static constexpr internal::Move_impl WideGuard{EnumType::WideGuard};
        static constexpr internal::Move_impl GuardSplit{EnumType::GuardSplit};
        static constexpr internal::Move_impl PowerSplit{EnumType::PowerSplit};
        static constexpr internal::Move_impl WonderRoom{EnumType::WonderRoom};
        static constexpr internal::Move_impl Psyshock{EnumType::Psyshock};
        static constexpr internal::Move_impl Venoshock{EnumType::Venoshock};
        static constexpr internal::Move_impl Autotomize{EnumType::Autotomize};
        static constexpr internal::Move_impl RagePowder{EnumType::RagePowder};
        static constexpr internal::Move_impl Telekinesis{EnumType::Telekinesis};
        static constexpr internal::Move_impl MagicRoom{EnumType::MagicRoom};
        static constexpr internal::Move_impl SmackDown{EnumType::SmackDown};
        static constexpr internal::Move_impl StormThrow{EnumType::StormThrow};
        static constexpr internal::Move_impl FlameBurst{EnumType::FlameBurst};
        static constexpr internal::Move_impl SludgeWave{EnumType::SludgeWave};
        static constexpr internal::Move_impl QuiverDance{EnumType::QuiverDance};
        static constexpr internal::Move_impl HeavySlam{EnumType::HeavySlam};
        static constexpr internal::Move_impl Synchronoise{EnumType::Synchronoise};
        static constexpr internal::Move_impl ElectroBall{EnumType::ElectroBall};
        static constexpr internal::Move_impl Soak{EnumType::Soak};
        static constexpr internal::Move_impl FlameCharge{EnumType::FlameCharge};
        static constexpr internal::Move_impl Coil{EnumType::Coil};
        static constexpr internal::Move_impl LowSweep{EnumType::LowSweep};
        static constexpr internal::Move_impl AcidSpray{EnumType::AcidSpray};
        static constexpr internal::Move_impl FoulPlay{EnumType::FoulPlay};
        static constexpr internal::Move_impl SimpleBeam{EnumType::SimpleBeam};
        static constexpr internal::Move_impl Entrainment{EnumType::Entrainment};
        static constexpr internal::Move_impl AfterYou{EnumType::AfterYou};
        static constexpr internal::Move_impl Round{EnumType::Round};
        static constexpr internal::Move_impl EchoedVoice{EnumType::EchoedVoice};
        static constexpr internal::Move_impl ChipAway{EnumType::ChipAway};
        static constexpr internal::Move_impl ClearSmog{EnumType::ClearSmog};
        static constexpr internal::Move_impl StoredPower{EnumType::StoredPower};
        static constexpr internal::Move_impl QuickGuard{EnumType::QuickGuard};
        static constexpr internal::Move_impl AllySwitch{EnumType::AllySwitch};
        static constexpr internal::Move_impl Scald{EnumType::Scald};
        static constexpr internal::Move_impl ShellSmash{EnumType::ShellSmash};
        static constexpr internal::Move_impl HealPulse{EnumType::HealPulse};
        static constexpr internal::Move_impl Hex{EnumType::Hex};
        static constexpr internal::Move_impl SkyDrop{EnumType::SkyDrop};
        static constexpr internal::Move_impl ShiftGear{EnumType::ShiftGear};
        static constexpr internal::Move_impl CircleThrow{EnumType::CircleThrow};
        static constexpr internal::Move_impl Incinerate{EnumType::Incinerate};
        static constexpr internal::Move_impl Quash{EnumType::Quash};
        static constexpr internal::Move_impl Acrobatics{EnumType::Acrobatics};
        static constexpr internal::Move_impl ReflectType{EnumType::ReflectType};
        static constexpr internal::Move_impl Retaliate{EnumType::Retaliate};
        static constexpr internal::Move_impl FinalGambit{EnumType::FinalGambit};
        static constexpr internal::Move_impl Bestow{EnumType::Bestow};
        static constexpr internal::Move_impl Inferno{EnumType::Inferno};
        static constexpr internal::Move_impl WaterPledge{EnumType::WaterPledge};
        static constexpr internal::Move_impl FirePledge{EnumType::FirePledge};
        static constexpr internal::Move_impl GrassPledge{EnumType::GrassPledge};
        static constexpr internal::Move_impl VoltSwitch{EnumType::VoltSwitch};
        static constexpr internal::Move_impl StruggleBug{EnumType::StruggleBug};
        static constexpr internal::Move_impl Bulldoze{EnumType::Bulldoze};
        static constexpr internal::Move_impl FrostBreath{EnumType::FrostBreath};
        static constexpr internal::Move_impl DragonTail{EnumType::DragonTail};
        static constexpr internal::Move_impl WorkUp{EnumType::WorkUp};
        static constexpr internal::Move_impl Electroweb{EnumType::Electroweb};
        static constexpr internal::Move_impl WildCharge{EnumType::WildCharge};
        static constexpr internal::Move_impl DrillRun{EnumType::DrillRun};
        static constexpr internal::Move_impl DualChop{EnumType::DualChop};
        static constexpr internal::Move_impl HeartStamp{EnumType::HeartStamp};
        static constexpr internal::Move_impl HornLeech{EnumType::HornLeech};
        static constexpr internal::Move_impl SacredSword{EnumType::SacredSword};
        static constexpr internal::Move_impl RazorShell{EnumType::RazorShell};
        static constexpr internal::Move_impl HeatCrash{EnumType::HeatCrash};
        static constexpr internal::Move_impl LeafTornado{EnumType::LeafTornado};
        static constexpr internal::Move_impl Steamroller{EnumType::Steamroller};
        static constexpr internal::Move_impl CottonGuard{EnumType::CottonGuard};
        static constexpr internal::Move_impl NightDaze{EnumType::NightDaze};
        static constexpr internal::Move_impl Psystrike{EnumType::Psystrike};
        static constexpr internal::Move_impl TailSlap{EnumType::TailSlap};
        static constexpr internal::Move_impl Hurricane{EnumType::Hurricane};
        static constexpr internal::Move_impl HeadCharge{EnumType::HeadCharge};
        static constexpr internal::Move_impl GearGrind{EnumType::GearGrind};
        static constexpr internal::Move_impl SearingShot{EnumType::SearingShot};
        static constexpr internal::Move_impl TechnoBlast{EnumType::TechnoBlast};
        static constexpr internal::Move_impl RelicSong{EnumType::RelicSong};
        static constexpr internal::Move_impl SecretSword{EnumType::SecretSword};
        static constexpr internal::Move_impl Glaciate{EnumType::Glaciate};
        static constexpr internal::Move_impl BoltStrike{EnumType::BoltStrike};
        static constexpr internal::Move_impl BlueFlare{EnumType::BlueFlare};
        static constexpr internal::Move_impl FieryDance{EnumType::FieryDance};
        static constexpr internal::Move_impl FreezeShock{EnumType::FreezeShock};
        static constexpr internal::Move_impl IceBurn{EnumType::IceBurn};
        static constexpr internal::Move_impl Snarl{EnumType::Snarl};
        static constexpr internal::Move_impl IcicleCrash{EnumType::IcicleCrash};
        static constexpr internal::Move_impl Vcreate{EnumType::Vcreate};
        static constexpr internal::Move_impl FusionFlare{EnumType::FusionFlare};
        static constexpr internal::Move_impl FusionBolt{EnumType::FusionBolt};
        static constexpr internal::Move_impl FlyingPress{EnumType::FlyingPress};
        static constexpr internal::Move_impl MatBlock{EnumType::MatBlock};
        static constexpr internal::Move_impl Belch{EnumType::Belch};
        static constexpr internal::Move_impl Rototiller{EnumType::Rototiller};
        static constexpr internal::Move_impl StickyWeb{EnumType::StickyWeb};
        static constexpr internal::Move_impl FellStinger{EnumType::FellStinger};
        static constexpr internal::Move_impl PhantomForce{EnumType::PhantomForce};
        static constexpr internal::Move_impl TrickorTreat{EnumType::TrickorTreat};
        static constexpr internal::Move_impl NobleRoar{EnumType::NobleRoar};
        static constexpr internal::Move_impl IonDeluge{EnumType::IonDeluge};
        static constexpr internal::Move_impl ParabolicCharge{EnumType::ParabolicCharge};
        static constexpr internal::Move_impl ForestsCurse{EnumType::ForestsCurse};
        static constexpr internal::Move_impl PetalBlizzard{EnumType::PetalBlizzard};
        static constexpr internal::Move_impl FreezeDry{EnumType::FreezeDry};
        static constexpr internal::Move_impl DisarmingVoice{EnumType::DisarmingVoice};
        static constexpr internal::Move_impl PartingShot{EnumType::PartingShot};
        static constexpr internal::Move_impl TopsyTurvy{EnumType::TopsyTurvy};
        static constexpr internal::Move_impl DrainingKiss{EnumType::DrainingKiss};
        static constexpr internal::Move_impl CraftyShield{EnumType::CraftyShield};
        static constexpr internal::Move_impl FlowerShield{EnumType::FlowerShield};
        static constexpr internal::Move_impl GrassyTerrain{EnumType::GrassyTerrain};
        static constexpr internal::Move_impl MistyTerrain{EnumType::MistyTerrain};
        static constexpr internal::Move_impl Electrify{EnumType::Electrify};
        static constexpr internal::Move_impl PlayRough{EnumType::PlayRough};
        static constexpr internal::Move_impl FairyWind{EnumType::FairyWind};
        static constexpr internal::Move_impl Moonblast{EnumType::Moonblast};
        static constexpr internal::Move_impl Boomburst{EnumType::Boomburst};
        static constexpr internal::Move_impl FairyLock{EnumType::FairyLock};
        static constexpr internal::Move_impl KingsShield{EnumType::KingsShield};
        static constexpr internal::Move_impl PlayNice{EnumType::PlayNice};
        static constexpr internal::Move_impl Confide{EnumType::Confide};
        static constexpr internal::Move_impl DiamondStorm{EnumType::DiamondStorm};
        static constexpr internal::Move_impl SteamEruption{EnumType::SteamEruption};
        static constexpr internal::Move_impl HyperspaceHole{EnumType::HyperspaceHole};
        static constexpr internal::Move_impl WaterShuriken{EnumType::WaterShuriken};
        static constexpr internal::Move_impl MysticalFire{EnumType::MysticalFire};
        static constexpr internal::Move_impl SpikyShield{EnumType::SpikyShield};
        static constexpr internal::Move_impl AromaticMist{EnumType::AromaticMist};
        static constexpr internal::Move_impl EerieImpulse{EnumType::EerieImpulse};
        static constexpr internal::Move_impl VenomDrench{EnumType::VenomDrench};
        static constexpr internal::Move_impl Powder{EnumType::Powder};
        static constexpr internal::Move_impl Geomancy{EnumType::Geomancy};
        static constexpr internal::Move_impl MagneticFlux{EnumType::MagneticFlux};
        static constexpr internal::Move_impl HappyHour{EnumType::HappyHour};
        static constexpr internal::Move_impl ElectricTerrain{EnumType::ElectricTerrain};
        static constexpr internal::Move_impl DazzlingGleam{EnumType::DazzlingGleam};
        static constexpr internal::Move_impl Celebrate{EnumType::Celebrate};
        static constexpr internal::Move_impl HoldHands{EnumType::HoldHands};
        static constexpr internal::Move_impl BabyDollEyes{EnumType::BabyDollEyes};
        static constexpr internal::Move_impl Nuzzle{EnumType::Nuzzle};
        static constexpr internal::Move_impl HoldBack{EnumType::HoldBack};
        static constexpr internal::Move_impl Infestation{EnumType::Infestation};
        static constexpr internal::Move_impl PowerUpPunch{EnumType::PowerUpPunch};
        static constexpr internal::Move_impl OblivionWing{EnumType::OblivionWing};
        static constexpr internal::Move_impl ThousandArrows{EnumType::ThousandArrows};
        static constexpr internal::Move_impl ThousandWaves{EnumType::ThousandWaves};
        static constexpr internal::Move_impl LandsWrath{EnumType::LandsWrath};
        static constexpr internal::Move_impl LightofRuin{EnumType::LightofRuin};
        static constexpr internal::Move_impl OriginPulse{EnumType::OriginPulse};
        static constexpr internal::Move_impl PrecipiceBlades{EnumType::PrecipiceBlades};
        static constexpr internal::Move_impl DragonAscent{EnumType::DragonAscent};
        static constexpr internal::Move_impl HyperspaceFury{EnumType::HyperspaceFury};
        static constexpr internal::Move_impl BreakneckBlitzA{EnumType::BreakneckBlitzA};
        static constexpr internal::Move_impl BreakneckBlitzB{EnumType::BreakneckBlitzB};
        static constexpr internal::Move_impl AllOutPummelingA{EnumType::AllOutPummelingA};
        static constexpr internal::Move_impl AllOutPummelingB{EnumType::AllOutPummelingB};
        static constexpr internal::Move_impl SupersonicSkystrikeA{EnumType::SupersonicSkystrikeA};
        static constexpr internal::Move_impl SupersonicSkystrikeB{EnumType::SupersonicSkystrikeB};
        static constexpr internal::Move_impl AcidDownpourA{EnumType::AcidDownpourA};
        static constexpr internal::Move_impl AcidDownpourB{EnumType::AcidDownpourB};
        static constexpr internal::Move_impl TectonicRageA{EnumType::TectonicRageA};
        static constexpr internal::Move_impl TectonicRageB{EnumType::TectonicRageB};
        static constexpr internal::Move_impl ContinentalCrushA{EnumType::ContinentalCrushA};
        static constexpr internal::Move_impl ContinentalCrushB{EnumType::ContinentalCrushB};
        static constexpr internal::Move_impl SavageSpinOutA{EnumType::SavageSpinOutA};
        static constexpr internal::Move_impl SavageSpinOutB{EnumType::SavageSpinOutB};
        static constexpr internal::Move_impl NeverEndingNightmareA{EnumType::NeverEndingNightmareA};
        static constexpr internal::Move_impl NeverEndingNightmareB{EnumType::NeverEndingNightmareB};
        static constexpr internal::Move_impl CorkscrewCrashA{EnumType::CorkscrewCrashA};
        static constexpr internal::Move_impl CorkscrewCrashB{EnumType::CorkscrewCrashB};
        static constexpr internal::Move_impl InfernoOverdriveA{EnumType::InfernoOverdriveA};
        static constexpr internal::Move_impl InfernoOverdriveB{EnumType::InfernoOverdriveB};
        static constexpr internal::Move_impl HydroVortexA{EnumType::HydroVortexA};
        static constexpr internal::Move_impl HydroVortexB{EnumType::HydroVortexB};
        static constexpr internal::Move_impl BloomDoomA{EnumType::BloomDoomA};
        static constexpr internal::Move_impl BloomDoomB{EnumType::BloomDoomB};
        static constexpr internal::Move_impl GigavoltHavocA{EnumType::GigavoltHavocA};
        static constexpr internal::Move_impl GigavoltHavocB{EnumType::GigavoltHavocB};
        static constexpr internal::Move_impl ShatteredPsycheA{EnumType::ShatteredPsycheA};
        static constexpr internal::Move_impl ShatteredPsycheB{EnumType::ShatteredPsycheB};
        static constexpr internal::Move_impl SubzeroSlammerA{EnumType::SubzeroSlammerA};
        static constexpr internal::Move_impl SubzeroSlammerB{EnumType::SubzeroSlammerB};
        static constexpr internal::Move_impl DevastatingDrakeA{EnumType::DevastatingDrakeA};
        static constexpr internal::Move_impl DevastatingDrakeB{EnumType::DevastatingDrakeB};
        static constexpr internal::Move_impl BlackHoleEclipseA{EnumType::BlackHoleEclipseA};
        static constexpr internal::Move_impl BlackHoleEclipseB{EnumType::BlackHoleEclipseB};
        static constexpr internal::Move_impl TwinkleTackleA{EnumType::TwinkleTackleA};
        static constexpr internal::Move_impl TwinkleTackleB{EnumType::TwinkleTackleB};
        static constexpr internal::Move_impl Catastropika{EnumType::Catastropika};
        static constexpr internal::Move_impl ShoreUp{EnumType::ShoreUp};
        static constexpr internal::Move_impl FirstImpression{EnumType::FirstImpression};
        static constexpr internal::Move_impl BanefulBunker{EnumType::BanefulBunker};
        static constexpr internal::Move_impl SpiritShackle{EnumType::SpiritShackle};
        static constexpr internal::Move_impl DarkestLariat{EnumType::DarkestLariat};
        static constexpr internal::Move_impl SparklingAria{EnumType::SparklingAria};
        static constexpr internal::Move_impl IceHammer{EnumType::IceHammer};
        static constexpr internal::Move_impl FloralHealing{EnumType::FloralHealing};
        static constexpr internal::Move_impl HighHorsepower{EnumType::HighHorsepower};
        static constexpr internal::Move_impl StrengthSap{EnumType::StrengthSap};
        static constexpr internal::Move_impl SolarBlade{EnumType::SolarBlade};
        static constexpr internal::Move_impl Leafage{EnumType::Leafage};
        static constexpr internal::Move_impl Spotlight{EnumType::Spotlight};
        static constexpr internal::Move_impl ToxicThread{EnumType::ToxicThread};
        static constexpr internal::Move_impl LaserFocus{EnumType::LaserFocus};
        static constexpr internal::Move_impl GearUp{EnumType::GearUp};
        static constexpr internal::Move_impl ThroatChop{EnumType::ThroatChop};
        static constexpr internal::Move_impl PollenPuff{EnumType::PollenPuff};
        static constexpr internal::Move_impl AnchorShot{EnumType::AnchorShot};
        static constexpr internal::Move_impl PsychicTerrain{EnumType::PsychicTerrain};
        static constexpr internal::Move_impl Lunge{EnumType::Lunge};
        static constexpr internal::Move_impl FireLash{EnumType::FireLash};
        static constexpr internal::Move_impl PowerTrip{EnumType::PowerTrip};
        static constexpr internal::Move_impl BurnUp{EnumType::BurnUp};
        static constexpr internal::Move_impl SpeedSwap{EnumType::SpeedSwap};
        static constexpr internal::Move_impl SmartStrike{EnumType::SmartStrike};
        static constexpr internal::Move_impl Purify{EnumType::Purify};
        static constexpr internal::Move_impl RevelationDance{EnumType::RevelationDance};
        static constexpr internal::Move_impl CoreEnforcer{EnumType::CoreEnforcer};
        static constexpr internal::Move_impl TropKick{EnumType::TropKick};
        static constexpr internal::Move_impl Instruct{EnumType::Instruct};
        static constexpr internal::Move_impl BeakBlast{EnumType::BeakBlast};
        static constexpr internal::Move_impl ClangingScales{EnumType::ClangingScales};
        static constexpr internal::Move_impl DragonHammer{EnumType::DragonHammer};
        static constexpr internal::Move_impl BrutalSwing{EnumType::BrutalSwing};
        static constexpr internal::Move_impl AuroraVeil{EnumType::AuroraVeil};
        static constexpr internal::Move_impl SinisterArrowRaid{EnumType::SinisterArrowRaid};
        static constexpr internal::Move_impl MaliciousMoonsault{EnumType::MaliciousMoonsault};
        static constexpr internal::Move_impl OceanicOperetta{EnumType::OceanicOperetta};
        static constexpr internal::Move_impl GuardianofAlola{EnumType::GuardianofAlola};
        static constexpr internal::Move_impl SoulStealing7StarStrike{
            EnumType::SoulStealing7StarStrike};
        static constexpr internal::Move_impl StokedSparksurfer{EnumType::StokedSparksurfer};
        static constexpr internal::Move_impl PulverizingPancake{EnumType::PulverizingPancake};
        static constexpr internal::Move_impl ExtremeEvoboost{EnumType::ExtremeEvoboost};
        static constexpr internal::Move_impl GenesisSupernova{EnumType::GenesisSupernova};
        static constexpr internal::Move_impl ShellTrap{EnumType::ShellTrap};
        static constexpr internal::Move_impl FleurCannon{EnumType::FleurCannon};
        static constexpr internal::Move_impl PsychicFangs{EnumType::PsychicFangs};
        static constexpr internal::Move_impl StompingTantrum{EnumType::StompingTantrum};
        static constexpr internal::Move_impl ShadowBone{EnumType::ShadowBone};
        static constexpr internal::Move_impl Accelerock{EnumType::Accelerock};
        static constexpr internal::Move_impl Liquidation{EnumType::Liquidation};
        static constexpr internal::Move_impl PrismaticLaser{EnumType::PrismaticLaser};
        static constexpr internal::Move_impl SpectralThief{EnumType::SpectralThief};
        static constexpr internal::Move_impl SunsteelStrike{EnumType::SunsteelStrike};
        static constexpr internal::Move_impl MoongeistBeam{EnumType::MoongeistBeam};
        static constexpr internal::Move_impl TearfulLook{EnumType::TearfulLook};
        static constexpr internal::Move_impl ZingZap{EnumType::ZingZap};
        static constexpr internal::Move_impl NaturesMadness{EnumType::NaturesMadness};
        static constexpr internal::Move_impl MultiAttack{EnumType::MultiAttack};
        static constexpr internal::Move_impl TenMillionVoltThunderbolt{
            EnumType::TenMillionVoltThunderbolt};
        static constexpr internal::Move_impl MindBlown{EnumType::MindBlown};
        static constexpr internal::Move_impl PlasmaFists{EnumType::PlasmaFists};
        static constexpr internal::Move_impl PhotonGeyser{EnumType::PhotonGeyser};
        static constexpr internal::Move_impl LightThatBurnstheSky{EnumType::LightThatBurnstheSky};
        static constexpr internal::Move_impl SearingSunrazeSmash{EnumType::SearingSunrazeSmash};
        static constexpr internal::Move_impl MenacingMoonrazeMaelstrom{
            EnumType::MenacingMoonrazeMaelstrom};
        static constexpr internal::Move_impl LetsSnuggleForever{EnumType::LetsSnuggleForever};
        static constexpr internal::Move_impl SplinteredStormshards{EnumType::SplinteredStormshards};
        static constexpr internal::Move_impl ClangorousSoulblaze{EnumType::ClangorousSoulblaze};
        static constexpr internal::Move_impl ZippyZap{EnumType::ZippyZap};
        static constexpr internal::Move_impl SplishySplash{EnumType::SplishySplash};
        static constexpr internal::Move_impl FloatyFall{EnumType::FloatyFall};
        static constexpr internal::Move_impl PikaPapow{EnumType::PikaPapow};
        static constexpr internal::Move_impl BouncyBubble{EnumType::BouncyBubble};
        static constexpr internal::Move_impl BuzzyBuzz{EnumType::BuzzyBuzz};
        static constexpr internal::Move_impl SizzlySlide{EnumType::SizzlySlide};
        static constexpr internal::Move_impl GlitzyGlow{EnumType::GlitzyGlow};
        static constexpr internal::Move_impl BaddyBad{EnumType::BaddyBad};
        static constexpr internal::Move_impl SappySeed{EnumType::SappySeed};
        static constexpr internal::Move_impl FreezyFrost{EnumType::FreezyFrost};
        static constexpr internal::Move_impl SparklySwirl{EnumType::SparklySwirl};
        static constexpr internal::Move_impl VeeveeVolley{EnumType::VeeveeVolley};
        static constexpr internal::Move_impl DoubleIronBash{EnumType::DoubleIronBash};
        static constexpr internal::Move_impl MaxGuard{EnumType::MaxGuard};
        static constexpr internal::Move_impl DynamaxCannon{EnumType::DynamaxCannon};
        static constexpr internal::Move_impl SnipeShot{EnumType::SnipeShot};
        static constexpr internal::Move_impl JawLock{EnumType::JawLock};
        static constexpr internal::Move_impl StuffCheeks{EnumType::StuffCheeks};
        static constexpr internal::Move_impl NoRetreat{EnumType::NoRetreat};
        static constexpr internal::Move_impl TarShot{EnumType::TarShot};
        static constexpr internal::Move_impl MagicPowder{EnumType::MagicPowder};
        static constexpr internal::Move_impl DragonDarts{EnumType::DragonDarts};
        static constexpr internal::Move_impl Teatime{EnumType::Teatime};
        static constexpr internal::Move_impl Octolock{EnumType::Octolock};
        static constexpr internal::Move_impl BoltBeak{EnumType::BoltBeak};
        static constexpr internal::Move_impl FishiousRend{EnumType::FishiousRend};
        static constexpr internal::Move_impl CourtChange{EnumType::CourtChange};
        static constexpr internal::Move_impl MaxFlare{EnumType::MaxFlare};
        static constexpr internal::Move_impl MaxFlutterby{EnumType::MaxFlutterby};
        static constexpr internal::Move_impl MaxLightning{EnumType::MaxLightning};
        static constexpr internal::Move_impl MaxStrike{EnumType::MaxStrike};
        static constexpr internal::Move_impl MaxKnuckle{EnumType::MaxKnuckle};
        static constexpr internal::Move_impl MaxPhantasm{EnumType::MaxPhantasm};
        static constexpr internal::Move_impl MaxHailstorm{EnumType::MaxHailstorm};
        static constexpr internal::Move_impl MaxOoze{EnumType::MaxOoze};
        static constexpr internal::Move_impl MaxGeyser{EnumType::MaxGeyser};
        static constexpr internal::Move_impl MaxAirstream{EnumType::MaxAirstream};
        static constexpr internal::Move_impl MaxStarfall{EnumType::MaxStarfall};
        static constexpr internal::Move_impl MaxWyrmwind{EnumType::MaxWyrmwind};
        static constexpr internal::Move_impl MaxMindstorm{EnumType::MaxMindstorm};
        static constexpr internal::Move_impl MaxRockfall{EnumType::MaxRockfall};
        static constexpr internal::Move_impl MaxQuake{EnumType::MaxQuake};
        static constexpr internal::Move_impl MaxDarkness{EnumType::MaxDarkness};
        static constexpr internal::Move_impl MaxOvergrowth{EnumType::MaxOvergrowth};
        static constexpr internal::Move_impl MaxSteelspike{EnumType::MaxSteelspike};
        static constexpr internal::Move_impl ClangorousSoul{EnumType::ClangorousSoul};
        static constexpr internal::Move_impl BodyPress{EnumType::BodyPress};
        static constexpr internal::Move_impl Decorate{EnumType::Decorate};
        static constexpr internal::Move_impl DrumBeating{EnumType::DrumBeating};
        static constexpr internal::Move_impl SnapTrap{EnumType::SnapTrap};
        static constexpr internal::Move_impl PyroBall{EnumType::PyroBall};
        static constexpr internal::Move_impl BehemothBlade{EnumType::BehemothBlade};
        static constexpr internal::Move_impl BehemothBash{EnumType::BehemothBash};
        static constexpr internal::Move_impl AuraWheel{EnumType::AuraWheel};
        static constexpr internal::Move_impl BreakingSwipe{EnumType::BreakingSwipe};
        static constexpr internal::Move_impl BranchPoke{EnumType::BranchPoke};
        static constexpr internal::Move_impl Overdrive{EnumType::Overdrive};
        static constexpr internal::Move_impl AppleAcid{EnumType::AppleAcid};
        static constexpr internal::Move_impl GravApple{EnumType::GravApple};
        static constexpr internal::Move_impl SpiritBreak{EnumType::SpiritBreak};
        static constexpr internal::Move_impl StrangeSteam{EnumType::StrangeSteam};
        static constexpr internal::Move_impl LifeDew{EnumType::LifeDew};
        static constexpr internal::Move_impl Obstruct{EnumType::Obstruct};
        static constexpr internal::Move_impl FalseSurrender{EnumType::FalseSurrender};
        static constexpr internal::Move_impl MeteorAssault{EnumType::MeteorAssault};
        static constexpr internal::Move_impl Eternabeam{EnumType::Eternabeam};
        static constexpr internal::Move_impl SteelBeam{EnumType::SteelBeam};
        static constexpr internal::Move_impl ExpandingForce{EnumType::ExpandingForce};
        static constexpr internal::Move_impl SteelRoller{EnumType::SteelRoller};
        static constexpr internal::Move_impl ScaleShot{EnumType::ScaleShot};
        static constexpr internal::Move_impl MeteorBeam{EnumType::MeteorBeam};
        static constexpr internal::Move_impl ShellSideArm{EnumType::ShellSideArm};
        static constexpr internal::Move_impl MistyExplosion{EnumType::MistyExplosion};
        static constexpr internal::Move_impl GrassyGlide{EnumType::GrassyGlide};
        static constexpr internal::Move_impl RisingVoltage{EnumType::RisingVoltage};
        static constexpr internal::Move_impl TerrainPulse{EnumType::TerrainPulse};
        static constexpr internal::Move_impl SkitterSmack{EnumType::SkitterSmack};
        static constexpr internal::Move_impl BurningJealousy{EnumType::BurningJealousy};
        static constexpr internal::Move_impl LashOut{EnumType::LashOut};
        static constexpr internal::Move_impl Poltergeist{EnumType::Poltergeist};
        static constexpr internal::Move_impl CorrosiveGas{EnumType::CorrosiveGas};
        static constexpr internal::Move_impl Coaching{EnumType::Coaching};
        static constexpr internal::Move_impl FlipTurn{EnumType::FlipTurn};
        static constexpr internal::Move_impl TripleAxel{EnumType::TripleAxel};
        static constexpr internal::Move_impl DualWingbeat{EnumType::DualWingbeat};
        static constexpr internal::Move_impl ScorchingSands{EnumType::ScorchingSands};
        static constexpr internal::Move_impl JungleHealing{EnumType::JungleHealing};
        static constexpr internal::Move_impl WickedBlow{EnumType::WickedBlow};
        static constexpr internal::Move_impl SurgingStrikes{EnumType::SurgingStrikes};

        static constexpr internal::Move_impl INVALID{EnumType::INVALID};
    };
}

#endif
