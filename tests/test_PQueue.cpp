#include <gtest/gtest.h>
#include <sstream>
#include "..\lib_PQueue\PQueue.h"
#include "..\lib_TVector\TVector.h"


TEST(TestPriorityQueue, check_correct_order_of_most_important) {
    TVector<std::pair<std::string, int>> data({
        {"Vasily", 2},
        {"Leonid", 1},
        {"Petya", 4},
        {"Ivan", 1},
        {"Vasya", 3},
        {"Vasilisa", 2} });

    TVector<std::string> res = find_most_important_k(data, 5);
    //for (int i = 0; i < res.size(); i++) {
    //    std::cout << res[i] << " ";
    //}
    //std::cout << std::endl;

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    for (int i = 0; i < res.size(); i++) {
        std::cout << res[i] << " ";
    }
    std::cout.rdbuf(old);
    EXPECT_EQ(buffer.str(), "Leonid Ivan Vasily Vasilisa Vasya ");
}

TEST(TestPriorityQueue, the_exception_is_when_queue_is_empty) {
    TVector<std::pair<std::string, int>> data;
    PriorityQueue<std::string> q(data);

    ASSERT_ANY_THROW(q.top());
    EXPECT_TRUE(q.is_empty());
}

TEST(TestPriorityQueue, check_correct_order_of_print_most_important) {
    TVector<std::pair<std::string, int>> data({
        {"Vasily", 2},
        {"Leonid", 1},
        {"Petya", 4},
        {"Ivan", 1},
        {"Vasya", 3},
        {"Vasilisa", 2} });

    data.push_back({ "Maria", 0 });

    //print_most_important_k(data, 4);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    print_most_important_k(data, 4);
    std::cout.rdbuf(old);
    EXPECT_EQ(buffer.str(), "Maria(0) Leonid(1) Ivan(1) Vasily(2) \n");
}