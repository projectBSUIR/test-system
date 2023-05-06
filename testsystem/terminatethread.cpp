#include "testsystem/testsystem.h"
#include "threaddatamanager/threaddatamanager.h"

void TestSystem::terminateThread(int index){
    pthread_cancel(*ThreadDataManager::getThreadPointer(index));
    ThreadDataManager::setThreadStatus(index, 0);
}