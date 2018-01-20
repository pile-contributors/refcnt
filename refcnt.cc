/**
 * @file refcnt.cc
 * @brief Definitions for Example class.
 * @author Nicu Tofan <nicu.tofan@gmail.com>
 * @copyright Copyright 2014 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#include <refcnt/refcnt.h>
#include "refcnt-private.h"

#ifdef REFCNT_DEBUG
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif // REFCNT_DEBUG

/**
 * @class RefCnt
 *
 * In debug builds an internal list of owners is stored so that
 * allocations can be traced. In release builds this adds no overhead.
 * This is controlled using the REFCNT_DEBUG definition.
 */

/* ------------------------------------------------------------------------- */
RefCnt::RefCnt() :
    ref_cnt_(0)
#   ifdef REFCNT_DEBUG
    , owners_list_(NULL)
    , owners_list_used_(0)
    , owners_list_alloc_(0)
#   endif // REFCNT_DEBUG
{
    REFCNT_TRACE_ENTRY;

#   ifdef REFCNT_DEBUG
    owners_list_alloc_ = 64;
    owners_list_ = (void**)malloc (sizeof(void*)*owners_list_alloc_);
    memset (owners_list_, 0, sizeof(void*)*owners_list_alloc_);
#   endif // REFCNT_DEBUG

    reference (this);

    REFCNT_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
RefCnt::~RefCnt()
{
    REFCNT_TRACE_ENTRY;

    REFCNT_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */

int RefCnt::reference (void * owner)
{
    ++ref_cnt_;
    REFCNT_DEBUGM("RefCnt for %p is incremented to %d for %p\n",
                      this, ref_cnt_, owner);
#   ifdef REFCNT_DEBUG
    if (owners_list_alloc_ == owners_list_used_) {
        owners_list_alloc_ *= 2;
        owners_list_ = (void**)realloc (
                    owners_list_,
                    sizeof(void*)*owners_list_alloc_);
    }
    owners_list_[owners_list_used_++] = owner;
#   endif // REFCNT_DEBUG
    return ref_cnt_;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
int RefCnt::dereference (void * owner)
{
    --ref_cnt_;
    REFCNT_DEBUGM("RefCnt for %p is dedcremented to %d by %p\n",
                      this, ref_cnt_, owner);

#ifdef REFCNT_DEBUG
    int i = locateOwner (owner);
    if (i == -1) {
        REFCNT_DEBUGM ("DEBUG ERROR! %p is not an owner\n", owner);
    } else {
        owners_list_[i] = NULL;
    }
#endif // REFCNT_DEBUG

    return ref_cnt_;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
int RefCnt::release (void * owner)
{
    int ret = dereference (owner);
    if (ret == 0) {
        delete this;
    } else if (ret < 0) {
        // TODO debug assert
        delete this;
    }
    return ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
int RefCnt::forceRelease ()
{
    int ret = ref_cnt_;
    delete this;
    return ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
#ifdef REFCNT_DEBUG
void  RefCnt::printReferenceList ()
{
    printf ("Owners list for instance %p:\n", this);
    for (int i = 0; i < owners_list_used_; ++i) {
        if (owners_list_[i] != NULL) {
            printf (" - %p\n", owners_list_[i]);
        }
    }
}
#endif // REFCNT_DEBUG
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
#ifdef REFCNT_DEBUG
int RefCnt::locateOwner (void * owner)
{
    for (int i = 0; i < owners_list_used_; ++i) {
        if ((owners_list_[i] != NULL) && (owners_list_[i] == owner)) {
            return i;
        }
    }
    return -1;
}
#endif // REFCNT_DEBUG
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
#ifdef REFCNT_DEBUG
void RefCnt::changeOwner (void * current_owner, void * new_owner)
{
    int i = locateOwner (current_owner);
    if (i == -1) {
        REFCNT_DEBUGM ("DEBUG ERROR! %p is not an owner\n", current_owner);
    } else {
        owners_list_[i] = new_owner;
    }
}
#endif // REFCNT_DEBUG
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
#ifdef REFCNT_DEBUG
bool RefCnt::isOwner (void * value)
{
    return locateOwner (value) != -1;
}
#endif // REFCNT_DEBUG
/* ========================================================================= */


