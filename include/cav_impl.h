//
// Created by victor on 4/9/17.
//

#ifndef CAVITY_MT_CAV_IMPL_H
#define CAVITY_MT_CAV_IMPL_H

#include <pthread.h>
#include <iostream>
#include "handle.h"
#include "pthread_mc.h"
#include "ocs_sim.h"

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
    int  alloc_impl(T length, handle *h);
    T dealloc_impl(handle *sst_f);
    int init_impl(T start, T end);



private:
    struct alloc_str{
        int size;
        int addr;
        struct alloc_str *next;
    }*alloc;
    int alloc_run(T length, handle *h);
    int ocs_alloc_impl(T length, handle *h);
    int seek_ocs_mt(T length, handle *h, T *left_length);
};

template <typename T>
cav_impl<T>::cav_impl() {

}

template <typename T>
cav_impl<T>::~cav_impl() {

}

template <typename T>
int cav_impl<T>::alloc_impl(T length, handle *h) {
    return alloc_run(length, h);
}

template <typename T>
T cav_impl<T>::dealloc_impl(handle *sst_f) {
    struct alloc_str * p = NULL;
    T length = 0;
    alloc = (alloc_str *) sst_f -> alloc;
    ocs_sim *ocs = ocs_sim::Get_ocs();
//    std::cout<<"111"<<std::endl;
    p = alloc;
    while(p != NULL){
        length += p -> size;
        ocs -> set_ocs_status(p -> addr, p -> size, FREE);
//        std::cout<<"111"<<std::endl;
        ocs -> add_mt(p->addr, p->size);
        p = p->next;
    }
    return length;
}

template <typename T>
int cav_impl<T>::init_impl(T start, T end) {
    ocs_sim *ocs = ocs_sim::Get_ocs();
    ocs ->set_ocs_status(start, end - start, FREE);
    return 1;
}




template <typename T>
int cav_impl<T>::alloc_run(T length, handle *h)  {
    Mutex *mu_ = Mutex::Get_mutex();
    int ret;
    mu_ -> lock();
    ret = ocs_alloc_impl(length, h);
    mu_ -> unlock();
    return ret;
}

template <typename T>
int cav_impl<T>::ocs_alloc_impl(T length, handle *h) {
    int ret;
    T left_length;
    ocs_sim *ocs = ocs_sim::Get_ocs();
    ret = seek_ocs_mt(length, h, &left_length);
    if(ret == NO_MT){
        if(ocs -> alloc_max_length > length){
            ocs -> set_ocs_status(ocs -> alloc_addr, length, VALID);
            h->creat_new_alloc(length, ocs -> alloc_addr);
            ocs -> alloc_addr = (ocs -> alloc_addr + length)%200; //200 means the total chunk number of the disk
            ocs -> alloc_max_length -= length;
            return SUCCESS;
        }
        else
            return FAIL;
    }
    if(ret == COMPLETLY_ALLOC)
        return SUCCESS;
    if(ret == ALLOC_NOT_COMPLETE){
        if(ocs -> alloc_max_length > left_length){
            ocs -> set_ocs_status(ocs -> alloc_addr, left_length, VALID);
            h->creat_new_alloc(left_length, ocs -> alloc_addr);
            ocs ->alloc_addr = (ocs -> alloc_addr + left_length)%200; //200 means the total chunk number of the disk
            ocs -> alloc_max_length -= left_length;
            return SUCCESS;
        }
        else
            return FAIL;
    }
}

template <typename T>
int cav_impl<T>::seek_ocs_mt(T length, handle *h, T *left_length) {
    ocs_sim *ocs = ocs_sim::Get_ocs();
    T mt_alloc_len = length;
    std::cout<<"mt_num is: "<<ocs -> mt_num<<std::endl;
    if(ocs -> mt_num <= 0){ //if there is no mapping table, return
        return NO_MT;
    }
    else{
        for(int i = 0; i < ocs->mt_num && mt_alloc_len > 0; i++){
            if (((ocs->mt) + i)->statu == FREE) {
                if (mt_alloc_len < ((ocs->mt) + i)->length) { //the request length < mapping table's line
                    h->creat_new_alloc(mt_alloc_len, ((ocs->mt) + i)->first_addr);
                    ocs->set_ocs_status(((ocs->mt) + i)->first_addr, mt_alloc_len, VALID);
                    ((ocs->mt) + i)->first_addr += mt_alloc_len;
                    ((ocs->mt) + i)->length -= mt_alloc_len;
                    return COMPLETLY_ALLOC;
                } else {
                    h->creat_new_alloc(((ocs->mt) + i)->length, ((ocs->mt) + i)->first_addr);
                    ocs->set_ocs_status(((ocs->mt) + i)->first_addr, ((ocs->mt) + i)->length, VALID);
                    mt_alloc_len -= ((ocs->mt) + i)->length;
                    ocs->delete_mt(((ocs->mt) + i)->first_addr);
                }
            }
        }
        if(mt_alloc_len > 0){
            *left_length = mt_alloc_len;
            return ALLOC_NOT_COMPLETE;
        }
        else
            return COMPLETLY_ALLOC;
    }
}
#endif //CAVITY_MT_CAV_IMPL_H
