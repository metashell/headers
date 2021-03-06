//  (C) Copyright Steve Cleary, Beman Dawes, Howard Hinnant & John Maddock 2000.
//  Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  See http://www.boost.org for most recent version including documentation.
//
//  defines object traits classes:
//  is_object, is_scalar, is_class, is_compound, is_POD, 
//  has_trivial_constructor, has_trivial_copy, has_trivial_assign, 
//  has_trivial_destructor, is_empty.
//

#ifndef BOOST_OBJECT_TYPE_TRAITS_HPP
#define BOOST_OBJECT_TYPE_TRAITS_HPP

#ifndef BOOST_ICE_TYPE_TRAITS_HPP
#include <boost/type_traits/ice.hpp>
#endif
#ifndef BOOST_FWD_TYPE_TRAITS_HPP
#include <boost/type_traits/fwd.hpp>
#endif
#ifndef BOOST_COMPOSITE_TYPE_TRAITS_HPP
#include <boost/type_traits/composite_traits.hpp>
#endif
#ifndef BOOST_ARITHMETIC_TYPE_TRAITS_HPP
#include <boost/type_traits/arithmetic_traits.hpp>
#endif
#ifndef BOOST_FUNCTION_TYPE_TRAITS_HPP
#include <boost/type_traits/function_traits.hpp>
#endif

namespace boost{

/**********************************************
 *
 * is_object
 *
 **********************************************/
template <typename T>
struct is_object
{
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
   BOOST_STATIC_CONSTANT(bool, value =
      (::boost::type_traits::ice_and<
         ::boost::type_traits::ice_not< ::boost::is_reference<T>::value>::value,
         ::boost::type_traits::ice_not< ::boost::is_void<T>::value>::value,
         ::boost::type_traits::ice_not< ::boost::is_function<T>::value>::value
      >::value));
#else
   BOOST_STATIC_CONSTANT(bool, value =
      (::boost::type_traits::ice_and<
         ::boost::type_traits::ice_not< ::boost::is_reference<T>::value>::value,
         ::boost::type_traits::ice_not< ::boost::is_void<T>::value>::value
      >::value));
#endif
};

/**********************************************
 *
 * is_scalar
 *
 **********************************************/
template <typename T>
struct is_scalar
{ 
   BOOST_STATIC_CONSTANT(bool, value =
      (::boost::type_traits::ice_or<
         ::boost::is_arithmetic<T>::value,
         ::boost::is_enum<T>::value,
         ::boost::is_pointer<T>::value,
         ::boost::is_member_pointer<T>::value
      >::value));
};

/**********************************************
 *
 * is_class
 *
 **********************************************/
template <typename T>
struct is_class
{
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
   BOOST_STATIC_CONSTANT(bool, value =
      (::boost::type_traits::ice_and<
         ::boost::type_traits::ice_not< ::boost::is_union<T>::value >::value,
         ::boost::type_traits::ice_not< ::boost::is_scalar<T>::value >::value,
         ::boost::type_traits::ice_not< ::boost::is_array<T>::value >::value,
         ::boost::type_traits::ice_not< ::boost::is_reference<T>::value>::value,
         ::boost::type_traits::ice_not< ::boost::is_void<T>::value >::value,
         ::boost::type_traits::ice_not< ::boost::is_function<T>::value >::value
      >::value));
#else
   BOOST_STATIC_CONSTANT(bool, value =
      (::boost::type_traits::ice_and<
         ::boost::type_traits::ice_not< ::boost::is_union<T>::value >::value,
         ::boost::type_traits::ice_not< ::boost::is_scalar<T>::value >::value,
         ::boost::type_traits::ice_not< ::boost::is_array<T>::value >::value,
         ::boost::type_traits::ice_not< ::boost::is_reference<T>::value>::value,
         ::boost::type_traits::ice_not< ::boost::is_void<T>::value >::value
      >::value));
#endif
};

/**********************************************
 *
 * is_compound
 *
 **********************************************/
template <typename T> struct is_compound
{
   BOOST_STATIC_CONSTANT(bool, value =
      (::boost::type_traits::ice_or<
         ::boost::is_array<T>::value,
         ::boost::is_pointer<T>::value,
         ::boost::is_reference<T>::value,
         ::boost::is_class<T>::value,
         ::boost::is_union<T>::value,
         ::boost::is_enum<T>::value,
         ::boost::is_member_pointer<T>::value
      >::value));
};

/**********************************************
 *
 * is_POD
 *
 **********************************************/
template <typename T> struct is_POD
{ 
   BOOST_STATIC_CONSTANT(bool, value =
      (::boost::type_traits::ice_or<
         ::boost::is_scalar<T>::value,
         ::boost::is_void<T>::value,
         BOOST_IS_POD(T)
      >::value));
};
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
template <typename T, std::size_t sz>
struct is_POD<T[sz]>
{
   BOOST_STATIC_CONSTANT(bool, value = ::boost::is_POD<T>::value);
};
#endif

/**********************************************
 *
 * has_trivial_constructor
 *
 **********************************************/
template <typename T>
struct has_trivial_constructor
{
   BOOST_STATIC_CONSTANT(bool, value =
      (::boost::type_traits::ice_or<
         ::boost::is_POD<T>::value,
         BOOST_HAS_TRIVIAL_CONSTRUCTOR(T)
      >::value));
};

/**********************************************
 *
 * has_trivial_copy
 *
 **********************************************/
template <typename T>
struct has_trivial_copy
{
   BOOST_STATIC_CONSTANT(bool, value =
      (::boost::type_traits::ice_and<
         ::boost::type_traits::ice_or<
            ::boost::is_POD<T>::value,
            BOOST_HAS_TRIVIAL_COPY(T)
         >::value,
      ::boost::type_traits::ice_not< ::boost::is_volatile<T>::value >::value
      >::value));
};

/**********************************************
 *
 * has_trivial_assign
 *
 **********************************************/
template <typename T>
struct has_trivial_assign
{
   BOOST_STATIC_CONSTANT(bool, value =
      (::boost::type_traits::ice_and<
         ::boost::type_traits::ice_or<
            ::boost::is_POD<T>::value,
            BOOST_HAS_TRIVIAL_ASSIGN(T)
         >::value,
      ::boost::type_traits::ice_not< ::boost::is_const<T>::value >::value,
      ::boost::type_traits::ice_not< ::boost::is_volatile<T>::value >::value
      >::value));
};

/**********************************************
 *
 * has_trivial_destructor
 *
 **********************************************/
template <typename T>
struct has_trivial_destructor
{
   BOOST_STATIC_CONSTANT(bool, value =
      (::boost::type_traits::ice_or<
         ::boost::is_POD<T>::value,
         BOOST_HAS_TRIVIAL_DESTRUCTOR(T)
      >::value));
};

/**********************************************
 *
 * is_empty
 *
 **********************************************/
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
namespace detail{

template <typename T>
struct empty_helper_t1 : public T
{
#ifdef __MWERKS__
   empty_helper_t1();  // hh compiler bug workaround
#endif
   int i[256];
};
struct empty_helper_t2 { int i[256]; };

template <typename T, bool b, bool b2>
struct empty_helper{ BOOST_STATIC_CONSTANT(bool, value = false); };

template <typename T>
struct empty_helper<T, true, false>
{
   BOOST_STATIC_CONSTANT(bool, value =
      (sizeof(empty_helper_t1<T>) == sizeof(empty_helper_t2)));
};
}

template <typename T>
struct is_empty
{
private:
   typedef typename remove_cv<T>::type cvt;
   typedef typename add_reference<T>::type r_type;
public:
   BOOST_STATIC_CONSTANT(bool, value =
      (::boost::type_traits::ice_or<
         ::boost::detail::empty_helper<T,
            ::boost::is_class<T>::value ,
            ::boost::is_convertible< r_type,int>::value
         >::value,
         BOOST_IS_EMPTY(cvt)
      >::value));
};

#else // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#if defined(BOOST_MSVC6_MEMBER_TEMPLATES) || !defined(BOOST_NO_MEMBER_TEMPLATES)

namespace detail{

template <typename T>
struct empty_helper_t1 : public T
{
   int i[256];
};
struct empty_helper_t2 { int i[256]; };

template <typename T>
struct empty_helper_base
{
   enum{ value = (sizeof(empty_helper_t1<T>) == sizeof(empty_helper_t2)) };
};

template <typename T>
struct empty_helper_nonbase
{
   enum{ value = false };
};

template <bool base>
struct empty_helper_chooser
{
   template <class T>
   struct rebind
   {
      typedef empty_helper_nonbase<T> type;
   };
};

template <>
struct empty_helper_chooser<true>
{
   template <class T>
   struct rebind
   {
      typedef empty_helper_base<T> type;
   };
};

} // namespace detail

template <typename T> 
struct is_empty
{ 
private:
   typedef ::boost::detail::empty_helper_chooser<
      ::boost::type_traits::ice_and<
         ::boost::type_traits::ice_not< 
            ::boost::is_reference<T>::value>::value,
         ::boost::type_traits::ice_not< 
            ::boost::is_convertible<T,double>::value>::value,
         ::boost::type_traits::ice_not< 
            ::boost::is_pointer<T>::value>::value,
         ::boost::type_traits::ice_not< 
            ::boost::is_member_pointer<T>::value>::value,
         ::boost::type_traits::ice_not< 
            ::boost::is_array<T>::value>::value,
         ::boost::type_traits::ice_not< 
            ::boost::is_void<T>::value>::value,
         ::boost::type_traits::ice_not< 
            ::boost::is_convertible<T, const volatile void*>::value>::value
      >::value> chooser;
   typedef typename chooser::template rebind<T> bound_type;
   typedef typename bound_type::type eh_type;
public:
   BOOST_STATIC_CONSTANT(bool, value =
      (::boost::type_traits::ice_or<eh_type::value, BOOST_IS_EMPTY(T)>::value)); 
};

#else
template <typename T> struct is_empty
{ enum{ value = BOOST_IS_EMPTY(T) }; };
#endif  // defined(BOOST_MSVC6_MEMBER_TEMPLATES) || !defined(BOOST_NO_MEMBER_TEMPLATES)

#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

} // namespace boost

#endif // BOOST_OBJECT_TYPE_TRAITS_HPP






