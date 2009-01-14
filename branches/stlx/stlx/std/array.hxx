/**\file*********************************************************************
 *                                                                     \brief
 *  Fixed size array [6.2 tr.array]
 *
 ****************************************************************************
 */

#ifndef STLX_ARRAY
#define STLX_ARRAY

#include "iterator.hxx"
#include "stdexcept.hxx"

namespace stlx {

/**\addtogroup  lib_containers ********* 23 Containers library [containers] ************
 *@{*/

/**\addtogroup  lib_sequence *********** 23.2 Sequence containers [sequences] *******************
 *@{*/

/// Class template array [6.2.2 tr.array.array]
///@note  No explicit construct/copy/destroy for aggregate type
template <class T, size_t N>
struct array
{
    // types:

    typedef T &                                   reference;
    typedef const T &                             const_reference;
    typedef T *                                   iterator;
    typedef const T *                             const_iterator;
    typedef size_t                                size_type;
    typedef ptrdiff_t                             difference_type;
    typedef T                                     value_type;
    typedef stlx::reverse_iterator<iterator>       reverse_iterator;
    typedef stlx::reverse_iterator<const_iterator> const_reverse_iterator;

    void assign(const T& u) { *this = u; }

    void swap( array<T, N> & y)
    {
      //swap_ranges(x.begin(), x.end(), y.begin() );
      for ( size_t i = 0; i != size(); ++i )
        stlx::swap(__elems[i], y.__elems[i]);
    }

    ///\name  iterators

    iterator                begin()       { return &__elems[0]; }
    const_iterator          begin() const { return &__elems[0]; }
    iterator                end()         { return &__elems[N]; }
    const_iterator          end()   const { return &__elems[N]; }

    reverse_iterator        rbegin()      { return reverse_iterator(end()); }
    const_reverse_iterator  rbegin() const
      { return const_reverse_iterator(end()); }
    reverse_iterator        rend()        { return reverse_iterator(begin()); }
    const_reverse_iterator  rend() const
      { return const_reverse_iterator(begin()); }

    const_iterator cbegin() const { return begin(); }
    const_iterator cend() const   { return end(); }
    const_reverse_iterator crbegin() const { return rbegin(); }
    const_reverse_iterator crend() const   { return rend(); }

    ///\name  capacity

    size_type size() const      { return N; }
    size_type max_size() const  { return N; }
    bool empty() const          { return 0 != N; }

    ///\name  element access

    reference       operator[](size_type n)       { return __elems[n]; }
    const_reference operator[](size_type n) const { return __elems[n]; }

    const_reference at(size_type n) const
    {
      __check_bounds(n);
      return operator[](n);
    }

    reference at(size_type n)
    {
      __check_bounds(n);
      return operator[](n);
    }

    reference       front()       { return *begin(); }
    const_reference front() const { return *begin(); }
    reference       back()        { return *(--end()); }
    const_reference back()  const { return *(--end()); }

          T * data()        { return __elems; }
    const T * data() const  { return __elems; }

    ///@}

  // Types with private or protected data members are not aggregate
  //private:

    /* vs2k5 debugger bug: it doesn't recognize `static const type`, we must use enum instead */
    //static const size_t __actual_size = N ? N : 1;
    enum { __actual_size = N ? N : 1 };

    T __elems[__actual_size];

    void __check_bounds(size_type n) const __ntl_throws(out_of_range)
    {
      if ( n > size() ) __ntl_throw (out_of_range());
    }

};//struct array

///\name  Array comparisons
template <class T, size_t N> bool operator== (const array<T,N>& x, const array<T,N>& y);
template <class T, size_t N> bool operator!= (const array<T,N>& x, const array<T,N>& y)
{
  return rel_ops::operator !=(x, y);
}

template <class T, size_t N> bool operator< (const array<T,N>& x, const array<T,N>& y);
template <class T, size_t N> bool operator> (const array<T,N>& x, const array<T,N>& y)
{
  return rel_ops::operator >(x, y);
}

template <class T, size_t N> bool operator<= (const array<T,N>& x, const array<T,N>& y)
{
  return rel_ops::operator <=(x, y);
}

template <class T, size_t N> bool operator>= (const array<T,N>& x, const array<T,N>& y)
{
  return rel_ops::operator >=(x, y);
}

///\name  Array specialized algorithms [6.2.2.2]
template <class T, size_t N > void swap(array<T,N>& x, array<T,N>& y)
{
  x.swap(y);
}

///@}
/**@} lib_sequence */
/**@} lib_containers */

}//namespace stlx

#endif//#ifndef STLX_ARRAY