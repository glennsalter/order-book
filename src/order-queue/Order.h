#ifndef ORDERBOOK_ORDER_H
#define ORDERBOOK_ORDER_H

namespace OrderQueue {
    class Order {
    public:
        int price;
        int quantity;

        Order(int price, int quantity);
    };
}


#endif //ORDERBOOK_ORDER_H
