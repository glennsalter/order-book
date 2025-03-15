#ifndef ORDERBOOK_NODE_H
#define ORDERBOOK_NODE_H

namespace BBST
{
    class Node {
    public:
        int value;
        int height;
        Node* left;
        Node* right;

        explicit Node(int value);
        ~Node();
        void update_height();
    };
}


#endif //ORDERBOOK_NODE_H
