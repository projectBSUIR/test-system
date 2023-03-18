#include <pthread.h>

#ifndef LIMITER_LIMITER_H
#define LIMITER_LIMITER_H

class limiter{
private:
    static pthread_t thread_pointer;
public:
    static void* limiter_loop(void* arg);
    static bool check_time_limit();
    static bool check_memory_limit();
};

#endif 