#include "queryhandler/queryhandler.h"
#include "testsystem/testsystem.h"
#include "threaddatamanager/threaddatamanager.h"

void QueryHandler::tryPopSubmission(int threadIndex){
    std::string inputJson = "{\"login\":\"testmachine\",\"password\":\"";
    inputJson += "202979ff6105a2c7859b95efb411adc7392e43b6aae92a88";
    inputJson +="d8992aba90fe83f4\",\"payload\":{}}";

    http::Request request{"http://127.0.0.1:5000/testing/extractSubmission"};
    const auto response = request.send("GET",inputJson,
        {{"Content-Type", "application/json"}});

    //get output
    std::string outputJson = std::string(response.body.begin(),
        response.body.end());
    
    long requestStatus = response.status.code;
   
    if(requestStatus != 200){
        std::cout << "Pop Submission Request failed...\n";
        std::cout<< outputJson<<"\n";
    }
    else{
        std::cout << "Pop Submission Request succeed, starting thread...\n";
        setTestingStatus(outputJson);
        ThreadDataManager::setThreadSubmissionInfo(threadIndex,
            outputJson);
        TestSystem::startTestRoutine(threadIndex);
    }
}