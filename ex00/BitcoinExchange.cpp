#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &bit): db(bit.db) {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &bit)
{
	if (this != &bit)
		this->db = bit.db;
	return (*this);
}

void BitcoinExchange::loadMap()
{
	std::string part1;
	std::string part2;

	std::ifstream file("data.csv");
	if (!file)
	{
		std::cerr << "Error: could not open file" << std::endl;
		return ;
	}
	getline(file, part1);

	while (getline(file, part1, ','))
	{
		getline(file, part2);
		double value = atof(part2.c_str());
		this->db[part1] = value;
	}

	std::map<std::string, double>::iterator it = db.find("2022-03-26");

	if (it == db.end())
		std::cout << "non existente" << std::endl;
	else
		std::cout << it->second << std::endl;
}