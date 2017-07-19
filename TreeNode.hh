#pragma once

#include <cstdint>
#include "BinarySearchTree.hh"

#define PGSIZE 4096
// TODO: set capacity
#define CAPACITY 10
// TODO: max depth for BST

class TreeNode {
public:
    struct Data {
        int64_t key;
        void* ptr;
        bool valid;
    };
private:
    BinarySearchTree *bst;
    void *parent;
    Data data[CAPACITY];
    void *next;
    int16_t level;
    int16_t size; // valid size
    int16_t tsize; // total size
public:
    TreeNode();
    TreeNode(void *parent, void *next);
    void copyData(Data &*tocopy, int16_t from, int16_t to);
    void insert(int64_t key, void *ptr);
    void remove(int64_t key);
    void setNext(void *next);
    void replaceFirst(int64_t key, int64_t new_key, void *ptr);
    void *getPtr(int64_t key);
    void *getNext();
    void *getParent();
    void *getNeighbor(int64_t key);
    void *getPrev(int64_t key);
    void *getNext(int64_t key);
    void *first();
    void *last();
    Data getData(int16_t idx);
    int64_t getKey();
    int16_t getSize();
    int16_t getTotalSize();
    int16_t getLevel();
    bool isLeaf();
    bool isFull();
    void defragmentation();
};
