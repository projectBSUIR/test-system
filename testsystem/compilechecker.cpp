#include "testsystem/testsystem.h"
#include "threaddatamanager/threaddatamanager.h"

bool TestSystem::compileChecker(int threadIndex){
    std::string command = "g++ -std=c++20 ./TestSystemData/ThreadData";
    command += (char)(threadIndex + 48);
    command += "/check.cpp -o ./TestSystemData/ThreadData";
    command += (char)(threadIndex + 48);
    command += "/checker -I ./TestSystemData";
    system(command.c_str());
    return false;
}