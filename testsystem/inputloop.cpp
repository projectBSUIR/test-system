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
        //
        else if(command=="testThreadThing3"){
            int a=ThreadDataManager::getAvailableThread();
            if(a!=-1){
                startTestRoutine(a);
            }
            a=ThreadDataManager::getAvailableThread();
            if(a!=-1){
                startTestRoutine(a);
            }
            a=ThreadDataManager::getAvailableThread();
            if(a!=-1){
                startTestRoutine(a);
            }
        }
        else if(command=="testThreadThing1"){
            int a=ThreadDataManager::getAvailableThread();
            if(a!=-1){
                startTestRoutine(a);
            }
        }
        else if(command=="testThreadThing2"){
            int a=ThreadDataManager::getAvailableThread();
            if(a!=-1){
                startTestRoutine(1);
            }
        }
        else if(command=="testThreadThing4"){
            int a=ThreadDataManager::getAvailableThread();
            if(a!=-1){
                startTestRoutine(3);
            }
        }
    }
}