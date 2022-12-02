#include "expression.h"
#include<map>

#include <gtest.h>

TEST(Expression, can_create_empty_expression)
{
	ASSERT_NO_THROW(Expression e);
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
TEST(Expression, can_determine_division_by_zero) {
	Expression exp("1/0");
	EXPECT_EQ(0, exp.isCorrect());
}



TEST(Expression, can_determine_incorrectness_of_expression_INCORRECT_NUM) {
	Expression exp("3.1.1");
	EXPECT_EQ(0, exp.isCorrect());
}
TEST(Expression, can_determine_incorrectness_of_expression_INCORRECT_DOUBLE_SEPORATOR) {
	Expression exp("1..0");
	EXPECT_EQ(0, exp.isCorrect());
}

TEST(Expression, can_determine_incorrectness_of_expression_INCORRECT_VARIABLE_STARTED_WITH_NUM) {
	Expression exp("1abc");
	EXPECT_EQ(0, exp.isCorrect());
}
TEST(Expression, can_determine_incorrectness_of_expression_INCORRECT_VARIABLE_WITH_DOT) {
	Expression exp("tmp.1");
	EXPECT_EQ(0, exp.isCorrect());
}
TEST(Expression, can_determine_incorrectness_of_expression_INCORRECT_SEQUENCE_OF_OPERATIONS) {
	Expression exp("1+-2");
	EXPECT_EQ(0, exp.isCorrect());
}
TEST(Expression, can_determine_incorrectness_of_expression_INCORRECT_DOUBLE_UNARY_MINUS) {
	Expression exp("--1");
	EXPECT_EQ(0, exp.isCorrect());
}
TEST(Expression, can_determine_incorrectness_of_expression_INCORRECT_SINGLES_BRACKETS) {
	Expression exp("{1)");
	EXPECT_EQ(0, exp.isCorrect());
}
TEST(Expression, can_determine_incorrectness_of_expression_INCORRECT_BRACKETS) {
	Expression exp("({1)}");
	EXPECT_EQ(0, exp.isCorrect());
}
TEST(Expression, can_determine_incorrectness_of_expression_INCORRECT_SINGLES_BRACKETS_WITHOUT_VALUE) {
	Expression exp("()");
	EXPECT_EQ(0, exp.isCorrect());
}
TEST(Expression, can_determine_incorrectness_of_expression_DIFFERENT_NUM_OF_BRACKETS) {
	Expression exp("(1))");
	EXPECT_EQ(0, exp.isCorrect());
}
TEST(Expression, can_determine_incorrectness_of_expression_INCORRECT_LAST_SYMBOL_OPERATION) {
	Expression exp("1+2-");
	EXPECT_EQ(0, exp.isCorrect());
}
TEST(Expression, can_determine_incorrectness_of_expression_INCORRECT_LAST_SYMBOL_DOT) {
	Expression exp("1+2.");
	EXPECT_EQ(0, exp.isCorrect());
}


TEST(Expression, can_correctly_calculate_expression_after_change_value_of_variable) {
	Expression exp("1+a");
	exp("a=2");
	EXPECT_EQ(3, exp.getResult());
}
TEST(Expression, can_correctly_calculate_expression_after_change_values_of_variables) {
	Expression exp("b+a");
	exp("a=2");
	exp("b=1");
	EXPECT_EQ(3, exp.getResult());
}
TEST(Expression, can_correctly_calculate_expression_after_change_value_of_variable_written_like_expression) {
	Expression exp("1.5+a");
	exp("a=2*(-1.5+3.5)");
	EXPECT_EQ(5.5, exp.getResult());
}
