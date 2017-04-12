//
// Created by victor on 4/10/17.
//


#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pthread_mc.h"

static void PthreadCall(const char *label, int result) {
    if (result != 0) {
        printf("pthread %s: %s\n", label, strerror(result));
        abort();
    }
}

Mutex::Mutex() {
    PthreadCall("init mutex", pthread_mutex_init(&mu_, NULL));
}

Mutex::~Mutex() {
    PthreadCall("destroy mutex", pthread_mutex_destroy(&mu_));
}

Mutex* Mutex::mu_instance = NULL;



Mutex* Mutex::Get_mutex() {
    static pthread_mutex_t pm = PTHREAD_MUTEX_INITIALIZER;
    if(mu_instance == NULL){
        pthread_mutex_lock(&pm);
        if(mu_instance == NULL){
            mu_instance = new Mutex();
        }
        pthread_mutex_unlock(&pm);
    }
    return mu_instance;
}

void Mutex::lock() {
    PthreadCall("lock", pthread_mutex_lock(&mu_));
}

void Mutex::unlock() {
    PthreadCall("unlock", pthread_mutex_unlock(&mu_));
}

CondVar::CondVar(Mutex *mu)
    : mu_(mu){
    PthreadCall("init cv", pthread_cond_init(&cv_, NULL));
}

CondVar::~CondVar() {
    PthreadCall("destroy cv", pthread_cond_destroy(&cv_));
}

CondVar* CondVar::cv_instance = NULL;

CondVar* CondVar::Get_cond(Mutex *mu) {
    static pthread_mutex_t pm_cv = PTHREAD_MUTEX_INITIALIZER;
    if(cv_instance == NULL){
        pthread_mutex_lock(&pm_cv);
        if(cv_instance == NULL){
            cv_instance = new CondVar(mu);
        }
        pthread_mutex_unlock(&pm_cv);
    }
    return cv_instance;
}

void CondVar::signal() {
    PthreadCall("signal", pthread_cond_signal(&cv_));
}

void CondVar::wait() {
    PthreadCall("wait", pthread_cond_wait(&cv_, &mu_->mu_));
}