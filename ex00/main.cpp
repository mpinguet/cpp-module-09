#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	BitcoinExchange a;

	if (argc != 2)
	{
		std::cout << "Error: could not open file." << std::endl;
		return 0;
	}
	if (a.loadMap())
		return (0);
	a.processInput(std::string(argv[1]));
}