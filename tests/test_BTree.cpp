
//
#include <gtest/gtest.h>
#include <sstream>
#include "..\lib_BTree\BTree.h" 



// Вспомогательная функция для захвата вывода
TEST(TestBinaryTree, check_insert_of_multiple_values_using_the_same_key) {
    BTree<int, std::string> tree(1, "1.");
    tree.insert(2, "2.");
    tree.insert(3, "3.");
    tree.insert(4, "4.");
    tree.insert(5, "5.");
    tree.insert(6, "6.");
    tree.erase(6);
    tree.erase(1);
    tree.insert(12, "12.");

    EXPECT_NO_FATAL_FAILURE(tree.insert(12, "Twelve"));

    //tree.print_W();

    std::stringstream buffer_W;
    std::streambuf* old = std::cout.rdbuf(buffer_W.rdbuf());
    tree.print_W();
    std::cout.rdbuf(old);
    EXPECT_EQ(buffer_W.str(), "5:5. 2:2. 3:3. 4:4. 12:12. 12:Twelve \n");
}

TEST(TestBinaryTree, check_find) {
    BTree<int, std::string> tree(1, "1.");
    tree.insert(2, "2.");
    tree.insert(3, "3.");
    tree.insert(4, "4.");
    tree.insert(5, "5.");
    tree.insert(6, "6.");
    tree.insert(7, "7.");
    tree.insert(8, "8.");
    tree.insert(9, "9.");
    tree.insert(10, "10.");
    tree.insert(11, "11.");
    tree.erase(6);
    tree.erase(1);
    tree.insert(12, "12.");

    //tree.print_W();

    EXPECT_EQ(*tree.find(11), "11.");
    EXPECT_EQ(tree.find(1), nullptr);
}

TEST(TestBinaryTree, check_erase_leaf) {
    BTree<int, std::string> tree;
    tree.insert(1, "1.");
    tree.insert(2, "2.");
    tree.insert(3, "3.");
    tree.insert(4, "4.");
    tree.insert(5, "5.");
    tree.insert(6, "6.");
    tree.erase(4);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    tree.print_W();
    std::cout.rdbuf(old);

    EXPECT_EQ(buffer.str(), "1:1. 2:2. 3:3. 6:6. 5:5. \n");
}

TEST(TestBinaryTree, check_erase_node) {
    BTree<int, std::string> tree;
    tree.insert(1, "1.");
    tree.insert(2, "2.");
    tree.insert(3, "3.");
    tree.insert(4, "4.");
    tree.insert(5, "5.");
    //tree.insert(6, "6.");
    tree.erase(2);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    tree.print_W();
    std::cout.rdbuf(old);

    EXPECT_EQ(buffer.str(), "1:1. 5:5. 3:3. 4:4. \n");
}
TEST(TestBinaryTree, check_erase_single_root) {
    BTree<int, std::string> tree;
    tree.insert(1, "1.");
    tree.erase(1);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    tree.print_W();
    std::cout.rdbuf(old);

    EXPECT_EQ(buffer.str(), "");
}

TEST(TestBinaryTree, the_exception_is_when_erase_from_empty_tree) {
    BTree<int, std::string> tree;
    ASSERT_ANY_THROW(tree.erase(2));
}

TEST(TestBinaryTree, check_clear) {
    BTree<int, std::string> tree;
    tree.insert(1, "1.");
    tree.insert(2, "2.");
    tree.insert(3, "3.");
    tree.insert(4, "4.");
    tree.insert(5, "5.");
    tree.insert(6, "6.");
    tree.erase(2);
    tree.erase(1);

    tree.clear();

    EXPECT_TRUE(tree.is_empty());

    tree.insert(34, "34.");
    tree.insert(56, "56.");

    EXPECT_FALSE(tree.is_empty());
}

TEST(TestBinaryTree, check_print) {
    BTree<int, std::string> tree(1, "1.");
    tree.insert(2, "2.");
    tree.insert(3, "3.");
    tree.insert(4, "4.");
    tree.insert(5, "5.");
    tree.insert(6, "6.");
    tree.insert(7, "7.");
    tree.insert(8, "8.");
    tree.insert(9, "9.");
    tree.insert(10, "10.");
    tree.insert(11, "11.");

    std::stringstream buffer_W;
    std::streambuf* old = std::cout.rdbuf(buffer_W.rdbuf());
    tree.print_W();
    std::cout.rdbuf(old);
    EXPECT_EQ(buffer_W.str(), "1:1. 2:2. 3:3. 4:4. 5:5. 6:6. 7:7. 8:8. 9:9. 10:10. 11:11. \n");

    std::stringstream buffer_DLCR;
    old = std::cout.rdbuf(buffer_DLCR.rdbuf());
    tree.print_DLCR();
    std::cout.rdbuf(old);
    EXPECT_EQ(buffer_DLCR.str(), "8:8. 4:4. 9:9. 2:2. 10:10. 5:5. 11:11. 1:1. 6:6. 3:3. 7:7. \n");

    std::stringstream buffer_DLRC;
    old = std::cout.rdbuf(buffer_DLRC.rdbuf());
    tree.print_DLRC();
    std::cout.rdbuf(old);
    EXPECT_EQ(buffer_DLRC.str(), "8:8. 9:9. 4:4. 10:10. 11:11. 5:5. 2:2. 6:6. 7:7. 3:3. 1:1. \n");

    std::stringstream buffer_DCLR;
    old = std::cout.rdbuf(buffer_DCLR.rdbuf());
    tree.print_DCLR();
    std::cout.rdbuf(old);
    EXPECT_EQ(buffer_DCLR.str(), "1:1. 2:2. 4:4. 8:8. 9:9. 5:5. 10:10. 11:11. 3:3. 6:6. 7:7. \n");
}
//
//// 1. Вставка нескольких значений, включая дубликат ключа
////TEST(TestBTree, check_insert_of_multiple_values_using_the_same_key) {
////    BTree<int, std::string> tree;
////    tree.insert(1, "1.");
////    tree.insert(2, "2.");
////    tree.insert(3, "3.");
////    tree.insert(4, "4.");
////    tree.insert(5, "5.");
////    tree.insert(6, "6.");
////    tree.erase(6);   // удаляем узел 6
////    tree.erase(1);   // удаляем узел 1
////    tree.insert(12, "12.");
////    tree.insert(12, "Twelve");  // второй узел с ключом 12
////
////    // Ожидаемое дерево после операций (complete tree):
////    // Уровни:      5
////    //            /   \
////    //           2     3
////    //          / \   /
////    //         4  12 12(Twelve)
////    // Вывод BFS: 5, 2, 3, 4, 12, 12
////
////    std::string out = capture_print([&]() { tree.print_W(); });
////    EXPECT_EQ(out, "5:5. 2:2. 3:3. 4:4. 12:12. 12:Twelve \n");
////}
//
//// 2. Поиск значений
//TEST(TestBTree, check_find) {
//    BTree<int, std::string> tree;
//    tree.insert(10, "ten");
//    tree.insert(20, "twenty");
//    tree.insert(30, "thirty");
//    tree.insert(40, "forty");
//    tree.insert(50, "fifty");
//    tree.erase(30);
//    tree.erase(10);
//    tree.insert(60, "sixty");
//
//    EXPECT_EQ(*tree.find(20), "twenty");
//    EXPECT_EQ(tree.find(10), nullptr);  // удалён
//    EXPECT_EQ(tree.find(60), "sixty");
//}
//
//// 3. Удаление листа (узел без детей)
//TEST(TestBTree, check_erase_leaf) {
//    BTree<int, std::string> tree;
//    tree.insert(1, "a");
//    tree.insert(2, "b");
//    tree.insert(3, "c");
//    tree.insert(4, "d");
//    tree.insert(5, "e");
//    tree.erase(4);  // 4 - лист (на 3-м уровне, левый ребёнок узла 2)
//
//    // Дерево после вставки 1,2,3,4,5: (complete)
//    //      1
//    //    /   \
//    //   2     3
//    //  / \
//    // 4   5
//    // После удаления 4: последний узел (5) копируется в 4, затем 5 удаляется.
//    // Итог: 1,2,3,5 (5 теперь на месте 4)
//    std::string out = capture_print([&]() { tree.print_W(); });
//    EXPECT_EQ(out, "1:a 2:b 3:c 5:e \n");
//}
//
//// 4. Удаление внутреннего узла (с детьми)
//TEST(TestBTree, check_erase_node) {
//    BTree<int, std::string> tree;
//    tree.insert(1, "one");
//    tree.insert(2, "two");
//    tree.insert(3, "three");
//    tree.insert(4, "four");
//    tree.insert(5, "five");
//    // дерево:      1
//    //            / \
//    //           2   3
//    //          / \
//    //         4   5
//    tree.erase(2);  // удаляем узел 2
//
//    // Самый глубокий правый узел = 5 (лист). Копируем 5 в узел 2, удаляем 5.
//    // Итог:     1
//    //          / \
//    //         5   3
//    //        /
//    //       4
//    std::string out = capture_print([&]() { tree.print_W(); });
//    EXPECT_EQ(out, "1:one 5:five 3:three 4:four \n");
//}
//
//// 5. Удаление единственного корня
//TEST(TestBTree, check_erase_single_root) {
//    BTree<int, std::string> tree;
//    tree.insert(42, "answer");
//    tree.erase(42);
//
//    std::string out = capture_print([&]() { tree.print_W(); });
//    EXPECT_EQ(out, "");
//    EXPECT_TRUE(tree.is_empty());
//}
//
//// 6. Исключение при удалении из пустого дерева
//TEST(TestBTree, the_exception_is_when_erase_from_empty_tree) {
//    BTree<int, std::string> tree;
//    ASSERT_ANY_THROW(tree.erase(100));
//}
//
//// 7. Очистка дерева (clear)
//TEST(TestBTree, check_clear) {
//    BTree<int, std::string> tree;
//    tree.insert(1, "a");
//    tree.insert(2, "b");
//    tree.insert(3, "c");
//    tree.erase(2);
//    tree.clear();
//
//    EXPECT_TRUE(tree.is_empty());
//
//    tree.insert(99, "new");
//    EXPECT_FALSE(tree.is_empty());
//    EXPECT_EQ(*tree.find(99), "new");
//}
//
//// 8. Проверка всех трёх рекурсивных обходов (DCLR, DLCR, DLRC) и BFS
//TEST(TestBTree, check_print) {
//    BTree<int, std::string> tree;
//    // Построим дерево из 11 узлов (полное, 4 уровня)
//    for (int i = 1; i <= 11; ++i) {
//        tree.insert(i, std::to_string(i) + ".");
//    }
//    // Структура дерева (complete binary tree):
//    //               1
//    //            /     \
//    //           2       3
//    //         /   \    / \
//    //        4     5  6   7
//    //       / \   / \
//    //      8   9 10 11
//    //
//    // Обходы (ключ:значение):
//    // BFS (level-order): 1 2 3 4 5 6 7 8 9 10 11
//    // Pre-order (DCLR):  1 2 4 8 9 5 10 11 3 6 7
//    // In-order (DLCR):   8 4 9 2 10 5 11 1 6 3 7
//    // Post-order (DLRC): 8 9 4 10 11 5 2 6 7 3 1
//
//    std::string bfs = capture_print([&]() { tree.print_W(); });
//    EXPECT_EQ(bfs, "1:1. 2:2. 3:3. 4:4. 5:5. 6:6. 7:7. 8:8. 9:9. 10:10. 11:11. \n");
//
//    std::string dclr = capture_print([&]() { tree.print_DCLR(); });
//    EXPECT_EQ(dclr, "1:1. 2:2. 4:4. 8:8. 9:9. 5:5. 10:10. 11:11. 3:3. 6:6. 7:7. \n");
//
//    std::string dlcr = capture_print([&]() { tree.print_DLCR(); });
//    EXPECT_EQ(dlcr, "8:8. 4:4. 9:9. 2:2. 10:10. 5:5. 11:11. 1:1. 6:6. 3:3. 7:7. \n");
//
//    std::string dlrc = capture_print([&]() { tree.print_DLRC(); });
//    EXPECT_EQ(dlrc, "8:8. 9:9. 4:4. 10:10. 11:11. 5:5. 2:2. 6:6. 7:7. 3:3. 1:1. \n");
//}
//
