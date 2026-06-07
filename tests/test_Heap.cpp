#include <gtest/gtest.h>
#include "..\lib_TVector\TVector.h"
#include "..\lib_Heap\heap.h"

TEST(TestHeap, check_insert) {
    Heap<int> heap;
    heap.insert(7);
    heap.insert(6);
    heap.insert(5);
    heap.insert(4);
    heap.insert(3);
    heap.insert(3);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    heap.print();
    std::cout.rdbuf(old);
    // В выводе print нет пробела после последнего числа, только перевод строки
    EXPECT_EQ(buffer.str(), "3 4 3 7 5 6\n");
}

TEST(TestHeap, check_insert_with_random_generation) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 100);

    TVector<int> vec1;

    for (int i = 0; i < 10; ++i) {
        int random_num = dist(gen);
        vec1.push_back(random_num);
    }
    TVector<int> vec = sort(vec1);
    //sort(vec1, vec);


    bool is_sorted = true;
    for (int i = 0; i < vec.size() - 1; ++i) {
        if (vec[i] > vec[i + 1]) {
            is_sorted = false;
            break;
        }
    }
    EXPECT_TRUE(is_sorted);

    std::string s;
    for (int i = 0; i < vec.size(); ++i) {
        s += std::to_string(vec[i]);
        if (i < vec.size() - 1) s += " ";
    }
    std::cout << "Sorted values: " << s << std::endl;
}

TEST(TestHeap, check_pop) {
    Heap<int> heap;
    heap.insert(7);
    heap.insert(6);
    heap.insert(5);
    heap.insert(4);
    heap.insert(3);
    heap.insert(3);

    heap.pop();   // удаляем первый минимум (3)
    std::stringstream buffer1;
    std::streambuf* old = std::cout.rdbuf(buffer1.rdbuf());
    heap.print();
    std::cout.rdbuf(old);
    EXPECT_EQ(buffer1.str(), "3 4 6 7 5\n");

    heap.pop();   // удаляем следующий минимум (3)
    std::stringstream buffer2;
    old = std::cout.rdbuf(buffer2.rdbuf());
    heap.print();
    std::cout.rdbuf(old);
    EXPECT_EQ(buffer2.str(), "4 5 6 7\n");
}

TEST(TestHeap, the_exception_is_when_pop_from_empty_heap) {
    Heap<int> heap;
    ASSERT_ANY_THROW(heap.pop());
}

TEST(TestHeap, check_pyramid_sort) {
    TVector<int> vec1({ 7, 6, 5, 4, 8, 1 });
    TVector<int> vec = sort(vec1);
    //sort(vec1, vec);
    std::string s;
    for (int i = 0; i < vec.size(); ++i) {
        s += std::to_string(vec[i]) + " ";
    }
    EXPECT_EQ(s, "1 4 5 6 7 8 ");
}

TEST(TestHeap, check_clear_and_is_empty) {
    Heap<int> heap;
    heap.insert(7);
    heap.insert(6);
    heap.insert(5);
    heap.insert(4);
    heap.insert(3);
    heap.insert(3);
    heap.insert(8);

    EXPECT_FALSE(heap.is_empty());

    heap.clear();
    EXPECT_TRUE(heap.is_empty());
}