#pragma once

#include <cstdint>

#define BST_CAPACITY 10

class BinarySearchTree {
    struct Node{
        int64_t key;
        Node *parent;
        Node *left;
        Node *right;
    };
    struct LeafNode : Node {
        int16_t idx;
    };

    Node *root;
    int16_t size;
public:
    BinarySearchTree();
    int16_t search(int64_t key);
    void insert(int64_t key, int16_t idx);
    void remove(int64_t key);
    void create(int64_t keys, int16_t idxs);
};
