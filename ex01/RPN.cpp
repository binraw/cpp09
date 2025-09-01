#include "RPN.hpp"

 
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



bool isNumber(const std::string& s)
{
    if (s.empty())
        return false;

    for (std::size_t i = 0; i < s.length(); ++i)
    {
        if (!std::isdigit(s[i]))
            return false;
    }
    return true;
}


void RPN::evaluateRPN(const std::string& input)
{
	std::istringstream iss(input);
	std::string token;
	std::stack<int> rpnStack;

	while (iss >> token)
	{
		if (isNumber(token))
		{
			int number = std::atoi(token.c_str());
			if (number > 10)
			{
				std::cerr << "Error: too large a number." << std::endl;
				return;
			}
			rpnStack.push(number);
		}
		else
		{
			if (rpnStack.size() < 2)
			{
				std::cerr << "Error: not enough operands." << std::endl;
				return;
			}

			int b = rpnStack.top(); rpnStack.pop();
			int a = rpnStack.top(); rpnStack.pop();
			int result = 0;

			if (token == "+")
				result = a + b;
			else if (token == "-")
				result = a - b;
			else if (token == "*")
				result = a * b;
			else if (token == "/")
			{
				if (b == 0)
				{
					std::cerr << "Error: division by zero." << std::endl;
					return;
				}
				result = a / b;
			}
			else
			{
				std::cerr << "Error: invalid operator." << std::endl;
				return;
			}
			rpnStack.push(result);
		}
	}

	if (rpnStack.size() != 1)
	{
		std::cerr << "Error: invalid expression." << std::endl;
		return;
	}

	std::cout << "Result: " << rpnStack.top() << std::endl;
}
