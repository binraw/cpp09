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
                std::cout << "rentre" << std::endl;
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
                std::cout << "rentre pair" << std::endl;
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

// void PmergeMe::recursiveSort(std::deque<std::pair<int, int>>& arr)
// {
//     if (arr.empty()) 
//         return;
//     int actualLevels = _levels;
//     int groupCount = arr.size() / actualLevels; // ici pour verifier qu'il y a toujours des comparaisons possible vu qu'on regroupe de plus en plus
//     if (groupCount < 2)
//         return;
//     // bool groupOdd = false;
//     // if ((groupCount % 2) != 0)
//     //     groupOdd = true;
//     std::deque<std::pair<int, int>>::iterator start = arr.begin();
//     std::deque<std::pair<int, int>>::iterator end = arr.end(); // obliger de initialiser avant advance
//     std::deque<std::pair<int, int>>::iterator lastGroup = start;
//     // std::advance(end, _levels * groupCount);
//     if (groupCount > 0) 
//     {
//         std::advance(lastGroup, -(groupCount)); 
//         // if (lastGroup < start) {
//         //     lastGroup = start; 
//         // }
//     }
//     for (std::deque<std::pair<int, int>>::iterator it = arr.begin(); it != lastGroup; std::advance(it, actualLevels))
//     { // ici je dois determiner la comparaison 
//         /* jai mis actualLevels a 1 de base car je procede deja avec des paires
//         */
//         std::deque<std::pair<int, int>>::iterator maxGroupActual = it;
//         std::deque<std::pair<int, int>>::iterator maxGroupeNext = it + actualLevels;
//         if (maxGroupeNext < end)
//         {
//             std::cout << "echange de groupe" << std::endl;
//             if (::min(maxGroupActual->second, maxGroupeNext->second) == maxGroupeNext->second)
//             {
//                 std::cout << "changement avec : " << maxGroupActual->second <<  " et : " << maxGroupeNext->second << std::endl; 
//                 ::swap(*maxGroupActual, *maxGroupeNext); // la je crois que je vais bien swap mais a verifier
//             }
//         }

//     }
//     _levels += 1; // pour donner au prochain une pair de plus dans son groupe
//     recursiveSort(arr);
//      /* La je doit creer le main et le rest container 
//         et je dois separer les paires en gros je dois bien passer en monde deque simple
//         car apres je vais inserer par rapport a l'index de chaque nombre 

//         enfaite dans les premiere insertion on doit seulement regarder le plus grand
//         donc possible de continuer avec un deque pair je pense 
//         et quand on arrive sur la derniere insertion de nombre a nombre 
//         alors la creer des container 'simple'
//      */
//    // std::vector<std::deque<std::pair<int, int>>::iterator> mainContainer; // je mets des iterator pour que ce soit plus flexible dans un vector pour insert
//     //std::vector<std::deque<std::pair<int, int>>::iterator> restContainer;

//     //std::deque<std::pair<int, int>>::iterator beginInsert = arr.begin();
//     //std::advance(beginInsert, actualLevels); // je fais avancer a la premiere pair a mettre
//     // mais j'ai l'impression de devoir mettre tout se qu'il y a devant aussi vu qu'on sait deja que les grands sont trier
//     // je mets direcctement les deux pairs au debut
//     // mainContainer.insert(mainContainer.end(), beginInsert);

// }


// void PmergeMe::recursiveSort(std::deque<int>& arr)
// {
//     std::cout << "rentre bien dans la recursive" << std::endl;
//     if (arr.empty()) 
//         return;
//     int actualLevels = _levels;
//     int groupCount = arr.size() / actualLevels; // ici pour verifier qu'il y a toujours des comparaisons possible vu qu'on regroupe de plus en plus
//     if (groupCount < 2)
//         return;
//     bool groupOdd = false;
//     if ((groupCount % 2) != 0)
//         groupOdd = true;
//     std::deque<int>::iterator start = arr.begin();
//     std::deque<int>::iterator end = arr.end(); // obliger de initialiser avant advance
//     std::deque<int>::iterator lastGroup = start;
//     std::advance(end, actualLevels * groupCount);

//     std::advance(lastGroup, -((arr.size() / actualLevels) % 2));
//         // std::advance(lastGroup, -(groupOdd * groupCount)); 
//         // if (lastGroup < start) {
//         //     lastGroup = start; 
//         // }

//     int jump = 2 * actualLevels;
//     for (std::deque<int>::iterator it = arr.begin(); it != lastGroup; std::advance(it, jump))
//     { // ici je dois determiner la comparaison 
//         /* jai mis actualLevels a 1 de base car je procede deja avec des paires
//         */
//        std::deque<int>::iterator maxGroupActual = it + (actualLevels - 1);
//        std::deque<int>::iterator maxGroupeNext = it + (actualLevels * 2 - 1);

//         if (maxGroupeNext < end)
//         {
//             if (*maxGroupeNext < *maxGroupActual)
//             {
//                 std::cout << "echange : " << *maxGroupActual << " avec " << *maxGroupeNext << std::endl;
//                  ::swap(*maxGroupActual, *maxGroupeNext);
//             }
//         }


//     }
//     _levels *= 2; // pour donner au prochain une pair de plus dans son groupe
//     recursiveSort(arr);
//      /* La je doit creer le main et le rest container 
//         et je dois separer les paires en gros je dois bien passer en monde deque simple
//         car apres je vais inserer par rapport a l'index de chaque nombre 

//         enfaite dans les premiere insertion on doit seulement regarder le plus grand
//         donc possible de continuer avec un deque pair je pense 
//         et quand on arrive sur la derniere insertion de nombre a nombre 
//         alors la creer des container 'simple'
//      */
//    // std::vector<std::deque<std::pair<int, int>>::iterator> mainContainer; // je mets des iterator pour que ce soit plus flexible dans un vector pour insert
//     //std::vector<std::deque<std::pair<int, int>>::iterator> restContainer;

//     //std::deque<std::pair<int, int>>::iterator beginInsert = arr.begin();
//     //std::advance(beginInsert, actualLevels); // je fais avancer a la premiere pair a mettre
//     // mais j'ai l'impression de devoir mettre tout se qu'il y a devant aussi vu qu'on sait deja que les grands sont trier
//     // je mets direcctement les deux pairs au debut
//     // mainContainer.insert(mainContainer.end(), beginInsert);

// }


/* */
void swap_pair(std::deque<int>::iterator it, int pair_level, std::deque<int> &container)
{
    std::deque<int>::iterator start = next(it, -pair_level + 1);
    std::deque<int>::iterator end = next(start, pair_level);
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
    std::cout << "Rentre bien dans la fonction recursive" << std::endl;
    if (arr.empty()) 
        return;
    std::cout << "Entre dans recursive avec : " <<  std::endl;
    iter(_simpleTest, printElement<int>);

    int actualLevels = _levels;
    int pair_units_nbr = arr.size() / actualLevels; // Nombre de paires
    if (pair_units_nbr < 2)
        return;

    bool is_odd = pair_units_nbr % 2 == 1; // Vérification des paires impaires

    std::deque<int>::iterator start = arr.begin();
    std::deque<int>::iterator last = next(start, actualLevels * pair_units_nbr);
    std::deque<int>::iterator end = last;  // Initialisez end avec last
    if (is_odd) 
    {
        --end; 
    }

    for (std::deque<int>::iterator it = start; it != end; std::advance(it, 2 * actualLevels))
    {
        std::deque<int>::iterator maxGroupActual = next(it, actualLevels - 1);
        if (next(it, actualLevels * 2 - 1) >= end) 
        {
            break; // protection pour si on depasse du container
        }
        std::deque<int>::iterator maxGroupeNext = next(it, actualLevels * 2 - 1);

        if (maxGroupeNext < end) 
        {
            if (*maxGroupeNext < *maxGroupActual)
            {
                std::cout << "Échange : " << *maxGroupActual << " et " << *maxGroupeNext << std::endl;
                std::cout << "Nombre d'elements deplacer " << actualLevels << std::endl;
                ::swap_pair(maxGroupActual, actualLevels, arr);
            }
        }
    }

    _levels *= 2; // Incrémenter le niveau pour le prochain appel
    recursiveSort(arr); // Appel récursif
}

/*

Je dois (je pense) mettre b1 et a1 de base. puis sil il y en d'autre alors j'insere par rapport au plus grand 
par rapport au plus grand en utilisant la suite de jacob
en utilisant la recherche binaire. 
Ah non enfaite je dois rentrer les max seulement puis apres les mini avec la technique du binaire 

je pense vu que j'ai stocker le niveau de recursivite je peux refaire une autre recursive en divisant
a voir si c'est possible ou si la logique ne le permet pas. 
*/