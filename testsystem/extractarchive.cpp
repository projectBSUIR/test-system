#include "threaddatamanager/threaddatamanager.h"
#include "testsystem.h"

void TestSystem::extractArchive(std::string path, int ind){
    path = "unzip -o " + path + " -d ./TestSystemData/ThreadData";
    path += (char)(ind + 48);
    path += " > /dev/null";
    system(path.c_str());
}