#include <pthread.h>
#include <chrono>
#include <string>
#include <boost/process.hpp>

#ifndef THREADDATAMANAGER_THREADDATAMANAGER_H
#define THREADDATAMANAGER_THREADDATAMANAGER_H

class ThreadDataManager{

private:
    static int threadTestQuantity[6];
    static int threadErrorCodes[6];
    static int threadStatuses[6];
    static pthread_t threadPointers[6];
    static boost::process::child* threadChildPointers[6];
    static int threadTimeLimits[6];
    static double threadMemoryLimits[6];
    static std::chrono::time_point<std::chrono::steady_clock> threadTimes[6];

public:
    static const std::string MAIN_FOLDER_NAME;
    static const double COMPILATION_MEMORY_LIMIT;
    static const int COMPILATION_TIME_LIMIT;

    static int getAvailableThread();
    static int getThreadTestQuantity(int index);
    static int getThreadStatus(int index);
    static pthread_t* getThreadPointer(int index);
    static std::chrono::time_point<std::chrono::steady_clock> getThreadTime(int index);
    static int getThreadTimeLimit(int index);
    static double getThreadMemoryLimit(int index);
    static boost::process::child* getThreadChildPointer(int index);
    static int getThreadErrorCode(int index);

    static void setThreadTestQuantity(int index, int quantity);
    static void setThreadStatus(int index,int newStatus);
    static void setThreadTime(int index, std::chrono::time_point<std::chrono::steady_clock> newTime);
    static void setThreadTimeLimit(int index, int newLimit);
    static void setThreadMemoryLimit(int index,double newLimit);
    static void setThreadPointer(int index,pthread_t newPointer);
    static void setThreadChildPointer(int index,boost::process::child* childPointer);
    static void setThreadErrorCode(int index,int errorCode);
};

#endif