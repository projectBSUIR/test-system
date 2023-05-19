#include "testsystem/testsystem.h"
#include "datamanager/datamanager.h"
#include "filemanager/filemanager.h"

void* TestSystem::testRoutine(void* arg){
    int threadIndex = *(int*)arg;
    int* a = (int*)arg;
    delete a;

    if(!DataManager::isAutotestMode()){
        FileManager::getTestFilesAndProperties(threadIndex);
    }

    if(compileChecker(threadIndex) || compileSolution(threadIndex) ||
        testingLoop(threadIndex) || 1){

        prepareReport(threadIndex);
        FileManager::clearThreadDirectories(threadIndex,
            DataManager::getThreadTestQuantity(threadIndex));
        DataManager::setThreadStatus(threadIndex, 0);
        return nullptr;
    }
    return nullptr;
}