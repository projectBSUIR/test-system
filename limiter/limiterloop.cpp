#include "datamanager/datamanager.h"
#include "limiter/limiter.h"
#include "testsystem/testsystem.h"

void* Limiter::limiterLoop(void * argument){
    int i = 0;
    std::string cgroupPathSolution = "/sys/fs/cgroup/testsystem";
    std::string cgroupPathCompilation = "/sys/fs/cgroup/testsystemcomp";
    std::string tempString;
    while (true){
        for(i = 0;i < DataManager::getMaximumThreadCount(); i++){
            if(!DataManager::getThreadStatus(i) ||
                DataManager::getThreadExecPid(i) == -1){
                continue;
            }
            else if(DataManager::getThreadStatus(i) == 2)
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
            else if(DataManager::getThreadStatus(i) == 3){
                
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
        usleep(200);
    }
}