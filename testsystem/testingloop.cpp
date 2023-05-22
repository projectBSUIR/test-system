#include "testsystem/testsystem.h"
#include "datamanager/datamanager.h"
#include "filemanager/filemanager.h"

bool TestSystem::testingLoop(int threadIndex){
    std::string checkerPath;
    checkerPath = "./TestSystemData";
    checkerPath += "/ThreadData";
    checkerPath += (char)(threadIndex + 48);
    checkerPath += "/checker";

    std::string inputPath;
    inputPath = "./TestSystemData";
    inputPath += "/ThreadRoot";
    inputPath += (char)(threadIndex + 48);
    inputPath += "/input.txt";

    std::string outputPath;
    outputPath = "./TestSystemData";
    outputPath += "/ThreadRoot";
    outputPath += (char)(threadIndex + 48);
    outputPath += "/output.txt";

    std::string testPath;
    std::string utilityCommand;

    for(int i = 0; i < DataManager::getThreadTestQuantity(threadIndex);
        i++){

        testPath = "./TestSystemData";
        testPath += "/ThreadData";
        testPath += (char)(threadIndex + 48);
        testPath += "/";
        if(i < 9){
            testPath += '0';
            testPath += char(i + 49);
        }
        else{
            testPath += std::to_string(i + 1);
        }   

        FileManager::createInputAndOutputFiles(threadIndex, 
            inputPath, outputPath);
        utilityCommand = "cp " + testPath + " " + inputPath;
        system(utilityCommand.c_str());

        InfoPackage* infoPackage = new InfoPackage;
        infoPackage->threadIndex = threadIndex;
        pipe(infoPackage->pipeSetup);
        pipe(infoPackage->pipeExec);

        char* solveStack = new char[8096];
        int solvePid = clone(preparedExecution, solveStack+8096,
            CLONE_NEWUSER | CLONE_NEWNET | CLONE_NEWPID | CLONE_NEWNS
            | CLONE_NEWIPC | CLONE_NEWUTS, infoPackage);
        delete[] solveStack;

        close(infoPackage->pipeSetup[0]);
        close(infoPackage->pipeExec[1]);
        
        setupUser(threadIndex, solvePid);
        setupCgroupSolution(threadIndex, solvePid);

        close(infoPackage->pipeSetup[1]);

        char tempInput;
        read(infoPackage->pipeExec[0], &tempInput, 1);
        close(infoPackage->pipeExec[0]);

        DataManager::setThreadExecPid(threadIndex, solvePid);
        DataManager::setThreadStartRealTime(threadIndex, std::time(nullptr));
        DataManager::setThreadStatus(threadIndex,3);

        int status;
        if(waitpid(solvePid, &status, WUNTRACED | __WALL) == -1){
            FileManager::setLogFile("./logThread" 
                + std::to_string(threadIndex) + ".txt",
                "Failed to waitpid() for solution process.");
            exit(1);
        }
        delete infoPackage;

        DataManager::setThreadExecPid(threadIndex, -1);
        DataManager::setThreadStatus(threadIndex, 1);

        int solveExitCode = 1004;
        if(WIFEXITED(status)){
            if(!WEXITSTATUS(status))
                solveExitCode = 0;
        }

        std::string cgroupPath = "/sys/fs/cgroup/testsystem";
        cgroupPath += (char)(threadIndex + 48);
        cgroupPath += "/memory.events";
        if(!checkOutOfMemory(threadIndex, cgroupPath)){
            DataManager::setThreadErrorCode(threadIndex, 1005);
            DataManager::setThreadTotalMemory(threadIndex,
                DataManager::getThreadMemoryLimit(threadIndex) + 1024);
        }

        if(DataManager::getThreadErrorCode(threadIndex) !=0 ||
            solveExitCode != 0){
            if(DataManager::getThreadErrorCode(threadIndex) == 0){
                DataManager::setThreadErrorCode(threadIndex, solveExitCode);
            }
            return true;
        }
        
        utilityCommand = checkerPath + " " +
            testPath + " " + outputPath + " " + testPath 
            + ".a > /dev/null 2>&1";
        int checkerStatus = system(utilityCommand.c_str());
        int checkerCode = 1;
        if(WIFEXITED(checkerStatus)){
            checkerCode = WEXITSTATUS(checkerStatus);
        }

        if(checkerCode){
            DataManager::setThreadErrorCode(threadIndex, checkerCode);
            return true;
        }

        utilityCommand = "rm ./TestSystemData/ThreadRoot";
        utilityCommand += (char)(threadIndex + 48);
        utilityCommand += "/output.txt > /dev/null 2>&1";
        system(utilityCommand.c_str());

        utilityCommand = "rm ./TestSystemData/ThreadRoot";
        utilityCommand += (char)(threadIndex + 48);
        utilityCommand += "/input.txt > /dev/null 2>&1";
        system(utilityCommand.c_str());
    }
    return false;
}