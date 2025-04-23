#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <string>
#include <iostream>
#include <stack>
#include <algorithm>

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

class PmergeMe
{
public:
	PmergeMe();
	PmergeMe(char **argv);
	PmergeMe(const PmergeMe &other);
	PmergeMe &operator=(const PmergeMe &other);
	~PmergeMe();
	void controlValue(char *value);
	void createDoublon(int argc, char **argv);
	void createlargestContainer();
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
	std::deque<std::pair<int, int>> _containerDequePair;
	std::deque<int> _containerDequeLong;
	std::deque<int> _containerDequeShort;
	std::deque<int> _containerDequeShortPreorder;
};

bool isNumber(std::string &str);

#endif
