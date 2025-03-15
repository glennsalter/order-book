#ifndef ORDERBOOK_TREE_H
#define ORDERBOOK_TREE_H

#include "Node.h"
#include <mutex>

namespace BBST {
    template<typename T>
    class Tree {
    public:
        Node<T>* root;
        Tree();
        ~Tree();
        Tree(const Tree& other);
        void insert(const T& value);
        void remove(const T& value);
        void search(const T& value) const;
        void print(const std::string& order) {
            if (order == "inorder")
                in_order_output(root);
            else if (order == "preorder")
                pre_order_output(root);
            else if (order == "postorder")
                post_order_output(root);
            else
                std::cout << "Invalid order";
            std::cout << "\n";
        };
    private:
        std::mutex mutex;
        Node<T>* find(const T& value) const;

        static Node<T>* insert_helper(Node<T>* node, const T& value);
        static int balance_factor(Node<T>* node) {
            auto left_height = node->left ? node->left->height : 0;
            auto right_height = node->right ? node->right->height : 0;
            return right_height - left_height;
        }
        static Node<T>* right_rotate(Node<T>* N);
        static Node<T>* left_rotate(Node<T>* N);
        static Node<T>* remove_helper(Node<T>* N,const T& value);
        static Node<T>* rebalance(Node<T>* node);
        static void in_order_output(const Node<T>* const node) {
            if (node == nullptr)
                return;
            in_order_output(node->left);
            std::cout << node->value << " ";
            in_order_output(node->right);
        }
        static void pre_order_output(const Node<T>* const node) {
            if (node == nullptr)
                return;
            std::cout << node->value << " ";
            pre_order_output(node->left);
            pre_order_output(node->right);
        }
        static void post_order_output(const Node<T>* const node) {
            if (node == nullptr)
                return;
            post_order_output(node->left);
            post_order_output(node->right);
            std::cout << node->value << " ";
        }
        static Node<T>* destructor_helper(Node<T>* node);
    };
}


template class BBST::Tree<int>;
#endif //ORDERBOOK_TREE_H
