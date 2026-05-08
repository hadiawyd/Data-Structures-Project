#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>
using namespace std;

// A BST keeps data sorted automatically as we insert things.
// Left child is always smaller, right child is always bigger.
// That makes searching really fast -- O(log n) on average

struct BSTNode {
    int data;
    BSTNode* left;   // smaller values go here
    BSTNode* right;  // bigger values go here

    BSTNode(int val) {
        data  = val;
        left  = nullptr;
        right = nullptr;
    }
};

class BinarySearchTree {
private:
    BSTNode* root;  // the very top of our tree

    // Helper -- does the actual recursive inserting
    // I like breaking things into a public function + private helper
    BSTNode* insertHelper(BSTNode* node, int value) {
        if (node == nullptr) {
            // We found an empty spot -- put the new node here
            return new BSTNode(value);
        }

        if (value < node->data) {
            // Go left because value is smaller
            node->left = insertHelper(node->left, value);
        } else if (value > node->data) {
            // Go right because value is bigger
            node->right = insertHelper(node->right, value);
        }
        // If value == node->data we just skip it (no duplicates)

        return node;
    }

    // Helper -- search recursively
    bool searchHelper(BSTNode* node, int value) {
        if (node == nullptr)
            return false;  // ran out of tree, it's not here

        if (value == node->data)
            return true;   // found it!

        if (value < node->data)
            return searchHelper(node->left, value);   // look left
        else
            return searchHelper(node->right, value);  // look right
    }

    // Find the smallest node in a subtree (needed for delete)
    BSTNode* findMin(BSTNode* node) {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

    // Helper -- remove a node and keep the BST valid
    BSTNode* removeHelper(BSTNode* node, int value) {
        if (node == nullptr) {
            cout << "Value " << value << " not found in tree.\n";
            return nullptr;
        }

        if (value < node->data) {
            node->left = removeHelper(node->left, value);
        } else if (value > node->data) {
            node->right = removeHelper(node->right, value);
        } else {
            // Found the node to delete -- three cases:

            // Case 1: no children (leaf node) -- just delete it
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }

            // Case 2: one child -- replace node with its child
            if (node->left == nullptr) {
                BSTNode* temp = node->right;
                delete node;
                return temp;
            }
            if (node->right == nullptr) {
                BSTNode* temp = node->left;
                delete node;
                return temp;
            }

            // Case 3: two children -- find the in-order successor
            // (smallest value in the right subtree) and copy it here
            BSTNode* successor = findMin(node->right);
            node->data = successor->data;
            // Now delete the successor from the right subtree
            node->right = removeHelper(node->right, successor->data);
        }

        return node;
    }

    // In-order traversal: left -> root -> right
    // This prints values in sorted order -- pretty cool!
    void inOrderHelper(BSTNode* node) {
        if (node == nullptr) return;
        inOrderHelper(node->left);
        cout << node->data << " ";
        inOrderHelper(node->right);
    }

    // Pre-order: root -> left -> right
    void preOrderHelper(BSTNode* node) {
        if (node == nullptr) return;
        cout << node->data << " ";
        preOrderHelper(node->left);
        preOrderHelper(node->right);
    }

    // Post-order: left -> right -> root
    void postOrderHelper(BSTNode* node) {
        if (node == nullptr) return;
        postOrderHelper(node->left);
        postOrderHelper(node->right);
        cout << node->data << " ";
    }

    // Clean up all nodes when the tree is destroyed
    void destroyHelper(BSTNode* node) {
        if (node == nullptr) return;
        destroyHelper(node->left);
        destroyHelper(node->right);
        delete node;
    }

public:
    BinarySearchTree() {
        root = nullptr;  // empty tree at the start
    }

    void insert(int value) {
        root = insertHelper(root, value);
        cout << "Inserted: " << value << "\n";
    }

    bool search(int value) {
        return searchHelper(root, value);
    }

    void remove(int value) {
        root = removeHelper(root, value);
    }

    // Print sorted (in-order is always sorted in a BST!)
    void printInOrder() {
        cout << "In-Order (sorted):  ";
        inOrderHelper(root);
        cout << "\n";
    }

    void printPreOrder() {
        cout << "Pre-Order:          ";
        preOrderHelper(root);
        cout << "\n";
    }

    void printPostOrder() {
        cout << "Post-Order:         ";
        postOrderHelper(root);
        cout << "\n";
    }

    // Destructor -- free all nodes in the tree
    ~BinarySearchTree() {
        destroyHelper(root);
    }
};

#endif