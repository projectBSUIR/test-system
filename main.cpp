#include <string>
#include <iostream>

#include "testsystem/testsystem.h"
#include "limiter/limiter.h"

int main()
{
    Limiter::startLimiterThread();
    TestSystem::inputLoop();
    return 0;
}
