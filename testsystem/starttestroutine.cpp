#include "testsystem/testsystem.h"
#include "datamanager/datamanager.h"
#include "filemanager/filemanager.h"

void TestSystem::startTestRoutine(int index){
    DataManager::setThreadStatus(index, 1);
    DataManager::setThreadErrorCode(index, 0);
    int* a = new int;
    *a = index;
    int ret =  pthread_create(DataManager::getThreadPointer(index),
         NULL, &testRoutine, a);
    if(ret){
        FileManager::setLogFile("./logThread" + std::to_string(index) + ".txt",
            "Failed to create thread.");
        exit(1);
    }
}