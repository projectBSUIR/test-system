#ifndef THREADDATAMANAGER_THREADDATAMANAGER_H
#define THREADDATAMANAGER_THREADDATAMANAGER_H

#include <pthread.h>
#include <chrono>
#include <string>

class ThreadDataManager{

private:
    static int threadTestQuantity[6];
    static int threadErrorCodes[6];
    static int threadStatuses[6];
    static pthread_t threadPointers[6];
    static int threadExecPids[6];
    static int threadTimeLimits[6];
    static int threadMemoryLimits[6];
    static long threadTotalMemory[6];
    static long threadTotalTime[6];

    static int maximumThreadCount;
public:
    static const std::string MAIN_FOLDER_NAME;
    static const long COMPILATION_MEMORY_LIMIT;
    static const long COMPILATION_TIME_LIMIT;

    static int getAvailableThread();
    static int getThreadTestQuantity(int index);
    static int getThreadStatus(int index);
    static pthread_t* getThreadPointer(int index);
    static long getThreadTimeLimit(int index);
    static long getThreadMemoryLimit(int index);
    static int getThreadErrorCode(int index);
    static int getThreadExecPid(int index);
    static int getMaximumThreadCount();
    static long getThreadTotalMemory(int index);
    static long getThreadTotalTime(int index);

    static void setThreadExecPid(int index, int pid);
    static void setThreadTestQuantity(int index, int quantity);
    static void setThreadStatus(int index,int newStatus);
    static void setThreadTimeLimit(int index, long newLimit);
    static void setThreadMemoryLimit(int index,long newLimit);
    static void setThreadPointer(int index,pthread_t newPointer);
    static void setThreadErrorCode(int index,int errorCode);
    static void setMaximumThreadCount(int newValue);
    static void setThreadTotalMemory(int index,long newValue);
    static void setThreadTotalTime(int index, long newValue);
};

#endif