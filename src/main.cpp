#include <iostream>
#include <atomic>
#include <thread>
#include <cassert>
#include <vector>
#include "bbst/Tree.h"

int main() {
    auto tree = new BBST::Tree();

    auto insert_work = [&] (int start, int stop) {
        for (int i=start; i<stop; i++) {
            tree->insert(i);
        }
    };

    auto delete_work = [&] (int start, int stop) {
        for (int i=start; i<stop; i++) {
            tree->remove(i);
        }
    };

    for (int i=0; i<256; i++) {
        std::vector<std::thread> threads;
        threads.reserve(8);
        threads.emplace_back(insert_work, 0, 32);
        threads.emplace_back(delete_work, 1, 10);

        for (auto& thread : threads) {
            thread.join();
        }
    }

    tree->print("inorder");

    delete tree;
    tree = nullptr;
    return 0;
}
