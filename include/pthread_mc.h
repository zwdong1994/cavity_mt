//
// Created by victor on 4/10/17.
//

#ifndef CAVITY_MT_PTHREAD_MC_H
#define CAVITY_MT_PTHREAD_MC_H

#include <pthread.h>

class CondVar;

class Mutex{
public:
    Mutex();
    ~Mutex();

    void lock();
    void unlock();


    pthread_mutex_t mu_;
};

class CondVar{
public:
    CondVar(Mutex *mu);
    ~CondVar();
    void wait();
    void signal();

private:
    pthread_cond_t cv_;
    Mutex *mu_;
};

#endif //CAVITY_MT_PTHREAD_MC_H
