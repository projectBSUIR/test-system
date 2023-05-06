#include "threaddatamanager/threaddatamanager.h"

int ThreadDataManager::threadTestQuantity[6]{};

int ThreadDataManager::threadErrorCodes[6]{};

int ThreadDataManager::threadStatuses[6]{};

pthread_t ThreadDataManager::threadPointers[6]{};

int ThreadDataManager::threadExecPids[6]{-1, -1, -1, -1, -1, -1};

int ThreadDataManager::threadTimeLimits[6]{};

int ThreadDataManager::threadMemoryLimits[6]{};
//in bytes (256 mb)
const long ThreadDataManager::COMPILATION_MEMORY_LIMIT = 1024 * 1024 * 256;
//in milliseconds
const long ThreadDataManager::COMPILATION_TIME_LIMIT = 4500;

int ThreadDataManager::maximumThreadCount = 5;

long ThreadDataManager::threadTotalMemory[6]{};

long ThreadDataManager::threadTotalTime[6]{};