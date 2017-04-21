//
// Created by victor on 4/9/17.
//

#include "cav_impl.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "pthread_mc.h"
#include "ocs_sim.h"
#include "handle.h"

template <typename T>
cav_impl<T>::cav_impl() {

}

template <typename T>
cav_impl<T>::~cav_impl() {

}

template <typename T>
pthread_t  cav_impl<T>::alloc_impl(T length, handle *h) {
    par *mid_par;
    mid_par->h = h;
    mid_par->length = length;
    mid_par->this_ = this;
    if(pthread_create(&pid, NULL, start_pthread, (void *) mid_par)){
        return -1;
    }
    else
        return pid;
}

template <typename T>
T cav_impl<T>::dealloc_impl(handle *sst_f) {
    struct alloc_str * p = NULL;
    T length = 0;
    alloc = (alloc_str *) sst_f -> alloc;
    ocs_sim *ocs = ocs_sim::Get_ocs();
    p = alloc;
    while(p != NULL){
        length += p -> size;
        ocs -> add_mt(p->addr, p->size);
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
void* cav_impl<T>::start_pthread(void *arg) {
    par *mid = (par *)arg;
    mid->this_->alloc_run(mid->length, mid->h);
}

template <typename T>
int cav_impl<T>::alloc_run(T length, handle *h) {
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
            ocs ->alloc_addr = (ocs -> alloc_addr + length)%200; //200 means the total chunk number of the disk
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