#include <sys/time.h>
#include <sys/resource.h>
#include <boost/process.hpp>

#include "limiter/limiter.h"
#include "threaddatamanager/threaddatamanager.h"
#include "thirdparty/processmemusage.h"

bool Limiter::checkMemoryLimitCompilation(int index){
    double vm=0;
    double rss=0;
    processMemUsage(vm,rss,ThreadDataManager::getThreadChildPointer(index)->id());
    if(vm!=0){
        if(rss>ThreadDataManager::COMPILATION_MEMORY_LIMIT)
        {
            return false;
        }
    }
    return true;
}