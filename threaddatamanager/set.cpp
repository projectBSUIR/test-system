#include "threaddatamanager/threaddatamanager.h"

void ThreadDataManager::setThreadErrorCode(int index, int errorCode){
    threadErrorCodes[index] = errorCode;
}

void ThreadDataManager::setThreadExecPid(int index, int pid){
    threadExecPids[index] = pid;
}

void ThreadDataManager::setThreadMemoryLimit(int index, long newLimit){
    threadMemoryLimits[index] = newLimit;
}

void ThreadDataManager::setThreadPointer(int index, pthread_t ptt){
    threadPointers[index] = ptt;
}

void ThreadDataManager::setThreadStatus(int index,int newStatus){
    threadStatuses[index] = newStatus;
}

void ThreadDataManager::setThreadSubmissionInfo(int index,
     std::string newValue){
    threadSubmissionInfo[index] = newValue;
}

void ThreadDataManager::setThreadTestQuantity(int index,int quantity){
    threadTestQuantity[index] = quantity;
}

void ThreadDataManager::setMaximumThreadCount(int newValue){
    maximumThreadCount = newValue;
}

void ThreadDataManager::setThreadTimeLimit(int index,
    long newLimit){
    threadTimeLimits[index] = newLimit;
}

void ThreadDataManager::setThreadTotalMemory(int index, long newValue){
    threadTotalMemory[index] = newValue;
}

void ThreadDataManager::setThreadTotalTime(int index, long newValue){
    threadTotalTime[index] = newValue;
}