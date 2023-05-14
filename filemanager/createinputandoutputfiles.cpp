#include "filemanager/filemanager.h"
#include "datamanager/datamanager.h"

void FileManager::createInputAndOutputFiles(int index,
    std::string& inputPath, std::string& outputPath){
    std::string tempString;
    tempString = "touch ./TestSystemData/ThreadRoot";
    tempString += (char)(index + 48);
    tempString += "/input.txt";
    system(tempString.c_str());

    tempString = "touch ./TestSystemData/ThreadRoot";
    tempString += (char)(index + 48);
    tempString += "/output.txt";
    system(tempString.c_str());

    tempString = "chmod 766 " + outputPath;
    system(tempString.c_str());

    tempString = "chmod 744 " + inputPath;
    system(tempString.c_str());
}