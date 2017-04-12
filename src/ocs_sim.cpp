//
// Created by victor on 4/10/17.
//

#include "ocs_sim.h"
#include <iostream>
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

void ocs_sim::set_ocs_status(int addr, int length, int status) {
    int i;
    for(i = 0; i < length; i++){
        ocs_blk[addr+i] = status;
    }
}

void ocs_sim::show_ocs() {

}