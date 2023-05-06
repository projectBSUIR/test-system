#include "threaddatamanager/threaddatamanager.h"

void ThreadDataManager::setThreadStatus(int index,int newStatus){
    threadStatuses[index] = newStatus;
}