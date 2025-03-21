#include <iostream>
#include "Tree.h"

/*
 * References:
 * https://en.wikipedia.org/wiki/AVL_tree
 * https://www.youtube.com/watch?v=PBkXmhiCP1M&ab_channel=MichaelSambol
 * */

using BBST::Node, BBST::Tree;

template<typename T>
Tree<T>::Tree() : _root(nullptr) {}

template<typename T>
Tree<T>::~Tree() {
    _root = _destructorHelper(_root);
}

template<typename T>
Node<T>* Tree<T>::_destructorHelper(Node<T>* node)
{
    if (node == nullptr)
        return nullptr;
    _destructorHelper(node->left);
    _destructorHelper(node->right);
    delete node;
    node = nullptr;
    return nullptr;
}

template<typename T>
void Tree<T>::search(const T& value) const {
    auto node = _find(value);
    if (node == nullptr) {
        std::cout << value << " is not found\n";
    } else {
        std::cout << value << " is found\n";
    }
}

template<typename T>
void Tree<T>::insert(const T& value) {
    std::lock_guard<std::mutex> guard(_mutex);
    _root = _insertHelper(_root, value);
}

template<typename T>
Node<T>* Tree<T>::_insertHelper(Node<T>* node, const T& value) {
    if (node == nullptr)
        return new Node<T>(value);
    if (value > node->value)
        node->right = _insertHelper(node->right, value);
    else if (value < node->value)
        node->left = _insertHelper(node->left, value);
    else
        return node;

    node->updateHeight();

    return _rebalance(node);
}

template<typename T>
Node<T>* Tree<T>::_rebalance(Node<T>* node) {
    int bf = _balanceFactor(node);

    if (std::abs(bf) <= 1)
        return node;

    // case: right heavy
    if (bf > 0) {
        int bf_right = _balanceFactor(node->right);
        if (bf_right < 0) {
            // right-left
            node->right = _rightRotate(node->right);
            node = _leftRotate(node);
            return node;
        }

        // right-right
        node = _leftRotate(node);
        return node;
    }

    // case: left heavy
    int bf_left = _balanceFactor(node->left);
    if (bf_left > 0) {
        // left-right
        node->left = _leftRotate(node->left);
        node = _rightRotate(node);
        return node;
    }

    // left-left
    node = _rightRotate(node);
    return node;
}


/* Right rotate
    N        L
   /          \
  L     =>     N
  \           /
  T2         T2
*/
template<typename T>
Node<T>* Tree<T>::_rightRotate(Node<T>* N) {
    auto L = N->left;
    auto T2 = L->right;

    L->right = N;
    N->left = T2;

    // Update heights
    N->updateHeight();
    L->updateHeight();

    return L;
};

/* Left rotate
    N          R
     \        /
      R  =>  N
     /        \
    T2        T2
*/
template<typename T>
Node<T>* Tree<T>::_leftRotate(Node<T>* N) {
    auto R = N->right;
    auto T2 = R->left;

    R->left = N;
    N->right = T2;

    // Update heights
    N->updateHeight();
    R->updateHeight();

    return R;

};

template<typename T>
void Tree<T>::remove(const T& value) {
    std::lock_guard<std::mutex> guard(_mutex);
    _root = _removeHelper(_root, value);
}

template<typename T>
Node<T>* Tree<T>::_removeHelper(Node<T>* N, const T& value) {
    if (N == nullptr)
        return nullptr;
    if (value > N->value) {
        N->right = _removeHelper(N->right, value);
    } else if (value < N->value) {
        N->left = _removeHelper(N->left, value);
    } else {
        // Found the N to remove
        if ((N->left == nullptr) && (N->right == nullptr)) {
            delete N;
            N = nullptr;
            return nullptr;
        }
        if (N->left == nullptr)
        {
            Node<T>* temp = N;
            N = N->right;
            delete temp;
            temp = nullptr;
        }
        else if (N->right == nullptr)
        {
            Node<T>* temp = N;
            N = N->left;
            delete temp;
            temp = nullptr;
        }
        else
        {
            // has two children
            // inorder successor (smallest in right subtree)
            Node<T>* temp = N->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }

            // Copy the inorder successor's
            // data to this node
            N->value = temp->value;

            // Delete the inorder successor
            N->right = _removeHelper(N->right, temp->value);
        }
    }

    N->updateHeight();

    return _rebalance(N);
}

template<typename T>
Node<T>* Tree<T>::_find(const T& value) const {
    auto current = _root;
    while (current != nullptr) {
        if (current->value == value) {
            return current;
        }
        if (value > current->value) {
            current = current->right;
        } else {
            current = current->left;
        }
    }
    return nullptr;
}
