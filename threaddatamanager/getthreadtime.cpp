#include <chrono>

#include "threaddatamanager/threaddatamanager.h"

std::chrono::time_point<std::chrono::steady_clock> ThreadDataManager::getThreadTime(int index){
    return threadTimes[index];
}