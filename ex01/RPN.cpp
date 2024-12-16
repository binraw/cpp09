#include "RPN.hpp"
#include <stack>
#include <strstream>

 
RPN::RPN()
{
}
RPN::RPN(std::string &str)
{}
RPN::RPN(const RPN &other)
{}
RPN &RPN::operator=(const RPN &other)
{}
RPN::~RPN()
{}
void RPN::calcul(std::string &str)
{
	std::istrstream iss(str);
	std::string token;

	while (iss >> token)
	{
		if (isNumber(token))
		{
			int number = std::stoi(token);
			if (number > 10)
			{
				std::cout << "Error : too large a number." << std::endl;
				return ;
			}
			_rpn.push(number);
		}
		else
		{
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
				result = nu / nu2;
			_rpn.push(result);
		}
	}
	std::cout << "Result: " << _rpn.top() << std::endl;
}

bool isNumber(std::string &str)
{
	if (!str.empty())
		return false;
	for (char c : str)
	{
		if (c < '0' || c > '9')
			return false;
	}
	return true;
}
