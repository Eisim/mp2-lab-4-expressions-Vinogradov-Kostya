#include"expression.h"
//20+(((-1.2))/10.0)
//a-2+(-1)
int main() {

	Expression a;

	while (true) {
		std::cin >> a;
		std::cout << a << "\n\n";
		//for (int i = 0; i < a.getPostfixForm().size(); i++)
		//	std::cout << a.getPostfixForm()[i]<<" ";
	}


	return 0;
}