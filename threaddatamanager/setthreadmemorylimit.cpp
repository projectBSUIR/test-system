#include "threaddatamanager/threaddatamanager.h"

void ThreadDataManager::setThreadMemoryLimit(int index, long newLimit){
    threadMemoryLimits[index] = newLimit;
}