#include "filemanager/filemanager.h"

void FileManager::setAutotestVerdict(std::string verdict){
    std::ofstream file("./logAutotest.txt",std::ios::out|std::ios::app);
    file << verdict <<"\n";
    file.close();
    return;
}