#include <pthread.h>

#ifndef LIMITER_LIMITER_H
#define LIMITER_LIMITER_H

class Limiter{
private:
    static pthread_t threadPointer;
public:
    static void* limiterLoop(void* argument);
    static void startLimiterThread();
    static bool checkTimeLimit();
    static bool checkMemoryLimit();
};

#endif 