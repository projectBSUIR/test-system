#include "testsystem/testsystem.h"

int TestSystem::preparedExecution(void* iP){
    InfoPackage* infoPackage = (InfoPackage*)iP;
    
    close(infoPackage->pipeSetup[1]);
    close(infoPackage->pipeExec[0]);
    
    char tempInput;
    read(infoPackage->pipeSetup[0], &tempInput, 1);

    unshare(CLONE_NEWCGROUP);

    sethostname("isolated", strlen("isolated"));

    std::string command;
    command = "./TestSystemData/ThreadRoot";
    command += (char)(infoPackage->threadIndex + 48);
    command += "/lib";
    mount("./lib", command.c_str(), NULL, MS_BIND | MS_RDONLY, NULL);

    command = "./TestSystemData/ThreadRoot";
    command += (char)(infoPackage->threadIndex + 48);
    command += "/lib64";
    mount("./lib64", command.c_str(), NULL, MS_BIND | MS_RDONLY, NULL);

    std::string newRoot = "./TestSystemData/ThreadRoot";
    newRoot += (char)(infoPackage->threadIndex + 48);
    chroot(newRoot.c_str());
    chdir("/");

    int inputFD = open("input.txt", O_RDONLY);
    int outputFD = open("output.txt", O_WRONLY);
    dup2(inputFD, STDIN_FILENO);
    dup2(outputFD, STDOUT_FILENO);
    close(inputFD);
    close(outputFD);

    close(infoPackage->pipeExec[1]);
    
    setuid(65534);

    execl("/exec", "./exec", NULL);
    return -1;
}