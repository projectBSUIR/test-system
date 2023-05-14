#include "filemanager/filemanager.h"

void FileManager::setLogFile(std::string path, std::string message){
    std::ofstream file(path,std::ios::trunc|std::ios::out);
    file << message;
    file.close();
    return;
}