#include "datamanager/datamanager.h"

void DataManager::setThreadErrorCode(int index, int errorCode){
    threadErrorCodes[index] = errorCode;
}

void DataManager::setThreadExecPid(int index, int pid){
    threadExecPids[index] = pid;
}

void DataManager::setThreadMemoryLimit(int index, long newLimit){
    threadMemoryLimits[index] = newLimit;
}

void DataManager::setThreadPointer(int index, pthread_t ptt){
    threadPointers[index] = ptt;
}

void DataManager::setThreadStatus(int index,int newStatus){
    threadStatuses[index] = newStatus;
}

void DataManager::setThreadSubmissionInfo(int index,
     std::string newValue){
    threadSubmissionInfo[index] = newValue;
}

void DataManager::setThreadTestQuantity(int index,int quantity){
    threadTestQuantity[index] = quantity;
}

void DataManager::setMaximumThreadCount(int newValue){
    maximumThreadCount = newValue;
}

void DataManager::setThreadTimeLimit(int index,
    long newLimit){
    threadTimeLimits[index] = newLimit;
}

void DataManager::setThreadTotalMemory(int index, long newValue){
    threadTotalMemory[index] = newValue;
}

void DataManager::setThreadTotalTime(int index, long newValue){
    threadTotalTime[index] = newValue;
}

void DataManager::setAutotestMode(bool newValue){
    autotestMode = newValue;
    terminalLogging = false;
}