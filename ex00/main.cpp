#include "BitcoinExchange.hpp"


int main(int argc, char **argv)
{

    if (argc != 2)
    {
	    std::cout << "Error: could not open file." << std::endl;
        return 1;
    }
    std::string arg = (std::string(argv[1]));
    BitcoinExchange bitcoin(arg);
    
	return 0;
}



