#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/stat.h>

#include "threaddatamanager/threaddatamanager.h"
#include "testsystem/testsystem.h"
#include "limiter/limiter.h"

//Thread statuses:
//0 - free, 1 - accupied, 2 - compiling solution
//3 - running solution

//Error descriptions:
//1001 - CRE, 1002 - CML, 1003 - CTL
//1004 - RE, 1005 - ML, 1006 - TL

//Checker codes:
//0 - AC, 1 - WA, 2 - PE, 3 - FAIL

int main(int argc,char* argv[])
{
    //input cfg
    if(argc > 1){
        int inputThreadCount = std::stoi(argv[1]);
        if(inputThreadCount >= 1 && inputThreadCount <= 5)
            ThreadDataManager::setMaximumThreadCount(inputThreadCount);
        else{
            std::cout<<"Invalid thread count, remains default (5).\n";
        }
    }

    //create a cgroup to limit cpu usage 
    rmdir("/sys/fs/cgroup/testsystemmain");
    mkdir("/sys/fs/cgroup/testsystemmain", 0755);

    std::ofstream file("/sys/fs/cgroup/testsystemmain/cgroup.procs");
    file << getpid();
    file.close();

    //cpu usage limit (10%)
    file.open("/sys/fs/cgroup/testsystemmain/cpu.cfs_period_us");
    file << 1000000;
    file.close();

    file.open("/sys/fs/cgroup/testsystemmain/cpu.cfs_quota_us");
    file << 100000;
    file.close();

    //create TestSystemData folder and its subfolders
    TestSystem::createBaseFolders();

    //start limiter thread
    Limiter::startLimiterThread();

    //start main thread
    TestSystem::inputLoop();

    return 0;
}
