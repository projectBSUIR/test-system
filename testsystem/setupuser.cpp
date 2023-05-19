#include "testsystem/testsystem.h"
#include "datamanager/datamanager.h"
#include "filemanager/filemanager.h"

void TestSystem::setupUser(int index, int solvePid){
    std::string procPath = "/proc/" + std::to_string(solvePid);
    std::string tempString = procPath + "/uid_map";

    std::ofstream file(tempString.c_str());
    if(!file.is_open()){
        FileManager::setLogFile("./logThread" + std::to_string(index) + ".txt",
            "Failed to open thread proc "
            "uid_map file.");
        exit(1);
    }
    file << "0 " << getuid() << " 1\n";
    file << "65534 65534 1\n";
    file.close();

    tempString = procPath + "/setgroups";
    file.open(tempString.c_str());
    if(!file.is_open()){
        FileManager::setLogFile("./logThread" + std::to_string(index) + ".txt",
            "Failed to open thread proc "
            "setgroups file.");
        exit(1);
    }
    file << "deny";
    file.close();

    tempString = procPath + "/gid_map";
    file.open(tempString.c_str());
    if(!file.is_open()){
        FileManager::setLogFile("./logThread" + std::to_string(index) + ".txt",
            "Failed to open thread proc "
            "gid_map file.");
        exit(1);
    }
    file << "0 " << getgid() << " 1\n";
    file << "65534 65534 1\n";
    file.close();
}