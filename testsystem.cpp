#include "testsystem.h"
#include <string>
#include <iostream>
#include <unistd.h>

using namespace std;

//Static fields
pthread_t TestSystem::threadPointers[6]{};
int TestSystem::threadStatus[6]{};
time_point<steady_clock> TestSystem::threadTimes[6]{};
pthread_t TestSystem::limiterThreadPointer{};

void* TestSystem::TestFunction(void* arg)
{
    while(true)
    {
        cout<<"|test thread message|\n";
        sleep(1);
    }
}

bool TestSystem::IsThreadAvailable()
{
    for(int i=0;i<6;i++)
    {
        if(!threadStatus[i])
        {
            return true;
        }
    }
    return false;
}

void TestSystem::InputCycle()
{
    string command;
    while(true)
    {
        cin>>command;
        if(command=="exit")
        {
            break;
        }
        else if(command=="available?")
        {
            cout<<IsThreadAvailable()<<"\n";
        }
        else if(command=="startTestThread")
        {
            if(!IsThreadAvailable)
            {
                cout<<"No available thread!\n";
                continue;
            }
            StartTestThread();
            cout<<"Test thread is started!\n";
        }
    }
}

void* TestSystem::LimiterCycle(void* arg)
{
    int i=0;
    while (true)
    {
        for(i=0;i<6;i++)
        {
            if(!threadStatus[i])
            {
                continue;
            }
            else if(threadStatus[i]==1)
            {
                if(steady_clock::now()-threadTimes[i]>3s)
                {
                    cout<<"Thread is being terminated!\n";
                    TerminateThread(i);
                    continue;
                }
            }
        }
        usleep(20);
    }
}

void TestSystem::StartTestThread()
{
    int ind;
    for(int i=0;i<6;i++)
    {
        if(!threadStatus[i])
        {
            ind=i;
        }
    }
    threadStatus[ind]=1;
    threadTimes[ind]=steady_clock::now();
    int ret =  pthread_create(&threadPointers[ind], NULL, &TestFunction, NULL);
    if(ret)
    {
        cout<<"Failed to create a thread!\n";
    }
}

void TestSystem::StartLimiterThread()
{
    int ret =  pthread_create(&limiterThreadPointer, NULL, &LimiterCycle, NULL);
    if(ret)
    {
        cout<<"Failed to create a thread!\n";
    }
}

void TestSystem::TerminateThread(int ind)
{
    pthread_cancel(threadPointers[ind]);
    threadStatus[ind]=0;
}

