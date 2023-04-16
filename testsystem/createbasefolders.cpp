#include <string>
#include <iostream>
#include <unistd.h>
#include <boost/process.hpp>
#include <boost/process/io.hpp>

#include "testsystem/testsystem.h"
#include "threaddatamanager/threaddatamanager.h"

void TestSystem::createBaseFolders(){
    boost::process::system("mkdir -m 755 -p "+ThreadDataManager::MAIN_FOLDER_NAME);
    for(int i=0;i<6;i++){
        boost::process::system("mkdir -m 755 -p ./"+
            ThreadDataManager::MAIN_FOLDER_NAME+"/ThreadData"+(char)(i+48));
        boost::process::system("cp -R ./testlib.h ./"+
            ThreadDataManager::MAIN_FOLDER_NAME+"/ThreadData"+(char)(i+48));
        boost::process::system("mkdir -m 755 -p ./"+
            ThreadDataManager::MAIN_FOLDER_NAME+"/ThreadRoot"+(char)(i+48));
        boost::process::system("cp -R ./lib ./"+ThreadDataManager::MAIN_FOLDER_NAME+"/ThreadRoot"+(char)(i+48));
        boost::process::system("cp -R ./lib64 ./"+
            ThreadDataManager::MAIN_FOLDER_NAME+"/ThreadRoot"+(char)(i+48));
        boost::process::system("chmod 755 ./"+
            ThreadDataManager::MAIN_FOLDER_NAME+"/ThreadRoot"+(char)(i+48)+"/lib");
        boost::process::system("chmod 755 ./"+
            ThreadDataManager::MAIN_FOLDER_NAME+"/ThreadRoot"+(char)(i+48)+"/lib64");
    }
}