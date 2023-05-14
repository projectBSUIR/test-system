#include "testsystem/testsystem.h"
#include "datamanager/datamanager.h"
#include "filemanager/filemanager.h"

void TestSystem::autotestSequence(){

    DataManager::setThreadMemoryLimit(0,1024 * 1024 * 256);
    DataManager::setThreadTimeLimit(0,1000);
    DataManager::setThreadTestQuantity(0,60);
    
    FileManager::extractArchive("./TestArchives/CE.zip",0);
    DataManager::setThreadStatus(0, 1);
    DataManager::setThreadErrorCode(0, 0);
    int* a = new int;
    *a = 0;
    testRoutine(a);

    FileManager::extractArchive("./TestArchives/TL.zip",0);
    DataManager::setThreadStatus(0, 1);
    DataManager::setThreadErrorCode(0, 0);
    a = new int;
    *a = 0;
    testRoutine(a);

    FileManager::extractArchive("./TestArchives/ML.zip",0);
    DataManager::setThreadStatus(0, 1);
    DataManager::setThreadErrorCode(0, 0);
    a = new int;
    *a = 0;
    testRoutine(a);

    FileManager::extractArchive("./TestArchives/AC.zip",0);
    DataManager::setThreadStatus(0, 1);
    DataManager::setThreadErrorCode(0, 0);
    a = new int;
    *a = 0;
    testRoutine(a);

    FileManager::extractArchive("./TestArchives/WA.zip",0);
    DataManager::setThreadStatus(0, 1);
    DataManager::setThreadErrorCode(0, 0);
    a = new int;
    *a = 0;
    testRoutine(a);

    FileManager::extractArchive("./TestArchives/FB.zip",0);
    DataManager::setThreadStatus(0, 1);
    DataManager::setThreadErrorCode(0, 0);
    a = new int;
    *a = 0;
    testRoutine(a);

    FileManager::extractArchive("./TestArchives/RE.zip",0);
    DataManager::setThreadStatus(0, 1);
    DataManager::setThreadErrorCode(0, 0);
    a = new int;
    *a = 0;
    testRoutine(a);
}