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

#ifndef PKX_HPP
#define PKX_HPP

#include "enums/Ability.hpp"
#include "enums/Ball.hpp"
#include "enums/GameVersion.hpp"
#include "enums/Gender.hpp"
#include "enums/Generation.hpp"
#include "enums/Language.hpp"
#include "enums/Move.hpp"
#include "enums/Nature.hpp"
#include "enums/Ribbon.hpp"
#include "enums/Species.hpp"
#include "enums/Stat.hpp"
#include "enums/Type.hpp"
#include "pkx/IPKFilterable.hpp"
#include "pkx/PKFilter.hpp"
#include "sav/Item.hpp"
#include "utils/DateTime.hpp"
#include "utils/coretypes.h"
#include "utils/genToPkx.hpp"
#include <memory>
#include <string>

namespace pksm
{
    class Sav;
    class PK3;
    class PK4;
    class PK5;
    class PK6;
    class PK7;
    class PK8;
    class PB7;

    class PKX : public IPKFilterable
    {
    private:
        bool directAccess;
        virtual int eggYear(void) const  = 0;
        virtual void eggYear(int v)      = 0;
        virtual int eggMonth(void) const = 0;
        virtual void eggMonth(int v)     = 0;
        virtual int eggDay(void) const   = 0;
        virtual void eggDay(int v)       = 0;
        virtual int metYear(void) const  = 0;
        virtual void metYear(int v)      = 0;
        virtual int metMonth(void) const = 0;
        virtual void metMonth(int v)     = 0;
        virtual int metDay(void) const   = 0;
        virtual void metDay(int v)       = 0;

    protected:
        struct PrivateConstructor
        {
        };

        PKX(u8* data, size_t length, bool directAccess = false);

        u32 expTable(u8 row, u8 col) const;
        virtual void reorderMoves(void);

        u32 length = 0;
        u8* data;

    public:
        static constexpr Species PKSM_MAX_SPECIES = Species::Calyrex;

        static std::unique_ptr<PKX> getPKM(
            Generation gen, u8* data, bool party = false, bool directAccess = false);
        template <Generation::EnumType g>
        static std::unique_ptr<typename GenToPkx<g>::PKX> getPKM(
            u8* data, bool party = false, bool directAccess = false)
        {
            return getPKM<typename GenToPkx<g>::PKX>(data, party, directAccess);
        }
        template <typename Pkm>
        static std::enable_if_t<std::is_base_of_v<::pksm::PKX, Pkm>, std::unique_ptr<Pkm>> getPKM(
            u8* data, bool party = false, bool directAccess = false)
        {
            return std::make_unique<Pkm>(PrivateConstructor{}, data, party, directAccess);
        }

        // Returns null if length is not valid for that generation, and a party Pokemon depending on
        // length
        static std::unique_ptr<PKX> getPKM(
            Generation gen, u8* data, size_t length, bool directAccess = false);
        template <Generation::EnumType g>
        static std::unique_ptr<typename GenToPkx<g>::PKX> getPKM(
            u8* data, size_t length, bool directAccess = false)
        {
            return getPKM<typename GenToPkx<g>::PKX>(data, length, directAccess);
        }
        template <typename Pkm>
        static std::enable_if_t<std::is_base_of_v<::pksm::PKX, Pkm>, std::unique_ptr<Pkm>> getPKM(
            u8* data, size_t length, bool directAccess = false)
        {
            if (Pkm::PARTY_LENGTH == length || Pkm::BOX_LENGTH == length)
            {
                return getPKM<Pkm>(data, length == Pkm::PARTY_LENGTH, directAccess);
            }
            return nullptr;
        }

        virtual ~PKX();
        PKX(const PKX& pk);
        PKX(PKX&& pk);
        PKX& operator=(const PKX& pk);
        PKX& operator=(PKX&& pk);
        bool operator==(const PKFilter& filter) const;

        virtual std::string extension(void) const { return ".pk" + (std::string)generation(); }

        u8* rawData(void) { return data; }
        const u8* rawData(void) const { return data; }
        u32 getLength(void) const { return length; }
        virtual bool isParty(void) const = 0;

        virtual void decrypt(void)       = 0;
        virtual void encrypt(void)       = 0;
        virtual bool isEncrypted() const = 0;

        virtual std::unique_ptr<PK3> convertToG3(Sav& save) const;
        virtual std::unique_ptr<PK4> convertToG4(Sav& save) const;
        virtual std::unique_ptr<PK5> convertToG5(Sav& save) const;
        virtual std::unique_ptr<PK6> convertToG6(Sav& save) const;
        virtual std::unique_ptr<PK7> convertToG7(Sav& save) const;
        virtual std::unique_ptr<PB7> convertToLGPE(Sav& save) const;
        virtual std::unique_ptr<PK8> convertToG8(Sav& save) const;
        virtual std::unique_ptr<PKX> clone(void) const = 0;
        std::unique_ptr<PKX> partyClone(void) const;

        virtual Generation generation(void) const override = 0;
        bool originGen7(void) const;
        bool originGen6(void) const;
        bool originGen5(void) const;
        bool originGen4(void) const;
        bool originGen3(void) const;
        Generation originGen(void) const;
        void fixMoves(void);

        static u32 getRandomPID(Species species, Gender gender, GameVersion originGame,
            Nature nature, u8 form, u8 abilityNum, u32 oldPid, Generation gen);
        static Gender genderFromRatio(u32 pid, u8 gt);

        // BLOCK A
        virtual u32 encryptionConstant(void) const   = 0;
        virtual void encryptionConstant(u32 v)       = 0;
        virtual u16 sanity(void) const               = 0;
        virtual void sanity(u16 v)                   = 0;
        virtual u16 checksum(void) const             = 0;
        virtual void checksum(u16 v)                 = 0;
        virtual Species species(void) const override = 0;
        virtual void species(Species v) override     = 0;
        virtual u16 heldItem(void) const override    = 0;
        virtual void heldItem(u16 v) override        = 0;
        virtual void heldItem(const Item& item) { heldItem(item.id()); }
        virtual u16 TID(void) const                      = 0;
        virtual void TID(u16 v)                          = 0;
        virtual u16 SID(void) const                      = 0;
        virtual void SID(u16 v)                          = 0;
        virtual u32 experience(void) const               = 0;
        virtual void experience(u32 v)                   = 0;
        virtual Ability ability(void) const override     = 0;
        virtual void ability(Ability v) override         = 0;
        virtual u8 abilityNumber(void) const             = 0;
        virtual void abilityNumber(u8 v)                 = 0;
        virtual void setAbility(u8 abilityNumber)        = 0;
        virtual u16 markValue(void) const                = 0;
        virtual void markValue(u16 v)                    = 0;
        virtual u32 PID(void) const                      = 0;
        virtual void PID(u32 v)                          = 0;
        virtual Nature nature(void) const override       = 0;
        virtual void nature(Nature v) override           = 0;
        virtual bool fatefulEncounter(void) const        = 0;
        virtual void fatefulEncounter(bool v)            = 0;
        virtual Gender gender(void) const override       = 0;
        virtual void gender(Gender g) override           = 0;
        virtual u16 alternativeForm(void) const override = 0;
        virtual void alternativeForm(u16 v) override     = 0;
        virtual u8 ev(Stat ev) const                     = 0;
        virtual void ev(Stat ev, u8 v)                   = 0;
        virtual u8 contest(u8 contest) const             = 0;
        virtual void contest(u8 contest, u8 v)           = 0;
        virtual u8 pkrs(void) const                      = 0;
        virtual void pkrs(u8 v)                          = 0;
        virtual u8 pkrsDays(void) const                  = 0;
        virtual void pkrsDays(u8 v)                      = 0;
        virtual u8 pkrsStrain(void) const                = 0;
        virtual void pkrsStrain(u8 v)                    = 0;
        virtual bool hasRibbon(Ribbon rib) const         = 0;
        virtual bool ribbon(Ribbon rib) const            = 0;
        virtual void ribbon(Ribbon rib, bool v)          = 0;

        // BLOCK B
        virtual std::string nickname(void) const           = 0;
        virtual void nickname(const std::string_view& v)   = 0;
        virtual Move move(u8 move) const override          = 0;
        virtual void move(u8 move, Move v) override        = 0;
        virtual Move relearnMove(u8 move) const override   = 0;
        virtual void relearnMove(u8 move, Move v) override = 0;
        virtual u8 PP(u8 move) const                       = 0;
        virtual void PP(u8 move, u8 v)                     = 0;
        virtual u8 PPUp(u8 move) const                     = 0;
        virtual void PPUp(u8 move, u8 v)                   = 0;
        virtual u8 iv(Stat iv) const override              = 0;
        virtual void iv(Stat iv, u8 v) override            = 0;
        virtual bool egg(void) const override              = 0;
        virtual void egg(bool v) override                  = 0;
        virtual bool nicknamed(void) const                 = 0;
        virtual void nicknamed(bool v)                     = 0;

        virtual bool hyperTrain(Stat stat) const   = 0;
        virtual void hyperTrain(Stat stat, bool v) = 0;

        u8 maxPP(u8 move) const;
        void healPP();
        void healPP(u8 move) { PP(move, maxPP(move)); }

        // BLOCK C
        virtual u8 currentHandler(void) const = 0;
        virtual void currentHandler(u8 v)     = 0;

        // BLOCK D
        virtual std::string otName(void) const         = 0;
        virtual void otName(const std::string_view& v) = 0;
        virtual u8 otFriendship(void) const            = 0;
        virtual void otFriendship(u8 v)                = 0;
        // Raw information handled in private functions
        virtual Date eggDate(void) const
        {
            return Date{(u8)eggDay(), (u8)eggMonth(), (u32)eggYear()};
        }
        virtual void eggDate(const Date& v)
        {
            eggDay(v.day());
            eggMonth(v.month());
            eggYear(v.year());
        }
        virtual Date metDate(void) const
        {
            return Date{(u8)metDay(), (u8)metMonth(), (u32)metYear()};
        }
        virtual void metDate(const Date& v)
        {
            metDay(v.day());
            metMonth(v.month());
            metYear(v.year());
        }
        virtual u16 eggLocation(void) const            = 0;
        virtual void eggLocation(u16 v)                = 0;
        virtual u16 metLocation(void) const            = 0;
        virtual void metLocation(u16 v)                = 0;
        virtual Ball ball(void) const override         = 0;
        virtual void ball(Ball v) override             = 0;
        virtual u8 metLevel(void) const                = 0;
        virtual void metLevel(u8 v)                    = 0;
        virtual Gender otGender(void) const            = 0;
        virtual void otGender(Gender v)                = 0;
        virtual GameVersion version(void) const        = 0;
        virtual void version(GameVersion v)            = 0;
        virtual Language language(void) const override = 0;
        virtual void language(Language v) override     = 0;

        virtual u8 currentFriendship(void) const = 0;
        virtual void currentFriendship(u8 v)     = 0;
        virtual void refreshChecksum(void)       = 0;
        virtual Type hpType(void) const          = 0;
        virtual void hpType(Type v)              = 0;
        virtual u16 TSV(void) const override     = 0;
        virtual u16 PSV(void) const              = 0;
        u32 versionTID(void) const;
        u32 versionSID(void) const;
        u32 formatTID(void) const;
        u32 formatSID(void) const;
        virtual u8 level(void) const override   = 0;
        virtual void level(u8 v) override       = 0;
        virtual bool shiny(void) const override = 0;
        virtual void shiny(bool v) override     = 0;
        virtual u16 formSpecies(void) const     = 0;
        virtual u16 stat(Stat stat) const       = 0;

        // Hehehehe... to be done
        // virtual u8 sleepTurns(void) const = 0;
        // virtual void sleepTurns(u8 v) = 0;
        // virtual bool poison(void) const = 0;
        // virtual void poison(bool v) = 0;
        // virtual bool burn(void) const = 0;
        // virtual void burn(bool v) = 0;
        // virtual bool frozen(void) const = 0;
        // virtual void frozen(bool v) = 0;
        // virtual bool paralyzed(void) const = 0;
        // virtual void paralyzed(bool v) = 0;
        // virtual bool toxic(void) const = 0;
        // virtual void toxic(bool v) = 0;
        // -1 means not a party pokemon
        virtual int partyCurrHP(void) const      = 0;
        virtual void partyCurrHP(u16 v)          = 0;
        virtual int partyStat(Stat stat) const   = 0;
        virtual void partyStat(Stat stat, u16 v) = 0;
        virtual int partyLevel(void) const       = 0;
        virtual void partyLevel(u8 v)            = 0;
        // Takes any calculated stats and writes them into the party offsets, provided they exist
        virtual void updatePartyData(void) = 0;

        // Personal interface
        virtual u8 baseHP(void) const         = 0;
        virtual u8 baseAtk(void) const        = 0;
        virtual u8 baseDef(void) const        = 0;
        virtual u8 baseSpe(void) const        = 0;
        virtual u8 baseSpa(void) const        = 0;
        virtual u8 baseSpd(void) const        = 0;
        virtual Type type1(void) const        = 0;
        virtual Type type2(void) const        = 0;
        virtual u8 genderType(void) const     = 0;
        virtual u8 baseFriendship(void) const = 0;
        virtual u8 expType(void) const        = 0;
        virtual Ability abilities(u8 n) const = 0;
        virtual u16 formStatIndex(void) const = 0;

        bool isFilter() const final { return false; }
    };
}

#endif
