// Copyright 2011 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Basic time formatting methods.  These methods use the current locale
// formatting for displaying the time.

#ifndef BASE_I18N_TIME_FORMATTING_H_
#define BASE_I18N_TIME_FORMATTING_H_

#include <string>

#include "base/i18n/base_i18n_export.h"
#include "build/build_config.h"
#include "build/chromeos_buildflags.h"

#if BUILDFLAG(IS_CHROMEOS_ASH)
#include "third_party/icu/source/i18n/unicode/timezone.h"
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)

namespace base {

class Time;
class TimeDelta;

// Argument type used to specify the hour clock type.
enum HourClockType {
  k12HourClock,  // Uses 1-12. e.g., "3:07 PM"
  k24HourClock,  // Uses 0-23. e.g., "15:07"
};

// Argument type used to specify whether or not to include AM/PM sign.
enum AmPmClockType {
  kDropAmPm,  // Drops AM/PM sign. e.g., "3:07"
  kKeepAmPm,  // Keeps AM/PM sign. e.g., "3:07 PM"
};

// Should match UMeasureFormatWidth in measfmt.h; replicated here to avoid
// requiring third_party/icu dependencies with this file.
enum DurationFormatWidth {
  DURATION_WIDTH_WIDE,    // "3 hours, 7 minutes"
  DURATION_WIDTH_SHORT,   // "3 hr, 7 min"
  DURATION_WIDTH_NARROW,  // "3h 7m"
  DURATION_WIDTH_NUMERIC  // "3:07"
};

// Date formats from third_party/icu/source/i18n/unicode/udat.h. Add more as
// necessary.
enum DateFormat {
  // November 2007
  DATE_FORMAT_YEAR_MONTH,
  // Tuesday, 7 November
  DATE_FORMAT_MONTH_WEEKDAY_DAY,
};

// Returns the time of day, e.g., "3:07 PM".
BASE_I18N_EXPORT std::u16string TimeFormatTimeOfDay(const Time& time);

// Returns the time of day in 24-hour clock format with millisecond accuracy,
// e.g., "15:07:30.568"
BASE_I18N_EXPORT std::u16string TimeFormatTimeOfDayWithMilliseconds(
    const Time& time);

// Returns the time of day in the specified hour clock type. e.g.
// "3:07 PM" (type == k12HourClock, ampm == kKeepAmPm).
// "3:07"    (type == k12HourClock, ampm == kDropAmPm).
// "15:07"   (type == k24HourClock).
BASE_I18N_EXPORT std::u16string TimeFormatTimeOfDayWithHourClockType(
    const Time& time,
    HourClockType type,
    AmPmClockType ampm);

// Returns a shortened date, e.g. "Nov 7, 2007"
BASE_I18N_EXPORT std::u16string TimeFormatShortDate(const Time& time);

// Returns a numeric date such as 12/13/52.
BASE_I18N_EXPORT std::u16string TimeFormatShortDateNumeric(const Time& time);

// Returns a numeric date and time such as "12/13/52 2:44:30 PM".
BASE_I18N_EXPORT std::u16string TimeFormatShortDateAndTime(const Time& time);

#if BUILDFLAG(IS_CHROMEOS_ASH)
// Returns a month and year, e.g. "November 2007" for the specified time zone.
BASE_I18N_EXPORT std::u16string TimeFormatMonthAndYearForTimeZone(
    const Time& time,
    const icu::TimeZone* time_zone);
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)

// Returns a month and year, e.g. "November 2007"
BASE_I18N_EXPORT std::u16string TimeFormatMonthAndYear(const Time& time);

// Returns a numeric date and time with time zone such as
// "12/13/52 2:44:30 PM PST".
BASE_I18N_EXPORT std::u16string TimeFormatShortDateAndTimeWithTimeZone(
    const Time& time);

// Formats a time in a friendly sentence format, e.g.
// "Monday, March 6, 2008 2:44:30 PM".
BASE_I18N_EXPORT std::u16string TimeFormatFriendlyDateAndTime(const Time& time);

// Formats a time in a friendly sentence format, e.g.
// "Monday, March 6, 2008".
BASE_I18N_EXPORT std::u16string TimeFormatFriendlyDate(const Time& time);

// Formats a time using a skeleton to produce a format for different locales
// when an unusual time format is needed, e.g. "Feb. 2, 18:00".
//
// See http://userguide.icu-project.org/formatparse/datetime for details.
BASE_I18N_EXPORT std::u16string TimeFormatWithPattern(const Time& time,
                                                      const char* pattern);

// Formats a time duration of hours and minutes into various formats, e.g.,
// "3:07" or "3 hours, 7 minutes", and returns true on success. See
// DurationFormatWidth for details.
[[nodiscard]] BASE_I18N_EXPORT bool TimeDurationFormat(
    TimeDelta time,
    DurationFormatWidth width,
    std::u16string* out);

// Formats a time duration of hours, minutes and seconds into various formats,
// e.g., "3:07:30" or "3 hours, 7 minutes, 30 seconds", and returns true on
// success. See DurationFormatWidth for details.
[[nodiscard]] BASE_I18N_EXPORT bool TimeDurationFormatWithSeconds(
    TimeDelta time,
    DurationFormatWidth width,
    std::u16string* out);

// Formats a date interval into various formats, e.g. "2 December - 4 December"
// or "March 2016 - December 2016". See DateFormat for details.
BASE_I18N_EXPORT std::u16string DateIntervalFormat(const Time& begin_time,
                                                   const Time& end_time,
                                                   DateFormat format);

// Gets the hour clock type of the current locale. e.g.
// k12HourClock (en-US).
// k24HourClock (en-GB).
BASE_I18N_EXPORT HourClockType GetHourClockType();

}  // namespace base

#endif  // BASE_I18N_TIME_FORMATTING_H_
