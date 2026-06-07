#pragma once

#include <iostream>
#include <stdexcept>

#include "..\lib_Queue\Queue.h"

template<class TKey, class TValue>
struct TNode {

	std::pair<TKey, TValue> _data;
	TNode* _left = nullptr;
	TNode* _right = nullptr;

	TNode(const TKey& key, const TValue& value);
	~TNode();
};

template <class TKey, class TValue>
TNode<TKey, TValue>::TNode(const TKey& key, const TValue& value) : _data(key, value) {}

template<class TKey, class TValue>
TNode<TKey, TValue>::~TNode() {
	delete _left;
	delete _right;
}



template<class TKey, class TValue>
class BTree {

	TNode<TKey, TValue>* _root;

public:
	BTree();
	BTree(const TKey& key, const TValue& value);
	~BTree();

    const TNode<TKey, TValue>* get_root() const noexcept;
    TNode<TKey, TValue>* get_root() noexcept;

    void insert(const TKey& key, const TValue& value) noexcept;
    TValue* find(const TKey& key) const noexcept;
    void erase(const TKey& key);

    bool is_empty() const noexcept;
    void clear() noexcept;

    void print_W() const noexcept;
    void print_DLCR() const noexcept;
    void print_DLRC() const noexcept;
    void print_DCLR() const noexcept;

    void print_DLCR_rec(TNode<TKey, TValue>* node) const;
    void print_DLRC_rec(TNode<TKey, TValue>* node) const;
    void print_DCLR_rec(TNode<TKey, TValue>* node) const;

};


template <class TKey, class TValue>
BTree<TKey, TValue>::BTree() : _root(nullptr) {}
template <class TKey, class TValue>
BTree<TKey, TValue>::BTree(const TKey& key, const TValue& value) : _root(new TNode<TKey, TValue>(key, value)) {}
template <class TKey, class TValue>
BTree<TKey, TValue>::~BTree() {
    clear();
}

template <class TKey, class TValue>
void BTree<TKey, TValue>::insert(const TKey& key, const TValue& value) noexcept {
    if (is_empty()) {
        _root = new TNode<TKey, TValue>(key, value);
        return;
    }

    TNode<TKey, TValue>* cur = nullptr;
    Queue<TNode<TKey, TValue>*> q;
    q.push(_root);

    while (!q.is_empty()) {
        cur = q.head();
        q.pop();

        if (!cur->_left) { 
            cur->_left = new TNode<TKey, TValue>(key, value); 
            return; 
        }

        if (!cur->_right) { 
            cur->_right = new TNode<TKey, TValue>(key, value);
            return; 
        }

        q.push(cur->_left);
        q.push(cur->_right);
    }

}


template <class TKey, class TValue>
TValue* BTree<TKey, TValue>::find(const TKey& key) const noexcept {
    if (is_empty()) {
        return nullptr;
    }

    TNode<TKey, TValue>* cur = nullptr;
    Queue<TNode<TKey, TValue>*> q;
    q.push(_root);

    while (!q.is_empty()) {
        cur = q.head();
        q.pop();

        if (cur->_data.first == key) {
            return &(cur->_data.second);
        }

        if (cur->_left) {
            q.push(cur->_left);
        }
        if (cur->_right) {
            q.push(cur->_right);
        }
    }
}


template <class TKey, class TValue>
void BTree<TKey, TValue>::erase(const TKey& key) {
    if (is_empty()) throw std::logic_error("The tree is empty!");

    TNode<TKey, TValue>* cur = nullptr;

    TNode<TKey, TValue>* erase_node = nullptr;

    TNode<TKey, TValue>* last_parent = nullptr;
    TNode<TKey, TValue>* last = nullptr;

    Queue<TNode<TKey, TValue>*> q;
    q.push(_root);

    while (!q.is_empty()) {
        cur = q.head();
        q.pop();

        if (cur->_data.first == key) erase_node = cur;
        last = cur;

        if (cur->_left) {
            q.push(cur->_left);
            last_parent = cur;
        }
        if (cur->_right) {
            q.push(cur->_right);
            last_parent = cur;
        }
    }

    if (!erase_node) throw std::logic_error("Key not found for erase!");

    if (erase_node == _root && !_root->_left && !_root->_right) {
        delete _root;
        _root = nullptr;
        return;
    }

    erase_node->_data = last->_data;

    if (last_parent->_left == last) {
        delete last_parent->_left;
        last_parent->_left = nullptr;
    }
    else if (last_parent->_right == last) {
        delete last_parent->_right;
        last_parent->_right = nullptr;
    }

}

template <class TKey, class TValue>
bool BTree<TKey, TValue>::is_empty() const noexcept {
    return _root == nullptr;
}

template <class TKey, class TValue>
void BTree<TKey, TValue>::clear() noexcept {
    if (is_empty()) return;

    TNode<TKey, TValue>* cur = nullptr;
    Queue<TNode<TKey, TValue>*> q;
    q.push(_root);

    while (!q.is_empty()) {
        cur = q.head();
        q.pop();

        if (cur->_left) q.push(cur->_left);
        if (cur->_right) q.push(cur->_right);

        cur->_left = nullptr;
        cur->_right = nullptr;
        delete cur;
    }

    _root = nullptr;
}

template <class TKey, class TValue>
void BTree<TKey, TValue>::print_W() const noexcept {      
    if (is_empty()) return;

    Queue<TNode<TKey, TValue>*> q;
    TNode<TKey, TValue>* cur = nullptr;
    q.push(_root);

    while (!q.is_empty()) {
        cur = q.head();
        q.pop();

        std::cout << cur->_data.first << ":" << cur->_data.second << " ";

        if (cur->_left) q.push(cur->_left);
        if (cur->_right) q.push(cur->_right);
    }
    std::cout << std::endl;
}
template <class TKey, class TValue>
void BTree<TKey, TValue>::print_DCLR() const noexcept {
    print_DCLR_rec(_root);
    std::cout << std::endl;
}
template <class TKey, class TValue>
void BTree<TKey, TValue>::print_DLCR() const noexcept {
    print_DLCR_rec(_root);
    std::cout << std::endl;
}
template <class TKey, class TValue>
void BTree<TKey, TValue>::print_DLRC() const noexcept {
    print_DLRC_rec(_root);
    std::cout << std::endl;
}

template <class TKey, class TValue>
void BTree<TKey, TValue>::print_DCLR_rec(TNode<TKey, TValue>* node) const {   
    if (node == nullptr) return;

    std::cout << node->_data.first << ":" << node->_data.second << " ";
    if (node->_left) print_DCLR_rec(node->_left);
    if (node->_right) print_DCLR_rec(node->_right);
}
template <class TKey, class TValue>
void BTree<TKey, TValue>::print_DLCR_rec(TNode<TKey, TValue>* node) const {   
    if (node == nullptr) return;

    if (node->_left) print_DLCR_rec(node->_left);
    std::cout << node->_data.first << ":" << node->_data.second << " ";
    if (node->_right) print_DLCR_rec(node->_right);
}
template <class TKey, class TValue>
void BTree<TKey, TValue>::print_DLRC_rec(TNode<TKey, TValue>* node) const {   
    if (node == nullptr) return;

    if (node->_left) print_DLRC_rec(node->_left);
    if (node->_right) print_DLRC_rec(node->_right);
    std::cout << node->_data.first << ":" << node->_data.second << " ";
}

template <class TKey, class TValue>
const TNode<TKey, TValue>* BTree<TKey, TValue>::get_root() const noexcept { 
    return _root; 
}
template <class TKey, class TValue>
TNode<TKey, TValue>* BTree<TKey, TValue>::get_root() noexcept { 
    return _root; 
}
