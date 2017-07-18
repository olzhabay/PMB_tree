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
    return node->key == key ? node->idx : -1;
}

void BinarySearchTree::insert(int64_t key, int16_t idx) {
    Node *leaf_a = new Node;
    leaf_a->key = key;
    leaf_a->idx = idx;
    leaf_a->left = leaf_a->right = nullptr;
    // new root
    if (root == nullptr) {
        root = leaf_a;
#if FLUSH
        clflush((char*)&leaf_a, sizeof(Node));
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
    Node *leaf_b = new Node;
    leaf_b->key = node->key;
    leaf_b->idx = node->idx;
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
    clflush((char*)&leaf_a, sizeof(Node));
    clflush((char*)&leaf_b, sizeof(Node));
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

// construct tree from given sorted array of keys
void BinarySearchTree::create(int64_t &keys[], int16_t size) {
    root = new Node;
    create(root, keys, 0, size-1);
}

void BinarySearchTree::create(Node *node, int64_t &keys[], int16_t from, int16_t to) {
    int16_t mid_id = (from + to) / 2 + (from + to) % 2;
    node->key = keys[mid_id];
    if (from < to) {
        node->left = new Node;
        create(node->left, keys, from, mid_id-1);
        node->right = new Node;
        create(node->right, keys, mid_id, to);
    } else {
        node->left = node->right = nullptr;
        node->idx = mid_id;
    }
}

int16_t BinarySearchTree::getNext(int64_t key) {
    return 0;
}

int16_t BinarySearchTree::getPrev(int64_t key) {
    return 0;
}

int16_t BinarySearchTree::getSmallest() {
    return 0;
}
