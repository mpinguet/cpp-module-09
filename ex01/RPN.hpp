#pragma once

#include <stack>
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>

class RPN
{
private:
	std::stack<int> stack;
public:
	RPN();
	RPN(const RPN &other);
	RPN &operator=(const RPN &other);
	~RPN();

	int parse_RPN(const std::string &);
	void calcul_rpn(const std::string &);
};