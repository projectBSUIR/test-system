#ifndef QUERYHANDLER_QUERYHANDLER_H
#define QUERYHANDLER_QUERYHANDLER_H

#include <vector>
#include <unistd.h>
#include <iostream>
#include <string>
#include <sstream>//
#include <jsoncpp/json/json.h>

#include "thirdparty/HTTPRequest.hpp"

class QueryHandler{
private:
    static pthread_t threadPointer;
public:
    static void sendVerdict(std::string verdict, int threadIndex);
    static void setTestingStatus(std::string json);
    static void tryPopSubmission(int threadIndex);
    static void* queryHandlerLoop(void* arg);
    static void startQueryHandlerThread();
    static void getPropertiesAndFilesJson(int threadIndex,
    std::vector<uint8_t>& jsonVector,std::vector<uint8_t>& archiveVector);
};

#endif