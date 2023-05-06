#include "testsystem/testsystem.h"
#include "threaddatamanager/threaddatamanager.h"

void TestSystem::setupCgroup(int threadIndex, int solvePid){
    std::string cgroupPath = "/sys/fs/cgroup/testsystem";
    cgroupPath += (char)(threadIndex + 48);

    rmdir(cgroupPath.c_str());
    mkdir(cgroupPath.c_str(), 0755);

    std::string tempString = cgroupPath + "/cgroup.procs";
    std::ofstream file(tempString.c_str());
    file << solvePid;
    file.close();

    //cpu usage limit (10%)
    file.open(cgroupPath + "/cpu.cfs_period_us");
    file << 1000000;
    file.close();

    file.open(cgroupPath + "/cpu.cfs_quota_us");
    file << 100000;
    file.close();

    //memory limit
    file.open(cgroupPath + "/memory.max");
    file << ThreadDataManager::getThreadMemoryLimit(threadIndex);
    file.close();

    tempString = cgroupPath + "/memory.swap.max";
    file.open(tempString.c_str());
    file << 0;
    file.close();

    //child processes limit
    tempString = cgroupPath + "/pids.max";
    file.open(tempString.c_str());
    file << 1;
    file.close();

    //limit threads
    tempString = cgroupPath + "/cpu.threads.max";
    file.open(tempString.c_str());
    file << 1;
    file.close();
}