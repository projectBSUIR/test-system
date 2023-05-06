#include "testsystem/testsystem.h"
#include "threaddatamanager/threaddatamanager.h"

bool TestSystem::checkOutOfMemory(int threadIndex, std::string path){
    long long oom_count;

    std::ifstream file(path.c_str());
    do{
        file >> path;
    }while(path != "oom");
    file >> oom_count;
    file.close();

    return !oom_count;
}