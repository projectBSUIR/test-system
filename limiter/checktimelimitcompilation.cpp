#include <chrono>
#include <iostream>

#include "limiter/limiter.h"
#include "threaddatamanager/threaddatamanager.h"

bool Limiter::checkTimeLimitCompilation(int index){
    if(std::chrono::steady_clock::now()
        -ThreadDataManager::getThreadTime(index)>
        std::chrono::milliseconds(ThreadDataManager::COMPILATION_TIME_LIMIT)){
        return false;
    }
    return true;
}