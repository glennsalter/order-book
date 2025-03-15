#include "Node.h"
#include <algorithm>

using namespace BBST;

template<typename T>
Node<T>::Node(int value) : value(value), height(1), left(nullptr), right(nullptr) {}

template<typename T>
Node<T>::~Node() = default;

template<typename T>
void Node<T>::update_height() {
    const int left_height = (left == nullptr) ? 0 : left->height;
    const int right_height = (right == nullptr) ? 0 : right->height;
    height = 1 + std::max(left_height, right_height);
}
