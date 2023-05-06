#include "queryhandler/queryhandler.h"

void QueryHandler::sendVerdict(std::string verdict){
    CURL* curl;
    CURLcode res;

    const char* url = "http://127.0.0.1:5000/setVerdict";
    const char* json = verdict.c_str();

    curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");

    do{
        curl = curl_easy_init();
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK){
            std::cout << "sendVerdict failed.\n";
        }
        curl_easy_cleanup(curl);
        if(){
            usleep(50);
        }
        else{
            break;
        }
    }while(true);
}

