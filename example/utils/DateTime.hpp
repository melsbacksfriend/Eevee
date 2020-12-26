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

#ifndef DATE_HPP
#define DATE_HPP

#include "utils/coretypes.h"
#include <time.h>

class Date
{
public:
    Date(const time_t& time) : Date(*gmtime(&time)) {}
    constexpr Date(const struct tm& time) : Date(time.tm_mday, time.tm_mon + 1, time.tm_year + 1900)
    {
    }
    constexpr Date(u8 day, u8 month, u32 year) : mYear(year), mDay(day), mMonth(month) {}

    static Date today() { return Date{time(nullptr)}; }

    // 1-31
    constexpr u8 day() const { return mDay; }
    // 1-12
    constexpr u8 month() const { return mMonth; }
    // full year, ex 2015
    constexpr u32 year() const { return mYear; }
    constexpr void day(u8 v) { mDay = v; }
    constexpr void month(u8 v) { mMonth = v; }
    constexpr void year(u32 v) { mYear = v; }

    constexpr bool operator==(const Date& other) const
    {
        return mDay == other.mDay && mMonth == other.mMonth && mYear == other.mYear;
    }
    constexpr bool operator!=(const Date& other) const { return !(*this == other); }

    constexpr bool operator<(const Date& other) const
    {
        if (mYear < other.mYear)
        {
            return true;
        }
        else if (mYear == other.mYear && mMonth < other.mMonth)
        {
            return true;
        }
        else if (mYear == other.mYear && mMonth == other.mMonth && mDay < other.mDay)
        {
            return true;
        }
        return false;
    }
    constexpr bool operator<=(const Date& other) const { return *this == other || *this < other; }

    constexpr bool operator>(const Date& other) const
    {
        if (mYear > other.mYear)
        {
            return true;
        }
        else if (mYear == other.mYear && mMonth > other.mMonth)
        {
            return true;
        }
        else if (mYear == other.mYear && mMonth == other.mMonth && mDay > other.mDay)
        {
            return true;
        }
        return false;
    }
    constexpr bool operator>=(const Date& other) const { return *this == other || *this > other; }

private:
    u32 mYear;
    u8 mDay;
    u8 mMonth;
};

class Time
{
public:
    Time(const time_t& time) : Time(*gmtime(&time)) {}
    constexpr Time(const struct tm& time) : Time(time.tm_hour, time.tm_min, time.tm_sec) {}
    constexpr Time(u8 hour, u8 minute, u8 second) : mHour(hour), mMinute(minute), mSecond(second) {}

    static Time now() { return Time{time(nullptr)}; }

    // 0-23
    constexpr u8 hour() const { return mHour; }
    // 0-59
    constexpr u8 minute() const { return mMinute; }
    // 0-60. 60 is possible because of leap seconds (https://en.wikipedia.org/wiki/Leap_second)
    constexpr u8 second() const { return mSecond; }
    constexpr void hour(u8 v) { mHour = v; }
    constexpr void minute(u8 v) { mMinute = v; }
    constexpr void second(u8 v) { mSecond = v; }

    constexpr bool operator==(const Time& other) const
    {
        return mSecond == other.mSecond && mMinute == other.mMinute && mHour == other.mHour;
    }
    constexpr bool operator!=(const Time& other) const { return !(*this == other); }

    constexpr bool operator<(const Time& other) const
    {
        if (mHour < other.mHour)
        {
            return true;
        }
        else if (mHour == other.mHour && mMinute < other.mMinute)
        {
            return true;
        }
        else if (mHour == other.mHour && mMinute == other.mMinute && mSecond < other.mSecond)
        {
            return true;
        }
        return false;
    }
    constexpr bool operator<=(const Time& other) const { return *this == other || *this < other; }

    constexpr bool operator>(const Time& other) const
    {
        if (mHour > other.mHour)
        {
            return true;
        }
        else if (mHour == other.mHour && mMinute > other.mMinute)
        {
            return true;
        }
        else if (mHour == other.mHour && mMinute == other.mMinute && mSecond > other.mSecond)
        {
            return true;
        }
        return false;
    }
    constexpr bool operator>=(const Time& other) const { return *this == other || *this > other; }

private:
    u8 mHour;
    u8 mMinute;
    u8 mSecond;
};

class DateTime : public Date, public Time
{
public:
    DateTime(const time_t& time) : DateTime(*gmtime(&time)) {}
    constexpr DateTime(const struct tm& time) : Date(time), Time(time) {}
    constexpr DateTime(const Date& date) : Date(date), Time(0, 0, 0) {}
    constexpr DateTime(const Time& time) : Date(1, 1, 1900), Time(time) {}
    constexpr DateTime(const Date& date, const Time& time) : Date(date), Time(time) {}
    constexpr DateTime(const Time& time, const Date& date) : Date(date), Time(time) {}

    constexpr DateTime& operator=(const Date& date)
    {
        day(date.day());
        month(date.month());
        year(date.year());
        return *this;
    }
    constexpr DateTime& operator=(const Time& time)
    {
        hour(time.hour());
        minute(time.minute());
        second(time.second());
        return *this;
    }
    constexpr DateTime& operator=(const DateTime& other) = default;

    using Date::operator==;
    using Time::operator==;
    using Date::operator!=;
    using Time::operator!=;
    using Date::operator<;
    using Time::operator<;
    using Date::operator>;
    using Time::operator>;
    using Date::operator<=;
    using Time::operator<=;
    using Date::operator>=;
    using Time::operator>=;

    constexpr bool operator==(const DateTime& other) const
    {
        return Date::operator==(other) && Time::operator==(other);
    }
    constexpr bool operator!=(const DateTime& other) const
    {
        return Date::operator!=(other) || Time::operator!=(other);
    }
    constexpr bool operator<(const DateTime& other) const
    {
        return Date::operator<(other) || (Date::operator==(other) && Time::operator<(other));
    }
    constexpr bool operator<=(const DateTime& other) const
    {
        return Date::operator<=(other) || (Date::operator==(other) && Time::operator<=(other));
    }
    constexpr bool operator>(const DateTime& other) const
    {
        return Date::operator>(other) || (Date::operator==(other) && Time::operator>(other));
    }
    constexpr bool operator>=(const DateTime& other) const
    {
        return Date::operator>(other) || (Date::operator==(other) && Time::operator>=(other));
    }

    // Remove overload ambiguity
    bool operator==(const time_t& tOther) const
    {
        DateTime other{tOther};
        return Date::operator==(other) && Time::operator==(other);
    }
    bool operator!=(const time_t& tOther) const
    {
        DateTime other{tOther};
        return Date::operator!=(other) || Time::operator!=(other);
    }
    bool operator<(const time_t& tOther) const
    {
        DateTime other{tOther};
        return Date::operator<(other) || (Date::operator==(other) && Time::operator<(other));
    }
    bool operator<=(const time_t& tOther) const
    {
        DateTime other{tOther};
        return Date::operator<=(other) || (Date::operator==(other) && Time::operator<=(other));
    }
    bool operator>(const time_t& tOther) const
    {
        DateTime other{tOther};
        return Date::operator>(other) || (Date::operator==(other) && Time::operator>(other));
    }
    bool operator>=(const time_t& tOther) const
    {
        DateTime other{tOther};
        return Date::operator>(other) || (Date::operator==(other) && Time::operator>=(other));
    }

    constexpr bool operator==(const struct tm& tOther) const
    {
        DateTime other{tOther};
        return Date::operator==(other) && Time::operator==(other);
    }
    constexpr bool operator!=(const struct tm& tOther) const
    {
        DateTime other{tOther};
        return Date::operator!=(other) || Time::operator!=(other);
    }
    constexpr bool operator<(const struct tm& tOther) const
    {
        DateTime other{tOther};
        return Date::operator<(other) || (Date::operator==(other) && Time::operator<(other));
    }
    constexpr bool operator<=(const struct tm& tOther) const
    {
        DateTime other{tOther};
        return Date::operator<=(other) || (Date::operator==(other) && Time::operator<=(other));
    }
    constexpr bool operator>(const struct tm& tOther) const
    {
        DateTime other{tOther};
        return Date::operator>(other) || (Date::operator==(other) && Time::operator>(other));
    }
    constexpr bool operator>=(const struct tm& tOther) const
    {
        DateTime other{tOther};
        return Date::operator>(other) || (Date::operator==(other) && Time::operator>=(other));
    }

    static DateTime now() { return DateTime{time(nullptr)}; }
};

inline bool operator==(const time_t& tThis, const DateTime& other)
{
    DateTime This{tThis};
    return This == other;
}
inline bool operator!=(const time_t& tThis, const DateTime& other)
{
    DateTime This{tThis};
    return This != other;
}
inline bool operator<(const time_t& tThis, const DateTime& other)
{
    DateTime This{tThis};
    return This < other;
}
inline bool operator<=(const time_t& tThis, const DateTime& other)
{
    DateTime This{tThis};
    return This <= other;
}
inline bool operator>(const time_t& tThis, const DateTime& other)
{
    DateTime This{tThis};
    return This > other;
}
inline bool operator>=(const time_t& tThis, const DateTime& other)
{
    DateTime This{tThis};
    return This >= other;
}

inline bool operator==(const time_t& tThis, const Date& other)
{
    Date This{tThis};
    return This == other;
}
inline bool operator!=(const time_t& tThis, const Date& other)
{
    Date This{tThis};
    return This != other;
}
inline bool operator<(const time_t& tThis, const Date& other)
{
    Date This{tThis};
    return This < other;
}
inline bool operator<=(const time_t& tThis, const Date& other)
{
    Date This{tThis};
    return This <= other;
}
inline bool operator>(const time_t& tThis, const Date& other)
{
    Date This{tThis};
    return This > other;
}
inline bool operator>=(const time_t& tThis, const Date& other)
{
    Date This{tThis};
    return This >= other;
}

inline bool operator==(const time_t& tThis, const Time& other)
{
    Time This{tThis};
    return This == other;
}
inline bool operator!=(const time_t& tThis, const Time& other)
{
    Time This{tThis};
    return This != other;
}
inline bool operator<(const time_t& tThis, const Time& other)
{
    Time This{tThis};
    return This < other;
}
inline bool operator<=(const time_t& tThis, const Time& other)
{
    Time This{tThis};
    return This <= other;
}
inline bool operator>(const time_t& tThis, const Time& other)
{
    Time This{tThis};
    return This > other;
}
inline bool operator>=(const time_t& tThis, const Time& other)
{
    Time This{tThis};
    return This >= other;
}

constexpr bool operator==(const struct tm& tThis, const DateTime& other)
{
    DateTime This{tThis};
    return This == other;
}
constexpr bool operator!=(const struct tm& tThis, const DateTime& other)
{
    DateTime This{tThis};
    return This != other;
}
constexpr bool operator<(const struct tm& tThis, const DateTime& other)
{
    DateTime This{tThis};
    return This < other;
}
constexpr bool operator<=(const struct tm& tThis, const DateTime& other)
{
    DateTime This{tThis};
    return This <= other;
}
constexpr bool operator>(const struct tm& tThis, const DateTime& other)
{
    DateTime This{tThis};
    return This > other;
}
constexpr bool operator>=(const struct tm& tThis, const DateTime& other)
{
    DateTime This{tThis};
    return This >= other;
}

constexpr bool operator==(const struct tm& tThis, const Date& other)
{
    Date This{tThis};
    return This == other;
}
constexpr bool operator!=(const struct tm& tThis, const Date& other)
{
    Date This{tThis};
    return This != other;
}
constexpr bool operator<(const struct tm& tThis, const Date& other)
{
    Date This{tThis};
    return This < other;
}
constexpr bool operator<=(const struct tm& tThis, const Date& other)
{
    Date This{tThis};
    return This <= other;
}
constexpr bool operator>(const struct tm& tThis, const Date& other)
{
    Date This{tThis};
    return This > other;
}
constexpr bool operator>=(const struct tm& tThis, const Date& other)
{
    Date This{tThis};
    return This >= other;
}

constexpr bool operator==(const struct tm& tThis, const Time& other)
{
    Time This{tThis};
    return This == other;
}
constexpr bool operator!=(const struct tm& tThis, const Time& other)
{
    Time This{tThis};
    return This != other;
}
constexpr bool operator<(const struct tm& tThis, const Time& other)
{
    Time This{tThis};
    return This < other;
}
constexpr bool operator<=(const struct tm& tThis, const Time& other)
{
    Time This{tThis};
    return This <= other;
}
constexpr bool operator>(const struct tm& tThis, const Time& other)
{
    Time This{tThis};
    return This > other;
}
constexpr bool operator>=(const struct tm& tThis, const Time& other)
{
    Time This{tThis};
    return This >= other;
}

#endif
