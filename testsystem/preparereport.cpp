#include "testsystem/testsystem.h"
#include "threaddatamanager/threaddatamanager.h"
#include "queryhandler/queryhandler.h"

void TestSystem::prepareReport(int index){
    std::cout << "Thread " << index << ", ec = ";
    std::cout << ThreadDataManager::getThreadErrorCode(index);
    std::cout << '\n';

    std::string status;
    switch(ThreadDataManager::getThreadErrorCode(index)){
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
    + std::to_string(ThreadDataManager::getThreadTotalMemory(index))
    + ",\"status\":\"" + status
    + "\",\"time\":" 
    + std::to_string(ThreadDataManager::getThreadTotalTime(index))
    + "}";

    std::cout << verdict<<"\n";
    QueryHandler::sendVerdict(verdict, index);
}