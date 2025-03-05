#ifndef ORDERBOOK_NODE_H
#define ORDERBOOK_NODE_H

namespace BBST
{
    class Node {
    public:
        int value;
        int height;
        Node* parent;
        Node* left;
        Node* right;

        explicit Node(int value);
        ~Node();
    };
}


#endif //ORDERBOOK_NODE_H
