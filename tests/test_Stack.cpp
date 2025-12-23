#include <gtest/gtest.h>
#include "../lib_Stack/stack.h"


TEST(StackTest, BasedConstructor) {
	Stack<int> tested_Stack;
	EXPECT_EQ(tested_Stack.is_empty(), true);
	EXPECT_EQ(tested_Stack.is_full(), false);

}

TEST(StackTest, SizeConstructor) {
	Stack<int> tested_Stack(5);
	EXPECT_EQ(tested_Stack.is_empty(), true);
	EXPECT_EQ(tested_Stack.is_full(), false);
}

TEST(StackTest, Copy_TVectorConstructor) {
	TVector<int> tested_vector{ 1,2,3 };
	Stack<int> tested_Stack(tested_vector);
	EXPECT_EQ(tested_vector.back(), tested_Stack.top());
	tested_Stack.pop();
	EXPECT_EQ(tested_vector[1], tested_Stack.top());
	tested_Stack.pop();
	EXPECT_EQ(tested_vector[0], tested_Stack.top());
	
}

TEST(StackTest, InitializerConstructor) {
	Stack<int> tested_Stack{ 1,2,3 };
	EXPECT_EQ(3, tested_Stack.top());
	tested_Stack.pop();
	EXPECT_EQ(2, tested_Stack.top());
	tested_Stack.pop();
	EXPECT_EQ(1, tested_Stack.top());
}

TEST(StackTest, CopyConstructor) {
	Stack<int> a{ 1,2,3 };
	Stack<int> tested_Stack(a);
	EXPECT_EQ(a.top(), tested_Stack.top());
	tested_Stack.pop();
	a.pop();
	EXPECT_EQ(a.top(), tested_Stack.top());
	tested_Stack.pop();
	a.pop();
	EXPECT_EQ(a.top(), tested_Stack.top());
}

TEST(StackTest, Push) {
	Stack<int> er{ 1,2 };
	//ASSERT_ANY_THROW(er.push(1));
	Stack<int> tested_Stack(3);
	for (int i = 0; i < 3; i++) {
		tested_Stack.push(i);
		EXPECT_EQ(tested_Stack.top(), i);
	}
	
}

TEST(StackTest, Pop) {
	Stack<int> er(2);
	ASSERT_ANY_THROW(er.pop());
	Stack<int> tested_Stack{ 1,2,3 };
	for (int i = 0; i < 3;i++) {
		EXPECT_EQ(tested_Stack.top(), 3 - i);
		tested_Stack.pop();
	}
}

TEST(StackTest, Top) {
	Stack<int> er(2);
	ASSERT_ANY_THROW(er.top());
	Stack<int> tested_Stack{ 1,2,3 };
	EXPECT_EQ(tested_Stack.top(), 3);
}

TEST(StackTest, Empty) {
	Stack<int> tested_Stack(2);
	EXPECT_TRUE(tested_Stack.is_empty());
	Stack<int> a{ 1,2 };
	EXPECT_FALSE(a.is_empty());
}

TEST(StackTest, Full) {
	Stack<int> tested_Stack(1);
	tested_Stack.push(1);

	//Stack<int> tested_Stack{ 1,2,3 };
	//for (int i = 0; i < 15;i++) {
	//	tested_Stack.push(i);
	//}
	EXPECT_TRUE(tested_Stack.is_full());
	Stack<int> a(2);
	EXPECT_FALSE(a.is_full());
}

TEST(StackTest, Clear) {
	Stack<int> tested_Stack{ 1,2,3 };
	tested_Stack.clear();
	EXPECT_TRUE(tested_Stack.is_empty());
}