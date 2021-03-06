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

#ifndef BOOST_UBLAS_DUFF_H
#define BOOST_UBLAS_DUFF_H

#define DD_SWITCH(n, d, r, expr) \
    { \
        unsigned r = ((n) + (d) - 1) / (d); \
        switch ((n) % (d))  { \
        case 0: do { expr;
#define DD_CASE_I(i, expr) \
        case (i): expr;
#define DD_WHILE(r) \
            } while (-- (r) > 0); \
        } \
    }

#define DD_1T(n, d, r, expr) \
    DD_WHILE(r)
#define DD_2T(n, d, r, expr) \
    DD_CASE_I(1, expr) \
    DD_1T(n, d, r, expr)
#define DD_3T(n, d, r, expr) \
    DD_CASE_I(2, expr) \
    DD_2T(n, d, r, expr)
#define DD_4T(n, d, r, expr) \
    DD_CASE_I(3, expr) \
    DD_3T(n, d, r, expr)
#define DD_5T(n, d, r, expr) \
    DD_CASE_I(4, expr) \
    DD_4T(n, d, r, expr)
#define DD_6T(n, d, r, expr) \
    DD_CASE_I(5, expr) \
    DD_5T(n, d, r, expr)
#define DD_7T(n, d, r, expr) \
    DD_CASE_I(6, expr) \
    DD_6T(n, d, r, expr)
#define DD_8T(n, d, r, expr) \
    DD_CASE_I(7, expr) \
    DD_7T(n, d, r, expr)

#define DD(n, d, r, expr) \
    DD_SWITCH(n, d, r, expr) \
    DD_##d##T(n, d, r, expr)

#endif
