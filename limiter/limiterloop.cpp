#include "threaddatamanager/threaddatamanager.h"
#include "limiter/limiter.h"
#include "testsystem/testsystem.h"

void* Limiter::limiterLoop(void * argument){
    int i = 0;
    std::string cgroupPathSolution = "/sys/fs/cgroup/testsystem";
    std::string cgroupPathCompilation = "/sys/fs/cgroup/testsystemcomp";
    std::string tempString;
    while (true){
        for(i = 0;i < ThreadDataManager::getMaximumThreadCount(); i++){
            if(!ThreadDataManager::getThreadStatus(i) ||
                ThreadDataManager::getThreadExecPid(i) == -1){
                continue;
            }
            else if(ThreadDataManager::getThreadStatus(i) == 2)
            {   
                if(!checkTimeLimitCompilation(i)){
                    tempString = cgroupPathCompilation + (char)(i + 48);
                    tempString += "/cgroup.procs";
                    TestSystem::terminateProcess(i, 1003, tempString);
                    continue;
                }

                if(!checkMemoryLimitCompilation(i)){
                    tempString = cgroupPathCompilation + (char)(i + 48);
                    tempString += "/cgroup.procs";
                    TestSystem::terminateProcess(i, 1002, tempString);
                    continue;
                }
            }
            else if(ThreadDataManager::getThreadStatus(i) == 3){
                
                if(!checkTimeLimit(i)){
                    tempString = cgroupPathSolution + (char)(i + 48);
                    tempString += "/cgroup.procs";
                    TestSystem::terminateProcess(i, 1006, tempString);
                    continue;
                }
                if(!checkMemoryLimit(i)){
                    tempString = cgroupPathSolution + (char)(i + 48);
                    tempString += "/cgroup.procs";
                    TestSystem::terminateProcess(i, 1005, tempString);
                    continue;
                }
            }
        }
        usleep(20);
    }
}