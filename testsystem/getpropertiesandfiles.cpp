#include "queryhandler/queryhandler.h"
#include "threaddatamanager/threaddatamanager.h"
#include "testsystem.h"
#include "thirdparty/base64.h"

void TestSystem::getPropertiesAndFiles(int threadIndex){
    //decode buffers
    std::vector<unsigned char> solutionDecoded; 
    std::vector<unsigned char> checkerDecoded; 
    std::vector<unsigned char> archiveDecoded;

    std::vector<uint8_t> archiveVector;

    {
        //get request data
        std::vector<uint8_t> jsonVector;
        QueryHandler::getPropertiesAndFilesJson(threadIndex,jsonVector,
            archiveVector);

        //read json
        Json::Value root;
        Json::Reader reader;
        reader.parse(reinterpret_cast<const char*>(jsonVector.data()),
            reinterpret_cast<const char*>(jsonVector.data())
            + jsonVector.size(),root,false);
        
        //write limits
        ThreadDataManager::setThreadMemoryLimit(threadIndex, 
            (root)["problem_properties"]["memoryLimit"].asInt64());
        ThreadDataManager::setThreadTimeLimit(threadIndex,
            (root)["problem_properties"]["timeLimit"].asInt64());

        //decode strings
        decodeBase64(root["solution"].asString(), solutionDecoded);
        decodeBase64(root["checker"].asString(), checkerDecoded);
        //decodeBase64(archiveVector,archiveDecoded);
    }

    //create solution.cpp
    std::string path = "./TestSystemData/ThreadData";
    path += (char)(threadIndex + 48);
    path += "/solution.cpp";

    std::ofstream file(path, std::ios::out|std::ios::binary);
    for(int i=0;i<solutionDecoded.size();i++){
        file<<solutionDecoded[i];
    }
    file.close();

    //create check.cpp
    path = "./TestSystemData/ThreadData";
    path += (char)(threadIndex + 48);
    path += "/check.cpp";

    file.open(path, std::ios::out|std::ios::binary);
    for(int i=0;i<checkerDecoded.size();i++){
        file<<checkerDecoded[i];
    }
    file.close();


    //extract test files
    zip_source_t* src = zip_source_buffer_create(archiveVector.data(),
        archiveVector.size(), 0, NULL);

    std::cout<<src<<" - src\n";

    zip* z = zip_open_from_source(src, 0, NULL);

    std::cout<<z<<" - z\n";
    
    int numberOfTests = zip_get_num_entries(z,0)/2;
    
    std::cout <<numberOfTests<<" - number of Tests\n";

    std::string testName;
    std::string directoryPath = "./TestSystemData/ThreadData";
    directoryPath += (char)(threadIndex + 48);
    for(int i = 0; i < numberOfTests; i++){
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

    for(int i = 0; i < numberOfTests; i++){
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

    //set number of tests
    ThreadDataManager::setThreadTestQuantity(threadIndex, numberOfTests);
}