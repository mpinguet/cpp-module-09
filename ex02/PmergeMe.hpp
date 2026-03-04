#pragma once

#include <vector>
#include <deque>
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <climits>

class PmergeMe
{
private:
	std::vector<int> vec;
	std::deque<int> deq;
public:
    PmergeMe();
    ~PmergeMe();
	PmergeMe(const PmergeMe &);
	PmergeMe &operator=(const PmergeMe &);
    int parse_input(int argc, char **argv);
};