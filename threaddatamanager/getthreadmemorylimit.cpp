#include "threaddatamanager/threaddatamanager.h"

long ThreadDataManager::getThreadMemoryLimit(int index){
    return threadMemoryLimits[index];
}