//#include <gtest/gtest.h>
////#include "../lib_stack/stack.h"
//#include "../lib_List/List.h"
//#include "../lib_StackL/stackl.h"
//// Ваш стек на основе List
//
//// Тест конструктора по умолчанию
//TEST(StackListTest, DefaultConstructor) {
//    Stack<int> stack;
//    EXPECT_TRUE(stack.is_empty());
//    EXPECT_FALSE(stack.is_full());
//}
//
//// Тест конструктора с параметром (вместимость)
//TEST(StackListTest, ConstructorWithCapacity) {
//    Stack<int> stack(5);  // Для List параметр игнорируется
//    EXPECT_TRUE(stack.is_empty());
//    EXPECT_FALSE(stack.is_full());
//}
//
//// Тест конструктора из List
//TEST(StackListTest, ConstructorFromList) {
//    List<int> list;
//    list.push_back(10);
//    list.push_back(20);
//    list.push_back(30);
//
//    Stack<int> stack(list);
//    EXPECT_FALSE(stack.is_empty());
//    EXPECT_EQ(stack.top(), 10);  // push_front добавляет в начало
//}
//
//// Тест конструктора копирования
//TEST(StackListTest, CopyConstructor) {
//    Stack<int> original;
//    original.push(1);
//    original.push(2);
//    original.push(3);
//
//    Stack<int> copy(original);
//
//    // Проверяем, что копия идентична оригиналу
//    EXPECT_FALSE(copy.is_empty());
//    EXPECT_EQ(copy.top(), 3);
//
//    // Удаляем из оригинала, копия не должна измениться
//    original.pop();
//    EXPECT_EQ(original.top(), 2);
//    EXPECT_EQ(copy.top(), 3);
//}
//
//// Тест добавления элементов
//TEST(StackListTest, Push) {
//    Stack<int> stack;
//
//    stack.push(10);
//    EXPECT_FALSE(stack.is_empty());
//    EXPECT_EQ(stack.top(), 10);
//
//    stack.push(20);
//    EXPECT_EQ(stack.top(), 20);
//
//    stack.push(30);
//    EXPECT_EQ(stack.top(), 30);
//}
//
//// Тест удаления элементов
//TEST(StackListTest, Pop) {
//    Stack<int> stack;
//    stack.push(1);
//    stack.push(2);
//    stack.push(3);
//
//    EXPECT_EQ(stack.top(), 3);
//    stack.pop();
//    EXPECT_EQ(stack.top(), 2);
//    stack.pop();
//    EXPECT_EQ(stack.top(), 1);
//    stack.pop();
//    EXPECT_TRUE(stack.is_empty());
//}
//
//// Тест получения вершины стека
//TEST(StackListTest, Top) {
//    Stack<int> stack;
//    stack.push(5);
//    EXPECT_EQ(stack.top(), 5);
//
//    stack.push(15);
//    EXPECT_EQ(stack.top(), 15);
//
//    stack.pop();
//    EXPECT_EQ(stack.top(), 5);
//}
//
//// Тест исключения при удалении из пустого стека
//TEST(StackListTest, PopEmptyStack) {
//    Stack<int> stack;
//    EXPECT_THROW(stack.pop(), std::logic_error);
//}
//
//// Тест исключения при получении вершины пустого стека
//TEST(StackListTest, TopEmptyStack) {
//    Stack<int> stack;
//    EXPECT_THROW(stack.top(), std::logic_error);
//}
//
//// Тест проверки пустоты стека
//TEST(StackListTest, IsEmpty) {
//    Stack<int> stack;
//    EXPECT_TRUE(stack.is_empty());
//
//    stack.push(1);
//    EXPECT_FALSE(stack.is_empty());
//
//    stack.pop();
//    EXPECT_TRUE(stack.is_empty());
//}
//
//// Тест проверки заполненности стека (всегда false для List)
//TEST(StackListTest, IsFull) {
//    Stack<int> stack;
//    EXPECT_FALSE(stack.is_full());  // Для List всегда false
//
//    // Добавляем несколько элементов
//    for (int i = 0; i < 5; ++i) {
//        stack.push(i);
//        EXPECT_FALSE(stack.is_full());
//    }
//}
//
//// Тест очистки стека
//TEST(StackListTest, Clear) {
//    Stack<int> stack;
//    stack.push(1);
//    stack.push(2);
//    stack.push(3);
//    EXPECT_FALSE(stack.is_empty());
//
//    stack.clear();
//    EXPECT_TRUE(stack.is_empty());
//
//    // После очистки можно снова использовать
//    stack.push(100);
//    EXPECT_EQ(stack.top(), 100);
//}
//
//// Тест последовательных операций
//TEST(StackListTest, SequenceOfOperations) {
//    Stack<int> stack;
//
//    // Добавляем элементы
//    stack.push(10);
//    stack.push(20);
//    stack.push(30);
//
//    EXPECT_EQ(stack.top(), 30);
//
//    // Удаляем и добавляем
//    stack.pop();
//    EXPECT_EQ(stack.top(), 20);
//
//    stack.push(40);
//    EXPECT_EQ(stack.top(), 40);
//
//    // Очищаем
//    stack.clear();
//    EXPECT_TRUE(stack.is_empty());
//
//    // Добавляем после очистки
//    stack.push(50);
//    EXPECT_EQ(stack.top(), 50);
//}
//
//// Тест с разными типами данных
//TEST(StackListTest, DifferentDataTypes) {
//    // Тест со строками
//    Stack<std::string> str_stack;
//    str_stack.push("hello");
//    str_stack.push("world");
//
//    EXPECT_EQ(str_stack.top(), "world");
//    str_stack.pop();
//    EXPECT_EQ(str_stack.top(), "hello");
//
//    // Тест с числами с плавающей точкой
//    Stack<double> double_stack;
//    double_stack.push(1.5);
//    double_stack.push(2.5);
//
//    EXPECT_DOUBLE_EQ(double_stack.top(), 2.5);
//    double_stack.pop();
//    EXPECT_DOUBLE_EQ(double_stack.top(), 1.5);
//}
//
//// Тест большого количества элементов
//TEST(StackListTest, LargeNumberOfElements) {
//    Stack<int> stack;
//
//    // Добавляем много элементов
//    for (int i = 0; i < 1000; ++i) {
//        stack.push(i);
//        EXPECT_EQ(stack.top(), i);
//        EXPECT_FALSE(stack.is_full());  // Всегда false
//    }
//
//    // Удаляем все элементы
//    for (int i = 999; i >= 0; --i) {
//        EXPECT_EQ(stack.top(), i);
//        stack.pop();
//    }
//
//    EXPECT_TRUE(stack.is_empty());
//}
//
//// Тест смешанных операций
//TEST(StackListTest, MixedOperations) {
//    Stack<int> stack(10);  // Параметр игнорируется
//
//    // Добавляем элементы
//    for (int i = 1; i <= 5; ++i) {
//        stack.push(i);
//    }
//
//    // Удаляем несколько
//    stack.pop();
//    stack.pop();
//
//    EXPECT_EQ(stack.top(), 3);
//
//    // Добавляем еще
//    stack.push(6);
//    stack.push(7);
//
//    EXPECT_EQ(stack.top(), 7);
//
//    // Очищаем и проверяем
//    stack.clear();
//    EXPECT_TRUE(stack.is_empty());
//
//    // Добавляем после очистки
//    stack.push(100);
//    EXPECT_EQ(stack.top(), 100);
//}
//
//// Тест работы с булевыми значениями
//TEST(StackListTest, BooleanType) {
//    Stack<bool> bool_stack;
//    bool_stack.push(true);
//    bool_stack.push(false);
//    bool_stack.push(true);
//
//    EXPECT_EQ(bool_stack.top(), true);
//    bool_stack.pop();
//    EXPECT_EQ(bool_stack.top(), false);
//    bool_stack.pop();
//    EXPECT_EQ(bool_stack.top(), true);
//}