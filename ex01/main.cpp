#include "RPN.hpp"
#include <iostream>
#include <sstream>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: ./RPN <RPN expression>" << std::endl;
        return 1;
    }

    std::string input;
    for (int i = 1; i < argc; ++i)
    {
        input += argv[i];
        if (i != argc - 1)
            input += " ";
    }

    RPN rpn;
    rpn.evaluateRPN(input);

    return 0;
}

