#include "threaddatamanager/threaddatamanager.h"

int ThreadDataManager::threadStatuses[6]{};

pthread_t ThreadDataManager::threadPointers[6]{};

std::chrono::time_point<std::chrono::steady_clock> ThreadDataManager::threadTimes[6]{};;