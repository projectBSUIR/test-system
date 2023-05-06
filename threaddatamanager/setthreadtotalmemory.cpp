#include "threaddatamanager/threaddatamanager.h"

void ThreadDataManager::setThreadTotalMemory(int index, long newValue){
    threadTotalMemory[index] = newValue;
}