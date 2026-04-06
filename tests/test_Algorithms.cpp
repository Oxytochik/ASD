#include <gtest/gtest.h>
#include "../lib_Algorithms/Algorithms.h"

TEST(AlgorithmTests, BracketsCount) {
	EXPECT_EQ(BracketsNumb("(("), 2);
	EXPECT_EQ(BracketsNumb(" "), 0);
	EXPECT_EQ(BracketsNumb("abc"), 0);
	EXPECT_EQ(BracketsNumb("){["), 2);
}

TEST(AlgorithmTests, BracketBalance) {
	std::string tested_string = "()()";
	EXPECT_TRUE(CheckBrackets(tested_string));
	EXPECT_FALSE(CheckBrackets(")"));
	EXPECT_FALSE(CheckBrackets("{"));
	EXPECT_FALSE(CheckBrackets("(("));
	EXPECT_TRUE(CheckBrackets("([{}])"));
	EXPECT_TRUE(CheckBrackets(""));
}

TEST(AlgorithmTests, Check_is_in) {
	char tested_array[2] = {'a', '4'};
	EXPECT_TRUE(is_in('a', tested_array, 2));
	EXPECT_TRUE(is_in('4', tested_array, 2));
	EXPECT_FALSE(is_in('c', tested_array, 2));

}

TEST(AlgotithmTests, CorrectExpression) {
	EXPECT_NO_THROW(read_expression("(x +(5-((7/y)*10)))^z"));
}

TEST(AlgotithmTests, Brackets_after_operation) {
	EXPECT_ANY_THROW(read_expression("x()"));
}

//TEST(AlgotithmTests, Brackets_after_operation_numb_version) {
//	EXPECT_ANY_THROW(read_expression("5*(5)"));
//}

TEST(AlgotithmTests, CloseBracket_without_open_bracket) {
	EXPECT_ANY_THROW(read_expression(" x + y)"));
}

TEST(AlgotithmTests, CloseBracket_after_operation) {
	EXPECT_ANY_THROW(read_expression("( x + ) y"));
}

TEST(AlgotithmTests, Open_bracket_without_close_bracket) {
	EXPECT_ANY_THROW(read_expression(" ((x + y)+8"));
}

TEST(AlgotithmTests, Number_after_number) {
	EXPECT_ANY_THROW(read_expression("(5 5)"));
}

TEST(AlgotithmTests, First_operator) {
	EXPECT_ANY_THROW(read_expression("+(5-5)"));
}

TEST(AlgotithmTests, Two_operation) {
	EXPECT_ANY_THROW(read_expression("5 ++ 5"));
}

TEST(AlgotithmTests, Operation_after_brackets) {
	EXPECT_ANY_THROW(read_expression("4 -(+5)"));
}

TEST(AlgotithmTests, Other_Symbol) {
	EXPECT_ANY_THROW(read_expression("5 + a"));
}

TEST(AlgotithmTests, Empty_Expression) {
	EXPECT_ANY_THROW(read_expression("()"));
}

TEST(AlgotithmTests, Operation_Symbol_Last) {
	EXPECT_ANY_THROW(read_expression("5 + "));
}

TEST(AlgotithmTests, Operator_First) {
	EXPECT_ANY_THROW(read_expression("+5"));
}

TEST(AlgotithmTests, Numb_and_Alphabet_Symbol_ver_1) {
	EXPECT_ANY_THROW(read_expression("5y"));
}

TEST(AlgotithmTests, Numb_and_Alphabet_Symbol_ver_2) {
	EXPECT_ANY_THROW(read_expression("z5"));
}

TEST(AlgotithmTests, One_Numb) {
	EXPECT_NO_THROW(read_expression("5"));
}






