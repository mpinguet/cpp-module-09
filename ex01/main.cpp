#include "RPN.hpp"

int main(int argc, char **argv)
{
	RPN rpn;
	if (argc != 2)
	{
		std::cout << "Two argument requiered" << std::endl;
		return (1);
	}
	if (rpn.parse_RPN(std::string (argv[1])))
		return (0);
	rpn.calcul_rpn(std::string(argv[1]));
}