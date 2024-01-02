#ifndef THREADPOOL_THREADPOOL_H
#define THREADPOOL_THREADPOOL_H

#include <atomic>
#include <future>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <queue>

enum taskState {
    PENDING = 1,
    RUNNING,
    COMPLETED,
    CANCELLED
};

void log(const std::string& msg)
{
    std::cout << msg << "\n";
}

template<typename RetType, typename... Args>
class tpool
{

private:
    void initThreadPool() {

    }

public:

    tpool(int numThreads = 10) : _numThreads(numThreads) {
        log("Initializing the Thread Pool");

        try {
            initThreadPool();
        }
        catch (std::runtime_error& err) {
            log("Unable to initialize Thread Pool. Exiting");
            throw err;
        }
    }

    std::future<RetType(Args...)> addTask(std::function<RetType(Args...)> func, Args&&... args) {
        
    }

    bool join();

private:

    std::vector<std::thread>    _tvec;

    std::condition_variable     _cv;
    std::mutex                  _mtx;

    int                         _numThreads;

    std::queue<std::packaged_task<RetType(Args...)>>     _taskQ;
};


#endif //THREADPOOL_THREADPOOL_H
