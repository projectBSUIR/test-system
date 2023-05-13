#include "queryhandler/queryhandler.h"

void QueryHandler::setTestingStatus(std::string json){
    //parse submission info to json
    Json::Value submissionInfoRoot;
    Json::Reader reader;
    reader.parse(
        json,
        submissionInfoRoot);

    //create input json
    Json::Value inputRoot;
    inputRoot["login"] = "testmachine";
    std::string password = "202979ff6105a2c7859b95efb411adc7392e43b6aae92a88";
    password += "d8992aba90fe83f4";
    inputRoot["password"] = password;
    inputRoot["payload"]["verdict"]["memory"] = 0;
    inputRoot["payload"]["verdict"]["time"] = 0; 
    inputRoot["payload"]["verdict"]["status"] = "Testing"; 
    inputRoot["payload"]["submission_id"] = 
        submissionInfoRoot["submission_id"];
    inputRoot["payload"]["problem_id"] = 
        submissionInfoRoot["problem_id"];
    Json::StyledWriter writer;
    std::string inputJson = writer.write(inputRoot);
    std::cout<<"Testing json - "<<inputJson<<"\n";
    //request
    do{
        http::Request request{"http://127.0.0.1:5000/testing/setVerdict"};
        const auto response = request.send("POST",
            inputJson,{{"Content-Type", "application/json"}});
        if(response.status.code != 200){
            std::cout<< "Set test status failed..."<<"\n";
            std::cout<< std::string(response.body.begin(),
                response.body.end())<<"\n";
            usleep(3000000);
        }
        else{
            std::cout<< "Set test status succeed..."<<"\n";
            std::cout<< std::string(response.body.begin(),
                response.body.end())<<"\n";
            break;
        }
    }while(true);
}
