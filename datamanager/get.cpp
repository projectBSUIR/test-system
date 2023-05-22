#include "datamanager/datamanager.h"

int DataManager::getAvailableThread(){
    for(int i = 0; i < DataManager::getMaximumThreadCount(); i++){
        if(!threadStatuses[i]){
            return i;
        }
    }
    return -1;
}

int DataManager::getThreadErrorCode(int index){
    return threadErrorCodes[index];
}

int DataManager::getThreadExecPid(int index){
    return threadExecPids[index];
}

long DataManager::getThreadMemoryLimit(int index){
    return threadMemoryLimits[index];
}

pthread_t* DataManager::getThreadPointer(int index){
    return &threadPointers[index];
}

int DataManager::getThreadStatus(int index){
    return threadStatuses[index];
}

std::string DataManager::getThreadSubmissionInfo(int index){
    return threadSubmissionInfo[index];
}

int DataManager::getThreadTestQuantity(int index){
    return threadTestQuantity[index];
}

int DataManager::getMaximumThreadCount(){
    return maximumThreadCount;
}

long DataManager::getThreadTimeLimit(int index){
    return threadTimeLimits[index];
}

long DataManager::getThreadTotalMemory(int index){
    return threadTotalMemory[index];
}

long DataManager::getThreadTotalTime(int index){
    return threadTotalTime[index];
}

long long DataManager::getCompilationMemoryLimit(){
    return compilationMemoryLimit;
}

long long DataManager::getCompilationTimeLimit(){
    return compilationTimeLimit;
}

int DataManager::getTestsystemCpuUsage(){
    return testsystemCpuUsage;
}

int DataManager::getWorkerCpuUsage(){
    return workerCpuUsage;
}

bool DataManager::isTerminalLogging(){
    return terminalLogging;
}

bool DataManager::isCpuLimiting(){
    return cpuLimiting;
}

bool DataManager::isAutotestMode(){
    return autotestMode;
}

std::string DataManager::getTestsystemLogin(){
    return testsystemLogin;
}

std::string DataManager::getTestsystemPassword(){
    return testsystemPassword;
}

std::string DataManager::getServerUrl(){
    return serverUrl;
}

std::string DataManager::getExtractSubmissionRout(){
    return extractSubmissionRout;
}

std::string DataManager::getSetVerdictRout(){
    return setVerdictRout;
}

std::string DataManager::getExtractTestingFilesRout(){
    return extractTestingFilesRout;
}

std::string DataManager::getExtractProblemTestsRout(){
    return extractProblemTestsRout;
}

time_t DataManager::getThreadStartRealTime(int index){
    return threadStartRealTime[index];
}