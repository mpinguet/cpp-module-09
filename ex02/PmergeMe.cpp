#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other) : vec(other.vec), deq(other.deq) {}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other)
	{
		vec = other.vec;
		deq = other.deq;
	}
	return *this;
}

void show_vector(std::string &str, std::vector<int> vec)
{
	std::cout << str;
	for (size_t i = 0; i < vec.size(); i++)
		std::cout << vec[i] << " ";
	std::cout << std::endl;
	
}
int PmergeMe::parse_input(int argc, char **argv)
{
	int n;
	for (int i = 1; i < argc; i++)
	{
		if (!argv[i][0])
		{
			std::cerr << "Error" << std::endl;
			return (1);
		}
		for (int j = 0; argv[i][j]; j++)
		{
			if (!isdigit(argv[i][j]))
			{
				std::cerr << "Error" << std::endl;
				return (1);
			}
		}
		n = atoi(argv[i]);
		if (n < 0)
		{
			std::cerr << "Error" << std::endl;
			return (1);
		}
		vec.push_back(n);
	}
	std::string bef = "Before: ";
	show_vector(bef, vec);
	return (0);	
}
