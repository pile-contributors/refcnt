/**
 * @file refcnt.h
 * @brief Declarations for RefCnt class
 * @author Nicu Tofan <nicu.tofan@gmail.com>
 * @copyright Copyright 2014 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#ifndef GUARD_REFCNT_H_INCLUDE
#define GUARD_REFCNT_H_INCLUDE

#include <refcnt/refcnt-config.h>

//! A reference counted base class.
class REFCNT_EXPORT RefCnt {

private:

    int ref_cnt_;           ///< The actual reference count.
#   ifdef REFCNT_DEBUG
    void ** owners_list_;   ///< List of owners - pointer.
    int owners_list_used_;  ///< List of owners - number of
                            ///< used entries.
    int owners_list_alloc_; ///< List of owners - number of
                            ///< allocated entries.
#   endif // REFCNT_DEBUG

protected:

    //! Default constructor.
    RefCnt ();

    //! Destructor.
    virtual ~RefCnt();

    //! Copy constructor.
    RefCnt (const RefCnt& other) :
        ref_cnt_(other.ref_cnt_),
        owners_list_(other.owners_list_),
        owners_list_used_(other.owners_list_used_),
        owners_list_alloc_(other.owners_list_alloc_)
    {}

    //! assignment operator
    RefCnt& operator= (const RefCnt& other) {
        ref_cnt_ = other.ref_cnt_;
        owners_list_ = other.owners_list_;
        owners_list_used_ = other.owners_list_used_;
        owners_list_alloc_ = other.owners_list_alloc_;
        return *this;
    }

public:


    //! increments the reference counter
    ///
    /// @return the value of the reference counter after increment.
    int
    reference (
            void * owner);

    //! decrements the reference counter
    ///
    /// @return the value of the reference counter after decrement.
    int
    dereference (
            void * owner);

    //! decrements the reference counter and deletes the instance if 0
    ///
    /// The caller must make sure that the reference count does not go below 0.
    /// @return the value of the reference counter after decrement.
    int
    release (
            void * owner);


    //! get the value of the reference count
    ///
    /// @return the value of the reference counter after decrement.
    int
    referenceCount () {
        return ref_cnt_;
    }

    //! deletes the instance
    ///
    /// @return the value of the reference counter.
    int
    forceRelease ();

    //! change the owner of a reference
    ///
    /// This does absolutely nothing in release builds.
#   ifdef REFCNT_DEBUG
    void
    changeOwner (
            void * current_owner,
            void * new_owner);
#   else // REFCNT_DEBUG
    inline void
    changeOwner (
            void *,
            void *) {}
#   endif // REFCNT_DEBUG



    //! tell if a pointer owns a reference to this object
    ///
    /// In release builds this always returns false.
#   ifdef REFCNT_DEBUG
    bool
    isOwner (
            void * value);
#   else // REFCNT_DEBUG
    inline bool
    isOwner (
            void *) {
        return false;
    }
#   endif // REFCNT_DEBUG



#   ifdef REFCNT_DEBUG
    //! print the list of owners for this instance
    void
    printReferenceList ();

    //! locate an owner (-1 if not found)
    int
    locateOwner (
            void * owner);
#   endif // REFCNT_DEBUG

public: virtual void anchorVtable() const;
};

#endif // GUARD_REFCNT_H_INCLUDE
