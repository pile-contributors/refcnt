#include "refcnt.h"
RefCnt::RefCnt() :
    ref_cnt_(1)
{}
RefCnt::~RefCnt()
{}
