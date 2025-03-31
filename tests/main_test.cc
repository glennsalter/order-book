#include "../src/bbst/Tree.h"
#include "../src/orderbook/SPSCQueue.h"

#include <gtest/gtest.h>
#include <iostream>
#include <memory>
#include <format>

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}

TEST (SimpleTest, SimpleTest) {
    EXPECT_EQ(1, 1);
}

TEST(InsertTest, TestBBST) {
    auto tree = std::make_unique<BBST::Tree<size_t>>();
    size_t start = 0, stop = 2 << 4;
    for (size_t i=start; i<=stop; i++) {
        tree->insert(i);
    }

    size_t lowest;
    tree->lowest(lowest);
    EXPECT_EQ(lowest, start);

    size_t highest;
    tree->highest(highest);
    EXPECT_EQ(highest, stop);
}

TEST(HeightTest, TestBBST) {
    // Inserts 2^max_height nodes
    // Height should be at most max_height + 1
    auto tree = std::make_unique<BBST::Tree<size_t>>();
    size_t max_height = 13;
    for (size_t i=0; i<1<<max_height; i++) {
        tree->insert(i);
    }
    const size_t height = tree->height();
    EXPECT_LE(height, max_height + 1);
}

TEST(DeleteTest, TestBBST) {
    auto tree = std::make_unique<BBST::Tree<size_t>>();
    for (size_t i=0; i<25; i++) {
        tree->insert(i);
    }

    for (size_t i=2; i<25; i=i+2) {
        tree->remove(i);
    }

    for (size_t i=2; i<25; i=i+2) {
        bool found = tree->search(i);
        EXPECT_EQ(found, false);
    }
}

TEST(ConcurrentTest, TestBBST) {
    /*
     * This test concurrently tries to insert the numbers 0...31 while deleting 1...9
     * Does this 256 times
     * Prints out the inorder traversal, lowest, and highest value
     */
    auto tree = std::make_unique<BBST::Tree<size_t>>();

    auto insert_work = [&] (size_t start, size_t stop) {
        for (size_t i=start; i<stop; i++) {
            const size_t val = i;
            tree->insert(val);
        }
    };

    auto delete_work = [&] (size_t start, size_t stop) {
        for (size_t i=start; i<stop; i++) {
            const size_t val = i;
            tree->remove(val);
        }
    };

    for (size_t i=0; i<256; i++) {
        std::vector<std::thread> threads;
        threads.reserve(8);
        threads.emplace_back(insert_work, 0, 32);
        threads.emplace_back(delete_work, 1, 10);

        for (auto& thread : threads) {
            thread.join();
        }
    }

    std::cout << "Inorder traversal: ";
    tree->print("inorder");

    size_t lowest, highest;
    tree->lowest(lowest);
    tree->highest(highest);
    std::cout << std::format("Lowest: {}, Highest: {}\n", lowest, highest);
}

TEST(PushPopTest, TestSPSCQueue) {
    using namespace OrderBook;

    auto queue = std::make_unique<SPSCQueue<BBSTOperation<size_t>>>(5);

    for (int i=0; i<5; i++) {
        auto op = BBSTOperation<size_t>(OperationType::Insert, i);
        if (!queue->push(op)) {
            std::cout << "Full\n";
        }
    }

    for (int i=0; i<5; i++) {
        BBSTOperation<size_t> op{};
        if (queue->pop(op)) {
            std::cout << op.param << "\n";
        } else {
            std::cout << "Empty\n";
        }
    }
}

TEST(ConcurrentTest, TestSPSCQueue) {
    /*
     * This test concurrently tries to push and pop to the queue
     */
    using namespace OrderBook;

    auto queue = std::make_unique<SPSCQueue<BBSTOperation<size_t>>>(2<<8);

    auto push_work = [&] (size_t start, size_t stop) {
        for (size_t i=start; i<stop; i++) {
            auto op = OrderBook::BBSTOperation<size_t> {OperationType::Insert, i};
            if (queue->push(op))
                std::cout << op.param << "\n";
            else
                std::cout << "Full\n";
        }
    };

    auto pop_work = [&] (size_t start, size_t stop) {
        size_t val;
        for (size_t i=start; i<stop; i++) {
            BBSTOperation<size_t> op{};
            if(queue->pop(op))
                std::cout << op.param << "\n";
            else
                std::cout << "Empty\n";
        }
    };

    std::vector<std::thread> threads;
    threads.reserve(2);
    threads.emplace_back(push_work, 1, 2<<10);
    threads.emplace_back(pop_work, 1, 2<<8);

    for (auto& thread: threads) {
        thread.join();
    }
}