//
// Created by victor on 4/10/17.
//

#ifndef CAVITY_MT_CAV_H
#define CAVITY_MT_CAV_H

#include <iostream>
#include "handle.h"


template <class T>
class cav {
public:
    cav();
    ~cav();
    pthread_t alloc(T size, handle *h);
    T dealloc(handle *sst_f);
    int init(T start, T end);

};


#endif //CAVITY_MT_CAV_H
