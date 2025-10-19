
#include <gtest/gtest.h>
#include <initializer_list>
#include "../lib_Queue/Queue.h"

TEST(QueueTest, BaseConstructor) {
	Queue<int> a;
	EXPECT_EQ(a.is_empty(), true);
	EXPECT_EQ(a.is_full(), true);
	ASSERT_ANY_THROW(a.head());
}

TEST(QueueTest, SizeConstructor) {
	Queue<int> a(5);
	EXPECT_EQ(a.is_empty(), true);
	EXPECT_EQ(a.is_full(), false);
	int result = 5;
	EXPECT_EQ(a.get_size(), result);
}

TEST(QueueTest, InitializerConstructor) {
	Queue<int> a{ 1, 2, 3, 5 };
	EXPECT_EQ(a.is_empty(), false);
	EXPECT_EQ(a.is_full(), true);
	EXPECT_EQ(a.get_size(), 4);
	EXPECT_EQ(a.head(), 1);
	EXPECT_EQ(a.tail(), 5);
}

TEST(QueueTest, CopyConstructor) {
	Queue<int> a{ 1,2,3 };
	Queue<int> copy(a);
	EXPECT_EQ(a.head(), copy.head());
	EXPECT_EQ(a.tail(), copy.tail());
}

TEST(QueueTest, getters) {
	Queue<int> a(3);
	EXPECT_EQ(a.get_size(), 3);
	Queue<int> b{ 1,2,3 };
	EXPECT_EQ(b.get_count(), 3);
	b.pop();
	EXPECT_EQ(b.get_count(), 2);
	EXPECT_EQ(b.get_size(), 3);
}

TEST(QueueTest, Push) {
	Queue<int> a;
	ASSERT_ANY_THROW(a.push(1));
	Queue<int> b(3);
	b.push(1);
	EXPECT_FALSE(b.is_empty());
	EXPECT_EQ(b.head(), 1);
	b.push(2);
	EXPECT_EQ(b.head(), 1);
	EXPECT_EQ(b.tail(), 2);
	b.push(3);
	EXPECT_TRUE(b.is_full());
	EXPECT_EQ(b.tail(), 3);

}

TEST(QueueTest, Pop) {
	Queue<int> a;
	ASSERT_ANY_THROW(a.pop());
	Queue<int> b{ 3,2,1 };
	EXPECT_EQ(b.head(), 3);
	for (int i = 0; i < 3;i++) {
		EXPECT_EQ(b.head(), 3 - i);
		b.pop();
	}
	EXPECT_TRUE(b.is_empty());
}

TEST(QueueTest, Head) {
	Queue<int> a{ 1, 2, 3 };

	EXPECT_EQ(a.head(), 1);
	a.pop();
	EXPECT_EQ(a.head(), 2);
	a.push(5);
	EXPECT_EQ(a.head(), 2);
}

TEST(QueueTest, Tail) {
	Queue<int> a{ 1, 2, 3 };

	EXPECT_EQ(a.tail(), 3);
	a.pop();
	EXPECT_EQ(a.tail(), 3);
	a.push(5);
	EXPECT_EQ(a.tail(), 5);

}

TEST(QueueTest, Empty) {
	Queue<int>a(3);
	EXPECT_TRUE(a.is_empty());
	a.push(1);
	EXPECT_FALSE(a.is_empty());
	Queue<int> b;
	EXPECT_TRUE(b.is_empty());
}
TEST(QueueTest, Full) {
	Queue<int> a(3);
	EXPECT_FALSE(a.is_full());
	for (int i = 0; i < a.get_size(); i++) {
		a.push(1);
	}
	EXPECT_TRUE(a.is_full());
	Queue<int> b{ 1,2,3 };
	EXPECT_TRUE(b.is_full());
}

TEST(QueueTest, Clear) {
	Queue<int> a{ 1,2,3 };

	EXPECT_FALSE(a.is_empty());
	a.clear();
	EXPECT_TRUE(a.is_empty());
}
