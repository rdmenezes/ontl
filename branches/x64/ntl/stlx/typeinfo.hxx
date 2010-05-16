/**\file*********************************************************************
 *                                                                     \brief
 *  18.7 Type identification [support.rtti]
 *
 ****************************************************************************
 */
#ifndef NTL__STLX_TYPEINFO
#define NTL__STLX_TYPEINFO
#pragma once

/**\addtogroup  lib_language_support *** 18 Language support library [language.support]
 * @{ */
/**\addtogroup  lib_support_rtti ******* 18.7 Type identification [support.rtti]
 * @{ */

#ifndef NTL__STLX_CSTRING
#include "cstring.hxx" // for std::strcmp
#endif
#ifndef NTL__STLX_EXCEPTION
#include "stdexception.hxx"
#endif

#pragma warning(push)
#pragma warning(disable:4820) // '3' bytes padding added after data member 'type_info::mname'

#if STLX__USE_RTTI
# define __ntl_typeid(T) typeid(T)
#else
# define __ntl_typeid(T) *reinterpret_cast<const std::type_info*>(0)
#endif

/**
 *	@brief 18.7.1 Class type_info [type.info] (N2857)
 *  @details The class type_info describes type information generated by the implementation. Objects of this class
 *  effectively store a pointer to a name for the type, and an encoded value suitable for comparing two types for
 *  equality or collating order.
 **/
class type_info
{
  public:

    /** type_info destructor */
    virtual ~type_info();

    /**
     *	@brief Compares the current object with \c rhs.
     *	@return true if the two values describe the same type.
     **/
    bool operator==(const type_info& rhs) const
    {
      return std::strcmp(mname()+1, rhs.mname()+1) == 0;
    }

    /**
     *	@brief Compares the current object with \c rhs.
     *	@return true if the two values describe the different types.
     **/
    bool operator!=(const type_info& rhs) const
    {
      return std::strcmp(mname()+1, rhs.mname()+1) != 0;
    }

    /**
     *	@brief Compares the current object with \c rhs.
     *	@return true if \c *this precedes \c rhs in the implementation's collation order.
     **/
    bool before(const type_info& rhs) const __ntl_nothrow
    {
      return std::strcmp(mname()+1, rhs.mname()+1) <= 0;
    }

    /** Hashes this object */
    size_t hash_code() const __ntl_nothrow
    {
      return reinterpret_cast<size_t>(this);
    }

    /**
     *	@brief Returns an implementation-defined NTBS.
     *	@return a null-terminated string representing the human-readable name of the type.
     **/
    const char* name() const  __ntl_nothrow
#ifndef _NTL_DEMANGLE
    {
      // return mangled name as implementation-defined :-)
      return mname(); 
    }
#else
    ;// use definition in rtti.cpp
#endif

  private:
    type_info(const type_info&) __deleted;
    type_info& operator=(const type_info&) __deleted;
    mutable void* data;
    const char* mname() const { return reinterpret_cast<const char*>(this + 1); }
};
#if defined(_MSC_VER) && !defined(__ICL)
///\warning break this to get `Unresolved external : const type_info::'vftable' (??_7type_info@@6B@)`
static_assert(sizeof _TypeDescriptor == sizeof type_info, "broken type");
#endif

#if (STLX__USE_RTTI || STLX__USE_EXCEPTIONS/*do we need another macro instead?*/) && !defined(__ICL)
inline type_info::~type_info()
{}
#endif
#pragma warning(pop)

/** @} lib_support_rtti */
/** @} lib_language_support */

namespace std
{
/**\addtogroup  lib_language_support *** 18 Language support library [language.support]
 * @{ */
/**\addtogroup  lib_support_rtti ******* 18.7 Type identification [support.rtti]
 * @{ */

/// 18.7.1 Class type_info [type.info] (N2960)
using ::type_info;

/// 18.7.3 Class bad_cast [bad.cast] (N2857)
class bad_cast:
  public exception
{
public:
  bad_cast() __ntl_nothrow
  {}
  bad_cast(const bad_cast&) __ntl_nothrow
  {}
  bad_cast& operator=(const bad_cast&) __ntl_nothrow
  { return *this; }
  ~bad_cast() __ntl_nothrow
  {}

  virtual const char* what() const __ntl_nothrow
  {
    return "bad_cast";
  }
};

/// 18.7.4 Class bad_typeid [bad.typeid] (N2857)
class bad_typeid:
  public exception
{
public:
  bad_typeid() __ntl_nothrow
  {}
  bad_typeid(const bad_typeid&) __ntl_nothrow
  {}
  bad_typeid& operator=(const bad_typeid&) __ntl_nothrow
  { return *this; }
  ~bad_typeid() __ntl_nothrow
  {}

  virtual const char* what() const __ntl_nothrow
  {
    return "bad_typeid";
  }
};

/** @} lib_support_rtti */
/** @} lib_language_support */
}//namespace std

#endif//#ifndef NTL__STLX_TYPEINFO
