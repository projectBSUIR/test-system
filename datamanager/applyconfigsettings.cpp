#include "datamanager/datamanager.h"
#include "testsystem/testsystem.h"
#include "filemanager/filemanager.h"

void DataManager::applyConfigSettings(){
    std::ifstream file("./config.txt");
    if(!file.is_open()){
        FileManager::setLogFile("./logDataManager.txt",
            "Failed to open config.txt.");
        exit(1);
    }
    std::string config((std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>());
    file.close();

    Json::Value configJson;
    Json::Reader reader;
    bool parseStatus = reader.parse(
        config,
        configJson);

    if(!parseStatus){
        FileManager::setLogFile("./logDataManager.txt",
            "Invalid config.txt .");
        exit(1);
    }

    if(configJson.isMember("use_cpu_usage_limits") &&
        configJson["use_cpu_usage_limits"].isBool()){
        cpuLimiting = configJson["use_cpu_usage_limits"].asBool();
        if(cpuLimiting){
            std::cout << "Cpu limits are enabled.\n";
        }
        else{
            std::cout << "Cpu limits are disabled.\n";
        }
    }
    else{
        FileManager::setLogFile("./logDataManager.txt",
            "config.txt invalid \"use_cpu_usage_limits\" field.");
        exit(1);
    }


    if(configJson.isMember("terminal_logging") &&
        configJson["terminal_logging"].isBool()){
        terminalLogging = configJson["terminal_logging"].asBool();
        if(terminalLogging){
            std::cout << "Terminal logging mode enabled.\n";
        }
        else{
            std::cout << "Terminal logging mode disabled.\n";
        }
    }
    else{
        FileManager::setLogFile("./logDataManager.txt",
            "config.txt invalid \"terminal_logging\" field.");
        exit(1);
    }

    if(configJson.isMember("max_worker_thread_count") &&
        configJson["max_worker_thread_count"].isInt()){
        maximumThreadCount = configJson["max_worker_thread_count"].asInt();
        if(maximumThreadCount < 1 || maximumThreadCount > 5){
            FileManager::setLogFile("./logDataManager.txt",
                "config.txt invalid \"max_worker_thread_count\" "
                "field (must be 1-5).");
            exit(1);
        }
        else{
            std::cout << "Max thread count is set to "<<
            maximumThreadCount << ".\n";
        }
    }
    else{
        FileManager::setLogFile("./logDataManager.txt",
            "config.txt invalid \"max_worker_thread_count\" "
            "field.");
        exit(1);
    }

    if(cpuLimiting){
        if(configJson.isMember("max_testsystem_process_cpu_usage") &&
            configJson["max_testsystem_process_cpu_usage"].isInt()){
            testsystemCpuUsage = 
                configJson["max_testsystem_process_cpu_usage"].asInt();
            if(testsystemCpuUsage < 10||testsystemCpuUsage > 100){
                FileManager::setLogFile("./logDataManager.txt",
                    "config.txt invalid \"max_testsystem_process_cpu_usage\" "
                    "field (must be 10-100).");
                exit(1);
            }
            else{
                TestSystem::setupCgroupTestsystem(testsystemCpuUsage);
                std::cout << "Max testsystem cpu usage is set to " <<
              testsystemCpuUsage <<"%.\n";
           }
        }
        else{
            FileManager::setLogFile("./logDataManager.txt",
                "config.txt invalid \"max_testsystem_process_cpu_usage\" "
                "field.");
            exit(1);
       }

        if(configJson.isMember("max_worker_process_cpu_usage") &&
            configJson["max_worker_process_cpu_usage"].isInt()){
            workerCpuUsage = 
                configJson["max_worker_process_cpu_usage"].asInt();
            if(workerCpuUsage < 10 || workerCpuUsage > 100){
                FileManager::setLogFile("./logDataManager.txt",
                    "config.txt invalid \"max_worker_process_cpu_usage\" "
                    "field (must be 10-100).");
                exit(1);
            }
            else{
                std::cout << "Max worker cpu usage is set to " <<
                workerCpuUsage << "%.\n";
            }
        }
        else{
            FileManager::setLogFile("./logDataManager.txt",
                "config.txt invalid \"max_solution_process_cpu_usage\" "
                "field.");
            exit(1);
        }
    }   

    if(configJson.isMember("compilation_memory_limit") &&
        configJson["compilation_memory_limit"].isInt64()){
        compilationMemoryLimit = 
            configJson["compilation_memory_limit"].asInt64();
        if(compilationMemoryLimit < 1024){
            FileManager::setLogFile("./logDataManager.txt",
                "config.txt invalid \"compilation_memory_limit\" "
                "field (must be >=1024).");
            exit(1);
        }
        else{
            std::cout << "Compilation memory limit is set to " <<
            compilationMemoryLimit << ".\n";
        }
    }
    else{
        FileManager::setLogFile("./logDataManager.txt",
            "config.txt invalid \"compilation_memory_limit\" "
            "field.");
        exit(1);
    }

    if(configJson.isMember("compilation_time_limit") &&
        configJson["compilation_time_limit"].isInt()){
        compilationTimeLimit = 
            configJson["compilation_time_limit"].asInt();
        if(compilationTimeLimit < 100){
            FileManager::setLogFile("./logDataManager.txt",
                "config.txt invalid \"compilation_time_limit\" "
                "field.");
            exit(1);
        }
        else{
            std::cout << "Compilation time limit is set to " <<
            compilationTimeLimit << ".\n";
        }
    }
    else{
        FileManager::setLogFile("./logDataManager.txt",
            "config.txt invalid \"compilation_time_limit\" "
            "field.");
        exit(1);
    }

    if(configJson.isMember("testsystem_login") &&
        configJson["testsystem_login"].isString()){
        testsystemLogin = 
            configJson["testsystem_login"].asString();
        if(testsystemLogin == ""){
            FileManager::setLogFile("./logDataManager.txt",
                "config.txt invalid \"testsystem_login\" "
                "field.");
            exit(1);
        }
        else{
            std::cout << "Testsystem login is set.\n";
        }
    }
    else{
        FileManager::setLogFile("./logDataManager.txt",
            "config.txt invalid \"testsystem_login\" "
            "field.");
        exit(1);
    }

    if(configJson.isMember("testsystem_password") &&
        configJson["testsystem_password"].isString()){
        testsystemPassword = 
            configJson["testsystem_password"].asString();
        if(testsystemPassword == ""){
            FileManager::setLogFile("./logDataManager.txt",
                "config.txt invalid \"testsystem_password\" "
                "field.");
            exit(1);
        }
        else{
            std::cout << "Testsystem password is set.\n";
        }
    }
    else{
        FileManager::setLogFile("./logDataManager.txt",
            "config.txt invalid \"testsystem_password\" "
            "field.");
        exit(1);
    }

    if(configJson.isMember("server_url") &&
        configJson["server_url"].isString()){
        serverUrl = 
            configJson["server_url"].asString();
        if(serverUrl == ""){
            FileManager::setLogFile("./logDataManager.txt",
                "config.txt invalid \"server_url\" "
                "field.");
            exit(1);
        }
        else{
            std::cout << "Server url is set to " <<
            serverUrl << ".\n";
        }
    }
    else{
        FileManager::setLogFile("./logDataManager.txt",
            "config.txt invalid \"server_url\" "
            "field.");
        exit(1);
    }

    if(configJson.isMember("extract_submission_rout") &&
        configJson["extract_submission_rout"].isString()){
        extractSubmissionRout = 
            configJson["extract_submission_rout"].asString();
        if(extractSubmissionRout == ""){
            FileManager::setLogFile("./logDataManager.txt",
                "config.txt invalid \"extract_submission_rout\" "
                "field.");
            exit(1);
        }
        else{
            std::cout << "Extract submission rout is set to " <<
            extractSubmissionRout << ".\n";
        }
    }
    else{
        FileManager::setLogFile("./logDataManager.txt",
            "config.txt invalid \"extract_submission_rout\" "
            "field.");
        exit(1);
    }

    if(configJson.isMember("set_verdict_rout") &&
        configJson["set_verdict_rout"].isString()){
        setVerdictRout = 
            configJson["set_verdict_rout"].asString();
        if(setVerdictRout == ""){
            FileManager::setLogFile("./logDataManager.txt",
                "config.txt invalid \"set_verdict_rout\" "
                "field.");
            exit(1);
        }
        else{
            std::cout << "Set verdict rout is set to " <<
            setVerdictRout << ".\n";
        }
    }
    else{
        FileManager::setLogFile("./logDataManager.txt",
            "config.txt invalid \"set_verdict_rout\" "
            "field.");
        exit(1);
    }

    if(configJson.isMember("extract_testing_files_rout") &&
        configJson["extract_testing_files_rout"].isString()){
        extractTestingFilesRout = 
            configJson["extract_testing_files_rout"].asString();
        if(extractTestingFilesRout == ""){
            FileManager::setLogFile("./logDataManager.txt",
                "config.txt invalid \"extract_testing_files_rout\" "
                "field.");
            exit(1);
        }
        else{
            std::cout << "Extract testing files rout is set to " <<
            extractTestingFilesRout << ".\n";
        }
    }
    else{
        FileManager::setLogFile("./logDataManager.txt",
            "config.txt invalid \"extract_testing_files_rout\" "
            "field.");
        exit(1);
    }

    if(configJson.isMember("extract_problem_tests_rout") &&
        configJson["extract_problem_tests_rout"].isString()){
        extractProblemTestsRout = 
            configJson["extract_problem_tests_rout"].asString();
        if(extractProblemTestsRout == ""){
            FileManager::setLogFile("./logDataManager.txt",
                "config.txt invalid \"extract_problem_tests_rout\" "
                "field.");
            exit(1);
        }
        else{
            std::cout << "Extract problem tests rout is set to " <<
            extractProblemTestsRout << ".\n";
        }
    }
    else{
        FileManager::setLogFile("./logDataManager.txt",
            "config.txt invalid \"extract_problem_tests_rout\" "
            "field.");
        exit(1);
    }

    return;
}