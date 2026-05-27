#include <iostream>
#include <stdexcept>
#include <utility>
#include <functional>      
#include "..\lib_Queue\Queue.h"   
template <class TKey, class TValue>
struct Node {
    std::pair<TKey, TValue> data;
    Node* left;
    Node* right;

    Node(const TKey& key, const TValue& value, Node* l = nullptr, Node* r = nullptr)
        : data(key, value), left(l), right(r) {
    }
};

template <class TKey, class TValue>
class BSTree {
private:
    Node<TKey, TValue>* _root;
    size_t _size;

    // Вспомогательные методы
    Node<TKey, TValue>* find_parent(const TKey& key) const noexcept;
    Node<TKey, TValue>* find_node(const TKey& key) const noexcept;
    Node<TKey, TValue>* find_replacing(Node<TKey, TValue>* node) const noexcept;
    void delete_tree(Node<TKey, TValue>* node) noexcept;

public:
    BSTree();
    BSTree(const TKey& key, const TValue& value);
    ~BSTree();

    bool is_empty() const noexcept;
    size_t size() const noexcept;

    void insert(const TKey& key, const TValue& value);
    TValue* find(const TKey& key) const noexcept;
    void erase(const TKey& key);
    void clear() noexcept;
    void print() const noexcept;
    void print_DLCR_rec(Node<TKey, TValue>* node) const;
};

// ---------- Реализация ----------

template <class TKey, class TValue>
BSTree<TKey, TValue>::BSTree() : _root(nullptr), _size(0) {}

template <class TKey, class TValue>
BSTree<TKey, TValue>::BSTree(const TKey& key, const TValue& value)
    : _root(new Node<TKey, TValue>(key, value)), _size(1) {
}

template <class TKey, class TValue>
BSTree<TKey, TValue>::~BSTree() {
    clear();
}

template <class TKey, class TValue>
bool BSTree<TKey, TValue>::is_empty() const noexcept {
    return _root == nullptr;
}

template <class TKey, class TValue>
size_t BSTree<TKey, TValue>::size() const noexcept {
    return _size;
}

template <class TKey, class TValue>
Node<TKey, TValue>* BSTree<TKey, TValue>::find_parent(const TKey& key) const noexcept {
    if (is_empty()) return nullptr;
    if (_root->data.first == key) return _root;

    Node<TKey, TValue>* cur = _root;
    while (true) {
        if (key < cur->data.first) {
            if (!cur->left) return cur;
            if (cur->left->data.first == key) return cur;
            cur = cur->left;
        }
        else {
            if (!cur->right) return cur;
            if (cur->right->data.first == key) return cur;
            cur = cur->right;
        }
    }
}

template <class TKey, class TValue>
Node<TKey, TValue>* BSTree<TKey, TValue>::find_node(const TKey& key) const noexcept {
    Node<TKey, TValue>* cur = _root;
    while (cur) {
        if (key == cur->data.first) return cur;
        else if (key < cur->data.first) cur = cur->left;
        else cur = cur->right;
    }
    return nullptr;
}

template <class TKey, class TValue>
Node<TKey, TValue>* BSTree<TKey, TValue>::find_replacing(Node<TKey, TValue>* node) const noexcept {
    if (!node || !node->left) return nullptr;
    Node<TKey, TValue>* cur = node->left;
    while (cur->right) cur = cur->right;
    return cur;
}

template <class TKey, class TValue>
void BSTree<TKey, TValue>::delete_tree(Node<TKey, TValue>* node) noexcept {
    if (!node) return;
    delete_tree(node->left);
    delete_tree(node->right);
    delete node;
}

template <class TKey, class TValue>
void BSTree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    Node<TKey, TValue>* parent = find_parent(key);
    if (!parent) {                       // дерево пусто
        _root = new Node<TKey, TValue>(key, value);
        _size++;
        return;
    }
    if (parent->data.first == key) {    // ключ в корне (или parent == _root)
        parent->data.second = value;
        return;
    }
    if (key < parent->data.first) {
        if (!parent->left) {
            parent->left = new Node<TKey, TValue>(key, value);
            _size++;
        }
        else {
            // ключ уже существует (parent->left->data.first == key)
            parent->left->data.second = value;
        }
    }
    else {
        if (!parent->right) {
            parent->right = new Node<TKey, TValue>(key, value);
            _size++;
        }
        else {
            parent->right->data.second = value;
        }
    }
}

template <class TKey, class TValue>
TValue* BSTree<TKey, TValue>::find(const TKey& key) const noexcept {
    Node<TKey, TValue>* parent = find_parent(key);
    if (!parent) return nullptr;
    if (parent->data.first == key) return &parent->data.second;
    if (parent->left && parent->left->data.first == key) return &parent->left->data.second;
    if (parent->right && parent->right->data.first == key) return &parent->right->data.second;
    return nullptr;
}

template <class TKey, class TValue>
void BSTree<TKey, TValue>::erase(const TKey& key) {
    Node<TKey, TValue>* node = find_node(key);
    if (!node) throw std::logic_error("Key not found for erase!");

    // Случай 1: лист
    if (!node->left && !node->right) {
        if (node == _root) {
            delete _root;
            _root = nullptr;
        }
        else {
            Node<TKey, TValue>* parent = find_parent(key);
            if (parent->left == node) parent->left = nullptr;
            else parent->right = nullptr;
            delete node;
        }
        _size--;
        return;
    }

    // Случай 2: один потомок
    if (!node->left || !node->right) {
        Node<TKey, TValue>* child = (node->left) ? node->left : node->right;
        if (node == _root) {
            _root = child;
        }
        else {
            Node<TKey, TValue>* parent = find_parent(key);
            if (parent->left == node) parent->left = child;
            else parent->right = child;
        }
        node->left = node->right = nullptr;
        delete node;
        _size--;
        return;
    }

    // Случай 3: два потомка
    Node<TKey, TValue>* replacement = find_replacing(node);
    TKey replKey = replacement->data.first;
    TValue replValue = replacement->data.second;

    erase(replKey);   // рекурсивно удаляем узел-замену

    node->data.first = replKey;
    node->data.second = replValue;
}

template <class TKey, class TValue>
void BSTree<TKey, TValue>::clear() noexcept {
    delete_tree(_root);
    _root = nullptr;
    _size = 0;
}

template <class TKey, class TValue>
void BSTree<TKey, TValue>::print() const noexcept {
    print_DLCR_rec(_root);
    std::cout << std::endl;
}
template <class TKey, class TValue>
void BSTree<TKey, TValue>::print_DLCR_rec(Node<TKey, TValue>* node) const {   
    if (node == nullptr) return;

    if (node->left) print_DLCR_rec(node->left);
    std::cout << node->data.first << ":" << node->data.second << " ";
    if (node->right) print_DLCR_rec(node->right);
}