#include <gtest/gtest.h>
#include <sstream>
#include "..\lib_BSTree\BSTree.h"

TEST(TestBinarySearchTree, the_exception_is_when_insert_of_multiple_values_using_the_same_key) {
    BSTree<int, std::string> tree(15, "15.");
    tree.insert(5, "5.");
    tree.insert(30, "30.");
    tree.insert(35, "35.");
    tree.insert(16, "16.");
    tree.insert(7, "7.");
    tree.insert(3, "3.");
    tree.insert(1, "1.");
    tree.insert(9, "9.");
    tree.insert(40, "40.");
    tree.insert(6, "6.");
    tree.erase(6);
    tree.erase(1);

    //tree.print();

    //ASSERT_ANY_THROW(tree.insert(16, "Twelve"));

    tree.insert(16, "Twelve.");

    std::stringstream buffer_W;
    std::streambuf* old = std::cout.rdbuf(buffer_W.rdbuf());
    tree.print();
    std::cout.rdbuf(old);
    EXPECT_EQ(buffer_W.str(), "3:3. 5:5. 7:7. 9:9. 15:15. 16:Twelve. 30:30. 35:35. 40:40. \n");
}

TEST(TestBinarySearchTree, check_find) {
    BSTree<int, std::string> tree;
    tree.insert(15, "15.");
    tree.insert(5, "5.");
    tree.insert(30, "30.");
    tree.insert(35, "35.");
    tree.insert(16, "16.");
    tree.insert(7, "7.");
    tree.insert(3, "3.");
    tree.insert(1, "1.");
    tree.insert(9, "9.");
    tree.insert(40, "40.");
    tree.insert(6, "6.");
    tree.erase(6);
    tree.erase(1);
    tree.insert(12, "12.");

    //tree.print();

    EXPECT_EQ(*tree.find(12), "12.");
    EXPECT_EQ(tree.find(1), nullptr);
}

TEST(TestBinarySearchTree, check_erase_leaf) {
    BSTree<int, std::string> tree;
    tree.insert(15, "15.");
    tree.insert(5, "5.");
    tree.insert(30, "30.");
    tree.insert(35, "35.");
    tree.insert(16, "16.");
    tree.insert(7, "7.");
    tree.insert(3, "3.");
    tree.insert(1, "1.");
    tree.insert(9, "9.");
    tree.insert(40, "40.");
    tree.insert(6, "6.");
    tree.erase(1);
    tree.erase(40);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    tree.print();
    std::cout.rdbuf(old);

    EXPECT_EQ(buffer.str(), "3:3. 5:5. 6:6. 7:7. 9:9. 15:15. 16:16. 30:30. 35:35. \n");
}

TEST(TestBinarySearchTree, check_erase_node) {
    BSTree<int, std::string> tree;
    tree.insert(15, "15.");
    tree.insert(5, "5.");
    tree.insert(30, "30.");
    tree.insert(35, "35.");
    tree.insert(18, "18.");
    tree.insert(7, "7.");
    tree.insert(3, "3.");
    tree.insert(1, "1.");
    tree.insert(9, "9.");
    tree.insert(40, "40.");
    tree.insert(6, "6.");
    tree.insert(17, "17.");
    tree.insert(19, "19.");
    tree.erase(30);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    tree.print();
    std::cout.rdbuf(old);

    EXPECT_EQ(buffer.str(), "1:1. 3:3. 5:5. 6:6. 7:7. 9:9. 15:15. 17:17. 18:18. 19:19. 35:35. 40:40. \n");
}

TEST(TestBinarySearchTree, check_erase_node_with_one_child) {
    BSTree<int, std::string> tree;
    tree.insert(15, "15.");
    tree.insert(5, "5.");
    tree.insert(30, "30.");
    tree.insert(35, "35.");
    tree.insert(18, "18.");
    tree.insert(7, "7.");
    tree.insert(3, "3.");
    tree.insert(1, "1.");
    tree.insert(9, "9.");
    tree.insert(40, "40.");
    tree.insert(6, "6.");
    tree.insert(17, "17.");
    tree.insert(19, "19.");
    tree.erase(35);
    tree.erase(3);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    tree.print();
    std::cout.rdbuf(old);

    EXPECT_EQ(buffer.str(), "1:1. 5:5. 6:6. 7:7. 9:9. 15:15. 17:17. 18:18. 19:19. 30:30. 40:40. \n");
}

TEST(TestBinarySearchTree, check_erase_single_root) {
    BSTree<int, std::string> tree;
    tree.insert(1, "1.");
    tree.erase(1);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    tree.print();
    std::cout.rdbuf(old);

    EXPECT_EQ(buffer.str(), "\n");
}

TEST(TestBinarySearchTree, the_exception_is_when_erase_from_empty_tree) {
    BSTree<int, std::string> tree;
    ASSERT_ANY_THROW(tree.erase(2));
}

TEST(TestBinarySearchTree, check_clear) {
    BSTree<int, std::string> tree;
    tree.insert(15, "15.");
    tree.insert(5, "5.");
    tree.insert(30, "30.");
    tree.insert(35, "35.");
    tree.insert(18, "18.");
    tree.insert(7, "7.");
    tree.insert(3, "3.");
    tree.insert(1, "1.");
    tree.insert(9, "9.");
    tree.insert(40, "40.");
    tree.insert(6, "6.");
    tree.insert(17, "17.");
    tree.insert(19, "19.");
    tree.erase(15);
    tree.erase(18);

    tree.clear();

    EXPECT_TRUE(tree.is_empty());

    tree.insert(34, "34.");
    tree.insert(56, "56.");

    EXPECT_FALSE(tree.is_empty());
}