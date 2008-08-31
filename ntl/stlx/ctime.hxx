/**\file*********************************************************************
 *                                                                     \brief
 *  Integer types ISO9899: 7.18
 *
 ****************************************************************************
 */

#ifndef NTL__STLX_CTIME
#define NTL__STLX_CTIME

#include "cstddef.hxx"
#include "../nt/time.hxx"
#include "../nt/process_information.hxx"

namespace std {

/**\addtogroup  lib_utilities *** 20 General utilities library [utilities] **
 *@{*/
/**\addtogroup  lib_date_time *** 20.9 Date and time functions [date.time] **
 *@{*/

  // 100ns (10^-7)
#define CLOCKS_PER_SEC system_time_resolution

typedef ntl::nt::systime_t clock_t;
typedef ntl::nt::systime_t time_t;

/** Holds the components of a calendar time, called the broken-down time. */
struct tm
{ 
  /** seconds after the minute [0, 60] */
  int tm_sec;
  /** minutes after the hour [0, 59] */
  int tm_min;
  /** hours since midnight [0, 23] */
  int tm_hour;
  /** day of the month [1, 31] */
  int tm_mday;
  /** months since January [0, 11] */
  int tm_mon; 
  /** years since 1900 */
  int tm_year; 
  /** days since Sunday [0, 6] */
  int tm_wday; 
  /** days since January 1 [0, 365] */
  int tm_yday; 
  /** Daylight Saving Time flag */
  int tm_isdst; 
};

// Time manipulation functions

/**
 *	The clock function determines the processor time used.
 *
 *  @note Processor time can not be retrieved for the current process, therefore
 *  function returns amount of time elapsed from the program's start time.
 **/
inline clock_t clock(void) 
{
  // unfortunately the best solution for the current function's specification does not works:
  // we can't retrieve the current process times except for create time field.
  const ntl::nt::process_information<ntl::nt::kernel_user_times> process_times;
  return process_times ? (ntl::nt::query_system_time() - process_times->CreateTime) : clock_t(-1);
}

/**
 *	The difftime function computes the difference between two calendar times: time1 - time0.
 *  @return The difftime function returns the difference expressed in seconds as a double.
 **/
double difftime(time_t time1, time_t time0);

/**
 *	The mktime function converts the broken-down time, expressed as local time, in the
 *  structure pointed to by \c timeptr into a calendar time value with the same encoding as
 *  that of the values returned by the time function.
 *
 *  @return The mktime function returns the specified calendar time encoded as a value of type
 *  time_t. If the calendar time cannot be represented, the function returns the value \c (time_t)(-1).
 **/
time_t mktime(const tm* timeptr);


/**
 *	The time function determines the current calendar time
 *  @return the time as seconds elapsed since midnight, January 1, 1970.
 **/
inline time_t time(time_t* timer = 0)
{
  // Number of 100 nanosecond units from 1/1/1601 to 1/1/1970
  static const int64_t epoch_bias = 116444736000000000i64;
  const ntl::nt::systime_t ntime = ntl::nt::query_system_time();
  const time_t ct = static_cast<time_t>((ntime - epoch_bias) / 10000000i64);
  if(timer)
    *timer = ct;
  return ct;
}


// Time conversion functions

/**
 *	The asctime function converts the broken-down time in the structure pointed to by
 *  \c timeptr into a string in the form\n
 *  \code Sun Sep 16 01:03:52 1973\n\0 \endcode
 *  @return The asctime function returns a pointer to the string.
 *  @note This function is not required to avoid data races.
 **/
char *asctime(const tm* timeptr);

/**
 *	The ctime function converts the calendar time pointed to by \c timer to local time in the
 *  form of a string. It is equivalent to
 *  \code asctime(localtime(timer)) \endcode
 *  @return The ctime function returns the pointer returned by the asctime function with that
 *  broken-down time as argument.
 *  @note This function is not required to avoid data races.
 **/
char *ctime(const time_t* timer);

/**
 *	The gmtime function converts the calendar time pointed to by \c timer into a broken-down time, expressed as UTC.
 *  @return The gmtime function returns a pointer to the broken-down time, or a null pointer if the
 *  specified time cannot be converted to UTC
 *  @note This function is not required to avoid data races.
 **/
tm *gmtime(const time_t* timer);

/**
 *	The localtime function converts the calendar time pointed to by \c timer into a
 *  broken-down time, expressed as local time.
 *  @return The localtime function returns a pointer to the broken-down time, or a null pointer if
 *  the specified time cannot be converted to local time.
 *  @note This function is not required to avoid data races.
 **/
tm *localtime(const time_t* timer);

/**
 *	The strftime function places characters into the array pointed to by s as controlled by the string pointed to by format. 
 **/
size_t strftime(char* s,
                size_t maxsize,
                const char* format,
                const tm* timeptr);

/**@} lib_date_time */
/**@} lib_utilities */

}//namespace std

#endif//#ifndef NTL__STLX_CTIME