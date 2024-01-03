//
// Created by Shantanu Banerjee on 29/12/23.
//

#include "threadpool.h"

#include <iostream>

int someTask(std::string data) {
    std::cout << data << "\n";
    return 0;
}

int main() {
    tpool<int, std::string> pool(1);

    std::this_thread::sleep_for(std::chrono::seconds(1));

    pool.addTask(someTask, "Some data");
    pool.addTask(someTask, "Some more datadata");

}
