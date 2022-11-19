#include"expression.h"
#include<stack>


bool bracketsIsCorrect(const std::string& str) {
	std::stack<char> st;
	for (unsigned int i = 0; i < str.size(); i++) {
		if (str[i] == '(') st.push(')');
		if (str[i] == '{') st.push('}');
		if (str[i] == '[') st.push(']');

		if (!st.empty() && str[i] == st.top()) {
			st.pop();
		}
		else if (str[i] == ')' || str[i] == '}' || str[i] == ']')return false;

	}



	return st.empty();
}


enum class states {
	WAIT_NUMBER__OR_MINUS_OR_OPENING_BRACKET,
	WAIT_NUMBER_OR_OPENING_BRACKET,
	WAIT_NUMBER,
	WAIT_NUMBER_OR_OPERATION_OR_DOT_OR_CLOSING_BRACKET,
	WAIT_NUMBER_OR_OPERATION_OR_CLOSING_BRACKET,
	WAIT_OPERATION_OR_CLOSING_BRACKET,

	ERROR
};

bool contains(char symb,std::string set) {
	for (int i = 0; i < set.size(); i++) {
		if (symb == set[i]) return true;
	}
	return false;
}

bool Expression::transform() {
	if (bracketsIsCorrect(source_str) == 0) return false; 
	states a = states::WAIT_NUMBER__OR_MINUS_OR_OPENING_BRACKET;
	char symb;

	for (int i = 0; i < source_str.size(); i++) {
		symb = source_str[i];

		switch (a) {
		//
		case(states::WAIT_NUMBER__OR_MINUS_OR_OPENING_BRACKET):

			//std::cout << "WAIT_NUMBER__OR_MINUS_OR_OPENING_BRACKET\n";

			if (!contains(symb,alph_nums)&& !contains(symb,alph_opening_brackets)&& !(symb=='-')) {
				a = states::ERROR;
			}
			else if (contains(symb, alph_nums)) {
				a = states::WAIT_NUMBER_OR_OPERATION_OR_DOT_OR_CLOSING_BRACKET;
			}
			else if (symb == '-') {
				a = states::WAIT_NUMBER_OR_OPENING_BRACKET;
			}
			else if (contains(symb, alph_opening_brackets)) {
				
				a = a;
			}
			break;
		//
		case(states::WAIT_NUMBER_OR_OPENING_BRACKET):

			//std::cout << "WAIT_NUMBER_OR_OPENING_BRACKET\n";

			if (!contains(symb,alph_nums) && !contains(symb,alph_opening_brackets)) {
				a = states::ERROR;
			}
			else if (contains(symb, alph_nums)) {
				a = states::WAIT_NUMBER_OR_OPERATION_OR_DOT_OR_CLOSING_BRACKET;
			}
			else if (contains(symb, alph_opening_brackets)) {
				a = states::WAIT_NUMBER__OR_MINUS_OR_OPENING_BRACKET;
			}
			break;
		//
		case(states::WAIT_NUMBER):

			//std::cout << "WAIT_NUMBER\n";

			if (!contains(symb, alph_nums)) {
				a = states::ERROR;

			}
			else {
				a = states::WAIT_NUMBER_OR_OPERATION_OR_CLOSING_BRACKET;
			}
			break;
		//
		case(states::WAIT_NUMBER_OR_OPERATION_OR_CLOSING_BRACKET):

			//std::cout << "WAIT_NUMBER_OR_OPERATION_OR_CLOSING_BRACKET\n";

			if (!contains(symb, alph_nums)&& !contains(symb, alph_operations)&&!contains(symb,alph_closing_brackets))
				a = states::ERROR;
			else if (contains(symb, alph_operations))
				a = states::WAIT_NUMBER_OR_OPENING_BRACKET;
			else if(contains(symb,alph_closing_brackets))
				a=a;
			else if (contains(symb, alph_nums)) {
				a = a;
			}
			break;
		//
		case(states::WAIT_OPERATION_OR_CLOSING_BRACKET):

			//std::cout << "WAIT_OPERATION_OR_CLOSING_BRACKET\n";

			if (!contains(symb, alph_operations) && !contains(symb, alph_closing_brackets)) {
				a = states::ERROR;
				
			}
			else if (contains(symb, alph_operations))
				a = states::WAIT_NUMBER_OR_OPENING_BRACKET;
			else if (contains(symb, alph_closing_brackets))
				a = a;
			break;
		//
		case(states::WAIT_NUMBER_OR_OPERATION_OR_DOT_OR_CLOSING_BRACKET):

			//std::cout << "WAIT_NUMBER_OR_OPERATION_OR_DOT_OR_CLOSING_BRACKET\n";

			if (!contains(symb, alph_nums)&& !contains(symb,alph_operations) && !contains(symb,alph_separator) && !contains(symb,alph_closing_brackets) ) {
				a = states::ERROR;
			}
			else if (contains(symb, alph_nums)) {
				a = a;
			}
			else if (contains(symb, alph_operations)) {
				a = states::WAIT_NUMBER_OR_OPENING_BRACKET;
			}
			else if (contains(symb, alph_separator)) {
				a = states::WAIT_NUMBER;
			}
			else if (contains(symb, alph_closing_brackets)) {
				a = states::WAIT_OPERATION_OR_CLOSING_BRACKET;
			}
			break;

		case(states::ERROR):
			//std::cout <<"ERROR\n";
			return false;
		}
		if (!contains(source_str[source_str.size() - 1], alph_nums) && !contains(source_str[source_str.size() - 1], alph_closing_brackets)) return false;
	}
	return true;
}
Expression::Expression(std::string str) {
	source_str = str;
	
	is_correct=this->transform();
}

std::istream& operator>>(std::istream& istream,Expression& exp) {
	istream >> exp.source_str;
	exp.is_correct=exp.transform();
	return istream;
}
std::ostream& operator<<(std::ostream& ostream, const Expression& exp) {
	if (exp.is_correct)
		ostream << exp.source_str;
	else ostream << "Expression is not correct";
	return ostream;
}