#include "limiter/limiter.h"
#include "filemanager/filemanager.h"

void Limiter::startLimiterThread(){
    int ret =  pthread_create(&threadPointer, NULL, &limiterLoop, NULL);
    if(ret){
        FileManager::setLogFile("./logLimiter.txt",
            "Failed to create limiter thread.");
        exit(1);
    }
};