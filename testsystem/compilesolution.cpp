#include "testsystem/testsystem.h"
#include "threaddatamanager/threaddatamanager.h"

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

    CompilationInfoPackage* compilationInfoPackage = new CompilationInfoPackage;
    compilationInfoPackage->command = command;
    compilationInfoPackage->threadIndex = threadIndex;
    pipe(compilationInfoPackage->pipeSetup);

    //allocate stack and launch prepared execution as child process
    char* compStack = new char[8096];
    int compPid = clone(preparedCompilation, compStack + 8096, 0,
        compilationInfoPackage);
    delete[] compStack;

    //close unused ends of the pipes
    close(compilationInfoPackage->pipeSetup[0]);
        
    //setup user and cgroups
    setupCgroupComp(threadIndex, compPid);

    //pass the turn to prepared execution
    close(compilationInfoPackage->pipeSetup[1]);

    //set thread information
    ThreadDataManager::setThreadExecPid(threadIndex, compPid);
    ThreadDataManager::setThreadStatus(threadIndex, 2);

    //wait for solution to end
    int status;
    if(waitpid(compPid, &status, WUNTRACED | __WALL) == -1){
        perror("waitpid comp failed");
    }
    delete compilationInfoPackage;

    //update thread status
    ThreadDataManager::setThreadExecPid(threadIndex, -1);
    ThreadDataManager::setThreadStatus(threadIndex, 1);

    int compExitCode = 1001;
    if(WIFEXITED(status)){
        compExitCode = WEXITSTATUS(status);
    }

    if(compExitCode != 0){
        compExitCode = 1001;
    }

    std::string cgroupPath = "/sys/fs/cgroup/testsystemcomp";
    cgroupPath += (char)(threadIndex + 48);
    cgroupPath += "/memory.events";

    if(!checkOutOfMemory(threadIndex, cgroupPath)){
        ThreadDataManager::setThreadErrorCode(threadIndex, 1002);
        ThreadDataManager::setThreadTotalMemory(threadIndex,
            ThreadDataManager::COMPILATION_MEMORY_LIMIT + 1024);
    }

    //process compilation errors
    if(ThreadDataManager::getThreadErrorCode(threadIndex) !=0 ||
        compExitCode != 0){
        if(ThreadDataManager::getThreadErrorCode(threadIndex) == 0){
            ThreadDataManager::setThreadErrorCode(threadIndex, compExitCode);
        }
        return true;
    }

    command = "chmod 755 ./TestSystemData/ThreadRoot";
    command += (char)(threadIndex + 48);
    command += "/exec";
    system(command.c_str());
    return false;
}