#include <iostream>
#include <string>
#include <initializer_list>
#include "../lib_Stack/stack.h"
#include "../lib_TwinList/TwinList.h"

int BracketsNumb(const std::string input) {
	int size = 0;
	for (char bracket : input) {
		if (bracket == '(' || bracket == '{' || bracket == '[') size++;
	}
	return size;
}

bool CheckBrackets(const std::string input) {
	int size = BracketsNumb(input);
	Stack<char> string(size);
	for (char element : input) {
		if (element == '(' || element == '{' || element == '[') {
			string.push(element);
		}
		else if(element == ')' || element == '}' || element == ']'){
			if (string.is_empty()) {
				//throw std::logic_error("For close bracket doesnt exist open bracket");
				return false;
			}
			else {
				char last_element = string.top();
				string.pop();
				if ((element == ')' && last_element != '(') || (element == ']' && last_element != '[') || (element == '}' && last_element != '{')) {
					//throw std::logic_error("Bracket logic incorrect");
					return false;
				}

			}
		}
	}
	return string.is_empty();
}

bool is_in(const char element, char arr[], int size) {
	
	for (int i = 0; i<size; i++){
		if (element == arr[i]) {
			return true;
		}
	}
	return false;
}

void read_expression(const std::string expression) {
	int size = expression.size();
	Stack<char> breckets(size);
	Stack<char> oper_numb(size);
	bool space = false;
	char numbers[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
	char operators[5] = { '*', '+', '-', '/', '^' };
	char alphabet[3] = { 'x', 'y', 'z' };

	for (char element : expression) {
		if (element == ' ') {
			space = true;
			continue;
		}
		//breckets block
		if (element == '(') {
			if (!oper_numb.is_empty() && (is_in(oper_numb.top(), numbers, 10) || is_in(oper_numb.top(), alphabet, 3))) {
				throw std::logic_error("Uncorrect position of operand and open breckets");
			}
			breckets.push(element);
			space = false;
			continue;
		}
		if (element == ')') {
			if (breckets.is_empty()) {
				throw std::logic_error("For close bracket doesnt exist open bracket");
			}
			else {
				if (is_in(oper_numb.top(), operators, 5)) {
					throw std::logic_error("Close breckets after operation symbol");
				}
				else {
					char last_element = breckets.top();
					breckets.pop();
					oper_numb.push(')');
					space = false;
					continue;
				}
				

			}
		}
		//number and opearatin block

		if (is_in(element, numbers, 10) || is_in(element, alphabet, 3)) {
			if ((oper_numb.is_empty() || is_in(oper_numb.top(), operators, 5)) 
				|| 
				(is_in(oper_numb.top(), numbers, 10) && space == false && (!is_in(element, alphabet, 3)))) 
			{
				oper_numb.push(element);
				space = false;
				continue;
			}
			else {
				throw std::logic_error("Incorrect pos of operor");
			}
		}
		if (is_in(element, operators, 5)) {
			if (oper_numb.is_empty()) {
				throw std::logic_error("Operation symbol cant be first");
			}
			else if (is_in(oper_numb.top(), numbers, 10) || is_in(oper_numb.top(), alphabet, 3) || (oper_numb.top() == ')')) {
				oper_numb.push(element);
				space = false;
				continue;
			}
			else {
				throw std::logic_error("Uncorrect operator position");
			}

		}
		throw std::logic_error("Uncorrect symbol");
		
	}
	if (oper_numb.is_empty()) {
		throw std::logic_error("Empty expression");
	}
	if (!breckets.is_empty()) {
		throw std::logic_error("Unclosed brackets");
	}
	if (is_in(oper_numb.top(), operators, 5)) {
		throw std::logic_error("Operation symbol cant be last symbol");
	}
}
template <class T>
bool is_looped(List<T> list) {
	list.Iterator()

}
