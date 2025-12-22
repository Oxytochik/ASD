#include <stdexcept>

template <class T>
class List {
private:
    struct Node {
        T value;
        Node* next;

        Node(T value, Node* next = nullptr)
            : value(value), next(next) {
        }
    };

    Node* _head, * _tail;

public:
    class Iterator {
        Node* _current;

    public:
        Iterator() : _current(nullptr) {}
        Iterator(Node* node) : _current(node) {}

        Node* get_node() { return _current; }

        Iterator& operator=(const Iterator& other) noexcept {
            _current = other._current;
            return *this;
        }

        Iterator& operator++() noexcept {
            if (_current != nullptr) {
                _current = _current->next;
            }
            return *this;
        }

        Iterator operator++(int) noexcept {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator!=(const Iterator& other) const noexcept {
            return _current != other._current;
        }

        bool operator==(const Iterator& other) const noexcept {
            return _current == other._current;
        }

        T& operator*() {
            if (_current == nullptr) {
                throw std::runtime_error(
                    "List::Iterator.operator*(): Dereferencing end iterator");
            }
            return _current->value;
        }

        T* operator->() {
            if (_current == nullptr) {
                throw std::runtime_error(
                    "List::Iterator.operator->(): Accessing end iterator");
            }
            return &(_current->value);
        }

        Iterator& operator+=(size_t n) {
            for (size_t i = 0; i < n && _current != nullptr; ++i) {
                _current = _current->next;
            }
            return *this;
        }
    };

    Iterator begin() { return Iterator(_head); }
    Iterator end() { return Iterator(nullptr); }

    Node* get_tail() { return _tail; }

    List() : _head(nullptr), _tail(nullptr) {}

    List(const List<T>& other) : _head(nullptr), _tail(nullptr) {
        Node* cur = other._head;
        while (cur != nullptr) {
            push_back(cur->value);
            cur = cur->next;
        }
    }

    ~List() {
        while (!is_empty()) {
            pop_front();
        }
    }

    bool is_empty() {
        return _head == nullptr;
    }

    void push_front(const T& value) {
        Node* node = new Node(value);
        if (is_empty()) {
            _head = node;
            _tail = node;
            return;
        }
        node->next = _head;
        _head = node;
    }

    void push_back(const T& value) {
        Node* node = new Node(value);
        if (is_empty()) {
            _head = node;
            _tail = node;
            return;
        }
        _tail->next = node;
        _tail = node;
    }

    void insert(size_t pos, const T& value) {
        if (pos == 0) {
            push_front(value);
            return;
        }

        Node* cur = _head;
        size_t cur_pos = 0;
        while (cur != nullptr && cur_pos < pos - 1) {
            cur_pos++;
            cur = cur->next;
        }

        if (cur == nullptr) {
            throw std::logic_error("List.insert(): Position out of range");
        }

        insert_after(cur, value);
    }

    void insert_after(Node* node, const T& value) {
        if (node == nullptr || is_empty()) {
            throw std::logic_error("List.insert_after(): Invalid node or empty list");
        }
        Node* new_node = new Node(value);
        new_node->next = node->next;
        node->next = new_node;
        if (node == _tail) {
            _tail = new_node;
        }
    }

    void pop_front() {
        if (is_empty()) {
            throw std::logic_error("List.pop_front(): List is empty");
        }
        Node* temp = _head;
        _head = _head->next;
        delete temp;
        if (_head == nullptr) {
            _tail = nullptr;
        }
    }

    void pop_back() {
        if (is_empty()) {
            throw std::logic_error("List.pop_back(): List is empty");
        }
        if (_head == _tail) {
            delete _head;
            _head = nullptr;
            _tail = nullptr;
            return;
        }

        Node* cur = _head;
        while (cur->next != _tail) {
            cur = cur->next;
        }

        delete _tail;
        cur->next = nullptr;
        _tail = cur;
    }

    void erase(size_t pos) {
        if (pos == 0) {
            pop_front();
            return;
        }

        Node* cur = _head;
        size_t cur_pos = 0;
        while (cur != nullptr && cur_pos < pos - 1) {
            cur_pos++;
            cur = cur->next;
        }

        if (cur == nullptr || cur->next == nullptr) {
            throw std::logic_error("List.erase(): Position out of range");
        }

        Node* node_to_delete = cur->next;
        cur->next = node_to_delete->next;
        if (node_to_delete == _tail) {
            _tail = cur;
        }
        delete node_to_delete;
    }

    void erase(Node* node) {
        if (node == nullptr || is_empty()) {
            throw std::logic_error("List.erase(): Invalid node or empty list");
        }

        if (node == _head) {
            pop_front();
            return;
        }

        Node* cur = _head;
        while (cur->next != node) {
            if (cur->next == nullptr) {
                throw std::logic_error("List.erase(): Node not found in list");
            }
            cur = cur->next;
        }

        cur->next = node->next;
        if (node == _tail) {
            _tail = cur;
        }
        delete node;
    }
};