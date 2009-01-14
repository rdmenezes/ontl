/**\file*********************************************************************
 *                                                                     \brief
 *  20.5 Metaprogramming and type traits [meta]
 *  C++ builder version
 ****************************************************************************
 */

#ifndef STLX_TYPE_TRAITS_BCB
#define STLX_TYPE_TRAITS_BCB

#ifndef NTL__IN_STLX_TYPE_TRAITS
  #error Always include this file through <type_traits>.
#endif

namespace stlx {

// 20.5.5 Relationships between types [meta.rel]

template <class T, class U> struct is_same : false_type {};
template <class T> struct is_same<T, T> : true_type {};

template <class Base, class Derived> struct is_base_of
: public integral_constant<bool, __is_base_of(Base, Derived)> {};

template <class From, class To> struct is_convertible
: public integral_constant<bool, __is_convertible(From, To)> {};


// 20.5.6 Transformations between types [meta.trans]

// 20.5.6.1 Const-volatile modifications [meta.trans.cv]

template <class T> struct remove_const              { typedef T type; };
template <class T> struct remove_const<const T>     { typedef T type; };

template <class T> struct remove_volatile             { typedef T type; };
template <class T> struct remove_volatile<volatile T> { typedef T type; };

template <class T> struct remove_cv                   { typedef T type; };
template <class T> struct remove_cv<const T>          { typedef T type; };
template <class T> struct remove_cv<volatile T>       { typedef T type; };
template <class T> struct remove_cv<volatile const T> { typedef T type; };

template <class T> struct add_const           { typedef const T type; };

template <class T> struct add_volatile  { typedef volatile T type; };

template <class T> struct add_cv { typedef const volatile T type; };

// 20.5.6.2 Reference modifications [meta.trans.ref]

template <class T> struct remove_reference     { typedef T type; };
template <class T> struct remove_reference<T&> { typedef T type; };
#ifdef NTL__CXX_RV
template <class T> struct remove_reference<T&&> { typedef T type; };
#endif

template <class T> struct add_lvalue_reference     { typedef T& type; };
template <class T> struct add_lvalue_reference<T&> { typedef T& type; };

template <class T> struct add_reference : add_lvalue_reference<T> {};

// 20.5.6.3 Sign modifications [meta.trans.sign]
template <class T> struct make_signed;
template <class T> struct make_unsigned;

// 20.5.6.4 Array modifications [meta.trans.arr]

template <class T> struct remove_extent { typedef T type; };
template <class T, size_t Size> struct remove_extent<T[Size]> { typedef T type; };
template <class T, size_t Size> struct remove_extent<const T[Size]> { typedef const T type; };
template <class T, size_t Size> struct remove_extent<volatile T[Size]> { typedef volatile T type; };
template <class T, size_t Size> struct remove_extent<const volatile T[Size]> { typedef const volatile T type; };
////
template <class T> struct remove_all_extents { typedef T type; };
//template <class T> struct remove_all_extents<T[]>
//  { typedef typename remove_all_extents<T>::type type; };
template <class T, size_t Size> struct remove_all_extents<T[Size]>
  { typedef typename remove_all_extents<T>::type type; };

//
// 20.5.6.5 Pointer modifications [meta.trans.ptr]

template <class T> struct remove_pointer     { typedef T type; };
template <class T> struct remove_pointer<T*> { typedef T type; };

template <class T> struct add_pointer     { typedef T* type; };
template <class T> struct add_pointer<T&> { typedef typename remove_reference<T>::type* type; };

// 20.5.7 Other transformations [meta.trans.other]

namespace __ { namespace aux {
#define _FITS(ty) Align == alignof(ty)
#define _NEXT_ALIGN(ty) typedef typename _Aligned<_Len, Align, ty, _FITS(ty)>::_Type _Type

template<class _Ty, size_t _Len> union _Align_type
  { // union with size _Len bytes and alignment of _Ty
  _Ty _Val;
  char _Pad[_Len];
  };

template<size_t _Len, size_t Align, class _Ty, bool _Ok>
  struct _Aligned;
template<size_t _Len, size_t Align, class _Ty>
  struct _Aligned<_Len, Align, _Ty, true>
  { // define type with size _Len and alignment _Ty
  typedef _Align_type<_Ty, _Len> _Type;
  };
template<size_t _Len, size_t Align>
  struct _Aligned<_Len, Align, long, false>
  { // define type with size _Len and alignment _Ty
  typedef _Align_type<double, _Len> _Type;
  };
template<size_t _Len, size_t Align>
  struct _Aligned<_Len, Align, int, false>
  { // define type with size _Len and alignment _Ty
  _NEXT_ALIGN(long);
  };
template<size_t _Len, size_t Align>
  struct _Aligned<_Len, Align, short, false>
  { // define type with size _Len and alignment _Ty
  _NEXT_ALIGN(int);
  };
template<size_t _Len, size_t Align>
  struct _Aligned<_Len, Align, char, false>
  { // define type with size _Len and alignment _Ty
  _NEXT_ALIGN(short);
  };
#undef _NEXT_ALIGN
}} // __

template <stlx::size_t Len, stlx::size_t Align>
struct aligned_storage
{
  typedef typename __::aux::_Aligned<Len, Align, char, _FITS(char)>::_Type type;
};
#undef _FITS

////
template <class T> struct decay;

template <bool, class T = void> struct enable_if {};
template <class T> struct enable_if<true, T> { typedef T type; };

template <bool, class IfTrueType, class IfFalseType> struct conditional;
template <class T, class F> struct conditional<true, T, F>  { typedef T type; };
template <class T, class F> struct conditional<false, T, F> { typedef F type; };

namespace __
{
  // static logical operators: OR and AND
  // usage:
  // select_or<condition1, condition2, TrueType, FalseType>::type is equal to "if(condition1 || condition2) TrueType; else FalseType;
  // select_and works same, but with the "&&" operation.

  template<bool cond1, bool cond2,
  class IfTrueType, class IfFalseType>
  struct select_or
  { typedef IfFalseType type; };

  template<bool cond2, class T, class F>
  struct select_or<true, cond2, T, F>
  { typedef T type; };

  template<bool cond1, class T, class F>
  struct select_or<cond1, true, T, F>
  { typedef T type; };

  template<class T, class F>
  struct select_or<true, true, T, F>
  { typedef T type; };

  template<bool cond1, bool cond2,
  class IfTrueType, class IfFalseType>
  struct select_and
  { typedef IfFalseType type; };

  template<class T, class F>
  struct select_and<true, true, T, F>
  { typedef T type; };
}

// 20.5.4 Unary Type Traits [meta.unary]

#define STLX_DEF_TRAIT(trait)\
  template <class T> struct trait : public integral_constant<bool, __##trait(T)> {};
#define STLX_DEF_TRAIT2(trait,builtin_trait)\
  template <class T> struct trait : public integral_constant<bool, __##builtin_trait(T)> {};

// 20.5.4.1 Primary Type Categories [meta.unary.cat]
STLX_DEF_TRAIT(is_void)

STLX_DEF_TRAIT(is_integral)

STLX_DEF_TRAIT(is_floating_point)

STLX_DEF_TRAIT(is_array)

STLX_DEF_TRAIT(is_pointer)

STLX_DEF_TRAIT(is_lvalue_reference)

STLX_DEF_TRAIT(is_rvalue_reference)

STLX_DEF_TRAIT(is_member_object_pointer)
STLX_DEF_TRAIT(is_member_function_pointer)

namespace test__impl {
struct has_members
{
  //int m;
  //void f(int);
          };
}//namespace test__impl

STLX_DEF_TRAIT(is_enum)

STLX_DEF_TRAIT(is_union)

STLX_DEF_TRAIT(is_class)

STLX_DEF_TRAIT(is_function)

// decay implementation
template <class T> struct decay
{
  private: typedef typename remove_reference<T>::type U;
  public:  typedef
    typename conditional<is_array<U>::value,
                          typename remove_extent<U>::type*,
                          typename conditional<is_function<U>::value,
                                                typename add_pointer<U>::type,
                                                typename remove_cv<U>::type
                                              >::type
                        >::type   type;
};


// 20.5.4.2 Composite type traits [meta.unary.comp]

STLX_DEF_TRAIT(is_reference)

STLX_DEF_TRAIT(is_arithmetic)

STLX_DEF_TRAIT(is_fundamental)

STLX_DEF_TRAIT(is_object)

STLX_DEF_TRAIT(is_member_pointer)

STLX_DEF_TRAIT(is_scalar)

STLX_DEF_TRAIT(is_compound)

// 20.5.4.3 Type properties [meta.unary.prop]

STLX_DEF_TRAIT(is_const)

STLX_DEF_TRAIT(is_volatile)

STLX_DEF_TRAIT(is_trivial);
STLX_DEF_TRAIT(is_standard_layout);

STLX_DEF_TRAIT(is_pod)

STLX_DEF_TRAIT(is_empty)

STLX_DEF_TRAIT(is_polymorphic)

STLX_DEF_TRAIT(is_abstract)

STLX_DEF_TRAIT(has_trivial_default_constructor)

STLX_DEF_TRAIT(has_trivial_copy_constructor)

STLX_DEF_TRAIT(has_trivial_assign)

STLX_DEF_TRAIT(has_trivial_destructor)

STLX_DEF_TRAIT(has_nothrow_default_constructor)

STLX_DEF_TRAIT(has_nothrow_copy_constructor)

STLX_DEF_TRAIT(has_nothrow_assign)

STLX_DEF_TRAIT(has_virtual_destructor)

STLX_DEF_TRAIT(is_signed)

STLX_DEF_TRAIT(is_unsigned)

namespace __ { namespace aux {
  template<typename T> struct Alignof_wrap { static const size_t value = alignof(T); };

  template<size_t N> struct Alignof_wrap2 {
    typedef integral_constant<size_t, N> type;
  };
}}
template <class T> struct alignment_of: __::aux::Alignof_wrap2<__::aux::Alignof_wrap<T>::value>::type {};
template<> struct alignment_of<void>: integral_constant<size_t, 0>{};

STLX_DEF_TRAIT2(rank, array_rank)
//
template <class T, unsigned I = 0> struct extent: public integral_constant<size_t, __array_extent(T, I)> {};


// 20.5.7.2 Other transformations [meta.trans.other]
#ifdef NTL__CXX_VT

template <class ...T> struct common_type;

template <class T>
struct common_type<T> { typedef T type; };

template <class T, class U>
struct common_type<T, U>
{
private:
  static T&& __t();
  static U&& __u();
public:
  typedef decltype(true ? __t() : __u()) type;
};

template <class T, class U, class... V>
struct common_type<T, U, V...>
{
  typedef typename common_type<typename common_type<T, U>::type, V...>::type type;
};

#else // NTL__CXX_VT

template<class T, class U = void, class V = void, class W = void>
struct common_type;

template <class T>
struct common_type<T, void, void, void>
{
  static_assert(sizeof(T) > 0, "T shall be complete");
  typedef T type;
};

template<class T, class U>
struct common_type<T, U, void, void>
{
  static_assert(sizeof(T) > 0, "T shall be complete");
  static_assert(sizeof(T) > 0, "U shall be complete");

private:
  typedef typename remove_cv<typename remove_reference<T>::type>::type rawT;
  typedef typename remove_cv<typename remove_reference<U>::type>::type rawU;

public:
  /**
   *  rules of selecting the "common" type
   *  1) if raw types (without qualificators) are equal, then select one of them, also raw (don't sure here)
   *  2) if one of types is convertible to other, select other type
   *  3) else place the void
   **/
  typedef
    typename conditional<is_same<rawT, rawU>::value, rawT,
      typename conditional<is_arithmetic<rawT>::value && is_arithmetic<rawU>::value, typename conditional<(sizeof(T) < sizeof(U)), rawU, rawT>::type,
        typename conditional<is_convertible<rawT,rawU>::value, rawU,
          typename conditional<is_convertible<rawU,rawT>::value, rawT, void>::type
                            >::type>::type>::type type;
};

template<class T, class U, class V>
struct common_type<T, U, V, void>
{
  typedef typename common_type<typename common_type<T, U>::type, V>::type type;
};

template<class T, class U, class V, class W>
struct common_type
{
  typedef typename common_type<typename common_type<T, U, V>::type, W>::type type;
};

#endif

}//namespace stlx

#endif//#ifndef STLX_TYPE_TRAITS_BCB
