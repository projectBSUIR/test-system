#include "datamanager/datamanager.h"
#include "testsystem/testsystem.h"
#include "limiter/limiter.h"
#include "queryhandler/queryhandler.h"
#include "filemanager/filemanager.h"
#include "thirdparty/base64.h"

//Thread statuses:
//0 - free, 1 - accupied, 2 - compiling solution
//3 - running solution

//Error descriptions:
//1001 - CRE, 1002 - CML, 1003 - CTL
//1004 - RE, 1005 - ML, 1006 - TL

//Checker codes:
//0 - AC, 1 - WA, 2 - PE, 3 - FAIL

#include <fstream>
int main(int argc,char* argv[]){
    //remove previous log files
    FileManager::removeLogFiles();

    //create TestSystemData folder and its subfolders
    FileManager::createBaseFolders();

    //apply config
    DataManager::applyConfigSettings();

    //start limiter thread
    Limiter::startLimiterThread();

    //check argv to determine running mode
    if(argc > 1){
        DataManager::setAutotestMode(true);
        TestSystem::autotestSequence();
        return 0;
    }
    else{
        std::cout<<"Running in default mode.\n";
    }

    //start query thread
    QueryHandler::startQueryHandlerThread();

    //start main thread
    TestSystem::inputLoop();
    return 0;
}
