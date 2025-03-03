#include <iostream>
#include "bbst/Tree.h"
#include "order-queue/Order.h"

int main() {
    BBST::Tree tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);

    OrderQueue::Order order(100, 10);

    std::cout << "Order: " << order.price << "@" << order.quantity << "\n";

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
