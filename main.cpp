#include "testsystem.h"
#include <string>
#include <iostream>

int main()
{
    TestSystem::StartLimiterThread();
    TestSystem::InputCycle();
    return 0;
}
