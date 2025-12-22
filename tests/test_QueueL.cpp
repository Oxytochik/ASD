#include <gtest/gtest.h>
#include <initializer_list>
#include "../lib_QueueL/queuel.h"

TEST(QueueListTest, DefaultConstructor) {
    Queue<int> q;
    EXPECT_TRUE(q.is_empty());
    EXPECT_FALSE(q.is_full());
}

TEST(QueueListTest, ConstructorWithCapacity) {
    Queue<int> q(5);
    EXPECT_TRUE(q.is_empty());
    EXPECT_FALSE(q.is_full());
}

TEST(QueueListTest, ConstructorWithZeroCapacity) {
    EXPECT_THROW(Queue<int> q(0), std::logic_error);
}

TEST(QueueListTest, ConstructorWithInitializerList) {
    Queue<int> q({ 1, 2, 3, 4, 5 });
    EXPECT_FALSE(q.is_empty());
    EXPECT_EQ(q.head(), 1);
    EXPECT_EQ(q.tail(), 5);
}

TEST(QueueListTest, CopyConstructor) {
    Queue<int> original({ 1, 2, 3 });
    Queue<int> copy(original);

    EXPECT_EQ(original.head(), copy.head());
    EXPECT_EQ(original.tail(), copy.tail());
    EXPECT_FALSE(copy.is_empty());
}

TEST(QueueListTest, BasicOperations) {
    Queue<int> q;
    EXPECT_TRUE(q.is_empty());

    q.push(1);
    EXPECT_EQ(q.head(), 1);
    EXPECT_EQ(q.tail(), 1);

    q.push(2);
    EXPECT_EQ(q.head(), 1);
    EXPECT_EQ(q.tail(), 2);

    q.push(3);
    EXPECT_EQ(q.head(), 1);
    EXPECT_EQ(q.tail(), 3);

    q.pop();
    EXPECT_EQ(q.head(), 2);
    EXPECT_EQ(q.tail(), 3);

    q.pop();
    EXPECT_EQ(q.head(), 3);
    EXPECT_EQ(q.tail(), 3);

    q.pop();
    EXPECT_TRUE(q.is_empty());
}

TEST(QueueListTest, PushToFullQueue) {
    Queue<int> q(2);
    q.push(1);
    q.push(2);

    EXPECT_THROW(q.push(3), std::logic_error);
}

TEST(QueueListTest, PopFromEmptyQueue) {
    Queue<int> q;
    EXPECT_THROW(q.pop(), std::logic_error);
}

TEST(QueueListTest, HeadAndTailOperations) {
    Queue<int> q({ 10, 20, 30 });

    EXPECT_EQ(q.head(), 10);
    EXPECT_EQ(q.tail(), 30);

    q.pop();
    EXPECT_EQ(q.head(), 20);
    EXPECT_EQ(q.tail(), 30);

    q.push(40);
    EXPECT_EQ(q.head(), 20);
    EXPECT_EQ(q.tail(), 40);

    q.pop();
    EXPECT_EQ(q.head(), 30);
    EXPECT_EQ(q.tail(), 40);
}

TEST(QueueListTest, HeadFromEmptyQueue) {
    Queue<int> q;
    EXPECT_THROW(q.head(), std::logic_error);
}

TEST(QueueListTest, TailFromEmptyQueue) {
    Queue<int> q;
    EXPECT_THROW(q.tail(), std::logic_error);
}

TEST(QueueListTest, IsEmpty) {
    Queue<int> q;
    EXPECT_TRUE(q.is_empty());

    q.push(1);
    EXPECT_FALSE(q.is_empty());

    q.pop();
    EXPECT_TRUE(q.is_empty());
}

TEST(QueueListTest, IsFull) {
    Queue<int> q(3);

    EXPECT_FALSE(q.is_full());
    q.push(1);
    EXPECT_FALSE(q.is_full());
    q.push(2);
    EXPECT_FALSE(q.is_full());
    q.push(3);
    EXPECT_TRUE(q.is_full());

    q.pop();
    EXPECT_FALSE(q.is_full());
}

TEST(QueueListTest, ClearOperation) {
    Queue<int> q = { 1, 2, 3, 4, 5 };

    EXPECT_FALSE(q.is_empty());
    q.clear();
    EXPECT_TRUE(q.is_empty());

    q.push(10);
    EXPECT_EQ(q.head(), 10);
    EXPECT_EQ(q.tail(), 10);
}

TEST(QueueListTest, MixedOperations) {
    Queue<int> q(10);

    for (int i = 1; i <= 5; i++) {
        q.push(i);
    }

    EXPECT_EQ(q.head(), 1);
    EXPECT_EQ(q.tail(), 5);

    q.pop();
    q.pop();

    EXPECT_EQ(q.head(), 3);
    EXPECT_EQ(q.tail(), 5);

    q.push(6);
    q.push(7);

    EXPECT_EQ(q.head(), 3);
    EXPECT_EQ(q.tail(), 7);

    q.clear();
    EXPECT_TRUE(q.is_empty());

    q.push(100);
    EXPECT_EQ(q.head(), 100);
    EXPECT_EQ(q.tail(), 100);
}

TEST(QueueListTest, LargeNumberOfElements) {
    Queue<int> q(1000);

    for (int i = 0; i < 500; i++) {
        q.push(i);
    }

    EXPECT_EQ(q.head(), 0);
    EXPECT_EQ(q.tail(), 499);

    for (int i = 0; i < 250; i++) {
        q.pop();
    }

    EXPECT_EQ(q.head(), 250);
    EXPECT_EQ(q.tail(), 499);
}