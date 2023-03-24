#include "threaddatamanager/threaddatamanager.h"

void ThreadDataManager::setThreadErrorCode(int index,int errorCode){
    threadErrorCodes[index]=errorCode;
}