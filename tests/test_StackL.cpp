#include <gtest/gtest.h>
#include <initializer_list>
#include "../lib_StackL/stackl.h"


TEST(StackListTest, DefaultConstructor) {
    Stack<int> stack;
    EXPECT_TRUE(stack.is_empty());
    EXPECT_FALSE(stack.is_full());
    EXPECT_EQ(stack.capacity(), 100);  // Проверяем вместимость
}

TEST(StackListTest, ConstructorWithCapacity) {
    Stack<int> stack(5);
    EXPECT_TRUE(stack.is_empty());
    EXPECT_FALSE(stack.is_full());
    EXPECT_EQ(stack.capacity(), 5);  // Проверяем вместимость
}

TEST(StackListTest, CopyConstructor) {
    Stack<int> original;
    original.push(1);
    original.push(2);
    original.push(3);

    Stack<int> copy(original);
    EXPECT_FALSE(copy.is_empty());
    EXPECT_EQ(copy.top(), 3);
    EXPECT_EQ(original.top(), 3);
    EXPECT_EQ(copy.count(), 3);  // Проверяем количество элементов
}

TEST(StackListTest, Push) {
    Stack<int> stack(5);  // Ограничиваем вместимость для теста

    stack.push(10);
    EXPECT_FALSE(stack.is_empty());
    EXPECT_EQ(stack.top(), 10);

    stack.push(20);
    EXPECT_EQ(stack.top(), 20);

    stack.push(30);
    EXPECT_EQ(stack.top(), 30);
}

TEST(StackListTest, Pop) {
    Stack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);

    EXPECT_EQ(stack.top(), 3);
    stack.pop();
    EXPECT_EQ(stack.top(), 2);
    stack.pop();
    EXPECT_EQ(stack.top(), 1);
    stack.pop();
    EXPECT_TRUE(stack.is_empty());
}

TEST(StackListTest, Top) {
    Stack<int> stack;
    stack.push(5);
    EXPECT_EQ(stack.top(), 5);

    stack.push(15);
    EXPECT_EQ(stack.top(), 15);
}

TEST(StackListTest, IsEmpty) {
    Stack<int> stack;
    EXPECT_TRUE(stack.is_empty());

    stack.push(1);
    EXPECT_FALSE(stack.is_empty());

    stack.pop();
    EXPECT_TRUE(stack.is_empty());
}

TEST(StackListTest, IsFull) {
    Stack<int> stack(10);  // Ограничиваем вместимость 10 для теста
    EXPECT_FALSE(stack.is_full());

    for (int i = 0; i < 10; ++i) {
        stack.push(i);
        if (i < 9) {
            EXPECT_FALSE(stack.is_full());
        }
        else {
            EXPECT_TRUE(stack.is_full());  // На 10-м элементе стек должен быть полон
        }
    }
}

TEST(StackListTest, Clear) {
    Stack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);

    EXPECT_FALSE(stack.is_empty());
    stack.clear();
    EXPECT_TRUE(stack.is_empty());
}

TEST(StackListTest, PopEmptyStack) {
    Stack<int> stack;
    EXPECT_THROW(stack.pop(), std::logic_error);
}

TEST(StackListTest, TopEmptyStack) {
    Stack<int> stack;
    EXPECT_THROW(stack.top(), std::logic_error);
}
