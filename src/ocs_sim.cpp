//
// Created by victor on 4/10/17.
//

#include "ocs_sim.h"
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ocs_sim::ocs_sim() {
    ocs_blk = new int[200];
}

ocs_sim::~ocs_sim() {
    delete ocs_blk;
}

ocs_sim* ocs_sim::ocs_instance = NULL;

ocs_sim* ocs_sim::Get_ocs() {
    static pthread_mutex_t mu = PTHREAD_MUTEX_INITIALIZER;
    if(ocs_instance = NULL){
        pthread_mutex_lock(&mu);
        if(ocs_instance ==NULL)
            ocs_instance = new ocs_sim();
        pthread_mutex_unlock(&mu);
    }
    return ocs_instance;
}

void ocs_sim::init() {
    int i;
    for(i = 0; i < 200; i++){
        ocs_blk[i] = VALID;
    }
}

int ocs_sim::set_ocs_status(int addr, int length, int status) {
    int i;
    if( status < 0 || status >3){
        std::cout<<"The input statu is a wrong status."<<std::endl;
        return -1;
    }
    for(i = 0; i < length; i++){
        ocs_blk[addr+i] = status;
    }
    return 1;
}

void ocs_sim::show_ocs() {
    std::cout<<"O: The block is in free status."
             <<std::endl
             <<"-: The block is in used status."
             <<std::endl
             <<"X: The block is in invalid status."
             <<std::endl
             <<"*: The block is in bad status."
             <<std::endl;
    for( int i = 0; i < 200; i++ ){
        if(i % 25 == 0 && i != 0)
            std::cout<<std::endl<<std::endl;
        if( ocs_blk[i] == 0 ){
            std::cout<<std::left<<std::setw(4)<<"O";
        }
        else if( ocs_blk[i] == 1 ){
            std::cout<<std::left<<std::setw(4)<<"-";
        }
        else if( ocs_blk[i] == 2 ){
            std::cout<<std::left<<std::setw(4)<<"X";
        }
        else
            std::cout<<std::left<<std::setw(4)<<"*";
    }
}