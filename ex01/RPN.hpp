#ifndef RPN_HPP
# define RPN_HPP

#include <string>
#include <iostream>
#include <stack>

class RPN
{
public:
	RPN();
	RPN(std::string &str);
	RPN(const RPN &other);
	RPN &operator=(const RPN &other);
	~RPN();
	void calcul(std::string &str);
private:
	std::stack<int> _rpn;
};

bool isNumber(std::string &str);

#endif
