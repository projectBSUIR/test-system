#include <pthread.h>
#include <chrono>

#ifndef THREADDATAMANAGER_THREADDATAMANAGER_H
#define THREADDATAMANAGER_THREADDATAMANAGER_H

class ThreadDataManager{

private:
    static int threadStatuses[6];
    static pthread_t threadPointers[6];
    static std::chrono::time_point<std::chrono::steady_clock> threadTimes[6];

public:
    static int getAvailableThread();
    static int getThreadStatus(int index);
    static pthread_t getThreadPointer(int index);
    static std::chrono::time_point<std::chrono::steady_clock> getThreadTime(int index);

    static void setThreadStatus(int index,int newStatus);
};

#endif