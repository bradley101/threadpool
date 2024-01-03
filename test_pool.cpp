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

    pool.addTask(someTask, "Some data");

}
