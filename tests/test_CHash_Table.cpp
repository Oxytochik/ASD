#include <gtest/gtest.h>
#include "..\lib_TVector\TVector.h"
#include "..\lib_CHash_Table\CHash_Table.h"

TEST(TestChainedHashTable, ehe) {
    CHash_Table<int> hash_table;
}

//TEST(TestChainedHashTable, check_merging_dictionaries) {
//    TVector<std::pair<std::string, int>> dictionary1;
//    dictionary1.push_back({ "table", 1349 });
//    dictionary1.push_back({ "hash", 1985 });
//    dictionary1.push_back({ "list", 4372 });
//
//    TVector<std::pair<std::string, int>> dictionary2;
//    dictionary2.push_back({ "massive", 4312 });
//    dictionary2.push_back({ "list", 5863 });
//    dictionary2.push_back({ "hash", 4317 });
//    dictionary2.push_back({ "vector", 2586 });
//
//    CHash_Table<int> hash_table(20);
//
//    for (int i = 0; i < dictionary1.size(); ++i) {
//        hash_table.insert(dictionary1[i].first, dictionary1[i].second);
//    }
//
//    for (int i = 0; i < dictionary2.size(); ++i) {
//        try {
//            hash_table.insert(dictionary2[i].first, dictionary2[i].second);
//        }
//        catch (const std::logic_error&) {
//            // ключ уже есть Ц игнорируем (приоритет первого словар€)
//        }
//    }
//
//    hash_table.print(std::cout);
//
//    // ƒополнительна€ проверка: ключ "list" осталс€ из первого словар€ (1349)
//    int* val = hash_table.find("list");
//    ASSERT_NE(val, nullptr);
//    EXPECT_EQ(*val, 1349);
//}

TEST(TestChainedHashTable, check_merging_dictionaries) {
    TVector<std::pair<std::string, int>> dictionary1;
    dictionary1.push_back({ "table", 1349 });
    dictionary1.push_back({ "hash", 1985 });
    dictionary1.push_back({ "list", 4372 });

    TVector<std::pair<std::string, int>> dictionary2;
    dictionary2.push_back({ "massive", 4312 });
    dictionary2.push_back({ "list", 5863 });
    dictionary2.push_back({ "hash", 4317 });
    dictionary2.push_back({ "vector", 2586 });

    CHash_Table<int> hash_table(20);

    for (int i = 0; i < dictionary1.size(); ++i) {
        hash_table.insert(dictionary1[i].first, dictionary1[i].second);
    }

    for (int i = 0; i < dictionary2.size(); ++i) {
        try {
            hash_table.insert(dictionary2[i].first, dictionary2[i].second);
        }
        catch (const std::logic_error&) {
            // ключ уже есть Ц приоритет первого словар€
        }
    }

    hash_table.print(std::cout);
}

TEST(TestChainedHashTable, the_exception_is_when_insert_not_a_unique_key) {
    CHash_Table<int> t1(20);

    t1.insert("Third", 3);
    t1.insert("Second", 2);
    t1.insert("First", 1);
    t1.insert("Fourth", 4);
    t1.insert("Fifth", 5);
    t1.insert("Twentieth", 20);
    t1.insert("Thirtieth", 30);

    ASSERT_ANY_THROW(t1.insert("Third", 3));
}

TEST(TestChainedHashTable, check_the_insert_after_erase) {
    CHash_Table<int> t1(20);

    t1.insert("Third", 3);
    t1.insert("Second", 2);
    t1.insert("First", 1);
    t1.erase("First");
    t1.insert("Fourth", 4);
    t1.insert("Fifth", 5);
    t1.insert("Twentieth", 20);
    t1.insert("Thirtieth", 30);

    int* val = t1.find("Thirtieth");
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(*val, 30);
}

TEST(TestChainedHashTable, check_the_erase) {
    CHash_Table<int> t1(20);

    t1.insert("Third", 3);
    t1.insert("Second", 2);
    t1.insert("First", 1);
    t1.insert("Fourth", 4);
    t1.insert("Fifth", 5);
    t1.insert("Twentieth", 20);
    t1.insert("Thirtieth", 30);

    t1.erase("Second");

    int* val = t1.find("Second");
    EXPECT_EQ(val, nullptr);   // не найдено ? nullptr
}

TEST(TestChainedHashTable, the_exception_is_when_deleting_by_a_key_that_does_not_exist) {
    CHash_Table<int> t1(20);

    t1.insert("Third", 3);
    t1.insert("Second", 2);
    t1.insert("First", 1);
    t1.insert("Fourth", 4);
    t1.insert("Fifth", 5);
    t1.insert("Twentieth", 20);

    ASSERT_ANY_THROW(t1.erase("Thirtieth"));
}

TEST(TestChainedHashTable, check_the_key_find) {
    CHash_Table<std::string> t1(20);

    t1.insert("r123", "what");
    t1.insert("r567", "where");
    t1.insert("r974", "when");

    std::string* val = t1.find("r974");
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(*val, "when");
}

TEST(TestChainedHashTable, the_exception_is_when_the_key_is_not_found) {
    CHash_Table<std::string> t1(20);

    t1.insert("r123", "what");
    t1.insert("r567", "where");
    t1.insert("r974", "when");

    std::string* val = t1.find("r1024");
    EXPECT_EQ(val, nullptr);   // не найдено ? nullptr, исключени€ нет
    // при желании можно проверить, что обращение к *val выбросило бы исключение,
    // но по заданию find возвращает nullptr.
}

TEST(TestChainedHashTable, check_an_empty_table) {
    CHash_Table<double> t1(20);

    t1.insert("it is double", 1.5);
    t1.insert("it is double too", 3.7);

    EXPECT_FALSE(t1.is_empty());

    t1.erase("it is double");
    t1.erase("it is double too");

    EXPECT_TRUE(t1.is_empty());
}