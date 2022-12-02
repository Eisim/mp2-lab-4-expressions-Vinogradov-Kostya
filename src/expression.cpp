#include"expression.h"
bool contains(char symb, std::string set) {
	for (int i = 0; i < set.size(); i++) {
		if (symb == set[i]) return true;
	}
	return false;
}

bool in(std::string str, std::vector<std::string> arr) {
	for (int i = 0; i < arr.size();i++) {
		if (str == arr[i]) return true;
	}
	return false;
}

bool bracketsIsCorrect(Expression& exp) {
	std::stack<char> st;
	std::string str = exp.getSourceString();

	for (unsigned int i = 0; i < str.size(); i++) {
		if (contains(str[i], exp.getAcceptableOpeningBrackets()) && contains(str[i+1], exp.getAcceptableClosingBrackets())) {
			return false;
		}
	}
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
	
};

bool Expression::expressionIsCorrect() {
	return false;
}

void Expression::rewriteForUnaryMinus()
{
	
}

void Expression::cut() {

	
}

void Expression::calculate() {
	
}

Expression::Expression(std::string str) {
	
}

Expression& Expression::operator=(std::string str) {
	return *this
}


void Expression::operator()(std::string str) {
	
}
std::istream& operator>>(std::istream& istream,Expression& exp) {

  return istream;
}
std::ostream& operator<<(std::ostream& ostream, const Expression& exp) {
	
	return ostream;
}
