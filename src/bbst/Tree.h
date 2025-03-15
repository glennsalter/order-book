#ifndef ORDERBOOK_TREE_H
#define ORDERBOOK_TREE_H

#include "Node.h"
#include <mutex>

namespace BBST {
    class Tree {
    public:
        Node* root;
        Tree();
        ~Tree();
        Tree(const Tree& other);
        void insert(int value);
        void remove(int value);
        void search(int value) const;
        void print(const std::string& order) const;
    private:
        std::mutex mutex;
        Node* find(int value) const;

        static Node* insert_helper(Node* node, int value);
        static inline int balance_factor(Node* node) {
            auto left_height = node->left ? node->left->height : 0;
            auto right_height = node->right ? node->right->height : 0;
            return right_height - left_height;
        }
        static Node* right_rotate(Node* N);
        static Node* left_rotate(Node* N);
        static Node* remove_helper(Node* N, int value);
        static Node* rebalance(Node* node);
        static void in_order_output(const Node* node);
        static void pre_order_output(const Node* node);
        static void post_order_output(const Node* node);
        static Node* destructor_helper(Node* node);
    };
}

#endif //ORDERBOOK_TREE_H
