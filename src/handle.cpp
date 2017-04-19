//
// Created by victor on 4/17/17.
//
#include "handle.h"
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

handle::handle() {
    alloc = NULL;
}

handle::~handle() {

}

handle* handle::handle_instance = NULL;

handle* handle::Get_handle() {
    static pthread_mutex_t mu = PTHREAD_MUTEX_INITIALIZER;
    if(NULL == handle_instance){
        pthread_mutex_lock(&mu);
        if(handle_instance ==NULL)
            handle_instance = new handle();
        pthread_mutex_unlock(&mu);
    }
    return handle_instance;
}
template <typename T>
int handle<T>::creat_new_alloc(T size, T addr) {
    struct alloc_str *p = new alloc_str;
    struct alloc_str *hp = NULL;
    p -> addr = addr;
    p -> size = size;
    hp = alloc;
    alloc = p;
    alloc -> next = hp;
    return 1;
}

struct alloc_str* handle::get_alloc() {
    return alloc;
}

void handle::show() {
    struct alloc_str *p = alloc;
    int i = 0;
    std::cout<<"Print the exist handle struct"<<std::endl;
    while(p!=NULL){
        std::cout<<std::left<<std::setw(30)<<"Sequential area "<<i++<<": ";
        std::cout<<std::left<<std::setw(20)<<"Address:"<<p->addr
                 <<std::left<<std::setw(20)<<"Length :"<<p->size
                 <<std::endl;
        p = p->next;
    }
}