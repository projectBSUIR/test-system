#include "testsystem/testsystem.h"
#include "datamanager/datamanager.h"

void TestSystem::terminateThread(int index){
    pthread_cancel(*DataManager::getThreadPointer(index));
    DataManager::setThreadStatus(index, 0);
}