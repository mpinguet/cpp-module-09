#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
	PmergeMe me;
    if (argc == 1)
		return (0);
	if (me.parse_input(argc, argv))
		return (0);
	me.sortVector();
	return (0);
}