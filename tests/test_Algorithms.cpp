#include <gtest/gtest.h>
#include "../lib_Algorithms/Algorithms.h"

TEST(AlgorithmTests, BracketBalance) {
	std::string tested_string = "()()";
	EXPECT_TRUE(CheckBrackets(tested_string));
	tested_string = ")";
	EXPECT_FALSE(CheckBrackets(tested_string));
	tested_string = "((";
	EXPECT_FALSE(CheckBrackets(tested_string));
	tested_string = "([{}])";
	EXPECT_TRUE(CheckBrackets(tested_string));



}