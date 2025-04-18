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


*/