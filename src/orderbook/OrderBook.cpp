//
// Created by gsalter on 3/15/2025.
//

#include "OrderBook.h"

namespace OrderBook {
    OrderBook::OrderBook() :
    _readCopy(std::make_unique<Tree<size_t>>()),
    _writeCopy(std::make_unique<Tree<size_t>>()),
    _operationQueue(std::make_unique<SPSCQueue<BBSTOperation<size_t>>>(2<<10))
    {}

    bool OrderBook::lowest(size_t& val) {
        return _readCopy->lowest(val);
    }

    bool OrderBook::highest(size_t& val) {
        return _readCopy->highest(val);
    }

    bool OrderBook::produceOperation(BBSTOperation<size_t>& op) {
        return _operationQueue->push(op);
    };

    bool OrderBook::consumeOperation() {
        BBSTOperation<size_t> op{};
        if (!_operationQueue->pop(op)) {
            return false;
        }

        // TODO: sync should be called after process
        // We shall have multiple instances of readCopy, perhaps a ring buffer of readCopy
        // Each time a read request comes, it reads from the latest instance that is not locked
        // When we want to sync, we lock one of the instance and update


        return process(op);
    };

    bool OrderBook::process(const BBSTOperation<size_t>& op) {
        if (op.operationType == OperationType::Insert) {
            _writeCopy->insert(op.param);
            return true;
        }
        if (op.operationType == OperationType::Remove) {
            _writeCopy->remove(op.param);
            return true;
        }
        return false;
    }


}