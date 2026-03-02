#include "RPN.hpp"

RPN::RPN() {};
RPN::~RPN() {};

int isOperator(int o)
{
	if (o == '*')
		return (3);
	if (o == '+')
		return (1);
	if (o == '-')
		return (2);
	if (o == '/')
		return (4);
	return (0);
}

int RPN::parse_RPN(const std::string &str)
{
	int n = 0;
	int dig = 0;
	int op = 0;
	int last_char = 0;
	for (size_t i = 0; i < str.size(); i++)
	{
		if (isdigit(str[i]) || isOperator(str[i]) || isspace(str[i]))
		{
			if (isOperator(str[i]))
			{
				last_char = 2;
				op += 1;
			}
			if (isdigit(str[i]))
			{
				dig += 1;
				n += 1;
				last_char = 1;
			}
			else
				dig = 0;
			if (dig > 1)
			{
				std::cout << "Error" << std::endl;
				return (1);
			}
		}
		else
		{
			std::cout << "Error" << std::endl;
			return (1);
		}
	}
	if (op + 1 != n || last_char == 1)
	{
		std::cout << "Error" << std::endl;
		return (1);
	}
	return (0);
}

void RPN::calcul_rpn(const std::string &str)
{
	int a;
	int b;
	for (size_t i = 0; i < str.size(); i++)
	{
		if (isdigit(str[i]))
			this->stack.push(str[i] - '0');
		if (isOperator(str[i]))
		{
			if (isOperator(str[i]) == 1)
			{
				a = stack.top();
				stack.pop();
				b = stack.top();
				stack.pop();
				stack.push(b + a);
			}
			if (isOperator(str[i]) == 2)
			{
				a = stack.top();
				stack.pop();
				b = stack.top();
				stack.pop();
				stack.push(b - a);
			}
			if (isOperator(str[i]) == 3)
			{
				a = stack.top();
				stack.pop();
				b = stack.top();
				stack.pop();
				stack.push(b * a);
			}
			if (isOperator(str[i]) == 4)
			{
				a = stack.top();
				if (a == 0)
				{
					std::cout << "Erreur: infinity" << std::endl;
					return ;
				}
				stack.pop();
				b = stack.top();
				stack.pop();
				stack.push(b / a);
			}
		}
	}
	std::cout << stack.top() << std::endl;
}