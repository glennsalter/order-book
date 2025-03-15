#ifndef ORDERBOOK_NODE_H
#define ORDERBOOK_NODE_H

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
        void update_height();
    };
}

template class BBST::Node<int>;

#endif //ORDERBOOK_NODE_H
