//
// Created by Shantanu Banerjee on 29/12/23.
//

#include "threadpool.h"

#include <iostream>

int someTask(std::string data, int seconds) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
    std::cout << data << "\n";
    return 0;
}

int main() {
    tpool<int, std::string, int> pool(3);

    std::this_thread::sleep_for(std::chrono::seconds(1));

    pool.addTask(someTask, "Some data", 2);
    pool.addTask(someTask, "Some more datadata", 3);

    pool.closeThreads();

}
