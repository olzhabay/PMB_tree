#include "PMBtree.hh"

PMBtree::PMBtree() {
    root = nullptr;
}

void *PMBtree::search(int64_t key) {
    TreeNode *node = (TreeNode*)searchLeaf(key);
    return node->getPtr(key);
}

void PMBtree::insert(int64_t key, void *ptr) {
    TreeNode *node = (TreeNode*)searchLeaf(key);
    if (node == nullptr) {
        root = new TreeNode;
        node = root;
    }
    node->insert(key, ptr);
    if (node->isFull()) {
        split(node);
    }
}

void PMBtree::remove(const int64_t &key) {
    TreeNode *node = (TreeNode*)searchLeaf(key);
    node->remove(key);
    while (node->getSize() < THRESHOLD) {
        TreeNode *neighbor = searchNeighbor(node);
        if (node->getSize()+neighbor->getSize() < CAPACITY) {
            merge(node, neighbor);
        } else {
            redistribute(node, neighbor);
        }
    }
}

int32_t PMBtree::getHeight() {
    return root->getLevel();
}

void *PMBtree::searchLeaf(int64_t key) {
    TreeNode *node = root;
    while (node != nullptr && !node->isLeaf()) {
        node = (TreeNode*)node->getPtr(key);
    }
    return node;
}

void PMBtree::split(TreeNode *node) {

}

void PMBtree::merge(TreeNode *node, TreeNode *neighbor) {

}

void PMBtree::redistribute(TreeNode *node, TreeNode *neighbor) {

}

void *PMBtree::searchNeighbor(TreeNode *node) {
    TreeNode *parent = (TreeNode*)node->getParent();
    TreeNode *next = parent->getNext(node->getKey());
    TreeNode *prev = parent->getPrev(node->getKey());
    return nullptr;
}
