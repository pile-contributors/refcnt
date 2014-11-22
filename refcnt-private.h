/**
 * @file refcnt-private.h
 * @brief Declarations for RefCnt class
 * @author Nicu Tofan <nicu.tofan@gmail.com>
 * @copyright Copyright 2014 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#ifndef GUARD_REFCNT_PRIVATE_H_INCLUDE
#define GUARD_REFCNT_PRIVATE_H_INCLUDE

#include <refcnt/refcnt-config.h>

#if 0
#    define REFCNT_DEBUGM printf
#else
#    define REFCNT_DEBUGM black_hole
#endif

#if 0
#    define REFCNT_TRACE_ENTRY printf("REFCNT ENTRY %s in %s[%d]\n", __func__, __FILE__, __LINE__)
#else
#    define REFCNT_TRACE_ENTRY
#endif

#if 0
#    define REFCNT_TRACE_EXIT printf("REFCNT EXIT %s in %s[%d]\n", __func__, __FILE__, __LINE__)
#else
#    define REFCNT_TRACE_EXIT
#endif


static inline void black_hole (...)
{}

#endif // GUARD_REFCNT_PRIVATE_H_INCLUDE
