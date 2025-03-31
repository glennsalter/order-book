#ifndef ORDERBOOK_NODE_H
#define ORDERBOOK_NODE_H

#include <algorithm>
#include <cstddef>

namespace BBST
{
    template <typename T>
    class Node {
    public:
        T value;
        size_t height = 0;
        Node* left;
        Node* right;

        explicit Node(T value);
        ~Node();
        void constexpr updateHeight() {
            const size_t leftHeight = (left == nullptr) ? 0 : left->height;
            const size_t rightHeight = (right == nullptr) ? 0 : right->height;
            height = 1 + std::max(leftHeight, rightHeight);
        }
    };
}

template class BBST::Node<size_t>;

#endif //ORDERBOOK_NODE_H
