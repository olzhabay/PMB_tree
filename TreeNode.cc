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

 void TreeNode::copyData(Data &*tocopy, int16_t from, int16_t to) {
     this->next = next;
     for (int16_t i = from; i <= to; i++) {
         data[i] = tocopy[i];
     }
     bst->create(data, size);
}

void TreeNode::insert(int64_t key, void *ptr) {
    this->data[tsize].key = key;
    this->data[tsize].ptr = ptr;
    this->data[tsize].valid = true;
#ifdef FLUSH
    clflush((char*)&data[tsize], sizeof(Data));
#endif
    bst->insert(key, tsize);
    tsize++;
    size++;
#ifdef FLUSH
    clflush((char*)size, 2*sizeof(int16_t));
#endif
}

void TreeNode::remove(int64_t key) {
    data[bst->remove(key)].valid = false;
    size--;
#ifdef FLUSH
    clflush((char*)size, sizeof(int16_t));
#endif
}

void *TreeNode::getPtr(int64_t key) {
    return data[bst->search(key)].ptr;
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

int16_t TreeNode::getTotalSize() {
    return tsize;
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
    return data[bst->getSmallest()].key;
}

void *TreeNode::getNeighbor(int64_t key) {
    return data[bst->getNeighbor(key)].ptr;
}

TreeNode::Data TreeNode::getData(int16_t idx) {
    return data[idx];
}

void *TreeNode::getPrev(int64_t key) {
    int prev_idx = bst->getPrev(key);
    return prev_idx == -1 ? nullptr : data[prev_idx].ptr;
}

void *TreeNode::getNext(int64_t key) {
    int next_idx = bst->getNext(key);
    return next_idx == -1 ? nullptr : data[next_idx].ptr;
}

void TreeNode::setNext(void *next) {
    this->next = next;
#ifdef FLUSH
    clflush((char*) this->next, sizeof(void*));
#endif
}


void TreeNode::replaceFirst(int64_t key, int64_t new_key, void *ptr) {
    BinarySearchTree::Node *node = bst->searchLeaf(key);
    int16_t idx = node->idx;
    data[idx].ptr = ptr;
    data[idx].key = new_key;
#ifdef FLUSH
    clflush((char*) data[idx].ptr, sizeof(void*));
    clflush((char*) data[idx].key, sizeof(int64_t));
#endif
}

// TODO
void TreeNode::defragmentation() {

}

void *TreeNode::first() {
    return size > 0 ? data[bst->getSmallest()].ptr : nullptr;
}

void *TreeNode::last() {
    return size > 0 ? data[bst->getBiggest()].ptr : nullptr;
}
