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

// PmergeMe::PmergeMe(int argc, char **argv)
// {
//     _levels = 2;
//     clock_t start = clock();
//     createDoublon(argc, argv);
//     _simpleTest = createSimpleContainer(_containerDequePair);
//     recursiveSort(_simpleTest);
//     duoSort(_simpleTest);

//     if (_containerDequeRest.size() == 1)
//     {
//         std::deque<int>::iterator it = _containerDequeRest.begin();
//         std::deque<int>::iterator posValid = std::lower_bound(_simpleTest.begin(), _simpleTest.end(), *it);
//         _simpleTest.insert(posValid, *it);

//     }
//     clock_t end = clock();
//     iter(_simpleTest, printElementFinal<int>);
//     // std::cout << "Nombre final d'elements : " << _simpleTest.size() << std::endl;
//     double duration = double(end - start) / CLOCKS_PER_SEC;
//     std::cout << "\nTime to process a range of " << _simpleTest.size()  << " elements with std::deque : " << duration << " secondes." << std::endl;
// }



PmergeMe::PmergeMe(int argc, char **argv)
{
    _levels = 1;
    int levelsDeque = _levels;
    int levelsVector = _levels;
    clock_t start = clock();
    createDoublonTemp(argc, argv, _containerDequePair, _containerDequeRest);
    _simpleTestDeque = createSimpleContainerTemp(_containerDequePair, _simpleTestDeque);
    recursiveSortTemp(_simpleTestDeque, levelsDeque, _containerDequeOfDeque);
    duoSortTemplate(_simpleTestDeque, _containerDequePair);

    if (_containerDequeRest.size() == 1)
    {
        std::deque<int>::iterator it = _containerDequeRest.begin();
        std::deque<int>::iterator posValid = std::lower_bound(_simpleTestDeque.begin(), _simpleTestDeque.end(), *it);
        _simpleTestDeque.insert(posValid, *it);

    }
    clock_t end = clock();
    iter(_simpleTestDeque, printElementFinal<int>);
    double duration = double(end - start) / CLOCKS_PER_SEC;
    std::cout << "\nTime to process a range of " << _simpleTestDeque.size()  << " elements with std::deque : " << duration << " secondes." << std::endl;

    clock_t startVector = clock();
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
    clock_t endVector = clock();
    iter(_simpleTestVector, printElementFinal<int>);
    double timeVector = double(endVector - startVector) / CLOCKS_PER_SEC;
    std::cout << "\nTime to process a range of " << _simpleTestVector.size()  << " elements with std::vector : " << timeVector << " secondes." << std::endl;

}

/*
C'est seulement le dernier insert que je dois opti car il prends bcp trop de temps mais deja il suffi de verifier 
par rapport a son max pour l'insert
*/



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

// std::deque<int> createSimpleContainer(std::deque<std::pair<int, int>> arr) // fait en templates
// {
//     std::deque<int> result;
//     for (std::deque<std::pair<int, int>>::iterator it = arr.begin(); it != arr.end(); it++)
//     {
//         result.push_back(it->first);
//         result.push_back(it->second);
//     }
//     return result;
// }



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




// void PmergeMe::controlValue(char *value) // fait en template
// {
//     int result;
//     try {
//         result = std::atoi(value);
//     }
//     catch (std::invalid_argument const& ex){
//         throw ErrorArgs();
//     }
//     catch (std::out_of_range const& ex){
//         throw ErrorRange();
//     }
//     if (result)
//     {
//         for (std::deque<std::pair<int, int>>::iterator it = _containerDequePair.begin(); it != _containerDequePair.end(); it++)
//         {
//             if (it->first == result || it->second == result)
//                 throw ErrorDouble(); //doublon
//         }
//     }
//     else
//         throw ErrorNull(); // no value
// }


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



// void PmergeMe::createDoublon(int argc, char **argv) // fait en template
// {
//     if ((argc % 2) == 0)
//     {
//         int i = 1;
//         controlValue(argv[i]);
//         _containerDequeRest.push_back(std::atoi(argv[i]));
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




// void swap_pair(std::deque<int>::iterator it, int pair_level, std::deque<int> &container) // fait en template
// {
//     std::deque<int>::iterator start = nextIt(it, -pair_level + 1);
//     std::deque<int>::iterator end = nextIt(start, pair_level);
//     if (start < it && end <= container.end())
//     {
//         while (start != end)
//         {
//             std::iter_swap(start, std::next(start, pair_level));
//             start++;
//         }
//     }
// }

/*
Ici la recurssive fais des groupe et swap les groupe en eux en se basant sur le plus grand du groupe
donc au debut fais des paires qui vont swap entre elles 
puis des paires de paires qui swap etc ... 
*/



// void PmergeMe::recursiveSort(std::deque<int>& arr) // fait en template
// {
//     if (arr.empty()) 
//         return;

//     int actualLevels = _levels;
//     int pair_units_nbr = arr.size() / actualLevels; // Nombre de paires
//     if (pair_units_nbr < 2)
//         return;

//     bool is_odd = pair_units_nbr % 2 == 1;

//     std::deque<int>::iterator start = arr.begin();
//     std::deque<int>::iterator last = nextIt(start, actualLevels * pair_units_nbr);
//     std::deque<int>::iterator end = last;
//     if (is_odd) 
//     {
//         --end; 
//     }

//     for (std::deque<int>::iterator it = start; it != end; std::advance(it, 2 * actualLevels))
//     {
//         std::deque<int>::iterator maxGroupActual = nextIt(it, actualLevels - 1);
//         if (nextIt(it, actualLevels * 2 - 1) >= end) 
//         {
//             break;
//         }
//         std::deque<int>::iterator maxGroupeNextIt = nextIt(it, actualLevels * 2 - 1);

//         if (maxGroupeNextIt < end) 
//         {
//             if (*maxGroupeNextIt < *maxGroupActual)
//             {
//                 ::swap_pair(maxGroupActual, actualLevels, arr);
//             }
//         }
//     }

//     _levels *= 2; // Incrémenter le niveau pour le prochain appel
//     recursiveSort(arr); // Appel récursif
//     recursiveInsertWithContainer(arr, actualLevels);
// }





    /*
    
    
    
    
    
    
    */

// void PmergeMe::recursiveInsertWithContainer(std::deque<int>& arr, int actualLevels) // fait en template
// {
//     std::deque<std::deque<int>> mainPart;
//     std::deque<std::deque<int>> pendingPart;
//     std::deque<int> rest;
//     int pair_units_nbr = arr.size() / actualLevels;
//     if (pair_units_nbr < 2)
//         return;

//     std::deque<int>::iterator start = arr.begin();
//     std::deque<int>::iterator end = nextIt(start, actualLevels * pair_units_nbr); // a voir si le reste je mets direct dans pendingPart

//         for (std::deque<int>::iterator it = end; it != arr.end(); it++)
//         {
//             rest.push_back(*it);
//         }


//     std::deque<std::deque<int>> allContainer;

    
//     for (size_t i = 0; i < arr.size(); i += actualLevels) 
//     {
//         std::deque<int> group;

//         for (size_t j = 0; j < actualLevels && (i + j) < arr.size(); ++j) 
//         {
//             group.push_back(arr[i + j]);
//         }

//         allContainer.push_back(group);
//     }
//         std::deque<std::deque<int>>::iterator maxGroupB = allContainer.begin(); // B1 max 
//         std::deque<std::deque<int>>::iterator maxGroupA = allContainer.begin() + 1; // A1 max
        
        
//         mainPart.push_back(*maxGroupB);  
//         mainPart.push_back(*maxGroupA);

//     if (pair_units_nbr > 2)
//     {
//         for (std::deque<std::deque<int>>::iterator it = maxGroupA + 1; it != allContainer.end(); it++)
//         {
//             pendingPart.push_back(*it);
//         }
//     }
    
    
//     if (pendingPart.size() != 0)
//     {
//         std::deque<std::deque<int>>::iterator startPending = pendingPart.begin();
//         std::deque<std::deque<int>>::iterator endPending = pendingPart.end();


//         size_t numJacob = jacobsthalValue(2);
    
//         if (startPending + numJacob < endPending)
//         {
//             for (size_t k = 2; startPending +  numJacob < endPending; ++k)
//             {
//                 std::deque<std::deque<int>>::iterator it = startPending +  numJacob;
//                 int lastElement = it->back();
//                 std::deque<std::deque<int>>::iterator posValid = std::lower_bound(mainPart.begin(), mainPart.end(), lastElement,
//                 [](const std::deque<int>& a, const int& b) 
//                 {
//                     return a.back() < b;
//                 });
//                 if (posValid == mainPart.end())
//                     mainPart.insert(posValid, *it);

//             int nu = (k == 2) ? 0 : k;
//             std::deque<std::deque<int>>::iterator newLimit = posValid;
//             for (int j = nu ; j <  numJacob - 1; j++)
//             {
//                 if (it - j >= startPending) 
//                 {
//                     for (std::deque<std::deque<int>>::iterator iter = startPending; iter != endPending; iter++)
//                     {
//                         int lastElement = iter->back();
//                         std::deque<std::deque<int>>::iterator pos = std::lower_bound(mainPart.begin(), mainPart.end(), lastElement,
//                         [](const std::deque<int>& a, const int& b) 
//                         {
//                             return a.back() < b;
//                         });
//                         if(pos == mainPart.end() || *pos != *iter)
//                             mainPart.insert(pos, *iter);
//                     }
//                 }

//             }
//             numJacob = jacobsthalValue(k + 1);
//             }
//         }
//         else
//         {
//             for (std::deque<std::deque<int>>::iterator it = startPending; it != endPending; it++)
//             {
//                 int lastElement = it->back();
//                 std::deque<std::deque<int>>::iterator posValid = std::lower_bound(mainPart.begin(), mainPart.end(), lastElement,
//                 [](const std::deque<int>& a, const int& b) 
//                 {
//                     return a.back() < b;
//                 });
//                 mainPart.insert(posValid, *it);
//             }

//         }
//     }

//         _simpleTest.clear();

//         for (std::deque<std::deque<int>>::iterator it = mainPart.begin(); it != mainPart.end(); it++)
//         {
//             for (std::deque<int>::iterator iter = it->begin(); iter != it->end(); ++iter)
//             {
//                _simpleTest.push_back(*iter); 
//             }
//         }

//         for (std::deque<int>::iterator it = rest.begin(); it != rest.end(); it++)
//         {
//                _simpleTest.push_back(*it); 
            
//         }
//     }

/*




*/









    /*
    
    
    
    
    
    
    
    
    */



// void PmergeMe::duoSort(std::deque<int>& arr) // fait en template
// {
//     std::deque<int> mainPart;
//     std::deque<int> pendingPart;
//     _containerDequePair.clear();
//     for (std::deque<int>::iterator it = arr.begin(); it != arr.end(); it += 2) 
//     {
//         if (it + 1 < arr.end())
//         {
            
//             int first = *it;
//             int second = *(it + 1);
//             _containerDequePair.push_back(std::make_pair(first, second));
//         }
//     }
//     mainPart.push_back(_containerDequePair.begin()->first);  
//     mainPart.push_back(_containerDequePair.begin()->second);


//     for (std::deque<std::pair<int, int>>::iterator it = _containerDequePair.begin() + 1; it != _containerDequePair.end(); it++)
//     {
//         pendingPart.push_back(it->first);
//     }

//     for (std::deque<std::pair<int, int>>::iterator it = _containerDequePair.begin() + 1; it != _containerDequePair.end(); it++)
//     {
//         mainPart.push_back(it->second);
//     }
    
//     if (pendingPart.size() != 0)
//     {
//         std::deque<int>::iterator startPending = pendingPart.begin();
//         std::deque<int>::iterator endPending = pendingPart.end();


//         size_t numJacob = jacobsthalValue(2);
    
//         if (startPending + numJacob < endPending)
//         {
//             for (size_t k = 2; startPending +  numJacob < endPending; ++k)
//             {
//                 std::deque<int>::iterator it = startPending +  numJacob;

//                 int lastElement = *it;
//                 std::deque<int>::iterator posValid = std::lower_bound(mainPart.begin(), mainPart.end(), lastElement);
//                 if (std::find(mainPart.begin(), mainPart.end(), *it) == mainPart.end())
//                     mainPart.insert(posValid, *it);

//             int nu = (k == 2) ? 0 : k;
            
//             for (int j = nu ; j <  numJacob - 1; j++)
//             {
//                 if (it - j >= startPending) 
//                 {
//                     for (std::deque<int>::iterator iter = startPending; iter != endPending; iter++)
//                     {
//                         int lastElement = *iter;

//                         std::deque<int>::iterator pos = std::lower_bound(mainPart.begin(), mainPart.end(), lastElement);
//                         if(pos == mainPart.end() || *pos != *iter)
//                             mainPart.insert(pos, *iter);
//                     }
//                 }

//             }
//             numJacob = jacobsthalValue(k + 1);
//             }
//         }
//         else
//         {
//             for (std::deque<int>::iterator it = startPending; it != endPending; it++)
//             {
//                 int lastElement = *it;
//                 std::deque<int>::iterator posValid = std::lower_bound(mainPart.begin(), mainPart.end(), lastElement);
//                 mainPart.insert(posValid, *it);
//             }

//         }
//     }
//         _simpleTest.clear();
//         _simpleTest = mainPart;

//     }

// int binome(int min, std::deque<std::pair<int, int>> arr)
// {
//     for (std::deque<std::pair<int, int>>::iterator it = arr.begin(); it != arr.end(); it++)
//     {
//         if (min == it->first)
//             return it->second;
//     }
//     return 0;
// }


int jacobsthalValue(int n) 
{
    return static_cast<int>(std::round((std::pow(2, n + 1) + (n % 2 == 0 ? 1 : -1)) / 3));
}