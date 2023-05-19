#include "testsystem/testsystem.h"
#include "datamanager/datamanager.h"
#include "filemanager/filemanager.h"

void TestSystem::setupCgroupSolution(int threadIndex, int solvePid){
    std::string cgroupPath = "/sys/fs/cgroup/testsystem";
    cgroupPath += (char)(threadIndex + 48);

    rmdir(cgroupPath.c_str());
    mkdir(cgroupPath.c_str(), 0755);

    std::string tempString = cgroupPath + "/cgroup.procs";
    std::ofstream file(tempString.c_str());
    if(!file.is_open()){
        FileManager::setLogFile("./logThread" 
            + std::to_string(threadIndex) + ".txt",
            "Failed to open thread solution "
            "cgroup.procs file.");
        exit(1);
    }
    file << solvePid;
    file.close();

    if(DataManager::isCpuLimiting()){
        file.open(cgroupPath + "/cpu.cfs_period_us");
        if(!file.is_open()){
            FileManager::setLogFile("./logThread" 
                + std::to_string(threadIndex) + ".txt",
                "Failed to open thread solution "
                "cgroup.cfs_period_us file.");
            exit(1);
        }
        file << 1000000;
        file.close();

        file.open(cgroupPath + "/cpu.cfs_quota_us");
        if(!file.is_open()){
            FileManager::setLogFile("./logThread" 
                + std::to_string(threadIndex) + ".txt",
                "Failed to open thread solution "
                "cgroup.cfs_quota_us file.");
            exit(1);
        }
        file << 10000 * DataManager::getWorkerCpuUsage();
        file.close();
    }

    file.open(cgroupPath + "/memory.max");
    if(!file.is_open()){
        FileManager::setLogFile("./logThread" 
            + std::to_string(threadIndex) + ".txt",
            "Failed to open thread solution "
            "cgroup memory.max file.");
        exit(1);
    }
    file << DataManager::getThreadMemoryLimit(threadIndex);
    file.close();

    tempString = cgroupPath + "/memory.swap.max";
    file.open(tempString.c_str());
    if(!file.is_open()){
        FileManager::setLogFile("./logThread" 
            + std::to_string(threadIndex) + ".txt",
            "Failed to open thread solution "
            "cgroup memory.swap.max file.");
        exit(1);
    }
    file << 0;
    file.close();

    tempString = cgroupPath + "/pids.max";
    file.open(tempString.c_str());
    if(!file.is_open()){
        FileManager::setLogFile("./logThread" 
            + std::to_string(threadIndex) + ".txt",
            "Failed to open thread solution "
            "cgroup pids.max file.");
        exit(1);
    }
    file << 1;
    file.close();
}