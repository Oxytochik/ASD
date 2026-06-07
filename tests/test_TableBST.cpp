#include <gtest/gtest.h>
#include "..\lib_TVector\TVector.h"
#include "..\lib_TableBST\TableBST.h"

TEST(TestSortedTable, the_exception_is_when_insert_not_a_unique_key) {
    Sorted_TableT<int, std::string> t1;

    t1.insert(1, "First");
    t1.insert(2, "Second");
    t1.insert(3, "Third");

    ASSERT_ANY_THROW(t1.insert(3, "Third"));
}

TEST(TestSortedTable, check_the_insert_after_erase) {
    Sorted_TableT<int, std::string> t1;

    t1.insert(3, "Third");
    t1.insert(1, "First");
    t1.insert(2, "Second");
    t1.erase(2);
    t1.insert(4, "Fourth");

    auto* val = t1.find(4);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(*val, "Fourth");
}

TEST(TestSortedTable, check_the_erase) {
    Sorted_TableT<int, std::string> t1;

    t1.insert(1, "First");
    t1.insert(2, "Second");
    t1.insert(3, "Third");
    t1.erase(1);

    EXPECT_EQ(t1.find(1), nullptr);
}

TEST(TestSortedTable, the_exception_is_when_deleting_by_a_key_that_does_not_exist) {
    Sorted_TableT<int, std::string> t1;

    t1.insert(1, "First");
    t1.insert(2, "Second");
    t1.insert(3, "Third");

    ASSERT_ANY_THROW(t1.erase(5));
}

TEST(TestSortedTable, check_the_table_for_sorting) {
    Sorted_TableT<std::string, std::string> t1;

    t1.insert("pos3", "Third");
    t1.insert("pos2", "Second");
    t1.insert("pos1", "First");

    auto* val = t1.find("pos3");
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(*val, "Third");
}

TEST(TestSortedTable, check_the_key_find) {
    Sorted_TableT<std::string, std::string> t1;

    t1.insert("r123", "what");
    t1.insert("r567", "where");
    t1.insert("r974", "when");

    auto* val = t1.find("r974");
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(*val, "when");
}

TEST(TestSortedTable, the_exception_is_when_the_key_is_not_found) {
    Sorted_TableT<std::string, std::string> t1;

    t1.insert("r123", "what");
    t1.insert("r567", "where");
    t1.insert("r974", "when");

    EXPECT_EQ(t1.find("r1024"), nullptr);   // не исключение, а nullptr
}

TEST(TestSortedTable, check_an_empty_table) {
    Sorted_TableT<double, std::string> t1;

    t1.insert(1.5, "it is double");
    t1.insert(3.7, "it is double too");

    EXPECT_FALSE(t1.is_empty());

    t1.erase(1.5);
    t1.erase(3.7);

    EXPECT_TRUE(t1.is_empty());
}