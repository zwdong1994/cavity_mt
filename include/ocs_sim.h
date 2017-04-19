//
// Created by victor on 4/10/17.
//

#ifndef CAVITY_MT_OCS_SIM_H
#define CAVITY_MT_OCS_SIM_H

#define FREE 0
#define VALID 1
#define INVALID 2
#define BAD 3

class ocs_sim {
public:

    void init(); //create a simulated ocs
    int set_ocs_status(int addr, int length, int status);
    void show_ocs();

    static ocs_sim *Get_ocs();
    static ocs_sim *ocs_instance;
    int alloc_addr;
    int mt_num;
    int alloc_max_length;
    struct cav_frag_mt{
        int first_addr;
        int length;
        int statu;
    }mt[200];
    int delete_mt(int first_ad);
    int add_mt(int first_ad, int size);

private:
    ocs_sim();
    ocs_sim(ocs_sim const&);
    ocs_sim& operator=(ocs_sim const&);
    ~ocs_sim();

    int *ocs_blk;
};


#endif //CAVITY_MT_OCS_SIM_H
