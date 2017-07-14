#include "TreeNode.hh"


TreeNode::TreeNode() {
    parent = nullptr;
    next = nullptr;
    size = 0;
    tsize = 0;
    level = 0;
}

TreeNode::TreeNode(void *parent, void *next) {
    this->parent = parent;
    this->next = next;
    size = 0;
    tsize = 0;
    level = 0;
}

void TreeNode::insert(int64_t key, void *ptr) {
    this->key[tsize] = key;
    this->ptr[tsize] = ptr;
    bst.insert(key, tsize);
    tsize++;
    size++;


}


