#include "queryhandler/queryhandler.h"

void QueryHandler::startQueryHandlerThread(){
    curl_global_init(CURL_GLOBAL_DEFAULT);
}
