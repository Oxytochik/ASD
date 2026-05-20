#include "..\lib_SkipList\Skip_list.h"

#include <gtest/gtest.h>

TEST(TestSkipList, check_the_print) {
    SkipList<int, std::string> list;

    list.insert(3, "three");
    list.print();
    list.insert(5, "five");
    list.print();
    list.insert(1, "one");
    list.print();
    list.insert(7, "seven");
    list.print();
    list.insert(9, "nine");
    list.print();
    list.insert(0, "zero");
    list.print();
    list.insert(11, "eleven");
    list.print();
    list.insert(6, "six");
    list.print();
}