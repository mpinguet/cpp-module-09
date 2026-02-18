#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	BitcoinExchange a;

	if (argc != 2)
	{
		std::cout << "Error: could not open file." << std::endl;
		return 1;
	}

	a.loadMap();
	a.processInput(std::string(argv[1]));
}