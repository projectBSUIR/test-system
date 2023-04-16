#include <pthread.h>

#ifndef LIMITER_LIMITER_H
#define LIMITER_LIMITER_H

class Limiter{
private:
    static pthread_t threadPointer;
public:
    static void* limiterLoop(void* argument);
    static void startLimiterThread();
    static bool checkTimeLimit(int index);
    static bool checkMemoryLimit(int index, double memory);
    static bool checkTimeLimitCompilation(int index);
    static bool checkMemoryLimitCompilation(int index, double memory);
    static bool checkThreadLimit(int threadCount);
};

#endif 