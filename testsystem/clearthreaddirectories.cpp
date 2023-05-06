#include "testsystem/testsystem.h"
#include "threaddatamanager/threaddatamanager.h"

void TestSystem::clearThreadDirectories(int index,int testNumber){
    std::string tempString;
    for(int i = 0; i < testNumber; i++){
        tempString = "rm -f ./TestSystemData/ThreadData";
        tempString += (char)(index + 48);
        tempString += "/";
        if(i < 9){
            tempString += '0';
            tempString += char(i + 49);
        }
        else{
            tempString += std::to_string(i+1);
        }
        system(tempString.c_str());
        tempString += ".a";
        system(tempString.c_str());
    }

    tempString = "rm -f ./TestSystemData/ThreadData";
    tempString += (char)(index + 48);
    tempString += "/check.cpp";
    system(tempString.c_str());

    tempString = "rm -f ./TestSystemData/ThreadData";
    tempString += (char)(index + 48);
    tempString += "/solution.cpp";
    system(tempString.c_str());

    tempString = "rm -f ./TestSystemData/ThreadData";
    tempString += (char)(index + 48);
    tempString += "/checker";
    system(tempString.c_str());

    tempString = "rm -f ./TestSystemData/ThreadRoot";
    tempString += (char)(index + 48);
    tempString += "/output.txt";
    system(tempString.c_str());

    tempString ="rm -f ./TestSystemData/ThreadRoot";
    tempString += (char)(index + 48);
    tempString += "/input.txt";
    system(tempString.c_str());

    tempString = "rm -f ./TestSystemData/ThreadRoot";
    tempString += (char)(index + 48);
    tempString += "/exec";
    system(tempString.c_str());
}