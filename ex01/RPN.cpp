#include "RPN.hpp"
#include <stack>
#include <string>
#include <sstream>
#include <iostream>
 
RPN::RPN()
{
}
RPN::RPN(std::string &)
{
}
RPN::RPN(const RPN &)
{}
RPN &RPN::operator=(const RPN &)
{
	return *this;
}
RPN::~RPN()
{}

std::string trim(const std::string& str) 
{
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return (first == std::string::npos) ? "" : str.substr(first, last - first + 1); 
}

void RPN::calcul(std::string &str)
{
	try
	{
	std::istringstream iss(str);
	str = trim(str);
	if (str == "")
		return;

	std::string token;

	while (iss >> token)
	{
		if (isNumber(token))
		{
			std::istringstream iss(token);
			int number;
			
			iss >> number;
			if (number > 10)
			{
				std::cout << "Error : too large a number." << std::endl;
				return ;
			}
			_rpn.push(number);
		}
		else
		{
			if (_rpn.size() < 2)
			{
				std::cout << "Error" << std::endl;
				return ;
			}

			int nu2 = _rpn.top();
			_rpn.pop();
			int nu = _rpn.top();
			_rpn.pop();
			int result = 0;
			if (token == "+")
				result = nu2 + nu;
			else if (token == "*")
				result = nu2 * nu;
			else if (token == "-")
				result = nu - nu2;
			else if (token == "/")
			{
				if (nu2 == 0)
				{
					std::cout << "Error : divion by zero" << std::endl;
					return ;
				}
				result = nu / nu2;
			}
			else
			{
				std::cout << "Error : invalid operator" << std::endl;
				return;
			}  
			_rpn.push(result);
		}
	}

	std::cout << "Result: " << _rpn.top() << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << "Error" << '\n';
	}
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
