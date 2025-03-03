#ifndef ORDERBOOK_TREE_H
#define ORDERBOOK_TREE_H

#include "Node.h"

namespace BBST {
    class Tree {
    public:
        Node* root;

        Tree();
        void insert(int value);
        // Add other tree-related methods here
    };
}

#endif //ORDERBOOK_TREE_H
