#include "testsystem/testsystem.h"
#include "datamanager/datamanager.h"

void TestSystem::inputLoop(){
    std::string command;
    while(true){
        std::cin >> command;
        if(command == "exit"){
            DataManager::setMaximumThreadCount(0);
            bool areBusy;
            do{
                areBusy = false;
                for(int i = 0;i < 5;i++){
                    areBusy |= DataManager::getThreadStatus(i) > 0;
                }
                usleep(300000);
            }while(areBusy);
            return;
        }
    }
}