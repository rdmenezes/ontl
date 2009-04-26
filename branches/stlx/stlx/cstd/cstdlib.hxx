/**\file*********************************************************************
 *                                                                     \brief
 *  C Library General utilities (ISO9899 7.20)
 *
 ****************************************************************************
 */

#ifndef STLX_CSTD_CSTDLIB
#define STLX_CSTD_CSTDLIB

#include "cstddef.hxx"
#include "cassert.hxx"

extern "C"
{
  typedef void __cdecl vfv_t(void);
  typedef int  __cdecl ifv_t(void);
  typedef void __cdecl vfi_t(int);

#ifndef _INC_STDLIB// MSVC compatibility

// ISO 9899
//

///\name  7.20.1 Numeric conversion functions

/// 7.20.1.1 The atof function
double
NTL__CRTCALL
  atof(const char *nptr);

/// 7.20.1.2 The atoi function
int
NTL__CRTCALL
  atoi(const char *nptr);

/// 7.20.1.2 The atol function
long int
NTL__CRTCALL
  atol(const char *nptr);

/// 7.20.1.3 The strtod function
double
NTL__CRTCALL
  strtod(const char * __restrict nptr, char ** __restrict endptr);

/// 7.20.1.4 The strtol function
long int
NTL__CRTCALL
  strtol(const char * __restrict nptr, char ** __restrict endptr, int base);

/// 7.20.1.4 The strtoul function
unsigned long int
NTL__CRTCALL
  strtoul(const char * __restrict nptr, char ** __restrict endptr, int base);

// C library extension
NTL__EXTERNAPI
char* _cdecl
  _itoa(int value, char* strbuf, int radix);

NTL__EXTERNAPI
wchar_t* _cdecl
  _itow(int value, wchar_t* strbuf, int radix);

///\name  7.20.2 Pseudo-random sequence generation functions

/// 7.20.2.1 The rand function
int
NTL__CRTCALL
  rand(void);

#ifndef RAND_MAX
#define RAND_MAX 0x7fff
#endif

//STATIC_ASSERT(RAND_MAX <= INT_MAX);

/// 7.20.2.2 The srand function
void
NTL__CRTCALL
  srand(unsigned int seed);


///\name  7.20.3 Memory management functions

/// 7.20.3.1 The calloc function
__noalias
void* __restrict 
NTL__CRTCALL
  calloc(size_t nmemb, size_t size);

/// 7.20.3.2 The free function
__noalias
void
NTL__CRTCALL
  free(void *ptr);

/// 7.20.3.3 The malloc function
__noalias
void* __restrict 
NTL__CRTCALL
  malloc(size_t size);

/// 7.20.3.4 The realloc function
__noalias
void* __restrict
NTL__CRTCALL
  realloc(void *ptr, size_t size);


///\name  7.20.4 Communication with the environment

/// 7.20.4.1 The abort function + 18.3/3
void
NTL__CRTCALL
  abort();

/// 7.20.4.2 The atexit function
int __cdecl atexit(vfv_t func);

#define EXIT_SUCCESS  0
#define EXIT_FAILURE  1

/// 7.20.4.3 The exit function
void
NTL__CRTCALL
  exit(int status);

/// 7.20.4.5 The getenv function
char *
NTL__CRTCALL
  getenv(const char *name);

/// 7.20.4.6 The system function
int
NTL__CRTCALL
  system(const char *string);


///\name  7.20.5 Searching and sorting utilities

/// 7.20.5.1 The bsearch function
void *
NTL__CRTCALL
  bsearch(const void *key, const void *base, size_t nmemb, size_t size,
              int (*compar)(const void *, const void *));

/// 7.20.5.2 The qsort function
void
NTL__CRTCALL
  qsort(void *base, size_t nmemb, size_t size,
           int (*compar)(const void *, const void *));


///\name  7.20.6 Integer arithmetic functions

/// 7.20.6.1 The abs, labs and llabs functions
int
NTL__CRTCALL
  abs(int j);

long int
NTL__CRTCALL
  labs(long int j);

#if 0
/// 7.20.6.2 The div, ldiv, and lldiv functions
div_t div(int numer, int denom);
ldiv_t ldiv(long int numer, long int denom);
lldiv_t lldiv(long long int numer, long long int denom);
#endif


///\name  7.20.7 Multibyte/wide character conversion functions

/// 7.20.7.1 The mblen function
int
NTL__CRTCALL
  mblen(const char *s, size_t n);

/// 7.20.7.2 The mbtowc function
int
NTL__CRTCALL
  mbtowc(wchar_t * __restrict pwc, const char * __restrict s, size_t n);

/// 7.20.7.3 The wctomb function
int
NTL__CRTCALL
  wctomb(char *s, wchar_t wc);


///\name  7.20.8 Multibyte/wide string conversion functions

/// 7.20.8.1 The mbstowcs function
size_t
NTL__CRTCALL
  mbstowcs(wchar_t * __restrict pwcs, const char * __restrict s, size_t n);

/// 7.20.8.2 The wcstombs function
size_t
NTL__CRTCALL
  wcstombs(char * __restrict s, const wchar_t * __restrict pwcs, size_t n);

#endif// #ifndef _INC_STDLIB

/// 7.20.1.2 The atoll function
long long int
NTL__CRTCALL
  atoll(const char *nptr);

/// 7.20.1.3 The strtof function
float
NTL__CRTCALL
  strtof(const char * __restrict nptr, char ** __restrict endptr);


/// 7.20.1.3 The strtold function
long double
NTL__CRTCALL
  strtold(const char * __restrict nptr, char ** __restrict endptr);

/// 7.20.1.4 The strtoll function
long long int
NTL__CRTCALL
  strtoll(const char * __restrict nptr, char ** __restrict endptr, int base);

/// 7.20.1.4 The strtoull function
unsigned long long int
NTL__CRTCALL
  strtoull(const char * __restrict nptr, char ** __restrict endptr, int base);

/// 7.20.4.4 The _Exit function
void
NTL__CRTCALL
  _Exit(int status);

long long int
NTL__CRTCALL
  llabs(long long int j);




//////////////////////////////////////////////////////////////////////////
/* c++ initializers */
extern vfv_t* __xc_a[];
extern vfv_t* __xc_z[];

}; // extern "C"
///@}

namespace ntl
{

  /**
   *	@brief C++ static initialization
   *	@param[in] init initialization or termination flag
   *  @sa crt_initializer
   *
   *  This function initializes and destroys the C++ static objects. It must be called before and after the main program code runs.
   *  For example:
   \code
   int main()
   {
      ntl::__init_crt(true);
      int ret_code = do_main_work();
      ntl::__init_crt(false);
      return ret_code;
   }
   \endcode
   **/
  extern "C" void _cdecl __init_crt(bool init);

  /**
   *	@brief C++ static initialization helper
   *
   *  This class helps to initialize the C++ static objects initialization and destruction. For usage see following code:
   *  @sa __init_crt
   \code
   int main()
   {
      ntl::crt_initializer __crt;
      return do_main_work();
   }
   \endcode
   **/
  struct crt_initializer
  {
    crt_initializer()
    {
      __init_crt(true);
    }
    ~crt_initializer()
    {
      __init_crt(false);
    }
  };
}


namespace stlx {

/**\addtogroup  lib_language_support *** 18 Language support library [language.support] ******
 *@{*/
/**\addtogroup  lib_support_start_term * 18.4 Start and termination [support.start.term] *******
 *@{*/


//extern "C"    int atexit(void (*f)(void));
//extern "C++"  int atexit(void (*f)(void));


/**@} lib_support_start_term
 */

/**\addtogroup  lib_general_utilities ** C Library filees [c.files  ] *******
 *@{*/

using ::atof;
using ::atoi;
using ::atol;
using ::atoll;
using ::strtod;
using ::strtof;
using ::strtold;
using ::strtol;
using ::strtoll;
using ::strtoul;
using ::strtoull;

using ::rand;
using ::srand;

using ::calloc;
using ::free;
using ::malloc;
using ::realloc;

using ::abort;
using ::atexit;
using ::exit;
using ::_Exit;

using ::getenv;
using ::system;

using::bsearch;
using::qsort;

using::abs;
using::labs;
using::llabs;

#if 0
using::div;
using::ldiv;
using::lldiv;
#endif

using::mblen;
using::mbtowc;
using::wctomb;

using::mbstowcs;
using::wcstombs;

/**@} lib_general_utilities
 */
/**@} lib_language_support */

}//namespace stlx

#endif//#ifndef STLX_CSTD_CSTDLIB