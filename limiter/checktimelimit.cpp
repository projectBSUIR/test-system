#include "limiter/limiter.h"
#include "filemanager/filemanager.h"
#include "datamanager/datamanager.h"

bool Limiter::checkTimeLimit(int index){
    std::string path = "/sys/fs/cgroup/testsystem";
    path += (char)(index + 48);
    path += "/cpu.stat";

    long long time;

    std::ifstream file(path.c_str());
    if(!file.is_open()){
        FileManager::setLogFile("./logLimiter.txt",
            "Failed to open thread solution "
            "cgroup cpu.stat file.");
        exit(1);
    }
    do{
        file >> path;
    }while(path != "usage_usec");
    file >> time;
    file.close();

    if((std::time(nullptr) - DataManager::getThreadStartRealTime(index) >= 
        ((DataManager::getThreadTimeLimit(index) + 999) / 1000) * 3)){
        if(!DataManager::getThreadErrorCode(index))
            DataManager::setThreadTotalTime(index, 
                DataManager::getThreadTimeLimit(index));
        return false;
    }

    if(!DataManager::getThreadErrorCode(index))
        DataManager::setThreadTotalTime(index, time / 1000);
    return (time / 1000) < DataManager::getThreadTimeLimit(index);
}