#ifndef TESTSYSTEM_TESTSYSTEM_H
#define TESTSYSTEM_TESTSYSTEM_H

#include <vector>
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
#include <zip.h>

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

    static void setupUser(int solvePid, int index);
    static void setupCgroupSolution(int threadIndex, int solvePid);
    static void setupCgroupCompilation(int threadIndex, int solvePid);
    static void setupCgroupTestsystem(int cpuProc);

    static bool compileChecker(int threadIndex);
    static bool compileSolution(int threadIndex);

    static bool checkOutOfMemory(int threadIndex, std::string path);
   
    static void prepareReport(int index);

    static void autotestSequence();
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