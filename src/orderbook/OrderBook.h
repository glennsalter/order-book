//
// Created by gsalter on 3/15/2025.
//

#ifndef ORDERBOOK_H
#define ORDERBOOK_H
#include "../bbst/Tree.h"
#include "../bbst/Node.h"

using BBST::Tree, BBST::Node;

namespace OrderBook {
    class OrderBook {
    public:
        Tree<int> readCopy;
        Tree<int> writeCopy;
        OrderBook();
        ~OrderBook() = default;
    private:
        // TODO: add member writeOperationsQueue
        // TODO: add method sync readCopy by popping from Write
    };
}


#endif //ORDERBOOK_H
