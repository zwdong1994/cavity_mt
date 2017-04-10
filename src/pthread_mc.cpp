//
// Created by victor on 4/10/17.
//


#include <pthread.h>
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

void CondVar::signal() {
    PthreadCall("signal", pthread_cond_signal(&cv_));
}

void CondVar::wait() {
    PthreadCall("wait", pthread_cond_wait(&cv_, &mu_->mu_));
}