//
// Created by Shantanu Banerjee on 29/12/23.
//

#include "threadpool.h"

#include <iostream>

int someTask(const std::string data) {
    return 0;
}

int main() {
    tpool<someTask, const std::string> pool(5);

    pool.addTask(someTask, "Some data");

}
