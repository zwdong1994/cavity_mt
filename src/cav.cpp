//
// Created by victor on 4/10/17.
//

#include <pthread.h>
#include "cav_impl.h"
#include "cav.h"

cav::cav() {

}

cav::~cav() {

}

template <typename T>
pthread_t cav::alloc(T size, handle* h) {

    return cimpl.alloc_impl(size, h);
}

template <typename T>
T cav::dealloc(handle *sst_f) {

    return cimpl.dealloc_impl(sst_f);
}

template <typename T>
int cav::init(T start, T end) {

    return cimpl.init_impl(start, end);
}