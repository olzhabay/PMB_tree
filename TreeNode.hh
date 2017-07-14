#pragma once

#include <cstdint>
#include "BinarySearchTree.hh"

#define PGSIZE 4096
// TODO: set capacity
#define CAPACITY 10
// TODO: max depth for BST

class TreeNode {
    BinarySearchTree bst;
    void *parent;
    int16_t level;
    int16_t size;
    int16_t tsize;
    int64_t key[CAPACITY];
    void *ptr[CAPACITY];
    void *next;
public:
    TreeNode();
    TreeNode(void *parent, void *next);
    void insert(int64_t key, void *ptr);
    void remove(int64_t key);
    void *getPtr(int64_t key);
    void *getNext();
    int16_t getSize();
    int16_t getLevel();
};
