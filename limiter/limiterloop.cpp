#include <unistd.h>
#include <chrono>
#include <iostream>

#include "threaddatamanager/threaddatamanager.h"
#include "limiter/limiter.h"
#include "testsystem/testsystem.h"
#include "thirdparty/getprocthreadnumandmemusage.h"

//old
void* Limiter::limiterLoop(void * argument){
    int i=0;
    double virtualMemory=0;
    double residentSet=0;
    int threadCount=0;
    while (true){
        for(i=0;i<6;i++){
            if(!ThreadDataManager::getThreadStatus(i)||
                ThreadDataManager::getThreadChildPointer(i)==nullptr){
                continue;
            }
            else if(ThreadDataManager::getThreadStatus(i)==2)
            {
                if(!checkTimeLimitCompilation(i)){
                    TestSystem::terminateProcess(i,3);
                    continue;
                }

                getProcThreadNumAndMemUsage(threadCount,virtualMemory,
                    residentSet,ThreadDataManager::getThreadChildPointer(i)->id());

                if(!checkMemoryLimitCompilation(i,virtualMemory)){
                    TestSystem::terminateProcess(i,4);
                    continue;
                }
            }
            else if(ThreadDataManager::getThreadStatus(i)==3){
                if(!checkTimeLimit(i)){
                    TestSystem::terminateProcess(i,1);
                    continue;
                }

                getProcThreadNumAndMemUsage(threadCount,virtualMemory,
                    residentSet,ThreadDataManager::getThreadChildPointer(i)->id());

                if(!checkMemoryLimit(i,virtualMemory)){
                    TestSystem::terminateProcess(i,2);
                    continue;
                }

                if(!checkThreadLimit(threadCount)){
                    TestSystem::terminateProcess(i,5);
                    continue;
                }
            }
        }
        usleep(20);
    }
}