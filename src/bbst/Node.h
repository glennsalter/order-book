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
        void constexpr update_height() {
            const int left_height = (left == nullptr) ? 0 : left->height;
            const int right_height = (right == nullptr) ? 0 : right->height;
            height = 1 + std::max(left_height, right_height);
        }
    };
}

template class BBST::Node<int>;

#endif //ORDERBOOK_NODE_H
