#include "threaddatamanager/threaddatamanager.h"

void ThreadDataManager::setThreadPointer(int index, pthread_t ptt){
    threadPointers[index] = ptt;
}