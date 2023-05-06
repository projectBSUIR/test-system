#include "threaddatamanager/threaddatamanager.h"

pthread_t* ThreadDataManager::getThreadPointer(int index){
    return &threadPointers[index];
}