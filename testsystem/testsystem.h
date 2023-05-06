#ifndef TESTSYSTEM_TESTSYSTEM_H
#define TESTSYSTEM_TESTSYSTEM_H

#include <sys/mount.h>
#include <sys/resource.h>
#include <sys/syscall.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <cstring>
#include <string>
#include <fstream>
#include <iostream>
#include <fcntl.h>
#include <jsoncpp/json/json.h>

class TestSystem{
public:

    static void inputLoop();

    static void terminateThread(int ind);
    static void terminateProcess(int ind, int errorCode, std::string&);

    static void startTestRoutine(int ind);
    static void* testRoutine(void* arg);
    static bool testingLoop(int threadIndex);

    static int preparedCompilation(void* iP);
    static int preparedExecution(void* iP);

    static void setupUser(int solvePid);
    static void setupCgroup(int threadIndex, int solvePid);
    static void setupCgroupComp(int threadIndex, int solvePid);

    static bool compileChecker(int threadIndex);
    static bool compileSolution(int threadIndex);

    static bool checkOutOfMemory(int threadIndex, std::string path);
   
    static void getTaskInformation(int threadIndex);
    static void prepareReport(int index);
    
    //utility
    static void createBaseFolders();
    static void clearThreadDirectories(int index, int testNumber);
    static void createInputAndOutputFiles(int index,
        std::string& inputPath, std::string& outputPath);
    static void extractArchive(std::string path, int ind);
};

struct InfoPackage{
    int pipeSetup[2];
    int pipeExec[2];
    int threadIndex;
};

struct CompilationInfoPackage{
    int pipeSetup[2];
    int threadIndex;
    std::string command;
};

#endif