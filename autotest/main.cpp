#include <iostream>
#include <fstream>
#include <streambuf>
#include <sys/wait.h>

int main(){
    std::cout << "Running autotests...\n";
    int status = system("sudo ./TestSystem 1 > /dev/null");
    if(WEXITSTATUS(status)){
        std::cout << "There was an error while"
         " performing tests, checking logs...\n";

        std::ifstream file("logDataManager.txt");
        if(file.is_open()){
            std::cout << "Found DataManager log : ";
            std::string log((std::istreambuf_iterator<char>(file)),
            std::istreambuf_iterator<char>());
            std::cout << log << "\n";
            file.close();
            return 0;
        }

        file.open("logFileManager.txt");
        if(file.is_open()){
            std::cout << "Found FileManager log : ";
            std::string log((std::istreambuf_iterator<char>(file)),
            std::istreambuf_iterator<char>());
            std::cout << log << "\n";
            file.close();
            return 0;
        }

        file.open("logLimiter.txt");
        if(file.is_open()){
            std::cout << "Found Limiter log : ";
            std::string log((std::istreambuf_iterator<char>(file)),
            std::istreambuf_iterator<char>());
            std::cout << log << "\n";
            file.close();
            return 0;
        }

        file.open("logQueryHandler.txt");
        if(file.is_open()){
            std::cout << "Found QueryHandler log : ";
            std::string log((std::istreambuf_iterator<char>(file)),
            std::istreambuf_iterator<char>());
            std::cout << log << "\n";
            file.close();
            return 0;
        }

        file.open("logThread0.txt");
        if(file.is_open()){
            std::cout << "Found Thread log : ";
            std::string log((std::istreambuf_iterator<char>(file)),
            std::istreambuf_iterator<char>());
            std::cout << log << "\n";
            file.close();
            return 0;
        }
        std::cout << "No log was found.\n";

        return 0;
    }

    std::cout << "Testsystem returned successfully,"
        " checking test verdicts...\n";

    std::string verdict;
    std::ifstream file("logAutotest.txt");
    
    verdict = "";
    std::getline(file,verdict);
    if(verdict == "CE"){
        std::cout << "\033[1;32mRight verdict\033[0m";
    }
    else{
        std::cout << "\033[1;31mWrong verdict\033[0m";
    }
    std::cout << " : Compilation Error test got "<< verdict << " verdict.\n";

    verdict = "";
    std::getline(file,verdict);
    if(verdict == "TL"){
        std::cout << "\033[1;32mRight verdict\033[0m";
    }
    else{
        std::cout << "\033[1;31mWrong verdict\033[0m";
    }
    std::cout << " : Time limit test got "<< verdict << " verdict.\n";

    verdict = "";
    std::getline(file,verdict);
    if(verdict == "ML"){
        std::cout << "\033[1;32mRight verdict\033[0m";
    }
    else{
        std::cout << "\033[1;31mWrong verdict\033[0m";
    }
    std::cout << " : Memory Limit test got "<< verdict << " verdict.\n";

    verdict = "";
    std::getline(file,verdict);
    if(verdict == "OK"){
        std::cout << "\033[1;32mRight verdict\033[0m";
    }
    else{
        std::cout << "\033[1;31mWrong verdict\033[0m";
    }
    std::cout << " : OK test got " << verdict << " verdict.\n";

    verdict = "";
    std::getline(file,verdict);
    if(verdict == "WA"){
        std::cout << "\033[1;32mRight verdict\033[0m";
    }
    else{
        std::cout << "\033[1;31mWrong verdict\033[0m";
    }
    std::cout << " : Wrong Answer test got "<< verdict << " verdict.\n";

    verdict = "";
    std::getline(file,verdict);
    if(verdict == "TL" || verdict == "ML"){
        std::cout << "\033[1;32mRight verdict\033[0m";
    }
    else{
        std::cout << "\033[1;31mWrong verdict\033[0m";
    }
    std::cout << " : Fork bomb test got "<< verdict << " verdict.\n";

    verdict = "";
    std::getline(file,verdict);
    if(verdict == "RE"){
        std::cout << "\033[1;32mRight verdict\033[0m";
    }
    else{
        std::cout << "\033[1;31mWrong verdict\033[0m";
    }
    std::cout << " : Runtime Error test got " << verdict << " verdict.\n";

    file.close();
    return 0;
}