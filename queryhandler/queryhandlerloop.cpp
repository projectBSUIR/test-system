#include "queryhandler/queryhandler.h"
#include "testsystem/testsystem.h"
#include "threaddatamanager/threaddatamanager.h"

void* QueryHandler::queryHandlerLoop(void* arg){
    while(true){
        int threadIndex = ThreadDataManager::getAvailableThread();
        if(threadIndex != -1){
            tryPopSubmission(threadIndex);
        }
        usleep(3000000);
    }
    return nullptr;
}