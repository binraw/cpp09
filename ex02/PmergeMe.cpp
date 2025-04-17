#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{

}

PmergeMe::PmergeMe(char **argv)
{

}

PmergeMe::PmergeMe(const PmergeMe &other)
{

}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{

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

int PmergeMe::control_value(char *value)
{
    try {
        int result = std::atoi(value);
    }
    catch (std::invalid_argument const& ex){
        throw
    }
    catch (std::out_of_range const& ex){
        throw
    }
    if (std::find(_containerDeque.begin(), _containerDeque.end(), result) == _containerDeque.end())
        _containerDeque.push(result);
    else
        throw //doublon
}