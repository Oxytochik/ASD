#include <stdexcept>

template <class T>
struct Node {
    T value;
    Node<T>* next;

    Node(T value, Node<T>* next = nullptr)
        : value(value), next(next) {
    }
};



template <class T>
class List {
    Node<T>* _head, * _tail;

public:

    class Iterator {
        Node<T>* _current;

    public:
        Iterator() : _current(nullptr) {}
        Iterator(Node<T>* node) : _current(node) {}

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

    Iterator begin();
    Iterator end();





    List() : _head(nullptr), _tail(nullptr) {}

    List(const List<T>& other) : _head(nullptr), _tail(nullptr) {
        Node<T>* cur = other._head;
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
        Node<T>* node = new Node<T>(value);
        if (is_empty()) {
            _head = node;
            _tail = node;
            return;
        }
        node->next = _head;
        _head = node;
    }

    void push_back(const T& value) {
        Node<T>* node = new Node<T>(value);
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

        Node<T>* cur = _head;
        size_t cur_pos = 0;
        while (cur != nullptr && cur_pos < pos - 1) {
            cur_pos++;
            cur = cur->next;
        }

        if (cur == nullptr) {
            throw std::out_of_range("Position out of range");
        }

        insert(cur, value);
    }

    void insert(Node<T>* node, const T& value) {
        if (node == nullptr || is_empty()) {
            throw std::invalid_argument("Invalid node");
        }
        Node<T>* new_node = new Node<T>(value);
        new_node->next = node->next;
        node->next = new_node;
        if (node == _tail) {
            _tail = new_node;
        }
    }

    void pop_front() {
        if (is_empty()) {
            throw std::runtime_error("List is empty");
        }
        Node<T>* temp = _head;
        _head = _head->next;
        delete temp;
        if (_head == nullptr) {
            _tail = nullptr;
        }
    }

    void pop_back() {
        if (is_empty()) {
            throw std::runtime_error("List is empty");
        }
        if (_head == _tail) {
            delete _head;
            _head = nullptr;
            _tail = nullptr;
            return;
        }

        Node<T>* cur = _head;
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

        Node<T>* cur = _head;
        size_t cur_pos = 0;
        while (cur != nullptr && cur_pos < pos - 1) {
            cur_pos++;
            cur = cur->next;
        }

        if (cur == nullptr || cur->next == nullptr) {
            throw std::out_of_range("Position out of range");
        }

        Node<T>* node_to_delete = cur->next;
        cur->next = node_to_delete->next;
        if (node_to_delete == _tail) {
            _tail = cur;
        }
        delete node_to_delete;
    }

    void erase(Node<T>* node) {
        if (node == nullptr || is_empty()) {
            throw std::invalid_argument("Invalid node");
        }

        if (node == _head) {
            pop_front();
            return;
        }

        Node<T>* cur = _head;
        while (cur->next != node) {
            if (cur->next == nullptr) {
                throw std::invalid_argument("Node not found in list");
            }
            cur = cur->next;
        }

        cur->next = node->next;
        if (node == _tail) {
            _tail = cur;
        }
        delete node;
    }

    template <class T> //א גמע ץח קו חהוסü
    inline Node<T>* List::get_tail() {
        return _tail;
    }
};