#include <chrono>

#include "threaddatamanager/threaddatamanager.h"

void ThreadDataManager::setThreadTime(int index, std::chrono::time_point<std::chrono::steady_clock> newTime){
    threadTimes[index]=newTime;
}