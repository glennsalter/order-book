#include <iostream>
#include <memory>
#include "bbst/Tree.h"

using std::make_unique;

int main() {
    auto tree = new BBST::Tree();
    tree->insert(4);
    tree->insert(2);
    tree->insert(6);
    tree->insert(1);
    tree->insert(3);
    tree->insert(5);
    tree->insert(7);
    tree->print();

    tree->remove(4);
    tree->print();

    tree->remove(7);
    tree->print();

    tree->search(4);
    tree->search(6);

    delete tree;

    return 0;
}
