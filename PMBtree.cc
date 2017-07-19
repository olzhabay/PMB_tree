#include <algorithm>
#include "PMBtree.hh"
#include "util.hh"

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
    } else if (node->getTotalSize() >= CAPACITY) {
        node->defragmentation();
    }
}

void PMBtree::remove(const int64_t &key) {
    TreeNode *node = (TreeNode*)searchLeaf(key);
    node->remove(key);
    while (node->getSize() < THRESHOLD) {
        TreeNode *neighbor = (TreeNode *) searchNeighbor(node);
        if (node->getSize() + neighbor->getSize() < CAPACITY) {
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
    TreeNode *parent = (TreeNode *) node->getParent();
    // creating new nodes for split
    TreeNode *b = new TreeNode(parent, node->getNext());
    TreeNode *a = new TreeNode(parent, b);
    // copy data from node
    TreeNode::Data data[CAPACITY];
    int size = 0;
    for (int16_t i = 0; i < CAPACITY; i++)
        if (node->getData(i).valid)
            data[size++] = node->getData(i);
    std::sort(data, data + size, [](TreeNode::Data p1, TreeNode::Data p2) {
        return p1.key > p2.key;
    });
    // copy data to split nodes
    a->copyData(data, 0, size/2);
    b->copyData(data, size / 2 + 1, size);
#ifdef FLUSH
    clflush((char*)&a, sizeof(TreeNode));
    clflush((char*)&b, sizeof(TreeNode));
#endif
    // set next pointer in previous node of "node"
    int64_t key = node->getKey();
    TreeNode *prev = (TreeNode *) parent->getPrev(key);
    if (prev != nullptr) {
        prev->setNext(a);
        parent->remove(key);
        parent->insert(a->getKey(), a);
        parent->insert(b->getKey(), b);
    } else {
        parent->replaceFirst(key, a);
        parent->insert(b->getKey(), b);

    }
    delete node;

}

void PMBtree::merge(TreeNode *node, TreeNode *neighbor) {


}

void PMBtree::redistribute(TreeNode *node, TreeNode *neighbor) {

}

void *PMBtree::searchNeighbor(TreeNode *node) {
    TreeNode *parent = (TreeNode *) node->getParent();
    return parent->getNeighbor(node->getKey());
}
