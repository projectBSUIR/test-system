#include "queryhandler/queryhandler.h"
#include "datamanager/datamanager.h"

void QueryHandler::getSubmissionProperties(int threadIndex,
    std::vector<uint8_t>& jsonVector){

    Json::Value submissionInfoRoot;
    Json::Reader reader;
    reader.parse(
        DataManager::getThreadSubmissionInfo(threadIndex),
        submissionInfoRoot);

    Json::Value inputRoot;
    inputRoot["login"] = DataManager::getTestsystemLogin();
    inputRoot["password"] = DataManager::getTestsystemPassword();
    inputRoot["payload"]["submission_id"] = 
        submissionInfoRoot["submission_id"];
    inputRoot["payload"]["problem_id"] = 
        submissionInfoRoot["problem_id"];
    Json::StyledWriter writer;
    std::string inputJson = writer.write(inputRoot);

    do{
        http::Request request{DataManager::getServerUrl() +
            DataManager::getExtractTestingFilesRout()};
        auto response = request.send("GET",
            inputJson,
            {{"Content-Type", "application/json"}});

        long requestStatus = response.status.code;

        if(requestStatus != 200){
            if(DataManager::isTerminalLogging()){
                std::cout << "Testing files request failed, trying again...\n";
                std::cout << std::string(response.body.begin(),
                    response.body.end()) << "\n";
            }
            usleep(3000000);
        }
        else{
            jsonVector.swap(response.body);
            break;
        }
    }while(true);
}