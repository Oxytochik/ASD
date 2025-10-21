#include <iostream>
#include <string>
#include "../lib_Stack/stack.h"

bool CheckBrackets(const std::string& input) {
	int size;
	for (char bracket : input) {
		if (bracket == '(' || bracket == '{' || bracket == '[') size++;
	}
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