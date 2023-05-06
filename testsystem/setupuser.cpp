#include "testsystem/testsystem.h"
#include "threaddatamanager/threaddatamanager.h"

void TestSystem::setupUser(int solvePid){
    std::string procPath = "/proc/" + std::to_string(solvePid);
    std::string tempString = procPath + "/uid_map";

    std::ofstream file(tempString.c_str());
    file << "0 " << getuid() << " 1\n";
    file << "65534 65534 1\n";
    file.close();

    tempStr = procPath + "/setgroups";
    file.open(tempString.c_str());
    file << "deny";
    file.close();

    tempStr = procPath + "/gid_map";
    file.open(tempString.c_str());
    file << "0 " << getgid() << " 1\n";
    file << "65534 65534 1\n";
    file.close();
}