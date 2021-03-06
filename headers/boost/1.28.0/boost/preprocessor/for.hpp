#ifndef BOOST_PREPROCESSOR_FOR_HPP
#define BOOST_PREPROCESSOR_FOR_HPP

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

#include <boost/preprocessor/if.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

/** <p>Repeats <code>MACRO(R,STATE)</code> and iterates <code>OP(R,STATE)</code> while
<code>PRED(R,STATE)</code> is true.</p>

<p>In other words, expands to the sequence:</p>

<pre>
  MACRO(R,STATE)
  MACRO(R,OP(R,STATE))
  MACRO(R,OP(R,OP(R,STATE)))
  ...
  MACRO(R,OP(R,OP(...OP(R,STATE)...)))
</pre>

<p>The length of the sequence is determined by <code>PRED(R,STATE)</code>.</p>

<p>For example,</p>

<pre>
  #define PRED(R,STATE) BOOST_PP_LESS(BOOST_PP_TUPLE_ELEM(2,0,STATE),BOOST_PP_TUPLE_ELEM(2,1,STATE))
  #define OP(R,STATE) (BOOST_PP_INC(BOOST_PP_TUPLE_ELEM(2,0,STATE)),BOOST_PP_TUPLE_ELEM(2,1,STATE))
  #define MACRO(R,STATE) BOOST_PP_TUPLE_ELEM(2,0,STATE)
  BOOST_PP_FOR((0,3),PRED,OP,MACRO)
</pre>

<p>expands to:</p>

<pre>
  0 1 2
</pre>

<h3>Legend</h3>
<ul>
  <li><b>STATE</b> is the current state of iteration. The state is usually a tuple.</li>
  <li><b>PRED</b> is the condition for iteration. It must expand to a decimal
      integer literal.</li>
  <li><b>OP</b> is the iterated macro. Note that if the state is a tuple, then
      OP(R,STATE) usually expands to a tuple of the same number of elements.</li>
  <li><b>MACRO</b> is the state instantiation macro.</li>
  <li><b>R</b> is the recursion depth and should only be used as a parameter to
      other macros using BOOST_PP_FOR() or for invoking BOOST_PP_FOR##R()
      directly. For each macro using BOOST_PP_FOR(), e.g. BOOST_PP_LIST_FOR_EACH(),
      there is a version of the macro, e.g. BOOST_PP_LIST_FOR_EACH_R(), distinguished
      by the R suffix, that accepts an additional recursion depth as the first
      parameter. This technique is necessary to avoid recursively expanding the same
      macro again, which is not permitted by the C++ preprocessor.</li>
</ul>

<h3>BOOST_PP_REPEAT() vs BOOST_PP_FOR()</h3>

<p>BOOST_PP_FOR() is a generalization of BOOST_PP_REPEAT(). This means that
BOOST_PP_REPEAT() can be implemented using BOOST_PP_FOR(). However,
BOOST_PP_REPEAT() was introduced earlier, is generally easier to use, and is
still quite useful on its own.</p>

<h3>2D and 3D repetition</h3>

<p>BOOST_PP_FOR() can be used for multidimensional repetition simply by
invoking BOOST_PP_FOR##R() directly.</p>

<h3>Test</h3>
<ul>
  <li><a href="../../test/for_test.cpp">for_test.cpp</a></li>
</ul>
*/
#define BOOST_PP_FOR(STATE,PRED,OP,MACRO) BOOST_PP_FOR0(STATE,PRED,OP,MACRO)

#define BOOST_PP_FOR_C0(P,R,S,M) BOOST_PP_IF(P(R,S),M,BOOST_PP_TUPLE2_EAT)
#define BOOST_PP_FOR_C1(P,R,S) BOOST_PP_IF(P(R,S),BOOST_PP_FOR##R,BOOST_PP_TUPLE4_EAT)
#define BOOST_PP_FOR0(S,P,O,M) BOOST_PP_FOR_C0(P,1,S,M)(1,S) BOOST_PP_FOR_C1(P,1,S)(O(1,S),P,O,M)
#define BOOST_PP_FOR1(S,P,O,M) BOOST_PP_FOR_C0(P,2,S,M)(2,S) BOOST_PP_FOR_C1(P,2,S)(O(2,S),P,O,M)
#define BOOST_PP_FOR2(S,P,O,M) BOOST_PP_FOR_C0(P,3,S,M)(3,S) BOOST_PP_FOR_C1(P,3,S)(O(3,S),P,O,M)
#define BOOST_PP_FOR3(S,P,O,M) BOOST_PP_FOR_C0(P,4,S,M)(4,S) BOOST_PP_FOR_C1(P,4,S)(O(4,S),P,O,M)
#define BOOST_PP_FOR4(S,P,O,M) BOOST_PP_FOR_C0(P,5,S,M)(5,S) BOOST_PP_FOR_C1(P,5,S)(O(5,S),P,O,M)
#define BOOST_PP_FOR5(S,P,O,M) BOOST_PP_FOR_C0(P,6,S,M)(6,S) BOOST_PP_FOR_C1(P,6,S)(O(6,S),P,O,M)
#define BOOST_PP_FOR6(S,P,O,M) BOOST_PP_FOR_C0(P,7,S,M)(7,S) BOOST_PP_FOR_C1(P,7,S)(O(7,S),P,O,M)
#define BOOST_PP_FOR7(S,P,O,M) BOOST_PP_FOR_C0(P,8,S,M)(8,S) BOOST_PP_FOR_C1(P,8,S)(O(8,S),P,O,M)
#define BOOST_PP_FOR8(S,P,O,M) BOOST_PP_FOR_C0(P,9,S,M)(9,S) BOOST_PP_FOR_C1(P,9,S)(O(9,S),P,O,M)
#define BOOST_PP_FOR9(S,P,O,M) BOOST_PP_FOR_C0(P,10,S,M)(10,S) BOOST_PP_FOR_C1(P,10,S)(O(10,S),P,O,M)
#define BOOST_PP_FOR10(S,P,O,M) BOOST_PP_FOR_C0(P,11,S,M)(11,S) BOOST_PP_FOR_C1(P,11,S)(O(11,S),P,O,M)
#define BOOST_PP_FOR11(S,P,O,M) BOOST_PP_FOR_C0(P,12,S,M)(12,S) BOOST_PP_FOR_C1(P,12,S)(O(12,S),P,O,M)
#define BOOST_PP_FOR12(S,P,O,M) BOOST_PP_FOR_C0(P,13,S,M)(13,S) BOOST_PP_FOR_C1(P,13,S)(O(13,S),P,O,M)
#define BOOST_PP_FOR13(S,P,O,M) BOOST_PP_FOR_C0(P,14,S,M)(14,S) BOOST_PP_FOR_C1(P,14,S)(O(14,S),P,O,M)
#define BOOST_PP_FOR14(S,P,O,M) BOOST_PP_FOR_C0(P,15,S,M)(15,S) BOOST_PP_FOR_C1(P,15,S)(O(15,S),P,O,M)
#define BOOST_PP_FOR15(S,P,O,M) BOOST_PP_FOR_C0(P,16,S,M)(16,S) BOOST_PP_FOR_C1(P,16,S)(O(16,S),P,O,M)
#define BOOST_PP_FOR16(S,P,O,M) BOOST_PP_FOR_C0(P,17,S,M)(17,S) BOOST_PP_FOR_C1(P,17,S)(O(17,S),P,O,M)
#define BOOST_PP_FOR17(S,P,O,M) BOOST_PP_FOR_C0(P,18,S,M)(18,S) BOOST_PP_FOR_C1(P,18,S)(O(18,S),P,O,M)
#define BOOST_PP_FOR18(S,P,O,M) BOOST_PP_FOR_C0(P,19,S,M)(19,S) BOOST_PP_FOR_C1(P,19,S)(O(19,S),P,O,M)
#define BOOST_PP_FOR19(S,P,O,M) BOOST_PP_FOR_C0(P,20,S,M)(20,S) BOOST_PP_FOR_C1(P,20,S)(O(20,S),P,O,M)
#define BOOST_PP_FOR20(S,P,O,M) BOOST_PP_FOR_C0(P,21,S,M)(21,S) BOOST_PP_FOR_C1(P,21,S)(O(21,S),P,O,M)
#define BOOST_PP_FOR21(S,P,O,M) BOOST_PP_FOR_C0(P,22,S,M)(22,S) BOOST_PP_FOR_C1(P,22,S)(O(22,S),P,O,M)
#define BOOST_PP_FOR22(S,P,O,M) BOOST_PP_FOR_C0(P,23,S,M)(23,S) BOOST_PP_FOR_C1(P,23,S)(O(23,S),P,O,M)
#define BOOST_PP_FOR23(S,P,O,M) BOOST_PP_FOR_C0(P,24,S,M)(24,S) BOOST_PP_FOR_C1(P,24,S)(O(24,S),P,O,M)
#define BOOST_PP_FOR24(S,P,O,M) BOOST_PP_FOR_C0(P,25,S,M)(25,S) BOOST_PP_FOR_C1(P,25,S)(O(25,S),P,O,M)
#define BOOST_PP_FOR25(S,P,O,M) BOOST_PP_FOR_C0(P,26,S,M)(26,S) BOOST_PP_FOR_C1(P,26,S)(O(26,S),P,O,M)
#define BOOST_PP_FOR26(S,P,O,M) BOOST_PP_FOR_C0(P,27,S,M)(27,S) BOOST_PP_FOR_C1(P,27,S)(O(27,S),P,O,M)
#define BOOST_PP_FOR27(S,P,O,M) BOOST_PP_FOR_C0(P,28,S,M)(28,S) BOOST_PP_FOR_C1(P,28,S)(O(28,S),P,O,M)
#define BOOST_PP_FOR28(S,P,O,M) BOOST_PP_FOR_C0(P,29,S,M)(29,S) BOOST_PP_FOR_C1(P,29,S)(O(29,S),P,O,M)
#define BOOST_PP_FOR29(S,P,O,M) BOOST_PP_FOR_C0(P,30,S,M)(30,S) BOOST_PP_FOR_C1(P,30,S)(O(30,S),P,O,M)
#define BOOST_PP_FOR30(S,P,O,M) BOOST_PP_FOR_C0(P,31,S,M)(31,S) BOOST_PP_FOR_C1(P,31,S)(O(31,S),P,O,M)
#define BOOST_PP_FOR31(S,P,O,M) BOOST_PP_FOR_C0(P,32,S,M)(32,S) BOOST_PP_FOR_C1(P,32,S)(O(32,S),P,O,M)
#define BOOST_PP_FOR32(S,P,O,M) BOOST_PP_FOR_C0(P,33,S,M)(33,S) BOOST_PP_FOR_C1(P,33,S)(O(33,S),P,O,M)
#define BOOST_PP_FOR33(S,P,O,M) BOOST_PP_FOR_C0(P,34,S,M)(34,S) BOOST_PP_FOR_C1(P,34,S)(O(34,S),P,O,M)
#define BOOST_PP_FOR34(S,P,O,M) BOOST_PP_FOR_C0(P,35,S,M)(35,S) BOOST_PP_FOR_C1(P,35,S)(O(35,S),P,O,M)
#define BOOST_PP_FOR35(S,P,O,M) BOOST_PP_FOR_C0(P,36,S,M)(36,S) BOOST_PP_FOR_C1(P,36,S)(O(36,S),P,O,M)
#define BOOST_PP_FOR36(S,P,O,M) BOOST_PP_FOR_C0(P,37,S,M)(37,S) BOOST_PP_FOR_C1(P,37,S)(O(37,S),P,O,M)
#define BOOST_PP_FOR37(S,P,O,M) BOOST_PP_FOR_C0(P,38,S,M)(38,S) BOOST_PP_FOR_C1(P,38,S)(O(38,S),P,O,M)
#define BOOST_PP_FOR38(S,P,O,M) BOOST_PP_FOR_C0(P,39,S,M)(39,S) BOOST_PP_FOR_C1(P,39,S)(O(39,S),P,O,M)
#define BOOST_PP_FOR39(S,P,O,M) BOOST_PP_FOR_C0(P,40,S,M)(40,S) BOOST_PP_FOR_C1(P,40,S)(O(40,S),P,O,M)
#define BOOST_PP_FOR40(S,P,O,M) BOOST_PP_FOR_C0(P,41,S,M)(41,S) BOOST_PP_FOR_C1(P,41,S)(O(41,S),P,O,M)
#define BOOST_PP_FOR41(S,P,O,M) BOOST_PP_FOR_C0(P,42,S,M)(42,S) BOOST_PP_FOR_C1(P,42,S)(O(42,S),P,O,M)
#define BOOST_PP_FOR42(S,P,O,M) BOOST_PP_FOR_C0(P,43,S,M)(43,S) BOOST_PP_FOR_C1(P,43,S)(O(43,S),P,O,M)
#define BOOST_PP_FOR43(S,P,O,M) BOOST_PP_FOR_C0(P,44,S,M)(44,S) BOOST_PP_FOR_C1(P,44,S)(O(44,S),P,O,M)
#define BOOST_PP_FOR44(S,P,O,M) BOOST_PP_FOR_C0(P,45,S,M)(45,S) BOOST_PP_FOR_C1(P,45,S)(O(45,S),P,O,M)
#define BOOST_PP_FOR45(S,P,O,M) BOOST_PP_FOR_C0(P,46,S,M)(46,S) BOOST_PP_FOR_C1(P,46,S)(O(46,S),P,O,M)
#define BOOST_PP_FOR46(S,P,O,M) BOOST_PP_FOR_C0(P,47,S,M)(47,S) BOOST_PP_FOR_C1(P,47,S)(O(47,S),P,O,M)
#define BOOST_PP_FOR47(S,P,O,M) BOOST_PP_FOR_C0(P,48,S,M)(48,S) BOOST_PP_FOR_C1(P,48,S)(O(48,S),P,O,M)
#define BOOST_PP_FOR48(S,P,O,M) BOOST_PP_FOR_C0(P,49,S,M)(49,S) BOOST_PP_FOR_C1(P,49,S)(O(49,S),P,O,M)
#define BOOST_PP_FOR49(S,P,O,M) BOOST_PP_FOR_C0(P,50,S,M)(50,S) BOOST_PP_FOR_C1(P,50,S)(O(50,S),P,O,M)
#define BOOST_PP_FOR50(S,P,O,M) BOOST_PP_FOR_C0(P,51,S,M)(51,S) BOOST_PP_FOR_C1(P,51,S)(O(51,S),P,O,M)
#define BOOST_PP_FOR51(S,P,O,M) BOOST_PP_FOR_C0(P,52,S,M)(52,S) BOOST_PP_FOR_C1(P,52,S)(O(52,S),P,O,M)
#define BOOST_PP_FOR52(S,P,O,M) BOOST_PP_FOR_C0(P,53,S,M)(53,S) BOOST_PP_FOR_C1(P,53,S)(O(53,S),P,O,M)
#define BOOST_PP_FOR53(S,P,O,M) BOOST_PP_FOR_C0(P,54,S,M)(54,S) BOOST_PP_FOR_C1(P,54,S)(O(54,S),P,O,M)
#define BOOST_PP_FOR54(S,P,O,M) BOOST_PP_FOR_C0(P,55,S,M)(55,S) BOOST_PP_FOR_C1(P,55,S)(O(55,S),P,O,M)
#define BOOST_PP_FOR55(S,P,O,M) BOOST_PP_FOR_C0(P,56,S,M)(56,S) BOOST_PP_FOR_C1(P,56,S)(O(56,S),P,O,M)
#define BOOST_PP_FOR56(S,P,O,M) BOOST_PP_FOR_C0(P,57,S,M)(57,S) BOOST_PP_FOR_C1(P,57,S)(O(57,S),P,O,M)
#define BOOST_PP_FOR57(S,P,O,M) BOOST_PP_FOR_C0(P,58,S,M)(58,S) BOOST_PP_FOR_C1(P,58,S)(O(58,S),P,O,M)
#define BOOST_PP_FOR58(S,P,O,M) BOOST_PP_FOR_C0(P,59,S,M)(59,S) BOOST_PP_FOR_C1(P,59,S)(O(59,S),P,O,M)
#define BOOST_PP_FOR59(S,P,O,M) BOOST_PP_FOR_C0(P,60,S,M)(60,S) BOOST_PP_FOR_C1(P,60,S)(O(60,S),P,O,M)
#define BOOST_PP_FOR60(S,P,O,M) BOOST_PP_FOR_C0(P,61,S,M)(61,S) BOOST_PP_FOR_C1(P,61,S)(O(61,S),P,O,M)
#define BOOST_PP_FOR61(S,P,O,M) BOOST_PP_FOR_C0(P,62,S,M)(62,S) BOOST_PP_FOR_C1(P,62,S)(O(62,S),P,O,M)
#define BOOST_PP_FOR62(S,P,O,M) BOOST_PP_FOR_C0(P,63,S,M)(63,S) BOOST_PP_FOR_C1(P,63,S)(O(63,S),P,O,M)
#define BOOST_PP_FOR63(S,P,O,M) BOOST_PP_FOR_C0(P,64,S,M)(64,S) BOOST_PP_FOR_C1(P,64,S)(O(64,S),P,O,M)
#define BOOST_PP_FOR64(S,P,O,M) BOOST_PP_FOR_C0(P,65,S,M)(65,S) BOOST_PP_FOR_C1(P,65,S)(O(65,S),P,O,M)
#define BOOST_PP_FOR65(S,P,O,M) BOOST_PP_FOR_C0(P,66,S,M)(66,S) BOOST_PP_FOR_C1(P,66,S)(O(66,S),P,O,M)
#define BOOST_PP_FOR66(S,P,O,M) BOOST_PP_FOR_C0(P,67,S,M)(67,S) BOOST_PP_FOR_C1(P,67,S)(O(67,S),P,O,M)
#define BOOST_PP_FOR67(S,P,O,M) BOOST_PP_FOR_C0(P,68,S,M)(68,S) BOOST_PP_FOR_C1(P,68,S)(O(68,S),P,O,M)
#define BOOST_PP_FOR68(S,P,O,M) BOOST_PP_FOR_C0(P,69,S,M)(69,S) BOOST_PP_FOR_C1(P,69,S)(O(69,S),P,O,M)
#define BOOST_PP_FOR69(S,P,O,M) BOOST_PP_FOR_C0(P,70,S,M)(70,S) BOOST_PP_FOR_C1(P,70,S)(O(70,S),P,O,M)
#define BOOST_PP_FOR70(S,P,O,M) BOOST_PP_FOR_C0(P,71,S,M)(71,S) BOOST_PP_FOR_C1(P,71,S)(O(71,S),P,O,M)
#define BOOST_PP_FOR71(S,P,O,M) BOOST_PP_FOR_C0(P,72,S,M)(72,S) BOOST_PP_FOR_C1(P,72,S)(O(72,S),P,O,M)
#define BOOST_PP_FOR72(S,P,O,M) BOOST_PP_FOR_C0(P,73,S,M)(73,S) BOOST_PP_FOR_C1(P,73,S)(O(73,S),P,O,M)
#define BOOST_PP_FOR73(S,P,O,M) BOOST_PP_FOR_C0(P,74,S,M)(74,S) BOOST_PP_FOR_C1(P,74,S)(O(74,S),P,O,M)
#define BOOST_PP_FOR74(S,P,O,M) BOOST_PP_FOR_C0(P,75,S,M)(75,S) BOOST_PP_FOR_C1(P,75,S)(O(75,S),P,O,M)
#define BOOST_PP_FOR75(S,P,O,M) BOOST_PP_FOR_C0(P,76,S,M)(76,S) BOOST_PP_FOR_C1(P,76,S)(O(76,S),P,O,M)
#define BOOST_PP_FOR76(S,P,O,M) BOOST_PP_FOR_C0(P,77,S,M)(77,S) BOOST_PP_FOR_C1(P,77,S)(O(77,S),P,O,M)
#define BOOST_PP_FOR77(S,P,O,M) BOOST_PP_FOR_C0(P,78,S,M)(78,S) BOOST_PP_FOR_C1(P,78,S)(O(78,S),P,O,M)
#define BOOST_PP_FOR78(S,P,O,M) BOOST_PP_FOR_C0(P,79,S,M)(79,S) BOOST_PP_FOR_C1(P,79,S)(O(79,S),P,O,M)
#define BOOST_PP_FOR79(S,P,O,M) BOOST_PP_FOR_C0(P,80,S,M)(80,S) BOOST_PP_FOR_C1(P,80,S)(O(80,S),P,O,M)
#define BOOST_PP_FOR80(S,P,O,M) BOOST_PP_FOR_C0(P,81,S,M)(81,S) BOOST_PP_FOR_C1(P,81,S)(O(81,S),P,O,M)
#define BOOST_PP_FOR81(S,P,O,M) BOOST_PP_FOR_C0(P,82,S,M)(82,S) BOOST_PP_FOR_C1(P,82,S)(O(82,S),P,O,M)
#define BOOST_PP_FOR82(S,P,O,M) BOOST_PP_FOR_C0(P,83,S,M)(83,S) BOOST_PP_FOR_C1(P,83,S)(O(83,S),P,O,M)
#define BOOST_PP_FOR83(S,P,O,M) BOOST_PP_FOR_C0(P,84,S,M)(84,S) BOOST_PP_FOR_C1(P,84,S)(O(84,S),P,O,M)
#define BOOST_PP_FOR84(S,P,O,M) BOOST_PP_FOR_C0(P,85,S,M)(85,S) BOOST_PP_FOR_C1(P,85,S)(O(85,S),P,O,M)
#define BOOST_PP_FOR85(S,P,O,M) BOOST_PP_FOR_C0(P,86,S,M)(86,S) BOOST_PP_FOR_C1(P,86,S)(O(86,S),P,O,M)
#define BOOST_PP_FOR86(S,P,O,M) BOOST_PP_FOR_C0(P,87,S,M)(87,S) BOOST_PP_FOR_C1(P,87,S)(O(87,S),P,O,M)
#define BOOST_PP_FOR87(S,P,O,M) BOOST_PP_FOR_C0(P,88,S,M)(88,S) BOOST_PP_FOR_C1(P,88,S)(O(88,S),P,O,M)
#define BOOST_PP_FOR88(S,P,O,M) BOOST_PP_FOR_C0(P,89,S,M)(89,S) BOOST_PP_FOR_C1(P,89,S)(O(89,S),P,O,M)
#define BOOST_PP_FOR89(S,P,O,M) BOOST_PP_FOR_C0(P,90,S,M)(90,S) BOOST_PP_FOR_C1(P,90,S)(O(90,S),P,O,M)
#define BOOST_PP_FOR90(S,P,O,M) BOOST_PP_FOR_C0(P,91,S,M)(91,S) BOOST_PP_FOR_C1(P,91,S)(O(91,S),P,O,M)
#define BOOST_PP_FOR91(S,P,O,M) BOOST_PP_FOR_C0(P,92,S,M)(92,S) BOOST_PP_FOR_C1(P,92,S)(O(92,S),P,O,M)
#define BOOST_PP_FOR92(S,P,O,M) BOOST_PP_FOR_C0(P,93,S,M)(93,S) BOOST_PP_FOR_C1(P,93,S)(O(93,S),P,O,M)
#define BOOST_PP_FOR93(S,P,O,M) BOOST_PP_FOR_C0(P,94,S,M)(94,S) BOOST_PP_FOR_C1(P,94,S)(O(94,S),P,O,M)
#define BOOST_PP_FOR94(S,P,O,M) BOOST_PP_FOR_C0(P,95,S,M)(95,S) BOOST_PP_FOR_C1(P,95,S)(O(95,S),P,O,M)
#define BOOST_PP_FOR95(S,P,O,M) BOOST_PP_FOR_C0(P,96,S,M)(96,S) BOOST_PP_FOR_C1(P,96,S)(O(96,S),P,O,M)
#define BOOST_PP_FOR96(S,P,O,M) BOOST_PP_FOR_C0(P,97,S,M)(97,S) BOOST_PP_FOR_C1(P,97,S)(O(97,S),P,O,M)
#define BOOST_PP_FOR97(S,P,O,M) BOOST_PP_FOR_C0(P,98,S,M)(98,S) BOOST_PP_FOR_C1(P,98,S)(O(98,S),P,O,M)
#define BOOST_PP_FOR98(S,P,O,M) BOOST_PP_FOR_C0(P,99,S,M)(99,S) BOOST_PP_FOR_C1(P,99,S)(O(99,S),P,O,M)
#define BOOST_PP_FOR99(S,P,O,M) BOOST_PP_FOR_C0(P,100,S,M)(100,S) BOOST_PP_FOR_C1(P,100,S)(O(100,S),P,O,M)
#define BOOST_PP_FOR100(S,P,O,M) BOOST_PP_FOR_C0(P,101,S,M)(101,S) BOOST_PP_FOR_C1(P,101,S)(O(101,S),P,O,M)
#define BOOST_PP_FOR101(S,P,O,M) BOOST_PP_FOR_C0(P,102,S,M)(102,S) BOOST_PP_FOR_C1(P,102,S)(O(102,S),P,O,M)
#define BOOST_PP_FOR102(S,P,O,M) BOOST_PP_FOR_C0(P,103,S,M)(103,S) BOOST_PP_FOR_C1(P,103,S)(O(103,S),P,O,M)
#define BOOST_PP_FOR103(S,P,O,M) BOOST_PP_FOR_C0(P,104,S,M)(104,S) BOOST_PP_FOR_C1(P,104,S)(O(104,S),P,O,M)
#define BOOST_PP_FOR104(S,P,O,M) BOOST_PP_FOR_C0(P,105,S,M)(105,S) BOOST_PP_FOR_C1(P,105,S)(O(105,S),P,O,M)
#define BOOST_PP_FOR105(S,P,O,M) BOOST_PP_FOR_C0(P,106,S,M)(106,S) BOOST_PP_FOR_C1(P,106,S)(O(106,S),P,O,M)
#define BOOST_PP_FOR106(S,P,O,M) BOOST_PP_FOR_C0(P,107,S,M)(107,S) BOOST_PP_FOR_C1(P,107,S)(O(107,S),P,O,M)
#define BOOST_PP_FOR107(S,P,O,M) BOOST_PP_FOR_C0(P,108,S,M)(108,S) BOOST_PP_FOR_C1(P,108,S)(O(108,S),P,O,M)
#define BOOST_PP_FOR108(S,P,O,M) BOOST_PP_FOR_C0(P,109,S,M)(109,S) BOOST_PP_FOR_C1(P,109,S)(O(109,S),P,O,M)
#define BOOST_PP_FOR109(S,P,O,M) BOOST_PP_FOR_C0(P,110,S,M)(110,S) BOOST_PP_FOR_C1(P,110,S)(O(110,S),P,O,M)
#define BOOST_PP_FOR110(S,P,O,M) BOOST_PP_FOR_C0(P,111,S,M)(111,S) BOOST_PP_FOR_C1(P,111,S)(O(111,S),P,O,M)
#define BOOST_PP_FOR111(S,P,O,M) BOOST_PP_FOR_C0(P,112,S,M)(112,S) BOOST_PP_FOR_C1(P,112,S)(O(112,S),P,O,M)
#define BOOST_PP_FOR112(S,P,O,M) BOOST_PP_FOR_C0(P,113,S,M)(113,S) BOOST_PP_FOR_C1(P,113,S)(O(113,S),P,O,M)
#define BOOST_PP_FOR113(S,P,O,M) BOOST_PP_FOR_C0(P,114,S,M)(114,S) BOOST_PP_FOR_C1(P,114,S)(O(114,S),P,O,M)
#define BOOST_PP_FOR114(S,P,O,M) BOOST_PP_FOR_C0(P,115,S,M)(115,S) BOOST_PP_FOR_C1(P,115,S)(O(115,S),P,O,M)
#define BOOST_PP_FOR115(S,P,O,M) BOOST_PP_FOR_C0(P,116,S,M)(116,S) BOOST_PP_FOR_C1(P,116,S)(O(116,S),P,O,M)
#define BOOST_PP_FOR116(S,P,O,M) BOOST_PP_FOR_C0(P,117,S,M)(117,S) BOOST_PP_FOR_C1(P,117,S)(O(117,S),P,O,M)
#define BOOST_PP_FOR117(S,P,O,M) BOOST_PP_FOR_C0(P,118,S,M)(118,S) BOOST_PP_FOR_C1(P,118,S)(O(118,S),P,O,M)
#define BOOST_PP_FOR118(S,P,O,M) BOOST_PP_FOR_C0(P,119,S,M)(119,S) BOOST_PP_FOR_C1(P,119,S)(O(119,S),P,O,M)
#define BOOST_PP_FOR119(S,P,O,M) BOOST_PP_FOR_C0(P,120,S,M)(120,S) BOOST_PP_FOR_C1(P,120,S)(O(120,S),P,O,M)
#define BOOST_PP_FOR120(S,P,O,M) BOOST_PP_FOR_C0(P,121,S,M)(121,S) BOOST_PP_FOR_C1(P,121,S)(O(121,S),P,O,M)
#define BOOST_PP_FOR121(S,P,O,M) BOOST_PP_FOR_C0(P,122,S,M)(122,S) BOOST_PP_FOR_C1(P,122,S)(O(122,S),P,O,M)
#define BOOST_PP_FOR122(S,P,O,M) BOOST_PP_FOR_C0(P,123,S,M)(123,S) BOOST_PP_FOR_C1(P,123,S)(O(123,S),P,O,M)
#define BOOST_PP_FOR123(S,P,O,M) BOOST_PP_FOR_C0(P,124,S,M)(124,S) BOOST_PP_FOR_C1(P,124,S)(O(124,S),P,O,M)
#define BOOST_PP_FOR124(S,P,O,M) BOOST_PP_FOR_C0(P,125,S,M)(125,S) BOOST_PP_FOR_C1(P,125,S)(O(125,S),P,O,M)
#define BOOST_PP_FOR125(S,P,O,M) BOOST_PP_FOR_C0(P,126,S,M)(126,S) BOOST_PP_FOR_C1(P,126,S)(O(126,S),P,O,M)
#define BOOST_PP_FOR126(S,P,O,M) BOOST_PP_FOR_C0(P,127,S,M)(127,S) BOOST_PP_FOR_C1(P,127,S)(O(127,S),P,O,M)
#define BOOST_PP_FOR127(S,P,O,M) BOOST_PP_FOR_C0(P,128,S,M)(128,S) BOOST_PP_FOR_C1(P,128,S)(O(128,S),P,O,M)
#define BOOST_PP_FOR128(S,P,O,M) BOOST_PP_FOR_C0(P,129,S,M)(129,S) BOOST_PP_FOR_C1(P,129,S)(O(129,S),P,O,M)
#define BOOST_PP_FOR129(S,P,O,M) RECURSION DEPTH EXCEEDED!
#endif
