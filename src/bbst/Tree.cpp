#include <iostream>
#include "Tree.h"

/*
 * References:
 * https://en.wikipedia.org/wiki/AVL_tree
 * https://www.youtube.com/watch?v=PBkXmhiCP1M&ab_channel=MichaelSambol
 * */

using BBST::Node, BBST::Tree;

Tree::Tree() : root(nullptr) {}

Tree::~Tree() {
    // TODO: Traverse the tree and delete all nodes

}

void Tree::insert(int value) {
    root = insert_helper(root, value);
}

Node* Tree::insert_helper(Node* node, int value) {
    if (node == nullptr)
        return new Node(value);
    if (value > node->value)
        node->right = insert_helper(node->right, value);
    else
        node->left = insert_helper(node->left, value);

    return rebalance(node);
}

Node* Tree::rebalance(Node* node) {
    node->height = 1 + std::max(node->left ? node->left->height : 0,  node->right ? node->right->height : 0);
    int bf = balance_factor(node);

    if (std::abs(bf) <= 1)
        return node;

    // case: right heavy
    if (bf > 0) {
        int bf_right = balance_factor(node->right);
        if (bf_right < 0) {
            // right-left
            // node = rotate_right_left(node, node->right);
            node->right = rotate_right(node->right, node->right->left);
            node = rotate_left(node, node->right);
            return node;
        }

        // right-right
        node = rotate_left(node, node->right);
        return node;
    }

    // case: left heavy
    int bf_left = balance_factor(node->left);
    if (bf_left > 0) {
        // left-right
        // node = rotate_left_right(node->left, node);
        node->left = rotate_left(node->left, node->left->right);
        node = rotate_right(node->left, node);
        return node;
    }

    // left-left
    node = rotate_right(node->left, node);
    return node;
}

Node* Tree::rotate_left(Node* X, Node* Z) {
    auto t23 = Z->left;
    X->right = t23;
    if (t23 != nullptr) {
        t23->parent = X;
    }
    Z->left = X;
    X->parent = Z;

    // update heights
    X->height = 1 + std::max(X->left ? X->left->height : 0, X->right ? X->right->height : 0);
    Z->height = 1 + std::max(Z->left ? Z->left->height : 0, Z->right ? Z->right->height : 0);

    return Z;
}

Node* Tree::rotate_right(Node* Z, Node* X) {
    auto t23 = X->right;
    Z->left = t23;
    if (t23 != nullptr) {
        t23->parent = Z;
    }
    X->right = Z;
    Z->parent = X;

    // update heights
    Z->height = 1 + std::max(Z->left ? Z->left->height : 0, Z->right ? Z->right->height : 0);
    X->height = 1 + std::max(X->left ? X->left->height : 0, X->right ? X->right->height : 0);

    return X;
}

Node* Tree::rotate_left_right(Node* Z, Node* X) {
    auto Y = X->right;
    auto t2 = Y->left;
    X->right = t2;
    if (t2 != nullptr) {
        t2->parent = X;
    }
    Y->left = X;
    X->parent = Y;
    auto t3 = Y->right;
    Z->left = t3;
    if (t3 != nullptr) {
        t3->parent = Z;
    }
    Y->right = Z;
    Z->parent = Y;

    // update heights
    X->height = 1 + std::max(X->left ? X->left->height : 0, X->right ? X->right->height : 0);
    Z->height = 1 + std::max(Z->left ? Z->left->height : 0, Z->right ? Z->right->height : 0);
    Y->height = 1 + std::max(Y->left ? Y->left->height : 0, Y->right ? Y->right->height : 0);

    return Y;
}

Node* Tree::rotate_right_left(Node* X, Node*Z) {
    auto Y = Z->left;
    auto t3 = Y->right;
    Z->left = t3;
    if (t3 != nullptr) {
        t3->parent = Z;
    }
    Y->right = Z;
    Z->parent = Y;
    auto t2 = Y->left;
    X->right = t2;
    if (t2 != nullptr) {
        t2->parent = X;
    }
    Y->left = X;
    X->parent = Y;

    // update heights
    X->height = 1 + std::max(X->left ? X->left->height : 0, X->right ? X->right->height : 0);
    Z->height = 1 + std::max(Z->left ? Z->left->height : 0, Z->right ? Z->right->height : 0);
    Y->height = 1 + std::max(Y->left ? Y->left->height : 0, Y->right ? Y->right->height : 0);

    return Y;
}

void Tree::remove(int value) {
    root = remove_helper(root, value);
}

Node* Tree::remove_helper(Node* Z, int value) {
    if (Z == nullptr)
        return nullptr;
    if (value > Z->value)
    {
        Z->right = remove_helper(Z->right, value);
    }
    else if (value < Z->value)
    {
        Z->left = remove_helper(Z->left, value);
    }
    else
    {
        // Found the node to remove
        if (Z->left == nullptr && Z->right == nullptr) {
            delete Z;
            return nullptr;
        }

        if (Z->left == nullptr) {
            auto R = Z->right;
            delete Z;
            return R;
        }

        if (Z->right == nullptr) {
            auto L = Z->left;
            delete Z;
            return L;
        }

        // Node has two children
        // Find in-order successor
        auto min = Z->right;
        while (min->left != nullptr) {
            min = min->left;
        }
        Z->value = min->value;
        Z->right = remove_helper(Z->right, min->value);
    }

    Z->height = 1 + std::max(Z->left ? Z->left->height : 0, Z->right ? Z->right->height : 0);
    return rebalance(Z);

}

bool Tree::search(int value) {
    auto current = root;
    while (current != nullptr) {
        if (current->value == value) {
            std::cout << "Found " << value << "\n";
            return true;
        }
        if (value > current->value) {
            current = current->right;
        } else {
            current = current->left;
        }
    }
    std::cout << "Missing " << value << "\n";
    return false;
}

void Tree::print() {
    print_helper(root);
}

void Tree::print_helper(Node* node) {
    if (node == nullptr)
        return;

    print_helper(node->left);
    std::cout << node->value << " ";
    print_helper(node->right);
}