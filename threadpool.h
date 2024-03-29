#ifndef THREADPOOL_THREADPOOL_H
#define THREADPOOL_THREADPOOL_H

#include <algorithm>
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
        for (auto idx = 0; idx < _numThreads; ++idx) {
            std::thread th([&] {
                bool closeTh = false;
                while (!closeTh)
                {
                    auto task = std::packaged_task<RetType()>([]{ return 0; });
                    {
                        std::unique_lock<std::mutex> lock(_mtx);
                        _cv.wait(lock);
                        if (_shutdown) {
                            closeTh = true;
                            continue;
                        }
                        auto _task = std::move(_taskQ.front()); _taskQ.pop();
                        std::swap(task, _task);
                    }

                    task();
                }

            });
            _tvec.push_back(std::move(th));
        }
    }

public:

    ~tpool() {
        closeThreads();
        for (auto& th : _tvec) {
            th.join();
        }
    }

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

    std::future<RetType> addTask(std::function<RetType(Args...)> func, Args&&... args) {
        std::packaged_task<RetType()> task(std::bind(func, args...));
        auto fut = task.get_future();
        {
            std::lock_guard<std::mutex> lock(_mtx);
            _taskQ.push(std::move(task));
        }
        _cv.notify_all();
        return fut;
    }

    bool closeThreads() {
        {
            std::lock_guard<std::mutex> lock(_mtx);
            _shutdown = true;
        }
        _cv.notify_all();
    }

private:

    std::vector<std::thread>    _tvec;

    std::condition_variable     _cv;
    std::mutex                  _mtx;

    int                         _numThreads;

    std::queue<std::packaged_task<RetType()>>     _taskQ;

    bool                        _shutdown;
};


#endif //THREADPOOL_THREADPOOL_H
