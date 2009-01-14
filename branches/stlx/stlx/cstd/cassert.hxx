/**\file*********************************************************************
 *                                                                     \brief
 *  Assertions [lib.assertions 19.2]
 *
 ****************************************************************************
 */

#ifndef STLX_CSTD_CASSERT
#define STLX_CSTD_CASSERT

//namespace stlx {

#ifdef _DEBUG
#define NTL__DEBUG
#endif


#if defined NTL__DEBUG || !defined NDEBUG
#if defined(_MSC_VER)
#define __ntl_assert(__msg, __line)\
  { const char * volatile __assertion_failure; __assertion_failure = (__msg);\
    unsigned volatile __assertion_failure_at_line; __assertion_failure_at_line = (__line);\
    __debugbreak(); }
#elif defined(__BCPLUSPLUS__)
  NTL__EXTERNAPI void _stdcall DbgBreakPoint();
  #define __ntl_assert(__msg, __line) { DbgBreakPoint(); }
#elif defined(__GNUC__)
  #define __ntl_assert(__msg, __line) {  }
#endif // _MSC_VER
#endif


#ifdef NTL__DEBUG
  #define _Assert(expr) \
    if ( !!(expr) ); else \
    __ntl_assert("NTL Assertion ("#expr") failed in "__func__" //"__FILE__,__LINE__);\
    ((void)0)
#else
  #define _Assert(expr)
#endif

/// ISO C 7.2/1 The assert macro is redefined according to the current state
///             of NDEBUG each time that <assert.h> is included.
#undef assert
#ifdef NDEBUG
# ifdef _MSC_VER
  #define assert(expr)// (__assume(expr))
# else
  #define assert(expr) ((void)0)
# endif
#else
  #define assert(expr) \
    if ( !!(expr) ); else \
    __ntl_assert("Assertion ("#expr") failed in "__func__" //"__FILE__,__LINE__);\
    ((void)0)
#endif

//}//namespace stlx

#endif//#ifndef STLX_CSTD_CASSERT
