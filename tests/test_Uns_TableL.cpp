#include <gtest/gtest.h>
#include "../lib_Uns_TableL/Uns_TableL.h"

TEST(TestUnsortedTableL, insert_updates_existing_key) {
    UnsortedTableL<int, std::string> table;
    table.insert(1, "First");
    table.insert(2, "Second");
    table.insert(3, "Third");

    table.insert(2, "Updated");

    auto ptr = table.find(2);
    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(*ptr, "Updated");
}

TEST(TestUnsortedTableL, check_the_insert_after_erase) {
    UnsortedTableL<int, std::string> t1;
    t1.insert(1, "First");
    t1.insert(2, "Second");
    t1.insert(3, "Third");
    t1.erase(2);
    t1.insert(4, "Fourth");

    auto ptr = t1.find(4);
    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(*ptr, "Fourth");
}

TEST(TestUnsortedTableL, check_the_erase) {
    UnsortedTableL<int, std::string> t1;
    t1.insert(1, "First");
    t1.insert(2, "Second");
    t1.insert(3, "Third");
    t1.erase(1);

    EXPECT_EQ(t1.find(1), nullptr);
}

TEST(TestUnsortedTableL, erase_nonexistent_key_does_nothing) {
    UnsortedTableL<int, std::string> t1;
    t1.insert(1, "First");
    t1.insert(2, "Second");

    EXPECT_NO_THROW(t1.erase(5));

    auto ptr = t1.find(1);
    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(*ptr, "First");
    ptr = t1.find(2);
    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(*ptr, "Second");
}

TEST(TestUnsortedTableL, check_the_key_find) {
    UnsortedTableL<std::string, std::string> t1;
    t1.insert("r123", "what");
    t1.insert("r567", "where");
    t1.insert("r974", "when");

    auto ptr = t1.find("r974");
    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(*ptr, "when");
}

TEST(TestUnsortedTableL, find_returns_nullptr_for_missing_key) {
    UnsortedTableL<std::string, std::string> t1;
    t1.insert("r123", "what");
    t1.insert("r567", "where");
    t1.insert("r974", "when");

    EXPECT_EQ(t1.find("r1024"), nullptr);
}

TEST(TestUnsortedTableL, check_an_empty_table) {
    UnsortedTableL<double, std::string> t1;
    t1.insert(1.5, "it is double");
    t1.erase(1.5);

    EXPECT_TRUE(t1.isEmpty());
}

TEST(TestUnsortedTableL, check_a_non_empty_table) {
    UnsortedTableL<double, std::string> t1;
    t1.insert(1.5, "it is double");

    EXPECT_FALSE(t1.isEmpty());
}