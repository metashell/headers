#ifndef BOOST_PREPROCESSOR_TUPLE_ELEM_HPP
#define BOOST_PREPROCESSOR_TUPLE_ELEM_HPP

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

/** <p>Expands to the <code>I</code>:th element of an <code>N</code>-tuple.</p>

<p>For example,</p>

<pre>
  BOOST_PP_TUPLE_ELEM(2,1,(A,B))
</pre>

<p>expands to <code>B</code>.</p>

<p>Tuples can be used for representing structured data.</p>

<p>Examples of tuples:</p>

<pre>
  2-tuple: (A, B)
  3-tuple: (1, 2, 3)
  4-tuple: (A B C, D, EF, 34)
</pre>

<h3>See</h3>
<ul>
  <li>BOOST_PP_LIMIT_TUPLE</li>
</ul>
*/
#define BOOST_PP_TUPLE_ELEM(N,I,T) BOOST_PP_TUPLE_ELEM_DELAY(N,I,T)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#if !defined(BOOST_NO_COMPILER_CONFIG) && defined(__MWERKS__) && __MWERKS__ <= 0x2406
/* This is a workaround for a CodeWarrior PP bug. Strictly speaking
 * this workaround invokes undefined behavior, but it works as desired.
 */
#  define BOOST_PP_TUPLE_ELEM_DELAY(N,I,T) BOOST_PP_TUPLE##N##_ELEM##I##T
#elif !defined(BOOST_NO_COMPILER_CONFIG) && defined(_MSC_VER)
#  include <boost/preprocessor/expand.hpp>
/* This is a workaround for a MSVC++ PP bug. It should not be necessary
 * to use BOOST_PP_EXPAND(). Works on standard conforming compilers, too.
 */
#  define BOOST_PP_TUPLE_ELEM_DELAY(N,I,T) BOOST_PP_EXPAND(BOOST_PP_TUPLE##N##_ELEM##I T)
#else
#  define BOOST_PP_TUPLE_ELEM_DELAY(N,I,T) BOOST_PP_TUPLE##N##_ELEM##I T
#endif

/* TUPLE_ELEM can be implemented in O(N*N) space and O(N) time instead
 * of O(N*N*N) space and O(1) time. The current trade-off seems better.
 */
#define BOOST_PP_TUPLE1_ELEM0(A) A

#define BOOST_PP_TUPLE2_ELEM0(A,B) A
#define BOOST_PP_TUPLE2_ELEM1(A,B) B

#define BOOST_PP_TUPLE3_ELEM0(A,B,C) A
#define BOOST_PP_TUPLE3_ELEM1(A,B,C) B
#define BOOST_PP_TUPLE3_ELEM2(A,B,C) C

#define BOOST_PP_TUPLE4_ELEM0(A,B,C,D) A
#define BOOST_PP_TUPLE4_ELEM1(A,B,C,D) B
#define BOOST_PP_TUPLE4_ELEM2(A,B,C,D) C
#define BOOST_PP_TUPLE4_ELEM3(A,B,C,D) D

#define BOOST_PP_TUPLE5_ELEM0(A,B,C,D,E) A
#define BOOST_PP_TUPLE5_ELEM1(A,B,C,D,E) B
#define BOOST_PP_TUPLE5_ELEM2(A,B,C,D,E) C
#define BOOST_PP_TUPLE5_ELEM3(A,B,C,D,E) D
#define BOOST_PP_TUPLE5_ELEM4(A,B,C,D,E) E

#define BOOST_PP_TUPLE6_ELEM0(A,B,C,D,E,F) A
#define BOOST_PP_TUPLE6_ELEM1(A,B,C,D,E,F) B
#define BOOST_PP_TUPLE6_ELEM2(A,B,C,D,E,F) C
#define BOOST_PP_TUPLE6_ELEM3(A,B,C,D,E,F) D
#define BOOST_PP_TUPLE6_ELEM4(A,B,C,D,E,F) E
#define BOOST_PP_TUPLE6_ELEM5(A,B,C,D,E,F) F

#define BOOST_PP_TUPLE7_ELEM0(A,B,C,D,E,F,G) A
#define BOOST_PP_TUPLE7_ELEM1(A,B,C,D,E,F,G) B
#define BOOST_PP_TUPLE7_ELEM2(A,B,C,D,E,F,G) C
#define BOOST_PP_TUPLE7_ELEM3(A,B,C,D,E,F,G) D
#define BOOST_PP_TUPLE7_ELEM4(A,B,C,D,E,F,G) E
#define BOOST_PP_TUPLE7_ELEM5(A,B,C,D,E,F,G) F
#define BOOST_PP_TUPLE7_ELEM6(A,B,C,D,E,F,G) G

#define BOOST_PP_TUPLE8_ELEM0(A,B,C,D,E,F,G,H) A
#define BOOST_PP_TUPLE8_ELEM1(A,B,C,D,E,F,G,H) B
#define BOOST_PP_TUPLE8_ELEM2(A,B,C,D,E,F,G,H) C
#define BOOST_PP_TUPLE8_ELEM3(A,B,C,D,E,F,G,H) D
#define BOOST_PP_TUPLE8_ELEM4(A,B,C,D,E,F,G,H) E
#define BOOST_PP_TUPLE8_ELEM5(A,B,C,D,E,F,G,H) F
#define BOOST_PP_TUPLE8_ELEM6(A,B,C,D,E,F,G,H) G
#define BOOST_PP_TUPLE8_ELEM7(A,B,C,D,E,F,G,H) H

#define BOOST_PP_TUPLE9_ELEM0(A,B,C,D,E,F,G,H,I) A
#define BOOST_PP_TUPLE9_ELEM1(A,B,C,D,E,F,G,H,I) B
#define BOOST_PP_TUPLE9_ELEM2(A,B,C,D,E,F,G,H,I) C
#define BOOST_PP_TUPLE9_ELEM3(A,B,C,D,E,F,G,H,I) D
#define BOOST_PP_TUPLE9_ELEM4(A,B,C,D,E,F,G,H,I) E
#define BOOST_PP_TUPLE9_ELEM5(A,B,C,D,E,F,G,H,I) F
#define BOOST_PP_TUPLE9_ELEM6(A,B,C,D,E,F,G,H,I) G
#define BOOST_PP_TUPLE9_ELEM7(A,B,C,D,E,F,G,H,I) H
#define BOOST_PP_TUPLE9_ELEM8(A,B,C,D,E,F,G,H,I) I

#define BOOST_PP_TUPLE10_ELEM0(A,B,C,D,E,F,G,H,I,J) A
#define BOOST_PP_TUPLE10_ELEM1(A,B,C,D,E,F,G,H,I,J) B
#define BOOST_PP_TUPLE10_ELEM2(A,B,C,D,E,F,G,H,I,J) C
#define BOOST_PP_TUPLE10_ELEM3(A,B,C,D,E,F,G,H,I,J) D
#define BOOST_PP_TUPLE10_ELEM4(A,B,C,D,E,F,G,H,I,J) E
#define BOOST_PP_TUPLE10_ELEM5(A,B,C,D,E,F,G,H,I,J) F
#define BOOST_PP_TUPLE10_ELEM6(A,B,C,D,E,F,G,H,I,J) G
#define BOOST_PP_TUPLE10_ELEM7(A,B,C,D,E,F,G,H,I,J) H
#define BOOST_PP_TUPLE10_ELEM8(A,B,C,D,E,F,G,H,I,J) I
#define BOOST_PP_TUPLE10_ELEM9(A,B,C,D,E,F,G,H,I,J) J

#define BOOST_PP_TUPLE11_ELEM0(A,B,C,D,E,F,G,H,I,J,K) A
#define BOOST_PP_TUPLE11_ELEM1(A,B,C,D,E,F,G,H,I,J,K) B
#define BOOST_PP_TUPLE11_ELEM2(A,B,C,D,E,F,G,H,I,J,K) C
#define BOOST_PP_TUPLE11_ELEM3(A,B,C,D,E,F,G,H,I,J,K) D
#define BOOST_PP_TUPLE11_ELEM4(A,B,C,D,E,F,G,H,I,J,K) E
#define BOOST_PP_TUPLE11_ELEM5(A,B,C,D,E,F,G,H,I,J,K) F
#define BOOST_PP_TUPLE11_ELEM6(A,B,C,D,E,F,G,H,I,J,K) G
#define BOOST_PP_TUPLE11_ELEM7(A,B,C,D,E,F,G,H,I,J,K) H
#define BOOST_PP_TUPLE11_ELEM8(A,B,C,D,E,F,G,H,I,J,K) I
#define BOOST_PP_TUPLE11_ELEM9(A,B,C,D,E,F,G,H,I,J,K) J
#define BOOST_PP_TUPLE11_ELEM10(A,B,C,D,E,F,G,H,I,J,K) K

#define BOOST_PP_TUPLE12_ELEM0(A,B,C,D,E,F,G,H,I,J,K,L) A
#define BOOST_PP_TUPLE12_ELEM1(A,B,C,D,E,F,G,H,I,J,K,L) B
#define BOOST_PP_TUPLE12_ELEM2(A,B,C,D,E,F,G,H,I,J,K,L) C
#define BOOST_PP_TUPLE12_ELEM3(A,B,C,D,E,F,G,H,I,J,K,L) D
#define BOOST_PP_TUPLE12_ELEM4(A,B,C,D,E,F,G,H,I,J,K,L) E
#define BOOST_PP_TUPLE12_ELEM5(A,B,C,D,E,F,G,H,I,J,K,L) F
#define BOOST_PP_TUPLE12_ELEM6(A,B,C,D,E,F,G,H,I,J,K,L) G
#define BOOST_PP_TUPLE12_ELEM7(A,B,C,D,E,F,G,H,I,J,K,L) H
#define BOOST_PP_TUPLE12_ELEM8(A,B,C,D,E,F,G,H,I,J,K,L) I
#define BOOST_PP_TUPLE12_ELEM9(A,B,C,D,E,F,G,H,I,J,K,L) J
#define BOOST_PP_TUPLE12_ELEM10(A,B,C,D,E,F,G,H,I,J,K,L) K
#define BOOST_PP_TUPLE12_ELEM11(A,B,C,D,E,F,G,H,I,J,K,L) L

#define BOOST_PP_TUPLE13_ELEM0(A,B,C,D,E,F,G,H,I,J,K,L,M) A
#define BOOST_PP_TUPLE13_ELEM1(A,B,C,D,E,F,G,H,I,J,K,L,M) B
#define BOOST_PP_TUPLE13_ELEM2(A,B,C,D,E,F,G,H,I,J,K,L,M) C
#define BOOST_PP_TUPLE13_ELEM3(A,B,C,D,E,F,G,H,I,J,K,L,M) D
#define BOOST_PP_TUPLE13_ELEM4(A,B,C,D,E,F,G,H,I,J,K,L,M) E
#define BOOST_PP_TUPLE13_ELEM5(A,B,C,D,E,F,G,H,I,J,K,L,M) F
#define BOOST_PP_TUPLE13_ELEM6(A,B,C,D,E,F,G,H,I,J,K,L,M) G
#define BOOST_PP_TUPLE13_ELEM7(A,B,C,D,E,F,G,H,I,J,K,L,M) H
#define BOOST_PP_TUPLE13_ELEM8(A,B,C,D,E,F,G,H,I,J,K,L,M) I
#define BOOST_PP_TUPLE13_ELEM9(A,B,C,D,E,F,G,H,I,J,K,L,M) J
#define BOOST_PP_TUPLE13_ELEM10(A,B,C,D,E,F,G,H,I,J,K,L,M) K
#define BOOST_PP_TUPLE13_ELEM11(A,B,C,D,E,F,G,H,I,J,K,L,M) L
#define BOOST_PP_TUPLE13_ELEM12(A,B,C,D,E,F,G,H,I,J,K,L,M) M

#define BOOST_PP_TUPLE14_ELEM0(A,B,C,D,E,F,G,H,I,J,K,L,M,N) A
#define BOOST_PP_TUPLE14_ELEM1(A,B,C,D,E,F,G,H,I,J,K,L,M,N) B
#define BOOST_PP_TUPLE14_ELEM2(A,B,C,D,E,F,G,H,I,J,K,L,M,N) C
#define BOOST_PP_TUPLE14_ELEM3(A,B,C,D,E,F,G,H,I,J,K,L,M,N) D
#define BOOST_PP_TUPLE14_ELEM4(A,B,C,D,E,F,G,H,I,J,K,L,M,N) E
#define BOOST_PP_TUPLE14_ELEM5(A,B,C,D,E,F,G,H,I,J,K,L,M,N) F
#define BOOST_PP_TUPLE14_ELEM6(A,B,C,D,E,F,G,H,I,J,K,L,M,N) G
#define BOOST_PP_TUPLE14_ELEM7(A,B,C,D,E,F,G,H,I,J,K,L,M,N) H
#define BOOST_PP_TUPLE14_ELEM8(A,B,C,D,E,F,G,H,I,J,K,L,M,N) I
#define BOOST_PP_TUPLE14_ELEM9(A,B,C,D,E,F,G,H,I,J,K,L,M,N) J
#define BOOST_PP_TUPLE14_ELEM10(A,B,C,D,E,F,G,H,I,J,K,L,M,N) K
#define BOOST_PP_TUPLE14_ELEM11(A,B,C,D,E,F,G,H,I,J,K,L,M,N) L
#define BOOST_PP_TUPLE14_ELEM12(A,B,C,D,E,F,G,H,I,J,K,L,M,N) M
#define BOOST_PP_TUPLE14_ELEM13(A,B,C,D,E,F,G,H,I,J,K,L,M,N) N

#define BOOST_PP_TUPLE15_ELEM0(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O) A
#define BOOST_PP_TUPLE15_ELEM1(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O) B
#define BOOST_PP_TUPLE15_ELEM2(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O) C
#define BOOST_PP_TUPLE15_ELEM3(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O) D
#define BOOST_PP_TUPLE15_ELEM4(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O) E
#define BOOST_PP_TUPLE15_ELEM5(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O) F
#define BOOST_PP_TUPLE15_ELEM6(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O) G
#define BOOST_PP_TUPLE15_ELEM7(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O) H
#define BOOST_PP_TUPLE15_ELEM8(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O) I
#define BOOST_PP_TUPLE15_ELEM9(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O) J
#define BOOST_PP_TUPLE15_ELEM10(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O) K
#define BOOST_PP_TUPLE15_ELEM11(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O) L
#define BOOST_PP_TUPLE15_ELEM12(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O) M
#define BOOST_PP_TUPLE15_ELEM13(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O) N
#define BOOST_PP_TUPLE15_ELEM14(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O) O

#define BOOST_PP_TUPLE16_ELEM0(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) A
#define BOOST_PP_TUPLE16_ELEM1(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) B
#define BOOST_PP_TUPLE16_ELEM2(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) C
#define BOOST_PP_TUPLE16_ELEM3(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) D
#define BOOST_PP_TUPLE16_ELEM4(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) E
#define BOOST_PP_TUPLE16_ELEM5(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) F
#define BOOST_PP_TUPLE16_ELEM6(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) G
#define BOOST_PP_TUPLE16_ELEM7(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) H
#define BOOST_PP_TUPLE16_ELEM8(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) I
#define BOOST_PP_TUPLE16_ELEM9(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) J
#define BOOST_PP_TUPLE16_ELEM10(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) K
#define BOOST_PP_TUPLE16_ELEM11(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) L
#define BOOST_PP_TUPLE16_ELEM12(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) M
#define BOOST_PP_TUPLE16_ELEM13(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) N
#define BOOST_PP_TUPLE16_ELEM14(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) O
#define BOOST_PP_TUPLE16_ELEM15(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) P
#endif

/** <p>Obsolete. Use BOOST_PP_TUPLE_ELEM().</p> */
#define BOOST_PREPROCESSOR_TUPLE_ELEM(N,I,T) BOOST_PP_TUPLE_ELEM(N,I,T)
#endif
