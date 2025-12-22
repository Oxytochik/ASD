//стек на списке, очередь на списке (проверить на дубликаты и разбить их (два теста в одном), список покрыть тестами, не забыть про инициализатор.
#include <gtest/gtest.h>
#include "../lib_list/List.h"
#include <iostream>

// Тест пустого списка
TEST(ListTest, EmptyList) {
    List<int> list;
    EXPECT_TRUE(list.is_empty());
    EXPECT_EQ(list.begin(), list.end());
}

// Тест добавления в начало
TEST(ListTest, PushFront) {
    List<int> list;
    list.push_front(3);
    list.push_front(2);
    list.push_front(1);

    std::vector<int> values;
    for (int val : list) {
        values.push_back(val);
    }
    EXPECT_EQ(values, std::vector<int>({ 1, 2, 3 }));
}

// Тест добавления в конец
TEST(ListTest, PushBack) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    std::vector<int> values;
    for (int val : list) {
        values.push_back(val);
    }
    EXPECT_EQ(values, std::vector<int>({ 1, 2, 3 }));
}

// Тест вставки по позиции
TEST(ListTest, Insert) {
    List<int> list;
    list.push_back(1);
    list.push_back(3);

    list.insert(1, 2);

    std::vector<int> values;
    for (int val : list) {
        values.push_back(val);
    }
    EXPECT_EQ(values, std::vector<int>({ 1, 2, 3 }));
}

// Тест удаления из начала
TEST(ListTest, PopFront) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.pop_front();

    std::vector<int> values;
    for (int val : list) {
        values.push_back(val);
    }
    EXPECT_EQ(values, std::vector<int>({ 2, 3 }));
}

// Тест удаления из конца
TEST(ListTest, PopBack) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.pop_back();

    std::vector<int> values;
    for (int val : list) {
        values.push_back(val);
    }
    EXPECT_EQ(values, std::vector<int>({ 1, 2 }));
}

// Тест удаления по позиции
TEST(ListTest, EraseByIndex) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);

    list.erase(1); // Удаляем элемент с индексом 1 (значение 2)

    std::vector<int> values;
    for (int val : list) {
        values.push_back(val);
    }
    EXPECT_EQ(values, std::vector<int>({ 1, 3, 4 }));
}

// Тест удаления узла
TEST(ListTest, EraseNode) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    // Находим узел со значением 2
    auto it = list.begin();
    ++it;

    list.erase(it.get_node());

    std::vector<int> values;
    for (int val : list) {
        values.push_back(val);
    }
    EXPECT_EQ(values, std::vector<int>({ 1, 3 }));
}

// Тест вставки после узла
TEST(ListTest, InsertAfterNode) {
    List<int> list;
    list.push_back(1);
    list.push_back(3);

    // Находим первый узел
    auto it = list.begin();

    // Вставляем 2 после первого узла
    list.insert_after(it.get_node(), 2);

    std::vector<int> values;
    for (int val : list) {
        values.push_back(val);
    }
    EXPECT_EQ(values, std::vector<int>({ 1, 2, 3 }));
}

// Тест конструктора копирования
TEST(ListTest, CopyConstructor) {
    List<int> original;
    original.push_back(1);
    original.push_back(2);
    original.push_back(3);

    List<int> copy(original);

    // Проверяем оригинал
    std::vector<int> orig_values;
    for (int val : original) {
        orig_values.push_back(val);
    }
    EXPECT_EQ(orig_values, std::vector<int>({ 1, 2, 3 }));

    // Проверяем копию
    std::vector<int> copy_values;
    for (int val : copy) {
        copy_values.push_back(val);
    }
    EXPECT_EQ(copy_values, std::vector<int>({ 1, 2, 3 }));
}

// Тест исключений
TEST(ListTest, Exceptions) {
    List<int> list;

    // Попытка удалить из пустого списка
    EXPECT_THROW(list.pop_front(), std::logic_error);
    EXPECT_THROW(list.pop_back(), std::logic_error);

    // Попытка вставить по неверной позиции в пустом списке
    EXPECT_THROW(list.insert(5, 42), std::logic_error);

    // Добавляем элемент и проверяем вставку по неверной позиции
    list.push_back(1);
    EXPECT_THROW(list.insert(5, 42), std::logic_error);

    // Проверяем удаление по неверной позиции
    EXPECT_THROW(list.erase(5), std::logic_error);
}

// Тест работы с итераторами
TEST(ListTest, IteratorOperations) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    // Проверка чтения через итератор
    auto it = list.begin();
    EXPECT_EQ(*it, 10);

    // Проверка инкремента
    ++it;
    EXPECT_EQ(*it, 20);

    // Проверка записи через итератор
    *it = 25;
    EXPECT_EQ(*it, 25);

    // Проверка постинкремента
    auto old_it = it++;
    EXPECT_EQ(*old_it, 25);
    EXPECT_EQ(*it, 30);

    // Проверка операторов сравнения
    auto it1 = list.begin();
    auto it2 = list.begin();
    EXPECT_TRUE(it1 == it2);

    ++it1;
    EXPECT_TRUE(it1 != it2);
}

// Тест разных типов данных
TEST(ListTest, DifferentDataTypes) {
    // Тест со строками
    List<std::string> str_list;
    str_list.push_back("hello");
    str_list.push_back("world");

    std::vector<std::string> values;
    for (const auto& val : str_list) {
        values.push_back(val);
    }
    EXPECT_EQ(values, std::vector<std::string>({ "hello", "world" }));

    // Тест с числами с плавающей точкой
    List<double> double_list;
    double_list.push_back(1.1);
    double_list.push_back(2.2);
    double_list.push_back(3.3);

    auto it = double_list.begin();
    EXPECT_DOUBLE_EQ(*it, 1.1);
    ++it;
    EXPECT_DOUBLE_EQ(*it, 2.2);
}

// Тест последовательных операций
TEST(ListTest, SequenceOfOperations) {
    List<int> list;

    // Добавляем элементы
    list.push_front(2);
    list.push_back(3);
    list.push_front(1);

    // Проверяем состояние
    std::vector<int> values;
    for (int val : list) {
        values.push_back(val);
    }
    EXPECT_EQ(values, std::vector<int>({ 1, 2, 3 }));

    // Удаляем из конца
    list.pop_back();
    values.clear();
    for (int val : list) {
        values.push_back(val);
    }
    EXPECT_EQ(values, std::vector<int>({ 1, 2 }));

    // Вставляем в середину
    list.insert(1, 99);
    values.clear();
    for (int val : list) {
        values.push_back(val);
    }
    EXPECT_EQ(values, std::vector<int>({ 1, 99, 2 }));

    // Очищаем через удаление всех элементов
    while (!list.is_empty()) {
        list.pop_front();
    }
    EXPECT_TRUE(list.is_empty());
}

// Тест метода clear
TEST(ListTest, ClearMethod) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    EXPECT_FALSE(list.is_empty());

    // Явно вызываем clear (если он есть) или очищаем вручную
    // В вашем List нет метода clear, но можно очистить вручную:
    while (!list.is_empty()) {
        list.pop_front();
    }

    EXPECT_TRUE(list.is_empty());
}

// Тест вставки в начало через insert
TEST(ListTest, InsertAtFront) {
    List<int> list;
    list.push_back(2);
    list.push_back(3);

    list.insert(0, 1); // Вставляем в начало

    std::vector<int> values;
    for (int val : list) {
        values.push_back(val);
    }
    EXPECT_EQ(values, std::vector<int>({ 1, 2, 3 }));
}

// Тест вставки в конец через insert
TEST(ListTest, InsertAtEnd) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);

    list.insert(2, 3); // Вставляем в конец (позиция равна размеру списка)

    std::vector<int> values;
    for (int val : list) {
        values.push_back(val);
    }
    EXPECT_EQ(values, std::vector<int>({ 1, 2, 3 }));
}

// Тест нескольких последовательных удалений
TEST(ListTest, MultipleDeletions) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);

    // Удаляем несколько элементов
    list.pop_front();
    list.erase(1); // Удаляем элемент с индексом 1 (теперь это 3)

    std::vector<int> values;
    for (int val : list) {
        values.push_back(val);
    }
    EXPECT_EQ(values, std::vector<int>({ 2, 4 }));
}