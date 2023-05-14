#include "testsystem/testsystem.h"
#include "datamanager/datamanager.h"
#include "filemanager/filemanager.h"

bool TestSystem::compileChecker(int threadIndex){
    std::string command = "g++ -std=c++20 ./TestSystemData/ThreadData";
    command += (char)(threadIndex + 48);
    command += "/check.cpp -o ./TestSystemData/ThreadData";
    command += (char)(threadIndex + 48);
    command += "/checker -I ./TestSystemData";
    int status = system(command.c_str());
    if(WEXITSTATUS(status)){
        FileManager::setLogFile("./logThread" + std::to_string(threadIndex) + ".txt",
            "Failed to compile checker.");
        exit(1);
    }
    return false;
}