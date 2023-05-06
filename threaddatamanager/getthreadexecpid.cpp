#include "threaddatamanager/threaddatamanager.h"

int ThreadDataManager::getThreadExecPid(int index){
    return threadExecPids[index];
}