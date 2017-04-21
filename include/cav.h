//
// Created by victor on 4/10/17.
//

#ifndef CAVITY_MT_CAV_H
#define CAVITY_MT_CAV_H

#include <iostream>
#include "handle.h"
#include "cav_impl.h"

template <typename T>
class cav {
public:
    cav();
    ~cav();
    int alloc(T size, handle *h);
    T dealloc(handle *sst_f);
    int init(T start, T end);

};

template <typename T>
cav<T>::cav() {

}
template <typename T>
cav<T>::~cav() {

}

template <typename T>
int cav<T>::alloc(T size, handle* h) {
    cav_impl<T> cimpl;
    return cimpl.alloc_impl(size, h);
}

template <typename T>
T cav<T>::dealloc(handle *sst_f) {
    cav_impl<T> cimpl;
    return cimpl.dealloc_impl(sst_f);
}

template <typename T>
int cav<T>::init(T start, T end) {
    cav_impl<T> cimpl;
    return cimpl.init_impl(start, end);
}
#endif //CAVITY_MT_CAV_H
