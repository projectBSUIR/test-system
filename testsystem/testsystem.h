#include <pthread.h>
#include <chrono>

#ifndef TESTSYSTEM_TESTSYSTEM_H
#define TESTSYSTEM_TESTSYSTEM_H

class TestSystem{
public:
    static void inputLoop();
    static void* limiterLoop(void* argument);
    static void terminateThread(int ind);
    static void terminateProcess(int ind,int errorCode);
};

#endif