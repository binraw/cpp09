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

void PmergeMe::controlValue(char *value)
{
    int result;
    try {
        result = std::atoi(value);
    }
    catch (std::invalid_argument const& ex){
        throw ;
    }
    catch (std::out_of_range const& ex){
        throw ;
    }
    if (result)
    {
        if (std::find(_containerDequePair.begin(), _containerDequePair.end(), result) == _containerDequePair.end())
           return;
        else
            throw ; //doublon
    }
    else
        throw ; // no value
}

void PmergeMe::createDoublon(int argc, char **argv)
{
    if ((argc % 2) == 0) // si impair args
    {
        int i = 1;
        controlValue(argv[i]);
        _containerDequeLong.push_back(std::atoi(argv[i]));
        for (i = 2; i < argc; i += 2) 
        {
            if (i + 1 < argc)
            {
                controlValue(argv[i]);
                controlValue(argv[i + 1]);
                int first = std::atoi(argv[i]);
                int second = std::atoi(argv[i + 1]);
                _containerDequePair.push_back(std::make_pair(first, second));
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
            }
        }
    }

    for (std::deque<std::pair<int, int>>::iterator it = _containerDequePair.begin(); it != _containerDequePair.end(); it++)
    {
        if (::min(it->first, it->second) == it->second)
            ::swap(it->first, it->second);
    }
}


void PmergeMe::createlargestContainer()
{
    for (std::deque<std::pair<int, int>>::iterator it = _containerDequePair.begin(); it != _containerDequePair.end(); it++)
        _containerDequeLong.push_back(it->second);
     recursiveSort(_containerDequeLong);
}



void PmergeMe::recursiveSort(std::deque<int>& arr) 
{
    if (arr.size() <= 1) 
        return;


    size_t mid = arr.size() / 2;
    std::deque<int> left(arr.begin(), arr.begin() + mid);
    std::deque<int> right(arr.begin() + mid, arr.end());


    recursiveSort(left);
    recursiveSort(right);


    size_t i = 0, j = 0, k = 0;
    while (i < left.size() && j < right.size()) 
    {
        if (left[i] <= right[j]) 
        {
            arr[k++] = left[i++];
        } 
        else 
        {
            arr[k++] = right[j++];
        }
    }

    while (i < left.size()) 
    {
        arr[k++] = left[i++];
    }
    while (j < right.size()) 
    {
        arr[k++] = right[j++];
    }
}