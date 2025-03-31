#ifndef ORDERBOOK_ORDER_H
#define ORDERBOOK_ORDER_H
#include <cstddef>

namespace OrderQueue {
    class Order {
    public:
        size_t price;
        size_t quantity;

        Order(size_t price, size_t quantity);
    };
}


#endif //ORDERBOOK_ORDER_H
