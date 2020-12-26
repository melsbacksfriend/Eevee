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

#ifndef IPKFILTERABLE_HPP
#define IPKFILTERABLE_HPP

#include "enums/Ability.hpp"
#include "enums/Ball.hpp"
#include "enums/Gender.hpp"
#include "enums/Generation.hpp"
#include "enums/Language.hpp"
#include "enums/Move.hpp"
#include "enums/Nature.hpp"
#include "enums/Species.hpp"
#include "enums/Stat.hpp"

#define IFILTERABLE_DEFINE_METHOD(name, type)                                                      \
    virtual type name() const = 0;                                                                 \
    virtual void name(type v) = 0
#define IFILTERABLE_DEFINE_CONSTANT_METHOD(name, type) virtual type name() const = 0
#define IFILTERABLE_DEFINE_INDEXED_METHOD(name, type, indextype)                                   \
    virtual type name(indextype which) const   = 0;                                                \
    virtual void name(indextype which, type v) = 0
#define IFILTERABLE_DEFINE_CONSTANT_INDEXED_METHOD(name, type, indextype)                          \
    virtual type name(indextype which) const = 0

namespace pksm
{
    class IPKFilterable
    {
    public:
        IFILTERABLE_DEFINE_CONSTANT_METHOD(isFilter, bool);

        IFILTERABLE_DEFINE_CONSTANT_METHOD(generation, Generation);
        IFILTERABLE_DEFINE_METHOD(species, Species);
        IFILTERABLE_DEFINE_METHOD(alternativeForm, u16);
        IFILTERABLE_DEFINE_METHOD(shiny, bool);
        IFILTERABLE_DEFINE_METHOD(heldItem, u16);
        IFILTERABLE_DEFINE_METHOD(level, u8);
        IFILTERABLE_DEFINE_METHOD(ability, Ability);
        IFILTERABLE_DEFINE_CONSTANT_METHOD(TSV, u16);
        IFILTERABLE_DEFINE_METHOD(nature, Nature);
        IFILTERABLE_DEFINE_METHOD(gender, Gender);
        IFILTERABLE_DEFINE_INDEXED_METHOD(move, Move, u8);
        IFILTERABLE_DEFINE_INDEXED_METHOD(relearnMove, Move, u8);
        IFILTERABLE_DEFINE_METHOD(ball, Ball);
        IFILTERABLE_DEFINE_METHOD(language, Language);
        IFILTERABLE_DEFINE_METHOD(egg, bool);
        IFILTERABLE_DEFINE_INDEXED_METHOD(iv, u8, Stat);
    };
}

#undef IFILTERABLE_DEFINE_METHOD
#undef IFILTERABLE_DEFINE_CONSTANT_METHOD
#undef IFILTERABLE_DEFINE_INDEXED_METHOD
#undef IFILTERABLE_DEFINE_CONSTANT_INDEXED_METHOD

#endif
