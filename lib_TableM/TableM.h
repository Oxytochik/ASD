#pragma once

#include <iostream>
#include <stdexcept>

#include "..\lib_ITable\ITable.h"
#include "..\lib_TVector\TVector.h"

template <class TKey, class TValue>
class STableV : public ITable<TKey, TValue> {
    TVector<std::pair<TKey, TValue>> _rows;

public:
    STableV() = default;
    STableV(const STableV&) = default;
    ~STableV() override = default;

    void insert(const TKey& key, const TValue& value) override;
    void erase(const TKey& key) override;
    TValue* find(const TKey& key) noexcept override;

    bool is_empty() const noexcept override;
    void print(std::ostream& out) const override;

private:
    int binary_search(const TKey& key) const;
    int find_insert_position(const TKey& key) const;
};



template <class TKey, class TValue>
int STableV<TKey, TValue>::binary_search(const TKey& key) const {
    int left = 0;
    int right = _rows.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (_rows[mid].first == key)
            return mid;
        if (_rows[mid].first < key)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

template <class TKey, class TValue>
int STableV<TKey, TValue>::find_insert_position(const TKey& key) const {
    int left = 0;
    int right = _rows.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (_rows[mid].first < key) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return left;
}

template <class TKey, class TValue>
void STableV<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    int index = binary_search(key);
    if (index != -1) {
        _rows[index].second = value;
        return;
    }
    int insert_pos = find_insert_position(key);
    _rows.insert(insert_pos, std::make_pair(key, value));
}

template <class TKey, class TValue>
void STableV<TKey, TValue>::erase(const TKey& key) {
    int index = binary_search(key);
    if (index != -1)
        _rows.erase(index);
}

template <class TKey, class TValue>
TValue* STableV<TKey, TValue>::find(const TKey& key) noexcept {
    int index = binary_search(key);
    if (index != -1)
        return &_rows[index].second;
    return nullptr;
}

template <class TKey, class TValue>
bool STableV<TKey, TValue>::is_empty() const noexcept {
    return _rows.is_empty();
}

template <class TKey, class TValue>
void STableV<TKey, TValue>::print(std::ostream& out) const {
    out << "STableV (" << _rows.size() << " rows):\n";
    for (int i = 0; i < _rows.size(); ++i)
        out << "  " << _rows[i].first << " -> " << _rows[i].second << "\n";
}