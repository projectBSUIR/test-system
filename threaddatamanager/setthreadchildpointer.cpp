#include <boost/process.hpp>

#include "threaddatamanager/threaddatamanager.h"

void ThreadDataManager::setThreadChildPointer(int index,
    boost::process::child* childp){
    threadChildPointers[index]=childp;
}