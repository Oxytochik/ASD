#include <gtest/gtest.h>
#include "../lib_Uns_TableM/Uns_TableM.h"

TEST(TestUnsortedTableV, insert_updates_existing_key) {
    UnsortedTableV<int, std::string> t1;
    t1.insert(1, "First");
    t1.insert(2, "Second");
    t1.insert(3, "Third");

    t1.insert(2, "Updated");

    auto ptr = t1.find(2);
    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(*ptr, "Updated");
}

TEST(TestUnsortedTableV, check_the_insert_after_erase) {
    UnsortedTableV<int, std::string> t1;
    t1.insert(1, "First");
    t1.insert(2, "Second");
    t1.insert(3, "Third");
    t1.erase(2);
    t1.insert(4, "Fourth");

    auto ptr = t1.find(4);
    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(*ptr, "Fourth");
}

TEST(TestUnsortedTableV, check_the_erase) {
    UnsortedTableV<int, std::string> t1;
    t1.insert(1, "First");
    t1.insert(2, "Second");
    t1.insert(3, "Third");
    t1.erase(1);

    ASSERT_ANY_THROW(t1.find(1));
}

TEST(TestUnsortedTableV, erase_nonexistent_key_does_error) {
    UnsortedTableV<int, std::string> t1;
    t1.insert(1, "First");
    t1.insert(2, "Second");

    EXPECT_ANY_THROW(t1.erase(5));

    auto ptr = t1.find(1);
    EXPECT_EQ(*ptr, "First");
    ptr = t1.find(2);
    ASSERT_NE(ptr, nullptr);
}

TEST(TestUnsortedTableV, check_the_key_find) {
    UnsortedTableV<std::string, std::string> t1;
    t1.insert("r123", "what");
    t1.insert("r567", "where");
    t1.insert("r974", "when");

    auto ptr = t1.find("r974");
    EXPECT_EQ(*ptr, "when");
}

TEST(TestUnsortedTableV, find_returns_throw_for_missing_key) {
    UnsortedTableV<std::string, std::string> t1;
    t1.insert("r123", "what");
    t1.insert("r567", "where");
    t1.insert("r974", "when");

    EXPECT_ANY_THROW(t1.find("r1024"));
}

TEST(TestUnsortedTableV, check_an_empty_table) {
    UnsortedTableV<double, std::string> t1;
    t1.insert(1.5, "double");
    t1.erase(1.5);

    EXPECT_TRUE(t1.is_empty());
}

TEST(TestUnsortedTableV, check_a_non_empty_table) {
    UnsortedTableV<double, std::string> t1;
    t1.insert(1.5, "double");

    EXPECT_FALSE(t1.is_empty());
}
