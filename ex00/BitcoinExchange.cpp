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
}

int parse_date(std::string date)
{
	
}

void BitcoinExchange::processInput(std::string filename)
{
	std::ifstream file(filename.c_str());

	std::string line;
	std::string part1;
	std::string part2;
	if (!file)
	{
		std::cerr << "Error: could not open file" << std::endl;
		return ;
	}
	getline(file, line);
	if (line != "date | value")
		std::cout << "Error: you are not respecting the format 'date | value'." << std::endl;
	while(getline(file, line))
	{
		if (line.find('|') == std::string::npos)
			std::cout << "Error: bad input => " << line << std::endl;
		else
		{
			part1 = line.substr(0, line.find('|') - 1);
			part2 = line.substr(line.find('|') + 2);
		}
	}
	return ;
}