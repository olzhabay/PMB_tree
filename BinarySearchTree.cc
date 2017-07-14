#include "BinarySearchTree.hh"
#include "util.hh"

BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}

int16_t BinarySearchTree::search(int64_t key) {
    Node *node = root;
    while (node->left != node->right != nullptr) {
        node = node->key < key ? node->left : node->right;
    }
    return node->key == key ? ((LeafNode*)node)->idx : -1;
}

void BinarySearchTree::insert(int64_t key, int16_t idx) {
    LeafNode *leaf_a = new LeafNode;
    leaf_a->key = key;
    leaf_a->idx = idx;
    leaf_a->left = leaf_a->right = nullptr;
    // new root
    if (root == nullptr) {
        root = leaf_a;
#if FLUSH
        clflush((char*)&leaf_a, sizeof(LeafNode));
        clflush((char*)&root, sizeof(Node*));
#endif
        return;
    }
    // finding leaf_a
    Node *node = root;
    while (node->left != node->right != nullptr) {
        node = node->key > key ? node->left : node->right;
    }

    Node *grandparent = node->parent;
    Node *parent = new Node;

    // copy node to leaf_b
    LeafNode *leaf_b = new LeafNode;
    leaf_b->key = node->key;
    leaf_b->idx = ((LeafNode*)node)->idx;
    leaf_b->parent = parent;
    // assign leaf_a's parent
    leaf_a->parent = parent;
    // assign vals to new parent
    parent->key = key;
    parent->parent = grandparent;
    parent->left = (Node *) (leaf_a->key < leaf_b->key ? leaf_a : leaf_b);
    parent->right = (Node *) (leaf_a->key < leaf_b->key ? leaf_b : leaf_a);
#if FLUSH
    clflush((char*)&parent, sizeof(Node));
    clflush((char*)&leaf_a, sizeof(LeafNode));
    clflush((char*)&leaf_b, sizeof(LeafNode));
#endif
    // changing grandparent's child pointer to parent
    if (grandparent != nullptr) {
        if (grandparent->key > parent->key) {
            grandparent->left = parent;
#if FLUSH
            clflush((char*)&grandparent->left, sizeof(Node*));
#endif
        } else {
            grandparent->right = parent;
#if FLUSH
            clflush((char*)&grandparent->right, sizeof(Node*));
#endif
        }
    } else {
        root = parent;
#if FLUSH
        clflush((char*)&root, sizeof(Node*));
#endif
    }
}

void BinarySearchTree::remove(int64_t key) {
    Node *node = root;
    while (node->left != node->right != nullptr) {
        node = node->key < key ? node->left : node->right;
    }
    Node *parent = node->parent;
    if (parent == nullptr) {
        root = nullptr;
#if FLUSH
        clflush((char*)root, sizeof(Node*));
#endif
        return;
    }
    Node *grandparent = parent->parent;
    if (grandparent == nullptr) {
        root = parent->key > key ? parent->right : parent->left;
#if FLUSH
        clflush((char*)root, sizeof(Node*));
#endif
        return;
    }
    if (grandparent->key > parent->key) {
        grandparent->left = parent->key > key ? parent->right : parent->left;
#ifdef FLUSH
        clflush((char*)grandparent->left, sizeof(Node*));
#endif
    } else {
        grandparent->right = parent->key > key ? parent->right : parent->left;
#ifdef FLUSH
        clflush((char*)grandparent->right, sizeof(Node*));
#endif
    }
}

void BinarySearchTree::create(int64_t keys, int16_t idxs) {

}
