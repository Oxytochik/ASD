#include <iostream>
#include <stdexcept>

#include "..\lib_ITable\ITable.h"
#include "..\lib_TVector\TVector.h"

template <class TKey, class TValue>
class UnsortedTableV : public ITable<TKey, TValue> {
private:
    TVector<std::pair<TKey, TValue>> _rows;
public:
    UnsortedTableV() = default;
    UnsortedTableV(const UnsortedTableV&) = default;
    ~UnsortedTableV() override = default;

    void insert(const TKey&, const TValue&) override;
    void erase(const TKey&) override;
    TValue* find(const TKey&) override;

    bool is_empty() const noexcept override;
    void print(std::ostream& out) const override;

private:
    int find_pos(const TKey&) const noexcept;
};



template <class TKey, class TValue>
void UnsortedTableV<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    int pos = find_pos(key);
    if (pos != -1) {
        _rows[pos].second = value;
        return;
    }
    _rows.push_back(std::make_pair(key, value));
}

template <class TKey, class TValue>
void UnsortedTableV<TKey, TValue>::erase(const TKey& key) {
    int pos = find_pos(key);
    if (pos != -1) {
        _rows.erase(pos);
        return;
    }
    throw std::logic_error("Key not found!");
}

template <class TKey, class TValue>
TValue* UnsortedTableV<TKey, TValue>::find(const TKey& key) {
    int pos = find_pos(key);
    if (pos != -1) {
        return &_rows[pos].second;
    }
    throw std::logic_error("Key not found!");
}

template <class TKey, class TValue>
bool UnsortedTableV<TKey, TValue>::is_empty() const noexcept{
    return _rows.is_empty();
}

template <class TKey, class TValue>
void UnsortedTableV<TKey, TValue>::print(std::ostream& out) const {
    out << "UnsortedTableV: \n";
    for (int i = 0; i < _rows.size();i++) {
        out << "| " << _rows[i].first << " | " << _rows[i].second << " |\n";
    }
}

template <class TKey, class TValue>
int UnsortedTableV<TKey, TValue>::find_pos(const TKey& key) const noexcept {
    for (size_t i = 0; i < _rows.size(); i++) {
        if (_rows[i].first == key) {
            return i;
        }
    }
    return -1;
}

//template <class TKey, class Tvalue>
//int UnsortedTableV<class TKey, class TValue>::find_pos(const TKey& key) const {
//    for (size_t i = 0; i < _rows.size(); i++) {
//        if (_rows[i].first == key) {
//            return i;
//        }
//    }
//    return -1;
//}


