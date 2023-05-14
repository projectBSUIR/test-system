#include "limiter/limiter.h"
#include "filemanager/filemanager.h"
#include "datamanager/datamanager.h"

bool Limiter::checkTimeLimitCompilation(int index){
    std::string path = "/sys/fs/cgroup/testsystemcomp";
    path += (char)(index + 48);
    path += "/cpu.stat";

    long long time;

    std::ifstream file(path.c_str());
    if(!file.is_open()){
        FileManager::setLogFile("./logLimiter.txt",
            "Failed to open thread compilation "
            "cgroup cpu.stat file.");
        exit(1);
    }
    do{
        file >> path;
    }while(path != "usage_usec");
    file >> time;
    file.close();

    if(!DataManager::getThreadErrorCode(index))
        DataManager::setThreadTotalTime(index, time / 1000);
    
    return (time / 1000) < DataManager::getCompilationTimeLimit();
}