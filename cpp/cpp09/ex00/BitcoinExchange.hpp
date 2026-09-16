#ifndef BETCOIN_EXANGE
#define BETCOIN_EXANGE
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <stdlib.h>

class BitcoinExchange
{
    private:
        std::map<std::string, std::string> _Data;
        double getRateForDate(const std::string &date);
        std::string trim(const std::string &s);
        bool isLeapYear(int year);
        bool isValidDate(const std::string &date);
        bool isValidValue(const std::string &value, double &out);
    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &src);
        BitcoinExchange &operator=(const BitcoinExchange &src);
        ~BitcoinExchange();
        void StoreData(std::string str);
        void parseData(std::string str);
        
};

#endif