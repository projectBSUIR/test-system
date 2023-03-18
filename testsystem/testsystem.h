#include <pthread.h>
#include <chrono>
using namespace std::chrono;
using namespace std;

class TestSystem
{
private:
    static pthread_t limiterThreadPointer;
    static int threadStatus[6];
    static pthread_t threadPointers[6];
    static time_point<steady_clock> threadTimes[6];

public:

    static void InputCycle();
    static void* LimiterCycle(void* arg);

    static bool IsThreadAvailable();

    static void StartTestThread();
    static void StartLimiterThread();

    static void TerminateThread(int ind);

    static void* TestFunction(void* arg);
};
