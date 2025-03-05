#ifndef ORDERBOOK_TREE_H
#define ORDERBOOK_TREE_H

#include "Node.h"

namespace BBST {
    class Tree {
    public:
        Node* root;
        Tree();
        ~Tree();
        void insert(int value);
        void remove(int value);
        void search(int value);
        void print();
    private:
        Node* find(int value);
        Node* insert_helper(Node* node, int value);
        static inline int balance_factor(Node* node) {
            auto left_height = node->left ? node->left->height : 0;
            auto right_height = node->right ? node->right->height : 0;
            return right_height - left_height;
        }
        static Node* rotate_left(Node* X, Node* Z);
        static Node* rotate_right(Node* Z, Node* X);
        static Node* rotate_left_right(Node* Z, Node*X);
        static Node* rotate_right_left(Node* X, Node*Z);
        static Node* remove_helper(Node* Z, int value);
        static Node* rebalance(Node* node);
        void print_helper(Node* node);
        static Node* destructor_helper(Node* node);
    };
}

#endif //ORDERBOOK_TREE_H
