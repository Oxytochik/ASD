#pragma once

#include <iostream>
#include <stdexcept>
#include "ITable.h"
#include "..\lib_BSTree\BSTree.h"   // ваш BSTree

template <class TKey, class TValue>
class Sorted_TableT : public ITable<TKey, TValue> {
private:
    BSTree<TKey, TValue> _data;

public:
    Sorted_TableT() = default;
    Sorted_TableT(const Sorted_TableT& other) = default;
    ~Sorted_TableT() override = default;

    void insert(const TKey& key, const TValue& value) override {
        if (_data.find(key) != nullptr)
            throw std::logic_error("Sorted_TableT::insert: key already exists");
        _data.insert(key, value);
    }

    void erase(const TKey& key) override {
        _data.erase(key);   // при отсутствии ключа бросает исключение
    }

    TValue* find(const TKey& key) override {
        return _data.find(key);
    }

    bool is_empty() const noexcept override {
        return _data.is_empty();
    }

    void print(std::ostream& out) const override {
        out << "Sorted_TableT:\n";
        if (_data.is_empty()) return;

        // перенаправляем std::cout в out (так как BSTree::print() пишет в std::cout)
        auto old_buf = std::cout.rdbuf(out.rdbuf());
        _data.print();
        std::cout.rdbuf(old_buf);
    }
};