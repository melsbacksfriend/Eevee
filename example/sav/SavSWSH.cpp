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

#include "sav/SavSWSH.hpp"
#include "pkx/PK8.hpp"
#include "utils/endian.hpp"
#include "utils/i18n.hpp"
#include "utils/random.hpp"
#include "utils/utils.hpp"
#include "wcx/WC8.hpp"
#include <algorithm>

namespace
{
    struct DexEntry
    {
        u64 seenNonShinyMale : 63;
        u64 seenNonShinyMaleGiga : 1;
        u64 seenNonShinyFemale : 63;
        u64 seenNonShinyFemaleGiga : 1;
        u64 seenShinyMale : 63;
        u64 seenShinyMaleGiga : 1;
        u64 seenShinyFemale : 63;
        u64 seenShinyFemaleGiga : 1;
        // Obtained info
        u32 owned : 1;
        u32 ownedGiga : 1;
        u32 languages : 13;     // flags
        u32 displayFormID : 13; // value
        u32 displayGiga : 1;
        u32 displayGender : 2;
        u32 displayShiny : 1;

        u32 battled : 32;
        u32 unk1 : 32;
        u32 unk2 : 32;
    };
    static_assert(sizeof(DexEntry) == 0x30);

    void setProperLocation(DexEntry& entry, u16 form, bool shiny, pksm::Gender gender)
    {
        if (gender == pksm::Gender::Female)
        {
            if (shiny)
            {
                entry.seenShinyFemale |= 1 << form;
            }
            else
            {
                entry.seenNonShinyFemale |= 1 << form;
            }
        }
        else
        {
            if (shiny)
            {
                entry.seenShinyMale |= 1 << form;
            }
            else
            {
                entry.seenNonShinyMale |= 1 << form;
            }
        }
    }

    void setProperGiga(DexEntry& entry, bool giga, bool shiny, pksm::Gender gender)
    {
        if (gender == pksm::Gender::Female)
        {
            if (shiny)
            {
                entry.seenShinyFemaleGiga = giga ? 1 : 0;
            }
            else
            {
                entry.seenNonShinyFemaleGiga = giga ? 1 : 0;
            }
        }
        else
        {
            if (shiny)
            {
                entry.seenShinyMaleGiga = giga ? 1 : 0;
            }
            else
            {
                entry.seenNonShinyMaleGiga = giga ? 1 : 0;
            }
        }
    }
}

template <>
#if __cplusplus > 201703L
constexpr DexEntry LittleEndian::convertTo<DexEntry>(const u8* data)
#else
DexEntry LittleEndian::convertTo<DexEntry>(const u8* data)
#endif
{
    DexEntry ret{};
    u64 v64                  = LittleEndian::convertTo<u64>(data);
    ret.seenNonShinyMale     = v64;
    ret.seenNonShinyMaleGiga = v64 >> 63;

    v64                        = LittleEndian::convertTo<u64>(data + 8);
    ret.seenNonShinyFemale     = v64;
    ret.seenNonShinyFemaleGiga = v64 >> 63;

    v64                   = LittleEndian::convertTo<u64>(data + 16);
    ret.seenShinyMale     = v64;
    ret.seenShinyMaleGiga = v64 >> 63;

    v64                     = LittleEndian::convertTo<u64>(data + 24);
    ret.seenShinyFemale     = v64;
    ret.seenShinyFemaleGiga = v64 >> 63;

    u32 v32           = LittleEndian::convertTo<u32>(data + 32);
    ret.owned         = v32 & 1;
    ret.ownedGiga     = (v32 >> 1) & 1;
    ret.languages     = (v32 >> 2) & 0x1FFF;
    ret.displayFormID = (v32 >> 15) & 0x1FFF;
    ret.displayGiga   = (v32 >> 28) & 1;
    ret.displayGender = (v32 >> 29) & 3;
    ret.displayShiny  = v32 >> 31;

    ret.battled = LittleEndian::convertTo<u32>(data + 36);
    ret.unk1    = LittleEndian::convertTo<u32>(data + 40);
    ret.unk2    = LittleEndian::convertTo<u32>(data + 44);

    return ret;
}

template <>
#if __cplusplus > 201703L
constexpr void LittleEndian::convertFrom<DexEntry>(u8* data, const DexEntry& entry)
#else
void LittleEndian::convertFrom<DexEntry>(u8* data, const DexEntry& entry)
#endif
{
    u64 w64 = entry.seenNonShinyMale | (u64(entry.seenNonShinyMaleGiga) << 63);
    LittleEndian::convertFrom<u64>(data, w64);

    w64 = entry.seenNonShinyFemale | (u64(entry.seenNonShinyFemaleGiga) << 63);
    LittleEndian::convertFrom<u64>(data + 8, w64);

    w64 = entry.seenShinyMale | (u64(entry.seenShinyMaleGiga) << 63);
    LittleEndian::convertFrom<u64>(data + 16, w64);

    w64 = entry.seenShinyFemale | (u64(entry.seenShinyFemaleGiga) << 63);
    LittleEndian::convertFrom<u64>(data + 24, w64);

    u32 w32 = entry.owned | (entry.ownedGiga << 1) | (entry.languages << 2) |
              (entry.displayFormID << 15) | (entry.displayGiga << 28) |
              (entry.displayGender << 29) | (entry.displayShiny << 31);
    LittleEndian::convertFrom<u32>(data + 32, w32);

    LittleEndian::convertFrom<u32>(data + 36, entry.battled);
    LittleEndian::convertFrom<u32>(data + 40, entry.unk1);
    LittleEndian::convertFrom<u32>(data + 44, entry.unk2);
}

namespace pksm
{
    SavSWSH::SavSWSH(std::shared_ptr<u8[]> dt, size_t length) : Sav8(dt, length)
    {
        game = Game::SWSH;

        Box            = 0x0d66012c;
        WondercardData = 0x112d5141;
        Party          = 0x2985fe5d;
        PokeDex        = 0x4716c404;
        ArmorDex       = 0x3F936BA9;
        CrownDex       = 0x3C9366F0;
        Items          = 0x1177c2c4;
        BoxLayout      = 0x19722c89;
        Misc           = 0x1b882b09;
        TrainerCard    = 0x874da6fa;
        PlayTime       = 0x8cbbfd90;
        Status         = 0xf25c070e;
    }

    u16 SavSWSH::TID(void) const
    {
        return LittleEndian::convertTo<u16>(getBlock(Status)->decryptedData() + 0xA0);
    }
    void SavSWSH::TID(u16 v)
    {
        LittleEndian::convertFrom<u16>(getBlock(Status)->decryptedData() + 0xA0, v);
        LittleEndian::convertFrom<u32>(getBlock(TrainerCard)->decryptedData() + 0x1C, displayTID());
    }

    u16 SavSWSH::SID(void) const
    {
        return LittleEndian::convertTo<u16>(getBlock(Status)->decryptedData() + 0xA2);
    }
    void SavSWSH::SID(u16 v)
    {
        LittleEndian::convertFrom<u16>(getBlock(Status)->decryptedData() + 0xA2, v);
        LittleEndian::convertFrom<u32>(getBlock(TrainerCard)->decryptedData() + 0x1C, displayTID());
    }

    GameVersion SavSWSH::version(void) const
    {
        return GameVersion(getBlock(Status)->decryptedData()[0xA4]);
    }
    void SavSWSH::version(GameVersion v) { getBlock(Status)->decryptedData()[0xA4] = u8(v); }

    Gender SavSWSH::gender(void) const { return Gender{getBlock(Status)->decryptedData()[0xA5]}; }
    void SavSWSH::gender(Gender v) { getBlock(Status)->decryptedData()[0xA5] = u8(v); }

    Language SavSWSH::language(void) const
    {
        return Language(getBlock(Status)->decryptedData()[0xA7]);
    }
    void SavSWSH::language(Language v) { getBlock(Status)->decryptedData()[0xA7] = u8(v); }

    std::string SavSWSH::otName(void) const
    {
        return StringUtils::getString(getBlock(Status)->decryptedData(), 0xB0, 13);
    }
    void SavSWSH::otName(const std::string_view& v)
    {
        StringUtils::setString(getBlock(Status)->decryptedData(), v, 0xB0, 13);
        StringUtils::setString(getBlock(TrainerCard)->decryptedData(), v, 0, 13);
    }

    std::string SavSWSH::jerseyNum(void) const
    {
        return std::string((char*)getBlock(TrainerCard)->decryptedData() + 0x39, 3);
    }
    void SavSWSH::jerseyNum(const std::string_view& v)
    {
        for (size_t i = 0; i < std::min(v.size(), (size_t)3); i++)
        {
            getBlock(TrainerCard)->decryptedData()[0x39 + i] = v[i];
        }
    }

    u32 SavSWSH::money(void) const
    {
        return LittleEndian::convertTo<u32>(getBlock(Misc)->decryptedData());
    }
    void SavSWSH::money(u32 v)
    {
        LittleEndian::convertFrom<u32>(getBlock(Misc)->decryptedData(), v);
    }

    u32 SavSWSH::BP(void) const
    {
        return LittleEndian::convertTo<u32>(getBlock(Misc)->decryptedData() + 4);
    }
    void SavSWSH::BP(u32 v)
    {
        LittleEndian::convertFrom<u32>(getBlock(Misc)->decryptedData() + 4, v);
    }

    u8 SavSWSH::badges(void) const { return getBlock(Misc)->decryptedData()[0x11C]; }

    u16 SavSWSH::playedHours(void) const
    {
        return LittleEndian::convertTo<u16>(getBlock(PlayTime)->decryptedData());
    }
    void SavSWSH::playedHours(u16 v)
    {
        LittleEndian::convertFrom<u16>(getBlock(PlayTime)->decryptedData(), v);
    }

    u8 SavSWSH::playedMinutes(void) const { return getBlock(PlayTime)->decryptedData()[2]; }
    void SavSWSH::playedMinutes(u8 v) { getBlock(PlayTime)->decryptedData()[2] = v; }

    u8 SavSWSH::playedSeconds(void) const { return getBlock(PlayTime)->decryptedData()[3]; }
    void SavSWSH::playedSeconds(u8 v) { getBlock(PlayTime)->decryptedData()[3] = v; }

    void SavSWSH::item(const Item& item, Pouch pouch, u16 slot)
    {
        Item8 item8 = static_cast<Item8>(item);
        auto write  = item.bytes();
        switch (pouch)
        {
            case Pouch::Medicine:
                std::copy(write.begin(), write.end(), getBlock(Items)->decryptedData() + 4 * slot);
                break;
            case Pouch::Ball:
                std::copy(
                    write.begin(), write.end(), getBlock(Items)->decryptedData() + 0xF0 + 4 * slot);
                break;
            case Pouch::Battle:
                std::copy(write.begin(), write.end(),
                    getBlock(Items)->decryptedData() + 0x168 + 4 * slot);
                break;
            case Pouch::Berry:
                std::copy(write.begin(), write.end(),
                    getBlock(Items)->decryptedData() + 0x1B8 + 4 * slot);
                break;
            case Pouch::NormalItem:
                std::copy(write.begin(), write.end(),
                    getBlock(Items)->decryptedData() + 0x2F8 + 4 * slot);
                break;
            case Pouch::TM:
                std::copy(write.begin(), write.end(),
                    getBlock(Items)->decryptedData() + 0xB90 + 4 * slot);
                break;
            case Pouch::Treasure:
                std::copy(write.begin(), write.end(),
                    getBlock(Items)->decryptedData() + 0xED8 + 4 * slot);
                break;
            case Pouch::Ingredient:
                std::copy(write.begin(), write.end(),
                    getBlock(Items)->decryptedData() + 0x1068 + 4 * slot);
                break;
            case Pouch::KeyItem:
                std::copy(write.begin(), write.end(),
                    getBlock(Items)->decryptedData() + 0x11F8 + 4 * slot);
                break;
            default:
                break;
        }
    }
    std::unique_ptr<Item> SavSWSH::item(Pouch pouch, u16 slot) const
    {
        switch (pouch)
        {
            case Pouch::Medicine:
                return std::make_unique<Item8>(getBlock(Items)->decryptedData() + 4 * slot);
            case Pouch::Ball:
                return std::make_unique<Item8>(getBlock(Items)->decryptedData() + 0xF0 + 4 * slot);
            case Pouch::Battle:
                return std::make_unique<Item8>(getBlock(Items)->decryptedData() + 0x168 + 4 * slot);
            case Pouch::Berry:
                return std::make_unique<Item8>(getBlock(Items)->decryptedData() + 0x1B8 + 4 * slot);
            case Pouch::NormalItem:
                return std::make_unique<Item8>(getBlock(Items)->decryptedData() + 0x2F8 + 4 * slot);
            case Pouch::TM:
                return std::make_unique<Item8>(getBlock(Items)->decryptedData() + 0xB90 + 4 * slot);
            case Pouch::Treasure:
                return std::make_unique<Item8>(getBlock(Items)->decryptedData() + 0xED8 + 4 * slot);
            case Pouch::Ingredient:
                return std::make_unique<Item8>(
                    getBlock(Items)->decryptedData() + 0x1068 + 4 * slot);
            case Pouch::KeyItem:
                return std::make_unique<Item8>(
                    getBlock(Items)->decryptedData() + 0x11F8 + 4 * slot);
            default:
                return std::make_unique<Item8>();
        }
    }
    std::vector<std::pair<Sav::Pouch, int>> SavSWSH::pouches(void) const
    {
        return {{Pouch::Medicine, 60}, {Pouch::Ball, 30}, {Pouch::Battle, 20}, {Pouch::Berry, 80},
            {Pouch::NormalItem, 550}, {Pouch::TM, 210}, {Pouch::Treasure, 100},
            {Pouch::Ingredient, 100}, {Pouch::KeyItem, 64}};
    }
    std::map<Sav::Pouch, std::vector<int>> SavSWSH::validItems(void) const
    {
        return {{Pouch::Medicine,
                    {17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36,
                        37, 38, 39, 40, 41, 42, 43, 54, 134, 54, 591, 708, 709, 852, 903}},
            {Pouch::Ball, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 492, 493, 494,
                              495, 496, 497, 498, 499, 500, 576, 851}},
            {Pouch::Battle, {55, 56, 57, 58, 59, 60, 61, 62, 63, 1580}},
            {Pouch::Berry, {149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162,
                               163, 169, 170, 171, 172, 173, 174, 184, 185, 186, 187, 188, 189, 190,
                               191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204,
                               205, 206, 207, 208, 209, 210, 211, 212, 686, 687, 688}},
            {Pouch::NormalItem,
                {45, 46, 47, 48, 49, 50, 51, 52, 53, 76, 77, 79, 80, 81, 82, 83, 84, 85, 107, 108,
                    109, 110, 112, 116, 117, 118, 119, 135, 136, 213, 214, 215, 217, 218, 219, 220,
                    221, 222, 223, 224, 225, 228, 234, 236, 237, 238, 239, 240, 241, 242, 243, 244,
                    245, 246, 247, 248, 249, 250, 251, 253, 254, 255, 257, 229, 230, 231, 232, 233,
                    234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249,
                    259, 265, 266, 267, 268, 269, 270, 271, 272, 273, 274, 275, 276, 277, 278, 279,
                    280, 281, 282, 283, 284, 250, 251, 252, 253, 254, 255, 257, 258, 259, 265, 266,
                    267, 268, 269, 270, 271, 272, 273, 274, 275, 276, 285, 286, 287, 288, 289, 290,
                    291, 292, 293, 294, 295, 296, 297, 298, 299, 300, 301, 302, 303, 304, 305, 277,
                    278, 279, 280, 281, 282, 283, 284, 285, 286, 287, 288, 289, 290, 291, 292, 293,
                    294, 295, 296, 297, 306, 307, 308, 309, 310, 311, 312, 313, 314, 315, 316, 317,
                    318, 319, 320, 321, 325, 326, 537, 538, 539, 298, 299, 300, 301, 302, 303, 304,
                    305, 306, 307, 308, 309, 310, 311, 312, 313, 314, 315, 316, 317, 318, 540, 541,
                    542, 543, 544, 545, 546, 547, 564, 565, 566, 567, 568, 569, 570, 639, 640, 644,
                    645, 646, 647, 319, 320, 321, 322, 323, 324, 325, 326, 485, 486, 487, 488, 489,
                    490, 491, 537, 538, 539, 540, 541, 542, 648, 649, 650, 846, 849, 879, 880, 881,
                    882, 883, 884, 904, 905, 906, 907, 908, 909, 910, 911, 912, 913, 543, 544, 545,
                    546, 547, 564, 565, 566, 567, 568, 569, 570, 639, 640, 644, 645, 646, 647, 648,
                    649, 650, 914, 915, 916, 917, 918, 919, 920, 1103, 1104, 1109, 1110, 1111, 1112,
                    1113, 1114, 1115, 1116, 1117, 1118, 846, 849, 879, 880, 881, 882, 883, 884, 904,
                    905, 906, 907, 908, 909, 910, 911, 912, 913, 914, 915, 916, 1119, 1120, 1121,
                    1122, 1123, 1124, 1125, 1126, 1127, 1128, 1129, 1231, 1232, 1233, 1234, 1235,
                    1236, 1237, 917, 918, 919, 920, 1103, 1104, 1109, 1110, 1111, 1112, 1113, 1114,
                    1115, 1116, 1117, 1118, 1119, 1120, 1238, 1239, 1240, 1241, 1242, 1243, 1244,
                    1245, 1246, 1247, 1248, 1249, 1250, 1251, 1252, 1253, 1254, 1121, 1122, 1123,
                    1124, 1125, 1126, 1127, 1128, 1129, 1231, 1232, 1233, 1234, 1235, 1236, 1237,
                    1238, 1239, 1240, 1241, 1242, 1243, 1244, 1245, 1246, 1247, 1248, 1249, 1250,
                    1251, 1252, 1253, 1254, 1279, 1280, 1281, 1282, 1283, 1284, 1285, 1286, 1287,
                    1288, 1289, 1290, 1291, 1292, 1293, 1294, 1295, 1296, 1297, 1298, 1299, 1300,
                    1301, 1302, 1303, 1304, 1305, 1306, 1307, 1308, 1309, 1310, 1311, 1312, 1313,
                    1314, 1315, 1316, 1317, 1318, 1319, 1320, 1321, 1322, 1323, 1324, 1325, 1326,
                    1327, 1328, 1329, 1330, 1331, 1332, 1333, 1334, 1335, 1336, 1337, 1338, 1339,
                    1340, 1341, 1342, 1343, 1344, 1345, 1346, 1347, 1348, 1349, 1350, 1351, 1352,
                    1353, 1354, 1355, 1356, 1357, 1358, 1359, 1360, 1361, 1362, 1363, 1364, 1365,
                    1366, 1367, 1368, 1369, 1370, 1371, 1372, 1373, 1374, 1375, 1376, 1377, 1378,
                    1379, 1380, 1381, 1382, 1383, 1384, 1385, 1386, 1387, 1388, 1389, 1390, 1391,
                    1392, 1393, 1394, 1395, 1396, 1397, 1398, 1399, 1400, 1401, 1402, 1403, 1404,
                    1405, 1406, 1407, 1408, 1409, 1410, 1411, 1412, 1413, 1414, 1415, 1416, 1417,
                    1418, 1419, 1420, 1421, 1422, 1423, 1424, 1425, 1426, 1427, 1428, 1429, 1430,
                    1431, 1432, 1433, 1434, 1435, 1436, 1437, 1438, 1439, 1440, 1441, 1442, 1443,
                    1444, 1445, 1446, 1447, 1448, 1449, 1450, 1451, 1452, 1453, 1454, 1455, 1456,
                    1457, 1458, 1459, 1460, 1461, 1462, 1463, 1464, 1465, 1466, 1467, 1468, 1469,
                    1470, 1471, 1472, 1473, 1474, 1475, 1476, 1477, 1478, 1479, 1480, 1481, 1482,
                    1483, 1484, 1485, 1486, 1487, 1488, 1489, 1490, 1491, 1492, 1493, 1494, 1495,
                    1496, 1497, 1498, 1499, 1500, 1501, 1502, 1503, 1504, 1505, 1506, 1507, 1508,
                    1509, 1510, 1511, 1512, 1513, 1514, 1515, 1516, 1517, 1518, 1519, 1520, 1521,
                    1522, 1523, 1524, 1525, 1526, 1527, 1528, 1529, 1530, 1531, 1532, 1533, 1534,
                    1535, 1536, 1537, 1538, 1539, 1540, 1541, 1542, 1543, 1544, 1545, 1546, 1547,
                    1548, 1549, 1550, 1551, 1552, 1553, 1554, 1555, 1556, 1557, 1558, 1559, 1560,
                    1561, 1562, 1563, 1564, 1565, 1566, 1567, 1568, 1569, 1570, 1571, 1572, 1573,
                    1574, 1575, 1576, 1577, 1578, 1581, 1582, 1588}},
            {Pouch::TM,
                {328, 329, 330, 331, 332, 333, 334, 335, 336, 337, 338, 339, 340, 341, 342, 343,
                    344, 345, 346, 347, 348, 349, 350, 351, 352, 353, 354, 355, 356, 357, 358, 359,
                    360, 361, 362, 363, 364, 365, 366, 367, 368, 369, 370, 371, 372, 373, 374, 375,
                    376, 377, 378, 379, 380, 381, 382, 383, 384, 385, 386, 387, 388, 389, 390, 391,
                    392, 393, 394, 395, 396, 397, 398, 399, 400, 401, 402, 403, 404, 405, 406, 407,
                    408, 409, 410, 411, 412, 413, 414, 415, 416, 417, 418, 419, 618, 619, 620, 690,
                    691, 692, 693, 1230, 1130, 1131, 1132, 1133, 1134, 1135, 1136, 1137, 1138, 1139,
                    1140, 1141, 1142, 1143, 1144, 1145, 1146, 1147, 1148, 1149, 1150, 1151, 1152,
                    1153, 1154, 1155, 1156, 1157, 1158, 1159, 1160, 1161, 1162, 1163, 1164, 1165,
                    1166, 1167, 1168, 1169, 1170, 1171, 1172, 1173, 1174, 1175, 1176, 1177, 1178,
                    1179, 1180, 1181, 1182, 1183, 1184, 1185, 1186, 1187, 1188, 1189, 1190, 1191,
                    1192, 1193, 1194, 1195, 1196, 1197, 1198, 1199, 1200, 1201, 1202, 1203, 1204,
                    1205, 1206, 1207, 1208, 1209, 1210, 1211, 1212, 1213, 1214, 1215, 1216, 1217,
                    1218, 1219, 1220, 1221, 1222, 1223, 1224, 1225, 1226, 1227, 1228, 1229, 1579}},
            {Pouch::Treasure, {86, 87, 88, 89, 90, 91, 92, 94, 106, 571, 580, 581, 582, 583, 795,
                                  796, 1105, 1106, 1107, 1108}},
            {Pouch::Ingredient,
                {1084, 1085, 1086, 1087, 1088, 1089, 1090, 1091, 1092, 1093, 1094, 1095, 1096, 1097,
                    1098, 1099, 1256, 1257, 1258, 1259, 1260, 1261, 1262, 1263, 1264}},
            {Pouch::KeyItem,
                {78, 628, 629, 631, 632, 628, 629, 631, 632, 638, 703, 703, 847, 943, 944, 945, 946,
                    943, 944, 945, 946, 1074, 1075, 1076, 1077, 1080, 1081, 1100, 1074, 1075, 1076,
                    1077, 1080, 1081, 1100, 1255, 1266, 1267, 1255, 1266, 1267, 1269, 1270, 1271,
                    1278, 1269, 1270, 1271, 1278, 1583, 1584, 1585, 1586, 1587, 1589}}};
    }

    u8 SavSWSH::currentBox() const
    {
        return LittleEndian::convertTo<u32>(getBlock(0x017C3CBB)->decryptedData());
    }
    void SavSWSH::currentBox(u8 box)
    {
        LittleEndian::convertFrom<u32>(getBlock(0x017C3CBB)->decryptedData(), box);
    }

    std::string SavSWSH::boxName(u8 box) const
    {
        return StringUtils::getString(getBlock(BoxLayout)->decryptedData(), box * 0x22, 17);
    }
    void SavSWSH::boxName(u8 box, const std::string_view& name)
    {
        StringUtils::setString(getBlock(BoxLayout)->decryptedData(), name, box * 0x22, 17);
    }

    u8 SavSWSH::boxWallpaper(u8 box) const
    {
        return LittleEndian::convertTo<u32>(getBlock(0x017C3CBB)->decryptedData() + box * 4);
    }
    void SavSWSH::boxWallpaper(u8 box, u8 v)
    {
        LittleEndian::convertFrom<u32>(getBlock(0x2EB1B190)->decryptedData() + box * 4, v);
    }

    u32 SavSWSH::boxOffset(u8 box, u8 slot) const
    {
        return PK8::PARTY_LENGTH * slot + PK8::PARTY_LENGTH * 30 * box;
    }
    u32 SavSWSH::partyOffset(u8 slot) const { return PK8::PARTY_LENGTH * slot; }

    u8 SavSWSH::partyCount(void) const
    {
        return getBlock(Party)->decryptedData()[PK8::PARTY_LENGTH * 6];
    }
    void SavSWSH::partyCount(u8 count)
    {
        getBlock(Party)->decryptedData()[PK8::PARTY_LENGTH * 6] = count;
    }

    std::unique_ptr<PKX> SavSWSH::pkm(u8 slot) const
    {
        u32 offset = partyOffset(slot);
        return PKX::getPKM<Generation::EIGHT>(getBlock(Party)->decryptedData() + offset, true);
    }
    std::unique_ptr<PKX> SavSWSH::pkm(u8 box, u8 slot) const
    {
        u32 offset = boxOffset(box, slot);
        return PKX::getPKM<Generation::EIGHT>(getBlock(Box)->decryptedData() + offset, true);
    }

    void SavSWSH::pkm(const PKX& pk, u8 box, u8 slot, bool applyTrade)
    {
        if (pk.generation() == Generation::EIGHT)
        {
            auto pk8 = pk.partyClone();
            if (applyTrade)
            {
                trade(*pk8);
            }

            std::copy(pk8->rawData(), pk8->rawData() + pk8->getLength(),
                getBlock(Box)->decryptedData() + boxOffset(box, slot));
        }
    }
    void SavSWSH::pkm(const PKX& pk, u8 slot)
    {
        if (pk.generation() == Generation::EIGHT)
        {
            auto pk8 = pk.partyClone();
            pk8->encrypt();
            std::copy(pk8->rawData(), pk8->rawData() + pk8->getLength(),
                getBlock(Party)->decryptedData() + partyOffset(slot));
        }
    }

    void SavSWSH::cryptBoxData(bool crypted)
    {
        for (u8 box = 0; box < maxBoxes(); box++)
        {
            for (u8 slot = 0; slot < 30; slot++)
            {
                std::unique_ptr<PKX> pk8 = PKX::getPKM<Generation::EIGHT>(
                    getBlock(Box)->decryptedData() + boxOffset(box, slot), true, true);
                if (!crypted)
                {
                    pk8->encrypt();
                }
            }
        }
    }

    void SavSWSH::mysteryGift(const WCX& wc, int&)
    {
        if (wc.generation() == Generation::EIGHT)
        {
            const WC8& wc8 = reinterpret_cast<const WC8&>(wc);
            if (wc8.pokemon())
            {
                int injectPosition = 0;
                for (injectPosition = 0; injectPosition < maxSlot(); injectPosition++)
                {
                    if (pkm(injectPosition / 30, injectPosition % 30)->species() == Species::None)
                    {
                        break;
                    }
                }

                // No place to put generated PK8!
                if (injectPosition == maxSlot())
                {
                    return;
                }

                auto pk8 = PKX::getPKM<Generation::EIGHT>(nullptr, false);

                pk8->encryptionConstant(wc8.encryptionConstant()
                                            ? wc8.encryptionConstant()
                                            : pksm::randomNumber(0, 0xFFFFFFFF));
                pk8->TID(wc8.TID());
                pk8->SID(wc8.SID());
                pk8->species(wc8.species());
                pk8->alternativeForm(wc8.alternativeForm());
                pk8->level(wc8.level() ? wc8.level() : pksm::randomNumber(1, 100));
                pk8->ball(wc8.ball() ? wc8.ball() : Ball::Poke);
                pk8->metLevel(wc8.metLevel() ? wc8.metLevel() : pk8->level());
                pk8->heldItem(wc8.heldItem());

                for (size_t move = 0; move < 4; move++)
                {
                    pk8->move(move, wc8.move(move));
                    pk8->relearnMove(move, wc8.relearnMove(move));
                }

                pk8->version(wc8.version() != GameVersion::INVALID ? wc8.version() : version());

                std::string wcOT = wc8.otName(language());
                if (wcOT.empty())
                {
                    pk8->otName(otName());
                    pk8->otGender(gender());
                }
                else
                {
                    pk8->otName(wcOT);
                    pk8->otGender(wc8.otGender() < Gender::Genderless ? wc8.otGender() : gender());
                    pk8->htName(otName());
                    pk8->htGender(gender());
                    pk8->htLanguage(language());
                    pk8->currentHandler(1);
                }

                pk8->otIntensity(wc8.otIntensity());
                pk8->otMemory(wc8.otMemory());
                pk8->otTextVar(wc8.otTextvar());
                pk8->otFeeling(wc8.otFeeling());
                pk8->fatefulEncounter(true);

                for (Stat stat :
                    {Stat::HP, Stat::ATK, Stat::DEF, Stat::SPD, Stat::SPATK, Stat::SPDEF})
                {
                    pk8->ev(stat, wc8.ev(stat));
                }

                pk8->canGiga(wc8.canGigantamax());
                pk8->dynamaxLevel(wc8.dynamaxLevel());

                pk8->metLocation(wc8.metLocation());
                pk8->eggLocation(wc8.eggLocation());

                if (wc8.otGender() >= Gender::Genderless)
                {
                    pk8->TID(TID());
                    pk8->SID(SID());
                }

                if (pk8->species() == Species::Meowstic)
                {
                    pk8->alternativeForm(u8(pk8->gender()));
                }

                pk8->metDate(Date::today());

                Language nickLang = wc8.nicknameLanguage(language());
                if (nickLang != Language(0))
                {
                    pk8->language(nickLang);
                }
                else
                {
                    pk8->language(language());
                }

                pk8->nicknamed(wc8.nicknamed(pk8->language()));
                pk8->nickname(pk8->nicknamed() ? wc8.nickname(pk8->language())
                                               : pk8->species().localize(pk8->language()));

                constexpr std::array<Ribbon, 98> RIBBONS_TO_TRANSFER = {Ribbon::ChampionKalos,
                    Ribbon::ChampionG3Hoenn, Ribbon::ChampionSinnoh, Ribbon::BestFriends,
                    Ribbon::Training, Ribbon::BattlerSkillful, Ribbon::BattlerExpert,
                    Ribbon::Effort, Ribbon::Alert, Ribbon::Shock, Ribbon::Downcast,
                    Ribbon::Careless, Ribbon::Relax, Ribbon::Snooze, Ribbon::Smile,
                    Ribbon::Gorgeous, Ribbon::Royal, Ribbon::GorgeousRoyal, Ribbon::Artist,
                    Ribbon::Footprint, Ribbon::Record, Ribbon::Legend, Ribbon::Country,
                    Ribbon::National, Ribbon::Earth, Ribbon::World, Ribbon::Classic,
                    Ribbon::Premier, Ribbon::Event, Ribbon::Birthday, Ribbon::Special,
                    Ribbon::Souvenir, Ribbon::Wishing, Ribbon::ChampionBattle,
                    Ribbon::ChampionRegional, Ribbon::ChampionNational, Ribbon::ChampionWorld,
                    Ribbon::MemoryContest, Ribbon::MemoryBattle, Ribbon::ChampionG6Hoenn,
                    Ribbon::ContestStar, Ribbon::MasterCoolness, Ribbon::MasterBeauty,
                    Ribbon::MasterCuteness, Ribbon::MasterCleverness, Ribbon::MasterToughness,
                    Ribbon::ChampionAlola, Ribbon::BattleRoyale, Ribbon::BattleTreeGreat,
                    Ribbon::BattleTreeMaster, Ribbon::ChampionGalar, Ribbon::TowerMaster,
                    Ribbon::MasterRank, Ribbon::MarkLunchtime, Ribbon::MarkSleepyTime,
                    Ribbon::MarkDusk, Ribbon::MarkDawn, Ribbon::MarkCloudy, Ribbon::MarkRainy,
                    Ribbon::MarkStormy, Ribbon::MarkSnowy, Ribbon::MarkBlizzard, Ribbon::MarkDry,
                    Ribbon::MarkSandstorm, Ribbon::MarkMisty, Ribbon::MarkDestiny,
                    Ribbon::MarkFishing, Ribbon::MarkCurry, Ribbon::MarkUncommon, Ribbon::MarkRare,
                    Ribbon::MarkRowdy, Ribbon::MarkAbsentMinded, Ribbon::MarkJittery,
                    Ribbon::MarkExcited, Ribbon::MarkCharismatic, Ribbon::MarkCalmness,
                    Ribbon::MarkIntense, Ribbon::MarkZonedOut, Ribbon::MarkJoyful,
                    Ribbon::MarkAngry, Ribbon::MarkSmiley, Ribbon::MarkTeary, Ribbon::MarkUpbeat,
                    Ribbon::MarkPeeved, Ribbon::MarkIntellectual, Ribbon::MarkFerocious,
                    Ribbon::MarkCrafty, Ribbon::MarkScowling, Ribbon::MarkKindly,
                    Ribbon::MarkFlustered, Ribbon::MarkPumpedUp, Ribbon::MarkZeroEnergy,
                    Ribbon::MarkPrideful, Ribbon::MarkUnsure, Ribbon::MarkHumble,
                    Ribbon::MarkThorny, Ribbon::MarkVigor, Ribbon::MarkSlump};

                for (Ribbon ribbon : RIBBONS_TO_TRANSFER)
                {
                    pk8->ribbon(ribbon, wc8.ribbon(ribbon));
                }

                if (wc8.egg())
                {
                    pk8->eggDate(Date::today());
                    pk8->nickname(i18n::species(pk8->language(), Species::None));
                    pk8->nicknamed(true);
                }

                pk8->currentFriendship(pk8->baseFriendship());

                pk8->height(pksm::randomNumber(0, 0x80) + pksm::randomNumber(0, 0x7F));
                pk8->weight(pksm::randomNumber(0, 0x80) + pksm::randomNumber(0, 0x7F));

                pk8->nature(wc8.nature() == Nature::INVALID ? Nature{u8(pksm::randomNumber(0, 24))}
                                                            : wc8.nature());
                pk8->origNature(pk8->nature());
                pk8->gender(
                    PKX::genderFromRatio(pksm::randomNumber(0, 0xFFFFFFFF), pk8->genderType()));

                // Ability
                switch (wc8.abilityType())
                {
                    case 0:
                    case 1:
                    case 2:
                        pk8->setAbility(wc8.abilityType());
                        break;
                    case 3:
                    case 4:
                        pk8->setAbility(pksm::randomNumber(0, wc8.abilityType() - 2));
                        break;
                }

                // PID
                switch (wc8.PIDType())
                {
                    case 0: // Fixed value
                        pk8->PID(wc8.PID());
                        break;
                    case 1: // Random
                        pk8->PID(pksm::randomNumber(0, 0xFFFFFFFF));
                        break;
                    case 5: // Always star shiny
                        pk8->PID(pksm::randomNumber(0, 0xFFFFFFFF));
                        pk8->PID(((pk8->TID() ^ pk8->SID() ^ (pk8->PID() & 0xFFFF) ^ 1) << 16) |
                                 (pk8->PID() & 0xFFFF));
                        break;
                    case 6: // Always square shiny
                        pk8->PID(pksm::randomNumber(0, 0xFFFFFFFF));
                        pk8->PID(((pk8->TID() ^ pk8->SID() ^ (pk8->PID() & 0xFFFF) ^ 0) << 16) |
                                 (pk8->PID() & 0xFFFF));
                        break;
                    case 3: // Never shiny
                        pk8->PID(pksm::randomNumber(0, 0xFFFFFFFF));
                        pk8->shiny(false);
                        break;
                }

                // IVs
                int numPerfectIVs = 0;
                for (Stat stat :
                    {Stat::HP, Stat::ATK, Stat::DEF, Stat::SPD, Stat::SPATK, Stat::SPDEF})
                {
                    if (wc8.iv(stat) - 0xFC < 3)
                    {
                        numPerfectIVs = wc8.iv(stat) - 0xFB;
                        break;
                    }
                }
                for (int iv = 0; iv < numPerfectIVs; iv++)
                {
                    Stat setMeTo31 = Stat(pksm::randomNumber(0, 5));
                    while (pk8->iv(setMeTo31) == 31)
                    {
                        setMeTo31 = Stat(pksm::randomNumber(0, 5));
                    }
                    pk8->iv(setMeTo31, 31);
                }
                for (Stat stat :
                    {Stat::HP, Stat::ATK, Stat::DEF, Stat::SPD, Stat::SPATK, Stat::SPDEF})
                {
                    if (pk8->iv(stat) != 31)
                    {
                        pk8->iv(stat, pksm::randomNumber(0, 31));
                    }
                }

                pk8->refreshChecksum();

                pkm(*pk8, injectPosition / 30, injectPosition % 30, false);
            }
            else if (wc8.item())
            {
                auto valid  = validItems();
                auto limits = pouches();
                for (int itemNum = 0; itemNum < wc8.items(); itemNum++)
                {
                    bool currentSet = false;
                    for (size_t pouch = 0; pouch < limits.size(); pouch++)
                    {
                        // Check this is the correct pouch
                        if (!currentSet &&
                            std::binary_search(valid[limits[pouch].first].begin(),
                                valid[limits[pouch].first].end(), wc8.object(itemNum)))
                        {
                            for (int slot = 0; slot < limits[pouch].second; slot++)
                            {
                                auto occupying = item(limits[pouch].first, slot);
                                if (occupying->id() == 0)
                                {
                                    occupying->id(wc8.object(itemNum));
                                    occupying->count(wc8.objectQuantity(itemNum));
                                    reinterpret_cast<Item8*>(occupying.get())->newFlag(true);
                                    item(*occupying, limits[pouch].first, slot);
                                    currentSet = true;
                                    break;
                                }
                                else if (occupying->id() == wc8.object(itemNum) &&
                                         limits[pouch].first != Pouch::TM)
                                {
                                    occupying->count(occupying->count() + 1);
                                    item(*occupying, limits[pouch].first, slot);
                                    currentSet = true;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
            else if (wc8.BP())
            {
                // TODO
            }
            else if (wc8.clothing())
            {
                // TODO
            }
        }
    }
    std::unique_ptr<WCX> SavSWSH::mysteryGift(int) const { return nullptr; }

    void SavSWSH::dex(const PKX& pk)
    {
        u8* entryAddr = nullptr;
        if (!pk.egg())
        {
            if (u16 index = ((PK8&)pk).pokedexIndex())
            {
                entryAddr = getBlock(PokeDex)->decryptedData() + sizeof(DexEntry) * (index - 1);
            }
            else if (u16 index = reinterpret_cast<const PK8&>(pk).armordexIndex())
            {
                entryAddr = getBlock(ArmorDex)->decryptedData() + sizeof(DexEntry) * (index - 1);
            }
            else if (u16 index = reinterpret_cast<const PK8&>(pk).crowndexIndex())
            {
                entryAddr = getBlock(CrownDex)->decryptedData() + sizeof(DexEntry) * (index - 1);
            }
        }

        if (entryAddr)
        {
            DexEntry entry = LittleEndian::convertTo<DexEntry>(entryAddr);

            u16 form = pk.alternativeForm();
            if (pk.species() == Species::Alcremie)
            {
                form *= 7;
                form += reinterpret_cast<const PK8&>(pk).formDuration();
            }
            else if (pk.species() == Species::Eternatus)
            {
                form = 0;
                setProperGiga(entry, true, pk.shiny(), pk.gender());
            }

            setProperLocation(entry, form, pk.shiny(), pk.gender());
            entry.owned = 1;
            entry.languages |= 1 << u8(pk.language());
            entry.displayFormID = form;
            entry.displayShiny  = pk.shiny() ? 1 : 0;

            if (entry.battled == 0)
            {
                entry.battled++;
            }

            LittleEndian::convertFrom<DexEntry>(entryAddr, entry);
        }
    }

    int SavSWSH::dexSeen() const
    {
        int ret = 0;
        for (const auto& i : availableSpecies())
        {
            u16 index       = PersonalSWSH::pokedexIndex(u16(i));
            u8* entryOffset = getBlock(PokeDex)->decryptedData() + index * sizeof(DexEntry);
            for (size_t j = 0; j < 0x20; j++) // Entire seen region size
            {
                if (entryOffset[j])
                {
                    ret++;
                    break;
                }
            }
        }
        return ret;
    }

    int SavSWSH::dexCaught() const
    {
        int ret = 0;
        for (const auto& i : availableSpecies())
        {
            u16 index       = PersonalSWSH::pokedexIndex(u16(i));
            u8* entryOffset = getBlock(PokeDex)->decryptedData() + index * sizeof(DexEntry);
            if (entryOffset[0x20] & 3)
            {
                ret++;
            }
        }
        return ret;
    }
}
