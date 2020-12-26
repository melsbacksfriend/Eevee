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

#ifndef PKFILTER_HPP
#define PKFILTER_HPP

#include "enums/Ability.hpp"
#include "enums/Ball.hpp"
#include "enums/Gender.hpp"
#include "enums/Generation.hpp"
#include "enums/Language.hpp"
#include "enums/Move.hpp"
#include "enums/Nature.hpp"
#include "enums/Species.hpp"
#include "enums/Stat.hpp"
#include "pkx/IPKFilterable.hpp"
#include <bitset>
#include <string>
#include <vector>

#define MAKE_DEFN(name, type)                                                                      \
public:                                                                                            \
    type name(void) const override { return type##name; }                                          \
    void name(type v) override { type##name = v; }                                                 \
    bool name##Enabled(void) const { return name##Bool; }                                          \
    void name##Enabled(bool v) { name##Bool = v; }                                                 \
    bool name##Inversed(void) const { return name##Inverse; }                                      \
    void name##Inversed(bool v) { name##Inverse = v; }                                             \
                                                                                                   \
private:                                                                                           \
    type type##name    = type();                                                                   \
    bool name##Bool    = false;                                                                    \
    bool name##Inverse = false

#define MAKE_DEFN_CONSTANT(name, type)                                                             \
public:                                                                                            \
    type name(void) const override { return type##name; }                                          \
    void name(type v) { type##name = v; }                                                          \
    bool name##Enabled(void) const { return name##Bool; }                                          \
    void name##Enabled(bool v) { name##Bool = v; }                                                 \
    bool name##Inversed(void) const { return name##Inverse; }                                      \
    void name##Inversed(bool v) { name##Inverse = v; }                                             \
                                                                                                   \
private:                                                                                           \
    type type##name    = type();                                                                   \
    bool name##Bool    = false;                                                                    \
    bool name##Inverse = false

#define MAKE_NUM_DEFN(name, type, amount, indextype)                                               \
public:                                                                                            \
    type name(indextype which) const override { return type##name[size_t(which)]; }                \
    void name(indextype which, type v) override { type##name[size_t(which)] = v; }                 \
    bool name##Enabled(indextype which) const { return name##Bool[size_t(which)]; }                \
    void name##Enabled(indextype which, bool v) { name##Bool[size_t(which)] = v; }                 \
    bool name##Inversed(indextype which) const { return name##Inverse[size_t(which)]; }            \
    void name##Inversed(indextype which, bool v) { name##Inverse[size_t(which)] = v; }             \
                                                                                                   \
private:                                                                                           \
    std::vector<type> type##name      = std::vector<type>(amount, type());                         \
    std::bitset<amount> name##Bool    = std::bitset<amount>(0);                                    \
    std::bitset<amount> name##Inverse = std::bitset<amount>(0)

#define MAKE_NUM_DEFN_CONSTANT(name, type, amount, indextype)                                      \
public:                                                                                            \
    type name(indextype which) const override { return type##name[size_t(which)]; }                \
    void name(indextype which, type v) { type##name[size_t(which)] = v; }                          \
    bool name##Enabled(indextype which) const { return name##Bool[size_t(which)]; }                \
    void name##Enabled(indextype which, bool v) { name##Bool[size_t(which)] = v; }                 \
    bool name##Inversed(indextype which) const { return name##Inverse[size_t(which)]; }            \
    void name##Inversed(indextype which, bool v) { name##Inverse[size_t(which)] = v; }             \
                                                                                                   \
private:                                                                                           \
    std::vector<type> type##name      = std::vector<type>(amount, type());                         \
    std::bitset<amount> name##Bool    = std::bitset<amount>(0);                                    \
    std::bitset<amount> name##Inverse = std::bitset<amount>(0)

namespace pksm
{
    class PKFilter : public IPKFilterable
    {
    public:
        bool isFilter() const override { return true; }

        MAKE_DEFN_CONSTANT(generation, Generation);
        MAKE_DEFN(species, Species);
        MAKE_DEFN(alternativeForm, u16);
        MAKE_DEFN(shiny, bool);
        MAKE_DEFN(heldItem, u16);
        MAKE_DEFN(level, u8);
        MAKE_DEFN(ability, Ability);
        MAKE_DEFN_CONSTANT(TSV, u16);
        MAKE_DEFN(nature, Nature);
        MAKE_DEFN(gender, Gender);
        MAKE_NUM_DEFN(move, Move, 4, u8);
        MAKE_NUM_DEFN(relearnMove, Move, 4, u8);
        MAKE_DEFN(ball, Ball);
        MAKE_DEFN(language, Language);
        MAKE_DEFN(egg, bool);
        MAKE_NUM_DEFN(iv, u8, 6, Stat);
    };
}

#undef MAKE_DEFN
#undef MAKE_DEFN_CONSTANT
#undef MAKE_NUM_DEFN

#endif
