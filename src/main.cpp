#include "bbst/Tree.h"
#include "orderbook/OrderBook.h"
#include "orderbook/SPSCQueue.h"

#include <iostream>
#include <thread>
#include <cassert>
#include <vector>
#include <memory>
#include <format>

int main() {
    auto orderBook = std::make_unique<OrderBook::OrderBook>();

    auto op = OrderBook::BBSTOperation<size_t>{OrderBook::OperationType::Insert, 1};
    orderBook->produceOperation(op);

    // TODO: Sync read copy with write copy

    // size_t val;
    // orderBook->lowest(val);

    return 0;
}
