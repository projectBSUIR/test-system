#include <chrono>

#include "threaddatamanager/threaddatamanager.h"

void ThreadDataManager::setThreadTimeLimit(int index,
    int newLimit){
    threadTimeLimits[index]=newLimit;
}