#include <stdexcept>

template <class T>
struct Node {
    T value;
    Node<T>* next;
    Node<T>* prev;

    Node(T value, Node<T>* next = nullptr, Node<T>* prev = nullptr)
        : value(value), next(next), prev(prev) {
    }
};

template <class T>
class List {
    Node<T>* _head;
    Node<T>* _tail;

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

        // Префиксный инкремент
        Iterator& operator++() noexcept {
            if (_current != nullptr) {
                _current = _current->next;
            }
            return *this;
        }

        // Постфиксный инкремент
        Iterator operator++(int) noexcept {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        // Префиксный декремент
        Iterator& operator--() noexcept {
            if (_current != nullptr) {
                _current = _current->prev;
            }
            return *this;
        }

        // Постфиксный декремент
        Iterator operator--(int) noexcept {
            Iterator temp = *this;
            --(*this);
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
                throw std::runtime_error("Dereferencing end iterator");
            }
            return _current->value;
        }

        T* operator->() {
            if (_current == nullptr) {
                throw std::runtime_error("Accessing end iterator");
            }
            return &(_current->value);
        }

        Iterator& operator+=(size_t n) {
            for (size_t i = 0; i < n && _current != nullptr; ++i) {
                _current = _current->next;
            }
            return *this;
        }

        Iterator& operator-=(size_t n) {
            for (size_t i = 0; i < n && _current != nullptr; ++i) {
                _current = _current->prev;
            }
            return *this;
        }
    };

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

    bool is_empty() const {
        return _head == nullptr;
    }

    void push_front(const T& value) {
        Node<T>* new_node = new Node<T>(value, _head);
        if (!is_empty()) {
            _head->prev = new_node;
        }
        else {
            _tail = new_node;
        }
        _head = new_node;
    }

    void push_back(const T& value) {
        Node<T>* new_node = new Node<T>(value, nullptr, _tail);
        if (!is_empty()) {
            _tail->next = new_node;
        }
        else {
            _head = new_node;
        }
        _tail = new_node;
    }

    void insert(size_t pos, const T& value) {
        if (pos == 0) {
            push_front(value);
            return;
        }

        Node<T>* cur = _head;
        for (size_t i = 0; i < pos - 1 && cur != nullptr; ++i) {
            cur = cur->next;
        }

        if (cur == nullptr) {
            throw std::out_of_range("Position out of range");
        }

        Node<T>* new_node = new Node<T>(value, cur->next, cur);
        if (cur->next != nullptr) {
            cur->next->prev = new_node;
        }
        else {
            _tail = new_node;
        }
        cur->next = new_node;
    }
    void pop_front() {
        if (is_empty()) {
            throw std::runtime_error("List is empty");
        }
        Node<T>* temp = _head;
        _head = _head->next;
        if (_head != nullptr) {
            _head->prev = nullptr;
        }
        else {
            _tail = nullptr;
        }
        delete temp;
    }

    void pop_back() {
        if (is_empty()) {
            throw std::runtime_error("List is empty");
        }
        Node<T>* temp = _tail;
        _tail = _tail->prev;
        if (_tail != nullptr) {
            _tail->next = nullptr;
        }
        else {
            _head = nullptr;
        }
        delete temp;
    }

    void erase(size_t pos) {
        if (pos == 0) {
            pop_front();
            return;
        }

        Node<T>* cur = _head;
        for (size_t i = 0; i < pos && cur != nullptr; ++i) {
            cur = cur->next;
        }

        if (cur == nullptr) {
            throw std::out_of_range("Position out of range");
        }

        cur->prev->next = cur->next;
        if (cur->next != nullptr) {
            cur->next->prev = cur->prev;
        }
        else {
            _tail = cur->prev;
        }
        delete cur;
    }

    Iterator begin() { return Iterator(_head); }
    Iterator end() { return Iterator(nullptr); }
};