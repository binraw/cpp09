#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

class BitcoinExchange {
private:
	std::string _filename;
	std::string _dataBase;
    std::map<std::string, float> _dataMap;
public:
	BitcoinExchange();
	BitcoinExchange(std::string &filename);
    std::map<std::string, float> initDataMap();
    void process();
    void mainLoop();

    bool is_valid_date(std::string &date);
	BitcoinExchange(const BitcoinExchange &other);
	BitcoinExchange &operator=(const BitcoinExchange &other);
	~BitcoinExchange();

    class ErrorOpenFile: public std::exception
    {
        virtual const char* what() const throw();
    };
};

std::string trim(const std::string& str);


#endif
