//
// Created by victor on 4/10/17.
//

#include <pthread.h>
#include <iostream>
#include "cav.h"
#include "cav_impl.h"

template <class T>
cav<T>::cav() {

}
template <class T>
cav<T>::~cav() {

}

template <class T>
pthread_t cav<T>::alloc(T size, handle* h) {
    cav_impl<T> cimpl;
    return cimpl.alloc_impl(size, h);
}

template <class T>
T cav<T>::dealloc(handle *sst_f) {
    cav_impl<T> cimpl;
    return cimpl.dealloc_impl(sst_f);
}

template <class T>
int cav<T>::init(T start, T end) {
    cav_impl<T> cimpl;
    return cimpl.init_impl(start, end);
}