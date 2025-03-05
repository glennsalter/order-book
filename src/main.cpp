#include <iostream>
#include <memory>
#include "bbst/Tree.h"

using std::make_unique;

int main() {
    auto tree = make_unique<BBST::Tree>();
    tree->insert(4);
    tree->insert(2);
    tree->insert(6);
    tree->insert(1);
    tree->insert(3);
    tree->insert(5);
    tree->insert(7);
    tree->print();
    std::cout << "\n";

    tree->remove(4);
    tree->print();
    std::cout << "\n";

    tree->remove(7);
    tree->print();
    std::cout << "\n";

    return 0;
}
