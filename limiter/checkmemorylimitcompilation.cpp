#include "limiter/limiter.h"
#include "threaddatamanager/threaddatamanager.h"

bool Limiter::checkMemoryLimitCompilation(int index){
    std::string path = "/sys/fs/cgroup/testsystemcomp";
    path += (char)(index + 48);
    path += "/memory.max_usage_in_bytes";

    long memory;

    std::ifstream file(path.c_str());
    file >> memory;
    file.close();

    if(!ThreadDataManager::getThreadErrorCode(index))
        ThreadDataManager::setThreadTotalMemory(index, memory);
    
    return memory < ThreadDataManager::COMPILATION_MEMORY_LIMIT;
}