//
// Created by victor on 4/10/17.
//

#ifndef CAVITY_MT_OCS_SIM_H
#define CAVITY_MT_OCS_SIM_H

#define VALID 0
#define INVALID 1
#define BAD 3

class ocs_sim {
public:
    ocs_sim();
    ~ocs_sim();
    void init(); //create a simulated ocs
    void set_ocs_status(int addr, int length);

private:
    int *ocs_blk;
    int length;
};


#endif //CAVITY_MT_OCS_SIM_H
