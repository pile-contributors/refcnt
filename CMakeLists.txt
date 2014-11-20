if (NOT REFCNT_BUILD_MODE)
    set (REFCNT_BUILD_MODE STATIC)
endif ()

include(pile_support)
pileInclude (RefCnt)
refCntInit(${REFCNT_BUILD_MODE})
