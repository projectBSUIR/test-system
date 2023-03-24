#include <pthread.h>
#include <iostream>
#include <chrono>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <boost/process.hpp>
#include <boost/process/io.hpp>

#include "threaddatamanager/threaddatamanager.h"

void* testThreadRight(void* arg)
{
    std::string compilerCom="g++ -std=c++20 ";
    compilerCom+=ThreadDataManager::TEST_FILES_PATH;
    compilerCom+="/sc";
    compilerCom+=(char)(48+*(int*)arg);
    compilerCom+=".cpp -o ";
    compilerCom+=ThreadDataManager::TEST_FILES_PATH;
    compilerCom+="/exec";
    compilerCom+=(char)(48+*(int*)arg);
    compilerCom+=" -I";
    compilerCom+=ThreadDataManager::TEST_FILES_PATH;
    boost::process::child compC(compilerCom.c_str());
    ThreadDataManager::setThreadChildPointer(*(int*)arg,&compC);
    compC.wait();

    if(ThreadDataManager::getThreadErrorCode(*(int*)arg)==3)
    {
        std::cout<<"Thread "<<*(int*)arg<<" is being terminated due to memory limit on compilation!\n";
        ThreadDataManager::setThreadStatus(*(int*)arg,0);
        ThreadDataManager::setThreadErrorCode(*(int*)arg,0);
        ThreadDataManager::setThreadChildPointer(*(int*)arg,nullptr);
        int* ta=(int*)arg;
        delete ta;
        return nullptr;
    }
    else if(ThreadDataManager::getThreadErrorCode(*(int*)arg)==4)
    {
        std::cout<<"Thread "<<*(int*)arg<<" is being terminated due to time limit on compilation!\n";
        ThreadDataManager::setThreadStatus(*(int*)arg,0);
        ThreadDataManager::setThreadErrorCode(*(int*)arg,0);
        ThreadDataManager::setThreadChildPointer(*(int*)arg,nullptr);
        int* ta=(int*)arg;
        delete ta;
        return nullptr;
    }
    else if(compC.exit_code()!=0)
    {
        std::cout<<"Thread "<<*(int*)arg<<" is being terminated due to compilation error!\n";
        ThreadDataManager::setThreadStatus(*(int*)arg,0);
        ThreadDataManager::setThreadErrorCode(*(int*)arg,0);
        ThreadDataManager::setThreadChildPointer(*(int*)arg,nullptr);
        int* ta=(int*)arg;
        delete ta;
        return nullptr;
    }

    std::cout<<"Thread "<<*(int*)arg<<" succesfully compiled!\n";

    ThreadDataManager::setThreadStatus(*(int*)arg,2);
    ThreadDataManager::setThreadTime(*(int*)arg,std::chrono::steady_clock::now());
    std::string prPath=ThreadDataManager::TEST_FILES_PATH+"/exec"+(char)(48+*(int*)arg);
    std::string prIn=ThreadDataManager::TEST_FILES_PATH+"/in"+(char)(48+*(int*)arg);
    std::string prOut=ThreadDataManager::TEST_FILES_PATH+"/out"+(char)(48+*(int*)arg);
    boost::process::child c(prPath.c_str(),
        boost::process::std_in < prIn.c_str(),
        boost::process::std_out > prOut.c_str());
    ThreadDataManager::setThreadChildPointer(*(int*)arg,&c);
    c.wait();

    if(ThreadDataManager::getThreadErrorCode(*(int*)arg)==2)
    {
        std::cout<<"Thread "<<*(int*)arg<<" is being terminated due to memory limit!\n";
    }
    else if(ThreadDataManager::getThreadErrorCode(*(int*)arg)==1)
    {
        std::cout<<"Thread "<<*(int*)arg<<" is being terminated due to time limit!\n";
    }
    else if(ThreadDataManager::getThreadErrorCode(*(int*)arg)==0&&c.exit_code()==0)
    {
        std::chrono::duration<double> diff = std::chrono::steady_clock::now()-ThreadDataManager::getThreadTime(*((int*)arg));
        std::cout<<"Thread "<<*((int*)arg)<<" closed by itself, res = (in file) "<<" at "<<diff.count()<<"\n";
    }
    else
    {
        std::chrono::duration<double> diff = std::chrono::steady_clock::now()-ThreadDataManager::getThreadTime(*((int*)arg));
        std::cout<<"Thread "<<*((int*)arg)<<" closed by itself, runtime error "<<" at "<<diff.count()<<"\n";
    }
    ThreadDataManager::setThreadStatus(*(int*)arg,0);
    ThreadDataManager::setThreadErrorCode(*(int*)arg,0);
    ThreadDataManager::setThreadChildPointer(*(int*)arg,nullptr);
    int* ta=(int*)arg;
    delete ta;
    return nullptr;
}

void* testThreadTimeLimit(void* arg)
{
    std::string prPath=ThreadDataManager::TEST_FILES_PATH+"/lML";
    std::string prIn=ThreadDataManager::TEST_FILES_PATH+"/in"+(char)(48+*(int*)arg);
    std::string prOut=ThreadDataManager::TEST_FILES_PATH+"/out"+(char)(48+*(int*)arg);
    boost::process::child c(prPath.c_str(),
        boost::process::std_in < prIn.c_str(),
        boost::process::std_out > prOut.c_str());
    ThreadDataManager::setThreadChildPointer(*(int*)arg,&c);
    c.wait();
    
    if(ThreadDataManager::getThreadErrorCode(*(int*)arg)==2)
    {
        std::cout<<"Thread "<<*(int*)arg<<" is being terminated due to memory limit!\n";
    }
    else if(ThreadDataManager::getThreadErrorCode(*(int*)arg)==1)
    {
        std::cout<<"Thread "<<*(int*)arg<<" is being terminated due to time limit!\n";
    }
    else if(ThreadDataManager::getThreadErrorCode(*(int*)arg)==0&&c.exit_code()==0)
    {
        std::chrono::duration<double> diff = std::chrono::steady_clock::now()-ThreadDataManager::getThreadTime(*((int*)arg));
        std::cout<<"Thread "<<*((int*)arg)<<" closed by itself, res = (in file) "<<" at "<<diff.count()<<"\n";
    }
    else
    {
        std::chrono::duration<double> diff = std::chrono::steady_clock::now()-ThreadDataManager::getThreadTime(*((int*)arg));
        std::cout<<"Thread "<<*((int*)arg)<<" closed by itself, runtime error "<<" at "<<diff.count()<<"\n";
    }
    ThreadDataManager::setThreadStatus(*(int*)arg,0);
    ThreadDataManager::setThreadErrorCode(*(int*)arg,0);
    ThreadDataManager::setThreadChildPointer(*(int*)arg,nullptr);
    int* ta=(int*)arg;
    delete ta;
    return nullptr;
}

void startTestThreadRight()
{
    int ind=ThreadDataManager::getAvailableThread();
    if(ind==-1)
    {   
        std::cout<<"No available thread!";
        return;
    }
    int* a=new int;
    *a=ind;
    int ret =  pthread_create(ThreadDataManager::getThreadPointer(ind), NULL, &testThreadRight, a);
    ThreadDataManager::setThreadTime(ind,std::chrono::steady_clock::now());
    if(ret){
        std::cout<<"Failed to create a"<<ind<<" thread!\n";
    }

    ThreadDataManager::setThreadMemoryLimit(ind,256000);
    ThreadDataManager::setThreadTimeLimit(ind,3000);
    ThreadDataManager::setThreadStatus(ind,1);
}
void startTestThreadTimeLimit()
{
    int ind=ThreadDataManager::getAvailableThread();
    if(ind==-1)
    {   
        std::cout<<"No available thread!";
        return;
    }
    int* a=new int;
    *a=ind;
    int ret =  pthread_create(ThreadDataManager::getThreadPointer(ind), NULL, &testThreadTimeLimit, a);
    ThreadDataManager::setThreadTime(ind,std::chrono::steady_clock::now());
    if(ret){
        std::cout<<"Failed to create a"<<ind<<" thread!\n";
    }

    ThreadDataManager::setThreadMemoryLimit(ind,256000);
    ThreadDataManager::setThreadTimeLimit(ind,3000);
    ThreadDataManager::setThreadStatus(ind,1);
}
void startTestThreadMemoryLimit()
{
    int ind=ThreadDataManager::getAvailableThread();
    if(ind==-1)
    {   
        std::cout<<"No available thread!";
        return;
    }
    int* a=new int;
    *a=ind;
    int ret =  pthread_create(ThreadDataManager::getThreadPointer(ind), NULL, &testThreadTimeLimit, a);
    ThreadDataManager::setThreadTime(ind,std::chrono::steady_clock::now());
    if(ret){
        std::cout<<"Failed to create a"<<ind<<" thread!\n";
    }

    ThreadDataManager::setThreadMemoryLimit(ind,100);
    ThreadDataManager::setThreadTimeLimit(ind,3000);
    ThreadDataManager::setThreadStatus(ind,1);
}