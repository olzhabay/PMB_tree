#include "BinarySearchTree.hh"
#include "util.hh"

BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}

int16_t BinarySearchTree::search(int64_t key) {
    Node *node = searchLeaf(key);
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
    Node *node = searchLeaf(key);
    Node *grandparent = node->parent;
    // creating new parent
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
    parent->left = leaf_a->key < leaf_b->key ? leaf_a : leaf_b;
    parent->right = leaf_a->key < leaf_b->key ? leaf_b : leaf_a;
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
    delete node;
}

int16_t BinarySearchTree::remove(int64_t key) {
    Node *node = searchLeaf(key);
    Node *parent = node->parent;
    // if only one element in the tree, root
    if (parent == nullptr) {
        root = nullptr;
#if FLUSH
        clflush((char*)root, sizeof(Node*));
#endif
        int16_t idx = node->idx;
        delete node;
        return idx;
    }
    // if only two leaf elements in the tree
    Node *grandparent = parent->parent;
    if (grandparent == nullptr) {
        root = parent->key > key ? parent->right : parent->left;
#if FLUSH
        clflush((char*)root, sizeof(Node*));
#endif
    } else {
        // normal cases
        if (grandparent->key > parent->key) {
            grandparent->left = parent->key > key ? parent->right : parent->left;
#ifdef FLUSH
            clflush((char *) grandparent->left, sizeof(Node *));
#endif
        } else {
            grandparent->right = parent->key > key ? parent->right : parent->left;
#ifdef FLUSH
            clflush((char *) grandparent->right, sizeof(Node *));
#endif
        }
    }
    int16_t idx = node->idx;
    delete node;
    delete parent;
    return idx;
}

// construct tree from given sorted array of keys
void BinarySearchTree::create(TreeNode::Data &data[], int16_t size) {
    root = new Node;
    create(root, data, 0, size-1);
}

void BinarySearchTree::create(Node *node, TreeNode::Data &data[], int16_t from, int16_t to) {
    int16_t mid_id = (from + to) / 2 + (from + to) % 2;
    node->key = data[mid_id].key;
    if (from < to) {
        node->left = new Node;
        create(node->left, data, from, mid_id-1);
        node->right = new Node;
        create(node->right, data, mid_id, to);
    } else {
        node->left = node->right = nullptr;
        node->idx = mid_id;
    }
}

int16_t BinarySearchTree::getNeighbor(int64_t key) {
    Node *node = searchLeaf(key);
    node = node->parent;
    return node->key > key ? node->right->idx : node->left->idx;
}


int16_t BinarySearchTree::getSmallest() {
    Node *node = root;
    while (node->left != nullptr)
        node = node->left;
    return node == nullptr ? -1 : node->idx;
}

int16_t BinarySearchTree::getBiggest() {
    Node *node = root;
    while (node->right != nullptr)
        node = node->right;
    return node == nullptr ? -1 : node->idx;
}

int16_t BinarySearchTree::getNext(int64_t key) {
    Node *node = searchLeaf(key);
    while (node != nullptr && node->key <= key)
        node = node->parent;
    if (node == nullptr) return -1;
    node = node->right;
    while (node->left != node->right != nullptr) {
        node = node->left;
    }
    return node->idx;
}

int16_t BinarySearchTree::getPrev(int64_t key) {
    Node *node = searchLeaf(key);
    while (node != nullptr && node->key > key)
        node = node->parent;
    if (node == nullptr) return -1;
    node = node->left;
    while (node->left != node->right != nullptr) {
        node = node->right;
    }
    return node->idx;
}

BinarySearchTree::Node *BinarySearchTree::searchLeaf(int64_t key) {
    Node *node = root;
    while (node->left != node->right != nullptr) {
        node = node->key > key ? node->left : node->right;
    }
    return node;
}
