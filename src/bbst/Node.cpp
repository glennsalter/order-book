#include "Node.h"
#include <algorithm>

BBST::Node::Node(int value) : value(value), height(1), left(nullptr), right(nullptr) {}

BBST::Node::~Node() = default;

void BBST::Node::update_height() {
    const int left_height = (left == nullptr) ? 0 : left->height;
    const int right_height = (right == nullptr) ? 0 : right->height;
    height = 1 + std::max(left_height, right_height);
}
