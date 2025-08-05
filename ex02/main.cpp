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

//	controle des values envoyer
//	Former les paires (min, max)
// 	Trier récursivement les max
// 	Insérer les min dans l’ordre optimal
// 	Insérer l'élément restant s’il existe
// 	Retourner la liste finale


/*
- Faire un container de pair 
- trier les paires
- mettre les grand dans un autre container
- trie en recursif les grand
- trier le container des pair par rapport au trie des grands
- creer un container et mettre tout les petits en gardant bien l'ordre des paires (pre-ranger)
- inserer les petits dans le container des grands avec la suite et en se basant avec (le debut/le grand) de leur paire
- en utilisant en limite haute le grand de sa paire

U n = U n-1 + 2 * U n-2

Faire la gestion des blocks de paires et ranger a partir des plus grands des block de paire

Apres avoir creer mes block par rapport au nombre dans la suite 
Creer une fonction template de max mais avec un iter sur les nombre present dedans

*/