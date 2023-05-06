#include "threaddatamanager/threaddatamanager.h"

void ThreadDataManager::setThreadExecPid(int index, int pid){
    threadExecPids[index] = pid;
}