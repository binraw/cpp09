#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
    _numberOfPairs = 0;
    _oddArgs = 0;
    _levels = 1;
}

PmergeMe::PmergeMe(int argc, char **argv)
{
    _numberOfPairs = 0;
    _oddArgs = 0;
    _levels = 1;
    createDoublon(argc, argv);
    createlargestContainer();
    iter(_containerDequeLong, printElement<int>);
    reorderContainerPair();
    preorderContainerShort();
    std::cout << "VALUE SHORT CONTAINER :"  << std::endl;
    iter(_containerDequeShortPreorder, printElement<int>);
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

bool isNumber(std::string &str)
{
	if (str.empty())
		return false;
	for (size_t i = 0; i < str.size(); i++)
	{
		char c = str[i];
		if (c < '0' || c > '9')
			return false;
	}
	return true;
}

void PmergeMe::controlValue(char *value)
{
    int result;
    try {
        result = std::atoi(value);
    }
    catch (std::invalid_argument const& ex){
        throw ErrorArgs();
    }
    catch (std::out_of_range const& ex){
        throw ErrorRange();
    }
    if (result)
    {
        for (std::deque<std::pair<int, int>>::iterator it = _containerDequePair.begin(); it != _containerDequePair.end(); it++)
        {
            if (it->first == result || it->second == result)
                throw ErrorDouble(); //doublon
        }
    }
    else
        throw ErrorNull(); // no value
}

// void PmergeMe::createDoublon(int argc, char **argv)
// {
//     if ((argc % 2) == 0) // si impair args
//     {
//         int i = 1;
//         controlValue(argv[i]);
//         _containerDequeLong.push_back(std::atoi(argv[i]));
//         for (i = 2; i < argc; i += 2) 
//         {
//             if (i + 1 < argc)
//             {
//                 controlValue(argv[i]);
//                 controlValue(argv[i + 1]);
//                 int first = std::atoi(argv[i]);
//                 int second = std::atoi(argv[i + 1]);
//                 _containerDequePair.push_back(std::make_pair(first, second));
//             }
//         }
//     }
//     else 
//     {
//         for (int i = 1; i < argc; i += 2) 
//         {
//             if (i + 1 < argc)
//             {
//                 controlValue(argv[i]);
//                 controlValue(argv[i + 1]);
//                 int first = std::atoi(argv[i]);
//                 int second = std::atoi(argv[i + 1]);
//                 _containerDequePair.push_back(std::make_pair(first, second));
//             }
//         }
//     }

//     for (std::deque<std::pair<int, int>>::iterator it = _containerDequePair.begin(); it != _containerDequePair.end(); it++)
//     {
//         if (::min(it->first, it->second) == it->second)
//             ::swap(it->first, it->second);
//     }
// }


// void PmergeMe::createlargestContainer()
// {
//     for (std::deque<std::pair<int, int>>::iterator it = _containerDequePair.begin(); it != _containerDequePair.end(); it++)
//         _containerDequeLong.push_back(it->second);
//      recursiveSort(_containerDequeLong);
// }


// void PmergeMe::recursiveSort(std::deque<int>& arr) 
// {
//     if (arr.size() <= 1) 
//         return;


//     size_t mid = arr.size() / 2;
//     std::deque<int> left(arr.begin(), arr.begin() + mid);
//     std::deque<int> right(arr.begin() + mid, arr.end());


//     recursiveSort(left);
//     recursiveSort(right);


//     size_t i = 0, j = 0, k = 0;
//     while (i < left.size() && j < right.size()) 
//     {
//         if (left[i] <= right[j]) 
//         {
//             arr[k++] = left[i++];
//         } 
//         else 
//         {
//             arr[k++] = right[j++];
//         }
//     }

//     while (i < left.size()) 
//     {
//         arr[k++] = left[i++];
//     }
//     while (j < right.size()) 
//     {
//         arr[k++] = right[j++];
//     }
// }

void PmergeMe::reorderContainerPair()
{
    std::deque<std::pair<int, int>> reorderContainer;
    for (std::deque<int>::iterator it = _containerDequeLong.begin(); it != _containerDequeLong.end(); it++)
    {
        for (std::deque<std::pair<int, int>>::iterator iter = _containerDequePair.begin(); iter != _containerDequePair.end(); iter++)
        {
            if (*it == iter->second)
            {
                reorderContainer.push_back(*iter);
                break;
            }
        }
    }
    _containerDequePair = reorderContainer;
}

/*
    

*/


void PmergeMe::preorderContainerShort()
{
    for (std::deque<std::pair<int, int>>::iterator it = _containerDequePair.begin(); it != _containerDequePair.end(); it++)
    {
        _containerDequeShortPreorder.push_back(it->first);
    }
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


/* CHANGEMENT DE PLAN :
Calcul du Nombre de Paires
Gestion des Paires Impaires
Détermination des Itérateurs
Échange des Paires
Appel Recursif
Gestion des Éléments Restants
Insertion des Éléments Restants
Remplacement des Valeurs dans le Conteneur Original

*/



void PmergeMe::createDoublon(int argc, char **argv)
{
    if ((argc % 2) == 0) // si impair args
    {
        _oddArgs = 1;
        int i = 1;
        controlValue(argv[i]);
        _containerDequeRest.push_back(std::atoi(argv[i]));
        for (i = 2; i < argc; i += 2) 
        {
            if (i + 1 < argc)
            {
                controlValue(argv[i]);
                controlValue(argv[i + 1]);
                int first = std::atoi(argv[i]);
                int second = std::atoi(argv[i + 1]);
                _containerDequePair.push_back(std::make_pair(first, second));
                _numberOfPairs++;
            }
        }
    }
    else 
    {
        for (int i = 1; i < argc; i += 2) 
        {
            if (i + 1 < argc)
            {
                controlValue(argv[i]);
                controlValue(argv[i + 1]);
                int first = std::atoi(argv[i]);
                int second = std::atoi(argv[i + 1]);
                _containerDequePair.push_back(std::make_pair(first, second));
                _numberOfPairs++;
            }
        }
    }
    for (std::deque<std::pair<int, int>>::iterator it = _containerDequePair.begin(); it != _containerDequePair.end(); it++)
    {
        if (::min(it->first, it->second) == it->second)
            ::swap(it->first, it->second);
    }
}

void PmergeMe::recursiveSort(std::deque<std::pair<int, int>>& arr)
{
    int actualLevels = _levels;
    int groupCount = arr.size() / actualLevels; // ici pour verifier qu'il y a toujours des comparaisons possible vu qu'on regroupe de plus en plus
    if (groupCount < 2)
        return;
    bool groupOdd = false;
    if ((groupCount % 2) != 0)
        groupOdd = true;
    std::deque<std::pair<int, int>>::iterator start = arr.begin();
    std::deque<std::pair<int, int>>::iterator end = start; // obliger de initialiser avant advance
    std::deque<std::pair<int, int>>::iterator lastGroup = start;
    std::advance(end, _levels * groupCount);
    std::advance(lastGroup, -(groupOdd * groupCount)); // reel fin a trier de l'etape
    for (std::deque<std::pair<int, int>>::iterator it = start; it != lastGroup; std::advance(it, actualLevels))
    { // ici je dois determiner la comparaison 
        /* jai mis actualLevels a 1 de base car je procede deja avec des paires
        */
        std::deque<std::pair<int, int>>::iterator maxGroupActual = it;
        std::deque<std::pair<int, int>>::iterator maxGroupeNext = it + actualLevels;
        if (::min(maxGroupActual->second, maxGroupeNext->second) == maxGroupeNext->second)
            ::swap(maxGroupActual, maxGroupeNext); // la je crois que je vais bien swap mais a verifier

    }
    _levels += 1; // pour donner au prochain une pair de plus dans son groupe
    recursiveSort(arr);
     // au moment ou je rappelle cette fnction prendre en compte que je suis deja en mode pair
}


