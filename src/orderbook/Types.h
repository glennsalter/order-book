//
// Created by gsalter on 3/31/2025.
//

#ifndef TYPES_H
#define TYPES_H

namespace OrderBook {
    enum class OperationType : unsigned
    {
        Insert=11,
        Remove=12,
        Lowest=13,
        Highest=14,
    };

    template<typename T>
    struct BBSTOperation {
        OperationType operationType;
        T param;
    };
    template struct BBSTOperation<size_t>;
}

#endif //TYPES_H
