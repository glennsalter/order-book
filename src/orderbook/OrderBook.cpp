//
// Created by gsalter on 3/15/2025.
//

#include "OrderBook.h"

namespace OrderBook {
    OrderBook::OrderBook() : readCopy(Tree<int>()), writeCopy(Tree<int>()) {}
}