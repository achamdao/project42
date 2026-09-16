#include "BitcoinExchange.hpp"


int main(int argc, char **arr)
{
    if (argc !=2)
    {
        std::cerr<< "Error: argc not valid please enter input file !!\n";
        return 1;
    }
   try
   {
        BitcoinExchange o;
        o.StoreData("data.csv");
        o.parseData(arr[1]);
   }
   catch(const char* e)
   {
        std::cerr << e << '\n';
        return 1;
   }
   
    return 0;
}