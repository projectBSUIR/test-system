#include "testsystem/testsystem.h"
#include "datamanager/datamanager.h"
#include "filemanager/filemanager.h"

bool TestSystem::compileSolution(int threadIndex){
    std::string command = "g++ -std=c++20 ./";
    command += "TestSystemData/ThreadData";
    command += (char)(threadIndex + 48);
    command += "/solution.cpp -o ./";
    command += "TestSystemData/ThreadRoot";
    command += (char)(threadIndex + 48);
    command += "/exec ";
    command += "-I ./TestSystemData";
    command += "/ThreadData";
    command += (char)(threadIndex + 48);

    CompilationInfoPackage* compilationInfoPackage = 
        new CompilationInfoPackage;
    compilationInfoPackage->command = command;
    compilationInfoPackage->threadIndex = threadIndex;
    pipe(compilationInfoPackage->pipeSetup);

    char* compStack = new char[8096];
    int compPid = clone(preparedCompilation, compStack + 8096, 0,
        compilationInfoPackage);
    delete[] compStack;

    close(compilationInfoPackage->pipeSetup[0]);
        
    setupCgroupCompilation(threadIndex, compPid);

    close(compilationInfoPackage->pipeSetup[1]);

    DataManager::setThreadExecPid(threadIndex, compPid);
    DataManager::setThreadStatus(threadIndex, 2);

    int status;
    if(waitpid(compPid, &status, WUNTRACED | __WALL) == -1){
        FileManager::setLogFile("./logThread" 
            + std::to_string(threadIndex) + ".txt",
            "Failed to waitpid() for compilation process.");
        exit(1);
    }
    delete compilationInfoPackage;

    DataManager::setThreadExecPid(threadIndex, -1);
    DataManager::setThreadStatus(threadIndex, 1);

    int compExitCode = 1001;
    if(WIFEXITED(status)){
        if(!WEXITSTATUS(status)){
            compExitCode=0;
        }
    }

    std::string cgroupPath = "/sys/fs/cgroup/testsystemcomp";
    cgroupPath += (char)(threadIndex + 48);
    cgroupPath += "/memory.events";

    if(!checkOutOfMemory(threadIndex, cgroupPath)){
        DataManager::setThreadErrorCode(threadIndex, 1002);
        DataManager::setThreadTotalMemory(threadIndex,
            DataManager::getCompilationMemoryLimit() + 1024);
    }

    if(DataManager::getThreadErrorCode(threadIndex) !=0 ||
        compExitCode != 0){
        if(DataManager::getThreadErrorCode(threadIndex) == 0){
            DataManager::setThreadErrorCode(threadIndex, compExitCode);
        }
        return true;
    }

    command = "chmod 755 ./TestSystemData/ThreadRoot";
    command += (char)(threadIndex + 48);
    command += "/exec";
    system(command.c_str());
    return false;
}