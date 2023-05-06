#include "testsystem/testsystem.h"
#include "threaddatamanager/threaddatamanager.h"

void TestSystem::startTestRoutine(int index){
    ThreadDataManager::setThreadStatus(index, 1);
    ThreadDataManager::setThreadErrorCode(index, 0);
    int* a = new int;
    *a = index;
    int ret =  pthread_create(ThreadDataManager::getThreadPointer(index),
         NULL, &testRoutine, a);
}