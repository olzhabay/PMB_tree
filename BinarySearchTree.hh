#pragma once

#include <cstdint>
#include "TreeNode.hh"

#define BST_CAPACITY 10

class BinarySearchTree {
    // TODO: change
public:
    struct Node{
        int64_t key;
        Node *parent;
        Node *left;
        Node *right;
        int16_t idx;
    };

private:
    Node *root;
public:
    BinarySearchTree();
    int16_t search(int64_t key);
    void insert(int64_t key, int16_t idx);
    int16_t remove(int64_t key);
    void create(TreeNode::Data &data[], int16_t size);
    void create(Node *node, TreeNode::Data &data[], int16_t from, int16_t to);
    int16_t getNeighbor(int64_t key);
    int16_t getSmallest();
    int16_t getBiggest();
    int16_t getNext(int64_t key);
    int16_t getPrev(int64_t key);
    Node *searchLeaf(int64_t key);
};
