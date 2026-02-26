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

double minYear;
double minMonth;
double minDay;

int parse_date_2(std::string date, std::string value)
{
	size_t i = 0;
	std::string year;
	std::string month;
	std::string day;
	int thread = 0;

	if (date.empty() || value.empty())
		return (1);
	while(isdigit(date[i]) || date[i] == '-')
	{
		if (date[i] == '-')
			thread += 1;
		i++;
	}
	if (thread != 2 || i != date.size())
		return (1);
	i = 0;
	thread = 0;
	while(isdigit(value[i]) || value[i] == '.')
	{
		if (value[i] == '.')
			thread += 1;
		i++;
	}
	if (thread > 1 || i != value.size())
		return (1);
	return (0);
}

int BitcoinExchange::loadMap()
{
	std::string part1;
	std::string part2;

	std::ifstream file("data.csv");
	if (!file)
	{
		std::cerr << "Error: could not open file" << std::endl;
		return 1;
	}
	getline(file, part1);
	if (part1 != "date,exchange_rate")
	{
		std::cout << "Error: you are not respecting the format 'date,exchange_rate'." << std::endl;
		return (1);
	}
	while (getline(file, part1, ','))
	{
		getline(file, part2);
		if (!parse_date_2(part1, part2))
		{
			double value = atof(part2.c_str());
			this->db[part1] = value;
		}
	}

	return (0);
}

double toDouble(const std::string &str)
{
	std::stringstream ss(str);
	double i;
	ss >> i;
	return (i);
}

int toInt(const std::string &str)
{
	std::stringstream ss(str);
	int i;
	ss >> i;
	return (i);
}


int parse_month(int year, int month, int day)
{
	if (month % 2 == 0)
	{
		if (month == 2)
		{
			if ((( year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
			{
				if (day > 29)
					return (1);
			}
			else
			{
				if (day > 28)
					return (1);
			}
		}
		else
		{
			if (day > 30)
				return (1);
		}
	}

	return (0);
}

int parse_date(std::string date)
{
	size_t i = 0;
	std::string year;
	std::string month;
	std::string day;
	int thread = 0;

	while(isdigit(date[i]) || date[i] == '-')
	{
		if (date[i] == '-')
			thread += 1;
		i++;
	}
	if (thread != 2)
		return (1);
	if (i != date.size())
		return (1);
	year = date.substr(0, date.find('-'));
	month = date.substr(date.find('-') + 1, date.find('-') - 2);
	day = date.substr(date.find('-') + 4);
	if (toInt(year) > 2100)
		return (1);
	if (toDouble(month) > 12 || toDouble(month) < 1 || toDouble(day) > 31 || toDouble(day) < 1)
		return (1);
	if (toDouble(year) < minYear)
		return (1);
	if (toDouble(year) == minYear && toDouble(month) < minMonth)
		return (1);
	if (toDouble(year) == minYear && toDouble(month) == minMonth && toDouble(day) < minDay)
		return (1);
	if (parse_month(toInt(year), toInt(month), toInt(day)))
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

void get_max_min_date(std::map<std::string, double > db)
{
	std::string date;
	size_t i = 0;
	std::map<std::string, double>::iterator it = db.begin();

	if (it != db.end())
		date = it->first;
	while(isdigit(date[i]) || date[i] == '-')
		i++;
	minYear = toDouble(date.substr(0, date.find('-')));
	minMonth = toDouble(date.substr(date.find('-') + 1, date.find('-') - 2));
	minDay = toDouble(date.substr(date.find('-') + 4));

	i = 0;
	it = db.end();
	--it;
	if (it != db.end())
		date = it->first;
	while(isdigit(date[i]) || date[i] == '-')
		i++;
	return ;
}

int lower_bound_and_calcul(const std::map<std::string, double>& db,
                           const std::string& date,
                           const std::string& value)
{
    if (db.empty())
        return 1;

    std::map<std::string, double>::const_iterator it = db.lower_bound(date);

    if (it != db.end() && it->first == date)
    {
        std::cout << date << " => " << value << " = " << toDouble(value) * it->second << std::endl;
        return 0;
    }

    if (it == db.begin())
        return 1;

    --it;

    std::cout << date << " => " << value << " = " << toDouble(value) * it->second << std::endl;

    return 0;
}

int wrong_pipe(std::string line)
{
	int i = 0;
	int pipe = 0;
	while(line[i])
	{
		if (line[i] == '|')
			pipe += 1;
		if (pipe > 1)
			return (1);
		i++;
	}
	if (line[i - 1] == '|')
		return (1);
	return (0);
}

int wrong_part(std::string part1, std::string part2)
{
	int i = 0;
	while(isspace(part1[i]) && part1[i])
		i++;
	if (!part1[i])
		return (1);
	i = 0;
	while(isspace(part2[i]) && part2[i])
		i++;
	if (!part2[i])
		return (1);
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
	if (this->db.empty())
		return ;
	get_max_min_date(this->db);
	getline(file, line);
	if (line != "date | value")
		std::cout << "Error: you are not respecting the format 'date | value'." << std::endl;
	while(getline(file, line))
	{
		if (line.find('|') == std::string::npos || wrong_pipe(line))
			std::cout << "Error: bad input => " << line << std::endl;
		else
		{
			part1 = line.substr(0, line.find('|') - 1);
			part2 = line.substr(line.find('|') + 2);
			if (wrong_part(part1, part2))
			{
				std::cout << "Error: bad input => " << line << std::endl;
				continue;
			}
			if (parse_date(part1))
			{
				std::cout << "Error: bad input => " << line << std::endl;
				continue;
			}
			if (parse_value(part2, line))
				continue;
			lower_bound_and_calcul(this->db, part1, part2);
		}
	}
	return ;
}