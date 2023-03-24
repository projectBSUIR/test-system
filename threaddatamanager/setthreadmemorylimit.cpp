#include "threaddatamanager/threaddatamanager.h"

void ThreadDataManager::setThreadMemoryLimit(int index,double newLimit){
    threadMemoryLimits[index]=newLimit;
}