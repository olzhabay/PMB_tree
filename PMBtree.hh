#pragma once

#include <cstdint>
#include "TreeNode.hh"

#define THRESHOLD CAPACITY/2+CAPACITY%2

class PMBtree {
private:
    TreeNode *root;
    void *searchLeaf(int64_t key);
    void split(TreeNode *node);
    void merge(TreeNode *node, TreeNode *neighbor);
    void redistribute(TreeNode *node, TreeNode *neighbor);
    void *searchNeighbor(TreeNode *node);
public:
    PMBtree();
    void *search(int64_t key);
    void insert(int64_t key, void *ptr);
    void remove(const int64_t &key);
    int32_t getHeight();
};
