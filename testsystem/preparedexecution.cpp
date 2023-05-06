#include "testsystem/testsystem.h"
#include "threaddatamanager/threaddatamanager.h"

int TestSystem::preparedExecution(void* iP){
    InfoPackage* infoPackage = (InfoPackage*)iP;
    
    //close unused ends of pipes
    close(infoPackage->pipeSetup[1]);
    close(infoPackage->pipeExec[0]);
    
    //wait for setup from parent
    char tempInput;
    read(infoPackage->pipeSetup[0], &tempInput, 1);

    //unshare cgroup
    unshare(CLONE_NEWCGROUP);

    //change hostname
    sethostname("isolated", strlen("isolated"));

    //mount libs
    std::string command;
    command = "./TestSystemData/ThreadRoot";
    command += (char)(infoPackage->threadIndex + 48);
    command += "/lib";
    mount("./lib", command.c_str(), NULL, MS_BIND | MS_RDONLY, NULL);

    command = "./TestSystemData/ThreadRoot";
    command += (char)(infoPackage->threadIndex + 48);
    command += "/lib64";
    mount("./lib64", command.c_str(), NULL, MS_BIND | MS_RDONLY, NULL);

    //chroot
    std::string newRoot = "./TestSystemData/ThreadRoot";
    newRoot += (char)(infoPackage->threadIndex + 48);
    chroot(newRoot.c_str());
    chdir("/");

    //set input & output
    int inputFD = open("input.txt", O_RDONLY);
    int outputFD = open("output.txt", O_WRONLY);
    dup2(inputFD, STDIN_FILENO);
    dup2(outputFD, STDOUT_FILENO);
    close(inputFD);
    close(outputFD);

    //pass the turn to parent
    close(infoPackage->pipeExec[1]);
    
    //remove user privileges
    setuid(65534);

    //start solution
    execl("/exec", "./exec", NULL);
    return -1;
}