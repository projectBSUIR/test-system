#include "limiter/limiter.h"
#include "threaddatamanager/threaddatamanager.h"

bool Limiter::checkMemoryLimitCompilation(int index,double memory){
    if(memory!=0){
        if(memory>ThreadDataManager::COMPILATION_MEMORY_LIMIT){
            return false;
        }
    }
    return true;
}