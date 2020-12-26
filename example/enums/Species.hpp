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

#ifndef SPECIES_HPP
#define SPECIES_HPP

#include "enums/Generation.hpp"
#include "enums/Language.hpp"
#include <limits>
#include <type_traits>

namespace pksm
{
    class Species;
    namespace internal
    {
        class Species_impl
        {
            friend class pksm::Species;

        private:
            enum class SpeciesEnum : u16
            {
                None,
                Bulbasaur,
                Ivysaur,
                Venusaur,
                Charmander,
                Charmeleon,
                Charizard,
                Squirtle,
                Wartortle,
                Blastoise,
                Caterpie,
                Metapod,
                Butterfree,
                Weedle,
                Kakuna,
                Beedrill,
                Pidgey,
                Pidgeotto,
                Pidgeot,
                Rattata,
                Raticate,
                Spearow,
                Fearow,
                Ekans,
                Arbok,
                Pikachu,
                Raichu,
                Sandshrew,
                Sandslash,
                NidoranF,
                Nidorina,
                Nidoqueen,
                NidoranM,
                Nidorino,
                Nidoking,
                Clefairy,
                Clefable,
                Vulpix,
                Ninetales,
                Jigglypuff,
                Wigglytuff,
                Zubat,
                Golbat,
                Oddish,
                Gloom,
                Vileplume,
                Paras,
                Parasect,
                Venonat,
                Venomoth,
                Diglett,
                Dugtrio,
                Meowth,
                Persian,
                Psyduck,
                Golduck,
                Mankey,
                Primeape,
                Growlithe,
                Arcanine,
                Poliwag,
                Poliwhirl,
                Poliwrath,
                Abra,
                Kadabra,
                Alakazam,
                Machop,
                Machoke,
                Machamp,
                Bellsprout,
                Weepinbell,
                Victreebel,
                Tentacool,
                Tentacruel,
                Geodude,
                Graveler,
                Golem,
                Ponyta,
                Rapidash,
                Slowpoke,
                Slowbro,
                Magnemite,
                Magneton,
                Farfetchd,
                Doduo,
                Dodrio,
                Seel,
                Dewgong,
                Grimer,
                Muk,
                Shellder,
                Cloyster,
                Gastly,
                Haunter,
                Gengar,
                Onix,
                Drowzee,
                Hypno,
                Krabby,
                Kingler,
                Voltorb,
                Electrode,
                Exeggcute,
                Exeggutor,
                Cubone,
                Marowak,
                Hitmonlee,
                Hitmonchan,
                Lickitung,
                Koffing,
                Weezing,
                Rhyhorn,
                Rhydon,
                Chansey,
                Tangela,
                Kangaskhan,
                Horsea,
                Seadra,
                Goldeen,
                Seaking,
                Staryu,
                Starmie,
                MrMime,
                Scyther,
                Jynx,
                Electabuzz,
                Magmar,
                Pinsir,
                Tauros,
                Magikarp,
                Gyarados,
                Lapras,
                Ditto,
                Eevee,
                Vaporeon,
                Jolteon,
                Flareon,
                Porygon,
                Omanyte,
                Omastar,
                Kabuto,
                Kabutops,
                Aerodactyl,
                Snorlax,
                Articuno,
                Zapdos,
                Moltres,
                Dratini,
                Dragonair,
                Dragonite,
                Mewtwo,
                Mew,
                Chikorita,
                Bayleef,
                Meganium,
                Cyndaquil,
                Quilava,
                Typhlosion,
                Totodile,
                Croconaw,
                Feraligatr,
                Sentret,
                Furret,
                Hoothoot,
                Noctowl,
                Ledyba,
                Ledian,
                Spinarak,
                Ariados,
                Crobat,
                Chinchou,
                Lanturn,
                Pichu,
                Cleffa,
                Igglybuff,
                Togepi,
                Togetic,
                Natu,
                Xatu,
                Mareep,
                Flaaffy,
                Ampharos,
                Bellossom,
                Marill,
                Azumarill,
                Sudowoodo,
                Politoed,
                Hoppip,
                Skiploom,
                Jumpluff,
                Aipom,
                Sunkern,
                Sunflora,
                Yanma,
                Wooper,
                Quagsire,
                Espeon,
                Umbreon,
                Murkrow,
                Slowking,
                Misdreavus,
                Unown,
                Wobbuffet,
                Girafarig,
                Pineco,
                Forretress,
                Dunsparce,
                Gligar,
                Steelix,
                Snubbull,
                Granbull,
                Qwilfish,
                Scizor,
                Shuckle,
                Heracross,
                Sneasel,
                Teddiursa,
                Ursaring,
                Slugma,
                Magcargo,
                Swinub,
                Piloswine,
                Corsola,
                Remoraid,
                Octillery,
                Delibird,
                Mantine,
                Skarmory,
                Houndour,
                Houndoom,
                Kingdra,
                Phanpy,
                Donphan,
                Porygon2,
                Stantler,
                Smeargle,
                Tyrogue,
                Hitmontop,
                Smoochum,
                Elekid,
                Magby,
                Miltank,
                Blissey,
                Raikou,
                Entei,
                Suicune,
                Larvitar,
                Pupitar,
                Tyranitar,
                Lugia,
                HoOh,
                Celebi,
                Treecko,
                Grovyle,
                Sceptile,
                Torchic,
                Combusken,
                Blaziken,
                Mudkip,
                Marshtomp,
                Swampert,
                Poochyena,
                Mightyena,
                Zigzagoon,
                Linoone,
                Wurmple,
                Silcoon,
                Beautifly,
                Cascoon,
                Dustox,
                Lotad,
                Lombre,
                Ludicolo,
                Seedot,
                Nuzleaf,
                Shiftry,
                Taillow,
                Swellow,
                Wingull,
                Pelipper,
                Ralts,
                Kirlia,
                Gardevoir,
                Surskit,
                Masquerain,
                Shroomish,
                Breloom,
                Slakoth,
                Vigoroth,
                Slaking,
                Nincada,
                Ninjask,
                Shedinja,
                Whismur,
                Loudred,
                Exploud,
                Makuhita,
                Hariyama,
                Azurill,
                Nosepass,
                Skitty,
                Delcatty,
                Sableye,
                Mawile,
                Aron,
                Lairon,
                Aggron,
                Meditite,
                Medicham,
                Electrike,
                Manectric,
                Plusle,
                Minun,
                Volbeat,
                Illumise,
                Roselia,
                Gulpin,
                Swalot,
                Carvanha,
                Sharpedo,
                Wailmer,
                Wailord,
                Numel,
                Camerupt,
                Torkoal,
                Spoink,
                Grumpig,
                Spinda,
                Trapinch,
                Vibrava,
                Flygon,
                Cacnea,
                Cacturne,
                Swablu,
                Altaria,
                Zangoose,
                Seviper,
                Lunatone,
                Solrock,
                Barboach,
                Whiscash,
                Corphish,
                Crawdaunt,
                Baltoy,
                Claydol,
                Lileep,
                Cradily,
                Anorith,
                Armaldo,
                Feebas,
                Milotic,
                Castform,
                Kecleon,
                Shuppet,
                Banette,
                Duskull,
                Dusclops,
                Tropius,
                Chimecho,
                Absol,
                Wynaut,
                Snorunt,
                Glalie,
                Spheal,
                Sealeo,
                Walrein,
                Clamperl,
                Huntail,
                Gorebyss,
                Relicanth,
                Luvdisc,
                Bagon,
                Shelgon,
                Salamence,
                Beldum,
                Metang,
                Metagross,
                Regirock,
                Regice,
                Registeel,
                Latias,
                Latios,
                Kyogre,
                Groudon,
                Rayquaza,
                Jirachi,
                Deoxys,
                Turtwig,
                Grotle,
                Torterra,
                Chimchar,
                Monferno,
                Infernape,
                Piplup,
                Prinplup,
                Empoleon,
                Starly,
                Staravia,
                Staraptor,
                Bidoof,
                Bibarel,
                Kricketot,
                Kricketune,
                Shinx,
                Luxio,
                Luxray,
                Budew,
                Roserade,
                Cranidos,
                Rampardos,
                Shieldon,
                Bastiodon,
                Burmy,
                Wormadam,
                Mothim,
                Combee,
                Vespiquen,
                Pachirisu,
                Buizel,
                Floatzel,
                Cherubi,
                Cherrim,
                Shellos,
                Gastrodon,
                Ambipom,
                Drifloon,
                Drifblim,
                Buneary,
                Lopunny,
                Mismagius,
                Honchkrow,
                Glameow,
                Purugly,
                Chingling,
                Stunky,
                Skuntank,
                Bronzor,
                Bronzong,
                Bonsly,
                MimeJr,
                Happiny,
                Chatot,
                Spiritomb,
                Gible,
                Gabite,
                Garchomp,
                Munchlax,
                Riolu,
                Lucario,
                Hippopotas,
                Hippowdon,
                Skorupi,
                Drapion,
                Croagunk,
                Toxicroak,
                Carnivine,
                Finneon,
                Lumineon,
                Mantyke,
                Snover,
                Abomasnow,
                Weavile,
                Magnezone,
                Lickilicky,
                Rhyperior,
                Tangrowth,
                Electivire,
                Magmortar,
                Togekiss,
                Yanmega,
                Leafeon,
                Glaceon,
                Gliscor,
                Mamoswine,
                PorygonZ,
                Gallade,
                Probopass,
                Dusknoir,
                Froslass,
                Rotom,
                Uxie,
                Mesprit,
                Azelf,
                Dialga,
                Palkia,
                Heatran,
                Regigigas,
                Giratina,
                Cresselia,
                Phione,
                Manaphy,
                Darkrai,
                Shaymin,
                Arceus,
                Victini,
                Snivy,
                Servine,
                Serperior,
                Tepig,
                Pignite,
                Emboar,
                Oshawott,
                Dewott,
                Samurott,
                Patrat,
                Watchog,
                Lillipup,
                Herdier,
                Stoutland,
                Purrloin,
                Liepard,
                Pansage,
                Simisage,
                Pansear,
                Simisear,
                Panpour,
                Simipour,
                Munna,
                Musharna,
                Pidove,
                Tranquill,
                Unfezant,
                Blitzle,
                Zebstrika,
                Roggenrola,
                Boldore,
                Gigalith,
                Woobat,
                Swoobat,
                Drilbur,
                Excadrill,
                Audino,
                Timburr,
                Gurdurr,
                Conkeldurr,
                Tympole,
                Palpitoad,
                Seismitoad,
                Throh,
                Sawk,
                Sewaddle,
                Swadloon,
                Leavanny,
                Venipede,
                Whirlipede,
                Scolipede,
                Cottonee,
                Whimsicott,
                Petilil,
                Lilligant,
                Basculin,
                Sandile,
                Krokorok,
                Krookodile,
                Darumaka,
                Darmanitan,
                Maractus,
                Dwebble,
                Crustle,
                Scraggy,
                Scrafty,
                Sigilyph,
                Yamask,
                Cofagrigus,
                Tirtouga,
                Carracosta,
                Archen,
                Archeops,
                Trubbish,
                Garbodor,
                Zorua,
                Zoroark,
                Minccino,
                Cinccino,
                Gothita,
                Gothorita,
                Gothitelle,
                Solosis,
                Duosion,
                Reuniclus,
                Ducklett,
                Swanna,
                Vanillite,
                Vanillish,
                Vanilluxe,
                Deerling,
                Sawsbuck,
                Emolga,
                Karrablast,
                Escavalier,
                Foongus,
                Amoonguss,
                Frillish,
                Jellicent,
                Alomomola,
                Joltik,
                Galvantula,
                Ferroseed,
                Ferrothorn,
                Klink,
                Klang,
                Klinklang,
                Tynamo,
                Eelektrik,
                Eelektross,
                Elgyem,
                Beheeyem,
                Litwick,
                Lampent,
                Chandelure,
                Axew,
                Fraxure,
                Haxorus,
                Cubchoo,
                Beartic,
                Cryogonal,
                Shelmet,
                Accelgor,
                Stunfisk,
                Mienfoo,
                Mienshao,
                Druddigon,
                Golett,
                Golurk,
                Pawniard,
                Bisharp,
                Bouffalant,
                Rufflet,
                Braviary,
                Vullaby,
                Mandibuzz,
                Heatmor,
                Durant,
                Deino,
                Zweilous,
                Hydreigon,
                Larvesta,
                Volcarona,
                Cobalion,
                Terrakion,
                Virizion,
                Tornadus,
                Thundurus,
                Reshiram,
                Zekrom,
                Landorus,
                Kyurem,
                Keldeo,
                Meloetta,
                Genesect,
                Chespin,
                Quilladin,
                Chesnaught,
                Fennekin,
                Braixen,
                Delphox,
                Froakie,
                Frogadier,
                Greninja,
                Bunnelby,
                Diggersby,
                Fletchling,
                Fletchinder,
                Talonflame,
                Scatterbug,
                Spewpa,
                Vivillon,
                Litleo,
                Pyroar,
                Flabebe,
                Floette,
                Florges,
                Skiddo,
                Gogoat,
                Pancham,
                Pangoro,
                Furfrou,
                Espurr,
                Meowstic,
                Honedge,
                Doublade,
                Aegislash,
                Spritzee,
                Aromatisse,
                Swirlix,
                Slurpuff,
                Inkay,
                Malamar,
                Binacle,
                Barbaracle,
                Skrelp,
                Dragalge,
                Clauncher,
                Clawitzer,
                Helioptile,
                Heliolisk,
                Tyrunt,
                Tyrantrum,
                Amaura,
                Aurorus,
                Sylveon,
                Hawlucha,
                Dedenne,
                Carbink,
                Goomy,
                Sliggoo,
                Goodra,
                Klefki,
                Phantump,
                Trevenant,
                Pumpkaboo,
                Gourgeist,
                Bergmite,
                Avalugg,
                Noibat,
                Noivern,
                Xerneas,
                Yveltal,
                Zygarde,
                Diancie,
                Hoopa,
                Volcanion,
                Rowlet,
                Dartrix,
                Decidueye,
                Litten,
                Torracat,
                Incineroar,
                Popplio,
                Brionne,
                Primarina,
                Pikipek,
                Trumbeak,
                Toucannon,
                Yungoos,
                Gumshoos,
                Grubbin,
                Charjabug,
                Vikavolt,
                Crabrawler,
                Crabominable,
                Oricorio,
                Cutiefly,
                Ribombee,
                Rockruff,
                Lycanroc,
                Wishiwashi,
                Mareanie,
                Toxapex,
                Mudbray,
                Mudsdale,
                Dewpider,
                Araquanid,
                Fomantis,
                Lurantis,
                Morelull,
                Shiinotic,
                Salandit,
                Salazzle,
                Stufful,
                Bewear,
                Bounsweet,
                Steenee,
                Tsareena,
                Comfey,
                Oranguru,
                Passimian,
                Wimpod,
                Golisopod,
                Sandygast,
                Palossand,
                Pyukumuku,
                TypeNull,
                Silvally,
                Minior,
                Komala,
                Turtonator,
                Togedemaru,
                Mimikyu,
                Bruxish,
                Drampa,
                Dhelmise,
                Jangmoo,
                Hakamoo,
                Kommoo,
                TapuKoko,
                TapuLele,
                TapuBulu,
                TapuFini,
                Cosmog,
                Cosmoem,
                Solgaleo,
                Lunala,
                Nihilego,
                Buzzwole,
                Pheromosa,
                Xurkitree,
                Celesteela,
                Kartana,
                Guzzlord,
                Necrozma,
                Magearna,
                Marshadow,
                Poipole,
                Naganadel,
                Stakataka,
                Blacephalon,
                Zeraora,
                Meltan,
                Melmetal,
                Grookey,
                Thwackey,
                Rillaboom,
                Scorbunny,
                Raboot,
                Cinderace,
                Sobble,
                Drizzile,
                Inteleon,
                Skwovet,
                Greedent,
                Rookidee,
                Corvisquire,
                Corviknight,
                Blipbug,
                Dottler,
                Orbeetle,
                Nickit,
                Thievul,
                Gossifleur,
                Eldegoss,
                Wooloo,
                Dubwool,
                Chewtle,
                Drednaw,
                Yamper,
                Boltund,
                Rolycoly,
                Carkol,
                Coalossal,
                Applin,
                Flapple,
                Appletun,
                Silicobra,
                Sandaconda,
                Cramorant,
                Arrokuda,
                Barraskewda,
                Toxel,
                Toxtricity,
                Sizzlipede,
                Centiskorch,
                Clobbopus,
                Grapploct,
                Sinistea,
                Polteageist,
                Hatenna,
                Hattrem,
                Hatterene,
                Impidimp,
                Morgrem,
                Grimmsnarl,
                Obstagoon,
                Perrserker,
                Cursola,
                Sirfetchd,
                MrRime,
                Runerigus,
                Milcery,
                Alcremie,
                Falinks,
                Pincurchin,
                Snom,
                Frosmoth,
                Stonjourner,
                Eiscue,
                Indeedee,
                Morpeko,
                Cufant,
                Copperajah,
                Dracozolt,
                Arctozolt,
                Dracovish,
                Arctovish,
                Duraludon,
                Dreepy,
                Drakloak,
                Dragapult,
                Zacian,
                Zamazenta,
                Eternatus,
                Kubfu,
                Urshifu,
                Zarude,
                Regieleki,
                Regidrago,
                Glastrier,
                Spectrier,
                Calyrex,

                INVALID [[maybe_unused]] =
                    std::numeric_limits<std::underlying_type_t<SpeciesEnum>>::max()
            } v;
            constexpr explicit Species_impl(SpeciesEnum v) : v(v) {}
            constexpr Species_impl(const Species_impl&) = default;
            constexpr Species_impl(Species_impl&&)      = default;
            constexpr Species_impl& operator=(const Species_impl&) = default;
            constexpr Species_impl& operator=(Species_impl&&) = default;

        public:
            template <typename T>
            constexpr explicit operator T() const noexcept
            {
                static_assert(std::is_integral_v<T>);
                return T(v);
            }
            constexpr operator SpeciesEnum() const noexcept { return v; }

            constexpr bool operator<(const Species_impl& other) const noexcept
            {
                return v < other.v;
            }
            constexpr bool operator<=(const Species_impl& other) const noexcept
            {
                return v <= other.v;
            }

            constexpr bool operator>(const Species_impl& other) const noexcept
            {
                return v > other.v;
            }
            constexpr bool operator>=(const Species_impl& other) const noexcept
            {
                return v >= other.v;
            }

            constexpr bool operator==(const Species_impl& other) const noexcept
            {
                return v == other.v;
            }
            constexpr bool operator!=(const Species_impl& other) const noexcept
            {
                return v != other.v;
            }

            const std::string& localize(Language lang) const;
        };
    }

    class Species
    {
    private:
        internal::Species_impl impl;

    public:
        using EnumType = internal::Species_impl::SpeciesEnum;
        constexpr Species() noexcept : impl(EnumType{0}) {}
        constexpr Species(const internal::Species_impl& impl) noexcept : impl(impl) {}
        constexpr explicit Species(std::underlying_type_t<EnumType> v) noexcept : impl(EnumType{v})
        {
        }
        template <typename T>
        constexpr explicit operator T() const noexcept
        {
            static_assert(std::is_integral_v<T>);
            return T(impl);
        }
        constexpr operator EnumType() const noexcept { return static_cast<EnumType>(impl); }

        constexpr bool operator<(const Species& other) const noexcept { return impl < other.impl; }
        constexpr bool operator<=(const Species& other) const noexcept
        {
            return impl <= other.impl;
        }

        constexpr bool operator>(const Species& other) const noexcept { return impl > other.impl; }
        constexpr bool operator>=(const Species& other) const noexcept
        {
            return impl >= other.impl;
        }

        constexpr bool operator==(const Species& other) const noexcept
        {
            return impl == other.impl;
        }
        constexpr bool operator!=(const Species& other) const noexcept
        {
            return impl != other.impl;
        }

        constexpr bool operator<(const internal::Species_impl& other) const noexcept
        {
            return impl < other;
        }
        constexpr bool operator<=(const internal::Species_impl& other) const noexcept
        {
            return impl <= other;
        }

        constexpr bool operator>(const internal::Species_impl& other) const noexcept
        {
            return impl > other;
        }
        constexpr bool operator>=(const internal::Species_impl& other) const noexcept
        {
            return impl >= other;
        }

        constexpr bool operator==(const internal::Species_impl& other) const noexcept
        {
            return impl == other;
        }
        constexpr bool operator!=(const internal::Species_impl& other) const noexcept
        {
            return impl != other;
        }

        const std::string& localize(Language lang) const { return impl.localize(lang); }

        static constexpr internal::Species_impl None{EnumType::None};
        static constexpr internal::Species_impl Bulbasaur{EnumType::Bulbasaur};
        static constexpr internal::Species_impl Ivysaur{EnumType::Ivysaur};
        static constexpr internal::Species_impl Venusaur{EnumType::Venusaur};
        static constexpr internal::Species_impl Charmander{EnumType::Charmander};
        static constexpr internal::Species_impl Charmeleon{EnumType::Charmeleon};
        static constexpr internal::Species_impl Charizard{EnumType::Charizard};
        static constexpr internal::Species_impl Squirtle{EnumType::Squirtle};
        static constexpr internal::Species_impl Wartortle{EnumType::Wartortle};
        static constexpr internal::Species_impl Blastoise{EnumType::Blastoise};
        static constexpr internal::Species_impl Caterpie{EnumType::Caterpie};
        static constexpr internal::Species_impl Metapod{EnumType::Metapod};
        static constexpr internal::Species_impl Butterfree{EnumType::Butterfree};
        static constexpr internal::Species_impl Weedle{EnumType::Weedle};
        static constexpr internal::Species_impl Kakuna{EnumType::Kakuna};
        static constexpr internal::Species_impl Beedrill{EnumType::Beedrill};
        static constexpr internal::Species_impl Pidgey{EnumType::Pidgey};
        static constexpr internal::Species_impl Pidgeotto{EnumType::Pidgeotto};
        static constexpr internal::Species_impl Pidgeot{EnumType::Pidgeot};
        static constexpr internal::Species_impl Rattata{EnumType::Rattata};
        static constexpr internal::Species_impl Raticate{EnumType::Raticate};
        static constexpr internal::Species_impl Spearow{EnumType::Spearow};
        static constexpr internal::Species_impl Fearow{EnumType::Fearow};
        static constexpr internal::Species_impl Ekans{EnumType::Ekans};
        static constexpr internal::Species_impl Arbok{EnumType::Arbok};
        static constexpr internal::Species_impl Pikachu{EnumType::Pikachu};
        static constexpr internal::Species_impl Raichu{EnumType::Raichu};
        static constexpr internal::Species_impl Sandshrew{EnumType::Sandshrew};
        static constexpr internal::Species_impl Sandslash{EnumType::Sandslash};
        static constexpr internal::Species_impl NidoranF{EnumType::NidoranF};
        static constexpr internal::Species_impl Nidorina{EnumType::Nidorina};
        static constexpr internal::Species_impl Nidoqueen{EnumType::Nidoqueen};
        static constexpr internal::Species_impl NidoranM{EnumType::NidoranM};
        static constexpr internal::Species_impl Nidorino{EnumType::Nidorino};
        static constexpr internal::Species_impl Nidoking{EnumType::Nidoking};
        static constexpr internal::Species_impl Clefairy{EnumType::Clefairy};
        static constexpr internal::Species_impl Clefable{EnumType::Clefable};
        static constexpr internal::Species_impl Vulpix{EnumType::Vulpix};
        static constexpr internal::Species_impl Ninetales{EnumType::Ninetales};
        static constexpr internal::Species_impl Jigglypuff{EnumType::Jigglypuff};
        static constexpr internal::Species_impl Wigglytuff{EnumType::Wigglytuff};
        static constexpr internal::Species_impl Zubat{EnumType::Zubat};
        static constexpr internal::Species_impl Golbat{EnumType::Golbat};
        static constexpr internal::Species_impl Oddish{EnumType::Oddish};
        static constexpr internal::Species_impl Gloom{EnumType::Gloom};
        static constexpr internal::Species_impl Vileplume{EnumType::Vileplume};
        static constexpr internal::Species_impl Paras{EnumType::Paras};
        static constexpr internal::Species_impl Parasect{EnumType::Parasect};
        static constexpr internal::Species_impl Venonat{EnumType::Venonat};
        static constexpr internal::Species_impl Venomoth{EnumType::Venomoth};
        static constexpr internal::Species_impl Diglett{EnumType::Diglett};
        static constexpr internal::Species_impl Dugtrio{EnumType::Dugtrio};
        static constexpr internal::Species_impl Meowth{EnumType::Meowth};
        static constexpr internal::Species_impl Persian{EnumType::Persian};
        static constexpr internal::Species_impl Psyduck{EnumType::Psyduck};
        static constexpr internal::Species_impl Golduck{EnumType::Golduck};
        static constexpr internal::Species_impl Mankey{EnumType::Mankey};
        static constexpr internal::Species_impl Primeape{EnumType::Primeape};
        static constexpr internal::Species_impl Growlithe{EnumType::Growlithe};
        static constexpr internal::Species_impl Arcanine{EnumType::Arcanine};
        static constexpr internal::Species_impl Poliwag{EnumType::Poliwag};
        static constexpr internal::Species_impl Poliwhirl{EnumType::Poliwhirl};
        static constexpr internal::Species_impl Poliwrath{EnumType::Poliwrath};
        static constexpr internal::Species_impl Abra{EnumType::Abra};
        static constexpr internal::Species_impl Kadabra{EnumType::Kadabra};
        static constexpr internal::Species_impl Alakazam{EnumType::Alakazam};
        static constexpr internal::Species_impl Machop{EnumType::Machop};
        static constexpr internal::Species_impl Machoke{EnumType::Machoke};
        static constexpr internal::Species_impl Machamp{EnumType::Machamp};
        static constexpr internal::Species_impl Bellsprout{EnumType::Bellsprout};
        static constexpr internal::Species_impl Weepinbell{EnumType::Weepinbell};
        static constexpr internal::Species_impl Victreebel{EnumType::Victreebel};
        static constexpr internal::Species_impl Tentacool{EnumType::Tentacool};
        static constexpr internal::Species_impl Tentacruel{EnumType::Tentacruel};
        static constexpr internal::Species_impl Geodude{EnumType::Geodude};
        static constexpr internal::Species_impl Graveler{EnumType::Graveler};
        static constexpr internal::Species_impl Golem{EnumType::Golem};
        static constexpr internal::Species_impl Ponyta{EnumType::Ponyta};
        static constexpr internal::Species_impl Rapidash{EnumType::Rapidash};
        static constexpr internal::Species_impl Slowpoke{EnumType::Slowpoke};
        static constexpr internal::Species_impl Slowbro{EnumType::Slowbro};
        static constexpr internal::Species_impl Magnemite{EnumType::Magnemite};
        static constexpr internal::Species_impl Magneton{EnumType::Magneton};
        static constexpr internal::Species_impl Farfetchd{EnumType::Farfetchd};
        static constexpr internal::Species_impl Doduo{EnumType::Doduo};
        static constexpr internal::Species_impl Dodrio{EnumType::Dodrio};
        static constexpr internal::Species_impl Seel{EnumType::Seel};
        static constexpr internal::Species_impl Dewgong{EnumType::Dewgong};
        static constexpr internal::Species_impl Grimer{EnumType::Grimer};
        static constexpr internal::Species_impl Muk{EnumType::Muk};
        static constexpr internal::Species_impl Shellder{EnumType::Shellder};
        static constexpr internal::Species_impl Cloyster{EnumType::Cloyster};
        static constexpr internal::Species_impl Gastly{EnumType::Gastly};
        static constexpr internal::Species_impl Haunter{EnumType::Haunter};
        static constexpr internal::Species_impl Gengar{EnumType::Gengar};
        static constexpr internal::Species_impl Onix{EnumType::Onix};
        static constexpr internal::Species_impl Drowzee{EnumType::Drowzee};
        static constexpr internal::Species_impl Hypno{EnumType::Hypno};
        static constexpr internal::Species_impl Krabby{EnumType::Krabby};
        static constexpr internal::Species_impl Kingler{EnumType::Kingler};
        static constexpr internal::Species_impl Voltorb{EnumType::Voltorb};
        static constexpr internal::Species_impl Electrode{EnumType::Electrode};
        static constexpr internal::Species_impl Exeggcute{EnumType::Exeggcute};
        static constexpr internal::Species_impl Exeggutor{EnumType::Exeggutor};
        static constexpr internal::Species_impl Cubone{EnumType::Cubone};
        static constexpr internal::Species_impl Marowak{EnumType::Marowak};
        static constexpr internal::Species_impl Hitmonlee{EnumType::Hitmonlee};
        static constexpr internal::Species_impl Hitmonchan{EnumType::Hitmonchan};
        static constexpr internal::Species_impl Lickitung{EnumType::Lickitung};
        static constexpr internal::Species_impl Koffing{EnumType::Koffing};
        static constexpr internal::Species_impl Weezing{EnumType::Weezing};
        static constexpr internal::Species_impl Rhyhorn{EnumType::Rhyhorn};
        static constexpr internal::Species_impl Rhydon{EnumType::Rhydon};
        static constexpr internal::Species_impl Chansey{EnumType::Chansey};
        static constexpr internal::Species_impl Tangela{EnumType::Tangela};
        static constexpr internal::Species_impl Kangaskhan{EnumType::Kangaskhan};
        static constexpr internal::Species_impl Horsea{EnumType::Horsea};
        static constexpr internal::Species_impl Seadra{EnumType::Seadra};
        static constexpr internal::Species_impl Goldeen{EnumType::Goldeen};
        static constexpr internal::Species_impl Seaking{EnumType::Seaking};
        static constexpr internal::Species_impl Staryu{EnumType::Staryu};
        static constexpr internal::Species_impl Starmie{EnumType::Starmie};
        static constexpr internal::Species_impl MrMime{EnumType::MrMime};
        static constexpr internal::Species_impl Scyther{EnumType::Scyther};
        static constexpr internal::Species_impl Jynx{EnumType::Jynx};
        static constexpr internal::Species_impl Electabuzz{EnumType::Electabuzz};
        static constexpr internal::Species_impl Magmar{EnumType::Magmar};
        static constexpr internal::Species_impl Pinsir{EnumType::Pinsir};
        static constexpr internal::Species_impl Tauros{EnumType::Tauros};
        static constexpr internal::Species_impl Magikarp{EnumType::Magikarp};
        static constexpr internal::Species_impl Gyarados{EnumType::Gyarados};
        static constexpr internal::Species_impl Lapras{EnumType::Lapras};
        static constexpr internal::Species_impl Ditto{EnumType::Ditto};
        static constexpr internal::Species_impl Eevee{EnumType::Eevee};
        static constexpr internal::Species_impl Vaporeon{EnumType::Vaporeon};
        static constexpr internal::Species_impl Jolteon{EnumType::Jolteon};
        static constexpr internal::Species_impl Flareon{EnumType::Flareon};
        static constexpr internal::Species_impl Porygon{EnumType::Porygon};
        static constexpr internal::Species_impl Omanyte{EnumType::Omanyte};
        static constexpr internal::Species_impl Omastar{EnumType::Omastar};
        static constexpr internal::Species_impl Kabuto{EnumType::Kabuto};
        static constexpr internal::Species_impl Kabutops{EnumType::Kabutops};
        static constexpr internal::Species_impl Aerodactyl{EnumType::Aerodactyl};
        static constexpr internal::Species_impl Snorlax{EnumType::Snorlax};
        static constexpr internal::Species_impl Articuno{EnumType::Articuno};
        static constexpr internal::Species_impl Zapdos{EnumType::Zapdos};
        static constexpr internal::Species_impl Moltres{EnumType::Moltres};
        static constexpr internal::Species_impl Dratini{EnumType::Dratini};
        static constexpr internal::Species_impl Dragonair{EnumType::Dragonair};
        static constexpr internal::Species_impl Dragonite{EnumType::Dragonite};
        static constexpr internal::Species_impl Mewtwo{EnumType::Mewtwo};
        static constexpr internal::Species_impl Mew{EnumType::Mew};
        static constexpr internal::Species_impl Chikorita{EnumType::Chikorita};
        static constexpr internal::Species_impl Bayleef{EnumType::Bayleef};
        static constexpr internal::Species_impl Meganium{EnumType::Meganium};
        static constexpr internal::Species_impl Cyndaquil{EnumType::Cyndaquil};
        static constexpr internal::Species_impl Quilava{EnumType::Quilava};
        static constexpr internal::Species_impl Typhlosion{EnumType::Typhlosion};
        static constexpr internal::Species_impl Totodile{EnumType::Totodile};
        static constexpr internal::Species_impl Croconaw{EnumType::Croconaw};
        static constexpr internal::Species_impl Feraligatr{EnumType::Feraligatr};
        static constexpr internal::Species_impl Sentret{EnumType::Sentret};
        static constexpr internal::Species_impl Furret{EnumType::Furret};
        static constexpr internal::Species_impl Hoothoot{EnumType::Hoothoot};
        static constexpr internal::Species_impl Noctowl{EnumType::Noctowl};
        static constexpr internal::Species_impl Ledyba{EnumType::Ledyba};
        static constexpr internal::Species_impl Ledian{EnumType::Ledian};
        static constexpr internal::Species_impl Spinarak{EnumType::Spinarak};
        static constexpr internal::Species_impl Ariados{EnumType::Ariados};
        static constexpr internal::Species_impl Crobat{EnumType::Crobat};
        static constexpr internal::Species_impl Chinchou{EnumType::Chinchou};
        static constexpr internal::Species_impl Lanturn{EnumType::Lanturn};
        static constexpr internal::Species_impl Pichu{EnumType::Pichu};
        static constexpr internal::Species_impl Cleffa{EnumType::Cleffa};
        static constexpr internal::Species_impl Igglybuff{EnumType::Igglybuff};
        static constexpr internal::Species_impl Togepi{EnumType::Togepi};
        static constexpr internal::Species_impl Togetic{EnumType::Togetic};
        static constexpr internal::Species_impl Natu{EnumType::Natu};
        static constexpr internal::Species_impl Xatu{EnumType::Xatu};
        static constexpr internal::Species_impl Mareep{EnumType::Mareep};
        static constexpr internal::Species_impl Flaaffy{EnumType::Flaaffy};
        static constexpr internal::Species_impl Ampharos{EnumType::Ampharos};
        static constexpr internal::Species_impl Bellossom{EnumType::Bellossom};
        static constexpr internal::Species_impl Marill{EnumType::Marill};
        static constexpr internal::Species_impl Azumarill{EnumType::Azumarill};
        static constexpr internal::Species_impl Sudowoodo{EnumType::Sudowoodo};
        static constexpr internal::Species_impl Politoed{EnumType::Politoed};
        static constexpr internal::Species_impl Hoppip{EnumType::Hoppip};
        static constexpr internal::Species_impl Skiploom{EnumType::Skiploom};
        static constexpr internal::Species_impl Jumpluff{EnumType::Jumpluff};
        static constexpr internal::Species_impl Aipom{EnumType::Aipom};
        static constexpr internal::Species_impl Sunkern{EnumType::Sunkern};
        static constexpr internal::Species_impl Sunflora{EnumType::Sunflora};
        static constexpr internal::Species_impl Yanma{EnumType::Yanma};
        static constexpr internal::Species_impl Wooper{EnumType::Wooper};
        static constexpr internal::Species_impl Quagsire{EnumType::Quagsire};
        static constexpr internal::Species_impl Espeon{EnumType::Espeon};
        static constexpr internal::Species_impl Umbreon{EnumType::Umbreon};
        static constexpr internal::Species_impl Murkrow{EnumType::Murkrow};
        static constexpr internal::Species_impl Slowking{EnumType::Slowking};
        static constexpr internal::Species_impl Misdreavus{EnumType::Misdreavus};
        static constexpr internal::Species_impl Unown{EnumType::Unown};
        static constexpr internal::Species_impl Wobbuffet{EnumType::Wobbuffet};
        static constexpr internal::Species_impl Girafarig{EnumType::Girafarig};
        static constexpr internal::Species_impl Pineco{EnumType::Pineco};
        static constexpr internal::Species_impl Forretress{EnumType::Forretress};
        static constexpr internal::Species_impl Dunsparce{EnumType::Dunsparce};
        static constexpr internal::Species_impl Gligar{EnumType::Gligar};
        static constexpr internal::Species_impl Steelix{EnumType::Steelix};
        static constexpr internal::Species_impl Snubbull{EnumType::Snubbull};
        static constexpr internal::Species_impl Granbull{EnumType::Granbull};
        static constexpr internal::Species_impl Qwilfish{EnumType::Qwilfish};
        static constexpr internal::Species_impl Scizor{EnumType::Scizor};
        static constexpr internal::Species_impl Shuckle{EnumType::Shuckle};
        static constexpr internal::Species_impl Heracross{EnumType::Heracross};
        static constexpr internal::Species_impl Sneasel{EnumType::Sneasel};
        static constexpr internal::Species_impl Teddiursa{EnumType::Teddiursa};
        static constexpr internal::Species_impl Ursaring{EnumType::Ursaring};
        static constexpr internal::Species_impl Slugma{EnumType::Slugma};
        static constexpr internal::Species_impl Magcargo{EnumType::Magcargo};
        static constexpr internal::Species_impl Swinub{EnumType::Swinub};
        static constexpr internal::Species_impl Piloswine{EnumType::Piloswine};
        static constexpr internal::Species_impl Corsola{EnumType::Corsola};
        static constexpr internal::Species_impl Remoraid{EnumType::Remoraid};
        static constexpr internal::Species_impl Octillery{EnumType::Octillery};
        static constexpr internal::Species_impl Delibird{EnumType::Delibird};
        static constexpr internal::Species_impl Mantine{EnumType::Mantine};
        static constexpr internal::Species_impl Skarmory{EnumType::Skarmory};
        static constexpr internal::Species_impl Houndour{EnumType::Houndour};
        static constexpr internal::Species_impl Houndoom{EnumType::Houndoom};
        static constexpr internal::Species_impl Kingdra{EnumType::Kingdra};
        static constexpr internal::Species_impl Phanpy{EnumType::Phanpy};
        static constexpr internal::Species_impl Donphan{EnumType::Donphan};
        static constexpr internal::Species_impl Porygon2{EnumType::Porygon2};
        static constexpr internal::Species_impl Stantler{EnumType::Stantler};
        static constexpr internal::Species_impl Smeargle{EnumType::Smeargle};
        static constexpr internal::Species_impl Tyrogue{EnumType::Tyrogue};
        static constexpr internal::Species_impl Hitmontop{EnumType::Hitmontop};
        static constexpr internal::Species_impl Smoochum{EnumType::Smoochum};
        static constexpr internal::Species_impl Elekid{EnumType::Elekid};
        static constexpr internal::Species_impl Magby{EnumType::Magby};
        static constexpr internal::Species_impl Miltank{EnumType::Miltank};
        static constexpr internal::Species_impl Blissey{EnumType::Blissey};
        static constexpr internal::Species_impl Raikou{EnumType::Raikou};
        static constexpr internal::Species_impl Entei{EnumType::Entei};
        static constexpr internal::Species_impl Suicune{EnumType::Suicune};
        static constexpr internal::Species_impl Larvitar{EnumType::Larvitar};
        static constexpr internal::Species_impl Pupitar{EnumType::Pupitar};
        static constexpr internal::Species_impl Tyranitar{EnumType::Tyranitar};
        static constexpr internal::Species_impl Lugia{EnumType::Lugia};
        static constexpr internal::Species_impl HoOh{EnumType::HoOh};
        static constexpr internal::Species_impl Celebi{EnumType::Celebi};
        static constexpr internal::Species_impl Treecko{EnumType::Treecko};
        static constexpr internal::Species_impl Grovyle{EnumType::Grovyle};
        static constexpr internal::Species_impl Sceptile{EnumType::Sceptile};
        static constexpr internal::Species_impl Torchic{EnumType::Torchic};
        static constexpr internal::Species_impl Combusken{EnumType::Combusken};
        static constexpr internal::Species_impl Blaziken{EnumType::Blaziken};
        static constexpr internal::Species_impl Mudkip{EnumType::Mudkip};
        static constexpr internal::Species_impl Marshtomp{EnumType::Marshtomp};
        static constexpr internal::Species_impl Swampert{EnumType::Swampert};
        static constexpr internal::Species_impl Poochyena{EnumType::Poochyena};
        static constexpr internal::Species_impl Mightyena{EnumType::Mightyena};
        static constexpr internal::Species_impl Zigzagoon{EnumType::Zigzagoon};
        static constexpr internal::Species_impl Linoone{EnumType::Linoone};
        static constexpr internal::Species_impl Wurmple{EnumType::Wurmple};
        static constexpr internal::Species_impl Silcoon{EnumType::Silcoon};
        static constexpr internal::Species_impl Beautifly{EnumType::Beautifly};
        static constexpr internal::Species_impl Cascoon{EnumType::Cascoon};
        static constexpr internal::Species_impl Dustox{EnumType::Dustox};
        static constexpr internal::Species_impl Lotad{EnumType::Lotad};
        static constexpr internal::Species_impl Lombre{EnumType::Lombre};
        static constexpr internal::Species_impl Ludicolo{EnumType::Ludicolo};
        static constexpr internal::Species_impl Seedot{EnumType::Seedot};
        static constexpr internal::Species_impl Nuzleaf{EnumType::Nuzleaf};
        static constexpr internal::Species_impl Shiftry{EnumType::Shiftry};
        static constexpr internal::Species_impl Taillow{EnumType::Taillow};
        static constexpr internal::Species_impl Swellow{EnumType::Swellow};
        static constexpr internal::Species_impl Wingull{EnumType::Wingull};
        static constexpr internal::Species_impl Pelipper{EnumType::Pelipper};
        static constexpr internal::Species_impl Ralts{EnumType::Ralts};
        static constexpr internal::Species_impl Kirlia{EnumType::Kirlia};
        static constexpr internal::Species_impl Gardevoir{EnumType::Gardevoir};
        static constexpr internal::Species_impl Surskit{EnumType::Surskit};
        static constexpr internal::Species_impl Masquerain{EnumType::Masquerain};
        static constexpr internal::Species_impl Shroomish{EnumType::Shroomish};
        static constexpr internal::Species_impl Breloom{EnumType::Breloom};
        static constexpr internal::Species_impl Slakoth{EnumType::Slakoth};
        static constexpr internal::Species_impl Vigoroth{EnumType::Vigoroth};
        static constexpr internal::Species_impl Slaking{EnumType::Slaking};
        static constexpr internal::Species_impl Nincada{EnumType::Nincada};
        static constexpr internal::Species_impl Ninjask{EnumType::Ninjask};
        static constexpr internal::Species_impl Shedinja{EnumType::Shedinja};
        static constexpr internal::Species_impl Whismur{EnumType::Whismur};
        static constexpr internal::Species_impl Loudred{EnumType::Loudred};
        static constexpr internal::Species_impl Exploud{EnumType::Exploud};
        static constexpr internal::Species_impl Makuhita{EnumType::Makuhita};
        static constexpr internal::Species_impl Hariyama{EnumType::Hariyama};
        static constexpr internal::Species_impl Azurill{EnumType::Azurill};
        static constexpr internal::Species_impl Nosepass{EnumType::Nosepass};
        static constexpr internal::Species_impl Skitty{EnumType::Skitty};
        static constexpr internal::Species_impl Delcatty{EnumType::Delcatty};
        static constexpr internal::Species_impl Sableye{EnumType::Sableye};
        static constexpr internal::Species_impl Mawile{EnumType::Mawile};
        static constexpr internal::Species_impl Aron{EnumType::Aron};
        static constexpr internal::Species_impl Lairon{EnumType::Lairon};
        static constexpr internal::Species_impl Aggron{EnumType::Aggron};
        static constexpr internal::Species_impl Meditite{EnumType::Meditite};
        static constexpr internal::Species_impl Medicham{EnumType::Medicham};
        static constexpr internal::Species_impl Electrike{EnumType::Electrike};
        static constexpr internal::Species_impl Manectric{EnumType::Manectric};
        static constexpr internal::Species_impl Plusle{EnumType::Plusle};
        static constexpr internal::Species_impl Minun{EnumType::Minun};
        static constexpr internal::Species_impl Volbeat{EnumType::Volbeat};
        static constexpr internal::Species_impl Illumise{EnumType::Illumise};
        static constexpr internal::Species_impl Roselia{EnumType::Roselia};
        static constexpr internal::Species_impl Gulpin{EnumType::Gulpin};
        static constexpr internal::Species_impl Swalot{EnumType::Swalot};
        static constexpr internal::Species_impl Carvanha{EnumType::Carvanha};
        static constexpr internal::Species_impl Sharpedo{EnumType::Sharpedo};
        static constexpr internal::Species_impl Wailmer{EnumType::Wailmer};
        static constexpr internal::Species_impl Wailord{EnumType::Wailord};
        static constexpr internal::Species_impl Numel{EnumType::Numel};
        static constexpr internal::Species_impl Camerupt{EnumType::Camerupt};
        static constexpr internal::Species_impl Torkoal{EnumType::Torkoal};
        static constexpr internal::Species_impl Spoink{EnumType::Spoink};
        static constexpr internal::Species_impl Grumpig{EnumType::Grumpig};
        static constexpr internal::Species_impl Spinda{EnumType::Spinda};
        static constexpr internal::Species_impl Trapinch{EnumType::Trapinch};
        static constexpr internal::Species_impl Vibrava{EnumType::Vibrava};
        static constexpr internal::Species_impl Flygon{EnumType::Flygon};
        static constexpr internal::Species_impl Cacnea{EnumType::Cacnea};
        static constexpr internal::Species_impl Cacturne{EnumType::Cacturne};
        static constexpr internal::Species_impl Swablu{EnumType::Swablu};
        static constexpr internal::Species_impl Altaria{EnumType::Altaria};
        static constexpr internal::Species_impl Zangoose{EnumType::Zangoose};
        static constexpr internal::Species_impl Seviper{EnumType::Seviper};
        static constexpr internal::Species_impl Lunatone{EnumType::Lunatone};
        static constexpr internal::Species_impl Solrock{EnumType::Solrock};
        static constexpr internal::Species_impl Barboach{EnumType::Barboach};
        static constexpr internal::Species_impl Whiscash{EnumType::Whiscash};
        static constexpr internal::Species_impl Corphish{EnumType::Corphish};
        static constexpr internal::Species_impl Crawdaunt{EnumType::Crawdaunt};
        static constexpr internal::Species_impl Baltoy{EnumType::Baltoy};
        static constexpr internal::Species_impl Claydol{EnumType::Claydol};
        static constexpr internal::Species_impl Lileep{EnumType::Lileep};
        static constexpr internal::Species_impl Cradily{EnumType::Cradily};
        static constexpr internal::Species_impl Anorith{EnumType::Anorith};
        static constexpr internal::Species_impl Armaldo{EnumType::Armaldo};
        static constexpr internal::Species_impl Feebas{EnumType::Feebas};
        static constexpr internal::Species_impl Milotic{EnumType::Milotic};
        static constexpr internal::Species_impl Castform{EnumType::Castform};
        static constexpr internal::Species_impl Kecleon{EnumType::Kecleon};
        static constexpr internal::Species_impl Shuppet{EnumType::Shuppet};
        static constexpr internal::Species_impl Banette{EnumType::Banette};
        static constexpr internal::Species_impl Duskull{EnumType::Duskull};
        static constexpr internal::Species_impl Dusclops{EnumType::Dusclops};
        static constexpr internal::Species_impl Tropius{EnumType::Tropius};
        static constexpr internal::Species_impl Chimecho{EnumType::Chimecho};
        static constexpr internal::Species_impl Absol{EnumType::Absol};
        static constexpr internal::Species_impl Wynaut{EnumType::Wynaut};
        static constexpr internal::Species_impl Snorunt{EnumType::Snorunt};
        static constexpr internal::Species_impl Glalie{EnumType::Glalie};
        static constexpr internal::Species_impl Spheal{EnumType::Spheal};
        static constexpr internal::Species_impl Sealeo{EnumType::Sealeo};
        static constexpr internal::Species_impl Walrein{EnumType::Walrein};
        static constexpr internal::Species_impl Clamperl{EnumType::Clamperl};
        static constexpr internal::Species_impl Huntail{EnumType::Huntail};
        static constexpr internal::Species_impl Gorebyss{EnumType::Gorebyss};
        static constexpr internal::Species_impl Relicanth{EnumType::Relicanth};
        static constexpr internal::Species_impl Luvdisc{EnumType::Luvdisc};
        static constexpr internal::Species_impl Bagon{EnumType::Bagon};
        static constexpr internal::Species_impl Shelgon{EnumType::Shelgon};
        static constexpr internal::Species_impl Salamence{EnumType::Salamence};
        static constexpr internal::Species_impl Beldum{EnumType::Beldum};
        static constexpr internal::Species_impl Metang{EnumType::Metang};
        static constexpr internal::Species_impl Metagross{EnumType::Metagross};
        static constexpr internal::Species_impl Regirock{EnumType::Regirock};
        static constexpr internal::Species_impl Regice{EnumType::Regice};
        static constexpr internal::Species_impl Registeel{EnumType::Registeel};
        static constexpr internal::Species_impl Latias{EnumType::Latias};
        static constexpr internal::Species_impl Latios{EnumType::Latios};
        static constexpr internal::Species_impl Kyogre{EnumType::Kyogre};
        static constexpr internal::Species_impl Groudon{EnumType::Groudon};
        static constexpr internal::Species_impl Rayquaza{EnumType::Rayquaza};
        static constexpr internal::Species_impl Jirachi{EnumType::Jirachi};
        static constexpr internal::Species_impl Deoxys{EnumType::Deoxys};
        static constexpr internal::Species_impl Turtwig{EnumType::Turtwig};
        static constexpr internal::Species_impl Grotle{EnumType::Grotle};
        static constexpr internal::Species_impl Torterra{EnumType::Torterra};
        static constexpr internal::Species_impl Chimchar{EnumType::Chimchar};
        static constexpr internal::Species_impl Monferno{EnumType::Monferno};
        static constexpr internal::Species_impl Infernape{EnumType::Infernape};
        static constexpr internal::Species_impl Piplup{EnumType::Piplup};
        static constexpr internal::Species_impl Prinplup{EnumType::Prinplup};
        static constexpr internal::Species_impl Empoleon{EnumType::Empoleon};
        static constexpr internal::Species_impl Starly{EnumType::Starly};
        static constexpr internal::Species_impl Staravia{EnumType::Staravia};
        static constexpr internal::Species_impl Staraptor{EnumType::Staraptor};
        static constexpr internal::Species_impl Bidoof{EnumType::Bidoof};
        static constexpr internal::Species_impl Bibarel{EnumType::Bibarel};
        static constexpr internal::Species_impl Kricketot{EnumType::Kricketot};
        static constexpr internal::Species_impl Kricketune{EnumType::Kricketune};
        static constexpr internal::Species_impl Shinx{EnumType::Shinx};
        static constexpr internal::Species_impl Luxio{EnumType::Luxio};
        static constexpr internal::Species_impl Luxray{EnumType::Luxray};
        static constexpr internal::Species_impl Budew{EnumType::Budew};
        static constexpr internal::Species_impl Roserade{EnumType::Roserade};
        static constexpr internal::Species_impl Cranidos{EnumType::Cranidos};
        static constexpr internal::Species_impl Rampardos{EnumType::Rampardos};
        static constexpr internal::Species_impl Shieldon{EnumType::Shieldon};
        static constexpr internal::Species_impl Bastiodon{EnumType::Bastiodon};
        static constexpr internal::Species_impl Burmy{EnumType::Burmy};
        static constexpr internal::Species_impl Wormadam{EnumType::Wormadam};
        static constexpr internal::Species_impl Mothim{EnumType::Mothim};
        static constexpr internal::Species_impl Combee{EnumType::Combee};
        static constexpr internal::Species_impl Vespiquen{EnumType::Vespiquen};
        static constexpr internal::Species_impl Pachirisu{EnumType::Pachirisu};
        static constexpr internal::Species_impl Buizel{EnumType::Buizel};
        static constexpr internal::Species_impl Floatzel{EnumType::Floatzel};
        static constexpr internal::Species_impl Cherubi{EnumType::Cherubi};
        static constexpr internal::Species_impl Cherrim{EnumType::Cherrim};
        static constexpr internal::Species_impl Shellos{EnumType::Shellos};
        static constexpr internal::Species_impl Gastrodon{EnumType::Gastrodon};
        static constexpr internal::Species_impl Ambipom{EnumType::Ambipom};
        static constexpr internal::Species_impl Drifloon{EnumType::Drifloon};
        static constexpr internal::Species_impl Drifblim{EnumType::Drifblim};
        static constexpr internal::Species_impl Buneary{EnumType::Buneary};
        static constexpr internal::Species_impl Lopunny{EnumType::Lopunny};
        static constexpr internal::Species_impl Mismagius{EnumType::Mismagius};
        static constexpr internal::Species_impl Honchkrow{EnumType::Honchkrow};
        static constexpr internal::Species_impl Glameow{EnumType::Glameow};
        static constexpr internal::Species_impl Purugly{EnumType::Purugly};
        static constexpr internal::Species_impl Chingling{EnumType::Chingling};
        static constexpr internal::Species_impl Stunky{EnumType::Stunky};
        static constexpr internal::Species_impl Skuntank{EnumType::Skuntank};
        static constexpr internal::Species_impl Bronzor{EnumType::Bronzor};
        static constexpr internal::Species_impl Bronzong{EnumType::Bronzong};
        static constexpr internal::Species_impl Bonsly{EnumType::Bonsly};
        static constexpr internal::Species_impl MimeJr{EnumType::MimeJr};
        static constexpr internal::Species_impl Happiny{EnumType::Happiny};
        static constexpr internal::Species_impl Chatot{EnumType::Chatot};
        static constexpr internal::Species_impl Spiritomb{EnumType::Spiritomb};
        static constexpr internal::Species_impl Gible{EnumType::Gible};
        static constexpr internal::Species_impl Gabite{EnumType::Gabite};
        static constexpr internal::Species_impl Garchomp{EnumType::Garchomp};
        static constexpr internal::Species_impl Munchlax{EnumType::Munchlax};
        static constexpr internal::Species_impl Riolu{EnumType::Riolu};
        static constexpr internal::Species_impl Lucario{EnumType::Lucario};
        static constexpr internal::Species_impl Hippopotas{EnumType::Hippopotas};
        static constexpr internal::Species_impl Hippowdon{EnumType::Hippowdon};
        static constexpr internal::Species_impl Skorupi{EnumType::Skorupi};
        static constexpr internal::Species_impl Drapion{EnumType::Drapion};
        static constexpr internal::Species_impl Croagunk{EnumType::Croagunk};
        static constexpr internal::Species_impl Toxicroak{EnumType::Toxicroak};
        static constexpr internal::Species_impl Carnivine{EnumType::Carnivine};
        static constexpr internal::Species_impl Finneon{EnumType::Finneon};
        static constexpr internal::Species_impl Lumineon{EnumType::Lumineon};
        static constexpr internal::Species_impl Mantyke{EnumType::Mantyke};
        static constexpr internal::Species_impl Snover{EnumType::Snover};
        static constexpr internal::Species_impl Abomasnow{EnumType::Abomasnow};
        static constexpr internal::Species_impl Weavile{EnumType::Weavile};
        static constexpr internal::Species_impl Magnezone{EnumType::Magnezone};
        static constexpr internal::Species_impl Lickilicky{EnumType::Lickilicky};
        static constexpr internal::Species_impl Rhyperior{EnumType::Rhyperior};
        static constexpr internal::Species_impl Tangrowth{EnumType::Tangrowth};
        static constexpr internal::Species_impl Electivire{EnumType::Electivire};
        static constexpr internal::Species_impl Magmortar{EnumType::Magmortar};
        static constexpr internal::Species_impl Togekiss{EnumType::Togekiss};
        static constexpr internal::Species_impl Yanmega{EnumType::Yanmega};
        static constexpr internal::Species_impl Leafeon{EnumType::Leafeon};
        static constexpr internal::Species_impl Glaceon{EnumType::Glaceon};
        static constexpr internal::Species_impl Gliscor{EnumType::Gliscor};
        static constexpr internal::Species_impl Mamoswine{EnumType::Mamoswine};
        static constexpr internal::Species_impl PorygonZ{EnumType::PorygonZ};
        static constexpr internal::Species_impl Gallade{EnumType::Gallade};
        static constexpr internal::Species_impl Probopass{EnumType::Probopass};
        static constexpr internal::Species_impl Dusknoir{EnumType::Dusknoir};
        static constexpr internal::Species_impl Froslass{EnumType::Froslass};
        static constexpr internal::Species_impl Rotom{EnumType::Rotom};
        static constexpr internal::Species_impl Uxie{EnumType::Uxie};
        static constexpr internal::Species_impl Mesprit{EnumType::Mesprit};
        static constexpr internal::Species_impl Azelf{EnumType::Azelf};
        static constexpr internal::Species_impl Dialga{EnumType::Dialga};
        static constexpr internal::Species_impl Palkia{EnumType::Palkia};
        static constexpr internal::Species_impl Heatran{EnumType::Heatran};
        static constexpr internal::Species_impl Regigigas{EnumType::Regigigas};
        static constexpr internal::Species_impl Giratina{EnumType::Giratina};
        static constexpr internal::Species_impl Cresselia{EnumType::Cresselia};
        static constexpr internal::Species_impl Phione{EnumType::Phione};
        static constexpr internal::Species_impl Manaphy{EnumType::Manaphy};
        static constexpr internal::Species_impl Darkrai{EnumType::Darkrai};
        static constexpr internal::Species_impl Shaymin{EnumType::Shaymin};
        static constexpr internal::Species_impl Arceus{EnumType::Arceus};
        static constexpr internal::Species_impl Victini{EnumType::Victini};
        static constexpr internal::Species_impl Snivy{EnumType::Snivy};
        static constexpr internal::Species_impl Servine{EnumType::Servine};
        static constexpr internal::Species_impl Serperior{EnumType::Serperior};
        static constexpr internal::Species_impl Tepig{EnumType::Tepig};
        static constexpr internal::Species_impl Pignite{EnumType::Pignite};
        static constexpr internal::Species_impl Emboar{EnumType::Emboar};
        static constexpr internal::Species_impl Oshawott{EnumType::Oshawott};
        static constexpr internal::Species_impl Dewott{EnumType::Dewott};
        static constexpr internal::Species_impl Samurott{EnumType::Samurott};
        static constexpr internal::Species_impl Patrat{EnumType::Patrat};
        static constexpr internal::Species_impl Watchog{EnumType::Watchog};
        static constexpr internal::Species_impl Lillipup{EnumType::Lillipup};
        static constexpr internal::Species_impl Herdier{EnumType::Herdier};
        static constexpr internal::Species_impl Stoutland{EnumType::Stoutland};
        static constexpr internal::Species_impl Purrloin{EnumType::Purrloin};
        static constexpr internal::Species_impl Liepard{EnumType::Liepard};
        static constexpr internal::Species_impl Pansage{EnumType::Pansage};
        static constexpr internal::Species_impl Simisage{EnumType::Simisage};
        static constexpr internal::Species_impl Pansear{EnumType::Pansear};
        static constexpr internal::Species_impl Simisear{EnumType::Simisear};
        static constexpr internal::Species_impl Panpour{EnumType::Panpour};
        static constexpr internal::Species_impl Simipour{EnumType::Simipour};
        static constexpr internal::Species_impl Munna{EnumType::Munna};
        static constexpr internal::Species_impl Musharna{EnumType::Musharna};
        static constexpr internal::Species_impl Pidove{EnumType::Pidove};
        static constexpr internal::Species_impl Tranquill{EnumType::Tranquill};
        static constexpr internal::Species_impl Unfezant{EnumType::Unfezant};
        static constexpr internal::Species_impl Blitzle{EnumType::Blitzle};
        static constexpr internal::Species_impl Zebstrika{EnumType::Zebstrika};
        static constexpr internal::Species_impl Roggenrola{EnumType::Roggenrola};
        static constexpr internal::Species_impl Boldore{EnumType::Boldore};
        static constexpr internal::Species_impl Gigalith{EnumType::Gigalith};
        static constexpr internal::Species_impl Woobat{EnumType::Woobat};
        static constexpr internal::Species_impl Swoobat{EnumType::Swoobat};
        static constexpr internal::Species_impl Drilbur{EnumType::Drilbur};
        static constexpr internal::Species_impl Excadrill{EnumType::Excadrill};
        static constexpr internal::Species_impl Audino{EnumType::Audino};
        static constexpr internal::Species_impl Timburr{EnumType::Timburr};
        static constexpr internal::Species_impl Gurdurr{EnumType::Gurdurr};
        static constexpr internal::Species_impl Conkeldurr{EnumType::Conkeldurr};
        static constexpr internal::Species_impl Tympole{EnumType::Tympole};
        static constexpr internal::Species_impl Palpitoad{EnumType::Palpitoad};
        static constexpr internal::Species_impl Seismitoad{EnumType::Seismitoad};
        static constexpr internal::Species_impl Throh{EnumType::Throh};
        static constexpr internal::Species_impl Sawk{EnumType::Sawk};
        static constexpr internal::Species_impl Sewaddle{EnumType::Sewaddle};
        static constexpr internal::Species_impl Swadloon{EnumType::Swadloon};
        static constexpr internal::Species_impl Leavanny{EnumType::Leavanny};
        static constexpr internal::Species_impl Venipede{EnumType::Venipede};
        static constexpr internal::Species_impl Whirlipede{EnumType::Whirlipede};
        static constexpr internal::Species_impl Scolipede{EnumType::Scolipede};
        static constexpr internal::Species_impl Cottonee{EnumType::Cottonee};
        static constexpr internal::Species_impl Whimsicott{EnumType::Whimsicott};
        static constexpr internal::Species_impl Petilil{EnumType::Petilil};
        static constexpr internal::Species_impl Lilligant{EnumType::Lilligant};
        static constexpr internal::Species_impl Basculin{EnumType::Basculin};
        static constexpr internal::Species_impl Sandile{EnumType::Sandile};
        static constexpr internal::Species_impl Krokorok{EnumType::Krokorok};
        static constexpr internal::Species_impl Krookodile{EnumType::Krookodile};
        static constexpr internal::Species_impl Darumaka{EnumType::Darumaka};
        static constexpr internal::Species_impl Darmanitan{EnumType::Darmanitan};
        static constexpr internal::Species_impl Maractus{EnumType::Maractus};
        static constexpr internal::Species_impl Dwebble{EnumType::Dwebble};
        static constexpr internal::Species_impl Crustle{EnumType::Crustle};
        static constexpr internal::Species_impl Scraggy{EnumType::Scraggy};
        static constexpr internal::Species_impl Scrafty{EnumType::Scrafty};
        static constexpr internal::Species_impl Sigilyph{EnumType::Sigilyph};
        static constexpr internal::Species_impl Yamask{EnumType::Yamask};
        static constexpr internal::Species_impl Cofagrigus{EnumType::Cofagrigus};
        static constexpr internal::Species_impl Tirtouga{EnumType::Tirtouga};
        static constexpr internal::Species_impl Carracosta{EnumType::Carracosta};
        static constexpr internal::Species_impl Archen{EnumType::Archen};
        static constexpr internal::Species_impl Archeops{EnumType::Archeops};
        static constexpr internal::Species_impl Trubbish{EnumType::Trubbish};
        static constexpr internal::Species_impl Garbodor{EnumType::Garbodor};
        static constexpr internal::Species_impl Zorua{EnumType::Zorua};
        static constexpr internal::Species_impl Zoroark{EnumType::Zoroark};
        static constexpr internal::Species_impl Minccino{EnumType::Minccino};
        static constexpr internal::Species_impl Cinccino{EnumType::Cinccino};
        static constexpr internal::Species_impl Gothita{EnumType::Gothita};
        static constexpr internal::Species_impl Gothorita{EnumType::Gothorita};
        static constexpr internal::Species_impl Gothitelle{EnumType::Gothitelle};
        static constexpr internal::Species_impl Solosis{EnumType::Solosis};
        static constexpr internal::Species_impl Duosion{EnumType::Duosion};
        static constexpr internal::Species_impl Reuniclus{EnumType::Reuniclus};
        static constexpr internal::Species_impl Ducklett{EnumType::Ducklett};
        static constexpr internal::Species_impl Swanna{EnumType::Swanna};
        static constexpr internal::Species_impl Vanillite{EnumType::Vanillite};
        static constexpr internal::Species_impl Vanillish{EnumType::Vanillish};
        static constexpr internal::Species_impl Vanilluxe{EnumType::Vanilluxe};
        static constexpr internal::Species_impl Deerling{EnumType::Deerling};
        static constexpr internal::Species_impl Sawsbuck{EnumType::Sawsbuck};
        static constexpr internal::Species_impl Emolga{EnumType::Emolga};
        static constexpr internal::Species_impl Karrablast{EnumType::Karrablast};
        static constexpr internal::Species_impl Escavalier{EnumType::Escavalier};
        static constexpr internal::Species_impl Foongus{EnumType::Foongus};
        static constexpr internal::Species_impl Amoonguss{EnumType::Amoonguss};
        static constexpr internal::Species_impl Frillish{EnumType::Frillish};
        static constexpr internal::Species_impl Jellicent{EnumType::Jellicent};
        static constexpr internal::Species_impl Alomomola{EnumType::Alomomola};
        static constexpr internal::Species_impl Joltik{EnumType::Joltik};
        static constexpr internal::Species_impl Galvantula{EnumType::Galvantula};
        static constexpr internal::Species_impl Ferroseed{EnumType::Ferroseed};
        static constexpr internal::Species_impl Ferrothorn{EnumType::Ferrothorn};
        static constexpr internal::Species_impl Klink{EnumType::Klink};
        static constexpr internal::Species_impl Klang{EnumType::Klang};
        static constexpr internal::Species_impl Klinklang{EnumType::Klinklang};
        static constexpr internal::Species_impl Tynamo{EnumType::Tynamo};
        static constexpr internal::Species_impl Eelektrik{EnumType::Eelektrik};
        static constexpr internal::Species_impl Eelektross{EnumType::Eelektross};
        static constexpr internal::Species_impl Elgyem{EnumType::Elgyem};
        static constexpr internal::Species_impl Beheeyem{EnumType::Beheeyem};
        static constexpr internal::Species_impl Litwick{EnumType::Litwick};
        static constexpr internal::Species_impl Lampent{EnumType::Lampent};
        static constexpr internal::Species_impl Chandelure{EnumType::Chandelure};
        static constexpr internal::Species_impl Axew{EnumType::Axew};
        static constexpr internal::Species_impl Fraxure{EnumType::Fraxure};
        static constexpr internal::Species_impl Haxorus{EnumType::Haxorus};
        static constexpr internal::Species_impl Cubchoo{EnumType::Cubchoo};
        static constexpr internal::Species_impl Beartic{EnumType::Beartic};
        static constexpr internal::Species_impl Cryogonal{EnumType::Cryogonal};
        static constexpr internal::Species_impl Shelmet{EnumType::Shelmet};
        static constexpr internal::Species_impl Accelgor{EnumType::Accelgor};
        static constexpr internal::Species_impl Stunfisk{EnumType::Stunfisk};
        static constexpr internal::Species_impl Mienfoo{EnumType::Mienfoo};
        static constexpr internal::Species_impl Mienshao{EnumType::Mienshao};
        static constexpr internal::Species_impl Druddigon{EnumType::Druddigon};
        static constexpr internal::Species_impl Golett{EnumType::Golett};
        static constexpr internal::Species_impl Golurk{EnumType::Golurk};
        static constexpr internal::Species_impl Pawniard{EnumType::Pawniard};
        static constexpr internal::Species_impl Bisharp{EnumType::Bisharp};
        static constexpr internal::Species_impl Bouffalant{EnumType::Bouffalant};
        static constexpr internal::Species_impl Rufflet{EnumType::Rufflet};
        static constexpr internal::Species_impl Braviary{EnumType::Braviary};
        static constexpr internal::Species_impl Vullaby{EnumType::Vullaby};
        static constexpr internal::Species_impl Mandibuzz{EnumType::Mandibuzz};
        static constexpr internal::Species_impl Heatmor{EnumType::Heatmor};
        static constexpr internal::Species_impl Durant{EnumType::Durant};
        static constexpr internal::Species_impl Deino{EnumType::Deino};
        static constexpr internal::Species_impl Zweilous{EnumType::Zweilous};
        static constexpr internal::Species_impl Hydreigon{EnumType::Hydreigon};
        static constexpr internal::Species_impl Larvesta{EnumType::Larvesta};
        static constexpr internal::Species_impl Volcarona{EnumType::Volcarona};
        static constexpr internal::Species_impl Cobalion{EnumType::Cobalion};
        static constexpr internal::Species_impl Terrakion{EnumType::Terrakion};
        static constexpr internal::Species_impl Virizion{EnumType::Virizion};
        static constexpr internal::Species_impl Tornadus{EnumType::Tornadus};
        static constexpr internal::Species_impl Thundurus{EnumType::Thundurus};
        static constexpr internal::Species_impl Reshiram{EnumType::Reshiram};
        static constexpr internal::Species_impl Zekrom{EnumType::Zekrom};
        static constexpr internal::Species_impl Landorus{EnumType::Landorus};
        static constexpr internal::Species_impl Kyurem{EnumType::Kyurem};
        static constexpr internal::Species_impl Keldeo{EnumType::Keldeo};
        static constexpr internal::Species_impl Meloetta{EnumType::Meloetta};
        static constexpr internal::Species_impl Genesect{EnumType::Genesect};
        static constexpr internal::Species_impl Chespin{EnumType::Chespin};
        static constexpr internal::Species_impl Quilladin{EnumType::Quilladin};
        static constexpr internal::Species_impl Chesnaught{EnumType::Chesnaught};
        static constexpr internal::Species_impl Fennekin{EnumType::Fennekin};
        static constexpr internal::Species_impl Braixen{EnumType::Braixen};
        static constexpr internal::Species_impl Delphox{EnumType::Delphox};
        static constexpr internal::Species_impl Froakie{EnumType::Froakie};
        static constexpr internal::Species_impl Frogadier{EnumType::Frogadier};
        static constexpr internal::Species_impl Greninja{EnumType::Greninja};
        static constexpr internal::Species_impl Bunnelby{EnumType::Bunnelby};
        static constexpr internal::Species_impl Diggersby{EnumType::Diggersby};
        static constexpr internal::Species_impl Fletchling{EnumType::Fletchling};
        static constexpr internal::Species_impl Fletchinder{EnumType::Fletchinder};
        static constexpr internal::Species_impl Talonflame{EnumType::Talonflame};
        static constexpr internal::Species_impl Scatterbug{EnumType::Scatterbug};
        static constexpr internal::Species_impl Spewpa{EnumType::Spewpa};
        static constexpr internal::Species_impl Vivillon{EnumType::Vivillon};
        static constexpr internal::Species_impl Litleo{EnumType::Litleo};
        static constexpr internal::Species_impl Pyroar{EnumType::Pyroar};
        static constexpr internal::Species_impl Flabebe{EnumType::Flabebe};
        static constexpr internal::Species_impl Floette{EnumType::Floette};
        static constexpr internal::Species_impl Florges{EnumType::Florges};
        static constexpr internal::Species_impl Skiddo{EnumType::Skiddo};
        static constexpr internal::Species_impl Gogoat{EnumType::Gogoat};
        static constexpr internal::Species_impl Pancham{EnumType::Pancham};
        static constexpr internal::Species_impl Pangoro{EnumType::Pangoro};
        static constexpr internal::Species_impl Furfrou{EnumType::Furfrou};
        static constexpr internal::Species_impl Espurr{EnumType::Espurr};
        static constexpr internal::Species_impl Meowstic{EnumType::Meowstic};
        static constexpr internal::Species_impl Honedge{EnumType::Honedge};
        static constexpr internal::Species_impl Doublade{EnumType::Doublade};
        static constexpr internal::Species_impl Aegislash{EnumType::Aegislash};
        static constexpr internal::Species_impl Spritzee{EnumType::Spritzee};
        static constexpr internal::Species_impl Aromatisse{EnumType::Aromatisse};
        static constexpr internal::Species_impl Swirlix{EnumType::Swirlix};
        static constexpr internal::Species_impl Slurpuff{EnumType::Slurpuff};
        static constexpr internal::Species_impl Inkay{EnumType::Inkay};
        static constexpr internal::Species_impl Malamar{EnumType::Malamar};
        static constexpr internal::Species_impl Binacle{EnumType::Binacle};
        static constexpr internal::Species_impl Barbaracle{EnumType::Barbaracle};
        static constexpr internal::Species_impl Skrelp{EnumType::Skrelp};
        static constexpr internal::Species_impl Dragalge{EnumType::Dragalge};
        static constexpr internal::Species_impl Clauncher{EnumType::Clauncher};
        static constexpr internal::Species_impl Clawitzer{EnumType::Clawitzer};
        static constexpr internal::Species_impl Helioptile{EnumType::Helioptile};
        static constexpr internal::Species_impl Heliolisk{EnumType::Heliolisk};
        static constexpr internal::Species_impl Tyrunt{EnumType::Tyrunt};
        static constexpr internal::Species_impl Tyrantrum{EnumType::Tyrantrum};
        static constexpr internal::Species_impl Amaura{EnumType::Amaura};
        static constexpr internal::Species_impl Aurorus{EnumType::Aurorus};
        static constexpr internal::Species_impl Sylveon{EnumType::Sylveon};
        static constexpr internal::Species_impl Hawlucha{EnumType::Hawlucha};
        static constexpr internal::Species_impl Dedenne{EnumType::Dedenne};
        static constexpr internal::Species_impl Carbink{EnumType::Carbink};
        static constexpr internal::Species_impl Goomy{EnumType::Goomy};
        static constexpr internal::Species_impl Sliggoo{EnumType::Sliggoo};
        static constexpr internal::Species_impl Goodra{EnumType::Goodra};
        static constexpr internal::Species_impl Klefki{EnumType::Klefki};
        static constexpr internal::Species_impl Phantump{EnumType::Phantump};
        static constexpr internal::Species_impl Trevenant{EnumType::Trevenant};
        static constexpr internal::Species_impl Pumpkaboo{EnumType::Pumpkaboo};
        static constexpr internal::Species_impl Gourgeist{EnumType::Gourgeist};
        static constexpr internal::Species_impl Bergmite{EnumType::Bergmite};
        static constexpr internal::Species_impl Avalugg{EnumType::Avalugg};
        static constexpr internal::Species_impl Noibat{EnumType::Noibat};
        static constexpr internal::Species_impl Noivern{EnumType::Noivern};
        static constexpr internal::Species_impl Xerneas{EnumType::Xerneas};
        static constexpr internal::Species_impl Yveltal{EnumType::Yveltal};
        static constexpr internal::Species_impl Zygarde{EnumType::Zygarde};
        static constexpr internal::Species_impl Diancie{EnumType::Diancie};
        static constexpr internal::Species_impl Hoopa{EnumType::Hoopa};
        static constexpr internal::Species_impl Volcanion{EnumType::Volcanion};
        static constexpr internal::Species_impl Rowlet{EnumType::Rowlet};
        static constexpr internal::Species_impl Dartrix{EnumType::Dartrix};
        static constexpr internal::Species_impl Decidueye{EnumType::Decidueye};
        static constexpr internal::Species_impl Litten{EnumType::Litten};
        static constexpr internal::Species_impl Torracat{EnumType::Torracat};
        static constexpr internal::Species_impl Incineroar{EnumType::Incineroar};
        static constexpr internal::Species_impl Popplio{EnumType::Popplio};
        static constexpr internal::Species_impl Brionne{EnumType::Brionne};
        static constexpr internal::Species_impl Primarina{EnumType::Primarina};
        static constexpr internal::Species_impl Pikipek{EnumType::Pikipek};
        static constexpr internal::Species_impl Trumbeak{EnumType::Trumbeak};
        static constexpr internal::Species_impl Toucannon{EnumType::Toucannon};
        static constexpr internal::Species_impl Yungoos{EnumType::Yungoos};
        static constexpr internal::Species_impl Gumshoos{EnumType::Gumshoos};
        static constexpr internal::Species_impl Grubbin{EnumType::Grubbin};
        static constexpr internal::Species_impl Charjabug{EnumType::Charjabug};
        static constexpr internal::Species_impl Vikavolt{EnumType::Vikavolt};
        static constexpr internal::Species_impl Crabrawler{EnumType::Crabrawler};
        static constexpr internal::Species_impl Crabominable{EnumType::Crabominable};
        static constexpr internal::Species_impl Oricorio{EnumType::Oricorio};
        static constexpr internal::Species_impl Cutiefly{EnumType::Cutiefly};
        static constexpr internal::Species_impl Ribombee{EnumType::Ribombee};
        static constexpr internal::Species_impl Rockruff{EnumType::Rockruff};
        static constexpr internal::Species_impl Lycanroc{EnumType::Lycanroc};
        static constexpr internal::Species_impl Wishiwashi{EnumType::Wishiwashi};
        static constexpr internal::Species_impl Mareanie{EnumType::Mareanie};
        static constexpr internal::Species_impl Toxapex{EnumType::Toxapex};
        static constexpr internal::Species_impl Mudbray{EnumType::Mudbray};
        static constexpr internal::Species_impl Mudsdale{EnumType::Mudsdale};
        static constexpr internal::Species_impl Dewpider{EnumType::Dewpider};
        static constexpr internal::Species_impl Araquanid{EnumType::Araquanid};
        static constexpr internal::Species_impl Fomantis{EnumType::Fomantis};
        static constexpr internal::Species_impl Lurantis{EnumType::Lurantis};
        static constexpr internal::Species_impl Morelull{EnumType::Morelull};
        static constexpr internal::Species_impl Shiinotic{EnumType::Shiinotic};
        static constexpr internal::Species_impl Salandit{EnumType::Salandit};
        static constexpr internal::Species_impl Salazzle{EnumType::Salazzle};
        static constexpr internal::Species_impl Stufful{EnumType::Stufful};
        static constexpr internal::Species_impl Bewear{EnumType::Bewear};
        static constexpr internal::Species_impl Bounsweet{EnumType::Bounsweet};
        static constexpr internal::Species_impl Steenee{EnumType::Steenee};
        static constexpr internal::Species_impl Tsareena{EnumType::Tsareena};
        static constexpr internal::Species_impl Comfey{EnumType::Comfey};
        static constexpr internal::Species_impl Oranguru{EnumType::Oranguru};
        static constexpr internal::Species_impl Passimian{EnumType::Passimian};
        static constexpr internal::Species_impl Wimpod{EnumType::Wimpod};
        static constexpr internal::Species_impl Golisopod{EnumType::Golisopod};
        static constexpr internal::Species_impl Sandygast{EnumType::Sandygast};
        static constexpr internal::Species_impl Palossand{EnumType::Palossand};
        static constexpr internal::Species_impl Pyukumuku{EnumType::Pyukumuku};
        static constexpr internal::Species_impl TypeNull{EnumType::TypeNull};
        static constexpr internal::Species_impl Silvally{EnumType::Silvally};
        static constexpr internal::Species_impl Minior{EnumType::Minior};
        static constexpr internal::Species_impl Komala{EnumType::Komala};
        static constexpr internal::Species_impl Turtonator{EnumType::Turtonator};
        static constexpr internal::Species_impl Togedemaru{EnumType::Togedemaru};
        static constexpr internal::Species_impl Mimikyu{EnumType::Mimikyu};
        static constexpr internal::Species_impl Bruxish{EnumType::Bruxish};
        static constexpr internal::Species_impl Drampa{EnumType::Drampa};
        static constexpr internal::Species_impl Dhelmise{EnumType::Dhelmise};
        static constexpr internal::Species_impl Jangmoo{EnumType::Jangmoo};
        static constexpr internal::Species_impl Hakamoo{EnumType::Hakamoo};
        static constexpr internal::Species_impl Kommoo{EnumType::Kommoo};
        static constexpr internal::Species_impl TapuKoko{EnumType::TapuKoko};
        static constexpr internal::Species_impl TapuLele{EnumType::TapuLele};
        static constexpr internal::Species_impl TapuBulu{EnumType::TapuBulu};
        static constexpr internal::Species_impl TapuFini{EnumType::TapuFini};
        static constexpr internal::Species_impl Cosmog{EnumType::Cosmog};
        static constexpr internal::Species_impl Cosmoem{EnumType::Cosmoem};
        static constexpr internal::Species_impl Solgaleo{EnumType::Solgaleo};
        static constexpr internal::Species_impl Lunala{EnumType::Lunala};
        static constexpr internal::Species_impl Nihilego{EnumType::Nihilego};
        static constexpr internal::Species_impl Buzzwole{EnumType::Buzzwole};
        static constexpr internal::Species_impl Pheromosa{EnumType::Pheromosa};
        static constexpr internal::Species_impl Xurkitree{EnumType::Xurkitree};
        static constexpr internal::Species_impl Celesteela{EnumType::Celesteela};
        static constexpr internal::Species_impl Kartana{EnumType::Kartana};
        static constexpr internal::Species_impl Guzzlord{EnumType::Guzzlord};
        static constexpr internal::Species_impl Necrozma{EnumType::Necrozma};
        static constexpr internal::Species_impl Magearna{EnumType::Magearna};
        static constexpr internal::Species_impl Marshadow{EnumType::Marshadow};
        static constexpr internal::Species_impl Poipole{EnumType::Poipole};
        static constexpr internal::Species_impl Naganadel{EnumType::Naganadel};
        static constexpr internal::Species_impl Stakataka{EnumType::Stakataka};
        static constexpr internal::Species_impl Blacephalon{EnumType::Blacephalon};
        static constexpr internal::Species_impl Zeraora{EnumType::Zeraora};
        static constexpr internal::Species_impl Meltan{EnumType::Meltan};
        static constexpr internal::Species_impl Melmetal{EnumType::Melmetal};
        static constexpr internal::Species_impl Grookey{EnumType::Grookey};
        static constexpr internal::Species_impl Thwackey{EnumType::Thwackey};
        static constexpr internal::Species_impl Rillaboom{EnumType::Rillaboom};
        static constexpr internal::Species_impl Scorbunny{EnumType::Scorbunny};
        static constexpr internal::Species_impl Raboot{EnumType::Raboot};
        static constexpr internal::Species_impl Cinderace{EnumType::Cinderace};
        static constexpr internal::Species_impl Sobble{EnumType::Sobble};
        static constexpr internal::Species_impl Drizzile{EnumType::Drizzile};
        static constexpr internal::Species_impl Inteleon{EnumType::Inteleon};
        static constexpr internal::Species_impl Skwovet{EnumType::Skwovet};
        static constexpr internal::Species_impl Greedent{EnumType::Greedent};
        static constexpr internal::Species_impl Rookidee{EnumType::Rookidee};
        static constexpr internal::Species_impl Corvisquire{EnumType::Corvisquire};
        static constexpr internal::Species_impl Corviknight{EnumType::Corviknight};
        static constexpr internal::Species_impl Blipbug{EnumType::Blipbug};
        static constexpr internal::Species_impl Dottler{EnumType::Dottler};
        static constexpr internal::Species_impl Orbeetle{EnumType::Orbeetle};
        static constexpr internal::Species_impl Nickit{EnumType::Nickit};
        static constexpr internal::Species_impl Thievul{EnumType::Thievul};
        static constexpr internal::Species_impl Gossifleur{EnumType::Gossifleur};
        static constexpr internal::Species_impl Eldegoss{EnumType::Eldegoss};
        static constexpr internal::Species_impl Wooloo{EnumType::Wooloo};
        static constexpr internal::Species_impl Dubwool{EnumType::Dubwool};
        static constexpr internal::Species_impl Chewtle{EnumType::Chewtle};
        static constexpr internal::Species_impl Drednaw{EnumType::Drednaw};
        static constexpr internal::Species_impl Yamper{EnumType::Yamper};
        static constexpr internal::Species_impl Boltund{EnumType::Boltund};
        static constexpr internal::Species_impl Rolycoly{EnumType::Rolycoly};
        static constexpr internal::Species_impl Carkol{EnumType::Carkol};
        static constexpr internal::Species_impl Coalossal{EnumType::Coalossal};
        static constexpr internal::Species_impl Applin{EnumType::Applin};
        static constexpr internal::Species_impl Flapple{EnumType::Flapple};
        static constexpr internal::Species_impl Appletun{EnumType::Appletun};
        static constexpr internal::Species_impl Silicobra{EnumType::Silicobra};
        static constexpr internal::Species_impl Sandaconda{EnumType::Sandaconda};
        static constexpr internal::Species_impl Cramorant{EnumType::Cramorant};
        static constexpr internal::Species_impl Arrokuda{EnumType::Arrokuda};
        static constexpr internal::Species_impl Barraskewda{EnumType::Barraskewda};
        static constexpr internal::Species_impl Toxel{EnumType::Toxel};
        static constexpr internal::Species_impl Toxtricity{EnumType::Toxtricity};
        static constexpr internal::Species_impl Sizzlipede{EnumType::Sizzlipede};
        static constexpr internal::Species_impl Centiskorch{EnumType::Centiskorch};
        static constexpr internal::Species_impl Clobbopus{EnumType::Clobbopus};
        static constexpr internal::Species_impl Grapploct{EnumType::Grapploct};
        static constexpr internal::Species_impl Sinistea{EnumType::Sinistea};
        static constexpr internal::Species_impl Polteageist{EnumType::Polteageist};
        static constexpr internal::Species_impl Hatenna{EnumType::Hatenna};
        static constexpr internal::Species_impl Hattrem{EnumType::Hattrem};
        static constexpr internal::Species_impl Hatterene{EnumType::Hatterene};
        static constexpr internal::Species_impl Impidimp{EnumType::Impidimp};
        static constexpr internal::Species_impl Morgrem{EnumType::Morgrem};
        static constexpr internal::Species_impl Grimmsnarl{EnumType::Grimmsnarl};
        static constexpr internal::Species_impl Obstagoon{EnumType::Obstagoon};
        static constexpr internal::Species_impl Perrserker{EnumType::Perrserker};
        static constexpr internal::Species_impl Cursola{EnumType::Cursola};
        static constexpr internal::Species_impl Sirfetchd{EnumType::Sirfetchd};
        static constexpr internal::Species_impl MrRime{EnumType::MrRime};
        static constexpr internal::Species_impl Runerigus{EnumType::Runerigus};
        static constexpr internal::Species_impl Milcery{EnumType::Milcery};
        static constexpr internal::Species_impl Alcremie{EnumType::Alcremie};
        static constexpr internal::Species_impl Falinks{EnumType::Falinks};
        static constexpr internal::Species_impl Pincurchin{EnumType::Pincurchin};
        static constexpr internal::Species_impl Snom{EnumType::Snom};
        static constexpr internal::Species_impl Frosmoth{EnumType::Frosmoth};
        static constexpr internal::Species_impl Stonjourner{EnumType::Stonjourner};
        static constexpr internal::Species_impl Eiscue{EnumType::Eiscue};
        static constexpr internal::Species_impl Indeedee{EnumType::Indeedee};
        static constexpr internal::Species_impl Morpeko{EnumType::Morpeko};
        static constexpr internal::Species_impl Cufant{EnumType::Cufant};
        static constexpr internal::Species_impl Copperajah{EnumType::Copperajah};
        static constexpr internal::Species_impl Dracozolt{EnumType::Dracozolt};
        static constexpr internal::Species_impl Arctozolt{EnumType::Arctozolt};
        static constexpr internal::Species_impl Dracovish{EnumType::Dracovish};
        static constexpr internal::Species_impl Arctovish{EnumType::Arctovish};
        static constexpr internal::Species_impl Duraludon{EnumType::Duraludon};
        static constexpr internal::Species_impl Dreepy{EnumType::Dreepy};
        static constexpr internal::Species_impl Drakloak{EnumType::Drakloak};
        static constexpr internal::Species_impl Dragapult{EnumType::Dragapult};
        static constexpr internal::Species_impl Zacian{EnumType::Zacian};
        static constexpr internal::Species_impl Zamazenta{EnumType::Zamazenta};
        static constexpr internal::Species_impl Eternatus{EnumType::Eternatus};
        static constexpr internal::Species_impl Kubfu{EnumType::Kubfu};
        static constexpr internal::Species_impl Urshifu{EnumType::Urshifu};
        static constexpr internal::Species_impl Zarude{EnumType::Zarude};
        static constexpr internal::Species_impl Regieleki{EnumType::Regieleki};
        static constexpr internal::Species_impl Regidrago{EnumType::Regidrago};
        static constexpr internal::Species_impl Glastrier{EnumType::Glastrier};
        static constexpr internal::Species_impl Spectrier{EnumType::Spectrier};
        static constexpr internal::Species_impl Calyrex{EnumType::Calyrex};

        static constexpr internal::Species_impl INVALID{EnumType::INVALID};
    };
}

#endif
