#include "testsystem/testsystem.h"
#include "datamanager/datamanager.h"
#include "filemanager/filemanager.h"
#include "queryhandler/queryhandler.h"

void TestSystem::prepareReport(int index){
    std::string status;
    switch(DataManager::getThreadErrorCode(index)){
        case 0:
            status = "OK";
            break;
        case 1:
        case 2:
        case 3:
            status = "WA";
            break;

        case 1001:
        case 1002:
        case 1003:
            status = "CE";
            break;

        case 1004:
            status = "RE";
            break;
        case 1005:
            status = "ML";
            break;
        case 1006:
            status = "TL";
            break;
    }
    
    std::string verdict = "{\"memory\":"
    + std::to_string(DataManager::getThreadTotalMemory(index))
    + ",\"status\":\"" + status
    + "\",\"time\":" 
    + std::to_string(DataManager::getThreadTotalTime(index))
    + "}";

    if(DataManager::isTerminalLogging()){
        std::cout << "Thread " << index << ", ec = ";
        std::cout << DataManager::getThreadErrorCode(index);
        std::cout << '\n';
        std::cout << "Verdict - " << verdict <<"\n";
    }

    if(!DataManager::isAutotestMode()){
        QueryHandler::sendVerdict(verdict, index);
    }
    else{
        FileManager::setAutotestVerdict(status);
    }
}