#include "threaddatamanager/threaddatamanager.h"

int ThreadDataManager::getAvailableThread(){
    for(int i=0;i<6;i++){
        if(!threadStatuses[i]){
            return i;
        }
    }
    return -1;
}