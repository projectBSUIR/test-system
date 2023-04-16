#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <pthread.h>
#include <iostream>
#include <chrono>

#include "testsystem/testsystem.h"
#include "threaddatamanager/threaddatamanager.h"

//debug
std::chrono::time_point<std::chrono::steady_clock> threadDebugTimes[6];

void ClearThreadDirectories(int index,int testNumber){
    std::string tempStr;
    for(int i=0;i<testNumber;i++){
        tempStr="rm -f ./"+ThreadDataManager::MAIN_FOLDER_NAME+
            "/ThreadData"+(char)(index+48)+"/";
        if(i<9){
            tempStr+='0';
            tempStr+=char(i+49);
        }
        else{
            tempStr+=std::to_string(i+1);
        }
        boost::process::system(tempStr);
        boost::process::system(tempStr+".a");
    }

    boost::process::system("rm -f ./"+ThreadDataManager::MAIN_FOLDER_NAME+
        "/ThreadData"+(char)(index+48)+"/check.cpp");
    boost::process::system("rm -f ./"+ThreadDataManager::MAIN_FOLDER_NAME+
        "/ThreadData"+(char)(index+48)+"/solution.cpp");
    boost::process::system("rm -f ./"+ThreadDataManager::MAIN_FOLDER_NAME+
        "/ThreadData"+(char)(index+48)+"/checker");

    boost::process::system("rm -f ./"+ThreadDataManager::MAIN_FOLDER_NAME+
        "/ThreadRoot"+(char)(index+48)+"/output.txt");
    boost::process::system("rm -f ./"+ThreadDataManager::MAIN_FOLDER_NAME+
        "/ThreadRoot"+(char)(index+48)+"/input.txt");
    boost::process::system("rm -f ./"+ThreadDataManager::MAIN_FOLDER_NAME+
        "/ThreadRoot"+(char)(index+48)+"/exec");
}

void CreateInputAndOutputFiles(int index){
    boost::process::system("touch ./"+ThreadDataManager::MAIN_FOLDER_NAME+
        "/ThreadRoot"+(char)(index+48)+"/input.txt");
    boost::process::system("touch ./"+ThreadDataManager::MAIN_FOLDER_NAME+
        "/ThreadRoot"+(char)(index+48)+"/output.txt");
}

void ConsoleReportPreparing(int index){
    std::cout<<"Thread "<<index<<" preparing failure, ec = ";
    std::cout<<ThreadDataManager::getThreadErrorCode(index);
    std::chrono::duration<double> diff=std::chrono::steady_clock::now()-
        threadDebugTimes[index];
    std::cout<<", at "<<diff.count()<<"\n";
}

void ConsoleReportTesting(int index,int checkerCode, int testNumber=-1){
    if(!checkerCode){
        std::cout<<"Thread "<<index<<" accepted, ec = 0";
        std::chrono::duration<double> diff=std::chrono::steady_clock::now()-
            threadDebugTimes[index];
        std::cout<<", at "<<diff.count()<<"\n";
        return;
    }
    std::cout<<"Thread "<<index<<" testing failure, test = ";
    std::cout<<testNumber<<", ec = "<<checkerCode;
    std::chrono::duration<double> diff=std::chrono::steady_clock::now()-
        threadDebugTimes[index];
    std::cout<<", at "<<diff.count()<<"\n";
}

void SetTestPath(std::string& path, int threadIndex,int i){
    path="./"+ThreadDataManager::MAIN_FOLDER_NAME;
    path+="/ThreadData";
    path+=(char)(threadIndex+48);
    path+="/";
    if(i<9){
        path+='0';
        path+=char(i+49);
    }
    else{
        path+=std::to_string(i+1);
    }
}

void SetExecPath(std::string& path, int threadIndex){
    path="./"+ThreadDataManager::MAIN_FOLDER_NAME;
    path+="/ThreadRoot";
    path+=(char)(threadIndex+48);
    path+="/exec";
}

void SetRootPath(std::string& path, int threadIndex){
    path="./"+ThreadDataManager::MAIN_FOLDER_NAME;
    path+="/ThreadRoot";
    path+=(char)(threadIndex+48);
}

void SetCheckerPath(std::string& path, int threadIndex){
    path="./"+ThreadDataManager::MAIN_FOLDER_NAME;
    path+="/ThreadData";
    path+=(char)(threadIndex+48);
    path+="/checker";
}

void SetOutputPath(std::string& path, int threadIndex){
    path="./"+ThreadDataManager::MAIN_FOLDER_NAME;
    path+="/ThreadRoot";
    path+=(char)(threadIndex+48);
    path+="/output.txt";
}

void SetInputPath(std::string& path, int threadIndex){
    path="./"+ThreadDataManager::MAIN_FOLDER_NAME;
    path+="/ThreadRoot";
    path+=(char)(threadIndex+48);
    path+="/input.txt";
}

void SetChildCommand(std::string& command,std::string& rootPath,
    std::string& execPath){
    command="sudo unshare -i -n -u -C  chroot --userspec=65534:65534 "+
    rootPath+" /exec";
}

void* TestSystem::TestRoutine(void* arg){
    //delete arg dynamic memory
    int threadIndex=*(int*)arg;
    int* a=(int*)arg;
    delete a;

    //debug
    threadDebugTimes[threadIndex]=std::chrono::steady_clock::now();

    //get packages and info
    //archive it into threaddata(ind)
    //change limits according to the info

    ThreadDataManager::setThreadTestQuantity(threadIndex,60);
    ThreadDataManager::setThreadMemoryLimit(threadIndex,256000);
    ThreadDataManager::setThreadTimeLimit(threadIndex,2000);
    
    //compile checker
    std::string compilerCom="g++ -std=c++20 ./"
        +ThreadDataManager::MAIN_FOLDER_NAME+"/ThreadData"
        +(char)(threadIndex+48)
        +"/check.cpp "
        +" -o ./"
        +ThreadDataManager::MAIN_FOLDER_NAME+"/ThreadData"
        +(char)(threadIndex+48)
        +"/checker -I ./"
        +ThreadDataManager::MAIN_FOLDER_NAME;
    boost::process::system(compilerCom);

    //compile solution
    compilerCom="g++ -std=c++20 ./"
        +ThreadDataManager::MAIN_FOLDER_NAME+"/ThreadData"
        +(char)(threadIndex+48)
        +"/solution.cpp -o ./"
        +ThreadDataManager::MAIN_FOLDER_NAME+"/ThreadRoot"
        +(char)(threadIndex+48)
        +"/exec "
        + "-I ./" + ThreadDataManager::MAIN_FOLDER_NAME
        +"/ThreadData"+(char)(threadIndex+48);

    ThreadDataManager::setThreadTime(threadIndex,
        std::chrono::steady_clock::now());
    ThreadDataManager::setThreadStatus(threadIndex,2);
    boost::process::child compC(compilerCom.c_str(),
        boost::process::std_out>boost::process::null);
    ThreadDataManager::setThreadChildPointer(threadIndex,&compC);
    compC.wait();
    ThreadDataManager::setThreadStatus(threadIndex,1);

    //process compilation errors
    if(ThreadDataManager::getThreadErrorCode(threadIndex)!=0||
        compC.exit_code()!=0){
        ConsoleReportPreparing(threadIndex);
        ClearThreadDirectories(threadIndex,
            ThreadDataManager::getThreadTestQuantity(threadIndex));
        ThreadDataManager::setThreadStatus(threadIndex,0);
        return nullptr;
    }

    boost::process::system("chmod 755 ./"+ThreadDataManager::MAIN_FOLDER_NAME+
        "/ThreadRoot"+(char)(threadIndex+48)+"/exec");

    //testing loop
    std::string checkerPath;
    std::string inputPath;
    std::string outputPath;
    std::string testPath;
    std::string execPath;
    std::string rootPath;
    std::string childCommand;
    SetCheckerPath(checkerPath,threadIndex);
    SetInputPath(inputPath,threadIndex);
    SetOutputPath(outputPath,threadIndex);
    SetExecPath(execPath,threadIndex);
    SetRootPath(rootPath,threadIndex);
    SetChildCommand(childCommand,rootPath,execPath);
    for(int i=0;i<ThreadDataManager::getThreadTestQuantity(threadIndex);
        i++){
        SetTestPath(testPath,threadIndex,i);

        //set test data to input.txt, clear output.txt
        CreateInputAndOutputFiles(threadIndex);
        boost::process::system("chmod 766 "+outputPath);
        boost::process::system("chmod 744 "+inputPath);
        boost::process::system("cp "+testPath+" "+inputPath);

        //run solution
        boost::process::child execC(childCommand.c_str(),
            boost::process::std_in < testPath.c_str(),
            boost::process::std_out > outputPath.c_str());
        ThreadDataManager::setThreadStatus(threadIndex,3);
        ThreadDataManager::setThreadTime(threadIndex,
            std::chrono::steady_clock::now());
        ThreadDataManager::setThreadChildPointer(threadIndex,&execC);
        execC.wait();
        ThreadDataManager::setThreadStatus(threadIndex,1);

        //process limits/runtime errors
        if(ThreadDataManager::getThreadErrorCode(threadIndex)!=0||
            execC.exit_code()!=0){
            int ec;
            if(execC.exit_code()!=0) ec=execC.exit_code();
            else{
                ec=ThreadDataManager::getThreadErrorCode(threadIndex);
                
            }
            ConsoleReportTesting(threadIndex,ec,i+1);
            ClearThreadDirectories(threadIndex,
                ThreadDataManager::getThreadTestQuantity(threadIndex));
            ThreadDataManager::setThreadStatus(threadIndex,0);
            return nullptr;
        }
        
        //run checker
        int checkerCode = boost::process::system(checkerPath+" "+
            testPath+" "+outputPath+" "+testPath+".a");

        //check checker result
        if(checkerCode)
        {
            ConsoleReportTesting(threadIndex,checkerCode,i+1);
            ClearThreadDirectories(threadIndex,
                ThreadDataManager::getThreadTestQuantity(threadIndex));
            ThreadDataManager::setThreadStatus(threadIndex,0);
            return nullptr;
        }

        //remove input and output
        boost::process::system("rm ./"+ThreadDataManager::MAIN_FOLDER_NAME+
            "/ThreadRoot"+(char)(threadIndex+48)+"/output.txt");
        boost::process::system("rm ./"+ThreadDataManager::MAIN_FOLDER_NAME+
            "/ThreadRoot"+(char)(threadIndex+48)+"/input.txt");
    }

    //final verdict 
    ConsoleReportTesting(threadIndex,0,-1);
    ClearThreadDirectories(threadIndex,
        ThreadDataManager::getThreadTestQuantity(threadIndex));
    ThreadDataManager::setThreadStatus(threadIndex,0);
    return nullptr;
}