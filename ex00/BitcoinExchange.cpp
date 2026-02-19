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

int toDouble(std::string &str)
{
	std::stringstream ss(str);
	double i;
	ss >> i;

	return (i);
}

int parse_date(std::string date)
{
	size_t i = 0;
	std::string year;
	std::string month;
	std::string day;

	while(isdigit(date[i]) || date[i] == '-')
		i++;
	if (i != date.size())
		return (1);
	year = date.substr(0, date.find('-'));
	month = date.substr(date.find('-') + 1, date.find('-') - 2);
	day = date.substr(date.find('-') + 4);

	if (toDouble(year) < 2009 || toDouble(year) > 2022)
		return (1);
	if (toDouble(month) < 1 || toDouble(month) > 12)
		return (1);
	if (toDouble(day) < 1 || toDouble(day) > 31)
		return (1);

	return (0);
}

int parse_value(std::string value, std::string line)
{
	size_t i = 0;
	int sign = 0;
	int dot = 0;

	while (isspace(value[i]))
		i++;
	while(i != value.size())
	{
		if (value[i] == '-' || value[i] == '+' || isdigit(value[i]) || value[i] == '.')
		{
			if (value[i] == '.')
				dot += 1;
			if (value[i] == '-' || value[i] == '+')
				sign += 1;
			if (sign == 2 || dot == 2)
			{
				std::cout << "Error: bad input => " << line << std::endl;
				return (1);
			}
		}
		else
		{
			std::cout << "Error: bad input => " << line << std::endl;
			return (1);
		}
		i++;
	}
	if (toDouble(value) > 1000)
	{
		std::cout << "Error: too large a number." << std::endl;
		return (1);
	}
	if (toDouble(value) < 0)
	{
		std::cout << "Error: not a positive number." << std::endl;
		return (1);
	}
	return (0);
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
			if (parse_date(part1))
			{
				std::cout << "Error: bad input => " << line << std::endl;
				continue;
			}
			if (parse_value(part2, line))
				continue;
			
		}
	}
	return ;
}