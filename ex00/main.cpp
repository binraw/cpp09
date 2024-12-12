#include "BitcoinExchange.hpp"
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

	}

	std::map<std::string, int> myMap; // Déclaration de la map
    std::ifstream file("data.csv");

    if (!file.is_open()) {
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
        std::cout << it->first << " value : " << it->second << std::endl;
    }
    std::string line_file;
    while(std::getline(agrv[1], line_file)
    {

        std::stringstream ssf(line_file);
        std::string key_file;
        std::string valueFile;
        if (std::getline(ssf, key_file, '|') && std::getline(ssf, valueFile))
        {

        }

    file.close();

	return 0;
}


// je prends chaque ligne de mon fichier et je l'envoie dasn une fonction et je regarde si elle est trouver dans ma map 
// our ca je pense faire une boucle sur la focntion et envoyer a chaque fois la ligne suivante du fichier dnner en argv
// et std::cout le resultat de la recherche
void print_result(std::map<std::string, int> map, std::string lign)
{
    

}

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
