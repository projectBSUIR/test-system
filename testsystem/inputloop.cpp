#include <string>
#include <iostream>
#include <unistd.h>

#include "testsystem/testsystem.h"
#include "threaddatamanager/threaddatamanager.h"

void TestSystem::inputLoop(){
    std::string command;
    while(true){
        std::cin>>command;
        if(command=="exit"){
            break;
        }
        else if(command=="available?"){
            std::cout<<(ThreadDataManager::getAvailableThread()==-1)<<"\n";
        }
    }
}