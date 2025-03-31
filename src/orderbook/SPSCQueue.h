//
// Created by gsalter on 3/31/2025.
//

#ifndef SPSCQUEUE_H
#define SPSCQUEUE_H

#include <atomic>
#include <cstddef>
#include <vector>

#include "Types.h"

namespace OrderBook {
    template <typename T>
    class SPSCQueue {
    public:
        SPSCQueue(size_t capacity);
        bool push(const T& item);
        bool pop(T& item);

    private:
        inline size_t increment(size_t pos) const {
            return (pos + 1) % static_cast<size_t>(mBuffer.size());
        }
        alignas(64) std::atomic<size_t> mReadPos;
        alignas(64) std::atomic<size_t> mWritePos;
        std::vector<T> mBuffer;
    };

    template class SPSCQueue<size_t>;
    template class SPSCQueue<BBSTOperation<size_t>>;
}


#endif //SPSCQUEUE_H
