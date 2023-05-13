#include "threaddatamanager/threaddatamanager.h"

int ThreadDataManager::getAvailableThread(){
    for(int i = 0; i < ThreadDataManager::getMaximumThreadCount(); i++){
        if(!threadStatuses[i]){
            return i;
        }
    }
    return -1;
}

int ThreadDataManager::getThreadErrorCode(int index){
    return threadErrorCodes[index];
}

int ThreadDataManager::getThreadExecPid(int index){
    return threadExecPids[index];
}

long ThreadDataManager::getThreadMemoryLimit(int index){
    return threadMemoryLimits[index];
}

pthread_t* ThreadDataManager::getThreadPointer(int index){
    return &threadPointers[index];
}

int ThreadDataManager::getThreadStatus(int index){
    return threadStatuses[index];
}

std::string ThreadDataManager::getThreadSubmissionInfo(int index){
    return threadSubmissionInfo[index];
}

int ThreadDataManager::getThreadTestQuantity(int index){
    return threadTestQuantity[index];
}

int ThreadDataManager::getMaximumThreadCount(){
    return maximumThreadCount;
}

long ThreadDataManager::getThreadTimeLimit(int index){
    return threadTimeLimits[index];
}

long ThreadDataManager::getThreadTotalMemory(int index){
    return threadTotalMemory[index];
}

long ThreadDataManager::getThreadTotalTime(int index){
    return threadTotalTime[index];
}