#include "filemanager/filemanager.h"

void FileManager::removeLogFiles(){
    std::string utilityCommand = "rm ./logFileManager.txt > /dev/null 2>&1";
    system(utilityCommand.c_str());

    utilityCommand = "rm ./logLimiter.txt > /dev/null 2>&1";
    system(utilityCommand.c_str());

    utilityCommand = "rm ./logAutotest.txt > /dev/null 2>&1";
    system(utilityCommand.c_str());

    utilityCommand = "rm ./logDataManager.txt > /dev/null 2>&1";
    system(utilityCommand.c_str());

    utilityCommand = "rm ./logQueryHandler.txt > /dev/null 2>&1";
    system(utilityCommand.c_str());

    for(int i=0;i<5;i++){
        utilityCommand = "rm ./logThread";
        utilityCommand += std::to_string(i);
        utilityCommand += ".txt > /dev/null 2>&1";
        system(utilityCommand.c_str());
    }
}