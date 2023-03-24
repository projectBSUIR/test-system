#include "threaddatamanager/threaddatamanager.h"

double ThreadDataManager::getThreadMemoryLimit(int index){
    return threadMemoryLimits[index];
}