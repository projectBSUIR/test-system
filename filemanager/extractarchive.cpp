#include "filemanager/filemanager.h"
#include "datamanager/datamanager.h"

void FileManager::extractArchive(std::string path, int ind){
    path = "unzip -o " + path + " -d ./TestSystemData/ThreadData";
    path += (char)(ind + 48);
    path += " > /dev/null";
    system(path.c_str());
}