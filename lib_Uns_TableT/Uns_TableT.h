#pragma once

#include <iostream>
#include <stdexcept>
#include "ITable.h"
#include "..\lib_BTree\BTree.h"   // ваш BTree
#include "..\lib_queue\Queue.h"

template <class TKey, class TValue>
class Uns_TableT : public ITable<TKey, TValue> {
private:
    BTree<TKey, TValue> _data;

public:
    Uns_TableT() = default;
    Uns_TableT(const Uns_TableT& other) = default;
    ~Uns_TableT() override = default;

    void insert(const TKey& key, const TValue& value) override {
        if (_data.find(key) != nullptr)
            throw std::logic_error("Uns_TableT::insert: key already exists");
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
        out << "Uns_TableT:\n";
        if (_data.is_empty()) return;

        // BTree::print_W() выводит в std::cout Ц перенаправл€ем
        auto old_buf = std::cout.rdbuf(out.rdbuf());
        _data.print_W();
        std::cout.rdbuf(old_buf);
    }
};