#include "testsystem/testsystem.h"
#include "threaddatamanager/threaddatamanager.h"

void TestSystem::terminateProcess(int index, int errorCode,
    std::string& cgroupPath){
    if(!ThreadDataManager::getThreadErrorCode(index)){
        kill(ThreadDataManager::getThreadExecPid(index), SIGKILL);
    }  
    ThreadDataManager::setThreadErrorCode(index, errorCode);
}