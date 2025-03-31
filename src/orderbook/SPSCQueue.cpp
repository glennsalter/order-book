//
// Created by gsalter on 3/31/2025.
//

#include "SPSCQueue.h"

#include <atomic>
#include <assert.h>

using namespace OrderBook;

template<typename T>
SPSCQueue<T>::SPSCQueue(size_t capacity) : mBuffer(capacity+1), mReadPos(0), mWritePos(0) {
    assert(capacity > 0);
    assert(capacity + 1 > 0);
}

template<typename T>
bool SPSCQueue<T>::push(const T& item) {
    const size_t r = mReadPos.load(std::memory_order_acquire);
    const size_t w = mWritePos.load(std::memory_order_relaxed);

    // check if full
    const size_t next_w = increment(w);
    if (r==next_w) return false;

    mBuffer[w] = item;
    mWritePos.store(next_w, std::memory_order_release);
    return true;
}

template<typename T>
bool SPSCQueue<T>::pop(T& item) {
    int r = mReadPos.load(std::memory_order_relaxed);
    int w = mWritePos.load(std::memory_order_acquire);

    // check if empty
    if (r==w) return false;

    item = mBuffer[r];
    mReadPos.store(increment(r), std::memory_order_release);
    return true;
}

