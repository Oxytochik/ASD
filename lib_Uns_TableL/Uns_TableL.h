#pragma once

#include <iostream>
#include <stdexcept>

#include "..\lib_TVector\TVector.h"
#include "..\lib_ITable\ITable.h"
#include "..\lib_List\List.h"


template <class TKey, class TValue>
class UnsortedTableL : public ITable<TKey, TValue> {
    List<std::pair<TKey, TValue>> _rows;
public:
    UnsortedTableL() = default;
    UnsortedTableL(const UnsortedTableL&) = default;
    ~UnsortedTableL() override = default;

    void insert(const TKey&, const TValue&) override;
    void erase(const TKey&) override;
    TValue* find(const TKey&) override;
    bool is_empty() const noexcept override;
    void print(std::ostream& out) const override;

private:
    auto find_pos(const TKey&) const;
    auto find_pos(const TKey&);
};

template <class TKey, class TValue>
void UnsortedTableL<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    auto it = find_pos(key);
    if (it != _rows.end()) {
        it->second = value;
        return;
    }
    _rows.push_back(std::make_pair(key, value));
}

template <class TKey, class TValue>
void UnsortedTableL<TKey, TValue>::erase(const TKey& key) {
    auto it = find_pos(key);
    if (it != _rows.end()) {
        _rows.erase(it.get_node());
        return;
    }
    throw std::logic_error("Key not found!");
}

template <class TKey, class TValue>
TValue* UnsortedTableL<TKey, TValue>::find(const TKey& key) {
    auto it = find_pos(key);
    if (it != _rows.end()) {
        return &(it->second);
    }
    throw std::logic_error("Key not found!");
}

template <class TKey, class TValue>
bool UnsortedTableL<TKey, TValue>::is_empty() const noexcept {
    return _rows.is_empty();
}

template <class TKey, class TValue>
void UnsortedTableL<TKey, TValue>::print(std::ostream& out) const {
    out << "UnsortedTableL: \n";
    for (auto it = _rows.begin(); it != _rows.end(); ++it) {
        out << "| " << it->first << " | " << it->second << " |\n";
    }
}



template <class TKey, class TValue>
auto UnsortedTableL<TKey, TValue>:: find_pos(const TKey& key) const {
    for (auto it = _rows.begin(); it != _rows.end(); ++it) {
        if (it->first == key) {
            return it;
        }
    }
    return _rows.end();
}

template <class TKey, class TValue>
auto UnsortedTableL<TKey, TValue>::find_pos(const TKey& key) {
    for (auto it = _rows.begin(); it != _rows.end(); ++it) {
        if (it->first == key) {
            return it;
        }
    }
    return _rows.end();
}
