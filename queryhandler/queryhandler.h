#ifndef QUERYHANDLER_QUERYHANDLER_H
#define QUERYHANDLER_QUERYHANDLER_H

#include <string>
#include <curl/curl.h>

class QueryHandler{
    static void startQueryHandlerThread();
    static void sendVerdict(std::string verdict);
}

#endif