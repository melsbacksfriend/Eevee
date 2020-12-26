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

#ifndef I18N_HPP
#define I18N_HPP

#include "enums/Ability.hpp"
#include "enums/Ball.hpp"
#include "enums/GameVersion.hpp"
#include "enums/Generation.hpp"
#include "enums/Language.hpp"
#include "enums/Move.hpp"
#include "enums/Nature.hpp"
#include "enums/Ribbon.hpp"
#include "enums/Species.hpp"
#include "enums/Type.hpp"
#include "utils/coretypes.h"
#include <map>
#include <string>
#include <vector>

namespace i18n
{
    using initCallback = void (*)(pksm::Language);
    using exitCallback = void (*)(pksm::Language);
    void addInitCallback(initCallback callback);
    void removeInitCallback(initCallback callback);
    void addExitCallback(exitCallback callback);
    void removeExitCallback(exitCallback callback);

    inline void addCallbacks(initCallback init, exitCallback exit)
    {
        addInitCallback(init);
        addExitCallback(exit);
    }
    inline void removeCallbacks(initCallback init, exitCallback exit)
    {
        removeInitCallback(init);
        removeExitCallback(exit);
    }

    // Calls the callbacks that have been registered with addInitCallback in a thread-safe manner
    // NOTE: default callbacks include all init functions in this file
    void init(pksm::Language lang);
    // Calls the callbacks that have been registered with addExitCallback in a thread-safe manner
    // for all languages that have been initialized NOTE: default callbacks include all exit
    // functions in this file
    void exit(void);

    const std::string& langString(pksm::Language l);
    pksm::Language langFromString(const std::string_view& value);

    void initAbility(pksm::Language lang);
    void exitAbility(pksm::Language lang);
    const std::string& ability(pksm::Language lang, pksm::Ability value);
    const std::vector<std::string>& rawAbilities(pksm::Language lang);

    void initBall(pksm::Language lang);
    void exitBall(pksm::Language lang);
    const std::string& ball(pksm::Language lang, pksm::Ball value);
    const std::vector<std::string>& rawBalls(pksm::Language lang);

    void initForm(pksm::Language lang);
    void exitForm(pksm::Language lang);
    const std::string& form(
        pksm::Language lang, pksm::GameVersion version, pksm::Species species, u8 form);
    std::vector<std::string> forms(
        pksm::Language lang, pksm::GameVersion version, pksm::Species species);
    // No good raw interface for this

    void initGame(pksm::Language lang);
    void exitGame(pksm::Language lang);
    const std::string& game(pksm::Language lang, pksm::GameVersion value);
    const std::vector<std::string>& rawGames(pksm::Language lang);

    void initItem(pksm::Language lang);
    void exitItem(pksm::Language lang);
    const std::string& item(pksm::Language lang, u16 value);
    const std::vector<std::string>& rawItems(pksm::Language lang);

    void initItem3(pksm::Language lang);
    void exitItem3(pksm::Language lang);
    const std::string& item3(pksm::Language lang, u16 value);
    const std::vector<std::string>& rawItems3(pksm::Language lang);

    void initMove(pksm::Language lang);
    void exitMove(pksm::Language lang);
    const std::string& move(pksm::Language lang, pksm::Move value);
    const std::vector<std::string>& rawMoves(pksm::Language lang);

    void initNature(pksm::Language lang);
    void exitNature(pksm::Language lang);
    const std::string& nature(pksm::Language lang, pksm::Nature value);
    const std::vector<std::string>& rawNatures(pksm::Language lang);

    void initRibbon(pksm::Language lang);
    void exitRibbon(pksm::Language lang);
    const std::string& ribbon(pksm::Language lang, pksm::Ribbon value);
    const std::vector<std::string>& rawRibbons(pksm::Language lang);

    // Note: several functions require this to function properly.
    // A nonexhaustive list includes PK3::nicknamed, PK4::convertToPK3, PK5::convertToPK6,
    // SavLGPE::mysteryGift, and SavSWSH::mysteryGift
    void initSpecies(pksm::Language lang);
    void exitSpecies(pksm::Language lang);
    const std::string& species(pksm::Language lang, pksm::Species value);
    const std::vector<std::string>& rawSpecies(pksm::Language lang);

    void initType(pksm::Language lang);
    void exitType(pksm::Language lang);
    const std::string& type(pksm::Language lang, pksm::Type value);
    const std::vector<std::string>& rawType(pksm::Language lang);

    void initLocation(pksm::Language lang);
    void exitLocation(pksm::Language lang);
    const std::string& location(pksm::Language lang, pksm::Generation generation, u16 value);
    const std::map<u16, std::string>& rawLocations(pksm::Language lang, pksm::Generation g);

    void initGeo(pksm::Language lang);
    void exitGeo(pksm::Language lang);
    const std::string& subregion(pksm::Language lang, u8 country, u8 value);
    const std::map<u8, std::string>& rawSubregions(pksm::Language lang, u8 country);
    const std::string& country(pksm::Language lang, u8 value);
    const std::map<u8, std::string>& rawCountries(pksm::Language lang);
};

#endif
