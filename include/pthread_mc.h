//
// Created by victor on 4/10/17.
//

#ifndef CAVITY_MT_PTHREAD_MC_H
#define CAVITY_MT_PTHREAD_MC_H

#include <pthread.h>

class CondVar;

class Mutex{
public:

    void lock();
    void unlock();

    static Mutex *Get_mutex();
    static Mutex *mu_instance;
    pthread_mutex_t mu_;

private:
    Mutex();
    Mutex(Mutex const&);
    Mutex& operator=(Mutex const&);
    ~Mutex();
};

class CondVar{
public:

    void wait();
    void signal();

    static CondVar *Get_cond(Mutex *mu);
    static CondVar *cv_instance;


private:
    CondVar(Mutex *mu);
    CondVar(CondVar const&);
    CondVar& operator=(CondVar const&);
    ~CondVar();
    pthread_cond_t cv_;
    Mutex *mu_;
};

#endif //CAVITY_MT_PTHREAD_MC_H
