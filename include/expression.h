#pragma once
#include<vector>
#include<iostream>
#include<string>
//abcdefghijklmnopqrstuvwxyz
class Expression {
	std::string source_str,operations;
	std::string alph_nums = "0123456789", alph_operations = "*/+-", alph_opening_brackets ="({[", alph_closing_brackets=")}]",alph_separator=".,";
	std::vector<double> nums;
	bool is_correct;
	bool transform();
	
public:
	Expression() :is_correct(false) {};
	Expression(std::string str);
	std::string getSourceString() {
		return source_str;
	}

	friend std::istream& operator>>(std::istream& istr,Expression& exp);
	friend std::ostream& operator<<(std::ostream& ostr,const Expression& exp);
};