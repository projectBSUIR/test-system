#ifndef DATAMANAGER_DATAMANAGER_H
#define DATAMANAGER_DATAMANAGER_H

#include <pthread.h>
#include <string>
#include <ctime>
#include <streambuf>
#include <jsoncpp/json/json.h>

class DataManager{

private:
    static std::string threadSubmissionInfo[5];

    static int threadErrorCodes[5];
    static int threadStatuses[5];

    static pthread_t threadPointers[5];
    static int threadExecPids[5];

    static int threadTimeLimits[5];
    static int threadMemoryLimits[5];
    static int threadTestQuantity[5];

    static long threadTotalMemory[5];
    static long threadTotalTime[5];
    static time_t threadStartRealTime[5];

    static long long compilationMemoryLimit;
    static long long compilationTimeLimit;

    static int maximumThreadCount;
    static int testsystemCpuUsage;
    static int workerCpuUsage;

    static bool terminalLogging;
    static bool cpuLimiting;

    static std::string testsystemLogin;
    static std::string testsystemPassword;

    static std::string serverUrl;
    static std::string extractSubmissionRout;
    static std::string setVerdictRout;
    static std::string extractTestingFilesRout;
    static std::string extractProblemTestsRout;

    static bool autotestMode;

public:

    static bool isAutotestMode();
    static void setAutotestMode(bool newValue);

    static void applyConfigSettings();

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
    static time_t getThreadStartRealTime(int index);
    static std::string getThreadSubmissionInfo(int index);
    static long long getCompilationMemoryLimit();
    static long long getCompilationTimeLimit();
    static int getTestsystemCpuUsage();
    static int getWorkerCpuUsage();
    static bool isTerminalLogging();
    static bool isCpuLimiting();
    static std::string getTestsystemLogin();
    static std::string getTestsystemPassword();
    static std::string getServerUrl();
    static std::string getExtractSubmissionRout();
    static std::string getSetVerdictRout();
    static std::string getExtractTestingFilesRout();
    static std::string getExtractProblemTestsRout();

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
    static void setThreadStartRealTime(int index, time_t newValue);
    static void setThreadSubmissionInfo(int index, std::string newValue);
};

#endif