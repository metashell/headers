#ifndef BOOST_PREPROCESSOR_ENUM_PARAMS_WITH_A_DEFAULT_HPP
#define BOOST_PREPROCESSOR_ENUM_PARAMS_WITH_A_DEFAULT_HPP

/* Copyright (C) 2001
 * Housemarque Oy
 * http://www.housemarque.com
 *
 * Permission to copy, use, modify, sell and distribute this software is
 * granted provided this copyright notice appears in all copies. This
 * software is provided "as is" without express or implied warranty, and
 * with no claim as to its suitability for any purpose.
 *
 * See http://www.boost.org for most recent version.
 */

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/enum.hpp>

/** <p>Generates a comma separated list of parameters with a default.</p>

<p>In other words, expands to the sequence:</p>

<pre>
  BOOST_PP_CAT(P,0) = D, BOOST_PP_CAT(P,1) = D, ..., BOOST_PP_CAT(P,BOOST_PP_DEC(N)) = D
</pre>

<h3>Uses</h3>
<ul>
  <li>BOOST_PP_REPEAT()</li>
</ul>

<h3>Test</h3>
<ul>
  <li><a href="../../test/repeat_test.cpp">repeat_test.cpp</a></li>
</ul>
*/
#define BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(N,P,D) BOOST_PP_ENUM(N,BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT_F,(P,D))

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#if !defined(BOOST_NO_COMPILER_CONFIG) && defined(__MWERKS__) && __MWERKS__ <= 0x2406
#  define BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT_F(I,PD) BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(2,0,PD),I)=BOOST_PP_TUPLE_ELEM(2,1,PD)
#else
#  define BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT_F(I,PD) BOOST_PP_CAT(BOOST_PP_TUPLE2_ELEM0 PD,I)=BOOST_PP_TUPLE2_ELEM1 PD
#endif
#endif

/** <p>Obsolete. Use BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT().</p> */
#define BOOST_PREPROCESSOR_ENUM_PARAMS_WITH_A_DEFAULT(N,P,D) BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(N,P,D)
#endif
