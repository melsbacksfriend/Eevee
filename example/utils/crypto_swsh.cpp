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

#include "utils/crypto.hpp"
#include "utils/endian.hpp"

namespace pksm::crypto::swsh
{
    namespace internal
    {
        // clang-format off
            constexpr std::array<u8, 127> xorpad = {
                0xA0, 0x92, 0xD1, 0x06, 0x07, 0xDB, 0x32, 0xA1, 0xAE, 0x01, 0xF5, 0xC5, 0x1E, 0x84, 0x4F, 0xE3,
                0x53, 0xCA, 0x37, 0xF4, 0xA7, 0xB0, 0x4D, 0xA0, 0x18, 0xB7, 0xC2, 0x97, 0xDA, 0x5F, 0x53, 0x2B,
                0x75, 0xFA, 0x48, 0x16, 0xF8, 0xD4, 0x8A, 0x6F, 0x61, 0x05, 0xF4, 0xE2, 0xFD, 0x04, 0xB5, 0xA3,
                0x0F, 0xFC, 0x44, 0x92, 0xCB, 0x32, 0xE6, 0x1B, 0xB9, 0xB1, 0x2E, 0x01, 0xB0, 0x56, 0x53, 0x36,
                0xD2, 0xD1, 0x50, 0x3D, 0xDE, 0x5B, 0x2E, 0x0E, 0x52, 0xFD, 0xDF, 0x2F, 0x7B, 0xCA, 0x63, 0x50,
                0xA4, 0x67, 0x5D, 0x23, 0x17, 0xC0, 0x52, 0xE1, 0xA6, 0x30, 0x7C, 0x2B, 0xB6, 0x70, 0x36, 0x5B,
                0x2A, 0x27, 0x69, 0x33, 0xF5, 0x63, 0x7B, 0x36, 0x3F, 0x26, 0x9B, 0xA3, 0xED, 0x7A, 0x53, 0x00,
                0xA4, 0x48, 0xB3, 0x50, 0x9E, 0x14, 0xA0, 0x52, 0xDE, 0x7E, 0x10, 0x2B, 0x1B, 0x77, 0x6E
            };

            constexpr std::array<u8, 64> hashBegin = {
                0x9E, 0xC9, 0x9C, 0xD7, 0x0E, 0xD3, 0x3C, 0x44, 0xFB, 0x93, 0x03, 0xDC, 0xEB, 0x39, 0xB4, 0x2A,
                0x19, 0x47, 0xE9, 0x63, 0x4B, 0xA2, 0x33, 0x44, 0x16, 0xBF, 0x82, 0xA2, 0xBA, 0x63, 0x55, 0xB6,
                0x3D, 0x9D, 0xF2, 0x4B, 0x5F, 0x7B, 0x6A, 0xB2, 0x62, 0x1D, 0xC2, 0x1B, 0x68, 0xE5, 0xC8, 0xB5,
                0x3A, 0x05, 0x90, 0x00, 0xE8, 0xA8, 0x10, 0x3D, 0xE2, 0xEC, 0xF0, 0x0C, 0xB2, 0xED, 0x4F, 0x6D,
            };

            constexpr std::array<u8, 64> hashEnd = {
                0xD6, 0xC0, 0x1C, 0x59, 0x8B, 0xC8, 0xB8, 0xCB, 0x46, 0xE1, 0x53, 0xFC, 0x82, 0x8C, 0x75, 0x75,
                0x13, 0xE0, 0x45, 0xDF, 0x32, 0x69, 0x3C, 0x75, 0xF0, 0x59, 0xF8, 0xD9, 0xA2, 0x5F, 0xB2, 0x17,
                0xE0, 0x80, 0x52, 0xDB, 0xEA, 0x89, 0x73, 0x99, 0x75, 0x79, 0xAF, 0xCB, 0x2E, 0x80, 0x07, 0xE6,
                0xF1, 0x26, 0xE0, 0x03, 0x0A, 0xE6, 0x6F, 0xF6, 0x41, 0xBF, 0x7E, 0x59, 0xC2, 0xAE, 0x55, 0xFD,
            };
        // clang-format on

        std::array<u8, 32> computeHash(u8* data, size_t length)
        {
            SHA256 context;
            context.update(internal::hashBegin.data(), hashBegin.size());
            context.update(data, length);
            context.update(internal::hashEnd.data(), hashEnd.size());
            return context.finish();
        }

        class XorShift32
        {
        private:
            u32 mCounter = 0;
            u32 mSeed;
            static void advance(u32& key)
            {
                key ^= key << 2;
                key ^= key >> 15;
                key ^= key << 13;
            }

        public:
            explicit XorShift32(u32 seed)
            {
                u32 count = pksm::crypto::popcount(seed);
                for (u32 i = 0; i < count; i++)
                {
                    advance(seed);
                }

                mSeed = seed;
            }

            u8 next()
            {
                u8 ret = (mSeed >> (mCounter << 3)) & 0xFF;
                if (mCounter == 3)
                {
                    advance(mSeed);
                    mCounter = 0;
                }
                else
                {
                    ++mCounter;
                }
                return ret;
            }

            u32 next32()
            {
                return next() | (u32(next()) << 8) | (u32(next()) << 16) | (u32(next()) << 24);
            }
        };

        class CryptoException : public std::exception
        {
        public:
            explicit CryptoException(const std::string& message)
                : mMessage("CryptoException: " + message)
            {
            }

            const char* what() const noexcept override { return mMessage.c_str(); }

        private:
            std::string mMessage;
        };
    }

    void applyXor(std::shared_ptr<u8[]> data, size_t length)
    {
        for (size_t i = 0; i < length - 32; i++)
        {
            data[i] ^= internal::xorpad[i % internal::xorpad.size()];
        }
    }

    void sign(std::shared_ptr<u8[]> data, size_t length)
    {
        if (length > 32)
        {
            auto hash = internal::computeHash(data.get(), length - 32);
            std::copy(hash.begin(), hash.end(), data.get() + length - 32);
        }
    }

    bool verify(std::shared_ptr<u8[]> data, size_t length)
    {
        if (length <= 32)
        {
            return false;
        }
        auto hash = internal::computeHash(data.get(), length - 32);
        for (size_t i = 0; i < 32; i++)
        {
            if (hash[i] != data[length - 32 + i])
            {
                return false;
            }
        }
        return true;
    }

    std::vector<std::shared_ptr<SCBlock>> getBlockList(std::shared_ptr<u8[]> data, size_t length)
    {
        std::vector<std::shared_ptr<SCBlock>> ret;
        size_t offset = 0;
        while (offset < length - 32)
        {
            ret.emplace_back(new SCBlock(data, offset));
        }

        return ret;
    }

    SCBlock::SCBlock(std::shared_ptr<u8[]> data, size_t& offset) : data(data), myOffset(offset)
    {
        // Key size
        offset += 4;

        internal::XorShift32 xorShift(key());

        type = SCBlockType(data[offset] ^= xorShift.next());

        switch (type)
        {
            case SCBlockType::Bool1:
            case SCBlockType::Bool2:
            case SCBlockType::Bool3:
                // No extra data
                offset++;
                break;
            case SCBlockType::Object:
            {
                dataLength =
                    LittleEndian::convertTo<u32>(data.get() + offset + 1) ^ xorShift.next32();
                LittleEndian::convertFrom<u32>(data.get() + offset + 1, dataLength);
                for (size_t i = 0; i < dataLength; i++)
                {
                    data[offset + 5 + i] ^= xorShift.next();
                }
                offset += 5 + dataLength;
            }
            break;
            case SCBlockType::Array:
            {
                dataLength =
                    LittleEndian::convertTo<u32>(data.get() + offset + 1) ^ xorShift.next32();
                LittleEndian::convertFrom<u32>(data.get() + offset + 1, dataLength);
                subtype = SCBlockType(data[offset + 5] ^= xorShift.next());
                switch (subtype)
                {
                    case SCBlockType::Bool3:
                        // An array of booleans
                        for (size_t i = 0; i < dataLength; i++)
                        {
                            data[offset + 6 + i] ^= xorShift.next();
                        }
                        offset += 6 + dataLength;
                        break;
                    case SCBlockType::U8:
                    case SCBlockType::U16:
                    case SCBlockType::U32:
                    case SCBlockType::U64:
                    case SCBlockType::S8:
                    case SCBlockType::S16:
                    case SCBlockType::S32:
                    case SCBlockType::S64:
                    case SCBlockType::Float:
                    case SCBlockType::Double:
                    {
                        size_t entrySize = arrayEntrySize(subtype);
                        for (size_t i = 0; i < dataLength * entrySize; i++)
                        {
                            data[offset + 6 + i] ^= xorShift.next();
                        }
                        offset += 6 + (dataLength * entrySize);
                    }
                    break;
                    default:
                        throw internal::CryptoException(
                            "Decoding block: Key: " + std::to_string(key()) +
                            "\nSubtype: " + std::to_string(u8(type)));
                }
            }
            break;
            case SCBlockType::U8:
            case SCBlockType::U16:
            case SCBlockType::U32:
            case SCBlockType::U64:
            case SCBlockType::S8:
            case SCBlockType::S16:
            case SCBlockType::S32:
            case SCBlockType::S64:
            case SCBlockType::Float:
            case SCBlockType::Double:
            {
                size_t entrySize = arrayEntrySize(type);
                for (size_t i = 0; i < entrySize; i++)
                {
                    data[offset + 1 + i] ^= xorShift.next();
                }
                offset += 1 + entrySize;
            }
            break;
            default:
                throw internal::CryptoException("Decoding block: Key: " + std::to_string(key()) +
                                                "\nType: " + std::to_string(u8(type)));
        }
    }

    void SCBlock::encrypt()
    {
        if (!currentlyEncrypted)
        {
            internal::XorShift32 xorShift(key());
            for (size_t i = 0; i < encryptedDataSize() - 4; i++)
            {
                data[myOffset + 4 + i] ^= xorShift.next();
            }

            currentlyEncrypted = true;
        }
    }

    void SCBlock::decrypt()
    {
        if (currentlyEncrypted)
        {
            internal::XorShift32 xorShift(key());
            for (size_t i = 0; i < encryptedDataSize() - 4; i++)
            {
                data[myOffset + 4 + i] ^= xorShift.next();
            }

            currentlyEncrypted = false;
        }
    }

    u32 SCBlock::key() const { return LittleEndian::convertTo<u32>(&data[myOffset]); }
    void SCBlock::key(u32 v) { LittleEndian::convertFrom<u32>(&data[myOffset], v); }

    size_t SCBlock::arrayEntrySize(SCBlockType type)
    {
        switch (type)
        {
            case SCBlockType::Bool3:
            case SCBlockType::U8:
            case SCBlockType::S8:
                return 1;
            case SCBlockType::U16:
            case SCBlockType::S16:
                return 2;
            case SCBlockType::U32:
            case SCBlockType::S32:
            case SCBlockType::Float:
                return 4;
            case SCBlockType::U64:
            case SCBlockType::S64:
            case SCBlockType::Double:
                return 8;
            default:
                throw internal::CryptoException("Type size unknown: " + std::to_string(u32(type)));
        }
    }

    size_t SCBlock::headerSize(SCBlockType type)
    {
        switch (type)
        {
            case SCBlockType::Bool1:
            case SCBlockType::Bool2:
            case SCBlockType::Bool3:
            case SCBlockType::U8:
            case SCBlockType::U16:
            case SCBlockType::U32:
            case SCBlockType::U64:
            case SCBlockType::S8:
            case SCBlockType::S16:
            case SCBlockType::S32:
            case SCBlockType::S64:
            case SCBlockType::Float:
            case SCBlockType::Double:
                return 5; // key + type
            case SCBlockType::Object:
                return 9; // key + type + length
            case SCBlockType::Array:
                return 10; // key + type + subtype + length
            default:
                throw internal::CryptoException("Type size unknown: " + std::to_string(u32(type)));
        }
    }

    size_t SCBlock::encryptedDataSize()
    {
        constexpr int baseSize = 4 + 1; // key + type
        switch (type)
        {
            case SCBlockType::Bool1:
            case SCBlockType::Bool2:
            case SCBlockType::Bool3:
                return baseSize;
            case SCBlockType::Object:
                return baseSize + 4 + dataLength; // + datalength variable + actual data
            case SCBlockType::Array:
                return baseSize + 5 +
                       dataLength *
                           arrayEntrySize(subtype); // + subtype + datalength variable + actual data
            case SCBlockType::U8:
            case SCBlockType::U16:
            case SCBlockType::U32:
            case SCBlockType::U64:
            case SCBlockType::S8:
            case SCBlockType::S16:
            case SCBlockType::S32:
            case SCBlockType::S64:
            case SCBlockType::Float:
            case SCBlockType::Double:
                return baseSize + arrayEntrySize(type); // + actual data
            default:
                throw internal::CryptoException("Type size unknown: " + std::to_string(u32(type)));
        }
    }
}
