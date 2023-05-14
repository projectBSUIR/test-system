#include "testsystem/testsystem.h"
#include "datamanager/datamanager.h"
#include "filemanager/filemanager.h"

bool TestSystem::checkOutOfMemory(int threadIndex, std::string path){
    long long oom_count;

    std::ifstream file(path.c_str());
    if(!file.is_open()){
        FileManager::setLogFile("./logThread" + std::to_string(threadIndex) + ".txt",
            "Failed to open thread solution "
            "cgroup memory.events file.");
        exit(1);
    }
    do{
        file >> path;
    }while(path != "oom");
    file >> oom_count;
    file.close();

    return !oom_count;
}