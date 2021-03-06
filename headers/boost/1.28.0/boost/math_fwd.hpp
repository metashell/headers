//  Boost math_fwd.hpp header file  ------------------------------------------//

//  (C) Copyright boost.org 2001.  Permission to copy, use, modify, sell
//  and distribute this software is granted provided this copyright
//  notice appears in all copies.  This software is provided "as is" without
//  express or implied warranty, and with no claim as to its suitability for
//  any purpose.

//  See http://www.boost.org for most recent version including documentation.

#ifndef BOOST_MATH_FWD_HPP
#define BOOST_MATH_FWD_HPP


namespace boost
{
namespace math
{


//  From <boost/math/quaternion.hpp>  ----------------------------------------//

template < typename T >
    class quaternion;

template < >
    class quaternion< float >;
template < >
    class quaternion< double >;
template < >
    class quaternion< long double >;

// Also has many function templates (including operators)


//  From <boost/math/octonion.hpp>  ------------------------------------------//

template < typename T >
    class octonion;

template < >
    class octonion< float >;
template < >
    class octonion< double >;
template < >
    class octonion< long double >;

// Also has many function templates (including operators)


//  From <boost/math/special_functions/acosh.hpp>  ---------------------------//

// Only has function template


//  From <boost/math/special_functions/asinh.hpp>  ---------------------------//

// Only has function template


//  From <boost/math/special_functions/atanh.hpp>  ---------------------------//

// Only has function template


//  From <boost/math/special_functions/sinc.hpp>  ----------------------------//

// Only has function templates


//  From <boost/math/special_functions/sinhc.hpp>  ---------------------------//

// Only has function templates


//  From <boost/math/common_factor.hpp>  -------------------------------------//

template < typename IntegerType >
    class gcd_evaluator;
template < typename IntegerType >
    class lcm_evaluator;

template < unsigned long Value1, unsigned long Value2 >
    struct static_gcd;
template < unsigned long Value1, unsigned long Value2 >
    struct static_lcm;

// Also has a couple of function templates


}  // namespace math
}  // namespace boost


#endif  // BOOST_MATH_FWD_HPP
