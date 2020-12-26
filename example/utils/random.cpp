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

#include "utils/random.hpp"
#include "utils/DateTime.hpp"
#include <random>

#ifndef _PKSMCORE_CONFIGURED
#include "PKSMCORE_CONFIG.h"
#endif

namespace
{
#ifdef _PKSMCORE_DISABLE_THREAD_SAFETY
    std::mt19937 randomNumbers;
    std::uniform_int_distribution<u32> distrib;
    bool seeded = false;
#else
    thread_local std::mt19937 randomNumbers;
    thread_local std::uniform_int_distribution<u32> distrib;
    thread_local bool seeded = false;
#endif
}

u32 pksm::randomNumber(u32 minInclusive, u32 maxInclusive)
{
    if (!seeded)
    {
        DateTime now      = DateTime::now();
        std::seed_seq seq = std::initializer_list<u32>{
            now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second()};
        seedRand(seq);
    }

    return distrib(
        randomNumbers, std::uniform_int_distribution<u32>::param_type{minInclusive, maxInclusive});
}

void pksm::seedRand(u32 seed)
{
    randomNumbers.seed(seed);
    seeded = true;
}

void pksm::seedRand(std::seed_seq& seed)
{
    randomNumbers.seed(seed);
    seeded = true;
}
