#include <gtest/gtest.h>
#include <iostream>
#include <memory>
#include "../src/bbst/Tree.h"

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

    auto lowest = tree->lowest();
    EXPECT_EQ(lowest, start);

    auto highest = tree->highest();
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