#include "queryhandler/queryhandler.h"
#include "testsystem/testsystem.h"
#include "threaddatamanager/threaddatamanager.h"

void* TestSystem::testRoutine(void* arg){
    //delete arg dynamic memory
    int threadIndex = *(int*)arg;
    int* a = (int*)arg;
    delete a;

    getTaskInformation(threadIndex);

    if(compileChecker(threadIndex) || compileSolution(threadIndex) ||
        testingLoop(threadIndex) || 1){

        prepareReport(threadIndex);
        clearThreadDirectories(threadIndex,
            ThreadDataManager::getThreadTestQuantity(threadIndex));
        ThreadDataManager::setThreadStatus(threadIndex, 0);
        return nullptr;
    }
    return nullptr;
}