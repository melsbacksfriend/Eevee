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

#include "utils/VersionTables.hpp"
#include "personal/personal.hpp"
#include "ppCount.hpp"
#include <functional>
#include <unordered_map>

namespace
{
    template <typename T>
    static inline std::set<T> create_set_consecutive(const T& begin, const T& end)
    {
        std::set<T> set;
        if constexpr (std::is_integral_v<T>)
        {
            for (T i = begin; i <= end; i++)
            {
                set.insert(i);
            }
        }
        else
        {
            static_assert(std::is_enum_v<typename T::EnumType>);
            using INT = std::underlying_type_t<typename T::EnumType>;
            for (INT i = INT(begin); i <= INT(end); i++)
            {
                set.insert(T(i));
            }
        }
        return set;
    }
}

namespace pksm
{
    const std::set<int>& VersionTables::availableItems(GameVersion version)
    {
        static const std::set<int> emptySet;
        switch (version)
        {
            case GameVersion::R:
            case GameVersion::S:
            {
                static const std::set<int> items =
                    std::invoke([]() { return create_set_consecutive<int>(0, 348); });
                return items;
            }
            case GameVersion::FR:
            case GameVersion::LG:
            {
                static const std::set<int> items =
                    std::invoke([]() { return create_set_consecutive<int>(0, 374); });
                return items;
            }
            case GameVersion::E:
            {
                static const std::set<int> items =
                    std::invoke([]() { return create_set_consecutive<int>(0, 376); });
                return items;
            }
            case GameVersion::D:
            case GameVersion::P:
            {
                static const std::set<int> items =
                    std::invoke([]() { return create_set_consecutive<int>(0, 464); });
                return items;
            }
            case GameVersion::Pt:
            {
                static const std::set<int> items =
                    std::invoke([]() { return create_set_consecutive<int>(0, 467); });
                return items;
            }
            case GameVersion::HG:
            case GameVersion::SS:
            {
                static const std::set<int> items =
                    std::invoke([]() { return create_set_consecutive<int>(0, 536); });
                return items;
            }
            case GameVersion::B:
            case GameVersion::W:
            {
                static const std::set<int> items =
                    std::invoke([]() { return create_set_consecutive<int>(0, 632); });
                return items;
            }
            case GameVersion::B2:
            case GameVersion::W2:
            {
                static const std::set<int> items =
                    std::invoke([]() { return create_set_consecutive<int>(0, 638); });
                return items;
            }
            case GameVersion::X:
            case GameVersion::Y:
            {
                static const std::set<int> items =
                    std::invoke([]() { return create_set_consecutive<int>(0, 717); });
                return items;
            }
            case GameVersion::OR:
            case GameVersion::AS:
            {
                static const std::set<int> items =
                    std::invoke([]() { return create_set_consecutive<int>(0, 775); });
                return items;
            }
            case GameVersion::SN:
            case GameVersion::MN:
            {
                static const std::set<int> items =
                    std::invoke([]() { return create_set_consecutive<int>(0, 920); });
                return items;
            }
            case GameVersion::US:
            case GameVersion::UM:
            {
                static const std::set<int> items =
                    std::invoke([]() { return create_set_consecutive<int>(0, 959); });
                return items;
            }
            case GameVersion::GE:
            case GameVersion::GP:
            {
                static const std::set<int> items = {0, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27,
                    28, 29, 30, 31, 32, 38, 39, 40, 41, 709, 903, 328, 329, 330, 331, 332, 333, 334,
                    335, 336, 337, 338, 339, 340, 341, 342, 343, 344, 345, 346, 347, 348, 349, 350,
                    351, 352, 353, 354, 355, 356, 357, 358, 359, 360, 361, 362, 363, 364, 365, 366,
                    367, 368, 369, 370, 371, 372, 373, 374, 375, 376, 377, 378, 379, 380, 381, 382,
                    383, 384, 385, 386, 387, 50, 960, 961, 962, 963, 964, 965, 966, 967, 968, 969,
                    970, 971, 972, 973, 974, 975, 976, 977, 978, 979, 980, 981, 982, 983, 984, 985,
                    986, 987, 988, 989, 990, 991, 992, 993, 994, 995, 996, 997, 998, 999, 1000,
                    1001, 1002, 1003, 1004, 1005, 1006, 1007, 1008, 1009, 1010, 1011, 1012, 1013,
                    1014, 1015, 1016, 1017, 1018, 1019, 1020, 1021, 1022, 1023, 1024, 1025, 1026,
                    1027, 1028, 1029, 1030, 1031, 1032, 1033, 1034, 1035, 1036, 1037, 1038, 1039,
                    1040, 1041, 1042, 1043, 1044, 1045, 1046, 1047, 1048, 1049, 1050, 1051, 1052,
                    1053, 1054, 1055, 1056, 1057, 51, 53, 81, 82, 83, 84, 85, 849, 1, 2, 3, 4, 12,
                    164, 166, 168, 861, 862, 863, 864, 865, 866, 55, 56, 57, 58, 59, 60, 61, 62,
                    656, 659, 660, 661, 662, 663, 671, 672, 675, 676, 678, 679, 760, 762, 770, 773,
                    76, 77, 78, 79, 86, 87, 88, 89, 90, 91, 92, 93, 101, 102, 103, 113, 115, 121,
                    122, 123, 124, 125, 126, 127, 128, 442, 571, 632, 651, 795, 796, 872, 873, 874,
                    875, 876, 877, 878, 885, 886, 887, 888, 889, 890, 891, 892, 893, 894, 895, 896,
                    900, 901, 902};
                return items;
            }
            case GameVersion::SW:
            case GameVersion::SH:
            {
                static const std::set<int> items =
                    std::invoke([]() { return create_set_consecutive<int>(0, 1589); });
                return items;
            }
            default:
                return emptySet;
        }
    }

    const std::set<Move>& VersionTables::availableMoves(GameVersion version)
    {
        static const std::set<Move> emptySet;
        switch (version)
        {
            case GameVersion::R:
            case GameVersion::S:
            case GameVersion::FR:
            case GameVersion::LG:
            case GameVersion::E:
            {
                static const std::set<Move> items = std::invoke(
                    []() { return create_set_consecutive<Move>(Move::None, Move::PsychoBoost); });
                return items;
            }
            case GameVersion::D:
            case GameVersion::P:
            case GameVersion::Pt:
            case GameVersion::HG:
            case GameVersion::SS:
            {
                static const std::set<Move> items = std::invoke(
                    []() { return create_set_consecutive<Move>(Move::None, Move::ShadowForce); });
                return items;
            }
            case GameVersion::B:
            case GameVersion::W:
            case GameVersion::B2:
            case GameVersion::W2:
            {
                static const std::set<Move> items = std::invoke(
                    []() { return create_set_consecutive<Move>(Move::None, Move::FusionBolt); });
                return items;
            }
            case GameVersion::X:
            case GameVersion::Y:
            {
                static const std::set<Move> items = std::invoke(
                    []() { return create_set_consecutive<Move>(Move::None, Move::LightofRuin); });
                return items;
            }
            case GameVersion::OR:
            case GameVersion::AS:
            {
                static const std::set<Move> items = std::invoke([]() {
                    return create_set_consecutive<Move>(Move::None, Move::HyperspaceFury);
                });
                return items;
            }
            case GameVersion::SN:
            case GameVersion::MN:
            {
                static const std::set<Move> items = std::invoke(
                    []() { return create_set_consecutive<Move>(Move::None, Move::MindBlown); });
                return items;
            }
            case GameVersion::US:
            case GameVersion::UM:
            {
                static const std::set<Move> items = std::invoke([]() {
                    return create_set_consecutive<Move>(Move::None, Move::ClangorousSoulblaze);
                });
                return items;
            }
            case GameVersion::GE:
            case GameVersion::GP:
            {
                static const std::set<Move> items = {Move::None, Move::Pound, Move::KarateChop,
                    Move::DoubleSlap, Move::CometPunch, Move::MegaPunch, Move::PayDay,
                    Move::FirePunch, Move::IcePunch, Move::ThunderPunch, Move::Scratch,
                    Move::ViseGrip, Move::Guillotine, Move::RazorWind, Move::SwordsDance, Move::Cut,
                    Move::Gust, Move::WingAttack, Move::Whirlwind, Move::Fly, Move::Bind,
                    Move::Slam, Move::VineWhip, Move::Stomp, Move::DoubleKick, Move::MegaKick,
                    Move::JumpKick, Move::RollingKick, Move::SandAttack, Move::Headbutt,
                    Move::HornAttack, Move::FuryAttack, Move::HornDrill, Move::Tackle,
                    Move::BodySlam, Move::Wrap, Move::TakeDown, Move::Thrash, Move::DoubleEdge,
                    Move::TailWhip, Move::PoisonSting, Move::Twineedle, Move::PinMissile,
                    Move::Leer, Move::Bite, Move::Growl, Move::Roar, Move::Sing, Move::Supersonic,
                    Move::SonicBoom, Move::Disable, Move::Acid, Move::Ember, Move::Flamethrower,
                    Move::Mist, Move::WaterGun, Move::HydroPump, Move::Surf, Move::IceBeam,
                    Move::Blizzard, Move::Psybeam, Move::BubbleBeam, Move::AuroraBeam,
                    Move::HyperBeam, Move::Peck, Move::DrillPeck, Move::Submission, Move::LowKick,
                    Move::Counter, Move::SeismicToss, Move::Strength, Move::Absorb, Move::MegaDrain,
                    Move::LeechSeed, Move::Growth, Move::RazorLeaf, Move::SolarBeam,
                    Move::PoisonPowder, Move::StunSpore, Move::SleepPowder, Move::PetalDance,
                    Move::StringShot, Move::DragonRage, Move::FireSpin, Move::ThunderShock,
                    Move::Thunderbolt, Move::ThunderWave, Move::Thunder, Move::RockThrow,
                    Move::Earthquake, Move::Fissure, Move::Dig, Move::Toxic, Move::Confusion,
                    Move::Psychic, Move::Hypnosis, Move::Meditate, Move::Agility, Move::QuickAttack,
                    Move::Rage, Move::Teleport, Move::NightShade, Move::Mimic, Move::Screech,
                    Move::DoubleTeam, Move::Recover, Move::Harden, Move::Minimize,
                    Move::Smokescreen, Move::ConfuseRay, Move::Withdraw, Move::DefenseCurl,
                    Move::Barrier, Move::LightScreen, Move::Haze, Move::Reflect, Move::FocusEnergy,
                    Move::Bide, Move::Metronome, Move::MirrorMove, Move::SelfDestruct,
                    Move::EggBomb, Move::Lick, Move::Smog, Move::Sludge, Move::BoneClub,
                    Move::FireBlast, Move::Waterfall, Move::Clamp, Move::Swift, Move::SkullBash,
                    Move::SpikeCannon, Move::Constrict, Move::Amnesia, Move::Kinesis,
                    Move::SoftBoiled, Move::HighJumpKick, Move::Glare, Move::DreamEater,
                    Move::PoisonGas, Move::Barrage, Move::LeechLife, Move::LovelyKiss,
                    Move::SkyAttack, Move::Transform, Move::Bubble, Move::DizzyPunch, Move::Spore,
                    Move::Flash, Move::Psywave, Move::Splash, Move::AcidArmor, Move::Crabhammer,
                    Move::Explosion, Move::FurySwipes, Move::Bonemerang, Move::Rest,
                    Move::RockSlide, Move::HyperFang, Move::Sharpen, Move::Conversion,
                    Move::TriAttack, Move::SuperFang, Move::Slash, Move::Substitute, Move::Protect,
                    Move::SludgeBomb, Move::Outrage, Move::Megahorn, Move::Encore, Move::IronTail,
                    Move::Crunch, Move::MirrorCoat, Move::ShadowBall, Move::FakeOut, Move::HeatWave,
                    Move::WillOWisp, Move::Facade, Move::Taunt, Move::HelpingHand, Move::Superpower,
                    Move::BrickBreak, Move::Yawn, Move::BulkUp, Move::CalmMind, Move::Roost,
                    Move::Feint, Move::Uturn, Move::SuckerPunch, Move::FlareBlitz, Move::PoisonJab,
                    Move::DarkPulse, Move::AirSlash, Move::XScissor, Move::BugBuzz,
                    Move::DragonPulse, Move::NastyPlot, Move::IceShard, Move::FlashCannon,
                    Move::PowerWhip, Move::StealthRock, Move::AquaJet, Move::QuiverDance,
                    Move::FoulPlay, Move::ClearSmog, Move::Scald, Move::ShellSmash,
                    Move::DragonTail, Move::DrillRun, Move::PlayRough, Move::Moonblast,
                    Move::HappyHour, Move::DazzlingGleam, Move::Celebrate, Move::HoldHands,
                    Move::ZippyZap, Move::SplishySplash, Move::FloatyFall, Move::BouncyBubble,
                    Move::BuzzyBuzz, Move::SizzlySlide, Move::GlitzyGlow, Move::BaddyBad,
                    Move::SappySeed, Move::FreezyFrost, Move::SparklySwirl, Move::DoubleIronBash};
                return items;
            }
            case GameVersion::SW:
            case GameVersion::SH:
            {
                static const std::set<Move> items = std::invoke([]() {
                    return create_set_consecutive<Move>(Move::None, Move::SurgingStrikes);
                });
                return items;
            }
            default:
                return emptySet;
        }
    }

    const std::set<Species>& VersionTables::availableSpecies(GameVersion version)
    {
        static const std::set<Species> emptySet;
        switch (version)
        {
            case GameVersion::R:
            case GameVersion::S:
            case GameVersion::FR:
            case GameVersion::LG:
            case GameVersion::E:
            {
                static const std::set<Species> items = std::invoke([]() {
                    return create_set_consecutive<Species>(Species::Bulbasaur, Species::Deoxys);
                });
                return items;
            }
            case GameVersion::D:
            case GameVersion::P:
            case GameVersion::Pt:
            case GameVersion::HG:
            case GameVersion::SS:
            {
                static const std::set<Species> items = std::invoke([]() {
                    return create_set_consecutive<Species>(Species::Bulbasaur, Species::Arceus);
                });
                return items;
            }
            case GameVersion::B:
            case GameVersion::W:
            case GameVersion::B2:
            case GameVersion::W2:
            {
                static const std::set<Species> items = std::invoke([]() {
                    return create_set_consecutive<Species>(Species::Bulbasaur, Species::Genesect);
                });
                return items;
            }
            case GameVersion::X:
            case GameVersion::Y:
            case GameVersion::OR:
            case GameVersion::AS:
            {
                static const std::set<Species> items = std::invoke([]() {
                    return create_set_consecutive<Species>(Species::Bulbasaur, Species::Volcanion);
                });
                return items;
            }
            case GameVersion::SN:
            case GameVersion::MN:
            {
                static const std::set<Species> items = std::invoke([]() {
                    return create_set_consecutive<Species>(Species::Bulbasaur, Species::Marshadow);
                });
                return items;
            }
            case GameVersion::US:
            case GameVersion::UM:
            {
                static const std::set<Species> items = std::invoke([]() {
                    return create_set_consecutive<Species>(Species::Bulbasaur, Species::Zeraora);
                });
                return items;
            }
            case GameVersion::GE:
            case GameVersion::GP:
            {
                static const std::set<Species> items = std::invoke([]() {
                    auto ret = create_set_consecutive<Species>(Species::Bulbasaur, Species::Mew);
                    ret.emplace(Species::Meltan);
                    ret.emplace(Species::Melmetal);
                    return ret;
                });
                return items;
            }
            case GameVersion::SW:
            case GameVersion::SH:
            {
                static const std::set<Species> items = {Species::Bulbasaur, Species::Ivysaur,
                    Species::Venusaur, Species::Charmander, Species::Charmeleon, Species::Charizard,
                    Species::Squirtle, Species::Wartortle, Species::Blastoise, Species::Caterpie,
                    Species::Metapod, Species::Butterfree, Species::Pikachu, Species::Raichu,
                    Species::Clefairy, Species::Clefable, Species::Vulpix, Species::Ninetales,
                    Species::Oddish, Species::Gloom, Species::Vileplume, Species::Diglett,
                    Species::Dugtrio, Species::Meowth, Species::Persian, Species::Growlithe,
                    Species::Arcanine, Species::Machop, Species::Machoke, Species::Machamp,
                    Species::Ponyta, Species::Rapidash, Species::Farfetchd, Species::Shellder,
                    Species::Cloyster, Species::Gastly, Species::Haunter, Species::Gengar,
                    Species::Onix, Species::Krabby, Species::Kingler, Species::Hitmonlee,
                    Species::Hitmonchan, Species::Koffing, Species::Weezing, Species::Rhyhorn,
                    Species::Rhydon, Species::Goldeen, Species::Seaking, Species::MrMime,
                    Species::Magikarp, Species::Gyarados, Species::Lapras, Species::Ditto,
                    Species::Eevee, Species::Vaporeon, Species::Jolteon, Species::Flareon,
                    Species::Snorlax, Species::Mewtwo, Species::Mew, Species::Hoothoot,
                    Species::Noctowl, Species::Chinchou, Species::Lanturn, Species::Pichu,
                    Species::Cleffa, Species::Togepi, Species::Togetic, Species::Natu,
                    Species::Xatu, Species::Bellossom, Species::Sudowoodo, Species::Wooper,
                    Species::Quagsire, Species::Espeon, Species::Umbreon, Species::Wobbuffet,
                    Species::Steelix, Species::Qwilfish, Species::Shuckle, Species::Sneasel,
                    Species::Swinub, Species::Piloswine, Species::Corsola, Species::Remoraid,
                    Species::Octillery, Species::Delibird, Species::Mantine, Species::Tyrogue,
                    Species::Hitmontop, Species::Larvitar, Species::Pupitar, Species::Tyranitar,
                    Species::Celebi, Species::Zigzagoon, Species::Linoone, Species::Lotad,
                    Species::Lombre, Species::Ludicolo, Species::Seedot, Species::Nuzleaf,
                    Species::Shiftry, Species::Wingull, Species::Pelipper, Species::Ralts,
                    Species::Kirlia, Species::Gardevoir, Species::Nincada, Species::Ninjask,
                    Species::Shedinja, Species::Sableye, Species::Mawile, Species::Electrike,
                    Species::Manectric, Species::Roselia, Species::Wailmer, Species::Wailord,
                    Species::Torkoal, Species::Trapinch, Species::Vibrava, Species::Flygon,
                    Species::Lunatone, Species::Solrock, Species::Barboach, Species::Whiscash,
                    Species::Corphish, Species::Crawdaunt, Species::Baltoy, Species::Claydol,
                    Species::Feebas, Species::Milotic, Species::Duskull, Species::Dusclops,
                    Species::Wynaut, Species::Snorunt, Species::Glalie, Species::Jirachi,
                    Species::Budew, Species::Roserade, Species::Combee, Species::Vespiquen,
                    Species::Cherubi, Species::Cherrim, Species::Shellos, Species::Gastrodon,
                    Species::Drifloon, Species::Drifblim, Species::Stunky, Species::Skuntank,
                    Species::Bronzor, Species::Bronzong, Species::Bonsly, Species::MimeJr,
                    Species::Munchlax, Species::Riolu, Species::Lucario, Species::Hippopotas,
                    Species::Hippowdon, Species::Skorupi, Species::Drapion, Species::Croagunk,
                    Species::Toxicroak, Species::Mantyke, Species::Snover, Species::Abomasnow,
                    Species::Weavile, Species::Rhyperior, Species::Togekiss, Species::Leafeon,
                    Species::Glaceon, Species::Mamoswine, Species::Gallade, Species::Dusknoir,
                    Species::Froslass, Species::Rotom, Species::Purrloin, Species::Liepard,
                    Species::Munna, Species::Musharna, Species::Pidove, Species::Tranquill,
                    Species::Unfezant, Species::Roggenrola, Species::Boldore, Species::Gigalith,
                    Species::Woobat, Species::Swoobat, Species::Drilbur, Species::Excadrill,
                    Species::Timburr, Species::Gurdurr, Species::Conkeldurr, Species::Tympole,
                    Species::Palpitoad, Species::Seismitoad, Species::Throh, Species::Sawk,
                    Species::Cottonee, Species::Whimsicott, Species::Basculin, Species::Darumaka,
                    Species::Darmanitan, Species::Maractus, Species::Dwebble, Species::Crustle,
                    Species::Scraggy, Species::Scrafty, Species::Sigilyph, Species::Yamask,
                    Species::Cofagrigus, Species::Trubbish, Species::Garbodor, Species::Minccino,
                    Species::Cinccino, Species::Gothita, Species::Gothorita, Species::Gothitelle,
                    Species::Solosis, Species::Duosion, Species::Reuniclus, Species::Vanillite,
                    Species::Vanillish, Species::Vanilluxe, Species::Karrablast,
                    Species::Escavalier, Species::Frillish, Species::Jellicent, Species::Joltik,
                    Species::Galvantula, Species::Ferroseed, Species::Ferrothorn, Species::Klink,
                    Species::Klang, Species::Klinklang, Species::Elgyem, Species::Beheeyem,
                    Species::Litwick, Species::Lampent, Species::Chandelure, Species::Axew,
                    Species::Fraxure, Species::Haxorus, Species::Cubchoo, Species::Beartic,
                    Species::Shelmet, Species::Accelgor, Species::Stunfisk, Species::Golett,
                    Species::Golurk, Species::Pawniard, Species::Bisharp, Species::Rufflet,
                    Species::Braviary, Species::Vullaby, Species::Mandibuzz, Species::Heatmor,
                    Species::Durant, Species::Deino, Species::Zweilous, Species::Hydreigon,
                    Species::Cobalion, Species::Terrakion, Species::Virizion, Species::Reshiram,
                    Species::Zekrom, Species::Kyurem, Species::Keldeo, Species::Bunnelby,
                    Species::Diggersby, Species::Pancham, Species::Pangoro, Species::Espurr,
                    Species::Meowstic, Species::Honedge, Species::Doublade, Species::Aegislash,
                    Species::Spritzee, Species::Aromatisse, Species::Swirlix, Species::Slurpuff,
                    Species::Inkay, Species::Malamar, Species::Binacle, Species::Barbaracle,
                    Species::Helioptile, Species::Heliolisk, Species::Sylveon, Species::Hawlucha,
                    Species::Goomy, Species::Sliggoo, Species::Goodra, Species::Phantump,
                    Species::Trevenant, Species::Pumpkaboo, Species::Gourgeist, Species::Bergmite,
                    Species::Avalugg, Species::Noibat, Species::Noivern, Species::Rowlet,
                    Species::Dartrix, Species::Decidueye, Species::Litten, Species::Torracat,
                    Species::Incineroar, Species::Popplio, Species::Brionne, Species::Primarina,
                    Species::Grubbin, Species::Charjabug, Species::Vikavolt, Species::Cutiefly,
                    Species::Ribombee, Species::Wishiwashi, Species::Mareanie, Species::Toxapex,
                    Species::Mudbray, Species::Mudsdale, Species::Dewpider, Species::Araquanid,
                    Species::Morelull, Species::Shiinotic, Species::Salandit, Species::Salazzle,
                    Species::Stufful, Species::Bewear, Species::Bounsweet, Species::Steenee,
                    Species::Tsareena, Species::Oranguru, Species::Passimian, Species::Wimpod,
                    Species::Golisopod, Species::Pyukumuku, Species::TypeNull, Species::Silvally,
                    Species::Turtonator, Species::Togedemaru, Species::Mimikyu, Species::Drampa,
                    Species::Dhelmise, Species::Jangmoo, Species::Hakamoo, Species::Kommoo,
                    Species::Cosmog, Species::Cosmoem, Species::Solgaleo, Species::Lunala,
                    Species::Necrozma, Species::Marshadow, Species::Zeraora, Species::Meltan,
                    Species::Melmetal, Species::Grookey, Species::Thwackey, Species::Rillaboom,
                    Species::Scorbunny, Species::Raboot, Species::Cinderace, Species::Sobble,
                    Species::Drizzile, Species::Inteleon, Species::Skwovet, Species::Greedent,
                    Species::Rookidee, Species::Corvisquire, Species::Corviknight, Species::Blipbug,
                    Species::Dottler, Species::Orbeetle, Species::Nickit, Species::Thievul,
                    Species::Gossifleur, Species::Eldegoss, Species::Wooloo, Species::Dubwool,
                    Species::Chewtle, Species::Drednaw, Species::Yamper, Species::Boltund,
                    Species::Rolycoly, Species::Carkol, Species::Coalossal, Species::Applin,
                    Species::Flapple, Species::Appletun, Species::Silicobra, Species::Sandaconda,
                    Species::Cramorant, Species::Arrokuda, Species::Barraskewda, Species::Toxel,
                    Species::Toxtricity, Species::Sizzlipede, Species::Centiskorch,
                    Species::Clobbopus, Species::Grapploct, Species::Sinistea, Species::Polteageist,
                    Species::Hatenna, Species::Hattrem, Species::Hatterene, Species::Impidimp,
                    Species::Morgrem, Species::Grimmsnarl, Species::Obstagoon, Species::Perrserker,
                    Species::Cursola, Species::Sirfetchd, Species::MrRime, Species::Runerigus,
                    Species::Milcery, Species::Alcremie, Species::Falinks, Species::Pincurchin,
                    Species::Snom, Species::Frosmoth, Species::Stonjourner, Species::Eiscue,
                    Species::Indeedee, Species::Morpeko, Species::Cufant, Species::Copperajah,
                    Species::Dracozolt, Species::Arctozolt, Species::Dracovish, Species::Arctovish,
                    Species::Duraludon, Species::Dreepy, Species::Drakloak, Species::Dragapult,
                    Species::Zacian, Species::Zamazenta, Species::Eternatus,

                    // Isle of Armor
                    Species::Sandshrew, Species::Sandslash, Species::Jigglypuff,
                    Species::Wigglytuff, Species::Psyduck, Species::Golduck, Species::Poliwag,
                    Species::Poliwhirl, Species::Poliwrath, Species::Abra, Species::Kadabra,
                    Species::Alakazam, Species::Tentacool, Species::Tentacruel, Species::Slowpoke,
                    Species::Slowbro, Species::Magnemite, Species::Magneton, Species::Exeggcute,
                    Species::Exeggutor, Species::Cubone, Species::Marowak, Species::Lickitung,
                    Species::Chansey, Species::Tangela, Species::Kangaskhan, Species::Horsea,
                    Species::Seadra, Species::Staryu, Species::Starmie, Species::Scyther,
                    Species::Pinsir, Species::Tauros, Species::Igglybuff, Species::Marill,
                    Species::Azumarill, Species::Politoed, Species::Slowking, Species::Dunsparce,
                    Species::Scizor, Species::Heracross, Species::Skarmory, Species::Kingdra,
                    Species::Porygon2, Species::Miltank, Species::Blissey, Species::Whismur,
                    Species::Loudred, Species::Exploud, Species::Azurill, Species::Carvanha,
                    Species::Sharpedo, Species::Shinx, Species::Luxio, Species::Luxray,
                    Species::Buneary, Species::Lopunny, Species::Happiny, Species::Magnezone,
                    Species::Lickilicky, Species::Tangrowth, Species::PorygonZ, Species::Lillipup,
                    Species::Herdier, Species::Stoutland, Species::Venipede, Species::Whirlipede,
                    Species::Scolipede, Species::Petilil, Species::Lilligant, Species::Sandile,
                    Species::Krokorok, Species::Krookodile, Species::Zorua, Species::Zoroark,
                    Species::Emolga, Species::Foongus, Species::Amoonguss, Species::Mienfoo,
                    Species::Mienshao, Species::Druddigon, Species::Bouffalant, Species::Larvesta,
                    Species::Volcarona, Species::Fletchling, Species::Fletchinder,
                    Species::Talonflame, Species::Skrelp, Species::Dragalge, Species::Clauncher,
                    Species::Clawitzer, Species::Dedenne, Species::Klefki, Species::Rockruff,
                    Species::Lycanroc, Species::Fomantis, Species::Lurantis, Species::Comfey,
                    Species::Sandygast, Species::Palossand, Species::Magearna, Species::Kubfu,
                    Species::Urshifu, Species::Zarude};
                return items;
            }
            default:
                return emptySet;
        }
    }

    const std::set<Ability>& VersionTables::availableAbilities(GameVersion version)
    {
        static const std::set<Ability> emptySet;
        switch (version)
        {
            case GameVersion::R:
            case GameVersion::S:
            case GameVersion::FR:
            case GameVersion::LG:
            case GameVersion::E:
            {
                static const std::set<Ability> items = std::invoke([]() {
                    return create_set_consecutive<Ability>(Ability::Stench, Ability::TangledFeet);
                });
                return items;
            }
            case GameVersion::D:
            case GameVersion::P:
            case GameVersion::Pt:
            case GameVersion::HG:
            case GameVersion::SS:
            {
                static const std::set<Ability> items = std::invoke([]() {
                    return create_set_consecutive<Ability>(Ability::Stench, Ability::BadDreams);
                });
                return items;
            }
            case GameVersion::B:
            case GameVersion::W:
            case GameVersion::B2:
            case GameVersion::W2:
            {
                static const std::set<Ability> items = std::invoke([]() {
                    return create_set_consecutive<Ability>(Ability::Stench, Ability::Teravolt);
                });
                return items;
            }
            case GameVersion::X:
            case GameVersion::Y:
            {
                static const std::set<Ability> items = std::invoke([]() {
                    return create_set_consecutive<Ability>(Ability::Stench, Ability::AuraBreak);
                });
                return items;
            }
            case GameVersion::OR:
            case GameVersion::AS:
            {
                static const std::set<Ability> items = std::invoke([]() {
                    return create_set_consecutive<Ability>(Ability::Stench, Ability::DeltaStream);
                });
                return items;
            }
            case GameVersion::SN:
            case GameVersion::MN:
            {
                static const std::set<Ability> items = std::invoke([]() {
                    return create_set_consecutive<Ability>(Ability::Stench, Ability::PrismArmor);
                });
                return items;
            }
            case GameVersion::US:
            case GameVersion::UM:
            {
                static const std::set<Ability> items = std::invoke([]() {
                    return create_set_consecutive<Ability>(Ability::Stench, Ability::Neuroforce);
                });
                return items;
            }
            case GameVersion::GE:
            case GameVersion::GP:
            {
                static const std::set<Ability> items = std::invoke([]() {
                    return create_set_consecutive<Ability>(Ability::Stench, Ability::Neuroforce);
                });
                return items;
            }
            case GameVersion::SW:
            case GameVersion::SH:
            {
                static const std::set<Ability> items = std::invoke([]() {
                    return create_set_consecutive<Ability>(Ability::Stench, Ability::UnseenFist);
                });
                return items;
            }
            default:
                return emptySet;
        }
    }

    const std::set<Ball>& VersionTables::availableBalls(GameVersion version)
    {
        static const std::set<Ball> emptySet;
        switch ((Generation)version)
        {
            case Generation::THREE:
            {
                static const std::set<Ball> items = std::invoke(
                    []() { return create_set_consecutive<Ball>(Ball::Master, Ball::Premier); });
                return items;
            }
            case Generation::FOUR:
            {
                static const std::set<Ball> items = std::invoke(
                    []() { return create_set_consecutive<Ball>(Ball::Master, Ball::Sport); });
                return items;
            }
            case Generation::FIVE:
            case Generation::SIX:
            {
                static const std::set<Ball> items = std::invoke(
                    []() { return create_set_consecutive<Ball>(Ball::Master, Ball::Dream); });
                return items;
            }
            case Generation::SEVEN:
            case Generation::LGPE:
            case Generation::EIGHT:
            {
                static const std::set<Ball> items = std::invoke(
                    []() { return create_set_consecutive<Ball>(Ball::Master, Ball::Beast); });
                return items;
            }
            default:
                return emptySet;
        }
    }

    int VersionTables::maxItem(GameVersion version)
    {
        switch (version)
        {
            case GameVersion::R:
            case GameVersion::S:
            case GameVersion::FR:
            case GameVersion::LG:
            case GameVersion::E:
                return 374;
            case GameVersion::D:
            case GameVersion::P:
                return 464;
            case GameVersion::Pt:
                return 467;
            case GameVersion::HG:
            case GameVersion::SS:
                return 536;
            case GameVersion::B:
            case GameVersion::W:
                return 632;
            case GameVersion::B2:
            case GameVersion::W2:
                return 638;
            case GameVersion::X:
            case GameVersion::Y:
                return 717;
            case GameVersion::OR:
            case GameVersion::AS:
                return 775;
            case GameVersion::SN:
            case GameVersion::MN:
                return 920;
            case GameVersion::US:
            case GameVersion::UM:
                return 959;
            case GameVersion::GE:
            case GameVersion::GP:
                return 1057;
            case GameVersion::SW:
            case GameVersion::SH:
                return 1589;
            default:
                return 0;
        }
    }

    Move VersionTables::maxMove(GameVersion version)
    {
        switch (version)
        {
            case GameVersion::R:
            case GameVersion::S:
            case GameVersion::FR:
            case GameVersion::LG:
            case GameVersion::E:
                return Move::PsychoBoost;
            case GameVersion::D:
            case GameVersion::P:
            case GameVersion::Pt:
            case GameVersion::HG:
            case GameVersion::SS:
                return Move::ShadowForce;
            case GameVersion::B:
            case GameVersion::W:
            case GameVersion::B2:
            case GameVersion::W2:
                return Move::FusionBolt;
            case GameVersion::X:
            case GameVersion::Y:
                return Move::LightofRuin;
            case GameVersion::OR:
            case GameVersion::AS:
                return Move::HyperspaceFury;
            case GameVersion::SN:
            case GameVersion::MN:
                return Move::MindBlown;
            case GameVersion::US:
            case GameVersion::UM:
                return Move::ClangorousSoulblaze;
            case GameVersion::GE:
            case GameVersion::GP:
                return Move::DoubleIronBash;
            case GameVersion::SW:
            case GameVersion::SH:
                return Move::SurgingStrikes;
            default:
                return Move::None;
        }
    }

    Species VersionTables::maxSpecies(GameVersion version)
    {
        switch (version)
        {
            case GameVersion::R:
            case GameVersion::S:
            case GameVersion::FR:
            case GameVersion::LG:
            case GameVersion::E:
                return Species::Deoxys;
            case GameVersion::D:
            case GameVersion::P:
            case GameVersion::Pt:
            case GameVersion::HG:
            case GameVersion::SS:
                return Species::Arceus;
            case GameVersion::B:
            case GameVersion::W:
            case GameVersion::B2:
            case GameVersion::W2:
                return Species::Genesect;
            case GameVersion::X:
            case GameVersion::Y:
            case GameVersion::OR:
            case GameVersion::AS:
                return Species::Volcanion;
            case GameVersion::SN:
            case GameVersion::MN:
                return Species::Marshadow;
            case GameVersion::US:
            case GameVersion::UM:
                return Species::Zeraora;
            case GameVersion::GE:
            case GameVersion::GP:
                return Species::Melmetal;
            case GameVersion::SW:
            case GameVersion::SH:
                return Species::Zarude;
            default:
                return Species::None;
        }
    }

    Ability VersionTables::maxAbility(GameVersion version)
    {
        switch (version)
        {
            case GameVersion::R:
            case GameVersion::S:
            case GameVersion::FR:
            case GameVersion::LG:
            case GameVersion::E:
                return Ability::TangledFeet;
            case GameVersion::D:
            case GameVersion::P:
            case GameVersion::Pt:
            case GameVersion::HG:
            case GameVersion::SS:
                return Ability::BadDreams;
            case GameVersion::B:
            case GameVersion::W:
            case GameVersion::B2:
            case GameVersion::W2:
                return Ability::Teravolt;
            case GameVersion::X:
            case GameVersion::Y:
                return Ability::AuraBreak;
            case GameVersion::OR:
            case GameVersion::AS:
                return Ability::DeltaStream;
            case GameVersion::SN:
            case GameVersion::MN:
                return Ability::PrismArmor;
            case GameVersion::US:
            case GameVersion::UM:
                return Ability::Neuroforce;
            case GameVersion::GE:
            case GameVersion::GP:
                return Ability::Neuroforce;
            case GameVersion::SW:
            case GameVersion::SH:
                return Ability::UnseenFist;
            default:
                return Ability::None;
        }
    }

    Ball VersionTables::maxBall(GameVersion version)
    {
        switch ((Generation)version)
        {
            case Generation::THREE:
                return Ball::Premier;
            case Generation::FOUR:
                return Ball::Sport;
            case Generation::FIVE:
            case Generation::SIX:
                return Ball::Dream;
            case Generation::SEVEN:
            case Generation::LGPE:
            case Generation::EIGHT:
                return Ball::Beast;
            default:
                return Ball::None;
        }
    }

    u8 VersionTables::formCount(GameVersion version, Species species)
    {
        switch (version)
        {
            case GameVersion::R:
            case GameVersion::S:
            case GameVersion::FR:
            case GameVersion::LG:
            case GameVersion::E:
                return PersonalRSFRLGE::formCount(u16(species));
            case GameVersion::D:
            case GameVersion::P:
                if (species == Species::Rotom || species == Species::Giratina ||
                    species == Species::Shaymin)
                {
                    return 1;
                }
            // falls through
            case GameVersion::Pt:
                if (species == Species::Pichu)
                {
                    return 1;
                }
                // falls through
            case GameVersion::HG:
            case GameVersion::SS:
                return PersonalDPPtHGSS::formCount(u16(species));
            case GameVersion::B:
            case GameVersion::W:
                if (species == Species::Tornadus || species == Species::Thundurus ||
                    species == Species::Landorus || species == Species::Kyurem ||
                    species == Species::Keldeo)
                {
                    return 1;
                }
            // falls through
            case GameVersion::B2:
            case GameVersion::W2:
                return PersonalBWB2W2::formCount(u16(species));
            case GameVersion::X:
            case GameVersion::Y:
                if (species == Species::Beedrill || species == Species::Pidgeot ||
                    species == Species::Pikachu || species == Species::Slowbro ||
                    species == Species::Steelix || species == Species::Sceptile ||
                    species == Species::Swampert || species == Species::Sableye ||
                    species == Species::Sharpedo || species == Species::Camerupt ||
                    species == Species::Altaria || species == Species::Glalie ||
                    species == Species::Salamence || species == Species::Metagross ||
                    species == Species::Kyogre || species == Species::Groudon ||
                    species == Species::Rayquaza || species == Species::Lopunny ||
                    species == Species::Gallade || species == Species::Audino ||
                    species == Species::Hoopa || species == Species::Diancie)
                {
                    return 1;
                }
                // falls through
            case GameVersion::OR:
            case GameVersion::AS:
                return PersonalXYORAS::formCount(u16(species));
            case GameVersion::SN:
            case GameVersion::MN:
                if (species == Species::Lycanroc)
                {
                    return 2;
                }
                if (species == Species::Pikachu)
                {
                    return 6;
                }
                if (species == Species::Necrozma)
                {
                    return 1;
                }
                // falls through
            case GameVersion::US:
            case GameVersion::UM:
                return PersonalSMUSUM::formCount(u16(species));
            case GameVersion::GE:
            case GameVersion::GP:
                return PersonalLGPE::formCount(u16(species));
            case GameVersion::SW:
            case GameVersion::SH:
                return PersonalSWSH::formCount(u16(species));
            default:
                return 1;
        }
    }

    u8 VersionTables::movePP(pksm::Generation gen, Move move, u8 ppUps)
    {
        if (move == pksm::Move::INVALID || move == pksm::Move::None ||
            size_t(move) >= internal::PP_G8.size())
        {
            return 0;
        }
        u8 val = 0;
        switch (gen)
        {
            case pksm::Generation::EIGHT:
            case pksm::Generation::SEVEN:
                val = internal::PP_G8[size_t(move)];
                break;
            case pksm::Generation::SIX:
            {
                auto found = std::find_if(internal::PPDiff_G6.begin(), internal::PPDiff_G6.end(),
                    [move](const std::pair<pksm::Move, u8>& v) { return v.first == move; });
                if (found != internal::PPDiff_G6.end())
                {
                    val = found->second;
                }
                else
                {
                    val = internal::PP_G8[size_t(move)];
                }
            }
            break;
            case pksm::Generation::FIVE:
            {
                auto found = std::find_if(internal::PPDiff_G5.begin(), internal::PPDiff_G5.end(),
                    [move](const std::pair<pksm::Move, u8>& v) { return v.first == move; });
                if (found != internal::PPDiff_G5.end())
                {
                    val = found->second;
                }
                else
                {
                    val = internal::PP_G8[size_t(move)];
                }
            }
            break;
            case pksm::Generation::FOUR:
            {
                auto found = std::find_if(internal::PPDiff_G4.begin(), internal::PPDiff_G4.end(),
                    [move](const std::pair<pksm::Move, u8>& v) { return v.first == move; });
                if (found != internal::PPDiff_G4.end())
                {
                    val = found->second;
                }
                else
                {
                    val = internal::PP_G8[size_t(move)];
                }
            }
            break;
            case pksm::Generation::THREE:
            {
                auto found = std::find_if(internal::PPDiff_G3.begin(), internal::PPDiff_G3.end(),
                    [move](const std::pair<pksm::Move, u8>& v) { return v.first == move; });
                if (found != internal::PPDiff_G3.end())
                {
                    val = found->second;
                }
                else
                {
                    val = internal::PP_G8[size_t(move)];
                }
            }
            break;
            case pksm::Generation::LGPE:
            {
                auto found =
                    std::find_if(internal::PPDiff_LGPE.begin(), internal::PPDiff_LGPE.end(),
                        [move](const std::pair<pksm::Move, u8>& v) { return v.first == move; });
                if (found != internal::PPDiff_LGPE.end())
                {
                    val = found->second;
                }
                else
                {
                    val = internal::PP_G8[size_t(move)];
                }
            }
            break;
            default:
                // TODO: G1/2 (very low priority)
                return 0;
        }

        // Stupid thing G1/2 does: they can't store above 63 for PP value
        if (gen <= pksm::Generation::TWO && val == 40)
        {
            return val + 7 * ppUps;
        }
        return val + ((val / 5) * ppUps);
    }
}
