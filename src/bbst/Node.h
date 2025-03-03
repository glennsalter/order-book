#ifndef ORDERBOOK_NODE_H
#define ORDERBOOK_NODE_H

namespace BBST
{
    class Node {
    public:
        int data;
        Node* left;
        Node* right;

        Node(int value);
    };
}


#endif //ORDERBOOK_NODE_H
