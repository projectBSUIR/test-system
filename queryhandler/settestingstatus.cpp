#include "queryhandler/queryhandler.h"
#include "datamanager/datamanager.h"

void QueryHandler::setTestingStatus(std::string json){
    //parse submission info to json
    Json::Value submissionInfoRoot;
    Json::Reader reader;
    reader.parse(
        json,
        submissionInfoRoot);

    //create input json
    Json::Value inputRoot;
    inputRoot["login"] = DataManager::getTestsystemLogin();
    inputRoot["password"] = DataManager::getTestsystemPassword();
    inputRoot["payload"]["verdict"]["memory"] = 0;
    inputRoot["payload"]["verdict"]["time"] = 0; 
    inputRoot["payload"]["verdict"]["status"] = "Testing"; 
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
                std::cout<< "Set test status failed..."<<"\n";
                std::cout<< std::string(response.body.begin(),
                    response.body.end())<<"\n";
            }
            usleep(3000000);
        }
        else{
            break;
        }
    }while(true);
}
