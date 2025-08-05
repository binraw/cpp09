#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <string>
#include <iostream>
#include <stack>
#include <algorithm>
#include <utility>
#include <iterator>
#include <vector>
#include <cmath>
#include <ctime>
#include <exception>


template <typename Container>
struct CompareByBack
{
    bool operator()(const Container& a, const int& b) const
    {
        return a.back() < b;
    }
};

template <typename ContainerOfContainer>
    void controlValueTemp(char *value, ContainerOfContainer &arr);

template <typename Container, typename ContainerOfContainer>
    void recursiveInsertWithContainerTemp(Container &arr, int actualLevels, ContainerOfContainer &container);

bool isNumber(std::string &str);

static int jacobsthalValue(int n);

template <typename T>
	T min(T &a, T &b)
	{
		if(b <= a)
			return b;
		else
			return a;
	}

template <typename T>
	void swap(T &a, T &b)
	{
		T temp = a;
		a = b;
		b = temp;
	}


template <typename T> T 
	nextIt(T it, int steps)
	{
		std::advance(it, steps);
		return it;
	}
	


template <typename T,  typename Func>
	void iter(T &container, Func func)
	{
		for(typename T::iterator it = container.begin(); it != container.end(); it++)
			func(*it);
	}

template <typename T, typename Func>
	void iterContainerOfContainer(T &container, Func func)
	{
		for (typename T::iterator iter = container.begin(); iter != container.end(); ++iter)
		{
			for (typename T::value_type::iterator it = iter->begin(); it != iter->end(); ++it)
			{
				func(*it);
			}
		}
	}

template< typename T >
	void printElement( T& x )
	{
	  std::cout << x << std::endl;
	  return;
	}

template< typename T >
	void printElementFinal( T& x )
	{
	  std::cout << x << " ";
	  return;
	}


template <typename Container, typename ResultContainer>
    ResultContainer createSimpleContainerTemp(const Container &arr, ResultContainer result)
    {
        result.clear();
        for (typename Container::const_iterator it = arr.begin(); it != arr.end(); it++)
        {
            result.push_back(it->first);
            result.push_back(it->second);
        }
        return result;
    }




template <typename ContainerOfContainer, typename Container>
    void createDoublonTemp(int argc, char **argv, ContainerOfContainer &arr, Container &arrRest)
    {
        if ((argc % 2) == 0)
        {
            int i = 1;
            controlValueTemp(argv[i], arr);
            arrRest.push_back(std::atoi(argv[i]));
            for (i = 2; i < argc; i += 2) 
            {
                if (i + 1 < argc)
                {
                    controlValueTemp(argv[i], arr);
                    controlValueTemp(argv[i + 1], arr);
                    int first = std::atoi(argv[i]);
                    int second = std::atoi(argv[i + 1]);
                    arr.push_back(std::make_pair(first, second));
                }
            }
        }
        else 
        {
            for (int i = 1; i < argc; i += 2) 
            {
                if (i + 1 < argc)
                {
                    controlValueTemp(argv[i], arr);
                    controlValueTemp(argv[i + 1], arr);
                    int first = std::atoi(argv[i]);
                    int second = std::atoi(argv[i + 1]);
                    arr.push_back(std::make_pair(first, second));
                }
            }
        }
        for (typename ContainerOfContainer::iterator it = arr.begin(); it != arr.end(); it++)
        {
            if (::min(it->first, it->second) == it->second)
                ::swap(it->first, it->second);
        }
    }

template <typename Container>
    void swap_pairTemp(typename Container::iterator it, int pair_level, Container &container)
    {
        typename Container::iterator start = nextIt(it, -pair_level + 1);
        typename Container::iterator end = nextIt(start, pair_level);
        if (start < it && end <= container.end())
        {
            while (start != end)
            {
                std::iter_swap(start, std::next(start, pair_level));
                start++;
            }
        }
    }



template <typename Container, typename ContainerOfContainer>
    void recursiveSortTemp(Container &arr, int levels, ContainerOfContainer &container)
    {
        if (arr.empty()) 
            return;

        int actualLevels = levels;
        int pair_units_nbr = arr.size() / actualLevels; // Nombre de paires / groupes
        if (pair_units_nbr < 2)
            return;

        bool is_odd = pair_units_nbr % 2 == 1;
        typename Container::iterator start = arr.begin();
        typename Container::iterator last = nextIt(start, actualLevels * pair_units_nbr);
        typename Container::iterator end = last;
        if (is_odd) 
        {
            --end; 
        }
        for (typename Container::iterator it = start; it != end; std::advance(it, 2 * actualLevels))
        {
            typename Container::iterator maxGroupActual = nextIt(it, actualLevels - 1);
            if (nextIt(it, actualLevels * 2 - 1) >= end) 
            {
                break;
            }
            typename Container::iterator maxGroupeNextIt = nextIt(it, actualLevels * 2 - 1);

            if (maxGroupeNextIt < end) 
            {
                if (*maxGroupeNextIt < *maxGroupActual)
                    ::swap_pairTemp(maxGroupActual, actualLevels, arr);
            }
        }
        levels *= 2;
        recursiveSortTemp(arr, levels, container);
        recursiveInsertWithContainerTemp(arr, actualLevels, container);
    }





template <typename Container, typename ContainerOfContainer>
    void recursiveInsertWithContainerTemp(Container &arr, int actualLevels, ContainerOfContainer &container)
    {
        ContainerOfContainer mainPart;
        ContainerOfContainer pendingPart;
        Container rest;

        int pair_units_nbr = arr.size() / actualLevels;
        if (pair_units_nbr < 2)
            return;
        typename Container::iterator start = arr.begin();
        typename Container::iterator end = nextIt(start, actualLevels * pair_units_nbr);

        for (typename Container::iterator it = end; it != arr.end(); it++)
            rest.push_back(*it);

        ContainerOfContainer allContainer;
        
        for (size_t i = 0; i < arr.size(); i += actualLevels) 
        {
            Container group;
    
            for (size_t j = 0; j < actualLevels && (i + j) < arr.size(); ++j) 
            {
                group.push_back(arr[i + j]);
            }
    
            allContainer.push_back(group);
        }

        typename ContainerOfContainer::iterator maxGroupB = allContainer.begin(); // B1 max 
        typename ContainerOfContainer::iterator maxGroupA = allContainer.begin() + 1; // A1 max

        mainPart.push_back(*maxGroupB);  
        mainPart.push_back(*maxGroupA);

        if (pair_units_nbr > 2)
        {
            for (typename ContainerOfContainer::iterator it = maxGroupA + 1; it != allContainer.end(); it++)
            {
                pendingPart.push_back(*it);
            }
        }

        if (pendingPart.size() != 0)
        {
            typename ContainerOfContainer::iterator startPending = pendingPart.begin();
            typename ContainerOfContainer::iterator endPending = pendingPart.end();


            size_t numJacob = jacobsthalValue(2);
            
            if (startPending + numJacob < endPending)
            {
                for (size_t k = 2; startPending +  numJacob < endPending; ++k)
                {
                    typename ContainerOfContainer::iterator it = startPending +  numJacob;
                    int lastElement = it->back();
                    typename ContainerOfContainer::iterator posValid = std::lower_bound(mainPart.begin(), mainPart.end(), lastElement,
                    CompareByBack<Container>());
                    if (posValid == mainPart.end())
                        mainPart.insert(posValid, *it);

                int nu = (k == 2) ? 0 : k;
                typename ContainerOfContainer::iterator newLimit = posValid;
                for (int j = nu ; j <  numJacob - 1; j++)
                {
                    if (it - j >= startPending) 
                    {
                        for (typename ContainerOfContainer::iterator iter = startPending; iter != endPending; iter++)
                        {
                            int lastElement = iter->back();
                            typename ContainerOfContainer::iterator pos = std::lower_bound(mainPart.begin(), mainPart.end(), lastElement,
                            CompareByBack<Container>());
                            if(pos == mainPart.end() || *pos != *iter)
                                mainPart.insert(pos, *iter);
                        }
                    }

                }
                numJacob = jacobsthalValue(k + 1);
                }
            }
            else
            {
                for (typename ContainerOfContainer::iterator it = startPending; it != endPending; it++)
                {
                    int lastElement = it->back();
                    typename ContainerOfContainer::iterator posValid = std::lower_bound(mainPart.begin(), mainPart.end(), lastElement,
                    CompareByBack<Container>());
                    mainPart.insert(posValid, *it);
                }

            }
        }


        arr.clear();

        for (typename ContainerOfContainer::iterator it = mainPart.begin(); it != mainPart.end(); it++)
        {
            for (typename Container::iterator iter = it->begin(); iter != it->end(); ++iter)
               arr.push_back(*iter);
        }

        for (typename Container::iterator it = rest.begin(); it != rest.end(); it++)
            arr.push_back(*it); 
    }





template <typename Container, typename ContainerOfPair>
    void duoSortTemplate(Container &arr, ContainerOfPair &arrPair)
    {
        Container mainPart;
        Container pendingPart;

        arrPair.clear();
        for (typename Container::iterator it = arr.begin(); it != arr.end(); it += 2)
        {
            if (it + 1 < arr.end())
            {
                
                int first = *it;
                int second = *(it + 1);
                arrPair.push_back(std::make_pair(first, second));
            }
        }

        mainPart.push_back(arrPair.begin()->first);  
        mainPart.push_back(arrPair.begin()->second);

        for (typename ContainerOfPair::iterator it = arrPair.begin() + 1; it != arrPair.end(); it++)
            pendingPart.push_back(it->first);


        for (typename ContainerOfPair::iterator it = arrPair.begin() + 1; it != arrPair.end(); it++)
            mainPart.push_back(it->second);


        if (pendingPart.size() != 0)
        {
            typename Container::iterator startPending = pendingPart.begin();
            typename Container::iterator endPending = pendingPart.end();
    
    
            size_t numJacob = jacobsthalValue(2);
        
            if (startPending + numJacob < endPending)
            {
                for (size_t k = 2; startPending +  numJacob < endPending; ++k)
                {
                    typename Container::iterator it = startPending +  numJacob;
    
                    int lastElement = *it;
                    typename Container::iterator posValid = std::lower_bound(mainPart.begin(), mainPart.end(), lastElement);
                    if (std::find(mainPart.begin(), mainPart.end(), *it) == mainPart.end())
                        mainPart.insert(posValid, *it);
    
                int nu = (k == 2) ? 0 : k;
                
                for (int j = nu ; j <  numJacob - 1; j++)
                {
                    if (it - j >= startPending) 
                    {
                        for (typename Container::iterator iter = startPending; iter != endPending; iter++)
                        {
                            int lastElement = *iter;
    
                            typename Container::iterator pos = std::lower_bound(mainPart.begin(), mainPart.end(), lastElement);
                            if(pos == mainPart.end() || *pos != *iter)
                                mainPart.insert(pos, *iter);
                        }
                    }
    
                }
                numJacob = jacobsthalValue(k + 1);
                }
            }
            else
            {
                for (typename Container::iterator it = startPending; it != endPending; it++)
                {
                    int lastElement = *it;
                    typename Container::iterator posValid = std::lower_bound(mainPart.begin(), mainPart.end(), lastElement);
                    mainPart.insert(posValid, *it);
                }
    
            }
        }

        arr.clear();
        arr = mainPart;
    }


    class PmergeMe
    {
        
        public:
        PmergeMe();
        PmergeMe(int argc, char **argv);
        PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);
        ~PmergeMe();
        class ErrorArgs: public std::exception
        {
            virtual const char* what() const throw();
        };
        class ErrorRange: public std::exception
        {
            virtual const char* what() const throw();
        };
        class ErrorDouble: public std::exception
        {
            virtual const char* what() const throw();
        };
        class ErrorNull: public std::exception
        {
            virtual const char* what() const throw();
        };


    
    private:
    std::deque<std::pair<int, int> > _containerDequePair;
    std::deque<std::deque<int> > _containerDequeOfDeque;
    std::deque<int> _containerDequeRest;
    std::deque<int> _simpleTestDeque;

    std::vector<std::pair<int, int> > _containerVectorPair;
    std::vector<std::vector<int> > _containerVectorOfVector;
    std::vector<int> _containerVectorRest;
    std::vector<int> _simpleTestVector;

    int _levels;
};
	
    template <typename ContainerOfContainer>
    void controlValueTemp(char *value, ContainerOfContainer &arr)
    {
        int result;
        try {
            result = std::atoi(value);
        }
        catch (std::invalid_argument const& ex){
            throw  PmergeMe::ErrorArgs();
        }
        catch (std::out_of_range const& ex){
            throw   PmergeMe::ErrorNull();
        }
        if (result)
        {
            for (typename ContainerOfContainer::iterator it = arr.begin(); it != arr.end(); it++)
            {
                if (it->first == result || it->second == result)
                    throw  PmergeMe::ErrorDouble();
            }
        }
        else
            throw PmergeMe::ErrorNull();
    }


#endif
