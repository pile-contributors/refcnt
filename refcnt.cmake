
# enable/disable debug messages related to this pile
set (REFCNT_DEBUG_MSG ON)

# make sure support code is present; no harm
# in including it twice; the user, however, should have used
# pileInclude() from pile_support.cmake module.
include(pile_support)

# initialize this module
macro    (refcntInit
          ref_cnt_use_mode)

    # default name
    if (NOT REF_CNT_INIT_NAME)
        set(REF_CNT_INIT_NAME "RefCnt")
    endif ()

    # compose the list of headers and sources
    set(REFCNT_HEADERS
        "refcnt.h")
    set(REFCNT_SOURCES
        "refcnt.cc")

    pileSetSources(
        "${REF_CNT_INIT_NAME}"
        "${REFCNT_HEADERS}"
        "${REFCNT_SOURCES}")

    pileSetCommon(
        "${REF_CNT_INIT_NAME}"
        "0;0;1;d"
        "${ref_cnt_use_mode}"
        ""
        "basics"
        "referece-count;management")

endmacro ()
