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

#include "wcx/WC8.hpp"
#include "personal/personal.hpp"
#include "utils/endian.hpp"
#include "utils/flagUtil.hpp"
#include "utils/utils.hpp"

#define RIBBON_ABSENT 0xFFFFFFFF

namespace
{
    int langIndex(pksm::Language lang)
    {
        if (lang > pksm::Language::UNUSED)
        {
            return u8(lang) - 2;
        }
        else if (lang == pksm::Language::UNUSED)
        {
            return 2 - 1; // English
        }
        else
        {
            return u8(lang) - 1;
        }
    }

    std::pair<size_t, size_t> OFFSET_OF(pksm::Ribbon rib)
    {
        switch (rib)
        {
            case pksm::Ribbon::ChampionKalos:
                return {0x24C, 0};
            case pksm::Ribbon::ChampionG3Hoenn:
                return {0x24C, 1};
            case pksm::Ribbon::ChampionSinnoh:
                return {0x24C, 2};
            case pksm::Ribbon::BestFriends:
                return {0x24C, 3};
            case pksm::Ribbon::Training:
                return {0x24C, 4};
            case pksm::Ribbon::BattlerSkillful:
                return {0x24C, 5};
            case pksm::Ribbon::BattlerExpert:
                return {0x24C, 6};
            case pksm::Ribbon::Effort:
                return {0x24C, 7};
            case pksm::Ribbon::Alert:
                return {0x24D, 0};
            case pksm::Ribbon::Shock:
                return {0x24D, 1};
            case pksm::Ribbon::Downcast:
                return {0x24D, 2};
            case pksm::Ribbon::Careless:
                return {0x24D, 3};
            case pksm::Ribbon::Relax:
                return {0x24D, 4};
            case pksm::Ribbon::Snooze:
                return {0x24D, 5};
            case pksm::Ribbon::Smile:
                return {0x24D, 6};
            case pksm::Ribbon::Gorgeous:
                return {0x24D, 7};
            case pksm::Ribbon::Royal:
                return {0x24E, 0};
            case pksm::Ribbon::GorgeousRoyal:
                return {0x24E, 1};
            case pksm::Ribbon::Artist:
                return {0x24E, 2};
            case pksm::Ribbon::Footprint:
                return {0x24E, 3};
            case pksm::Ribbon::Record:
                return {0x24E, 4};
            case pksm::Ribbon::Legend:
                return {0x24E, 5};
            case pksm::Ribbon::Country:
                return {0x24E, 6};
            case pksm::Ribbon::National:
                return {0x24E, 7};
            case pksm::Ribbon::Earth:
                return {0x24F, 0};
            case pksm::Ribbon::World:
                return {0x24F, 1};
            case pksm::Ribbon::Classic:
                return {0x24F, 2};
            case pksm::Ribbon::Premier:
                return {0x24F, 3};
            case pksm::Ribbon::Event:
                return {0x24F, 4};
            case pksm::Ribbon::Birthday:
                return {0x24F, 5};
            case pksm::Ribbon::Special:
                return {0x24F, 6};
            case pksm::Ribbon::Souvenir:
                return {0x24F, 7};
            case pksm::Ribbon::Wishing:
                return {0x250, 0};
            case pksm::Ribbon::ChampionBattle:
                return {0x250, 1};
            case pksm::Ribbon::ChampionRegional:
                return {0x250, 2};
            case pksm::Ribbon::ChampionNational:
                return {0x250, 3};
            case pksm::Ribbon::ChampionWorld:
                return {0x250, 4};
            case pksm::Ribbon::MemoryContest:
                return {0x250, 5};
            case pksm::Ribbon::MemoryBattle:
                return {0x250, 6};
            case pksm::Ribbon::ChampionG6Hoenn:
                return {0x250, 7};
            case pksm::Ribbon::ContestStar:
                return {0x251, 0};
            case pksm::Ribbon::MasterCoolness:
                return {0x251, 1};
            case pksm::Ribbon::MasterBeauty:
                return {0x251, 2};
            case pksm::Ribbon::MasterCuteness:
                return {0x251, 3};
            case pksm::Ribbon::MasterCleverness:
                return {0x251, 4};
            case pksm::Ribbon::MasterToughness:
                return {0x251, 5};
            case pksm::Ribbon::ChampionAlola:
                return {0x251, 6};
            case pksm::Ribbon::BattleRoyale:
                return {0x251, 7};
            case pksm::Ribbon::BattleTreeGreat:
                return {0x252, 0};
            case pksm::Ribbon::BattleTreeMaster:
                return {0x252, 1};
            case pksm::Ribbon::ChampionGalar:
                return {0x252, 2};
            case pksm::Ribbon::TowerMaster:
                return {0x252, 3};
            case pksm::Ribbon::MasterRank:
                return {0x252, 4};
            case pksm::Ribbon::MarkLunchtime:
                return {0x252, 5};
            case pksm::Ribbon::MarkSleepyTime:
                return {0x252, 6};
            case pksm::Ribbon::MarkDusk:
                return {0x252, 7};
            case pksm::Ribbon::MarkDawn:
                return {0x253, 0};
            case pksm::Ribbon::MarkCloudy:
                return {0x253, 1};
            case pksm::Ribbon::MarkRainy:
                return {0x253, 2};
            case pksm::Ribbon::MarkStormy:
                return {0x253, 3};
            case pksm::Ribbon::MarkSnowy:
                return {0x253, 4};
            case pksm::Ribbon::MarkBlizzard:
                return {0x253, 5};
            case pksm::Ribbon::MarkDry:
                return {0x253, 6};
            case pksm::Ribbon::MarkSandstorm:
                return {0x253, 7};
            case pksm::Ribbon::MarkMisty:
                return {0x258, 0};
            case pksm::Ribbon::MarkDestiny:
                return {0x258, 1};
            case pksm::Ribbon::MarkFishing:
                return {0x258, 2};
            case pksm::Ribbon::MarkCurry:
                return {0x258, 3};
            case pksm::Ribbon::MarkUncommon:
                return {0x258, 4};
            case pksm::Ribbon::MarkRare:
                return {0x258, 5};
            case pksm::Ribbon::MarkRowdy:
                return {0x258, 6};
            case pksm::Ribbon::MarkAbsentMinded:
                return {0x258, 7};
            case pksm::Ribbon::MarkJittery:
                return {0x259, 0};
            case pksm::Ribbon::MarkExcited:
                return {0x259, 1};
            case pksm::Ribbon::MarkCharismatic:
                return {0x259, 2};
            case pksm::Ribbon::MarkCalmness:
                return {0x259, 3};
            case pksm::Ribbon::MarkIntense:
                return {0x259, 4};
            case pksm::Ribbon::MarkZonedOut:
                return {0x259, 5};
            case pksm::Ribbon::MarkJoyful:
                return {0x259, 6};
            case pksm::Ribbon::MarkAngry:
                return {0x259, 7};
            case pksm::Ribbon::MarkSmiley:
                return {0x25A, 0};
            case pksm::Ribbon::MarkTeary:
                return {0x25A, 1};
            case pksm::Ribbon::MarkUpbeat:
                return {0x25A, 2};
            case pksm::Ribbon::MarkPeeved:
                return {0x25A, 3};
            case pksm::Ribbon::MarkIntellectual:
                return {0x25A, 4};
            case pksm::Ribbon::MarkFerocious:
                return {0x25A, 5};
            case pksm::Ribbon::MarkCrafty:
                return {0x25A, 6};
            case pksm::Ribbon::MarkScowling:
                return {0x25A, 7};
            case pksm::Ribbon::MarkKindly:
                return {0x25B, 0};
            case pksm::Ribbon::MarkFlustered:
                return {0x25B, 1};
            case pksm::Ribbon::MarkPumpedUp:
                return {0x25B, 2};
            case pksm::Ribbon::MarkZeroEnergy:
                return {0x25B, 3};
            case pksm::Ribbon::MarkPrideful:
                return {0x25B, 4};
            case pksm::Ribbon::MarkUnsure:
                return {0x25B, 5};
            case pksm::Ribbon::MarkHumble:
                return {0x25B, 6};
            case pksm::Ribbon::MarkThorny:
                return {0x25B, 7};
            case pksm::Ribbon::MarkVigor:
                return {0x25C, 0};
            case pksm::Ribbon::MarkSlump:
                return {0x25C, 1};

            default:
                return {RIBBON_ABSENT, 0};
        }
    }
}

namespace pksm
{
    WC8::WC8(u8* dt)
    {
        std::copy(dt, dt + length, data);
        for (int i = 0; i < 6; i++)
        {
            if (object(i) != 0)
            {
                numItems++;
            }
            else
                break;
        }
    }

    Generation WC8::generation() const { return Generation::EIGHT; }

    u16 WC8::ID() const { return LittleEndian::convertTo<u16>(data + 8); }

    std::string WC8::title() const { return title(titleIndex()); }

    std::string WC8::title(Language lang) const
    {
        // TODO: use titleIndex to get offset, then get string from offset
        (void)lang;
        return "Wonder Card";
    }

    Language WC8::titleIndex() const { return Language(data[0x15]); }

    u8 WC8::type() const { return data[0x11]; }

    u8 WC8::flags() const { return data[0x10]; }

    bool WC8::multiObtainable() const { return (flags() & 1) == 1; }

    bool WC8::BP(void) const { return type() == 3; }

    bool WC8::item(void) const { return type() == 2; }

    bool WC8::pokemon(void) const { return type() == 1; }

    bool WC8::clothing(void) const { return type() == 4; }

    u16 WC8::object(void) const { return object(0); }

    u16 WC8::object(int index) const
    {
        return LittleEndian::convertTo<u16>(data + 0x20 + index * 4);
    }

    int WC8::items(void) const { return numItems; }

    u16 WC8::objectQuantity(void) const { return objectQuantity(0); }

    u16 WC8::objectQuantity(int index) const
    {
        return LittleEndian::convertTo<u16>(data + 0x22 + index * 4);
    }

    u8 WC8::PIDType(void) const { return data[0x248]; }

    bool WC8::shiny(void) const { return PIDType() == 2 || PIDType() == 3; }

    u16 WC8::TID(void) const { return LittleEndian::convertTo<u16>(data + 0x20); }

    u16 WC8::SID(void) const { return LittleEndian::convertTo<u16>(data + 0x22); }

    GameVersion WC8::version(void) const
    {
        return GameVersion(LittleEndian::convertTo<u32>(data + 0x24));
    }

    u32 WC8::encryptionConstant(void) const { return LittleEndian::convertTo<u32>(data + 0x28); }

    u32 WC8::PID(void) const { return LittleEndian::convertTo<u32>(data + 0x2C); }

    Ball WC8::ball(void) const { return Ball{data[0x22C]}; }

    u16 WC8::heldItem(void) const { return LittleEndian::convertTo<u16>(data + 0x22E); }

    Move WC8::move(u8 m) const { return Move{LittleEndian::convertTo<u16>(data + 0x230 + m * 2)}; }

    Move WC8::relearnMove(u8 index) const
    {
        return Move{LittleEndian::convertTo<u16>(data + 0x238 + index * 2)};
    }

    Species WC8::species(void) const { return Species{LittleEndian::convertTo<u16>(data + 0x240)}; }

    u8 WC8::alternativeForm(void) const { return data[0x242]; }

    Gender WC8::gender(void) const { return Gender{data[0x243]}; }

    u8 WC8::level(void) const { return data[0x244]; }

    bool WC8::egg(void) const { return data[0x245] == 1; }

    Nature WC8::nature(void) const { return Nature{data[0x246]}; }

    u8 WC8::abilityType(void) const { return data[0x247]; }

    Ability WC8::ability(void) const
    {
        u8 abilitynum, type = abilityType();

        if (type == 2)
            abilitynum = 2;
        else if (type == 4)
            abilitynum = 2;
        else
            abilitynum = 0;

        return PersonalSWSH::ability(u16(species()), abilitynum);
    }

    u8 WC8::metLevel(void) const { return data[0x249]; }

    u8 WC8::dynamaxLevel(void) const { return data[0x24A]; }

    bool WC8::canGigantamax() const { return data[0x24B] != 0; }

    u8 WC8::ribbonValue(int index) const { return data[0x24C + index]; }

    u8 WC8::iv(Stat index) const { return data[0x26C + u8(index)]; }

    Gender WC8::otGender(void) const { return Gender{data[0x272]}; }

    u8 WC8::ev(Stat index) const { return data[0x273 + u8(index)]; }

    u8 WC8::otIntensity(void) const { return data[0x279]; }

    u8 WC8::otMemory(void) const { return data[0x27A]; }

    u8 WC8::otFeeling(void) const { return data[0x27B]; }

    u16 WC8::otTextvar(void) const { return LittleEndian::convertTo<u16>(data + 0x27C); }

    u16 WC8::eggLocation(void) const { return LittleEndian::convertTo<u16>(data + 0x228); }

    u16 WC8::metLocation(void) const { return LittleEndian::convertTo<u16>(data + 0x22A); }

    bool WC8::hasRibbon(Ribbon rib) const { return OFFSET_OF(rib).first != RIBBON_ABSENT; }

    bool WC8::ribbon(Ribbon rib) const
    {
        auto offset = OFFSET_OF(rib);
        return offset.first != RIBBON_ABSENT ? FlagUtil::getFlag(data, offset.first, offset.second)
                                             : false;
    }

    bool WC8::nicknamed(Language lang) const { return nickname(lang)[0] != 0; }

    std::string WC8::nickname(Language lang) const
    {
        return StringUtils::getString(data, 0x30 + langIndex(lang) * 0x1C, 13);
    }

    Language WC8::nicknameLanguage(Language orig) const
    {
        return Language(data[0x30 + langIndex(orig) * 0x1C + 0x1A]);
    }

    std::string WC8::otName(Language lang) const
    {
        return StringUtils::getString(data, 0x12C + langIndex(lang) * 0x1C, 13);
    }

    std::string WC8::nickname() const { return nickname(Language::ENG); }

    std::string WC8::otName() const { return otName(Language::ENG); }

    bool WC8::used() const { return false; }

    u16 WC8::formSpecies(void) const
    {
        u16 tmpSpecies = u16(species());
        u8 form        = alternativeForm();
        u8 formcount   = PersonalSWSH::formCount(tmpSpecies);

        if (form && form < formcount)
        {
            u16 backSpecies = tmpSpecies;
            tmpSpecies      = PersonalSWSH::formStatIndex(tmpSpecies);
            if (!tmpSpecies)
            {
                tmpSpecies = backSpecies;
            }
            else
            {
                tmpSpecies += form - 1;
            }
        }

        return tmpSpecies;
    }
}
