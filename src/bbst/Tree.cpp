#include <iostream>
#include "Tree.h"

/*
 * References:
 * https://en.wikipedia.org/wiki/AVL_tree
 * https://www.youtube.com/watch?v=PBkXmhiCP1M&ab_channel=MichaelSambol
 * */

using BBST::Node, BBST::Tree;

template<typename T>
Tree<T>::Tree() : root(nullptr) {}

template<typename T>
Tree<T>::~Tree() {
    root = destructor_helper(root);
}

template<typename T>
Node<T>* Tree<T>::destructor_helper(Node<T>* node)
{
    if (node == nullptr)
        return nullptr;
    destructor_helper(node->left);
    destructor_helper(node->right);
    delete node;
    node = nullptr;
    return nullptr;
}

template<typename T>
void Tree<T>::search(const T& value) const {
    auto node = find(value);
    if (node == nullptr) {
        std::cout << value << " is not found\n";
    } else {
        std::cout << value << " is found\n";
    }
}

template<typename T>
void Tree<T>::insert(const T& value) {
    std::lock_guard<std::mutex> guard(mutex);
    root = insert_helper(root, value);
}

template<typename T>
Node<T>* Tree<T>::insert_helper(Node<T>* node, const T& value) {
    if (node == nullptr)
        return new Node<T>(value);
    if (value > node->value)
        node->right = insert_helper(node->right, value);
    else if (value < node->value)
        node->left = insert_helper(node->left, value);
    else
        return node;

    node->update_height();

    return rebalance(node);
}

template<typename T>
Node<T>* Tree<T>::rebalance(Node<T>* node) {
    int bf = balance_factor(node);

    if (std::abs(bf) <= 1)
        return node;

    // case: right heavy
    if (bf > 0) {
        int bf_right = balance_factor(node->right);
        if (bf_right < 0) {
            // right-left
            node->right = right_rotate(node->right);
            node = left_rotate(node);
            return node;
        }

        // right-right
        node = left_rotate(node);
        return node;
    }

    // case: left heavy
    int bf_left = balance_factor(node->left);
    if (bf_left > 0) {
        // left-right
        node->left = left_rotate(node->left);
        node = right_rotate(node);
        return node;
    }

    // left-left
    node = right_rotate(node);
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
Node<T>* Tree<T>::right_rotate(Node<T>* N) {
    auto L = N->left;
    auto T2 = L->right;

    L->right = N;
    N->left = T2;

    // Update heights
    N->update_height();
    L->update_height();

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
Node<T>* Tree<T>::left_rotate(Node<T>* N) {
    auto R = N->right;
    auto T2 = R->left;

    R->left = N;
    N->right = T2;

    // Update heights
    N->update_height();
    R->update_height();

    return R;

};

template<typename T>
void Tree<T>::remove(const T& value) {
    std::lock_guard<std::mutex> guard(mutex);
    root = remove_helper(root, value);
}

template<typename T>
Node<T>* Tree<T>::remove_helper(Node<T>* N, const T& value) {
    if (N == nullptr)
        return nullptr;
    if (value > N->value) {
        N->right = remove_helper(N->right, value);
    } else if (value < N->value) {
        N->left = remove_helper(N->left, value);
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
            N->right = remove_helper(N->right, temp->value);
        }
    }

    N->update_height();

    return rebalance(N);
}

template<typename T>
Node<T>* Tree<T>::find(const T& value) const {
    auto current = root;
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

template<typename T>
void Tree<T>::print(const std::string& order) const {
    if (order == "inorder") {
        in_order_output(root);
    }
    else if (order == "preorder") {
        pre_order_output(root);
    }
    else if (order == "postorder") {
        post_order_output(root);
    }
    else {
        std::cout << "Invalid order\n";
    }
    std::cout << "\n";
}

template<typename T>
void Tree<T>::in_order_output(const Node<T>* node) {
    if (node == nullptr)
        return;
    in_order_output(node->left);
    std::cout << node->value << " ";
    in_order_output(node->right);
}

template<typename T>
void Tree<T>::pre_order_output(const Node<T>* node) {
    if (node == nullptr)
        return;
    std::cout << node->value << " ";
    pre_order_output(node->left);
    pre_order_output(node->right);
}

template<typename T>
void Tree<T>::post_order_output(const Node<T>* node) {
    if (node == nullptr)
        return;
    post_order_output(node->left);
    post_order_output(node->right);
    std::cout << node->value << " ";
}