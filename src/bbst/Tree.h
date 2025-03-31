#ifndef ORDERBOOK_TREE_H
#define ORDERBOOK_TREE_H

#include "Node.h"
#include <iostream>
#include <mutex>
#include <cstddef>

namespace BBST {
    template<typename T>
    class Tree {
    public:
        Tree();
        ~Tree();
        Tree(const Tree& other);
        void insert(const T& val);
        void remove(const T& val);
        bool search(const T& val) const;
        bool lowest(T& val);
        bool highest(T& val);
        void print(std::string order) {
            if (order == "inorder")
                _inOrderOutput(_root);
            else if (order == "preorder")
                _preOrderOutput(_root);
            else if (order == "postorder")
                _postOrderOutput(_root);
            else
                std::cout << "Invalid order";
            std::cout << "\n";
        };
        constexpr size_t height() {
            return _root->height;
        }
    private:
        Node<T>* _root;
        std::mutex _mutex;
        Node<T>* _find(const T& value) const;
        static Node<T>* _insertHelper(Node<T>* node, const T& value);
        static int _balanceFactor(Node<T>* node) {
            auto leftHeight = node->left ? node->left->height : 0;
            auto rightHeight = node->right ? node->right->height : 0;
            return rightHeight - leftHeight;
        }
        static Node<T>* _rightRotate(Node<T>* N);
        static Node<T>* _leftRotate(Node<T>* N);
        static Node<T>* _removeHelper(Node<T>* N,const T& value);
        static Node<T>* _rebalance(Node<T>* node);
        static void _inOrderOutput(const Node<T>* node);
        static void _preOrderOutput(const Node<T>* node);
        static void _postOrderOutput(const Node<T>*node);
        static Node<T>* _destructorHelper(Node<T>* node);
    };
}


template class BBST::Tree<size_t>;
#endif //ORDERBOOK_TREE_H
