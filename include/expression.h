#pragma once
#include<vector>
#include<iostream>
#include<string>
#include<map>
//abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ
class Expression {
	std::string source_str,operations;
	std::string alph_nums = "0123456789abcdefghijklmnopqrstuvwxyz", 
		alph_just_letters="abcdefghijklmnopqrstuvwxyz",
		alph_operations = "-+/*",//this sorted by priority  .  index is the priority
		alph_opening_brackets ="({[",
		alph_closing_brackets=")}]",
		alph_separator=".,";
	std::vector<std::string> postfix_form;
	std::map <std::string, double> operands;
	std::map < char, int > priority = {
		{'(',0},
		{'[',0},
		{'{',0},
		{'+',1},
		{'-',1},
		{'*',2},
		{'/',2},
	};
	double res;
	bool is_correct;

	bool expressionIsCorrect();
	void cut();
	void calculate();
public:
	Expression() :is_correct(false),res(0) {};
	Expression(std::string str);
	std::string getSourceString() {
		return source_str;
	}
	std::string getAcceptableNums() { return alph_nums; }
	std::string getAcceptableOperations() { return alph_operations; }
	std::string getAcceptableOpeningBrackets() { return alph_opening_brackets; }
	std::string getAcceptableClosingBrackets() { return alph_closing_brackets; }
	std::string getAcceptableSeparators() { return alph_separator; }
	std::vector<std::string> getPostfixForm() { return postfix_form; }

	
	friend std::istream& operator>>(std::istream& istr,Expression& exp);
	friend std::ostream& operator<<(std::ostream& ostr,const Expression& exp);
};