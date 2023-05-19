#include "datamanager/datamanager.h"
#include "testsystem/testsystem.h"
#include "limiter/limiter.h"
#include "queryhandler/queryhandler.h"
#include "filemanager/filemanager.h"
#include "thirdparty/base64.h"

int main(int argc, char* argv[]){

    FileManager::removeLogFiles();

    DataManager::applyConfigSettings();

    Limiter::startLimiterThread();

    FileManager::createBaseFolders();

    if(argc > 1){
        DataManager::setAutotestMode(true);
        TestSystem::autotestSequence();
        return 0;
    }
    else{
        std::cout << "Running in default mode.\n";
    }

    QueryHandler::startQueryHandlerThread();

    TestSystem::inputLoop();
    
    return 0;
}
