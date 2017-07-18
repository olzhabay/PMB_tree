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
    int64_t key[CAPACITY];
    void *ptr[CAPACITY];
    void *next;
    int16_t level;
    int16_t size;
    int16_t tsize;
public:
    TreeNode();
    TreeNode(void *parent, void *next);
    void insert(int64_t key, void *ptr);
    void remove(int64_t key);
    void *getPtr(int64_t key);
    void *getNext();
    void *getParent();
    void *getNext(int64_t key);
    void *getPrev(int64_t key);
    int64_t getKey();
    int16_t getSize();
    int16_t getLevel();
    bool isLeaf();
    bool isFull();
};
