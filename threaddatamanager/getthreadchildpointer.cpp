#include <boost/process.hpp>

#include "threaddatamanager/threaddatamanager.h"

boost::process::child* ThreadDataManager::getThreadChildPointer(int index){
    return threadChildPointers[index];
}