#include <gtest/gtest.h>
#include "..\lib_TVector\TVector.h"
#include "..\lib_Uns_TableT\Uns_TableT.h"


TEST(TestUnsTable, the_exception_is_when_insert_not_a_unique_key) {
    Uns_TableT<int, std::string> t1;

    t1.insert(1, "First");
    t1.insert(2, "Second");
    t1.insert(3, "Third");

    ASSERT_ANY_THROW(t1.insert(3, "Third"));
}

TEST(TestUnsTable, check_the_insert_after_erase) {
    Uns_TableT<int, std::string> t1;

    t1.insert(1, "First");
    t1.insert(2, "Second");
    t1.insert(3, "Third");
    t1.erase(2);
    t1.insert(4, "Fourth");

    auto* val = t1.find(4);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(*val, "Fourth");
}

TEST(TestUnsTable, check_the_erase) {
    Uns_TableT<int, std::string> t1;

    t1.insert(5, "Five");
    t1.insert(1, "First");
    t1.insert(3, "Third");
    t1.insert(7, "Seven");
    t1.insert(2, "Second");
    t1.insert(4, "Four");

    t1.erase(7);
    EXPECT_EQ(t1.find(7), nullptr);

    t1.erase(5);
    EXPECT_EQ(t1.find(5), nullptr);

    auto* p2 = t1.find(2);
    auto* p1 = t1.find(1);
    auto* p3 = t1.find(3);
    auto* p4 = t1.find(4);
    ASSERT_NE(p2, nullptr);
    ASSERT_NE(p1, nullptr);
    ASSERT_NE(p3, nullptr);
    ASSERT_NE(p4, nullptr);
    std::string s = *p2 + *p1 + *p3 + *p4;
    EXPECT_EQ(s, "SecondFirstThirdFour");
}

TEST(TestUnsTable, the_exception_is_when_deleting_by_a_key_that_does_not_exist) {
    Uns_TableT<int, std::string> t1;

    t1.insert(1, "First");
    t1.insert(2, "Second");
    t1.insert(3, "Third");

    ASSERT_ANY_THROW(t1.erase(5));
}

TEST(TestUnsTable, check_the_key_find) {
    Uns_TableT<std::string, std::string> t1;

    t1.insert("r123", "what");
    t1.insert("r567", "where");
    t1.insert("r974", "when");

    auto* val = t1.find("r974");
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(*val, "when");
}

TEST(TestUnsTable, the_exception_is_when_the_key_is_not_found) {
    Uns_TableT<std::string, std::string> t1;

    t1.insert("r123", "what");
    t1.insert("r567", "where");
    t1.insert("r974", "when");

    EXPECT_EQ(t1.find("r1024"), nullptr);
}

TEST(TestUnsTable, check_an_empty_table) {
    Uns_TableT<double, std::string> t1;

    t1.insert(1.5, "it is double");
    t1.erase(1.5);

    EXPECT_TRUE(t1.is_empty());
}

TEST(TestUnsTable, check_a_non_empty_table) {
    Uns_TableT<double, std::string> t1;

    t1.insert(1.5, "it is double");

    EXPECT_FALSE(t1.is_empty());
}