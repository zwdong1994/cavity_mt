//
// Created by victor on 4/10/17.
//

#ifndef CAVITY_MT_OCS_SIM_H
#define CAVITY_MT_OCS_SIM_H

#define VALID 0
#define IN_USE 1
#define INVALID 2
#define BAD 3

class ocs_sim {
public:

    void init(); //create a simulated ocs
    void set_ocs_status(int addr, int length, int status);
    void show_ocs();

    static ocs_sim *Get_ocs();
    static ocs_sim *ocs_instance;


private:
    ocs_sim();
    ocs_sim(ocs_sim const&);
    ocs_sim& operator=(ocs_sim const&);
    ~ocs_sim();

    int *ocs_blk;
    int length;
};


#endif //CAVITY_MT_OCS_SIM_H
