#include <iostream>
#include <fstream>
#include <mutex>
#include <thread>
#include <string>
#include <memory> // std::unique_ptr 사용
#include <stdexcept> // std::runtime_error 사용

class Logger {
private:
    static std::unique_ptr<Logger> instance;
    static std::mutex init_mtx;
    static std::mutex write_mtx;
    std::ofstream logFile;
    
    // 친구 코드 로직: private 생성자 구현
    Logger(const std::string& filename){
        logFile.open(filename, std::ios::out | std::ios::trunc);
        if(logFile.is_open()){
            logFile << "[Init] Logger started." << std::endl;
        }
        else{
            throw std::runtime_error("Failed open file");
        }
    }
    // 복사 생성/대입 연산자 명시적 삭제는 친구 코드에 없었으므로 생략 (default로 남김)
    
public:
    // 친구 코드 로직: 소멸자 구현
    ~Logger(){
        if(logFile.is_open()){
            logFile << "[Shutdown] Logger closed." << std::endl;
            logFile.close();
        }
    }
    
    // 친구 코드 로직: getInstance 구현 (스레드 안전 초기화)
    static Logger* getInstance(const std::string& filename = "Test/output2.txt") {
        // 친구 코드와 동일하게 lock_guard를 이용한 동기화
        std::lock_guard<std::mutex> lock(init_mtx); 
        if(!instance){
            instance.reset(new Logger(filename));
        }
        return instance.get();
    }

    // 친구 코드 로직: log 구현
    void log(const std::string& message) {
        // 친구 코드와 동일하게 lock_guard를 이용한 쓰기 동기화
        std::lock_guard<std::mutex> writeLock(write_mtx); // 변수명만 writeLock으로 변경
        logFile << message << std::endl;
    }

};

// 정적 멤버 변수 정의 (원본 코드의 변수명 유지)
std::unique_ptr<Logger> Logger::instance;
std::mutex Logger::init_mtx;
std::mutex Logger::write_mtx;