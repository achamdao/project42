#include "RPN.hpp"


int main(int argc , char **arr)
{
    
    try
    {
        RPN n;
        if (argc == 1)
            throw RPN::Error("Error: add more args !!");
       std::cout << n.eval(arr)<< std::endl;
    }
    catch(RPN::Error e)
    {
        e.write_error();
        return 1;
    }
    
    return 0;
}