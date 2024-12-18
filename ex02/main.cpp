#include "PmergeMe.hpp"

#include <iostream>

int main(int argc, char **argv)
{

	std::cout << "Before: ";
	for (int i = 1; i < argc; i++)
		std::cout << argv[i] << " ";
	std::cout << std::endl;
	std::cout << "After: " << std::endl;
}
