#ifndef LIMITER_LIMITER_H
#define LIMITER_LIMITER_H

#include <pthread.h>
#include <unistd.h>
#include <fstream>
#include <iostream>

class Limiter{
private:
    static pthread_t threadPointer;
public:
    static void* limiterLoop(void* argument);
    static void startLimiterThread();
    static bool checkTimeLimit(int index);
    static bool checkMemoryLimit(int index);
    static bool checkTimeLimitCompilation(int index);
    static bool checkMemoryLimitCompilation(int index);
};

#endif 