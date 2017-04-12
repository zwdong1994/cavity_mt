//
// Created by victor on 4/9/17.
//

#ifndef CAVITY_MT_CAV_IMPL_H
#define CAVITY_MT_CAV_IMPL_H

#include "handle.h"

template <typename T>
class cav_impl{
public:
    cav_impl();
    ~cav_impl();

public:
    handle* alloc_impl(T length);
    T dealloc_impl(handle *sst_f);
    int init_imple(T start, T end);
};

#endif //CAVITY_MT_CAV_IMPL_H
