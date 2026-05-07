#include <gtest/gtest.h>
#include "../lib_TableM/TableM.h"

TEST(TestSTableV, insert_updates_existing_key) {
    STableV<int, std::string> t1;
    t1.insert(3, "Third");
    t1.insert(1, "First");
    t1.insert(2, "Second");

    t1.insert(2, "Updated");

    auto ptr = t1.find(2);
    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(*ptr, "Updated");
}

TEST(TestSTableV, check_the_insert_after_erase) {
    STableV<int, std::string> t1;
    t1.insert(3, "Third");
    t1.insert(1, "First");
    t1.insert(2, "Second");
    t1.erase(2);
    t1.insert(4, "Fourth");

    auto ptr = t1.find(4);
    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(*ptr, "Fourth");
}

TEST(TestSTableV, check_the_erase) {
    STableV<int, std::string> t1;
    t1.insert(3, "Third");
    t1.insert(1, "First");
    t1.insert(2, "Second");
    t1.erase(1);

    EXPECT_EQ(t1.find(1), nullptr);
}

TEST(TestSTableV, erase_nonexistent_key_does_nothing) {
    STableV<int, std::string> t1;
    t1.insert(3, "Third");
    t1.insert(1, "First");

    EXPECT_NO_THROW(t1.erase(5));

    auto ptr = t1.find(1);
    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(*ptr, "First");
    ptr = t1.find(3);
    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(*ptr, "Third");
}

TEST(TestSTableV, check_the_key_find) {
    STableV<std::string, std::string> t1;
    t1.insert("r567", "where");
    t1.insert("r123", "what");
    t1.insert("r974", "when");

    auto ptr = t1.find("r974");
    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(*ptr, "when");
}

TEST(TestSTableV, find_returns_nullptr_for_missing_key) {
    STableV<std::string, std::string> t1;
    t1.insert("r123", "what");
    t1.insert("r567", "where");
    t1.insert("r974", "when");

    EXPECT_EQ(t1.find("r1024"), nullptr);
}

TEST(TestSTableV, check_an_empty_table) {
    STableV<double, std::string> t1;
    t1.insert(1.5, "it is double");
    t1.erase(1.5);

    EXPECT_TRUE(t1.is_empty());
}

TEST(TestSTableV, check_a_non_empty_table) {
    STableV<double, std::string> t1;
    t1.insert(1.5, "it is double");

    EXPECT_FALSE(t1.is_empty());
}

TEST(TestSTableV, check_the_table_for_sorting) {
    STableV<std::string, std::string> t1;
    t1.insert("pos3", "Third");
    t1.insert("pos2", "Second");
    t1.insert("pos1", "First");

    // Проверяем, что все ключи доступны (сортировка не должна ломать поиск)
    auto ptr = t1.find("pos3");
    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(*ptr, "Third");
    ptr = t1.find("pos2");
    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(*ptr, "Second");
    ptr = t1.find("pos1");
    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(*ptr, "First");
}