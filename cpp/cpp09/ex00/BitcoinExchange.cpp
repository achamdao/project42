#include "BitcoinExchange.hpp"
#include <fstream>
#include <exception>

BitcoinExchange::BitcoinExchange(){};
BitcoinExchange::BitcoinExchange(const BitcoinExchange &src)
{
    _Data = src._Data;
}
BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &src)
{
    if (this != &src)
        _Data = src._Data;
    return *this;
}
BitcoinExchange::~BitcoinExchange(){}

void BitcoinExchange::StoreData(std::string str)
{
    std::ifstream file(str.c_str());
    if (!file.is_open()) {
        throw "Error: Could not open the file.";
    }
    std::string line;
    bool flag = false;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        size_t commaPos = line.find(',');
        if (commaPos == std::string::npos)
        {
            file.close();
            throw "Error: not have ','.";
        }
        std::string date = line.substr(0, commaPos);
        std::string rateStr = line.substr(commaPos + 1);
        if (!flag)
        {
           if (date != "date" || rateStr != "exchange_rate")
           {
                throw "Error: the key value not valid";
                file.close();
           }
            flag = true;
           continue;
        }
        _Data[date] = rateStr;
    }
    file.close();
}

std::string BitcoinExchange::trim(const std::string &s)
{
    size_t start = s.find_first_not_of(" \t");
    size_t end = s.find_last_not_of(" \t");
    if (start == std::string::npos)
        return "";
    return s.substr(start, end - start + 1);
}

bool BitcoinExchange::isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool BitcoinExchange::isValidDate(const std::string &date)
{
    if (date.size() != 10 || date[4] != '-' || date[7] != '-')
        return false;
    for (size_t i = 0; i < date.size(); i++)
    {
        if (i == 4 || i == 7)
            continue;
        if (!std::isdigit(date[i]))
            return false;
    }
    int month = std::atoi(date.substr(5, 2).c_str());
    int day   = std::atoi(date.substr(8, 2).c_str());
    int year   = std::atoi(date.substr(0, 4).c_str());
    if (month < 1 || month > 12)
        return false;
    const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int maxDay = daysInMonth[month - 1];

    if (month == 2 && isLeapYear(year))
        maxDay = 29;

    if (day < 1 || day > maxDay)
        return false;
    return true;
}

bool BitcoinExchange::isValidValue(const std::string &value, double &out)
{
    if (value.empty())
        return false;
    std::stringstream d;
    d << value;
    d >> out;
    if (d.fail() || !d.eof())
        return false;
    if (out < 0 || out > 1000)
        return false;
    return true;
}

double BitcoinExchange::getRateForDate(const std::string &date)
{
    std::map<std::string, std::string>::const_iterator it = _Data.lower_bound(date);
    double d = 0;
    std::stringstream s;
    if(it == _Data.end())
        return -1;

    if ((*it).first == date)
    {
        s << (*it).second;
        s >> d;
        return d;
    }
    else if (it == _Data.begin())
        return -1;
    --it;
    s << (*it).second;
    s >> d;
    return d;
}

void BitcoinExchange::parseData(std::string str)
{
    std::ifstream file(str.c_str());
    if (!file.is_open()) 
        throw "Error: Could not open input file.";
    std::string line;
    bool flag = false;
    std::string key ;
    std::string value;

    while (std::getline(file, line)) 
    {
        if (line.empty()) 
            continue;
        size_t Pos = line.find('|');
        if (Pos == std::string::npos)
        {
            std::cout << "Error: not have '|'."<< std::endl;
            continue;
        }
        key = trim(line.substr(0, Pos));
        value = trim(line.substr(Pos + 1));
        if (key.empty() || value.empty())
        {
            std::cout << "Error: the key value empty"<< std::endl;
            continue;
        }
        if (!flag)
        {
           if (key != "date" || value != "value")
                std::cout << "Error  : start line "<< line <<std::endl;
            flag = true;
            continue;
        }
        if (!isValidDate(key))
        {
            std::cout << "Error  : bad input "<< line <<std::endl;
            continue;
        }
        double val;
        if (!isValidValue(value, val))
        {
            std::cout << "Error  : bad input "<< line <<std::endl;
            continue;
        }
        double f = getRateForDate(key);
        if (f == -1)
        {
            std::cout << "Error  : bad input "<< line <<std::endl;
            continue;
        }
        std::cout <<key << " = "<<value<< " => " << val * f <<std::endl;
    }   
    file.close();
}