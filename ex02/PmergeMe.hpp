#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <string>
#include <iostream>
#include <stack>
#include <algorithm>
#include <utility>
#include <iterator>
#include <vector>

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
	next(T it, int steps)
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

template< typename T >
	void printElement( T& x )
	{
	  std::cout << x << std::endl;
	  return;
	}

class PmergeMe
{
public:
	PmergeMe();
	PmergeMe(int argc, char **argv);
	PmergeMe(const PmergeMe &other);
	PmergeMe &operator=(const PmergeMe &other);
	~PmergeMe();
	void controlValue(char *value);
	void createDoublon(int argc, char **argv);
	void createlargestContainer();
	// void recursiveSort(std::deque<std::pair<int, int>>& arr);
	void recursiveSort(std::deque<int>& arr);
	void reorderContainerPair();
	void preorderContainerShort();
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
	int _numberOfPairs;
	int _oddArgs;
	int _levels; // pour augmenter commencer avec des pair et pair puis multiplier par 2
	std::deque<std::pair<int, int>> _containerDequePair;
	std::deque<int> _containerDequeLong;
	std::deque<int> _containerDequeRest;
	std::deque<int> _containerDequeShort;
	std::deque<int> _containerDequeShortPreorder;
	std::deque<int> _simpleTest;
};
std::deque<int> createSimpleContainer(std::deque<std::pair<int, int>> arr);
bool isNumber(std::string &str);
void swap_pair(std::deque<int>::iterator it, int pair_level, std::deque<int> &container);
#endif
