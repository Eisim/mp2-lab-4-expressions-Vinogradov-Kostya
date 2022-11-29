#include"expression.h"
#include<stack>
//can be used
//int getPriority(char elem,std::string str) {//priority is based on index in string
//	int index = 0;
//	for(index;elem!=str[index]||index<str.size();index++)
//	return (index>=str.size())?-1:index;
//}
bool contains(char symb, std::string set) {
	for (int i = 0; i < set.size(); i++) {
		if (symb == set[i]) return true;
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
	WAIT_NUMBER__OR_MINUS_OR_OPENING_BRACKET,
	WAIT_NUMBER_OR_OPENING_BRACKET,
	WAIT_NUMBER,
	WAIT_NUMBER_OR_OPERATION_OR_DOT_OR_CLOSING_BRACKET,
	WAIT_NUMBER_OR_OPERATION_OR_CLOSING_BRACKET,
	WAIT_OPERATION_OR_CLOSING_BRACKET,

	ERROR
};


bool Expression::expressionIsCorrect() {
	if (bracketsIsCorrect(*this) == 0) return false; 
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

void Expression::cut() {

	std::stack<char> operations_stack;
	
	if (is_correct == false) return; 
	char cur_symb;
	std::string token;

	for (int i = 0; i < source_str.size(); i++) {
		cur_symb = source_str[i];
		if (contains(cur_symb, alph_operations) || contains(cur_symb, alph_opening_brackets)) {

			if (token != "") {
				postfix_form.push_back(token);
				operands.insert({ token, (contains(token[0],alph_just_letters)) ? 0.0 : std::stod(token) });

				token = "";
			}
			if(contains(cur_symb, alph_opening_brackets)==false)
			while (operations_stack.empty() == false && (priority[cur_symb]<=priority[operations_stack.top()])) {
				if(contains(operations_stack.top(), alph_opening_brackets) == false)
				postfix_form.push_back(std::string(1,operations_stack.top()));
				operations_stack.pop();
			}
			operations_stack.push(cur_symb);


		}
		else if (contains(cur_symb, alph_closing_brackets)) {
			if (token != "") {
				postfix_form.push_back(token);
				operands.insert({ token, (contains(token[0],alph_just_letters)) ? 0.0 : std::stod(token) });

				token = "";
			}

			while (operations_stack.empty() == false) {
				if (contains(operations_stack.top(), alph_opening_brackets) == false) 
					postfix_form.push_back(std::string(1, operations_stack.top()));
					operations_stack.pop();
				
			}

		}
		else {
			token += cur_symb;
		}
	}
	if (token != "") {
		postfix_form.push_back(token);
		operands.insert({ token, (contains(token[0],alph_just_letters)) ? 0.0: std::stod(token) });
	}
	while (operations_stack.empty() == false) {
		if (contains(operations_stack.top(), alph_opening_brackets) == false) 
			postfix_form.push_back(std::string(1, operations_stack.top()));
			operations_stack.pop();

	}

}

void Expression::calculate() {
	std::stack<double> st;
	std::string lexem;
	double v1, v2;
	for (int i = 0; i < postfix_form.size(); i++) {
		lexem = postfix_form[i];
		//------------------------------------------------HERE APPEND OPERATIONS
		if (lexem == "+") {
			v2 = st.top(); st.pop();
			v1 = st.top(); st.pop();
			st.push(v1 + v2);
		}
		else if (lexem == "-") {
			v2 = st.top(); st.pop();
			v1 = st.top(); st.pop();
			st.push(v1 - v2);
		}
		else if (lexem == "*") {
			v2 = st.top(); st.pop();
			v1 = st.top(); st.pop();
			st.push(v1 * v2);
		}
		else if (lexem == "/") {
			v2 = st.top(); st.pop();
			v1 = st.top(); st.pop();
			st.push(v1 / v2);
		}
		else st.push(operands[lexem]);
		
	}
	res = st.top();
}
Expression::Expression(std::string str) {
	source_str = str;
	
	is_correct=this->expressionIsCorrect();
	this->cut();
	this->calculate();
}

std::istream& operator>>(std::istream& istream,Expression& exp) {
	std::string tmp,token1,token2;
	bool flag=false;
	if (exp.source_str == "") {
		istream >> exp.source_str;
		exp.is_correct = exp.expressionIsCorrect();
		exp.cut();
	}
	else {  //TODO if's
		istream >> tmp;
		for (auto symb:tmp) {
			if (symb == '=') {
				flag = true;
				continue;
			}
			if (flag == false)
				token1 += symb;
			else token2 += symb;
		}
		exp.operands[token1] = std::stod(token2);// ({ token1,std::stod(token2) });
	}
	exp.calculate();

	return istream;
}
std::ostream& operator<<(std::ostream& ostream, const Expression& exp) {
	if (exp.is_correct)
		ostream << exp.source_str<<"="<<exp.res;
	else ostream << "Expression is not correct";
	return ostream;
}