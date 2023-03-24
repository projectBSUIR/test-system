#include <unistd.h>
#include <chrono>
#include <iostream>

#include "threaddatamanager/threaddatamanager.h"
#include "limiter/limiter.h"
#include "testsystem/testsystem.h"

//old
void* Limiter::limiterLoop(void * argument){
    int i=0;
    while (true){
        for(i=0;i<6;i++){
            if(!ThreadDataManager::getThreadStatus(i)||
                ThreadDataManager::getThreadChildPointer(i)==nullptr){
                continue;
            }
            else if(ThreadDataManager::getThreadStatus(i)==1)
            {
                if(!checkTimeLimitCompilation(i)){
                    TestSystem::terminateProcess(i,3);
                    continue;
                }
                if(!checkMemoryLimitCompilation(i)){
                    TestSystem::terminateProcess(i,4);
                    continue;
                }
            }
            else if(ThreadDataManager::getThreadStatus(i)==2){
                if(!checkTimeLimit(i)){
                    TestSystem::terminateProcess(i,1);
                    continue;
                }
                if(!checkMemoryLimit(i)){
                    TestSystem::terminateProcess(i,2);
                    continue;
                }
            }
        }
        usleep(20);
    }
}