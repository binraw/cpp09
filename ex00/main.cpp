#include "BitcoinExchange.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <string>

int main(int argc, char **argv)
{
    (void) argv; 

    if (argc != 2)
    {
	    std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }
    std::map<std::string, int> myMap; // Déclaration de la map
    std::ifstream file("data.csv");
    if (!file.is_open()) 
    {
        std::cerr << "Could not open the file." << std::endl;
        return 1;
    }
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
    std::map<std::string, int>::iterator it;
    for (it = myMap.begin();it != myMap.end(); it++)
    {
        std::cout << it->first << std::endl;
    }
    std::string line_file;
    std::ifstream file_input(argv[1]);
    if (!file_input.is_open()) 
    {
        std::cerr << "Could not open the input file." << std::endl;
        return 1;
    }
    while(std::getline(file_input, line_file))
    {
        std::stringstream ssf(line_file);
        std::string key_file;
        std::string valueFile;
        std::map<std::string, int>::iterator it_find;
        if (std::getline(ssf, key_file, '|') && std::getline(ssf, valueFile))
        {
            int nb_btc;
            it_find = myMap.find(key_file);
            std::cout << it_find->first << std::endl; 
            if (it_find != myMap.end()) //find la value correspondante a la date
            {
                std::stringstream(valueFile) >> nb_btc;
                nb_btc = it_find->second * nb_btc;
                std::cout << "Valeur fin : " << nb_btc << std::endl;
            }
            else
                std::cout << "rien trouver avec : " << key_file << std::endl;
        }
    }
    file.close(); 
    file_input.close();
	return 0;
}


// je prends chaque ligne de mon fichier et je l'envoie dasn une fonction et je regarde si elle est trouver dans ma map 
// our ca je pense faire une boucle sur la focntion et envoyer a chaque fois la ligne suivante du fichier dnner en argv
// et std::cout le resultat de la recherche
// void print_result(std::map<std::string, int> map, std::string lign)
// {
//     
//
// }

// int copy_file(std::string filename, std::vector<typename T>)
// {
// 	if (!filename.is_open())
// 	{
// 		std::cerr << "Could not open the file: " << filename << std::endl;
// 		return (-1);
// 	}
// 	string str;
// 	while (getline(filename, str))
// 	{
// 		T.push_back(str);
// 	}
// 	filename.close();
// } 
