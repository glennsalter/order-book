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
    root = destructor_helper(root);
}

Node* Tree::destructor_helper(Node* node)
{
    if (node == nullptr)
        return nullptr;
    node->left = destructor_helper(node->left);
    node->right = destructor_helper(node->right);
    delete node;
    return nullptr;
}

void Tree::search(int value) const {
    auto node = find(value);
    if (node == nullptr) {
        std::cout << value << " is not found\n";
    } else {
        std::cout << value << " is found\n";
    }
}

void Tree::insert(int value) {
    std::lock_guard<std::mutex> guard(mutex);
    root = insert_helper(root, value);
}

Node* Tree::insert_helper(Node* node, int value) {
    if (node == nullptr)
        return new Node(value);
    if (value > node->value)
        node->right = insert_helper(node->right, value);
    else if (value < node->value)
        node->left = insert_helper(node->left, value);
    else
        return node;

    node->update_height();

    return rebalance(node);
}

Node* Tree::rebalance(Node* node) {
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
Node* Tree::right_rotate(Node* N) {
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
Node* Tree::left_rotate(Node* N) {
    auto R = N->right;
    auto T2 = R->left;

    R->left = N;
    N->right = T2;

    // Update heights
    N->update_height();
    R->update_height();

    return R;

};

void Tree::remove(int value) {
    std::lock_guard<std::mutex> guard(mutex);
    root = remove_helper(root, value);
}

Node* Tree::remove_helper(Node* N, int value) {
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
            return nullptr;
        }
        if (N->left == nullptr)
        {
            Node* temp = N;
            N = N->right;
            delete temp;
        }
        else if (N->right == nullptr)
        {
            Node* temp = N;
            N = N->left;
            delete temp;
        }
        else
        {
            // has two children
            // inorder successor (smallest in right subtree)
            Node* temp = N->right;
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

Node* Tree::find(int value) const {
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

void Tree::print(const std::string& order) const {
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

void Tree::in_order_output(const Node* node) {
    if (node == nullptr)
        return;
    in_order_output(node->left);
    std::cout << node->value << " ";
    in_order_output(node->right);
}

void Tree::pre_order_output(const Node* node) {
    if (node == nullptr)
        return;
    std::cout << node->value << " ";
    pre_order_output(node->left);
    pre_order_output(node->right);
}

void Tree::post_order_output(const Node* node) {
    if (node == nullptr)
        return;
    post_order_output(node->left);
    post_order_output(node->right);
    std::cout << node->value << " ";
}