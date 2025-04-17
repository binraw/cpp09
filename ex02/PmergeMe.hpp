#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <string>
#include <iostream>
#include <stack>
#include <algorithm>

class PmergeMe
{
public:
	PmergeMe();
	PmergeMe(char **argv);
	PmergeMe(const PmergeMe &other);
	PmergeMe &operator=(const PmergeMe &other);
	~PmergeMe();
    class Error: public std::exception
    {
        virtual const char* what() const throw();
    };

private:
	std::deque<int> _containerDeque;
};

bool isNumber(std::string &str);

#endif
