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

#include "sav/SavE.hpp"

namespace pksm
{
    SavE::SavE(std::shared_ptr<u8[]> dt) : Sav3(dt, {0x44, 0x988, 0xCA4})
    {
        game = Game::E;

        OFS_PCItem        = blockOfs[1] + 0x0498;
        OFS_PouchHeldItem = blockOfs[1] + 0x0560;
        OFS_PouchKeyItem  = blockOfs[1] + 0x05D8;
        OFS_PouchBalls    = blockOfs[1] + 0x0650;
        OFS_PouchTMHM     = blockOfs[1] + 0x0690;
        OFS_PouchBerry    = blockOfs[1] + 0x0790;
        eventFlag         = blockOfs[2] + 0x2F0;
        // EventConst = EventFlag + (EventFlagMax / 8);
        // DaycareOffset = blockOfs[4] + 0x1B0;
    }

    std::map<Sav::Pouch, std::vector<int>> SavE::validItems() const
    {
        std::map<Sav::Pouch, std::vector<int>> items = {
            {Pouch::NormalItem,
                {17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37,
                    38, 39, 40, 41, 42, 65, 66, 67, 68, 69, 43, 44, 70, 71, 72, 73, 74, 75, 45, 46,
                    47, 48, 49, 50, 51, 52, 53, 55, 56, 57, 58, 59, 60, 61, 63, 64, 76, 77, 78, 79,
                    80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 128, 128, 128, 128, 128,
                    128, 128, 128, 128, 128, 128, 128, 213, 214, 215, 216, 217, 218, 219, 220, 221,
                    222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237,
                    238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253,
                    254, 255, 256, 257, 258, 259, 260, 261, 262, 263, 264}},
            {Pouch::Ball, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}},
            {Pouch::KeyItem,
                {128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
                    128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128}},
            {Pouch::TM, {328, 329, 330, 331, 332, 333, 334, 335, 336, 337, 338, 339, 340, 341, 342,
                            343, 344, 345, 346, 347, 348, 349, 350, 351, 352, 353, 354, 355, 356,
                            357, 358, 359, 360, 361, 362, 363, 364, 365, 366, 367, 368, 369, 370,
                            371, 372, 373, 374, 375, 376, 377}},
            {Pouch::Berry,
                {149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164,
                    165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180,
                    181, 182, 183, 201, 202, 203, 204, 205, 206, 207, 208}},
            {Pouch::PCItem, {}},
        };

        // PC can hold any item
        items[Pouch::PCItem].insert(items[Pouch::PCItem].end(), items[Pouch::NormalItem].begin(),
            items[Pouch::NormalItem].end());
        items[Pouch::PCItem].insert(
            items[Pouch::PCItem].end(), items[Pouch::Ball].begin(), items[Pouch::Ball].end());
        items[Pouch::PCItem].insert(
            items[Pouch::PCItem].end(), items[Pouch::KeyItem].begin(), items[Pouch::KeyItem].end());
        items[Pouch::PCItem].insert(
            items[Pouch::PCItem].end(), items[Pouch::TM].begin(), items[Pouch::TM].end());
        items[Pouch::PCItem].insert(
            items[Pouch::PCItem].end(), items[Pouch::Berry].begin(), items[Pouch::Berry].end());

        return items;
    }

    std::map<Sav::Pouch, std::vector<int>> SavE::validItems3() const
    {
        std::map<Sav::Pouch, std::vector<int>> items = {
            {Pouch::NormalItem,
                {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33,
                    34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 63, 64,
                    65, 66, 67, 68, 69, 70, 71, 73, 74, 75, 76, 77, 78, 79, 80, 81, 83, 84, 85, 86,
                    93, 94, 95, 96, 97, 98, 103, 104, 106, 107, 108, 109, 110, 111, 121, 122, 123,
                    124, 125, 126, 127, 128, 129, 130, 131, 132, 179, 180, 181, 182, 183, 184, 185,
                    186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201,
                    202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217,
                    218, 219, 220, 221, 222, 223, 224, 225, 254, 255, 256, 257, 258}},
            {Pouch::Ball, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}},
            {Pouch::KeyItem,
                {259, 260, 261, 262, 263, 264, 265, 266, 268, 269, 270, 271, 272, 273, 274, 275,
                    276, 277, 278, 279, 280, 281, 282, 283, 284, 285, 286, 287, 288, 349, 350, 351,
                    352, 353, 354, 355, 356, 357, 358, 359, 360, 361, 362, 363, 364, 365, 366, 367,
                    368, 369, 370, 371, 372, 373, 374, 375, 376}},
            {Pouch::TM,
                {289, 290, 291, 292, 293, 294, 295, 296, 297, 298, 299, 300, 301, 302, 303, 304,
                    305, 306, 307, 308, 309, 310, 311, 312, 313, 314, 315, 316, 317, 318, 319, 320,
                    321, 322, 323, 324, 325, 326, 327, 328, 329, 330, 331, 332, 333, 334, 335, 336,
                    337, 338, 339, 340, 341, 342, 343, 344, 345, 346}},
            {Pouch::Berry,
                {133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148,
                    149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164,
                    165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175}},
            {Pouch::PCItem, {}}};

        // PC can hold any item
        items[Pouch::PCItem].insert(items[Pouch::PCItem].end(), items[Pouch::NormalItem].begin(),
            items[Pouch::NormalItem].end());
        items[Pouch::PCItem].insert(
            items[Pouch::PCItem].end(), items[Pouch::Ball].begin(), items[Pouch::Ball].end());
        items[Pouch::PCItem].insert(
            items[Pouch::PCItem].end(), items[Pouch::KeyItem].begin(), items[Pouch::KeyItem].end());
        items[Pouch::PCItem].insert(
            items[Pouch::PCItem].end(), items[Pouch::TM].begin(), items[Pouch::TM].end());
        items[Pouch::PCItem].insert(
            items[Pouch::PCItem].end(), items[Pouch::Berry].begin(), items[Pouch::Berry].end());

        return items;
    }
}
