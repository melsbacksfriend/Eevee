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

#ifndef PK4_HPP
#define PK4_HPP

#include "personal/personal.hpp"
#include "pkx/PKX.hpp"

namespace pksm
{
    class PK4 : public PKX
    {
    private:
        static constexpr size_t BLOCK_LENGTH     = 32;
        static constexpr size_t ENCRYPTION_START = 8;
        int eggYear(void) const override;
        void eggYear(int v) override;
        int eggMonth(void) const override;
        void eggMonth(int v) override;
        int eggDay(void) const override;
        void eggDay(int v) override;
        int metYear(void) const override;
        void metYear(int v) override;
        int metMonth(void) const override;
        void metMonth(int v) override;
        int metDay(void) const override;
        void metDay(int v) override;

    protected:
        static constexpr Species beasts[4] = {
            Species::Celebi, Species::Raikou, Species::Entei, Species::Suicune};
        static constexpr Move banned[8] = {Move::Cut, Move::Fly, Move::Surf, Move::Strength,
            Move::Whirlpool, Move::RockSmash, Move::Waterfall, Move::RockClimb};

    public:
        static constexpr size_t BOX_LENGTH            = 136;
        static constexpr size_t PARTY_LENGTH          = 236;
        static constexpr Species FORMAT_SPECIES_LIMIT = Species::Arceus;

        PK4(PrivateConstructor, u8* dt, bool party = false, bool directAccess = false);

        std::unique_ptr<PK3> convertToG3(Sav& save) const override;
        std::unique_ptr<PK5> convertToG5(Sav& save) const override;
        std::unique_ptr<PK6> convertToG6(Sav& save) const override;
        std::unique_ptr<PK7> convertToG7(Sav& save) const override;
        // std::unique_ptr<PB7> convertToLGPE(Sav& save) const override;
        std::unique_ptr<PK8> convertToG8(Sav& save) const override;

        std::unique_ptr<PKX> clone(void) const override;

        Generation generation(void) const override;
        void decrypt(void) override;
        void encrypt(void) override;
        bool isEncrypted(void) const override;
        bool isParty(void) const override { return getLength() == PARTY_LENGTH; }

        u32 encryptionConstant(void) const override;
        void encryptionConstant(u32 v) override;
        u8 currentFriendship(void) const override;
        void currentFriendship(u8 v) override;
        u8 currentHandler(void) const override { return 0; }
        void currentHandler(u8) override {}
        u8 abilityNumber(void) const override;
        void abilityNumber(u8 v) override;
        void setAbility(u8 abilityNumber) override;

        u32 PID(void) const override;
        void PID(u32 v) override;
        u16 sanity(void) const override;
        void sanity(u16 v) override;
        u16 checksum(void) const override;
        void checksum(u16 v) override;
        Species species(void) const override;
        void species(Species v) override;
        u16 heldItem(void) const override;
        void heldItem(u16 v) override;
        u16 TID(void) const override;
        void TID(u16 v) override;
        u16 SID(void) const override;
        void SID(u16 v) override;
        u32 experience(void) const override;
        void experience(u32 v) override;
        u8 otFriendship(void) const override;
        void otFriendship(u8 v) override;
        Ability ability(void) const override;
        void ability(Ability v) override;
        u16 markValue(void) const override;
        void markValue(u16 v) override;
        Language language(void) const override;
        void language(Language v) override;
        u8 ev(Stat ev) const override;
        void ev(Stat ev, u8 v) override;
        u8 contest(u8 contest) const override;
        void contest(u8 contest, u8 v) override;
        bool hasRibbon(Ribbon rib) const override;
        bool ribbon(Ribbon rib) const override;
        void ribbon(Ribbon rib, bool v) override;

        Move move(u8 move) const override;
        void move(u8 move, Move v) override;
        Move relearnMove(u8) const override { return Move::None; }
        void relearnMove(u8, Move) override {}
        u8 PP(u8 move) const override;
        void PP(u8 move, u8 v) override;
        u8 PPUp(u8 move) const override;
        void PPUp(u8 move, u8 v) override;
        u8 iv(Stat iv) const override;
        void iv(Stat iv, u8 v) override;
        bool egg(void) const override;
        void egg(bool v) override;
        bool nicknamed(void) const override;
        void nicknamed(bool v) override;
        bool fatefulEncounter(void) const override;
        void fatefulEncounter(bool v) override;
        Gender gender(void) const override;
        void gender(Gender g) override;
        u16 alternativeForm(void) const override;
        void alternativeForm(u16 v) override;
        u8 shinyLeaf(void) const;
        void shinyLeaf(u8 v);
        Nature nature(void) const override;
        void nature(Nature v) override;
        bool hiddenAbility(void) const;
        void hiddenAbility(bool v);

        bool hyperTrain(Stat) const override { return false; }
        void hyperTrain(Stat, bool) override {}

        std::string nickname(void) const override;
        void nickname(const std::string_view& v) override;
        GameVersion version(void) const override;
        void version(GameVersion v) override;

        std::string otName(void) const override;
        void otName(const std::string_view& v) override;
        u16 eggLocation(void) const override;
        void eggLocation(u16 v) override;
        u16 metLocation(void) const override;
        void metLocation(u16 v) override;
        u8 pkrs(void) const override;
        void pkrs(u8 v) override;
        u8 pkrsDays(void) const override;
        void pkrsDays(u8 v) override;
        u8 pkrsStrain(void) const override;
        void pkrsStrain(u8 v) override;
        Ball ball(void) const override;
        void ball(Ball v) override;
        u8 metLevel(void) const override;
        void metLevel(u8 v) override;
        Gender otGender(void) const override;
        void otGender(Gender v) override;
        u8 encounterType(void) const;
        void encounterType(u8 v);
        u8 characteristic(void) const;

        void refreshChecksum(void) override;
        Type hpType(void) const override;
        void hpType(Type v) override;
        u16 TSV(void) const override;
        u16 PSV(void) const override;
        u8 level(void) const override;
        void level(u8 v) override;
        bool shiny(void) const override;
        void shiny(bool v) override;
        u16 formSpecies(void) const override;
        u16 stat(Stat stat) const override;

        int partyCurrHP(void) const override;
        void partyCurrHP(u16 v) override;
        int partyStat(Stat stat) const override;
        void partyStat(Stat stat, u16 v) override;
        int partyLevel() const override;
        void partyLevel(u8 v) override;
        void updatePartyData(void) override;

        inline u8 baseHP(void) const override { return PersonalDPPtHGSS::baseHP(formSpecies()); }
        inline u8 baseAtk(void) const override { return PersonalDPPtHGSS::baseAtk(formSpecies()); }
        inline u8 baseDef(void) const override { return PersonalDPPtHGSS::baseDef(formSpecies()); }
        inline u8 baseSpe(void) const override { return PersonalDPPtHGSS::baseSpe(formSpecies()); }
        inline u8 baseSpa(void) const override { return PersonalDPPtHGSS::baseSpa(formSpecies()); }
        inline u8 baseSpd(void) const override { return PersonalDPPtHGSS::baseSpd(formSpecies()); }
        inline Type type1(void) const override { return PersonalDPPtHGSS::type1(formSpecies()); }
        inline Type type2(void) const override { return PersonalDPPtHGSS::type2(formSpecies()); }
        inline u8 genderType(void) const override
        {
            return PersonalDPPtHGSS::gender(formSpecies());
        }
        inline u8 baseFriendship(void) const override
        {
            return PersonalDPPtHGSS::baseFriendship(formSpecies());
        }
        inline u8 expType(void) const override { return PersonalDPPtHGSS::expType(formSpecies()); }
        inline Ability abilities(u8 n) const override
        {
            return PersonalDPPtHGSS::ability(formSpecies(), n);
        }
        inline u16 formStatIndex(void) const override
        {
            return PersonalDPPtHGSS::formStatIndex(formSpecies());
        }
    };
}

#endif
