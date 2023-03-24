#include <string>

#include "threaddatamanager/threaddatamanager.h"

int ThreadDataManager::threadErrorCodes[6]{};

int ThreadDataManager::threadStatuses[6]{};

pthread_t ThreadDataManager::threadPointers[6]{};

std::chrono::time_point<std::chrono::steady_clock> 
    ThreadDataManager::threadTimes[6]{};

boost::process::child* ThreadDataManager::threadChildPointers[6]={nullptr,nullptr,nullptr,
                                                                nullptr,nullptr,nullptr};

int ThreadDataManager::threadTimeLimits[6]{};

double ThreadDataManager::threadMemoryLimits[6]{};
//in kbs
const double ThreadDataManager::COMPILATION_MEMORY_LIMIT=256000;
//in milliseconds
const int ThreadDataManager::COMPILATION_TIME_LIMIT=45000;

const std::string ThreadDataManager::TEST_FILES_PATH="/home/emind/TestSystemStuff/TestSystem/testfiles";