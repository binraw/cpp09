#include "BitcoinExchange.hpp"
#include <fstream>


BitcoinExchange::BitcoinExchange()
{
    _dataBase = "data.csv";
    _filename = "input.txt";
    process();

}
BitcoinExchange::BitcoinExchange(std::string &filename)
{
    _dataBase = "data.csv";
    _filename = filename;
    process();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{

}
BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{

}
BitcoinExchange::~BitcoinExchange()
{

}

void BitcoinExchange::process()
{
    _dataMap = initDataMap();
    mainLoop();

}

std::map<std::string, int> BitcoinExchange::initDataMap() throw()
{
    std::map<std::string, int> myMap;
    std::ifstream file("data.csv");
    if (!file.is_open()) 
        throw ErrorOpenFile();
    std::string line;
    while (std::getline(file, line)) 
    {
        std::stringstream ss(line);
        std::string key;
        std::string valueStr;

        if (std::getline(ss, key, ',') && std::getline(ss, valueStr))
        {
            int value;
            std::stringstream(valueStr) >> value;
            myMap[key] = value;
        }
    }
    file.close();
    return myMap;
}

void BitcoinExchange::mainLoop() throw()
{
    std::string line_file;
    std::ifstream file_input(_filename);
    if (!file_input.is_open()) 
        throw ErrorOpenFile();
    while(std::getline(file_input, line_file))
    {
        std::stringstream ssf(line_file);
        std::string key_file;
        std::string valueFile;
        std::map<std::string, int>::iterator it_find;
        if (std::getline(ssf, key_file, '|') && std::getline(ssf, valueFile))
        {
            float nb_btc = 0;
            std::stringstream(valueFile) >> nb_btc;
            key_file = trim(key_file);
            std::map<std::string, int>::iterator it_find = _dataMap.lower_bound(key_file);
            if (is_valid_date(key_file) == 0)
                std::cout << "Error : Bad input => " << key_file << std::endl;
            else if (nb_btc < 0 || nb_btc > 1000)
            {
                if (nb_btc > 1000)
                    std::cout << "Error : too large a number." << std::endl;
                else
                    std::cout << "Error : not a positive number." << std::endl;
            }
            else if (it_find != _dataMap.end())
            {
                int value_btc = it_find->second;
                std::cout << key_file << " => " << nb_btc * value_btc << std::endl;
            } 
        }
    }
    file_input.close();
}

const char* BitcoinExchange::ErrorOpenFile::what() const throw()
{
    return "Could not open the file.";
}
std::string trim(const std::string& str) 
{
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return (first == std::string::npos) ? "" : str.substr(first, last - first + 1); 
}

bool BitcoinExchange::is_valid_date(std::string &date)
{
    int year;
    int month;
    int day;

    if (date.length() != 10 || date[4] != '-' || date[7] != '-')
        return false;
    year = std::atoi(date.substr(0, 4).c_str());
    month = std::atoi(date.substr(5, 2).c_str());
    day = std::atoi(date.substr(8, 2).c_str());
    if (year > 2025)
        return false;
    if (month > 12 || month < 1)
        return false;
    if (day > 31 || day < 1)
        return false;
    if (month == 2)
    {
        if (day > 29)
            return false;
    }
    if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        if (day > 30)
            return false;
    }
    return true;
}