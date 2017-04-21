//
// Created by victor on 4/9/17.
//

#ifndef CAVITY_MT_CAV_IMPL_H
#define CAVITY_MT_CAV_IMPL_H

#include <pthread.h>
#include <iostream>
#include "handle.h"


#define NO_MT 0
#define COMPLETLY_ALLOC 1
#define ALLOC_NOT_COMPLETE 2

#define SUCCESS 1
#define FAIL 0

template <typename T>
class cav_impl{
public:
    cav_impl();
    ~cav_impl();

public:
    pthread_t  alloc_impl(T length, handle *h);
    T dealloc_impl(handle *sst_f);
    int init_impl(T start, T end);

private:
    pthread_t pid;
    static void* start_pthread(void *arg);

private:
    typedef struct para_struct{
        cav_impl *this_;
        handle *h;
        T length;
    }par;

    struct alloc_str{
        int size;
        int addr;
        struct alloc_str *next;
    }*alloc;
    int alloc_run(T length, handle *h);
    int ocs_alloc_impl(T length, handle *h);
    int seek_ocs_mt(T length, handle *h, T *left_length);
};

#endif //CAVITY_MT_CAV_IMPL_H
