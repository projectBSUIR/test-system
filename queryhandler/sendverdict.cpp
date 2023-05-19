#include "queryhandler/queryhandler.h"
#include "datamanager/datamanager.h"

void QueryHandler::sendVerdict(std::string verdict, int threadIndex){
    Json::Value submissionInfoRoot;
    Json::Reader reader;
    reader.parse(
        DataManager::getThreadSubmissionInfo(threadIndex),
        submissionInfoRoot);

    Json::Value verdictRoot;
    reader.parse(
        verdict,
        verdictRoot);

    Json::Value inputRoot;
    inputRoot["login"] = DataManager::getTestsystemLogin();
    inputRoot["password"] = DataManager::getTestsystemPassword();
    inputRoot["payload"]["verdict"] = verdictRoot;
    inputRoot["payload"]["submission_id"] =
        submissionInfoRoot["submission_id"];
    inputRoot["payload"]["problem_id"] = 
        submissionInfoRoot["problem_id"];
    Json::StyledWriter writer;
    std::string inputJson = writer.write(inputRoot);

    do{
        http::Request request{DataManager::getServerUrl() + 
            DataManager::getSetVerdictRout()};
        const auto response = request.send("POST",
            inputJson,{{"Content-Type", "application/json"}});
        if(response.status.code != 200){
            if(DataManager::isTerminalLogging()){
                std::cout << "Set verdict request failed..." << "\n";
                std::cout << std::string(response.body.begin(),
                    response.body.end()) << "\n";
            }
            usleep(3000000);
        }
        else{
            break;
        }
    }while(true);
}

