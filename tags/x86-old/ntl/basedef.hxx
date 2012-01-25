/**\file*********************************************************************
 *                                                                     \brief
 *
 *
 ****************************************************************************
 */

#ifndef NTL__BASEDEF
#define NTL__BASEDEF

#include "cstddef"
#include "cstdint"
#include "vector"

/// NT Native Template Lybrary
namespace ntl {

/**\addtogroup  ntative_types ********** NT Native Types ********************
 *@{*/

///\name  Exact-width integer types
using std::int8_t;
using std::uint8_t;
using std::int16_t;
using std::uint16_t;
using std::int32_t;
using std::uint32_t;
using std::int64_t;
using std::uint64_t;

///\name  Integer types capable of holding object pointers
using std::intptr_t;
using std::uintptr_t;

using std::ptrdiff_t;

///\name  

typedef std::vector<uint8_t> raw_data;


// class_enum by remark
template<typename def>
struct class_enum : def
{
  typedef typename def::type type;

  __forceinline
  class_enum(type v) : value(v) {}

  __forceinline
  operator type () const {return value;}

  type value;
};


#define __class_enum(name) struct name ## _def; typedef class_enum<name ## _def> name; struct name ## _def { enum type

enum times
{
  nanoseconds   = 1,
  microseconds  = 10   * nanoseconds,
  milliseconds  = 1000 * microseconds,
  seconds       = 1000 * milliseconds,
  minutes       = 60   * seconds, 
//  hours         = int64_t(60)   * minutes,
//  days          = int64_t(24)   * hours,
};

///@}


}//namespace ntl

#endif//#ifndef NTL__BASEDEF