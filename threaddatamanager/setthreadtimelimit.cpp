#include "threaddatamanager/threaddatamanager.h"

void ThreadDataManager::setThreadTimeLimit(int index,
    long newLimit){
    threadTimeLimits[index] = newLimit;
}