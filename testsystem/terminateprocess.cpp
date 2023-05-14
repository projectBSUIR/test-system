#include "testsystem/testsystem.h"
#include "datamanager/datamanager.h"

void TestSystem::terminateProcess(int index, int errorCode,
    std::string& cgroupPath){
    if(!DataManager::getThreadErrorCode(index)){
        kill(DataManager::getThreadExecPid(index), SIGKILL);
    }  
    DataManager::setThreadErrorCode(index, errorCode);
}