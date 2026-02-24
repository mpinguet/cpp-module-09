#pragma once

#include <map>
#include <iostream>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


extern double maxYear;
extern double maxMonth;
extern double maxDay;
extern double minYear;
extern double minMonth;
extern double minDay;


class BitcoinExchange
{
private:
	std::map<std::string, double > db;
public:
	BitcoinExchange();
	~BitcoinExchange();
	BitcoinExchange(const BitcoinExchange&);
	BitcoinExchange &operator=(const BitcoinExchange&);
	
	void loadMap();
	void processInput(std::string filename);
};