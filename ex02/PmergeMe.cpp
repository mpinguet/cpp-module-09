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

int toInt(char *str)
{
	std::stringstream ss;
	std::stringstream ss2;
	int i;
	double d;

	ss << str;
	ss2 << str;
	ss >> i;
	ss2 >> d;

	
	if (d > INT_MAX)
		return -1;
	return i;
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
		n = toInt(argv[i]);
		if (n < 0)
		{
			std::cerr << "Error" << std::endl;
			return (1);
		}
		vec.push_back(n);
		deq.push_back(n);
	}
	std::string bef = "Before: ";
	show_vector(bef, vec);
	return (0);

}


void seq_jacob(std::vector<int> &jacob, std::vector<int> small)
{
	int index;

	jacob.push_back(0);
	jacob.push_back(1);
	for (size_t i = 2; i < small.size(); i++)
	{
		index = jacob[i - 1] + 2 * jacob[i - 2];
		if (index >= (int)small.size())
			break;
		jacob.push_back(index);
	}
}

void insert_small(std::vector<int> &jacob, std::vector<int> &main_chain, std::vector<int> &small)
{
	std::vector<bool> used(small.size(), false);
	for (size_t i = 0; i < jacob.size(); i++)
	{
		std::vector<int>::iterator it = std::lower_bound(main_chain.begin(), main_chain.end(), small[jacob[i]]);
		main_chain.insert(it, small[jacob[i]]);
		used[jacob[i]] = true;
	}

	for (int i = small.size() - 1; i >= 0; i--)
	{
		if (used[i] == true)
			continue;
		else
		{
			std::vector<int>::iterator it = std::lower_bound(main_chain.begin(), main_chain.end(), small[i]);
			main_chain.insert(it, small[i]);
		}
	}
}

void PmergeMe::sortVector(std::vector<int> &vec)
{
	std::vector<int> big;
	std::vector<int> small;
	size_t len = vec.size();
	
	if (vec.size() <= 1)
		return;
	if (len % 2 != 0)
		len -= 1;
	for (size_t i = 0; i < len; i += 2)
	{
		if (vec[i] <= vec[i + 1])
		{
			small.push_back(vec[i]);
			big.push_back(vec[i + 1]);
		}
		else
		{
			small.push_back(vec[i + 1]);
			big.push_back(vec[i]);
		}
	}

	sortVector(big);

	std::vector<int> main_chain = big;
	std::vector<int> jacob;
	seq_jacob(jacob, small);
	insert_small(jacob, main_chain, small);
	if (len != vec.size())
	{
		std::vector<int>::iterator it = std::lower_bound(main_chain.begin(), main_chain.end(), vec[vec.size() - 1]);
		main_chain.insert(it, vec[vec.size() - 1]);
	}
	vec = main_chain;
}
void PmergeMe::main_algo_vec()
{
	sortVector(vec);
	for (size_t i = 0; i < vec.size(); i++)
	{
		std::cout << "vec [" << i << "] = " << vec[i] << std::endl;
	}
	
}
