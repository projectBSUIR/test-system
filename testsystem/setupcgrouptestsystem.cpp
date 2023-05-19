#include "testsystem/testsystem.h"
#include "filemanager/filemanager.h"

void TestSystem::setupCgroupTestsystem(int cpuProc){
    rmdir("/sys/fs/cgroup/testsystemmain");
    mkdir("/sys/fs/cgroup/testsystemmain", 0755);

    std::ofstream file("/sys/fs/cgroup/testsystemmain/cgroup.procs");
    if(!file.is_open()){
        FileManager::setLogFile("./logThread0.txt",
            "Failed to open testsystem "
            "cgroup.procs file.");
        exit(1);
    }
    file << getpid();
    file.close();

    file.open("/sys/fs/cgroup/testsystemmain/cpu.cfs_period_us");
    if(!file.is_open()){
        FileManager::setLogFile("./logThread0.txt",
            "Failed to open testsystem "
            "cpu.cfs_period_us file.");
        exit(1);
    }
    file << 1000000;
    file.close();

    file.open("/sys/fs/cgroup/testsystemmain/cpu.cfs_quota_us");
    if(!file.is_open()){
        FileManager::setLogFile("./logThread0.txt",
            "Failed to open testsystem "
            "cpu.cfs_quota_us file.");
        exit(1);
    }
    file << 10000*cpuProc;
    file.close();
}