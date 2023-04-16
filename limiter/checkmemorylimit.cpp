#include "limiter/limiter.h"
#include "threaddatamanager/threaddatamanager.h"

bool Limiter::checkMemoryLimit(int index, double memory){
    if(memory!=0){
        if(memory>ThreadDataManager::getThreadMemoryLimit(index)){
            return false;
        }
    }
    return true;
}