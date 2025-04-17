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

// controle des values envoyer
// Former les paires (min, max)
// 	Trier récursivement les max
// 	Insérer les min dans l’ordre optimal
// 	Insérer l'élément restant s’il existe
// 	Retourner la liste finale