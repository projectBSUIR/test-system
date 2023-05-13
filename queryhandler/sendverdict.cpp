#include "queryhandler/queryhandler.h"
#include "threaddatamanager/threaddatamanager.h"

void QueryHandler::sendVerdict(std::string verdict, int threadIndex){
    //parse submission info to json
    Json::Value submissionInfoRoot;
    Json::Reader reader;
    reader.parse(
        ThreadDataManager::getThreadSubmissionInfo(threadIndex),
        submissionInfoRoot);

    //parse verdict
    Json::Value verdictRoot;
    reader.parse(
        verdict,
        verdictRoot);

    //create input json
    Json::Value inputRoot;
    inputRoot["login"] = "testmachine";
    std::string password = "202979ff6105a2c7859b95efb411adc7392e43b6aae92a88";
    password += "d8992aba90fe83f4";
    inputRoot["password"] = password;
    inputRoot["payload"]["verdict"] = verdictRoot;
    inputRoot["payload"]["submission_id"] =
        submissionInfoRoot["submission_id"];
    inputRoot["payload"]["problem_id"] = 
        submissionInfoRoot["problem_id"];
    Json::StyledWriter writer;
    std::string inputJson = writer.write(inputRoot);

    //request
    do{
        http::Request request{"http://127.0.0.1:5000/testing/setVerdict"};
        const auto response = request.send("POST",
            inputJson,{{"Content-Type", "application/json"}});
        if(response.status.code != 200){
            usleep(3000000);
        }
        else{
            std::cout<< "Set verdict failed..."<<"\n";
            std::cout<< std::string(response.body.begin(),
                response.body.end())<<"\n";
            break;
        }
    }while(true);
}

