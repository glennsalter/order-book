#include <gtest/gtest.h>
#include <iostream>

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}

TEST (SimpleTest, SimpleTest) {
    EXPECT_EQ(1, 2);
    std::cout << "1 != 2" << std::endl;
}