#include "TreeNode.hh"
#include "util.hh"

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
#ifdef FLUSH
    clflush((char*)key[tsize], sizeof(int64_t));
    clflush((char*)ptr[tsize], sizeof(int64_t));
#endif
    bst.insert(key, tsize);
    tsize++;
    size++;
#ifdef FLUSH
    clflush((char*)size, 2*sizeof(int16_t));
#endif
}

void TreeNode::remove(int64_t key) {
    bst.remove(key);
    size--;
#ifdef FLUSH
    clflush((char*)size, sizeof(int16_t));
#endif
}

void *TreeNode::getPtr(int64_t key) {
    return ptr[bst.search(key)];
}

void *TreeNode::getNext() {
    return next;
}

void *TreeNode::getParent() {
    return parent;
}

int16_t TreeNode::getSize() {
    return size;
}

int16_t TreeNode::getLevel() {
    return level;
}

bool TreeNode::isLeaf() {
    return level == 0;
}

bool TreeNode::isFull() {
    return tsize >= CAPACITY;
}

int64_t TreeNode::getKey() {
    return key[bst.getSmallest()];
}

void *TreeNode::getNext(int64_t key) {
    return ptr[bst.getNext(key)];
}

void *TreeNode::getPrev(int64_t key) {
    return ptr[bst.getPrev(key)];
}
