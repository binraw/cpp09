#include "PmergeMe.hpp"

#include <iostream>

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "Usage: ./PmergeMe <numbers>" << std::endl;
		return 1;
	}

	std::cout << "Nombre de nombres : " << argc - 1 << std::endl;
	std::cout << "Before: ";
	for (int i = 1; i < argc; i++)
		std::cout << argv[i] << " ";
	std::cout << std::endl;
	std::cout << "After: " << std::endl;

	try {

		PmergeMe test(argc, argv);
	}
	catch(const std::exception& e)
	{
		std::cerr  << e.what() <<  '\n';
	}
	
}
