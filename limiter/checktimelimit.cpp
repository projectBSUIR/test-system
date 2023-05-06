#include "limiter/limiter.h"
#include "threaddatamanager/threaddatamanager.h"

bool Limiter::checkTimeLimit(int index){
    std::string path = "/sys/fs/cgroup/testsystem";
    path += (char)(index + 48);
    path += "/cpu.stat";

    long long time;

    std::ifstream file(path.c_str());
    do{
        file >> path;
    }while(path != "usage_usec");
    file >> time;
    file.close();

    if(!ThreadDataManager::getThreadErrorCode(index))
        ThreadDataManager::setThreadTotalTime(index, time / 1000);
    return (time / 1000) < ThreadDataManager::getThreadTimeLimit(index);
}