#include "limiter/limiter.h"
#include "filemanager/filemanager.h"
#include "datamanager/datamanager.h"

bool Limiter::checkMemoryLimit(int index){
    std::string path = "/sys/fs/cgroup/testsystem";
    path += (char)(index + 48);
    path += "/memory.peak";

    long memory;

    std::ifstream file(path.c_str());
    if(!file.is_open()){
        FileManager::setLogFile("./logLimiter.txt",
            "Failed to open thread solution "
            "cgroup memory.peak file.");
        exit(1);
    }
    file >> memory;
    file.close();

    if(!DataManager::getThreadErrorCode(index))
        DataManager::setThreadTotalMemory(index, memory);

    return memory < DataManager::getThreadMemoryLimit(index);
}