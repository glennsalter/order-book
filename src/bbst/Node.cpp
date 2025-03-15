#include "Node.h"
#include <memory>

BBST::Node::Node(int value) : value(value), height(1), left(nullptr), right(nullptr) {}

BBST::Node::~Node() = default;