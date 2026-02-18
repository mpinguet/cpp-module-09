#pragma once

#include <map>
#include <iostream>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>

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