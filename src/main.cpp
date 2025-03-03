#include <iostream>
#include "bbst/Tree.h"


int main() {
    BBST::Tree tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
