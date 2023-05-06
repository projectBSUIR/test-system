#include "testsystem/testsystem.h"
#include "threaddatamanager/threaddatamanager.h"

void TestSystem::inputLoop(){
    std::string command;
    while(true){
        std::cin >> command;
        if(command == "exit"){
            break;
        }
        else if(command == "available?"){
            std::cout << 
                (ThreadDataManager::getAvailableThread() == -1) << "\n";
        }
        else if(command == "startTestFB"){
            int a = ThreadDataManager::getAvailableThread();
            if(a != -1){
                std::cout << "Running FB Test on thread " << a << "...\n";
                extractArchive("./TestArchives/FB.zip", a);
                startTestRoutine(a);
            }
        }
        else if(command == "startTestCE"){
            int a = ThreadDataManager::getAvailableThread();
            if(a != -1){
                std::cout << "Running CE Test on thread " << a << "...\n";
                extractArchive("./TestArchives/CE.zip", a);
                startTestRoutine(a);
            }
        }
        else if(command == "startTestRE"){
            int a = ThreadDataManager::getAvailableThread();
            if(a != -1){
                std::cout << "Running RE Test on thread " << a <<"...\n";
                extractArchive("./TestArchives/RE.zip", a);
                startTestRoutine(a);
            }
        }
        else if(command == "startTestTL"){
            int a = ThreadDataManager::getAvailableThread();
            if(a != -1){
                std::cout<<"Running TL Test on thread " << a <<"...\n";
                extractArchive("./TestArchives/TL.zip",a);
                startTestRoutine(a);
            }
        }
        else if(command == "startTestML"){
            int a = ThreadDataManager::getAvailableThread();
            if(a != -1){
                std::cout << "Running ML Test on thread " << a <<"...\n";
                extractArchive("./TestArchives/ML.zip",a);
                startTestRoutine(a);
            }
        }
        else if(command == "startTestAC"){
            int a = ThreadDataManager::getAvailableThread();
            if(a != -1){
                std::cout << "Running AC Test on thread " << a <<"...\n";
                extractArchive("./TestArchives/AC.zip",a);
                startTestRoutine(a);
            }
        }
        else if(command == "startTestWA"){
            int a = ThreadDataManager::getAvailableThread();
            if(a != -1){
                std::cout << "Running WA Test on thread " << a <<"...\n";
                extractArchive("./TestArchives/WA.zip",a);
                startTestRoutine(a);
            }
        }
        else if(command == "startTestAll"){
            int a = ThreadDataManager::getAvailableThread();
            if(a != -1){
                std::cout << "Running ML Test on thread " << a << "...\n";
                extractArchive("./TestArchives/ML.zip", a);
                startTestRoutine(a);
            }
            a = ThreadDataManager::getAvailableThread();
            if(a != -1){
                std::cout << "Running AC Test on thread " << a <<"...\n";
                extractArchive("./TestArchives/AC.zip", a);
                startTestRoutine(a);
            }
            a = ThreadDataManager::getAvailableThread();
            if(a != -1){
                std::cout << "Running CE Test on thread " << a <<"...\n";
                extractArchive("./TestArchives/CE.zip", a);
                startTestRoutine(a);
            }
            a = ThreadDataManager::getAvailableThread();
            if(a != -1){
                std::cout << "Running RE Test on thread " << a <<"...\n";
                extractArchive("./TestArchives/RE.zip", a);
                startTestRoutine(a);
            }
            a = ThreadDataManager::getAvailableThread();
            if(a != -1){
                std::cout << "Running TL Test on thread " << a <<"...\n";
                extractArchive("./TestArchives/TL.zip", a);
                startTestRoutine(a);
            }
            a = ThreadDataManager::getAvailableThread();
            if(a != -1){
                std::cout << "Running WA Test on thread " << a << "...\n";
                extractArchive("./TestArchives/WA.zip", a);
                startTestRoutine(a);
            }
        }
    }
}