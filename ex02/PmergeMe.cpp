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
    _numberOfPairs = 0;
    _oddArgs = 0;
    _levels = 1;
}

PmergeMe::PmergeMe(int argc, char **argv)
{
    _numberOfPairs = 0;
    _oddArgs = 0;
    _levels = 2;
    createDoublon(argc, argv);
    _simpleTest = createSimpleContainer(_containerDequePair);
    // std::cout << "hop hop hop " << std::endl;
    // iter(_simpleTest, printElement<int>);
    // std::cout << "Nombre final d'elements : " << _simpleTest.size() << std::endl;
    // std::cout << "hop hop hop " << std::endl;
    recursiveSort(_simpleTest);
    recursiveInsertWithContainer(_simpleTest, 1);

    if (_containerDequeRest.size() == 1)
    {
        std::deque<int>::iterator it = _containerDequeRest.begin();
        std::deque<int>::iterator posValid = std::lower_bound(_simpleTest.begin(), _simpleTest.end(), *it);
        _simpleTest.insert(posValid, *it);

    }
    // std::cout << "Finale list elements : " << std::endl;
    iter(_simpleTest, printElement<int>);
    std::cout << "Nombre final d'elements : " << _simpleTest.size() << std::endl;
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

std::deque<int> createSimpleContainer(std::deque<std::pair<int, int>> arr)
{
    std::deque<int> result;
    for (std::deque<std::pair<int, int>>::iterator it = arr.begin(); it != arr.end(); it++)
    {
        result.push_back(it->first);
        result.push_back(it->second);
    }
    return result;
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
                // std::cout << "rentre" << std::endl;
                int first = std::atoi(argv[i]);
                int second = std::atoi(argv[i + 1]);
                _containerDequePair.push_back(std::make_pair(first, second));
                // _numberOfPairs++;
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
                // _numberOfPairs++;
            }
        }
    }
    for (std::deque<std::pair<int, int>>::iterator it = _containerDequePair.begin(); it != _containerDequePair.end(); it++)
    {
        if (::min(it->first, it->second) == it->second)
            ::swap(it->first, it->second);
    }
}


void swap_pair(std::deque<int>::iterator it, int pair_level, std::deque<int> &container)
{
    std::deque<int>::iterator start = nextIt(it, -pair_level + 1);
    std::deque<int>::iterator end = nextIt(start, pair_level);
    if (start < it && end <= container.end())
    {
        while (start != end)
        {
            std::iter_swap(start, std::next(start, pair_level));
            start++;
        }
    }
}

/*
Ici la recurssive fais des groupe et swap les groupe en eux en se basant sur le plus grand du groupe
donc au debut fais des paires qui vont swap entre elles 
puis des paires de paires qui swap etc ... 
*/

void PmergeMe::recursiveSort(std::deque<int>& arr)
{
    if (arr.empty()) 
        return;

    // iter(_simpleTest, printElement<int>);

    int actualLevels = _levels;
    int pair_units_nbr = arr.size() / actualLevels; // Nombre de paires
    if (pair_units_nbr < 2)
        return;

    bool is_odd = pair_units_nbr % 2 == 1;

    std::deque<int>::iterator start = arr.begin();
    std::deque<int>::iterator last = nextIt(start, actualLevels * pair_units_nbr);
    std::deque<int>::iterator end = last;
    if (is_odd) 
    {
        --end; 
    }

    for (std::deque<int>::iterator it = start; it != end; std::advance(it, 2 * actualLevels))
    {
        std::deque<int>::iterator maxGroupActual = nextIt(it, actualLevels - 1);
        if (nextIt(it, actualLevels * 2 - 1) >= end) 
        {
            break;
        }
        std::deque<int>::iterator maxGroupeNextIt = nextIt(it, actualLevels * 2 - 1);

        if (maxGroupeNextIt < end) 
        {
            if (*maxGroupeNextIt < *maxGroupActual)
            {
                // std::cout << "Échange : " << *maxGroupActual << " et " << *maxGroupeNextIt << std::endl;
                // std::cout << "Nombre d'elements deplacer " << actualLevels << std::endl;
                ::swap_pair(maxGroupActual, actualLevels, arr);
            }
        }
    }

    _levels *= 2; // Incrémenter le niveau pour le prochain appel
    recursiveSort(arr); // Appel récursif
    recursiveInsertWithContainer(arr, actualLevels);
}



// void PmergeMe::recursiveInsertWithContainer(std::deque<int>& arr, int actualLevels)
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
//         } // la je pense mettre le reste


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
//         // std::cout << "hop hop hop " << std::endl;
//         // std::cout << "level : " << actualLevels << std::endl;
//         // iterContainerOfContainer(mainPart, printElement<int>);
//         // std::cout << "Nombre final d'elements : " << mainPart.size() << std::endl;
//         // std::cout << "hop hop hop " << std::endl;

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
//                 // std::cout << "rentre" << std::endl;
//                 int lastElement = it->back();
//                 std::deque<std::deque<int>>::iterator posValid = std::lower_bound(mainPart.begin(), mainPart.end(), lastElement,
//                 [](const std::deque<int>& a, const int& b) 
//                 {
//                     return a.back() < b;
//                 }); // revenir car j'ai rien compris pourquoi la ca fonctionne alors quavant javais un beug
//                 if (std::find(mainPart.begin(), mainPart.end(), *it) == mainPart.end())
//                     mainPart.insert(posValid, *it);
//             int nu;    
//             if (k == 2)
//                 int nu = 0;
//             else 
//                 int nu = k;
//             for (int j = nu ; j <  numJacob - 1; j++)
//             {
//                 if (it - j >= startPending) 
//                 {
//                     // if (std::find(mainPart.begin(), mainPart.end(), *(it - j)) == mainPart.end())
//                     // {
//                     //     std::deque<std::deque<int>>::iterator prevPos = std::lower_bound(mainPart.begin(), mainPart.end(), *(it - j),
//                     //     [](const std::deque<int>& a, const std::deque<int>& b) 
//                     //     {
//                     //         return a.back() < b.back();
//                     //     });
//                     // }
//                     // else // rajout si jacob pas plus grand mais deja insert donc insert tout ce qui a avant lui
//                     // {
//                         for (std::deque<std::deque<int>>::iterator it = startPending; it != endPending; it++)
//                         {
//                             int lastElement = it->back();
//                             std::deque<std::deque<int>>::iterator posValid = std::lower_bound(mainPart.begin(), mainPart.end(), lastElement,
//                             [](const std::deque<int>& a, const int& b) 
//                             {
//                                 return a.back() < b;
//                             });
//                             if (std::find(mainPart.begin(), mainPart.end(), *it) == mainPart.end())
//                                 mainPart.insert(posValid, *it);
//                         }
//                     // }
//                 }
//             }

//             numJacob = jacobsthalValue(k + 1);
//             }
//         }
//         else // ici je fais si le nombre de jacob trop grand alors je commence au debut de la liste 
//         {
//             for (std::deque<std::deque<int>>::iterator it = startPending; it != endPending; it++)
//             {
//                 int lastElement = it->back();
//                 std::deque<std::deque<int>>::iterator posValid = std::lower_bound(mainPart.begin(), mainPart.end(), lastElement,
//                 [](const std::deque<int>& a, const int& b) 
//                 {
//                     return a.back() < b;
//                 });
//                 std::cout << "rentre dans insert debut" << std::endl;
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
//             _simpleTest.push_back(*it);
//         }

//         std::cout << "hop hop hop " << std::endl;
//         iter(_simpleTest, printElement<int>);
//         std::cout << "Nombre final d'elements : " << _simpleTest.size() << std::endl;
//         std::cout << "hop hop hop " << std::endl;
//     }












// }










void PmergeMe::recursiveInsertWithContainer(std::deque<int>& arr, int actualLevels)
{
    std::deque<std::deque<int>> mainPart;
    std::deque<std::deque<int>> pendingPart;
    std::deque<int> rest;
    int pair_units_nbr = arr.size() / actualLevels;
    if (pair_units_nbr < 2)
        return;

    std::deque<int>::iterator start = arr.begin();
    std::deque<int>::iterator end = nextIt(start, actualLevels * pair_units_nbr); // a voir si le reste je mets direct dans pendingPart

        for (std::deque<int>::iterator it = end; it != arr.end(); it++)
        {
            
            rest.push_back(*it);
        }


    std::deque<std::deque<int>> allContainer;

    
    for (size_t i = 0; i < arr.size(); i += actualLevels) 
    {
        std::deque<int> group;

        for (size_t j = 0; j < actualLevels && (i + j) < arr.size(); ++j) 
        {
            group.push_back(arr[i + j]);
        }

        allContainer.push_back(group);
    }
        std::deque<std::deque<int>>::iterator maxGroupB = allContainer.begin(); // B1 max 
        std::deque<std::deque<int>>::iterator maxGroupA = allContainer.begin() + 1; // A1 max
        
        
        mainPart.push_back(*maxGroupB);  
        mainPart.push_back(*maxGroupA);

    if (pair_units_nbr > 2)
    {
        for (std::deque<std::deque<int>>::iterator it = maxGroupA + 1; it != allContainer.end(); it++)
        {
            pendingPart.push_back(*it);
        }
    }
   
    if (pendingPart.size() != 0)
    {
        std::deque<std::deque<int>>::iterator startPending = pendingPart.begin();
        std::deque<std::deque<int>>::iterator endPending = pendingPart.end();


        size_t numJacob = jacobsthalValue(2);
    
        if (startPending + numJacob < endPending)
        {
            for (size_t k = 2; startPending +  numJacob < endPending; ++k)
            {
                std::deque<std::deque<int>>::iterator it = startPending +  numJacob;
                int lastElement = it->back();
                std::deque<std::deque<int>>::iterator posValid = std::lower_bound(mainPart.begin(), mainPart.end(), lastElement,
                [](const std::deque<int>& a, const int& b) 
                {
                    return a.back() < b;
                });
                if (std::find(mainPart.begin(), mainPart.end(), *it) == mainPart.end())
                    mainPart.insert(posValid, *it);
            int nu;    
            if (k == 2)
                int nu = 0;
            else 
                int nu = k;
            for (int j = nu ; j <  numJacob - 1; j++)
            {
                if (it - j >= startPending) 
                {
                    for (std::deque<std::deque<int>>::iterator it = startPending; it != endPending; it++)
                    {
                        int lastElement = it->back();
                        std::deque<std::deque<int>>::iterator posValid = std::lower_bound(mainPart.begin(), mainPart.end(), lastElement,
                        [](const std::deque<int>& a, const int& b) 
                        {
                            return a.back() < b;
                        });
                        if (std::find(mainPart.begin(), mainPart.end(), *it) == mainPart.end())
                            mainPart.insert(posValid, *it);
                    }
                }

            }

            numJacob = jacobsthalValue(k + 1);
            }
        }
        else
        {
            for (std::deque<std::deque<int>>::iterator it = startPending; it != endPending; it++)
            {
                int lastElement = it->back();
                std::deque<std::deque<int>>::iterator posValid = std::lower_bound(mainPart.begin(), mainPart.end(), lastElement,
                [](const std::deque<int>& a, const int& b) 
                {
                    return a.back() < b;
                });
                mainPart.insert(posValid, *it);
            }
        }
    }

    for (std::deque<std::deque<int>>::iterator it = pendingPart.begin(); it != pendingPart.end(); it++)
    {
        if (std::find(mainPart.begin(), mainPart.end(), *it) == mainPart.end())
        {
            int lastElement = it->back();
                std::deque<std::deque<int>>::iterator posValid = std::lower_bound(mainPart.begin(), mainPart.end(), lastElement,
                [](const std::deque<int>& a, const int& b) 
                {
                    return a.back() < b;
                });
                mainPart.insert(posValid, *it);
        }
    }
        _simpleTest.clear();

        for (std::deque<std::deque<int>>::iterator it = mainPart.begin(); it != mainPart.end(); it++)
        {
            for (std::deque<int>::iterator iter = it->begin(); iter != it->end(); ++iter)
            {
               _simpleTest.push_back(*iter); 
            }
        }
        for (std::deque<int>::iterator it = rest.begin(); it != rest.end(); it++)
        {

               _simpleTest.push_back(*it); 
            
        }
    }

// valeur pour jacobsthal ok lui donner 2 de base pour avoir 3 
// et apres quand tout les groupe de 3 a 0 sont insert alors mettre a 3 pour 5 et ainsi de suite
// ca va revenir d'insert 5 - 4 comme groupe
int jacobsthalValue(int n) {
    return static_cast<int>(std::round((std::pow(2, n + 1) + (n % 2 == 0 ? 1 : -1)) / 3));
}