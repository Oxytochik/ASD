#include <iostream>
#include <stdexcept>

#include "..\lib_ITable\ITable.h"
#include "..\lib_TVector\TVector.h"
//дублирование при всех поисках
template <class TKey, class TValue>
class UnsortedTableV : public ITable<TKey, TValue> {
private:
    TVector<std::pair<TKey, TValue>> _rows;

public:
    UnsortedTableV() = default;

    void insert(const TKey& key, const TValue& value) override {
        for (size_t i = 0; i < _rows.size(); i++) {
            if (_rows[i].first == key) {
                _rows[i].second = value;
                return;
            }
        }

        _rows.push_back({ key, value });
    }

    void erase(const TKey& key) override {
        for (size_t i = 0; i < _rows.size(); i++) {
            if (_rows[i].first == key) {
                _rows.erase(i);
                return;
            }
        }
    }

    TValue* find(const TKey& key) noexcept override {
        for (size_t i = 0; i < _rows.size(); i++) {
            if (_rows[i].first == key) {
                return &_rows[i].second;
            }
        }
        return nullptr;
    }

    bool isEmpty() const noexcept override { 
        return _rows.is_empty(); 
    }

    void print(std::ostream& out) const override {
        out << "UnsortedTableV (" << _rows.size() << " rows):\n";
        for (size_t i = 0; i < _rows.size(); i++) {
            out << "  " << _rows[i].first << " -> " << _rows[i].second << "\n";
        }
    }
};