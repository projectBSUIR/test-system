#include "queryhandler/queryhandler.h"
#include "filemanager/filemanager.h"

void QueryHandler::startQueryHandlerThread(){
    int ret =  pthread_create(&threadPointer, NULL,
         &queryHandlerLoop, NULL);
    if(ret){
        FileManager::setLogFile("./logQueryHandler.txt",
            "Failed to create query thread.");
        exit(1);
    }
}
