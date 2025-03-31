//
// Created by gsalter on 3/15/2025.
//

#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include "SPSCQueue.h"
#include "../bbst/Tree.h"
#include "../bbst/Node.h"

#include <memory>
#include <cstddef>


using BBST::Tree, BBST::Node;

namespace OrderBook {
    class OrderBook {
    public:
        OrderBook();
        ~OrderBook() = default;

        bool lowest(size_t& val);
        bool highest(size_t& val);
        bool produceOperation(BBSTOperation<size_t>& op);
        bool consumeOperation();
    private:
        bool process(const BBSTOperation<size_t>& op);

        std::unique_ptr<Tree<size_t>> _readCopy;
        std::unique_ptr<Tree<size_t>> _writeCopy;
        std::unique_ptr<SPSCQueue<BBSTOperation<size_t>>> _operationQueue;
        // TODO: Implement sync
    };
}


#endif //ORDERBOOK_H
