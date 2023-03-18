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
            if(!ThreadDataManager::getThreadStatus(i)){
                continue;
            }
            else if(ThreadDataManager::getThreadStatus(i)==1){
                if(std::chrono::steady_clock::now()
                    -ThreadDataManager::getThreadTime(i)>std::chrono::seconds(3)){
                    std::cout<<"Thread is being terminated!\n";
                    TestSystem::terminateThread(i);
                    continue;
                }
            }
        }
        usleep(20);
    }
}