#include <iostream>
#include <stdexcept>

#include "..\lib_ITable\ITable.h"
#include "..\lib_TVector\TVector.h"

template <class TKey, class TValue>
class STableV : public ITable<TKey, TValue> {
private:
    TVector<std::pair<TKey, TValue>> _rows;

    //int binarySearch(const TKey& key) const {
    //    int left = 0;
    //    int right = static_cast<int>(_rows.size()) - 1;
    //    while (left <= right) {
    //        int mid = left + (right - left) / 2;
    //        if (_rows[mid].first == key)
    //            return mid;
    //        if (_rows[mid].first < key)
    //            left = mid + 1;
    //        else
    //            right = mid - 1;
    //    }
    //    // left – позиция для вставки
    //    return -(left + 1);
    //}

    int binarySearch(const TKey& key) const {
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

public:
    STableV() = default;

    void insert(const TKey& key, const TValue& value) override {
        int index = binarySearch(key);
        if (index != -1) {
            _rows[index].second = value;
            return;
        }
        //бин поиск снизу переделать под единый формат
        int left = 0;
        int right = _rows.size() - 1;
        int insertPos = 0;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (_rows[mid].first == key) {
                insertPos = mid;
                break;
            }
            if (_rows[mid].first < key) {
                left = mid + 1;
                insertPos = left;
            }
            else {
                right = mid - 1;
                //insertPos = mid;
            }
        }
        _rows.insert(insertPos, std::make_pair(key, value));
    }

    void erase(const TKey& key) override {
        int index = binarySearch(key);
        if (index != -1)
            _rows.erase(index);
    }

    TValue* find(const TKey& key) noexcept override {
        int index = binarySearch(key);
        if (index != -1)
            return &_rows[index].second;
        return nullptr;
    }

    bool isEmpty() const noexcept override {
        return _rows.is_empty();
    }

    void print(std::ostream& out) const override {
        out << "STableV (" << _rows.size() << " rows):\n";
        for (int i = 0; i < _rows.size(); ++i)
            out << "  " << _rows[i].first << " -> " << _rows[i].second << "\n";
    }

};