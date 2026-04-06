#pragma once

#include <iostream>
#include <stdexcept>

#include "..\lib_TVector\TVector.h"
#include "..\lib_ITable\ITable.h"
#include "..\lib_List\List.h"
//то же самое дублирование
template <class TKey, class TValue>
class UnsortedTableL : public ITable<TKey, TValue> {
    List<std::pair<TKey, TValue>> _rows;

public:
    UnsortedTableL() = default;

    void insert(const TKey& key, const TValue& value) override {
        for (auto it = _rows.begin(); it != _rows.end(); ++it) {
            if (it->first == key) {
                it->second = value;
                return;
            }
        }
        _rows.push_back(std::make_pair(key, value));
    }

    void erase(const TKey& key) override {
        for (auto it = _rows.begin(); it != _rows.end(); ++it) {
            if (it->first == key) {
                _rows.erase(it.get_node());
                return;
            }
        }
    }

    TValue* find(const TKey& key) noexcept override {
        for (auto it = _rows.begin(); it != _rows.end(); ++it) {
            if (it->first == key) {
                return &(it->second);
            }
        }
        return nullptr;
    }

    bool isEmpty() const noexcept override {
        return _rows.is_empty();
    }

    void print(std::ostream& out) const override {
        size_t count = 0;
        for (auto it = _rows.begin(); it != _rows.end(); ++it) {
            ++count;
        }
        out << "UnsortedTableL (" << count << " rows):\n";
        for (auto it = _rows.begin(); it != _rows.end(); ++it) {
            out << "  " << it->first << " -> " << it->second << "\n";
        }
    }
};