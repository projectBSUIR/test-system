#include "queryhandler/queryhandler.h"
#include "threaddatamanager/threaddatamanager.h"

void QueryHandler::getPropertiesAndFilesJson(int threadIndex,
    std::vector<uint8_t>& jsonVector,std::vector<uint8_t>& archiveVector){

    //parse submission info to json
    Json::Value submissionInfoRoot;
    Json::Reader reader;
    reader.parse(
        ThreadDataManager::getThreadSubmissionInfo(threadIndex),
        submissionInfoRoot);

    //create input json
    Json::Value inputRoot;
    inputRoot["login"] = "testmachine";
    std::string password = "202979ff6105a2c7859b95efb411adc7392e43b6aae92a88";
    password += "d8992aba90fe83f4";
    inputRoot["password"] = password;
    inputRoot["payload"]["submission_id"] = 
        submissionInfoRoot["submission_id"];
    inputRoot["payload"]["problem_id"] = 
        submissionInfoRoot["problem_id"];
    Json::StyledWriter writer;
    std::string inputJson = writer.write(inputRoot);

    do{
        //request
        http::Request request{"http://127.0.0.1:5000/testing/extractTestingFiles"};
        auto response = request.send("GET",
            inputJson,
            {{"Content-Type", "application/json"}});

        long requestStatus = response.status.code;

        if(requestStatus != 200){
            std::cout << "Properties failed, trying again...\n";
            std::cout << std::string(response.body.begin(),
                response.body.end())<<"\n";
            usleep(3000000);
        }
        else{
            std::cout << "Properties request succeed...\n";
            jsonVector.swap(response.body);
            break;
        }
    }while(true);

    do{
        //request
        
        http::Request request{"http://127.0.0.1:5000/testing/extractProblemTests"};
        auto response = request.send("GET",
            inputJson,
            {{"Content-Type", "application/json"}});

        long requestStatus = response.status.code;

        if(requestStatus != 200){
            std::cout << "Archive failed, trying again...\n";
            std::cout << std::string(response.body.begin(),
                response.body.end())<<"\n";
            usleep(3000000);
        }
        else{
            std::cout << "Archive request succeed...\n";
            archiveVector.swap(response.body);
            break;
        }
    }while(true);
}