#include <string>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <boost/process.hpp>

#include "testsystem/testsystem.h"
#include "threaddatamanager/threaddatamanager.h"

void TestSystem::terminateThread(int index)
{
    pthread_cancel(*ThreadDataManager::getThreadPointer(index));
    ThreadDataManager::setThreadStatus(index,0);
    ThreadDataManager::getThreadChildPointer(index)->terminate();
    ThreadDataManager::setThreadChildPointer(index,nullptr);
}