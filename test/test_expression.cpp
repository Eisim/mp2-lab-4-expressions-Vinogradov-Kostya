#include "expression.h"
#include<iostream>


#include <gtest.h>

TEST(Expression, can_create_empty_expression)
{

	ASSERT_NO_THROW(Expression exp);
}
TEST(Expression, can_create_expression_with_empty_str)
{
	ASSERT_NO_THROW(Expression e(""));
}
TEST(Expression, can_create_expression_with_a_single_number)
{
	ASSERT_NO_THROW(Expression e("1"));
}
TEST(Expression, can_create_expression_with_a_single_variable)
{
	ASSERT_NO_THROW(Expression e("variable"));
}
TEST(Expression, can_create_expression_with_pair_numbers_and_one_operation)
{
	ASSERT_NO_THROW(Expression e("1+2"));
}
TEST(Expression, can_create_expression_with_pair_variables_and_one_operation)
{
	ASSERT_NO_THROW(Expression e("tmp1+tmp2"));
}
TEST(Expression, can_create_expression_with_one_number_and_one_variable_and_one_operation)
{
	ASSERT_NO_THROW(Expression e("5+tmp2"));
}
TEST(Expression, can_create_expression_with_pair_numbers_and_one_operation_and_brackets)
{
	ASSERT_NO_THROW(Expression e("{(1+2)}"));
}
TEST(Expression, can_create_incorrect_expression)
{
	ASSERT_NO_THROW(Expression e("{1+2)"));
}



TEST(Expression, can_calculate_expression_with_one_operation_plus_correctly) {
	Expression exp("3+2");
	EXPECT_EQ(5,exp.getResult());
}
TEST(Expression, can_calculate_expression_with_one_operation_minus_correctly) {
	Expression exp("3-2");
	EXPECT_EQ(1, exp.getResult());
}
TEST(Expression, can_calculate_expression_with_one_operation_multiplie_correctly) {
	Expression exp("3*2");
	EXPECT_EQ(6, exp.getResult());
}
TEST(Expression, can_calculate_expression_with_one_operation_division_correctly) {
	Expression exp("3/2");
	EXPECT_EQ(1.5, exp.getResult());
}
TEST(Expression, can_detect_division_by_zero) {
	Expression exp("1/0");
	EXPECT_EQ(0, exp.isCorrect());
}



TEST(Expression, can_detect_incorrectness_of_expression_INCORRECT_NUM) {
	Expression exp("3.1.1");
	EXPECT_EQ(0, exp.isCorrect());
}
TEST(Expression, can_detect_incorrectness_of_expression_INCORRECT_DOUBLE_SEPORATOR) {
	Expression exp("1..0");
	EXPECT_EQ(0, exp.isCorrect());
}

TEST(Expression, can_detect_incorrectness_of_expression_INCORRECT_VARIABLE_STARTED_WITH_NUM) {
	Expression exp("1abc");
	EXPECT_EQ(0, exp.isCorrect());
}
TEST(Expression, can_detect_incorrectness_of_expression_INCORRECT_VARIABLE_WITH_DOT) {
	Expression exp("tmp.1");
	EXPECT_EQ(0, exp.isCorrect());
}
TEST(Expression, can_detect_incorrectness_of_expression_INCORRECT_SEQUENCE_OF_OPERATIONS) {
	Expression exp("1+-2");
	EXPECT_EQ(0, exp.isCorrect());
}
TEST(Expression, can_detect_incorrectness_of_expression_INCORRECT_DOUBLE_UNARY_MINUS) {
	Expression exp("--1");
	EXPECT_EQ(0, exp.isCorrect());
}
TEST(Expression, can_detect_incorrectness_of_expression_INCORRECT_SINGLES_BRACKETS) {
	Expression exp("{1)");
	EXPECT_EQ(0, exp.isCorrect());
}
TEST(Expression, can_detect_incorrectness_of_expression_INCORRECT_BRACKETS) {
	Expression exp("({1)}");
	EXPECT_EQ(0, exp.isCorrect());
}
TEST(Expression, can_detect_incorrectness_of_expression_INCORRECT_SINGLES_BRACKETS_WITHOUT_VALUE) {
	Expression exp("()");
	EXPECT_EQ(0, exp.isCorrect());
}
TEST(Expression, can_detect_incorrectness_of_expression_DIFFERENT_NUM_OF_BRACKETS) {
	Expression exp("(1))");
	EXPECT_EQ(0, exp.isCorrect());
}
TEST(Expression, can_detect_incorrectness_of_expression_INCORRECT_LAST_SYMBOL_OPERATION) {
	Expression exp("1+2-");
	EXPECT_EQ(0, exp.isCorrect());
}
TEST(Expression, can_detect_incorrectness_of_expression_INCORRECT_LAST_SYMBOL_DOT) {
	Expression exp("1+2.");
	EXPECT_EQ(0, exp.isCorrect());
}


TEST(Expression, can_correctly_calculate_expression_after_change_value_of_variable) {
	Expression exp("1+a");
	std::istringstream input("a=2");
	input >> exp;
	EXPECT_EQ(3, exp.getResult());
}
TEST(Expression, can_correctly_calculate_expression_after_change_values_of_variables) {
	Expression exp("b+a");
	std::istringstream input1("a=2");
	input1 >> exp;
	std::istringstream input2("b=1");
	input2 >> exp;
	EXPECT_EQ(3, exp.getResult());
}
TEST(Expression, can_detect_change_value_of_constant_NUMBER) {
	Expression exp("1+a");
	std::istringstream input("a=2\n1=1.5");
	input >> exp;
	EXPECT_EQ(3, exp.getResult());
}
TEST(Expression, can_detect_change_value_of_constant_SPECIAL_CONSTANT) {
	Expression exp("pi+a");
	std::istringstream input("a=2\npi=5");
	input >> exp;
	EXPECT_EQ(5.1415926535897932384626433832795, exp.getResult());
}


TEST(Expression, can_correctly_calculate_expression_after_change_value_of_variable_written_like_expression) {
	Expression exp("1.5+a");
	std::istringstream input("a=2*(-1.5+3.5)");
	input >> exp;
	EXPECT_EQ(5.5, exp.getResult());
}



TEST(Expression, can_calculate_expression_with_different_priority_operations_correctly) {
	Expression exp("3+2*5");
	EXPECT_EQ(13, exp.getResult());
}
TEST(Expression, can_calculate_expression_with_brackets_correctly) {
	Expression exp("3*(2+5)");
	EXPECT_EQ(21, exp.getResult());
}



TEST(Expression, can_detect_unary_minus) {
	Expression exp("-3");
	EXPECT_EQ(-3, exp.getResult());
}
TEST(Expression, can_detect_unary_minuses) {
	Expression exp("-(-3)");
	EXPECT_EQ(3, exp.getResult());
}
TEST(Expression, can_calculate_expression_with_unary_minuse_correctly) {
	Expression exp("-(3*2)+(-(-1-1))");
	EXPECT_EQ(-4, exp.getResult());
}
TEST(Expression, can_calculate_different_expressions) {
	Expression exp;
	for (int i = 0; i < 5; i++) {
		 exp=std::to_string(i)+"+"+std::to_string(i+1);
		EXPECT_EQ(i+i+1, exp.getResult());
	}
}
TEST(Expression, can_calculate_expression_with_different_values_of_variable) {
	Expression exp("1+a");
	for (int i = 0; i < 5; i++) {
		std::istringstream input("a="+std::to_string(i));
		input >> exp;
		EXPECT_EQ(1+i, exp.getResult());
	}
  ASSERT_NO_THROW(Expression exp);

}
