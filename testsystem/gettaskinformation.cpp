#include "threaddatamanager/threaddatamanager.h"
#include "testsystem.h"

void TestSystem::getTaskInformation(int threadIndex){
    //get packages and info
    //archive it into threaddata(ind)
    //change limits according to the info
    ThreadDataManager::setThreadTestQuantity(threadIndex,60);
    ThreadDataManager::setThreadMemoryLimit(threadIndex,1024*1024*256);
    ThreadDataManager::setThreadTimeLimit(threadIndex,2000);
}