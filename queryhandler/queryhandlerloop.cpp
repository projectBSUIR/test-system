#include "queryhandler/queryhandler.h"
#include "testsystem/testsystem.h"
#include "datamanager/datamanager.h"

void* QueryHandler::queryHandlerLoop(void* arg){
    while(true){
        int threadIndex = DataManager::getAvailableThread();
        if(threadIndex != -1){
            tryPopSubmission(threadIndex);
        }
        usleep(3000000);
    }
    return nullptr;
}