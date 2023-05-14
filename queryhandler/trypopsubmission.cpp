#include "queryhandler/queryhandler.h"
#include "testsystem/testsystem.h"
#include "datamanager/datamanager.h"

void QueryHandler::tryPopSubmission(int threadIndex){
    std::string inputJson = "{\"login\":\"";
    inputJson += DataManager::getTestsystemLogin();
    inputJson += "\",\"password\":\"";
    inputJson += DataManager::getTestsystemPassword();
    inputJson += "\",\"payload\":{}}";

    http::Request request{DataManager::getServerUrl() + 
        DataManager::getExtractSubmissionRout()};
    const auto response = request.send("GET",inputJson,
        {{"Content-Type", "application/json"}});

    //get output
    std::string outputJson = std::string(response.body.begin(),
        response.body.end());
    
    long requestStatus = response.status.code;
   
    if(requestStatus != 200){
        if(DataManager::isTerminalLogging()){
            std::cout << "Pop Submission Request failed...\n";
            std::cout<< outputJson<<"\n";
        }
    }
    else{
        setTestingStatus(outputJson);
        DataManager::setThreadSubmissionInfo(threadIndex,
            outputJson);
        TestSystem::startTestRoutine(threadIndex);
    }
}