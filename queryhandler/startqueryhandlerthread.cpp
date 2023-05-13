#include "queryhandler/queryhandler.h"

void QueryHandler::startQueryHandlerThread(){
    int ret =  pthread_create(&threadPointer, NULL,
         &queryHandlerLoop, NULL);
    if(ret){
        std::cout << "Failed to create a thread!\n";
    }
}
