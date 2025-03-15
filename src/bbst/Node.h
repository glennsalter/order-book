#ifndef ORDERBOOK_NODE_H
#define ORDERBOOK_NODE_H

#include <algorithm>

namespace BBST
{
    template <typename T>
    class Node {
    public:
        T value;
        int height = 0;
        Node* left;
        Node* right;

        explicit Node(int value);
        ~Node();
        void constexpr updateHeight() {
            const int leftHeight = (left == nullptr) ? 0 : left->height;
            const int rightHeight = (right == nullptr) ? 0 : right->height;
            height = 1 + std::max(leftHeight, rightHeight);
        }
    };
}

template class BBST::Node<int>;

#endif //ORDERBOOK_NODE_H
