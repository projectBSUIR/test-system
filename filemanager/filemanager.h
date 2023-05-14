#ifndef FILEMANAGER_FILEMANAGER_H
#define FILEMANAGER_FILEMANAGER_H

#include <fstream>
#include <iostream>
#include <string>
#include <streambuf>
#include "thirdparty/base64.h"
#include <jsoncpp/json/json.h>
#include <zip.h>

class FileManager{
public:
    static void removeLogFiles();
    static void setLogFile(std::string,std::string);
    static void createBaseFolders();
    static void clearThreadDirectories(int index, int testNumber);
    static void createInputAndOutputFiles(int index,
        std::string& inputPath, std::string& outputPath);
    static void extractArchive(std::string path, int ind);
    static void getTestFilesAndProperties(int threadIndex);
    static void setAutotestVerdict(std::string verdict);
};

#endif 