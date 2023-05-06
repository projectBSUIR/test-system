#include "limiter/limiter.h"

void Limiter::startLimiterThread(){
    int ret =  pthread_create(&threadPointer, NULL, &limiterLoop, NULL);
    if(ret){
        std::cout << "Failed to create a thread!\n";
    }
};