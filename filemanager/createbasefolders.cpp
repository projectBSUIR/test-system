#include "filemanager/filemanager.h"
#include "datamanager/datamanager.h"

void FileManager::createBaseFolders(){
    system("mkdir -m 755 -p ./TestSystemData > /dev/null");
    std::string command;
    for(int i = 0; i < DataManager::getMaximumThreadCount();
        i++){
        command ="mkdir -m 755 -p ./TestSystemData/ThreadData";
        command += char(i + 48);
        command += " > /dev/null";
        system(command.c_str());

        command = "cp -R ./testlib.h ./TestSystemData/ThreadData";
        command += char(i + 48);
        command += " > /dev/null";
        system(command.c_str());

        command = "mkdir -m 755 -p ./TestSystemData/ThreadRoot";
        command += char(i + 48);
        command += " > /dev/null";
        system(command.c_str());

        command = "mkdir -m 755 -p ./TestSystemData/ThreadRoot";
        command += char(i + 48);
        command += "/lib > /dev/null";
        system(command.c_str());

        command = "mkdir -m 755 -p ./TestSystemData/ThreadRoot";
        command += char(i + 48);
        command += "/lib64 > /dev/null";
        system(command.c_str());
    }
}