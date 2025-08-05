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
	void evaluateRPN(const std::string& input);
	~RPN();

private:
	std::stack<int> _rpn;
};


bool isNumber(const std::string& s);

#endif
