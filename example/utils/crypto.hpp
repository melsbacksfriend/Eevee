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

#ifndef CRYPTO_HPP
#define CRYPTO_HPP

#include "utils/coretypes.h"
#include <array>
#include <memory>
#include <string>
#include <vector>

namespace pksm::crypto
{
    constexpr u32 popcount(u32 x)
    {
        x -= ((x >> 1) & 0x55555555u);
        x = (x & 0x33333333u) + ((x >> 2) & 0x33333333u);
        x = (x + (x >> 4)) & 0x0F0F0F0Fu;
        x += (x >> 8);
        x += (x >> 16);
        return x & 0x0000003Fu;
    }

    u16 ccitt16(const u8* buf, size_t len);
    u16 crc16(const u8* buf, size_t len);
    u16 crc16_noinvert(const u8* buf, size_t len);
    // Length must be a multiple of 4
    u32 sum32(const u8* buf, size_t len);

    // This SHA256 implementation is Brad Conte's. It has been modified to have a C++-style
    // interface.
    class SHA256
    {
    private:
        u8 data[64];
        u32 dataLength;
        u64 bitLength;
        std::array<u32, 8> state;

        void update();

    public:
        SHA256() { reinitialize(); }

        void reinitialize()
        {
            dataLength = 0;
            bitLength  = 0;
            state      = {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c,
                0x1f83d9ab, 0x5be0cd19};
        }
        void update(const u8* data, size_t len);
        std::array<u8, 32> finish();
    };
    std::array<u8, 32> sha256(const u8* buf, size_t len);

    namespace swsh
    {
        class SCBlock
        {
            friend std::vector<std::shared_ptr<SCBlock>> getBlockList(
                std::shared_ptr<u8[]> data, size_t length);

        public:
            enum class SCBlockType : u8
            {
                None = 0,

                Bool1 = 1, // False?
                Bool2 = 2, // True?
                Bool3 = 3, // Either? Array bool type

                Object = 4,

                Array = 5,

                U8     = 8,
                U16    = 9,
                U32    = 10,
                U64    = 11,
                S8     = 12,
                S16    = 13,
                S32    = 14,
                S64    = 15,
                Float  = 16,
                Double = 17,
            };
            u32 key() const;
            // Nop if in proper state
            void encrypt();
            void decrypt();

            u8* decryptedData()
            {
                decrypt();
                return rawData();
            }

        private:
            SCBlock(std::shared_ptr<u8[]> data, size_t& offset);
            SCBlock(const SCBlock&) = delete;
            SCBlock& operator=(const SCBlock&) = delete;

            // Returns pointer to data at the beginning of the block's data region, skipping block
            // identifying information
            u8* rawData() const { return data.get() + myOffset + headerSize(type); }
            void key(u32 v);
            // data.get() + myOffset points to the beginning of the block data: *(u32*)(data.get() +
            // myOffset) == key
            std::shared_ptr<u8[]> data = nullptr;
            size_t myOffset;
            size_t dataLength;
            SCBlockType type;
            SCBlockType subtype;
            bool currentlyEncrypted = false;

            size_t encryptedDataSize();
            static size_t arrayEntrySize(SCBlockType type);
            static size_t headerSize(SCBlockType type);
        };

        void applyXor(std::shared_ptr<u8[]> data, size_t length);
        void sign(std::shared_ptr<u8[]> data, size_t length);
        bool verify(std::shared_ptr<u8[]> data, size_t length);
        std::vector<std::shared_ptr<SCBlock>> getBlockList(
            std::shared_ptr<u8[]> data, size_t length);
    }

    namespace pkm
    {
        constexpr std::array<u8, 128> BlockPositions = {0, 1, 2, 3, 0, 1, 3, 2, 0, 2, 1, 3, 0, 3, 1,
            2, 0, 2, 3, 1, 0, 3, 2, 1, 1, 0, 2, 3, 1, 0, 3, 2, 2, 0, 1, 3, 3, 0, 1, 2, 2, 0, 3, 1,
            3, 0, 2, 1, 1, 2, 0, 3, 1, 3, 0, 2, 2, 1, 0, 3, 3, 1, 0, 2, 2, 3, 0, 1, 3, 2, 0, 1, 1,
            2, 3, 0, 1, 3, 2, 0, 2, 1, 3, 0, 3, 1, 2, 0, 2, 3, 1, 0, 3, 2, 1, 0,

            // duplicates of 0-7 to eliminate modulus
            0, 1, 2, 3, 0, 1, 3, 2, 0, 2, 1, 3, 0, 3, 1, 2, 0, 2, 3, 1, 0, 3, 2, 1, 1, 0, 2, 3, 1,
            0, 3, 2};

        constexpr std::array<u8, 32> InvertedBlockPositions = {
            0, 1, 2, 4, 3, 5, 6, 7, 12, 18, 13, 19, 8, 10, 14, 20, 16, 22, 9, 11, 15, 21, 17, 23, 0,
            1, 2, 4, 3, 5, 6, 7 // duplicates of 0-7 to eliminate
                                // modulus
        };

        constexpr u32 seedStep(u32 seed) { return seed * 0x41C64E6D + 0x6073; }

        template <size_t BlockLength>
        constexpr void blockShuffle(u8* data, u8 sv)
        {
            u8 temp[BlockLength * 4];
            std::copy(data, data + BlockLength * 4, temp);
            u8 index = sv * 4;
            for (size_t block = 0; block < 4; block++)
            {
                u8 ofs = BlockPositions[index + block];
                std::copy(temp + ofs * BlockLength, temp + (ofs + 1) * BlockLength,
                    data + block * BlockLength);
            }
        }

        template <size_t Size>
        constexpr void crypt(u8* data, u32 key)
        {
            for (size_t i = 0; i < Size; i += 2)
            {
                key = seedStep(key);
                data[i] ^= (key >> 16);
                data[i + 1] ^= (key >> 24);
            }
        }

        // NOTE: Use the templated version wherever possible. Compile-time constants are preferred
        constexpr void crypt(u8* data, u32 key, size_t size)
        {
            for (size_t i = 0; i < size; i += 2)
            {
                key = seedStep(key);
                data[i] ^= (key >> 16);
                data[i + 1] ^= (key >> 24);
            }
        }
    }
}

#endif
