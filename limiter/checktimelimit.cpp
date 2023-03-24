#include <chrono>
#include <iostream>

#include "limiter/limiter.h"
#include "threaddatamanager/threaddatamanager.h"

bool Limiter::checkTimeLimit(int index){
    if(std::chrono::steady_clock::now()
        -ThreadDataManager::getThreadTime(index)>
        std::chrono::milliseconds(ThreadDataManager::getThreadTimeLimit(index))){
        return false;
    }
    return true;
}