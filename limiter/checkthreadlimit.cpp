#include "limiter/limiter.h"

bool Limiter::checkThreadLimit(int threadCount){
    return threadCount<2;
}