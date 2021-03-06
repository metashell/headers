//-----------------------------------------------------------------------------
// boost mpl/sequence_tag.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#ifndef BOOST_MPL_SEQUENCE_TAG_HPP_INCLUDED
#define BOOST_MPL_SEQUENCE_TAG_HPP_INCLUDED

#include "boost/mpl/aux_/void_spec.hpp"
#include "boost/mpl/aux_/config/eti.hpp"

namespace boost {
namespace mpl {

template<
      typename BOOST_MPL_AUX_VOID_SPEC_PARAM(Sequence)
    >
struct sequence_tag
{
    typedef typename Sequence::tag type;
};

#if defined(BOOST_MPL_MSVC_ETI_BUG)
template<> struct sequence_tag<int>
{
    typedef int type;
};
#endif

BOOST_MPL_AUX_VOID_SPEC(1, sequence_tag)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_SEQUENCE_TAG_HPP_INCLUDED
