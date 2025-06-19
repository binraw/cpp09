
#include <stack>
#include "RPN.hpp"

int main(int argc, char **argv)
{
	RPN test;
	std::string words;
	if (argc <= 1)
	{
		std::cerr << "Error number of argument" << std::endl;
		return -1;
	}
	for (int i = 1; i < argc; i++)
	{
		words  += argv[i];
		if (i < argc - 1)
			words += " ";
	}

	test.calcul(words);

	return (0);
}  
