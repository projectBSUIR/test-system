#include "datamanager/datamanager.h"

std::string DataManager::threadSubmissionInfo[5]{};

int DataManager::threadTestQuantity[5]{};
int DataManager::threadTimeLimits[5]{};
int DataManager::threadMemoryLimits[5]{};

pthread_t DataManager::threadPointers[5]{};
int DataManager::threadExecPids[5]{-1, -1, -1, -1, -1};

int DataManager::threadErrorCodes[5]{};
int DataManager::threadStatuses[5]{};

long long DataManager::compilationMemoryLimit;
long long DataManager::compilationTimeLimit;

long DataManager::threadTotalMemory[5]{};
long DataManager::threadTotalTime[5]{};
time_t DataManager::threadStartRealTime[5];

int DataManager::maximumThreadCount;

int DataManager::testsystemCpuUsage;
int DataManager::workerCpuUsage;

bool DataManager::terminalLogging;
bool DataManager::cpuLimiting;
bool DataManager::autotestMode;

std::string DataManager::testsystemLogin;
std::string DataManager::testsystemPassword;

std::string DataManager::serverUrl;
std::string DataManager::extractSubmissionRout;
std::string DataManager::setVerdictRout;
std::string DataManager::extractTestingFilesRout;
std::string DataManager::extractProblemTestsRout;