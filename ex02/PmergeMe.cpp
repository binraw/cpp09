#include "PmergeMe.hpp"

/*
Process de mon algo ford-Johnson

dabord je recupere tout les nombres en verifiant leur valeur + si il n'y a pas de doublon
ensuite je les mets dans un container de pair
qui va par la suite directement trier ses deux valeurs : Petit - Grand
Ensuite je mets tout dans un nouveau container simple : _simpleTest
Apres je commence ma recursive ou je vais checker seulement la valeur la plus grande
et echanger avec un swap les paires exemple : 2-56 swap avec un 43-47.
Je continue dans la recursive qui va faire le meme travail avec des paires de paires 
donc 4 elements puis 8 etc ... 
Apres (etant inverser car recursif) je vais insert mes groupes en se basant toujours sur le plus grand
Ici j'ai passer mes groupes sous forme de deque<deque<int> beaucoup plus simple pour insert
sans s'embeter avec l'insertion des autres nombres qui font partie de ce groupe en question.
a chaque fin d'insert je redonne toutes mes valeurs a mon : _simpleTest
Pour que le prochain travail avec deja des values deja trier/insert 
je fais ca en ercursif jusqu'au paires car la le insert comme j'ai dis est inverser donc diminue
et ensuite je sors de la recursive et je relance la fonction en prenant seulement les nombre par groupe de 1. 
et ensuite si la liste de base etait impair j'avais mis le nombre de coter lors de la premiere creation des paires
je l'ajoute en insert seul de facon binaire dans l'algo de base il n'y a pas de methode + opti conseiller. 

Si dans insert j'ai des valeurs en trop (pas assez pour creer un groupe egale) alors je les mets dans un rest
et a la fin du niveau de insert je les rajoute a la fin ils finiront par etre assez nombreux pour creer un groupe

*/
PmergeMe::PmergeMe()
{
    _levels = 1;
}


PmergeMe::PmergeMe(int argc, char **argv)
{
    if (argc < 3)
        throw std::invalid_argument("Not enough arguments");
        
    _levels = 1;
    int levelsDeque = _levels;
    int levelsVector = _levels;
    
    clock_t start = clock();
    try {
        createDoublonTemp(argc, argv, _containerDequePair, _containerDequeRest);
        
        if (_containerDequePair.empty() && _containerDequeRest.empty())
            throw std::invalid_argument("No valid data to process");
            
        _simpleTestDeque = createSimpleContainerTemp(_containerDequePair, _simpleTestDeque);
        recursiveSortTemp(_simpleTestDeque, levelsDeque, _containerDequeOfDeque);
        duoSortTemplate(_simpleTestDeque, _containerDequePair);

        if (_containerDequeRest.size() == 1)
        {
            std::deque<int>::iterator it = _containerDequeRest.begin();
            std::deque<int>::iterator posValid = std::lower_bound(_simpleTestDeque.begin(), _simpleTestDeque.end(), *it);
            _simpleTestDeque.insert(posValid, *it);
        }
    }
    catch (...) {
        throw;
    }
    
    clock_t end = clock();
    iter(_simpleTestDeque, printElementFinal<int>);
    double duration = double(end - start) / CLOCKS_PER_SEC;
    std::cout << "\nTime to process a range of " << _simpleTestDeque.size()  << " elements with std::deque : " << duration << " secondes." << std::endl;


    clock_t startVector = clock();
    try {
        createDoublonTemp(argc, argv, _containerVectorPair, _containerVectorRest);
        _simpleTestVector = createSimpleContainerTemp(_containerVectorPair, _simpleTestVector);
        recursiveSortTemp(_simpleTestVector, levelsVector,_containerVectorOfVector);
        duoSortTemplate(_simpleTestVector, _containerVectorPair);

        if (_containerVectorRest.size() == 1)
        {
            std::vector<int>::iterator it = _containerVectorRest.begin();
            std::vector<int>::iterator posValid = std::lower_bound(_simpleTestVector.begin(), _simpleTestVector.end(), *it);
            _simpleTestVector.insert(posValid, *it);
        }
    }
    catch (...) {
        throw; 
    }
    
    clock_t endVector = clock();
    iter(_simpleTestVector, printElementFinal<int>);
    double timeVector = double(endVector - startVector) / CLOCKS_PER_SEC;
    std::cout << "\nTime to process a range of " << _simpleTestVector.size()  << " elements with std::vector : " << timeVector << " secondes." << std::endl;
}

PmergeMe::PmergeMe(const PmergeMe &other)
{
    *this = other;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    return *this;
}

PmergeMe::~PmergeMe()
{

}


bool isNumber(const std::string &str)
{
	if (str.empty())
		return false;
	
	size_t start = 0;
	if (str[0] == '+' || str[0] == '-')
	{
		if (str.size() == 1)
			return false;
		start = 1;
	}
	
	for (size_t i = start; i < str.size(); i++)
	{
		char c = str[i];
		if (c < '0' || c > '9')
			return false;
	}
	return true;
}


const char* PmergeMe::ErrorArgs::what() const  throw()
{
    return "Invalid Arguments.";
}

const char* PmergeMe::ErrorDouble::what() const  throw()
{
    return "Double values.";
}

const char* PmergeMe::ErrorNull::what() const  throw()
{
    return "NULL arguments.";
}

const char* PmergeMe::ErrorRange::what() const  throw()
{
    return "Out of range value.";
}



int jacobsthalValue(int n) 
{
    return static_cast<int>(std::round((std::pow(2, n + 1) + (n % 2 == 0 ? 1 : -1)) / 3));
}