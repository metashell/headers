//  boost sinhc.hpp header file

//  (C) Copyright Hubert Holin 2001. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

// See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_SINHC_HPP
#define BOOST_SINHC_HPP


#include <cmath>
#include <boost/limits.hpp>
#include <string>
#include <stdexcept>


// These are the the "Hyperbolic Sinus Cardinal" functions.

namespace boost
{
    namespace math
    {
#if defined(__GNUC__) && (__GNUC__ < 3)
        // gcc 2.x ignores function scope using declarations,
        // put them in the scope of the enclosing namespace instead:
        
        using    ::std::abs;
        using    ::std::sqrt;
        using    ::std::sinh;
        
        using    ::std::numeric_limits;
#endif
        
        // This is the "Hyperbolic Sinus Cardinal" of index Pi.
        
        template<typename T>
        inline T    sinhc_pi(const T x)
        {
            using    ::std::abs;
            using    ::std::sinh;
            using    ::std::sqrt;
            
            using    ::std::numeric_limits;
            
            static T const    taylor_0_bound = numeric_limits<T>::epsilon();
            static T const    taylor_2_bound = sqrt(taylor_0_bound);
            static T const    taylor_n_bound = sqrt(taylor_2_bound);
            
            if    (abs(x) >= taylor_n_bound)
            {
                return(sinh(x)/x);
            }
            else
            {
                // approximation by taylor series in x at 0 up to order 0
                T    result = static_cast<T>(1);
                
                if    (abs(x) >= taylor_0_bound)
                {
                    T    x2 = x*x;
                    
                    // approximation by taylor series in x at 0 up to order 2
                    result += x2/static_cast<T>(6);
                    
                    if    (abs(x) >= taylor_2_bound)
                    {
                        // approximation by taylor series in x at 0 up to order 4
                        result += (x2*x2)/static_cast<T>(120);
                    }
                }
                
                return(result);
            }
        }
        
        
        template<typename T, template<typename> class U>
        inline U<T>    sinhc_pi(const U<T> x)
        {
            using    ::std::abs;
            using    ::std::sinh;
            using    ::std::sqrt;
            
            using    ::std::numeric_limits;
            
            static T const    taylor_0_bound = numeric_limits<T>::epsilon();
            static T const    taylor_2_bound = sqrt(taylor_0_bound);
            static T const    taylor_n_bound = sqrt(taylor_2_bound);
            
            if    (abs(x) >= taylor_n_bound)
            {
                return(sinh(x)/x);
            }
            else
            {
                // approximation by taylor series in x at 0 up to order 0
                U<T>    result = static_cast< U<T> >(1);
                
                if    (abs(x) >= taylor_0_bound)
                {
                    U<T>    x2 = x*x;
                    
                    // approximation by taylor series in x at 0 up to order 2
                    result += x2/static_cast<T>(6);
                    
                    if    (abs(x) >= taylor_2_bound)
                    {
                        // approximation by taylor series in x at 0 up to order 4
                        result += (x2*x2)/static_cast<T>(120);
                    }
                }
                
                return(result);
            }
        }
    }
}

#endif /* BOOST_SINHC_HPP */
