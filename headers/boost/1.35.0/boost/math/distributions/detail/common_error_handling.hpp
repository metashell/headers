// Copyright John Maddock 2006, 2007.
// Copyright Paul A. Bristow 2006, 2007.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_DISTRIBUTIONS_COMMON_ERROR_HANDLING_HPP
#define BOOST_MATH_DISTRIBUTIONS_COMMON_ERROR_HANDLING_HPP

#include <boost/math/policies/error_handling.hpp>
#include <boost/math/special_functions/fpclassify.hpp>
// using boost::math::isfinite;

namespace boost{ namespace math{ namespace detail
{

template <class RealType, class Policy>
inline bool check_probability(const char* function, RealType const& prob, RealType* result, const Policy& pol)
{
   if((prob < 0) || (prob > 1) || !(boost::math::isfinite)(prob))
   {
      *result = policies::raise_domain_error<RealType>(
         function,
         "Probability argument is %1%, but must be >= 0 and <= 1 !", prob, pol);
      return false;
   }
   return true;
}

template <class RealType, class Policy>
inline bool check_df(const char* function, RealType const& df, RealType* result, const Policy& pol)
{
   if((df <= 0) || !(boost::math::isfinite)(df))
   {
      *result = policies::raise_domain_error<RealType>(
         function,
         "Degrees of freedom argument is %1%, but must be > 0 !", df, pol);
      return false;
   }
   return true;
}

template <class RealType, class Policy>
inline bool check_scale(
      const char* function,
      RealType scale,
      RealType* result,
      const Policy& pol)
{
   if((scale <= 0) || !(boost::math::isfinite)(scale))
   { // Assume scale == 0 is NOT valid for any distribution.
      *result = policies::raise_domain_error<RealType>(
         function,
         "Scale parameter is %1%, but must be > 0 !", scale, pol);
      return false;
   }
   return true;
}

template <class RealType, class Policy>
inline bool check_location(
      const char* function,
      RealType location,
      RealType* result,
      const Policy& pol)
{
   if(!(boost::math::isfinite)(location))
   {
      *result = policies::raise_domain_error<RealType>(
         function,
         "Location parameter is %1%, but must be finite!", location, pol);
      return false;
   }
   return true;
}

template <class RealType, class Policy>
inline bool check_x(
      const char* function,
      RealType x,
      RealType* result,
      const Policy& pol)
{
   if(!(boost::math::isfinite)(x))
   {
      *result = policies::raise_domain_error<RealType>(
         function,
         "Random variate x is %1%, but must be finite!", x, pol);
      return false;
   }
   return true;
   // Note that this test catches both infinity and NaN.
   // Some special cases permit x to be infinite, so these must be tested 1st,
   // leaving this test to catch any NaNs.  see Normal and cauchy for example.
}

} // namespace detail
} // namespace math
} // namespace boost

#endif // BOOST_MATH_DISTRIBUTIONS_COMMON_ERROR_HANDLING_HPP
