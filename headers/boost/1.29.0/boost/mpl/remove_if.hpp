//-----------------------------------------------------------------------------
// boost mpl/remove_if.hpp header file
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

#ifndef BOOST_MPL_REMOVE_IF_HPP_INCLUDED
#define BOOST_MPL_REMOVE_IF_HPP_INCLUDED

#include "boost/mpl/fold_backward.hpp"
#include "boost/mpl/clear.hpp"
#include "boost/mpl/apply_if.hpp"
#include "boost/mpl/push_front.hpp"
#include "boost/mpl/identity.hpp"
#include "boost/mpl/protect.hpp"
#include "boost/mpl/lambda.hpp"
#include "boost/mpl/aux_/void_spec.hpp"

namespace boost {
namespace mpl {

namespace aux {

template< typename Pred > struct remove_if_helper
{
    template< typename Sequence, typename U > struct apply
    {
        typedef typename apply_if<
			  typename apply1<Pred, U>::type
            , identity<Sequence>
            , push_front<Sequence,U>
            >::type type;
    };
};

} // namespace aux

template<
      typename BOOST_MPL_AUX_VOID_SPEC_PARAM(Sequence)
    , typename BOOST_MPL_AUX_VOID_SPEC_PARAM(Predicate)
    >
struct remove_if
{
 private:
    typedef typename lambda<Predicate>::type pred_;
 
 public:
    typedef typename fold_backward<
          Sequence
        , typename clear<Sequence>::type
        , protect< aux::remove_if_helper<pred_> >
        >::type type;
};

BOOST_MPL_AUX_VOID_SPEC(2, remove_if)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_REMOVE_IF_HPP_INCLUDED
