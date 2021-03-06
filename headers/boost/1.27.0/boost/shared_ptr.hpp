#ifndef BOOST_SHARED_PTR_HPP_INCLUDED
#define BOOST_SHARED_PTR_HPP_INCLUDED

//
//  shared_ptr.hpp
//
//  (C) Copyright Greg Colvin and Beman Dawes 1998, 1999.
//  Copyright (c) 2001, 2002 Peter Dimov
//
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  See http://www.boost.org/libs/smart_ptr/shared_ptr.htm for documentation.
//

#include <boost/config.hpp>   // for broken compiler workarounds

#ifndef BOOST_MSVC6_MEMBER_TEMPLATES
#include <boost/detail/shared_ptr_nmt.hpp>
#else

#include <boost/assert.hpp>
#include <boost/checked_delete.hpp>

#include <boost/detail/shared_count.hpp>

#include <memory>             // for std::auto_ptr
#include <algorithm>          // for std::swap
#include <functional>         // for std::less

#ifdef BOOST_MSVC  // moved here to work around VC++ compiler crash
# pragma warning(push)
# pragma warning(disable:4284) // odd return type for operator->
#endif

namespace boost
{

namespace detail
{

struct static_cast_tag {};
struct dynamic_cast_tag {};

template<typename T> struct shared_ptr_traits
{
    typedef T & reference;
};

template<> struct shared_ptr_traits<void>
{
    typedef void reference;
};

} // namespace detail


//
//  shared_ptr
//
//  An enhanced relative of scoped_ptr with reference counted copy semantics.
//  The object pointed to is deleted when the last shared_ptr pointing to it
//  is destroyed or reset.
//

template<typename T> class weak_ptr;

template<typename T> class shared_ptr
{
private:

    // Borland 5.5.1 specific workarounds
    typedef checked_deleter<T> deleter;
    typedef shared_ptr<T> this_type;

public:

    typedef T element_type;

    explicit shared_ptr(T * p = 0): px(p), pn(p, deleter())
    {
    }

    //
    // Requirements: D's copy constructor must not throw
    //
    // shared_ptr will release p by calling d(p)
    //

    template<typename D> shared_ptr(T * p, D d): px(p), pn(p, d)
    {
    }

//  generated copy constructor, assignment, destructor are fine

    template<typename Y>
    shared_ptr(shared_ptr<Y> const & r): px(r.px), pn(r.pn) // never throws
    {
    }

    template<typename Y>
    shared_ptr(shared_ptr<Y> const & r, detail::static_cast_tag): px(static_cast<element_type *>(r.px)), pn(r.pn)
    {
    }

    template<typename Y>
    shared_ptr(shared_ptr<Y> const & r, detail::dynamic_cast_tag): px(dynamic_cast<element_type *>(r.px)), pn(r.pn)
    {
        if (px == 0) // need to allocate new counter -- the cast failed
        {
            pn = detail::shared_count(static_cast<element_type *>(0), deleter());
        }
    }

#ifndef BOOST_NO_AUTO_PTR

    template<typename Y>
    explicit shared_ptr(std::auto_ptr<Y> & r): px(r.get()), pn(r)
    {
    }

#endif 

    template<typename Y>
    shared_ptr & operator=(shared_ptr<Y> const & r) // never throws
    {
        px = r.px;
        pn = r.pn; // shared_count::op= doesn't throw
        return *this;
    }

#ifndef BOOST_NO_AUTO_PTR

    template<typename Y>
    shared_ptr & operator=(std::auto_ptr<Y> & r)
    {
        this_type(r).swap(*this);
        return *this;
    }

#endif

    void reset(T * p = 0)
    {
        BOOST_ASSERT(p == 0 || p != px);
        this_type(p).swap(*this);
    }

    template<typename D> void reset(T * p, D d)
    {
        this_type(p, d).swap(*this);
    }

    typename detail::shared_ptr_traits<T>::reference operator* () const // never throws
    {
        BOOST_ASSERT(px != 0);
        return *px;
    }

    T * operator-> () const // never throws
    {
        BOOST_ASSERT(px != 0);
        return px;
    }
    
    T * get() const // never throws
    {
        return px;
    }

    bool unique() const // never throws
    {
        return pn.unique();
    }

    long use_count() const // never throws
    {
        return pn.use_count();
    }

    void swap(shared_ptr<T> & other) // never throws
    {
        std::swap(px, other.px);
        pn.swap(other.pn);
    }

// Tasteless as this may seem, making all members public allows member templates
// to work in the absence of member template friends. (Matthew Langston)

#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS

private:

    template<typename Y> friend class shared_ptr;
    template<typename Y> friend class weak_ptr;


#endif

    T * px;                     // contained pointer
    detail::shared_count pn;    // reference counter

};  // shared_ptr

template<typename T, typename U> inline bool operator==(shared_ptr<T> const & a, shared_ptr<U> const & b)
{
    return a.get() == b.get();
}

template<typename T, typename U> inline bool operator!=(shared_ptr<T> const & a, shared_ptr<U> const & b)
{
    return a.get() != b.get();
}

template<typename T> inline bool operator<(shared_ptr<T> const & a, shared_ptr<T> const & b)
{
    return std::less<T*>()(a.get(), b.get());
}

template<typename T> void swap(shared_ptr<T> & a, shared_ptr<T> & b)
{
    a.swap(b);
}

template<typename T, typename U> shared_ptr<T> shared_static_cast(shared_ptr<U> const & r)
{
    return shared_ptr<T>(r, detail::static_cast_tag());
}

template<typename T, typename U> shared_ptr<T> shared_dynamic_cast(shared_ptr<U> const & r)
{
    return shared_ptr<T>(r, detail::dynamic_cast_tag());
}

// get_pointer() enables boost::mem_fn to recognize shared_ptr

template<typename T> inline T * get_pointer(shared_ptr<T> const & p)
{
    return p.get();
}

} // namespace boost

#ifdef BOOST_MSVC
# pragma warning(pop)
#endif    

#endif  // #ifndef BOOST_MSVC6_MEMBER_TEMPLATES

#endif  // #ifndef BOOST_SHARED_PTR_HPP_INCLUDED
