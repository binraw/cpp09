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
    _levels = 2;
    createDoublon(argc, argv);
    _simpleTest = createSimpleContainer(_containerDequePair);
    recursiveSort(_simpleTest);
    recursiveInsertWithContainer(_simpleTest, 1);

    if (_containerDequeRest.size() == 1)
    {
        std::deque<int>::iterator it = _containerDequeRest.begin();
        std::deque<int>::iterator posValid = std::lower_bound(_simpleTest.begin(), _simpleTest.end(), *it);
        _simpleTest.insert(posValid, *it);

    }
    std::cout << "Finale list elements : " << std::endl;
    iter(_simpleTest, printElement<int>);
    // createlargestContainer();
    // iter(_containerDequeLong, printElement<int>);
    // reorderContainerPair();
    // preorderContainerShort();
    // std::cout << "VALUE SHORT CONTAINER :"  << std::endl;
    // iter(_containerDequeShortPreorder, printElement<int>);
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
                // std::cout << "rentre pair" << std::endl;
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

void PmergeMe::recursiveSort(std::deque<int>& arr)
{
    // std::cout << "Rentre bien dans la fonction recursive" << std::endl;
    if (arr.empty()) 
        return;
    // std::cout << "Entre dans recursive avec : " <<  std::endl;
    iter(_simpleTest, printElement<int>);

    int actualLevels = _levels;
    int pair_units_nbr = arr.size() / actualLevels; // Nombre de paires
    if (pair_units_nbr < 2)
        return;

    bool is_odd = pair_units_nbr % 2 == 1; // Vérification des paires impaires

    std::deque<int>::iterator start = arr.begin();
    std::deque<int>::iterator last = nextIt(start, actualLevels * pair_units_nbr);
    std::deque<int>::iterator end = last;  // Initialisez end avec last
    if (is_odd) 
    {
        --end; 
    }

    for (std::deque<int>::iterator it = start; it != end; std::advance(it, 2 * actualLevels))
    {
        std::deque<int>::iterator maxGroupActual = nextIt(it, actualLevels - 1);
        if (nextIt(it, actualLevels * 2 - 1) >= end) 
        {
            break; // protection pour si on depasse du container
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

/*

Je dois (je pense) mettre b1 et a1 de base. puis sil il y en d'autre alors j'insere par rapport au plus grand 
par rapport au plus grand en utilisant la suite de jacob
en utilisant la recherche binaire. 
Ah non enfaite je dois rentrer les max seulement puis apres les mini avec la technique du binaire 

je pense vu que j'ai stocker le niveau de recursivite je peux refaire une autre recursive en divisant
a voir si c'est possible ou si la logique ne le permet pas. 
*/


// void PmergeMe::recursiveInsert(std::deque<int>& arr, int actualLevels)
// {
//     std::cout << "RENTRE DANS INSERT avec actualLevels : " << actualLevels << std::endl;
//     std::deque<int> mainPart;
//     std::deque<int> pendingPart;
//     int pair_units_nbr = arr.size() / actualLevels;
//     if (pair_units_nbr < 2)
//         return;

//     std::deque<int>::iterator start = arr.begin();
//     std::deque<int>::iterator end = nextIt(start, actualLevels * pair_units_nbr); // a voir si le reste je mets direct dans pendingPart


//     // ici je vais juste mettre les premier donc B1 (min) et A1 (max) 

//         std::deque<int>::iterator maxGroupB = nextIt(start, actualLevels - 1); // B1 max 
//         std::deque<int>::iterator maxGroupA = nextIt(start, actualLevels * 2 - 1); // A1 max
        
//         for (std::deque<int>::iterator it = start; it != maxGroupB; ++it)
//             mainPart.push_back(*it); // a voir je pense qu'il manque les max
//         for (std::deque<int>::iterator iter = maxGroupB; iter != maxGroupA; ++iter)
//             mainPart.push_back(*iter); // a voir je pense qu'il manque les max
//         mainPart.push_back(*maxGroupA);
// // la il me manque la derniere partie de maxA 
//     std::cout << "Main Part du lvl : " << actualLevels << std::endl;
//     iter(mainPart, printElement<int>);
//     std::cout << "fin main Part." << std::endl;

//     if (pair_units_nbr > 2) // ici du coup le reste des valeurs a trier 
//     {
//         for (std::deque<int>::iterator it = maxGroupA + 1; it != end; it++)
//         {
//             pendingPart.push_back(*it);
//         }
//         std::cout << "Valeur de pendingPart level : " << actualLevels << std::endl;
//         iter(pendingPart, printElement<int>);
//         std::cout << "FIN PENDINGPART " << std::endl;
//     }
//     // la je pense je fais insert binaire jusqua deux apres ca me donne une liste avec les plus grands trier 
//     // et apres je recupere les min et la je les insert en faisant tres peu de comparaison
//     // la je vais faire une boucle avec le container pending
//     // em mode iter dessus avec la taille des pair et ensuite les ajouter au container main
   
   
//    // creation d'une liste avec seulement les max pour faire la recherche binaire dessus
//    // et ensuite rajouter pending dans la vrai liste avec toutes ses values
//     std::deque<int> maxValueMain;
//     for (std::deque<int>::iterator it = start; it != maxGroupB; it++)
//     {  
//         maxValueMain.push_back(*it); // add tout le contenant du group
//     }
//     maxValueMain.push_back(*maxGroupB);
//     for (std::deque<int>::iterator it = maxGroupB + 1; it != maxGroupA; it++)
//     {  
//         maxValueMain.push_back(*it); // add tout le contenant du group
//     }
//     maxValueMain.push_back(*maxGroupA);

//     std::cout << "VALUE SEULEMENT DES MAX MAIN: " << std::endl;
//     iter(maxValueMain, printElement<int>);
//     std::cout << "FIN DES MAX DE MAIN" << std::endl;
        
      
//     if (pendingPart.size() != 0)
//     {
//         std::deque<int>::iterator startPending = pendingPart.begin();
//         std::deque<int>::iterator endPending = pendingPart.end();

//         // std::cout << "VALUE pending: " << std::endl;
//         // iter(maxValueMain, printElement<int>);
//         // std::cout << "FIN DE pending" << std::endl;
//         size_t numJacob = jacobsthalValue(2);
    
//         if (startPending + (actualLevels * numJacob) - 1 < endPending)
//         {

//             for (size_t k = 2; startPending + (actualLevels * numJacob) - 1 < endPending; ++k)
//             {
              
//                 std::deque<int>::iterator it = startPending + (actualLevels * numJacob) - 1;
        
                
//                 std::deque<int>::iterator posValid = std::lower_bound(maxValueMain.begin(), maxValueMain.end(), *it);
//                 maxValueMain.insert(posValid, *it);
//                 // std::cout << "Valeur de la valeur insert : " << *it << std::endl;
               
//                 for (int j = 1; j < (actualLevels * numJacob); ++j) 
//                 {
//                     if (it - j >= startPending) 
//                     {
//                         std::deque<int>::iterator prevPos = std::lower_bound(maxValueMain.begin(), maxValueMain.end(), *(it - j));
//                         maxValueMain.insert(prevPos, *(it - j));
//                         // std::cout << "VALUE apres INSERT: " << std::endl;
//                         // iter(maxValueMain, printElement<int>);
//                         // std::cout << "FIN DE INSERT" << std::endl;
//                     }
//                 }
//                 // if (k == 2)
//                 //     numJacob = jacobsthalValue(3);
//                 // else
//                     numJacob = jacobsthalValue(k + 1);
//             }
//         }
//         else // ici je fais si le nombre de jacob trop grand alors je commence au debut de la liste 
//         {
//             for (std::deque<int>::iterator it = startPending + (actualLevels) - 1; it < endPending; it += actualLevels)
//             {
//                 std::deque<int>::iterator posValid = std::lower_bound(maxValueMain.begin(), maxValueMain.end(), *it);
//                 maxValueMain.insert(posValid, *it); // insert le max
//                 for (int i = actualLevels - 1; i > 0; i--) // ici j'insert tout les nombres de la part
//                 {
//                     it--;
//                     maxValueMain.insert(posValid, *it);
//                 }
//                 std::cout << "Valeur de la valeur insert avec jacob trop grand : " << *it << std::endl;
//                 std::cout << "VALUE apres INSERT avec jacob trop grand: " << std::endl;
//                 iter(maxValueMain, printElement<int>);
//                 std::cout << "FIN DE INSERT avec jacob trop grand" << std::endl;
//             }
//         }
//     }
        
//     }

    


void PmergeMe::recursiveInsertWithContainer(std::deque<int>& arr, int actualLevels)
{
    std::cout << "RENTRE DANS INSERT avec actualLevels : " << actualLevels << std::endl;


    std::deque<std::deque<int>> mainPart;
    std::deque<std::deque<int>> pendingPart;
    std::deque<int> rest;
    int pair_units_nbr = arr.size() / actualLevels;
    if (pair_units_nbr < 2)
        return;

    std::deque<int>::iterator start = arr.begin();
    std::deque<int>::iterator end = nextIt(start, actualLevels * pair_units_nbr); // a voir si le reste je mets direct dans pendingPart

    // if (end != arr.end())
    // {
        for (std::deque<int>::iterator it = end; it != arr.end(); it++)
        {
            std::cout << "Valeur du nombre mis de coter : " << *it << std::endl;
            rest.push_back(*it);
        } // la je pense mettre le reste
    // }

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
                std::cout << "valeur de jacob : " << numJacob << std::endl;
                std::deque<std::deque<int>>::iterator it = startPending +  numJacob;
        
                int lastElement = it->back();
                std::cout << "valeur de lastelement : " << lastElement << std::endl;
                std::deque<std::deque<int>>::iterator posValid = std::lower_bound(mainPart.begin(), mainPart.end(), lastElement,
                [](const std::deque<int>& a, const int& b) 
                {
                    return a.back() < b;
                }); // revenir car j'ai rien compris pourquoi la ca fonctionne alors quavant javais un beug
                if (std::find(mainPart.begin(), mainPart.end(), *it) == mainPart.end())
                    mainPart.insert(posValid, *it);
            int nu;    
            if (k == 2)
                int nu = 0;
            else 
                int nu = k;
            for (int j = nu ; j <  numJacob - 1; ++j)
            {
                if (it - j >= startPending) 
                {
                    if (std::find(mainPart.begin(), mainPart.end(), *(it - j)) == mainPart.end())
                    {
                        std::deque<std::deque<int>>::iterator prevPos = std::lower_bound(mainPart.begin(), mainPart.end(), *(it - j),
                        [](const std::deque<int>& a, const std::deque<int>& b) 
                        {
                            return a.back() < b.back();
                        });
                    }
                    else // rajout si jacob pas plus grand mais deja insert donc insert tout ce qui a avant lui
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
            }

            numJacob = jacobsthalValue(k + 1);
            }
        }
        else // ici je fais si le nombre de jacob trop grand alors je commence au debut de la liste 
        {
            std::cout << "rentre" << std::endl;
            for (std::deque<std::deque<int>>::iterator it = startPending /*ici -1 av*/; it != endPending; it++)
            {
                int lastElement = it->back();
                std::deque<std::deque<int>>::iterator posValid = std::lower_bound(mainPart.begin(), mainPart.end(), lastElement,
                [](const std::deque<int>& a, const int& b) 
                {
                    return a.back() < b;
                });
                mainPart.insert(posValid, *it); // insert le max

                // std::cout << "Valeur de la valeur insert avec jacob trop grand : " << *it << std::endl;
                // std::cout << "VALUE apres INSERT avec jacob trop grand: " << std::endl;
                // iterContainerOfContainer(mainPart, printElement<int>);
                // std::cout << "FIN DE INSERT avec jacob trop grand" << std::endl;
            }
        }
    }
                std::cout << "main part avant ajout a simple: " << std::endl;
                iterContainerOfContainer(mainPart, printElement<int>);
                std::cout << "FIN DE main" << std::endl;
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
            std::cout << "rentre dans rest" << std::endl;
            _simpleTest.push_back(*it);
        }
        std::cout << "FIN DE ARR : " << std::endl;
        iter(_simpleTest, printElement<int>);
        std::cout << "FIN FIN" << std::endl;

    }




// }

// valeur pour jacobsthal ok lui donner 2 de base pour avoir 3 
// et apres quand tout les groupe de 3 a 0 sont insert alors mettre a 3 pour 5 et ainsi de suite
// ca va revenir d'insert 5 - 4 comme groupe
int jacobsthalValue(int n) {
    return static_cast<int>(std::round((std::pow(2, n + 1) + (n % 2 == 0 ? 1 : -1)) / 3));
}