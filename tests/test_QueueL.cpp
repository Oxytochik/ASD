#include <gtest/gtest.h>
#include <initializer_list>
#include "../lib_queue/queue.h"

TEST(QueueListTest, DefaultConstructor) {
    Queue<int> queue;
    EXPECT_TRUE(queue.is_empty());
    EXPECT_FALSE(queue.is_full());
}

TEST(QueueListTest, ConstructorWithCapacity) {
    Queue<int> queue(5);
    EXPECT_TRUE(queue.is_empty());
    EXPECT_FALSE(queue.is_full());
}

TEST(QueueListTest, ConstructorInvalidCapacity) {
    EXPECT_THROW(Queue<int> queue(0), std::logic_error);
    EXPECT_THROW(Queue<int> queue(-5), std::logic_error);
}

TEST(QueueListTest, CopyConstructor) {
    Queue<int> original;
    original.push(1);
    original.push(2);
    original.push(3);

    Queue<int> copy(original);

    EXPECT_FALSE(copy.is_empty());
    EXPECT_EQ(copy.head(), 1);
    // В вашей реализации List нет get_count(), убираем эту проверку
}

TEST(QueueListTest, Push) {
    Queue<int> queue(3);

    queue.push(1);
    EXPECT_EQ(queue.head(), 1);

    queue.push(2);
    EXPECT_EQ(queue.head(), 1);

    queue.push(3);
    EXPECT_TRUE(queue.is_full());
}

TEST(QueueListTest, Pop) {
    Queue<int> queue;
    queue.push(1);
    queue.push(2);
    queue.push(3);

    EXPECT_EQ(queue.head(), 1);
    queue.pop();
    EXPECT_EQ(queue.head(), 2);
    queue.pop();
    EXPECT_EQ(queue.head(), 3);
    queue.pop();
    EXPECT_TRUE(queue.is_empty());
}

TEST(QueueListTest, Head) {
    Queue<int> queue;
    queue.push(10);
    EXPECT_EQ(queue.head(), 10);

    queue.push(20);
    EXPECT_EQ(queue.head(), 10);

    queue.pop();
    EXPECT_EQ(queue.head(), 20);
}

TEST(QueueListTest, IsEmpty) {
    Queue<int> queue;
    EXPECT_TRUE(queue.is_empty());

    queue.push(1);
    EXPECT_FALSE(queue.is_empty());

    queue.pop();
    EXPECT_TRUE(queue.is_empty());
}

TEST(QueueListTest, IsFull) {
    Queue<int> queue(2);
    EXPECT_FALSE(queue.is_full());

    queue.push(1);
    EXPECT_FALSE(queue.is_full());

    queue.push(2);
    EXPECT_TRUE(queue.is_full());

    queue.pop();
    EXPECT_FALSE(queue.is_full());
}

TEST(QueueListTest, Clear) {
    Queue<int> queue;
    queue.push(1);
    queue.push(2);
    queue.push(3);

    EXPECT_FALSE(queue.is_empty());
    queue.clear();
    EXPECT_TRUE(queue.is_empty());
    // В вашей реализации List нет get_count(), убираем эту проверку
}

TEST(QueueListTest, HeadEmptyQueue) {
    Queue<int> queue;
    EXPECT_THROW(queue.head(), std::logic_error);
}

TEST(QueueListTest, PushFullQueue) {
    Queue<int> queue(2);
    queue.push(1);
    queue.push(2);

    EXPECT_THROW(queue.push(3), std::logic_error);
}

TEST(QueueListTest, SequenceOfOperations) {
    Queue<int> queue(5);

    queue.push(10);
    queue.push(20);
    queue.push(30);

    EXPECT_EQ(queue.head(), 10);

    queue.pop();
    EXPECT_EQ(queue.head(), 20);

    queue.push(40);

    queue.clear();
    EXPECT_TRUE(queue.is_empty());
}