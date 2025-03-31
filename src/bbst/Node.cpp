#include "Node.h"
#include <algorithm>

using namespace BBST;

template<typename T>
Node<T>::Node(T value) : value(value), height(1), left(nullptr), right(nullptr) {}

template<typename T>
Node<T>::~Node() = default;
