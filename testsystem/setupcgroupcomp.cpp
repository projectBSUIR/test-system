#include "testsystem/testsystem.h"
#include "threaddatamanager/threaddatamanager.h"

void TestSystem::setupCgroupComp(int threadIndex, int solvePid){
    std::string cgroupPath = "/sys/fs/cgroup/testsystemcomp";
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

    //memory limits
    file.open(cgroupPath + "/memory.max");
    file << ThreadDataManager::COMPILATION_MEMORY_LIMIT;
    file.close();

    tempString = cgroupPath + "/memory.swap.max";
    file.open(tempString.c_str());
    file << 0;
    file.close();
}