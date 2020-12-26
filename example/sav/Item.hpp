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

#ifndef ITEM_HPP
#define ITEM_HPP

#include "enums/Generation.hpp"
#include "utils/ValueConverter.hpp"
#include "utils/coretypes.h"
#include "utils/endian.hpp"

namespace pksm
{
    class Item3;
    class Item4;
    class Item5;
    class Item6;
    class Item7;
    class Item7b;
    class Item8;

    class Item
    {
    public:
        virtual ~Item()                           = default;
        virtual Generation generation(void) const = 0;
        virtual u16 maxCount(void) const          = 0;
        virtual u16 id(void) const                = 0;
        virtual u16 count(void) const             = 0;
        virtual std::vector<u8> bytes(void) const = 0;
        virtual void id(u16 id)                   = 0;
        virtual void count(u16 id)                = 0;
        virtual operator Item3(void) const;
        virtual operator Item4(void) const;
        virtual operator Item5(void) const;
        virtual operator Item6(void) const;
        virtual operator Item7(void) const;
        virtual operator Item7b(void) const;
        virtual operator Item8(void) const;
    };

    class Item3 : public Item
    {
    private:
        std::array<u8, 4> itemData;
        u16 key;

    public:
        Item3(u8* data = nullptr, u16 securityKey = 0)
        {
            if (data)
            {
                std::copy(data, data + 4, itemData.data());
                LittleEndian::convertFrom<u16>(itemData.data() + 2,
                    LittleEndian::convertTo<u16>(itemData.data() + 2) ^ securityKey);
                key = securityKey;
            }
            else
            {
                itemData = {0, 0, 0, 0};
                key      = securityKey;
            }
        }
        Generation generation(void) const override { return Generation::THREE; }
        u16 maxCount(void) const override { return 0xFFFF; }
        u16 id(void) const override
        {
            return ItemConverter::g3ToNational(LittleEndian::convertTo<u16>(itemData.data()));
        }
        void id(u16 v) override
        {
            LittleEndian::convertFrom<u16>(itemData.data(), ItemConverter::nationalToG3(v));
        }
        u16 id3(void) const { return LittleEndian::convertTo<u16>(itemData.data()); }
        void id3(u16 v) { LittleEndian::convertFrom<u16>(itemData.data(), v); }
        u16 count(void) const override { return LittleEndian::convertTo<u16>(itemData.data() + 2); }
        void count(u16 v) override { LittleEndian::convertFrom<u16>(itemData.data() + 2, v); }
        u16 securityKey(void) const { return key; }
        void securityKey(u16 v) { key = v; }
        std::vector<u8> bytes(void) const override
        {
            std::vector<u8> data{itemData.begin(), itemData.end()};
            LittleEndian::convertFrom<u16>(
                data.data() + 2, LittleEndian::convertTo<u16>(data.data() + 2) ^ key);
            return data;
        }
    };

    class Item4 : public Item
    {
    private:
        std::array<u8, 4> itemData;

    public:
        Item4(u8* data = nullptr)
        {
            if (data)
            {
                std::copy(data, data + 4, itemData.data());
            }
            else
            {
                itemData = {0, 0, 0, 0};
            }
        }
        Generation generation(void) const override { return Generation::FOUR; }
        u16 maxCount(void) const override { return 0xFFFF; }
        u16 id(void) const override { return LittleEndian::convertTo<u16>(itemData.data()); }
        void id(u16 v) override { LittleEndian::convertFrom<u16>(itemData.data(), v); }
        u16 count(void) const override { return LittleEndian::convertTo<u16>(itemData.data() + 2); }
        void count(u16 v) override { LittleEndian::convertFrom<u16>(itemData.data() + 2, v); }
        std::vector<u8> bytes(void) const override
        {
            return std::vector<u8>{itemData.begin(), itemData.end()};
        }
    };

    class Item5 : public Item
    {
    private:
        std::array<u8, 4> itemData;

    public:
        Item5(u8* data = nullptr)
        {
            if (data)
            {
                std::copy(data, data + 4, itemData.data());
            }
            else
            {
                itemData = {0, 0, 0, 0};
            }
        }
        Generation generation(void) const override { return Generation::FIVE; }
        u16 maxCount(void) const override { return 0xFFFF; }
        u16 id(void) const override { return LittleEndian::convertTo<u16>(itemData.data()); }
        void id(u16 v) override { LittleEndian::convertFrom<u16>(itemData.data(), v); }
        u16 count(void) const override { return LittleEndian::convertTo<u16>(itemData.data() + 2); }
        void count(u16 v) override { LittleEndian::convertFrom<u16>(itemData.data() + 2, v); }
        std::vector<u8> bytes(void) const override
        {
            return std::vector<u8>{itemData.begin(), itemData.end()};
        }
    };

    class Item6 : public Item
    {
    private:
        std::array<u8, 4> itemData;

    public:
        Item6(u8* data = nullptr)
        {
            if (data)
            {
                std::copy(data, data + 4, itemData.data());
            }
            else
            {
                itemData = {0, 0, 0, 0};
            }
        }
        Generation generation(void) const override { return Generation::SIX; }
        u16 maxCount(void) const override { return 0xFFFF; }
        u16 id(void) const override { return LittleEndian::convertTo<u16>(itemData.data()); }
        void id(u16 v) override { LittleEndian::convertFrom<u16>(itemData.data(), v); }
        u16 count(void) const override { return LittleEndian::convertTo<u16>(itemData.data() + 2); }
        void count(u16 v) override { LittleEndian::convertFrom<u16>(itemData.data() + 2, v); }
        std::vector<u8> bytes(void) const override
        {
            return std::vector<u8>{itemData.begin(), itemData.end()};
        }
    };

    class Item7 : public Item
    {
    private:
        // Reference structure
        // struct
        // {
        //     unsigned int id : 10;
        //     unsigned int count : 10;
        //     unsigned int freeSpace : 10;
        //     unsigned int newFlag : 1;
        //     unsigned int reserved : 1;
        // };
        u32 itemData = 0;

    public:
        Item7(u8* data = nullptr)
        {
            if (data)
            {
                itemData = LittleEndian::convertTo<u32>(data);
            }
        }
        Generation generation(void) const override { return Generation::SEVEN; }
        u16 maxCount(void) const override { return 0x3FF; }
        u16 id(void) const override { return itemData & 0x3FF; }
        void id(u16 v) override { itemData = ((itemData & ~0x3FF) | std::min((u32)v, (u32)0x3FF)); }
        u16 count(void) const override { return (itemData >> 10) & 0x3FF; }
        void count(u16 v) override
        {
            itemData = (itemData & ~(0x3FF << 10)) | (std::min((u32)v, (u32)0x3FF) << 10);
        }
        u16 freeSpaceIndex(void) const { return (itemData >> 20) & 0x3FF; }
        void freeSpaceIndex(u16 v)
        {
            itemData = (itemData & ~(0x3FF << 20)) | (std::min((u32)v, (u32)0x3FF) << 20);
        }
        bool newFlag(void) const { return (itemData >> 30) & 1; }
        void newFlag(bool v) { itemData = (itemData & ~(1 << 30)) | (v ? 1 << 30 : 0); }
        bool reserved(void) const { return (itemData >> 31) & 1; }
        void reserved(bool v) { itemData = (itemData & ~(1u << 31)) | (v ? 1u << 31 : 0); }
        std::vector<u8> bytes(void) const override
        {
            std::vector<u8> ret = {0, 0, 0, 0};
            LittleEndian::convertFrom<u32>(ret.data(), itemData);
            return ret;
        }
        operator Item7b(void) const override;
        operator Item8(void) const override;
    };

    class Item7b : public Item
    {
    private:
        // Reference structure
        // struct
        // {
        // unsigned int id : 15;
        // unsigned int count : 15;
        // unsigned int newFlag : 1;
        // unsigned int reserved : 1;
        // };
        u32 itemData = 0;

    public:
        Item7b(u8* data = nullptr)
        {
            if (data)
            {
                itemData = LittleEndian::convertTo<u32>(data);
            }
        }
        Generation generation(void) const override { return Generation::LGPE; }
        u16 maxCount(void) const override { return 0x7FFF; }
        u16 id(void) const override { return itemData & 0x7FFF; }
        void id(u16 v) override
        {
            itemData = ((itemData & ~0x7FFF) | std::min((u32)v, (u32)0x7FFF));
        }
        u16 count(void) const override { return (itemData >> 15) & 0x7FFF; }
        void count(u16 v) override
        {
            itemData = (itemData & ~(0x7FFF << 15)) | (std::min((u32)v, (u32)0x7FFF) << 15);
        }
        bool newFlag(void) const { return (itemData >> 30) & 1; }
        void newFlag(bool v) { itemData = (itemData & ~(1 << 30)) | (v ? 1 << 30 : 0); }
        bool reserved(void) const { return (itemData >> 31) & 1; }
        void reserved(bool v) { itemData = (itemData & ~(1u << 31)) | (v ? 1u << 31 : 0); }
        std::vector<u8> bytes(void) const override
        {
            std::vector<u8> ret = {0, 0, 0, 0};
            LittleEndian::convertFrom<u32>(ret.data(), itemData);
            return ret;
        }
        operator Item7(void) const override;
        operator Item8(void) const override;
    };

    class Item8 : public Item
    {
    private:
        // Reference structure
        // struct
        // {
        // unsigned int id : 15;
        // unsigned int count : 15;
        // unsigned int newFlag : 1;
        // unsigned int reserved : 1;
        // };
        u32 itemData = 0;

    public:
        Item8(u8* data = nullptr)
        {
            if (data)
            {
                itemData = LittleEndian::convertTo<u32>(data);
            }
        }
        Generation generation(void) const override { return Generation::SEVEN; }
        u16 maxCount(void) const override { return 0x7FFF; }
        u16 id(void) const override { return itemData & 0x7FFF; }
        void id(u16 v) override
        {
            itemData = ((itemData & ~0x7FFF) | std::min((u32)v, (u32)0x7FFF));
        }
        u16 count(void) const override { return (itemData >> 15) & 0x7FFF; }
        void count(u16 v) override
        {
            itemData = (itemData & ~(0x7FFF << 15)) | (std::min((u32)v, (u32)0x7FFF) << 15);
        }
        bool newFlag(void) const { return (itemData >> 30) & 1; }
        void newFlag(bool v) { itemData = (itemData & ~(1 << 30)) | (v ? 1 << 30 : 0); }
        bool reserved(void) const { return (itemData >> 31) & 1; }
        void reserved(bool v) { itemData = (itemData & ~(1u << 31)) | (v ? 1u << 31 : 0); }
        std::vector<u8> bytes(void) const override
        {
            std::vector<u8> ret = {0, 0, 0, 0};
            LittleEndian::convertFrom<u32>(ret.data(), itemData);
            return ret;
        }
        operator Item7(void) const override;
        operator Item7b(void) const override;
    };
}

#endif
