#include "filemanager/filemanager.h"
#include "queryhandler/queryhandler.h"
#include "datamanager/datamanager.h"

void FileManager::getTestFilesAndProperties(int threadIndex){
    std::vector<uint8_t> archiveVector;
    QueryHandler::getTestArchive(threadIndex, archiveVector);

    zip_source_t* src = zip_source_buffer_create(archiveVector.data(),
        archiveVector.size(), 0, NULL);

    zip* z = zip_open_from_source(src, 0, NULL);

    if(z == NULL){
        FileManager::setLogFile("./logThread" 
            + std::to_string(threadIndex) + ".txt",
            "Failed open archive with logs.");
        exit(1);
    }
    
    int testCount = zip_get_num_entries(z, 0) / 2;

    std::ofstream file;

    std::string testName;
    std::string directoryPath = "./TestSystemData/ThreadData";
    directoryPath += (char)(threadIndex + 48);
    for(int i = 0; i < testCount; i++){
        testName = "";
        if(i < 9){
            testName += '0';
            testName += char(i + 49);
        }
        else{
            testName += std::to_string(i + 1);
        }

        zip_int64_t index = zip_name_locate(z, testName.c_str(),
            ZIP_FL_NOCASE);
        struct zip_stat st;
        zip_stat_index(z, index, 0, &st);
        char* contents = new char[st.size];

        zip_file* zfile = zip_fopen_index(z, index, 0);
        zip_fread(zfile, contents, st.size);
        zip_fclose(zfile);

        file.open(directoryPath + "/" + testName, std::ios::binary);
        file.write(contents, st.size);
        file.close();
        delete[] contents;
    }

    for(int i = 0; i < testCount; i++){
        testName = "";
        if(i < 9){
            testName += '0';
            testName += char(i + 49);
        }
        else{
            testName += std::to_string(i + 1);
        }
        
        testName += ".a";

        zip_int64_t index = zip_name_locate(z, testName.c_str(),
            ZIP_FL_NOCASE);
        struct zip_stat st;
        zip_stat_index(z, index, 0, &st);
        char* contents = new char[st.size];

        zip_file* zfile = zip_fopen_index(z, index, 0);
        zip_fread(zfile, contents, st.size);
        zip_fclose(zfile);

        file.open(directoryPath + "/" + testName, std::ios::binary);
        file.write(contents, st.size);
        file.close();
        delete[] contents;
    }

    zip_close(z);

    std::vector<uint8_t> solutionDecoded;
    std::vector<uint8_t> checkerDecoded;
    std::vector<uint8_t> jsonVector;

    QueryHandler::getSubmissionProperties(threadIndex, jsonVector);

    Json::Value root;
    Json::Reader reader;
    reader.parse(reinterpret_cast<const char*>(jsonVector.data()),
        reinterpret_cast<const char*>(jsonVector.data())
        + jsonVector.size(),root,false);
        
    DataManager::setThreadMemoryLimit(threadIndex, 
        (root)["problem_properties"]["memoryLimit"].asInt64());
    DataManager::setThreadTimeLimit(threadIndex,
        (root)["problem_properties"]["timeLimit"].asInt64());
    DataManager::setThreadTestQuantity(threadIndex, testCount);

    decodeBase64(root["solution"].asString(), solutionDecoded);
    decodeBase64(root["checker"].asString(), checkerDecoded);

    std::string path = "./TestSystemData/ThreadData";
    path += (char)(threadIndex + 48);
    path += "/solution.cpp";

    file.open(path, std::ios::out | std::ios::binary);
    for(int i=0; i<solutionDecoded.size(); i++){
        file << solutionDecoded[i];
    }
    file.close();

    path = "./TestSystemData/ThreadData";
    path += (char)(threadIndex + 48);
    path += "/check.cpp";

    file.open(path, std::ios::out | std::ios::binary);
    for(int i=0; i < checkerDecoded.size(); i++){
        file << checkerDecoded[i];
    }
    file.close();

    return;
}