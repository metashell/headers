//
//  Copyright (c) 2000-2002
//  Joerg Walter, Mathias Koch
//
//  Permission to use, copy, modify, distribute and sell this software
//  and its documentation for any purpose is hereby granted without fee,
//  provided that the above copyright notice appear in all copies and
//  that both that copyright notice and this permission notice appear
//  in supporting documentation.  The authors make no representations
//  about the suitability of this software for any purpose.
//  It is provided "as is" without express or implied warranty.
//
//  The authors gratefully acknowledge the support of
//  GeNeSys mbH & Co. KG in producing this work.
//

#ifndef BOOST_UBLAS_VECTOR_PROXY_H
#define BOOST_UBLAS_VECTOR_PROXY_H

#include <boost/numeric/ublas/config.hpp>
#include <boost/numeric/ublas/vector_expression.hpp>

// Iterators based on ideas of Jeremy Siek

namespace boost { namespace numeric { namespace ublas {

    // Vector based range class
    template<class V>
    class vector_range:
        public vector_expression<vector_range<V> > {
    public:
#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
        BOOST_UBLAS_USING vector_expression<vector_range<V> >::operator ();
#endif
        typedef const V const_vector_type;
        typedef V vector_type;
        typedef typename V::size_type size_type;
        typedef typename V::difference_type difference_type;
        typedef typename V::value_type value_type;
        typedef typename V::const_reference const_reference;
        typedef typename V::reference reference;
        typedef typename V::const_pointer const_pointer;
        typedef typename V::pointer pointer;
#ifdef BOOST_UBLAS_ET_CLOSURE_REFERENCE
        typedef const vector_const_reference<const vector_range<vector_type> > const_closure_type;
        typedef vector_reference<vector_range<vector_type> > closure_type;
#endif
#ifdef BOOST_UBLAS_ET_CLOSURE_VALUE
        typedef const vector_range<vector_type> const_closure_type;
        typedef vector_range<vector_type> closure_type;
#endif
        typedef typename V::const_iterator const_iterator_type;
        typedef typename V::iterator iterator_type;
        typedef typename storage_restrict_traits<typename V::storage_category,
                                                 dense_proxy_tag>::storage_category storage_category;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        vector_range ():
            data_ (nil_), r_ () {}
#ifdef BOOST_UBLAS_ENABLE_INDEX_SET_ALL
        BOOST_UBLAS_INLINE
        vector_range (vector_type &data, const range<> &r):
            data_ (data), r_ (r.preprocess (data.size ())) {}
#else
        BOOST_UBLAS_INLINE
        vector_range (vector_type &data, const range &r):
            data_ (data), r_ (r) {}
#endif

        // Accessors
        BOOST_UBLAS_INLINE
        size_type start () const {
            return r_.start ();
        }
        BOOST_UBLAS_INLINE
        size_type size () const {
            return r_.size ();
        }
        BOOST_UBLAS_INLINE
        const_vector_type &data () const {
            return data_;
        }
        BOOST_UBLAS_INLINE
        vector_type &data () {
            return data_;
        }

#ifdef BOOST_UBLAS_DEPRECATED
        // Resetting
        BOOST_UBLAS_INLINE
        void reset (vector_type &data) {
            // data_ = data;
            data_.reset (data);
        }
        BOOST_UBLAS_INLINE
        void reset (vector_type &data, const range<> &r) {
            // data_ = data;
            data_.reset (data);
            r_ = r;
        }
#endif

        // Element access
        BOOST_UBLAS_INLINE
        const_reference operator () (size_type i) const {
            return data () (r_ (i));
        }
        BOOST_UBLAS_INLINE
        reference operator () (size_type i) {
            return data () (r_ (i));
        }

        BOOST_UBLAS_INLINE
        const_reference operator [] (size_type i) const {
            return (*this) (i);
        }
        BOOST_UBLAS_INLINE
        reference operator [] (size_type i) {
            return (*this) (i);
        }

#ifdef BOOST_UBLAS_ENABLE_INDEX_SET_ALL
        BOOST_UBLAS_INLINE
        vector_range<vector_type> project (const range<> &r) const {
            return vector_range<vector_type> (data_, r_.compose (r));
        }
#else
        BOOST_UBLAS_INLINE
        vector_range<vector_type> project (const range &r) const {
            return vector_range<vector_type> (data_, r_.compose (r));
        }
#endif

        // Assignment
        BOOST_UBLAS_INLINE
        vector_range &operator = (const vector_range &vr) {
            // FIXME: the ranges could be differently sized.
            // std::copy (vr.begin (), vr.end (), begin ());
            vector_assign<scalar_assign<value_type, value_type> > () (*this, vector<value_type> (vr));
            return *this;
        }
        BOOST_UBLAS_INLINE
        vector_range &assign_temporary (vector_range &vr) {
            // FIXME: this is suboptimal.
            // return *this = vr;
            vector_assign<scalar_assign<value_type, value_type> > () (*this, vr);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        vector_range &operator = (const vector_expression<AE> &ae) {
            vector_assign<scalar_assign<value_type, value_type> > () (*this, vector<value_type> (ae));
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        vector_range &assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        vector_range &operator += (const vector_expression<AE> &ae) {
            vector_assign<scalar_assign<value_type, value_type> > () (*this, vector<value_type> (*this + ae));
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        vector_range &plus_assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_plus_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        vector_range &operator -= (const vector_expression<AE> &ae) {
            vector_assign<scalar_assign<value_type, value_type> > () (*this, vector<value_type> (*this - ae));
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        vector_range &minus_assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_minus_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        vector_range &operator *= (const AT &at) {
            vector_assign_scalar<scalar_multiplies_assign<value_type, AT> > () (*this, at);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        vector_range &operator /= (const AT &at) {
            vector_assign_scalar<scalar_divides_assign<value_type, AT> > () (*this, at);
            return *this;
        }

        // Swapping
        BOOST_UBLAS_INLINE
        void swap (vector_range &vr) {
            // Too unusual semantic.
            // BOOST_UBLAS_CHECK (this != &vr, external_logic ());
            if (this != &vr) {
                BOOST_UBLAS_CHECK (size () == vr.size (), bad_size ());
                std::swap_ranges (begin (), end (), vr.begin ());
            }
        }
#ifdef BOOST_UBLAS_FRIEND_FUNCTION
        BOOST_UBLAS_INLINE
        friend void swap (vector_range &vr1, vector_range &vr2) {
            vr1.swap (vr2);
        }
#endif

#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
        typedef indexed_iterator<vector_range<vector_type>, 
                                 BOOST_UBLAS_TYPENAME vector_type::iterator::iterator_category> iterator;
        typedef indexed_const_iterator<vector_range<vector_type>, 
                                       BOOST_UBLAS_TYPENAME vector_type::const_iterator::iterator_category> const_iterator;
#else
        class const_iterator;
        class iterator;
#endif

        // Element lookup
        BOOST_UBLAS_INLINE
        const_iterator find_first (size_type i) const {
            const_iterator_type it (data ().find_first (start () + i));
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            return const_iterator (*this, it.index ());
#else
            return const_iterator (*this, it);
#endif
        }
        BOOST_UBLAS_INLINE
        iterator find_first (size_type i) {
            iterator_type it (data ().find_first (start () + i));
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            return iterator (*this, it.index ());
#else
            return iterator (*this, it);
#endif
        }
        BOOST_UBLAS_INLINE
        const_iterator find_last (size_type i) const {
            const_iterator_type it (data ().find_last (start () + i));
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            return const_iterator (*this, it.index ());
#else
            return const_iterator (*this, it);
#endif
        }
        BOOST_UBLAS_INLINE
        iterator find_last (size_type i) {
            iterator_type it (data ().find_last (start () + i));
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            return iterator (*this, it.index ());
#else
            return iterator (*this, it);
#endif
        }

        // Iterators simply are pointers.

#ifndef BOOST_UBLAS_USE_INDEXED_ITERATOR
        class const_iterator:
            public container_const_reference<vector_range>,
#ifdef BOOST_UBLAS_USE_ITERATOR_BASE_TRAITS
            public iterator_base_traits<typename V::const_iterator::iterator_category>::template
                        iterator_base<const_iterator, value_type>::type {
#else
            public random_access_iterator_base<typename V::const_iterator::iterator_category,
                                               const_iterator, value_type> {
#endif
        public:
            typedef typename V::const_iterator::iterator_category iterator_category;
            typedef typename V::const_iterator::difference_type difference_type;
            typedef typename V::const_iterator::value_type value_type;
            typedef typename V::const_iterator::reference reference;
            typedef typename V::const_iterator::pointer pointer;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            const_iterator ():
                container_const_reference<vector_range> (), it_ () {}
            BOOST_UBLAS_INLINE
            const_iterator (const vector_range &vr, const const_iterator_type &it):
                container_const_reference<vector_range> (vr), it_ (it) {}
#ifndef BOOST_UBLAS_QUALIFIED_TYPENAME
            BOOST_UBLAS_INLINE
            const_iterator (const iterator &it):
                container_const_reference<vector_range> (it ()), it_ (it.it_) {}
#else
            BOOST_UBLAS_INLINE
            const_iterator (const typename vector_range::iterator &it):
                container_const_reference<vector_range> (it ()), it_ (it.it_) {}
#endif

            // Arithmetic
            BOOST_UBLAS_INLINE
            const_iterator &operator ++ () {
                ++ it_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator &operator -- () {
                -- it_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator &operator += (difference_type n) {
                it_ += n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator &operator -= (difference_type n) {
                it_ -= n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            difference_type operator - (const const_iterator &it) const {
                return it_ - it.it_;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                BOOST_UBLAS_CHECK (index () < (*this) ().size (), bad_index ());
                return *it_;
            }

            // Index
            BOOST_UBLAS_INLINE
            size_type index () const {
                return it_.index () - (*this) ().start ();
            }

            // Assignment 
            BOOST_UBLAS_INLINE
            const_iterator &operator = (const const_iterator &it) {
                container_const_reference<vector_range>::assign (&it ());
                it_ = it.it_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const const_iterator &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it_ == it.it_;
            }
            BOOST_UBLAS_INLINE
            bool operator < (const const_iterator &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it_ < it.it_;
            }

        private:
            const_iterator_type it_;
        };
#endif

        BOOST_UBLAS_INLINE
        const_iterator begin () const {
            return find_first (0);
        }
        BOOST_UBLAS_INLINE
        const_iterator end () const {
            return find_last (size ());
        }

#ifndef BOOST_UBLAS_USE_INDEXED_ITERATOR
        class iterator:
            public container_reference<vector_range>,
#ifdef BOOST_UBLAS_USE_ITERATOR_BASE_TRAITS
            public iterator_base_traits<typename V::iterator::iterator_category>::template
                        iterator_base<iterator, value_type>::type {
#else
            public random_access_iterator_base<typename V::iterator::iterator_category,
                                               iterator, value_type> {
#endif
        public:
            typedef typename V::iterator::iterator_category iterator_category;
            typedef typename V::iterator::difference_type difference_type;
            typedef typename V::iterator::value_type value_type;
            typedef typename V::iterator::reference reference;
            typedef typename V::iterator::pointer pointer;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            iterator ():
                container_reference<vector_range> (), it_ () {}
            BOOST_UBLAS_INLINE
            iterator (vector_range &vr, const iterator_type &it):
                container_reference<vector_range> (vr), it_ (it) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            iterator &operator ++ () {
                ++ it_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator &operator -- () {
                -- it_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator &operator += (difference_type n) {
                it_ += n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator &operator -= (difference_type n) {
                it_ -= n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            difference_type operator - (const iterator &it) const {
                return it_ - it.it_;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                BOOST_UBLAS_CHECK (index () < (*this) ().size (), bad_index ());
                return *it_;
            }

            // Index
            BOOST_UBLAS_INLINE
            size_type index () const {
                return it_.index () - (*this) ().start ();
            }

            // Assignment 
            BOOST_UBLAS_INLINE
            iterator &operator = (const iterator &it) {
                container_reference<vector_range>::assign (&it ());
                it_ = it.it_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const iterator &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it_ == it.it_;
            }
            BOOST_UBLAS_INLINE
            bool operator < (const iterator &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it_ < it.it_;
            }

        private:
            iterator_type it_;

            friend class const_iterator;
        };
#endif

        BOOST_UBLAS_INLINE
        iterator begin () {
            return find_first (0);
        }
        BOOST_UBLAS_INLINE
        iterator end () {
            return find_last (size ());
        }

        // Reverse iterator

#ifdef BOOST_MSVC_STD_ITERATOR
        typedef reverse_iterator_base<const_iterator, value_type, const_reference> const_reverse_iterator;
#else
        typedef reverse_iterator_base<const_iterator> const_reverse_iterator;
#endif

        BOOST_UBLAS_INLINE
        const_reverse_iterator rbegin () const {
            return const_reverse_iterator (end ());
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator rend () const {
            return const_reverse_iterator (begin ());
        }

#ifdef BOOST_MSVC_STD_ITERATOR
        typedef reverse_iterator_base<iterator, value_type, reference> reverse_iterator;
#else
        typedef reverse_iterator_base<iterator> reverse_iterator;
#endif

        BOOST_UBLAS_INLINE
        reverse_iterator rbegin () {
            return reverse_iterator (end ());
        }
        BOOST_UBLAS_INLINE
        reverse_iterator rend () {
            return reverse_iterator (begin ());
        }

    private:
        vector_type &data_;
#ifdef BOOST_UBLAS_ENABLE_INDEX_SET_ALL
        range<> r_;
#else
        range r_;
#endif
        static vector_type nil_;
    };

    template<class V>
    typename vector_range<V>::vector_type vector_range<V>::nil_;

    // Projections
#ifdef BOOST_UBLAS_ENABLE_INDEX_SET_ALL
    template<class V>
    BOOST_UBLAS_INLINE
    vector_range<V> project (V &data, const range<> &r) {
        return vector_range<V> (data, r);
    }
#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
    template<class V>
    BOOST_UBLAS_INLINE
    const vector_range<const V> project (const V &data, const range<> &r) {
        return vector_range<const V> (data, r);
    }
    template<class V>
    BOOST_UBLAS_INLINE
    vector_range<V> project (const vector_range<V> &data, const range<> &r) {
        return data.project (r);
    }
#endif
#else
    template<class V>
    BOOST_UBLAS_INLINE
    vector_range<V> project (V &data, const range &r) {
        return vector_range<V> (data, r);
    }
#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
    template<class V>
    BOOST_UBLAS_INLINE
    const vector_range<const V> project (const V &data, const range &r) {
        return vector_range<const V> (data, r);
    }
    template<class V>
    BOOST_UBLAS_INLINE
    vector_range<V> project (const vector_range<V> &data, const range &r) {
        return data.project (r);
    }
#endif
#endif

    // Vector based slice class
    template<class V>
    class vector_slice:
        public vector_expression<vector_slice<V> > {
    public:
#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
        BOOST_UBLAS_USING vector_expression<vector_slice<V> >::operator ();
#endif
        typedef const V const_vector_type;
        typedef V vector_type;
        typedef typename V::size_type size_type;
        typedef typename V::difference_type difference_type;
        typedef typename V::value_type value_type;
        typedef typename V::const_reference const_reference;
        typedef typename V::reference reference;
        typedef typename V::const_pointer const_pointer;
        typedef typename V::pointer pointer;
#ifdef BOOST_UBLAS_ET_CLOSURE_REFERENCE
        typedef const vector_const_reference<const vector_slice<vector_type> > const_closure_type;
        typedef vector_reference<vector_slice<vector_type> > closure_type;
#endif
#ifdef BOOST_UBLAS_ET_CLOSURE_VALUE
        typedef const vector_slice<vector_type> const_closure_type;
        typedef vector_slice<vector_type> closure_type;
#endif
#ifdef BOOST_UBLAS_ENABLE_INDEX_SET_ALL
        typedef slice<>::const_iterator const_iterator_type;
        typedef slice<>::const_iterator iterator_type;
#else
        typedef slice::const_iterator const_iterator_type;
        typedef slice::const_iterator iterator_type;
#endif
        typedef typename storage_restrict_traits<typename V::storage_category,
                                                 dense_proxy_tag>::storage_category storage_category;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        vector_slice ():
            data_ (nil_), s_ () {}
#ifdef BOOST_UBLAS_ENABLE_INDEX_SET_ALL
        BOOST_UBLAS_INLINE
        vector_slice (vector_type &data, const slice<> &s):
            data_ (data), s_ (s.preprocess (data.size ())) {}
#else
        BOOST_UBLAS_INLINE
        vector_slice (vector_type &data, const slice &s):
            data_ (data), s_ (s) {}
#endif

        // Accessors
        BOOST_UBLAS_INLINE
        size_type start () const {
            return s_.start ();
        }
        BOOST_UBLAS_INLINE
        difference_type stride () const {
            return s_.stride ();
        }
        BOOST_UBLAS_INLINE
        size_type size () const { 
            return s_.size (); 
        }
        BOOST_UBLAS_INLINE
        const_vector_type &data () const {
            return data_;
        }
        BOOST_UBLAS_INLINE
        vector_type &data () {
            return data_;
        }

#ifdef BOOST_UBLAS_DEPRECATED
        // Resetting
        BOOST_UBLAS_INLINE
        void reset (vector_type &data) {
            // data_ = data;
            data_.reset (data);
        }
        BOOST_UBLAS_INLINE
        void reset (vector_type &data, const slice<> &s) {
            // data_ = data;
            data_.reset (data);
            s_ = s;
        }
#endif

        // Element access
        BOOST_UBLAS_INLINE
        const_reference operator () (size_type i) const {
            return data () (s_ (i)); 
        }
        BOOST_UBLAS_INLINE
        reference operator () (size_type i) {
            return data () (s_ (i)); 
        }

        BOOST_UBLAS_INLINE
        const_reference operator [] (size_type i) const { 
            return (*this) (i); 
        }
        BOOST_UBLAS_INLINE
        reference operator [] (size_type i) {
            return (*this) (i); 
        }

#ifdef BOOST_UBLAS_ENABLE_INDEX_SET_ALL
        BOOST_UBLAS_INLINE
        vector_slice<vector_type> project (const range<> &r) const {
            return vector_slice<vector_type>  (data_, s_.compose (r));
        }
        BOOST_UBLAS_INLINE
        vector_slice<vector_type> project (const slice<> &s) const {
            return vector_slice<vector_type>  (data_, s_.compose (s));
        }
#else
        BOOST_UBLAS_INLINE
        vector_slice<vector_type> project (const range &r) const {
            return vector_slice<vector_type>  (data_, s_.compose (r));
        }
        BOOST_UBLAS_INLINE
        vector_slice<vector_type> project (const slice &s) const {
            return vector_slice<vector_type>  (data_, s_.compose (s));
        }
#endif

        // Assignment
        BOOST_UBLAS_INLINE
        vector_slice &operator = (const vector_slice &vs) { 
            // FIXME: the slices could be differently sized.
            // std::copy (vs.begin (), vs.end (), begin ());
            vector_assign<scalar_assign<value_type, value_type> > () (*this, vector<value_type> (vs));
            return *this;
        }
        BOOST_UBLAS_INLINE
        vector_slice &assign_temporary (vector_slice &vs) {
            // FIXME: this is suboptimal.
            // return *this = vs;
            vector_assign<scalar_assign<value_type, value_type> > () (*this, vs);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        vector_slice &operator = (const vector_expression<AE> &ae) {
            vector_assign<scalar_assign<value_type, value_type> > () (*this, vector<value_type> (ae));
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        vector_slice &assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        vector_slice &operator += (const vector_expression<AE> &ae) {
            vector_assign<scalar_assign<value_type, value_type> > () (*this, vector<value_type> (*this + ae));
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        vector_slice &plus_assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_plus_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        vector_slice &operator -= (const vector_expression<AE> &ae) {
            vector_assign<scalar_assign<value_type, value_type> > () (*this, vector<value_type> (*this - ae));
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        vector_slice &minus_assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_minus_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        vector_slice &operator *= (const AT &at) {
            vector_assign_scalar<scalar_multiplies_assign<value_type, AT> > () (*this, at);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        vector_slice &operator /= (const AT &at) {
            vector_assign_scalar<scalar_divides_assign<value_type, AT> > () (*this, at);
            return *this;
        }

        // Swapping
        BOOST_UBLAS_INLINE
        void swap (vector_slice &vs) {
            // Too unusual semantic.
            // BOOST_UBLAS_CHECK (this != &vs, external_logic ());
            if (this != &vs) {
                BOOST_UBLAS_CHECK (size () == vs.size (), bad_size ());
                std::swap_ranges (begin (), end (), vs.begin ());
            }
        }
#ifdef BOOST_UBLAS_FRIEND_FUNCTION
        BOOST_UBLAS_INLINE
        friend void swap (vector_slice &vs1, vector_slice &vs2) {
            vs1.swap (vs2);
        }
#endif

#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
        typedef indexed_iterator<vector_slice<vector_type>, 
                                 BOOST_UBLAS_TYPENAME vector_type::iterator::iterator_category> iterator;
        typedef indexed_const_iterator<vector_slice<vector_type>,
                                       BOOST_UBLAS_TYPENAME vector_type::const_iterator::iterator_category> const_iterator;
#else
        class const_iterator;
        class iterator;
#endif

        // Element lookup
        BOOST_UBLAS_INLINE
        const_iterator find_first (size_type i) const {
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            return const_iterator (*this, i);
#else
            return const_iterator (*this, s_.begin () + i);
#endif
        }
        BOOST_UBLAS_INLINE
        iterator find_first (size_type i) {
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            return iterator (*this, i);
#else
            return iterator (*this, s_.begin () + i);
#endif
        }
        BOOST_UBLAS_INLINE
        const_iterator find_last (size_type i) const {
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            return const_iterator (*this, i);
#else
            return const_iterator (*this, s_.begin () + i);
#endif
        }
        BOOST_UBLAS_INLINE
        iterator find_last (size_type i) {
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            return iterator (*this, i);
#else
            return iterator (*this, s_.begin () + i);
#endif
        }

        // Iterators simply are indices.

#ifndef BOOST_UBLAS_USE_INDEXED_ITERATOR
        class const_iterator:
            public container_const_reference<vector_slice>,
#ifdef BOOST_UBLAS_USE_ITERATOR_BASE_TRAITS
            public iterator_base_traits<typename V::const_iterator::iterator_category>::template
                        iterator_base<const_iterator, value_type>::type {
#else
            public random_access_iterator_base<typename V::const_iterator::iterator_category,
                                               const_iterator, value_type> {
#endif
        public:
            typedef typename V::const_iterator::iterator_category iterator_category;
            typedef typename V::const_iterator::difference_type difference_type;
            typedef typename V::const_iterator::value_type value_type;
            typedef typename V::const_iterator::reference reference;
            typedef typename V::const_iterator::pointer pointer;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            const_iterator ():
                container_const_reference<vector_slice> (), it_ () {}
            BOOST_UBLAS_INLINE
            const_iterator (const vector_slice &vs, const const_iterator_type &it):
                container_const_reference<vector_slice> (vs), it_ (it) {}
#ifndef BOOST_UBLAS_QUALIFIED_TYPENAME
            BOOST_UBLAS_INLINE
            const_iterator (const iterator &it):
                container_const_reference<vector_slice> (it ()), it_ (it.it_) {}
#else
            BOOST_UBLAS_INLINE
            const_iterator (const typename vector_slice::iterator &it):
                container_const_reference<vector_slice> (it ()), it_ (it.it_) {}
#endif

            // Arithmetic
            BOOST_UBLAS_INLINE
            const_iterator &operator ++ () {
                ++ it_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator &operator -- () {
                -- it_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator &operator += (difference_type n) {
                it_ += n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator &operator -= (difference_type n) {
                it_ -= n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            difference_type operator - (const const_iterator &it) const {
                return it_ - it.it_;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                BOOST_UBLAS_CHECK (index () < (*this) ().size (), bad_index ());
                return (*this) ().data () (*it_);
            }

            // Index
            BOOST_UBLAS_INLINE
            size_type index () const {
                return it_.index ();
            }

            // Assignment 
            BOOST_UBLAS_INLINE
            const_iterator &operator = (const const_iterator &it) {
                container_const_reference<vector_slice>::assign (&it ());
                it_ = it.it_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const const_iterator &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it_ == it.it_;
            }
            BOOST_UBLAS_INLINE
            bool operator < (const const_iterator &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it_ < it.it_;
            }

        private:
            const_iterator_type it_;
        };
#endif

        BOOST_UBLAS_INLINE
        const_iterator begin () const {
            return find_first (0);
        }
        BOOST_UBLAS_INLINE
        const_iterator end () const {
            return find_last (size ());
        }

#ifndef BOOST_UBLAS_USE_INDEXED_ITERATOR
        class iterator:
            public container_reference<vector_slice>,
#ifdef BOOST_UBLAS_USE_ITERATOR_BASE_TRAITS
            public iterator_base_traits<typename V::iterator::iterator_category>::template
                        iterator_base<iterator, value_type>::type {
#else
            public random_access_iterator_base<typename V::iterator::iterator_category,
                                               iterator, value_type> {
#endif
        public:
            typedef typename V::iterator::iterator_category iterator_category;
            typedef typename V::iterator::difference_type difference_type;
            typedef typename V::iterator::value_type value_type;
            typedef typename V::iterator::reference reference;
            typedef typename V::iterator::pointer pointer;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            iterator ():
                container_reference<vector_slice> (), it_ () {}
            BOOST_UBLAS_INLINE
            iterator (vector_slice &vs, const iterator_type &it):
                container_reference<vector_slice> (vs), it_ (it) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            iterator &operator ++ () {
                ++ it_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator &operator -- () {
                -- it_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator &operator += (difference_type n) {
                it_ += n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator &operator -= (difference_type n) {
                it_ -= n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            difference_type operator - (const iterator &it) const {
                return it_ - it.it_;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                BOOST_UBLAS_CHECK (index () < (*this) ().size (), bad_index ());
                return (*this) ().data () (*it_);
            }

            // Index
            BOOST_UBLAS_INLINE
            size_type index () const {
                return it_.index ();
            }

            // Assignment 
            BOOST_UBLAS_INLINE
            iterator &operator = (const iterator &it) {
                container_reference<vector_slice>::assign (&it ());
                it_ = it.it_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const iterator &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it_ == it.it_;
            }
            BOOST_UBLAS_INLINE
            bool operator < (const iterator &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it_ < it.it_;
            }

        private:
            iterator_type it_;

            friend class const_iterator;
        };
#endif

        BOOST_UBLAS_INLINE
        iterator begin () {
            return find_first (0);
        }
        BOOST_UBLAS_INLINE
        iterator end () {
            return find_last (size ());
        }

        // Reverse iterator

#ifdef BOOST_MSVC_STD_ITERATOR
        typedef reverse_iterator_base<const_iterator, value_type, const_reference> const_reverse_iterator;
#else
        typedef reverse_iterator_base<const_iterator> const_reverse_iterator;
#endif

        BOOST_UBLAS_INLINE
        const_reverse_iterator rbegin () const {
            return const_reverse_iterator (end ());
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator rend () const {
            return const_reverse_iterator (begin ());
        }

#ifdef BOOST_MSVC_STD_ITERATOR
        typedef reverse_iterator_base<iterator, value_type, reference> reverse_iterator;
#else
        typedef reverse_iterator_base<iterator> reverse_iterator;
#endif

        BOOST_UBLAS_INLINE
        reverse_iterator rbegin () {
            return reverse_iterator (end ());
        }
        BOOST_UBLAS_INLINE
        reverse_iterator rend () {
            return reverse_iterator (begin ());
        }

    private:
        vector_type &data_;
#ifdef BOOST_UBLAS_ENABLE_INDEX_SET_ALL
        slice<> s_;
#else
        slice s_;
#endif
        static vector_type nil_;
    };

    template<class V>
    typename vector_slice<V>::vector_type vector_slice<V>::nil_;

    // Projections
#ifdef BOOST_UBLAS_ENABLE_INDEX_SET_ALL
#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
    template<class V>
    BOOST_UBLAS_INLINE
    vector_slice<V> project (const vector_slice<V> &data, const range<> &r) {
        return data.project (r);
    }
#endif
    template<class V>
    BOOST_UBLAS_INLINE
    vector_slice<V> project (V &data, const slice<> &s) {
        return vector_slice<V> (data, s);
    }
#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
    template<class V>
    BOOST_UBLAS_INLINE
    const vector_slice<const V> project (const V &data, const slice<> &s) {
        return vector_slice<const V> (data, s);
    }
    template<class V>
    BOOST_UBLAS_INLINE
    vector_slice<V> project (const vector_slice<V> &data, const slice<> &s) {
        return data.project (s);
    }
#endif
#else
#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
    template<class V>
    BOOST_UBLAS_INLINE
    vector_slice<V> project (const vector_slice<V> &data, const range &r) {
        return data.project (r);
    }
#endif
    template<class V>
    BOOST_UBLAS_INLINE
    vector_slice<V> project (V &data, const slice &s) {
        return vector_slice<V> (data, s);
    }
#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
    template<class V>
    BOOST_UBLAS_INLINE
    const vector_slice<const V> project (const V &data, const slice &s) {
        return vector_slice<const V> (data, s);
    }
    template<class V>
    BOOST_UBLAS_INLINE
    vector_slice<V> project (const vector_slice<V> &data, const slice &s) {
        return data.project (s);
    }
#endif
#endif

    // Vector based indirection class
    // Contributed by Toon Knapen.
    // Extended and optimized by Kresimir Fresl.
    template<class V, class IA>
    class vector_indirect:
        public vector_expression<vector_indirect<V, IA> > {
    public:
#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
        BOOST_UBLAS_USING vector_expression<vector_indirect<V, IA> >::operator ();
#endif
        typedef const V const_vector_type;
        typedef V vector_type;
        typedef const IA const_indirect_array_type;
        typedef IA indirect_array_type;
        typedef typename V::size_type size_type;
        typedef typename V::difference_type difference_type;
        typedef typename V::value_type value_type;
        typedef typename V::const_reference const_reference;
        typedef typename V::reference reference;
        typedef typename V::const_pointer const_pointer;
        typedef typename V::pointer pointer;
#ifdef BOOST_UBLAS_ET_CLOSURE_REFERENCE
        typedef const vector_const_reference<const vector_indirect<vector_type, indirect_array_type> > const_closure_type;
        typedef vector_reference<vector_indirect<vector_type, indirect_array_type> > closure_type;
#endif
#ifdef BOOST_UBLAS_ET_CLOSURE_VALUE
        typedef const vector_indirect<vector_type, indirect_array_type> const_closure_type;
        typedef vector_indirect<vector_type, indirect_array_type> closure_type;
#endif
        typedef typename IA::const_iterator const_iterator_type;
        typedef typename IA::const_iterator iterator_type;
        typedef typename storage_restrict_traits<typename V::storage_category,
                                                 dense_proxy_tag>::storage_category storage_category;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        vector_indirect ():
            data_ (nil_), ia_ () {}
        BOOST_UBLAS_INLINE
        vector_indirect (vector_type &data, size_type size):
            data_ (data), ia_ (size) {}
#ifdef BOOST_UBLAS_ENABLE_INDEX_SET_ALL
        BOOST_UBLAS_INLINE
        vector_indirect (vector_type &data, const indirect_array_type &ia):
            data_ (data), ia_ (ia.preprocess (data.size ())) {}
#else
        BOOST_UBLAS_INLINE
        vector_indirect (vector_type &data, const indirect_array_type &ia):
            data_ (data), ia_ (ia) {}
#endif

        // Accessors
        BOOST_UBLAS_INLINE
        size_type size () const {
            return ia_.size ();
        }
        BOOST_UBLAS_INLINE
        const_vector_type &data () const {
            return data_;
        }
        BOOST_UBLAS_INLINE
        vector_type &data () {
            return data_;
        }
        BOOST_UBLAS_INLINE
        const_indirect_array_type &indirect () const {
            return ia_;
        }
        BOOST_UBLAS_INLINE
        indirect_array_type &indirect () {
            return ia_;
        }

#ifdef BOOST_UBLAS_DEPRECATED
        // Resetting
        BOOST_UBLAS_INLINE
        void reset (vector_type &data) {
            // data_ = data;
            data_.reset (data);
        }
        BOOST_UBLAS_INLINE
        void reset (vector_type &data, const indirect_array_type &ia) {
            // data_ = data;
            data_.reset (data);
            ia_ = ia;
        }
#endif

        // Element access
        BOOST_UBLAS_INLINE
        const_reference operator () (size_type i) const {
            return data () (ia_ (i));
        }
        BOOST_UBLAS_INLINE
        reference operator () (size_type i) {
            return data () (ia_ (i));
        }

        BOOST_UBLAS_INLINE
        const_reference operator [] (size_type i) const {
            return (*this) (i);
        }
        BOOST_UBLAS_INLINE
        reference operator [] (size_type i) {
            return (*this) (i);
        }

#ifdef BOOST_UBLAS_ENABLE_INDEX_SET_ALL
        BOOST_UBLAS_INLINE
        vector_indirect<vector_type, indirect_array_type> project (const range<> &r) const {
            return vector_indirect<vector_type, indirect_array_type> (data_, ia_.compose (r));
        }
        BOOST_UBLAS_INLINE
        vector_indirect<vector_type, indirect_array_type> project (const slice<> &s) const {
            return vector_indirect<vector_type, indirect_array_type> (data_, ia_.compose (s));
        }
#else
        BOOST_UBLAS_INLINE
        vector_indirect<vector_type, indirect_array_type> project (const range &r) const {
            return vector_indirect<vector_type, indirect_array_type> (data_, ia_.compose (r));
        }
        BOOST_UBLAS_INLINE
        vector_indirect<vector_type, indirect_array_type> project (const slice &s) const {
            return vector_indirect<vector_type, indirect_array_type> (data_, ia_.compose (s));
        }
#endif
        BOOST_UBLAS_INLINE
        vector_indirect<vector_type, indirect_array_type> project (const indirect_array_type &ia) const {
            return vector_indirect<vector_type, indirect_array_type> (data_, ia_.compose (ia));
        }

        // Assignment
        BOOST_UBLAS_INLINE
        vector_indirect &operator = (const vector_indirect &vi) {
            // FIXME: the indirect_arrays could be differently sized.
            // std::copy (vi.begin (), vi.end (), begin ());
            vector_assign<scalar_assign<value_type, value_type> > () (*this, vector<value_type> (vi));
            return *this;
        }
        BOOST_UBLAS_INLINE
        vector_indirect &assign_temporary (vector_indirect &vi) {
            // FIXME: this is suboptimal.
            // return *this = vi;
            vector_assign<scalar_assign<value_type, value_type> > () (*this, vi);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        vector_indirect &operator = (const vector_expression<AE> &ae) {
            vector_assign<scalar_assign<value_type, value_type> > () (*this, vector<value_type> (ae));
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        vector_indirect &assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        vector_indirect &operator += (const vector_expression<AE> &ae) {
            vector_assign<scalar_assign<value_type, value_type> > () (*this, vector<value_type> (*this + ae));
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        vector_indirect &plus_assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_plus_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        vector_indirect &operator -= (const vector_expression<AE> &ae) {
            vector_assign<scalar_assign<value_type, value_type> > () (*this, vector<value_type> (*this - ae));
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        vector_indirect &minus_assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_minus_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        vector_indirect &operator *= (const AT &at) {
            vector_assign_scalar<scalar_multiplies_assign<value_type, AT> > () (*this, at);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        vector_indirect &operator /= (const AT &at) {
            vector_assign_scalar<scalar_divides_assign<value_type, AT> > () (*this, at);
            return *this;
        }

        // Swapping
        BOOST_UBLAS_INLINE
        void swap (vector_indirect &vi) {
            // Too unusual semantic.
            // BOOST_UBLAS_CHECK (this != &vi, external_logic ());
            if (this != &vi) {
                BOOST_UBLAS_CHECK (size () == vi.size (), bad_size ());
                std::swap_ranges (begin (), end (), vi.begin ());
            }
        }
#ifdef BOOST_UBLAS_FRIEND_FUNCTION
        BOOST_UBLAS_INLINE
        friend void swap (vector_indirect &vi1, vector_indirect &vi2) {
            vi1.swap (vi2);
        }
#endif

#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
        typedef indexed_iterator<vector_indirect<vector_type, indirect_array_type>,
                                 BOOST_UBLAS_TYPENAME vector_type::iterator::iterator_category> iterator;
        typedef indexed_const_iterator<vector_indirect<vector_type, indirect_array_type>,
                                       BOOST_UBLAS_TYPENAME vector_type::const_iterator::iterator_category> const_iterator;
#else
        class const_iterator;
        class iterator;
#endif

        // Element lookup
        BOOST_UBLAS_INLINE
        const_iterator find_first (size_type i) const {
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            return const_iterator (*this, i);
#else
            return const_iterator (*this, ia_.begin () + i);
#endif
        }
        BOOST_UBLAS_INLINE
        iterator find_first (size_type i) {
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            return iterator (*this, i);
#else
            return iterator (*this, ia_.begin () + i);
#endif
        }
        BOOST_UBLAS_INLINE
        const_iterator find_last (size_type i) const {
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            return const_iterator (*this, i);
#else
            return const_iterator (*this, ia_.begin () + i);
#endif
        }
        BOOST_UBLAS_INLINE
        iterator find_last (size_type i) {
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            return iterator (*this, i);
#else
            return iterator (*this, ia_.begin () + i);
#endif
        }

        // Iterators simply are indices.

#ifndef BOOST_UBLAS_USE_INDEXED_ITERATOR
        class const_iterator:
            public container_const_reference<vector_indirect>,
#ifdef BOOST_UBLAS_USE_ITERATOR_BASE_TRAITS
            public iterator_base_traits<typename V::const_iterator::iterator_category>::template
                        iterator_base<const_iterator, value_type>::type {
#else
            public random_access_iterator_base<typename V::const_iterator::iterator_category,
                                               const_iterator, value_type> {
#endif
        public:
            typedef typename V::const_iterator::iterator_category iterator_category;
            typedef typename V::const_iterator::difference_type difference_type;
            typedef typename V::const_iterator::value_type value_type;
            typedef typename V::const_iterator::reference reference;
            typedef typename V::const_iterator::pointer pointer;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            const_iterator ():
                container_const_reference<vector_indirect> (), it_ () {}
            BOOST_UBLAS_INLINE
            const_iterator (const vector_indirect &vi, const const_iterator_type &it):
                container_const_reference<vector_indirect> (vi), it_ (it) {}
#ifndef BOOST_UBLAS_QUALIFIED_TYPENAME
            BOOST_UBLAS_INLINE
            const_iterator (const iterator &it):
                container_const_reference<vector_indirect> (it ()), it_ (it.it_) {}
#else
            BOOST_UBLAS_INLINE
            const_iterator (const typename vector_indirect::iterator &it):
                container_const_reference<vector_indirect> (it ()), it_ (it.it_) {}
#endif

            // Arithmetic
            BOOST_UBLAS_INLINE
            const_iterator &operator ++ () {
                ++ it_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator &operator -- () {
                -- it_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator &operator += (difference_type n) {
                it_ += n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator &operator -= (difference_type n) {
                it_ -= n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            difference_type operator - (const const_iterator &it) const {
                return it_ - it.it_;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                BOOST_UBLAS_CHECK (index () < (*this) ().size (), bad_index ());
                return (*this) ().data () (*it_);
            }

            // Index
            BOOST_UBLAS_INLINE
            size_type index () const {
                return it_.index ();
            }

            // Assignment
            BOOST_UBLAS_INLINE
            const_iterator &operator = (const const_iterator &it) {
                container_const_reference<vector_indirect>::assign (&it ());
                it_ = it.it_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const const_iterator &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it_ == it.it_;
            }
            BOOST_UBLAS_INLINE
            bool operator < (const const_iterator &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it_ < it.it_;
            }

        private:
            const_iterator_type it_;
        };
#endif

        BOOST_UBLAS_INLINE
        const_iterator begin () const {
            return find_first (0);
        }
        BOOST_UBLAS_INLINE
        const_iterator end () const {
            return find_last (size ());
        }

#ifndef BOOST_UBLAS_USE_INDEXED_ITERATOR
        class iterator:
            public container_reference<vector_indirect>,
#ifdef BOOST_UBLAS_USE_ITERATOR_BASE_TRAITS
            public iterator_base_traits<typename V::iterator::iterator_category>::template
                        iterator_base<iterator, value_type>::type {
#else
            public random_access_iterator_base<typename V::iterator::iterator_category,
                                               iterator, value_type> {
#endif
        public:
            typedef typename V::iterator::iterator_category iterator_category;
            typedef typename V::iterator::difference_type difference_type;
            typedef typename V::iterator::value_type value_type;
            typedef typename V::iterator::reference reference;
            typedef typename V::iterator::pointer pointer;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            iterator ():
                container_reference<vector_indirect> (), it_ () {}
            BOOST_UBLAS_INLINE
            iterator (vector_indirect &vi, const iterator_type &it):
                container_reference<vector_indirect> (vi), it_ (it) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            iterator &operator ++ () {
                ++ it_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator &operator -- () {
                -- it_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator &operator += (difference_type n) {
                it_ += n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator &operator -= (difference_type n) {
                it_ -= n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            difference_type operator - (const iterator &it) const {
                return it_ - it.it_;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                BOOST_UBLAS_CHECK (index () < (*this) ().size (), bad_index ());
                return (*this) ().data () (*it_);
            }

            // Index
            BOOST_UBLAS_INLINE
            size_type index () const {
                return it_.index ();
            }

            // Assignment
            BOOST_UBLAS_INLINE
            iterator &operator = (const iterator &it) {
                container_reference<vector_indirect>::assign (&it ());
                it_ = it.it_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const iterator &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it_ == it.it_;
            }
            BOOST_UBLAS_INLINE
            bool operator < (const iterator &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it_ < it.it_;
            }

        private:
            iterator_type it_;

            friend class const_iterator;
        };
#endif

        BOOST_UBLAS_INLINE
        iterator begin () {
            return find_first (0);
        }
        BOOST_UBLAS_INLINE
        iterator end () {
            return find_last (size ());
        }

        // Reverse iterator

#ifdef BOOST_MSVC_STD_ITERATOR
        typedef reverse_iterator_base<const_iterator, value_type, const_reference> const_reverse_iterator;
#else
        typedef reverse_iterator_base<const_iterator> const_reverse_iterator;
#endif

        BOOST_UBLAS_INLINE
        const_reverse_iterator rbegin () const {
            return const_reverse_iterator (end ());
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator rend () const {
            return const_reverse_iterator (begin ());
        }

#ifdef BOOST_MSVC_STD_ITERATOR
        typedef reverse_iterator_base<iterator, value_type, reference> reverse_iterator;
#else
        typedef reverse_iterator_base<iterator> reverse_iterator;
#endif

        BOOST_UBLAS_INLINE
        reverse_iterator rbegin () {
            return reverse_iterator (end ());
        }
        BOOST_UBLAS_INLINE
        reverse_iterator rend () {
            return reverse_iterator (begin ());
        }

    private:
        vector_type &data_;
        indirect_array_type ia_;
        static vector_type nil_;
    };

    template<class V, class IA>
    typename vector_indirect<V, IA>::vector_type vector_indirect<V, IA>::nil_;

    // Projections
#ifdef BOOST_UBLAS_ENABLE_INDEX_SET_ALL
#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
    template<class V, class IA>
    BOOST_UBLAS_INLINE
    vector_indirect<V, IA> project (const vector_indirect<V, IA> &data, const range<> &r) {
        return data.project (r);
    }
    template<class V, class IA>
    BOOST_UBLAS_INLINE
    vector_indirect<V, IA> project (const vector_indirect<V, IA> &data, const slice<> &s) {
        return data.project (s);
    }
#endif
#else
#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
    template<class V, class IA>
    BOOST_UBLAS_INLINE
    vector_indirect<V, IA> project (const vector_indirect<V, IA> &data, const range &r) {
        return data.project (r);
    }
    template<class V, class IA>
    BOOST_UBLAS_INLINE
    vector_indirect<V, IA> project (const vector_indirect<V, IA> &data, const slice &s) {
        return data.project (s);
    }
#endif
#endif
    // These signatures are to general for MSVC
    // template<class V, class IA>
    // BOOST_UBLAS_INLINE
    // vector_indirect<V, IA > project (V &data, const IA &ia) {
    //     return vector_indirect<V, IA > (data, ia);
    // }
#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
    // template<class V, class IA>
    // BOOST_UBLAS_INLINE
    // const vector_indirect<const V, IA> project (const V &data, const IA &ia) {
    //     return vector_indirect<const V, IA> (data, ia);
    // }
    // template<class V, class IA>
    // BOOST_UBLAS_INLINE
    // vector_indirect<V, IA> project (const vector_indirect<V, IA> &data, const IA &ia) {
    //     return data.project (ia);
    // }
#endif
    template<class V, class A>
    BOOST_UBLAS_INLINE
    vector_indirect<V, indirect_array<A> > project (V &data, const indirect_array<A> &ia) {
        return vector_indirect<V, indirect_array<A> > (data, ia);
    }
#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
    template<class V, class A>
    BOOST_UBLAS_INLINE
    const vector_indirect<const V, indirect_array<A> > project (const V &data, const indirect_array<A> &ia) {
        return vector_indirect<const V, indirect_array<A> > (data, ia);
    }
    template<class V, class A>
    BOOST_UBLAS_INLINE
    vector_indirect<V, indirect_array<A> > project (const vector_indirect<V, indirect_array<A> > &data, const indirect_array<A> &ia) {
        return data.project (ia);
    }
#endif

}}}

#endif




