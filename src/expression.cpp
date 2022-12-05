#include"expression.h"

#include<vector>
#include<iostream>
#include<string>
#include<map>
#include<stack>


void Expression::clear() {
	Expression tmp;
	*this = tmp;
}

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
bool Expression::isVariable(std::string str) {
	if(contains(str[0],alph_nums)) return false;
	for (int i = 1; i < str.size(); i++)
		if (!contains(str[i], alph_letters) || !contains(str[i], alph_nums)) return false;
	return true;
}

enum class states {
	WAIT_LET_NUM_MIN_OPENBR,
	WAIT_NUM_DOT_OPER_CLOSEBR,
	WAIT_NUM,
	WAIT_NUM_OPER_CLOSEBR,
	WAIT_OPER_CLOSEBR,
	WAIT_LET_NUM_OPENBR,
	WAIT_LET_NUM_OPER_CLOSEBR,

	ERROR
};

bool Expression::expressionIsCorrect() {
	if (bracketsIsCorrect(*this) == 0) return false;
	states a = states::WAIT_LET_NUM_MIN_OPENBR;
	char symb=' ';

	for (int i = 0; i < source_str.size(); i++) {
		symb = source_str[i];

		switch (a) {
		case(states::WAIT_LET_NUM_MIN_OPENBR):
			if (contains(symb, alph_nums)) {
				a = states::WAIT_NUM_DOT_OPER_CLOSEBR;
			}
			else if (contains(symb, alph_letters)) {
				a = states::WAIT_LET_NUM_OPER_CLOSEBR;
			}
			else if (symb == '-') {
				a = states::WAIT_LET_NUM_OPENBR;
			}
			else if (contains(symb, alph_opening_brackets)) {
				a = a;
			}
			else a = states::ERROR;

			break;
		case(states::WAIT_NUM_DOT_OPER_CLOSEBR):
			if (contains(symb, alph_nums)) {
				a = a;
			}
			else if (contains(symb, alph_separator)) {
				a = states::WAIT_NUM;
			}
			else if (contains(symb, alph_operations)) {
				a = states::WAIT_LET_NUM_OPENBR;
			}
			else if (contains(symb, alph_closing_brackets)) {
				a = states::WAIT_OPER_CLOSEBR;
			}
			else a = states::ERROR;

			break;
		case(states::WAIT_NUM):
			if (contains(symb, alph_nums)) {
				a = states::WAIT_NUM_OPER_CLOSEBR;
			}
			else a = states::ERROR;

			break;
		case(states::WAIT_NUM_OPER_CLOSEBR) :
			if (contains(symb, alph_nums)) {
				a = a;
			}
			else if (contains(symb, alph_operations)) {
				a = states::WAIT_LET_NUM_OPENBR;
			}
			else if (contains(symb, alph_closing_brackets)) {
				a = states::WAIT_OPER_CLOSEBR;
			}
			else a = states::ERROR;

			break;
		case(states::WAIT_OPER_CLOSEBR):
			if (contains(symb, alph_operations)) {
				a = states::WAIT_LET_NUM_OPENBR;
			}
			else if (contains(symb, alph_closing_brackets)) {
				a = a;
			}
			else a = states::ERROR;

				break;
		case(states::WAIT_LET_NUM_OPENBR):
			if (contains(symb, alph_letters)) {
				a = states::WAIT_LET_NUM_OPER_CLOSEBR;
			}
			else if (contains(symb, alph_nums)) {
				a = states::WAIT_NUM_DOT_OPER_CLOSEBR;
			}
			else if (contains(symb, alph_opening_brackets)) {
				a = states::WAIT_LET_NUM_MIN_OPENBR;
			}
			else {
				a = states::ERROR;
			}

			break;
		case(states::WAIT_LET_NUM_OPER_CLOSEBR): {
			if (contains(symb, alph_letters) || contains(symb, alph_nums)) {
				a = a;
			}
			else if (contains(symb, alph_operations)) {
				a = states::WAIT_LET_NUM_OPENBR;
			}
			else if (contains(symb, alph_closing_brackets)) {
				a=states::WAIT_OPER_CLOSEBR; //------------------------------
			}
			else {
				a = states::ERROR;
			}
			break;
		}
		case(states::ERROR) :
				return false;
				break;
		}
	}
	if (contains(symb, alph_nums) || contains(symb, alph_letters) || contains(symb, alph_closing_brackets)) {
		return true;
	}
	return false;
}

void Expression::rewriteForUnaryMinus()
{
	char cur_symb = ' ';
	std::string tmp;
	if (source_str[0] == '-')
		tmp += '0';
	tmp += source_str[0];

	for (int i = 1; i < source_str.size(); i++) {
		cur_symb = source_str[i];
		if (contains(source_str[i - 1], alph_opening_brackets) && cur_symb == '-')
			tmp += '0';
		tmp += cur_symb;
	}
	modified_str = tmp;
}

void Expression::cut() {

	std::stack<char> operations_stack;
	rewriteForUnaryMinus();
	if (is_correct == false) return; 
	char cur_symb;
	std::string token;

	for (int i = 0; i < modified_str.size(); i++) {
		cur_symb = modified_str[i];
		if (contains(cur_symb, alph_operations) || contains(cur_symb, alph_opening_brackets) || contains(cur_symb, alph_closing_brackets)) {
			if (token != "") {
				
				postfix_form.push_back(token);
				if (in(token, alph_constants)) {
					operands.insert({ token,constants[token] });
				}
				else {
					variables_list.push_back(token);
					operands.insert({ token, (contains(token[0],alph_letters)) ? 0.0 : std::stod(token) });
				}
				token = "";
			}
		}
		if (contains(cur_symb, alph_opening_brackets)) {
			operations_stack.push(cur_symb);
		}
		else if (contains(cur_symb, alph_closing_brackets)) {
			while (!contains(operations_stack.top(), alph_opening_brackets)) {
				postfix_form.push_back(std::string(1, operations_stack.top()));
				operations_stack.pop();
			}
			operations_stack.pop();
		}
		else if (contains(cur_symb, alph_operations)) {
			while (operations_stack.empty()==false&&(priority[cur_symb] <= priority[operations_stack.top()])) {
				postfix_form.push_back(std::string(1,operations_stack.top()));
				operations_stack.pop();

			}
			operations_stack.push(cur_symb);
		}

		if (contains(cur_symb, alph_nums) || contains(cur_symb, alph_letters)||contains(cur_symb,alph_separator))
			token += cur_symb;
	
	}
	if (token != "") {
		postfix_form.push_back(token);
		if (in(token, alph_constants)) 
			operands.insert({ token,constants[token] });
		else {
			operands.insert({ token, (contains(token[0],alph_letters)) ? 0.0 : std::stod(token) });
			variables_list.push_back(token);
		}
	}
	while(operations_stack.empty()==false) {
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
			if (v2 == 0) {
				std::cout << "Division by zero\n"; //throw("Division by zero");
			is_correct = false;
			break;
			}
			st.push(v1 / v2);
		}
		else st.push(operands[lexem]);
	}
	if(st.empty()==false)
	res = st.top();
}

Expression::Expression(std::string str) {
	source_str = str;
	
	is_correct=this->expressionIsCorrect();
	if (is_correct) {
		this->cut();
		this->calculate();
	}
}

Expression& Expression::operator=(const Expression& exp) {
	if (this == &exp) return *this;
	operands = exp.operands;
	postfix_form = exp.postfix_form;
	is_correct = exp.is_correct;
	res = exp.res;
	return *this;
}

void delete_spaces(std::string& str) {
	std::string tmp;
	for (int i = 0; i < str.size(); i++)
		if (str[i] != ' ')
			tmp += str[i];
	str = tmp;
}

Expression& Expression::operator=(std::string str) {
	delete_spaces(str);

	std::string token1, token2;
	bool flag = true;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == '=') {
			flag = false;
			continue;
		}
		if (flag)
			token1 += str[i];
		else token2 += str[i];
	}
	if (token2 == "") {
		source_str = str;
		is_correct = expressionIsCorrect();
		if (is_correct) {
			cut();
			calculate();
		}
	}
	else if (source_str=="" && isVariable(token1)) {
		Expression tmpexp2;
		tmpexp2.operands = operands;
		tmpexp2 = token2;
		if (!tmpexp2.is_correct) throw("Expression is not correct");
		operands[token1] = tmpexp2.res;
	}
	else if(in(token1,variables_list)) {
		Expression tmpexp2;
		tmpexp2.operands = operands;
		tmpexp2 = token2;
		if (!tmpexp2.expressionIsCorrect()) throw("Expression is not correct");
		
		operands[token1] = tmpexp2.res;
		calculate();
	}
	else {
		Expression tmpexp1(token1), tmpexp2(token2);
		if (tmpexp1.is_correct && tmpexp2.is_correct) {
			if (tmpexp1.res == tmpexp2.res) {
				source_str = str;
				res = tmpexp1.res;
				is_correct = true;
			}
			else is_correct = false;
			
		}
		if(!is_correct)
		throw("Expressions is not correct");
	}
	/*
	if (!contains('=', tmp)) {
		clear();
		source_str = tmp;
		is_correct = expressionIsCorrect();

		if (is_correct)
			cut();
		else source_str = "";
	}
	else {
		for (auto symb : tmp) {
			if (symb == '=') {
				flag = true;
				continue;
			}
			if (flag == false)
				token1 += symb;
			else token2 += symb;
		}
		if (in(token1, alph_constants) || contains(token1[0], alph_nums)) {
			std::cout << "Can't change constant\n";
			is_correct = false;
		}
		else if (token2 != "") {
			Expression tmpexp;
			tmpexp.operands = operands;
			tmpexp = token2;
			operands[token1] = tmpexp.res;
		}
		else if (token2 == "") {
			std::cout << '=' << operands[token1];
		}
	}
	is_correct = expressionIsCorrect();
	if (is_correct) {
		calculate();
		
	}
	*/
	return *this;
}

std::istream& operator>>(std::istream& istream,Expression& exp) {
	std::string tmp;
	std::getline(istream, tmp,'\n');
	exp = tmp;
	/*
	std::string tmp,token1,token2;
	bool flag=false;
	istream >> tmp;
	if (!contains('=',tmp)) {
		exp.clear();
		exp.source_str = tmp;
		exp.is_correct = exp.expressionIsCorrect();

		if (exp.is_correct)
			exp.cut();
		else exp.source_str = "";
	}
	else { 
		for (auto symb : tmp) {
			if (symb == '=') {
				flag = true;
				continue;
			}
			if (flag == false)
				token1 += symb;
			else token2 += symb;
		}
		if (in(token1, exp.alph_constants) || contains(token1[0], exp.alph_nums)) {
			std::cout << "Can't change constant\n";
			exp.is_correct = false;
		}
		else if(token2!="") {
			Expression tmpexp;
			tmpexp.operands = exp.operands;
			tmpexp = token2;
			exp.operands[token1] = tmpexp.res;
		}
		else if (token2 == "") {
			std::cout << '=' << exp.operands[token1];
		}
	}
	exp.is_correct = exp.expressionIsCorrect();
	if (exp.is_correct) {
		exp.calculate();
	}
	*/
	return istream;
}
std::ostream& operator<<(std::ostream& ostream, const Expression& exp) {
	if (exp.is_correct)
		ostream << exp.source_str<<"="<<exp.res;
	else if(exp.source_str!="")ostream << "Expression is not correct";
	return ostream;
}
