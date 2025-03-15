#include <iostream>
#include <thread>
#include <cassert>
#include <vector>
#include "bbst/Tree.h"
#include "orderbook/OrderBook.h"


int main() {
    // /*
    auto orderBook = new OrderBook::OrderBook();

    orderBook->writeCopy.insert(1);
    orderBook->writeCopy.search(1);

    delete orderBook;
    return 0;
    // */

    /*
    // Test out the BBST
    auto tree = new BBST::Tree<int>();

    auto insert_work = [&] (int start, int stop) {
        for (int i=start; i<stop; i++) {
            const int val = i;
            tree->insert(val);
        }
    };

    auto delete_work = [&] (int start, int stop) {
        for (int i=start; i<stop; i++) {
            const int val = i;
            tree->remove(val);
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
    */
}
