#include "testsystem/testsystem.h"
#include "threaddatamanager/threaddatamanager.h"

int TestSystem::preparedCompilation(void* iP){
    CompilationInfoPackage* compilationInfoPackage =
         (CompilationInfoPackage*)iP;
    
    //close unused ends of pipes
    close(compilationInfoPackage->pipeSetup[1]);

    int devNull = open("/dev/null", O_WRONLY);
    dup2(devNull, STDERR_FILENO);
    dup2(devNull, STDOUT_FILENO);
    close(devNull);
    
    //wait for setup from parent
    char tempInput;
    read(compilationInfoPackage->pipeSetup[0],
        &tempInput,1);

    //start compilation
    execl("/bin/sh", "sh", "-c",
        compilationInfoPackage->command.c_str(), NULL);
    return -1;
}