
#include <gtest/gtest.h>
#include <initializer_list>
#include "../lib_Queue/Queue.h"
//реализация конструктора - не корректна, добавить запас
TEST(QueueArrayTest, DefaultConstructor) {
	Queue<int> q;
	EXPECT_TRUE(q.is_empty());
	EXPECT_FALSE(q.is_full());
	EXPECT_EQ(q.get_count(), 0);
}

TEST(QueueArrayTest, ConstructorWithCapacity) {
	Queue<int> q(5);
	EXPECT_TRUE(q.is_empty());
	EXPECT_FALSE(q.is_full());
	EXPECT_EQ(q.get_capacity(), 5);
	EXPECT_EQ(q.get_count(), 0);
}

TEST(QueueArrayTest, ConstructorWithZeroCapacity) {
	EXPECT_THROW(Queue<int> q(0), std::logic_error);
}

TEST(QueueArrayTest, ConstructorWithNegativeCapacity) {
	EXPECT_THROW(Queue<int> q(-5), std::logic_error);
}

TEST(QueueArrayTest, ConstructorWithInitializerList) {
	Queue<int> q({ 1, 2, 3, 4, 5 });
	EXPECT_FALSE(q.is_empty());
	EXPECT_EQ(q.head(), 1);
	EXPECT_EQ(q.tail(), 5);
	EXPECT_EQ(q.get_count(), 5);
}

TEST(QueueArrayTest, CopyConstructor) {
	Queue<int> original({ 1, 2, 3 });
	Queue<int> copy(original);

	EXPECT_EQ(original.head(), copy.head());
	EXPECT_EQ(original.tail(), copy.tail());
	EXPECT_EQ(original.get_count(), copy.get_count());
	EXPECT_FALSE(copy.is_empty());
}

TEST(QueueArrayTest, PushOperation) {
	Queue<int> q(3);

	q.push(1);
	EXPECT_FALSE(q.is_empty());
	EXPECT_EQ(q.head(), 1);
	EXPECT_EQ(q.tail(), 1);
	EXPECT_EQ(q.get_count(), 1);

	q.push(2);
	EXPECT_EQ(q.head(), 1);
	EXPECT_EQ(q.tail(), 2);
	EXPECT_EQ(q.get_count(), 2);

	q.push(3);
	EXPECT_EQ(q.head(), 1);
	EXPECT_EQ(q.tail(), 3);
	EXPECT_TRUE(q.is_full());
	EXPECT_EQ(q.get_count(), 3);
}

TEST(QueueArrayTest, PushToFullQueue) {
	Queue<int> q(2);
	q.push(1);
	q.push(2);

	EXPECT_THROW(q.push(3), std::logic_error);
}

TEST(QueueArrayTest, PopOperation) {
	Queue<int> q({ 1, 2, 3, 4, 5 });

	EXPECT_EQ(q.head(), 1);
	q.pop();
	EXPECT_EQ(q.head(), 2);
	EXPECT_EQ(q.get_count(), 4);

	q.pop();
	EXPECT_EQ(q.head(), 3);
	EXPECT_EQ(q.get_count(), 3);

	q.pop();
	EXPECT_EQ(q.head(), 4);
	EXPECT_EQ(q.get_count(), 2);

	q.pop();
	EXPECT_EQ(q.head(), 5);
	EXPECT_EQ(q.get_count(), 1);

	q.pop();
	EXPECT_TRUE(q.is_empty());
	EXPECT_EQ(q.get_count(), 0);
}

TEST(QueueArrayTest, PopFromEmptyQueue) {
	Queue<int> q;
	EXPECT_THROW(q.pop(), std::logic_error);
}

TEST(QueueArrayTest, HeadAndTailOperations) {
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

TEST(QueueArrayTest, HeadFromEmptyQueue) {
	Queue<int> q;
	EXPECT_THROW(q.head(), std::logic_error);
}

TEST(QueueArrayTest, TailFromEmptyQueue) {
	Queue<int> q;
	EXPECT_THROW(q.tail(), std::logic_error);
}

TEST(QueueArrayTest, IsEmpty) {
	Queue<int> q;
	EXPECT_TRUE(q.is_empty());

	q.push(1);
	EXPECT_FALSE(q.is_empty());

	q.pop();
	EXPECT_TRUE(q.is_empty());
}

TEST(QueueArrayTest, IsFull) {
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

TEST(QueueArrayTest, ClearOperation) {
	Queue<int> q = { 1, 2, 3, 4, 5 };

	EXPECT_FALSE(q.is_empty());
	q.clear();
	EXPECT_TRUE(q.is_empty());
	EXPECT_EQ(q.get_count(), 0);

	q.push(10);
	EXPECT_EQ(q.head(), 10);
	EXPECT_EQ(q.tail(), 10);
	EXPECT_EQ(q.get_count(), 1);
}