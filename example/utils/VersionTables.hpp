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

#ifndef VERSION_TABLES_HPP
#define VERSION_TABLES_HPP

#include "enums/Ability.hpp"
#include "enums/Ball.hpp"
#include "enums/GameVersion.hpp"
#include "enums/Generation.hpp"
#include "enums/Move.hpp"
#include "enums/Species.hpp"
#include <set>

namespace pksm::VersionTables
{
    const std::set<int>& availableItems(GameVersion version);
    const std::set<Move>& availableMoves(GameVersion version);
    const std::set<Species>& availableSpecies(GameVersion version);
    const std::set<Ability>& availableAbilities(GameVersion version);
    const std::set<Ball>& availableBalls(GameVersion version);

    // Not guaranteed to be useful
    int maxItem(GameVersion version);
    Move maxMove(GameVersion version);
    Species maxSpecies(GameVersion version);
    Ability maxAbility(GameVersion version);
    Ball maxBall(GameVersion version);

    // Takes version-specific forms into account
    u8 formCount(GameVersion version, Species species);

    u8 movePP(Generation gen, Move move, u8 ppUps);
}

#endif
