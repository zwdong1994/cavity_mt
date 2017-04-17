//
// Created by victor on 4/10/17.
//

#ifndef CAVITY_MT_CAV_H
#define CAVITY_MT_CAV_H

#include <iostream>
#include "handle.h"

class cav {
public:
    cav(){}
    ~cav(){}

    template <typename T>
            pthread_t alloc(T size, handle *h);
    template <typename T>
            T dealloc(handle *sst_f);
    template <typename T>
            int init(T start, T end);

};


#endif //CAVITY_MT_CAV_H
