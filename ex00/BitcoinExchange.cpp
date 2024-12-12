#include "BitcoinExchange.hpp"
#include <fstream>

// int BitcoinExchange::copy_file()
// {
// 	if (!_filename.is_open())
// 	{
// 		std::cerr << "Could not open the file: " <<  std::endl;
// 		return (-1);
// 	}
// 	std::string str;
// 	while (std::getline(_filename, str))
// 	{
// 		_container.push_back(str);
// 	}
// 	_filename.close();
// 	return (0);
// }
//
//
// BitcoinExchange::BitcoinExchange()
// {
//
// }
// int BitcoinExchange::print_file()
// {
// 	std::vector<std::string>::iterator it_start = _container.begin();
// 	std::vector<std::string>::iterator it_end = _container.end();
// 	std::vector<std::string>::iterator it = it_start;
//
// 	while(it != it_end)
// 	{
// 		std::cout << *it << std::endl;
// 		it++;
// 	}
// 	return (0);
// }
// BitcoinExchange::BitcoinExchange(std::string &filename)
// {
// 	std::string str;
// 	std::string str_data_base;
// 	_filename.open(filename.c_str());
// 	if (!_filename.is_open())
// 	{
// 		std::cerr << "Could not open the file" <<  std::endl;
// 		return ;
// 	}
// 	_dataBase.open("./input.txt");
// 	if (!_dataBase.is_open())
// 	{
// 		std::cerr << "Error with Data Base" << std::endl;
// 		return;
// 	}
// 	while (std::getline(_dataBase, str_data_base))
// 	{
// 		_containerDataBase.push_back(str_data_base);
// 	}
// 	_dataBase.close();
// 	while (std::getline(_filename, str))
// 	{
// 		_container.push_back(str);
// 	}
// 	print_file();
// 	_filename.close();
//
// }
// BitcoinExchange::BitcoinExchange(const BitcoinExchange &)
// {
// 	// _container = other._container;
// 	// _filename = other._filename;
// 	// _dataBase = other._dataBase;
// 	// _containerDataBase = other._containerDataBase;
// }
// BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &)
// {
// // 	if (this != &other)
// // 	{
// // 		_filename.close();
// // 		_filename = other._filename;
// // 		_container.clear();
// // 		_containerDataBase.clear();
// 	return *this;
// }
// BitcoinExchange::~BitcoinExchange()
// {
// 	if (_filename.is_open())
// 		_filename.close();
// 	if (_dataBase.is_open())
// 		_dataBase.close();
// }
