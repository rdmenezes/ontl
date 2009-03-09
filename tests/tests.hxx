#ifndef STLX_TESTS_HXX
#define STLX_TESTS_HXX
// common tests part

// set to 1 to check compile-time errors
#ifndef CT_FAIL
#define CT_FAIL 0
#endif

#ifndef __GNUC__
#define __attribute__(x)
#endif
#ifdef _MSC_VER
#pragma once
#pragma warning(disable:4101 4127 4189 4512)
#endif

#include <tut/tut.hpp>

#define quick_ensure2(cond,line) ensure("'"#cond"' at '"__FILE__":"#line"'", cond)
#define quick_ensure1(cond,line) quick_ensure2(cond, line)
#define quick_ensure(cond) quick_ensure1(cond, __LINE__)

namespace
{
  // unique for each test file
  struct empty_type{};
}

// default test group
#define STLX_DEFAULT_TESTGROUP() \
  typedef test_group<empty_type> testgroup; \
  typedef testgroup::object to;

// specify type to test, e.g. stlx::string or stlx::vector<int>
#define STLX_DEFINE_TESTGROUP(class) \
  typedef test_group< class > testgroup; \
  typedef testgroup::object to;

#endif // STLX_TESTS_HXX