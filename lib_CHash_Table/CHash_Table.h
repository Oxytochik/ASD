
#pragma once

#include <iostream>
#include <string>
#include <utility>
#include <stdexcept>
#include <iomanip>

#include "..\lib_ITable\ITable.h"
#include "..\lib_TVector\TVector.h"
#include "..\lib_List\List.h"

template <class TValue>
class CHash_Table : public ITable<std::string, TValue> {
private:
    TVector<List<std::pair<std::string, TValue>>> _buckets;
    size_t _size;
    size_t _count;

    size_t h(const std::string& key) const noexcept {
        size_t hash = 0;
        for (char c : key) {
            hash += static_cast<size_t>(c);
        }
        return hash % _size;
    }

    auto find_node(const std::string& key, size_t index) {
        auto& chain = _buckets[index];
        for (auto it = chain.begin(); it != chain.end(); ++it) {
            if (it->first == key) return it;
        }
        return chain.end();
    }

    auto find_node(const std::string& key, size_t index) const {
        const auto& chain = _buckets[index];
        for (auto it = chain.begin(); it != chain.end(); ++it) {
            if (it->first == key) return it;
        }
        return chain.end();
    }

public:
    CHash_Table() : _size(10), _count(0) {
        _buckets.resize(10, false);
    }

    explicit CHash_Table(size_t size) : _size(size), _count(0) {
        if (_size == 0) {
            _size = 1;
        }
        _buckets.resize(_size, false);
    }

    void insert(const std::string& key, const TValue& value) override {
        size_t idx = h(key);
        auto it = find_node(key, idx);
        if (it != _buckets[idx].end()) {
            throw std::logic_error("CHash_Table::insert: key already exists");
        }
        _buckets[idx].push_back({ key, value });
        ++_count;
    }

    void erase(const std::string& key) override {
        size_t idx = h(key);
        auto it = find_node(key, idx);
        if (it == _buckets[idx].end()) {
            throw std::logic_error("CHash_Table::erase: key not found");
        }
        _buckets[idx].erase(it.get_node());
        --_count;
    }

    TValue* find(const std::string& key) override {
        size_t idx = h(key);
        auto it = find_node(key, idx);
        if (it == _buckets[idx].end()) return nullptr;
        return &(it->second);
    }

    bool is_empty() const noexcept override {
        return _count == 0;
    }

    void print(std::ostream& out) const override {
        out << "CHash_Table:\n";
        if (_count == 0) {
            out << "  (empty)\n";
            return;
        }
        for (size_t i = 0; i < _size; ++i) {
            const auto& chain = _buckets[i];
            for (auto it = chain.begin(); it != chain.end(); ++it) {
                out << "| " << std::setw(10) << it->first
                    << " | " << std::setw(6) << it->second << " |\n";
            }
        }
    }

    size_t size() const noexcept { return _count; }
    size_t capacity() const noexcept { return _size; }

    TVector<std::pair<std::string, TValue>> get_pairs() const {
        TVector<std::pair<std::string, TValue>> result;
        for (size_t i = 0; i < _size; ++i) {
            const auto& chain = _buckets[i];
            for (auto it = chain.begin(); it != chain.end(); ++it) {
                result.push_back(*it);
            }
        }
        return result;
    }
};

// Функция объединения двух словарей с приоритетом первого
template <class TValue>
CHash_Table<TValue> merge_dictionaries(
    const CHash_Table<TValue>& dict1,
    const CHash_Table<TValue>& dict2)
{
    CHash_Table<TValue> result(dict1.capacity() + dict2.capacity());
    for (const auto& p : dict1.get_pairs()) {
        result.insert(p.first, p.second);
    }
    for (const auto& p : dict2.get_pairs()) {
        if (result.find(p.first) == nullptr) {
            result.insert(p.first, p.second);
        }
    }
    return result;
}