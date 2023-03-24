#include <string>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <boost/process.hpp>

#include "testsystem/testsystem.h"
#include "threaddatamanager/threaddatamanager.h"

void TestSystem::terminateProcess(int index,int errorCode)
{
    ThreadDataManager::getThreadChildPointer(index)->terminate();
    ThreadDataManager::setThreadErrorCode(index,errorCode);
}