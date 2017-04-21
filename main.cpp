//
// Created by victor on 4/20/17.
//

#include <iostream>
#include <unistd.h>
#include "cav.h"
#include "ocs_sim.h"


int main(){
    ocs_sim *ocs = ocs_sim::Get_ocs();
    ocs -> show_ocs();

    handle h;
    handle h1;
    cav<int> c1;
    std::cout<<"alloc 10"<<std::endl;
    int alloc_l = 10;
    int alloc_l2 = 5;
    c1.alloc(alloc_l, &h);
    ocs -> show_ocs();
    sleep(1);
    std::cout<<"alloc 5"<<std::endl;
    c1.alloc(alloc_l2, &h1);
    ocs -> show_ocs();
    sleep(1);
    std::cout<<"dealloc the previous 10"<<std::endl;
    c1.dealloc(&h);
    ocs -> show_ocs();
    std::cout<<"alloc 5"<<std::endl;
    c1.alloc(alloc_l2,&h);
    ocs -> show_ocs();
    return 1;
}