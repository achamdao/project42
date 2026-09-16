#include "PmergeMe.hpp"
#include <iostream>

void printFinalResults(const std::deque<int> &before, const std::deque<int>& after, double vec_time, double deq_time) 
{
    std::cout << "Before: ";
    int count = 0;
    for (typename std::deque<int>::const_iterator it = before.begin(); it != before.end(); ++it) {
        std::cout << *it << " ";
        count++;
    }
    std::cout << "\n";

    std::cout << "After:  ";
    count = 0;
    for ( std::deque<int>::const_iterator it = after.begin(); it != after.end(); ++it) {
        std::cout << *it << " ";
        count++;
    }
    std::cout << "\n";

    std::cout << "Time to process a range of " << before.size() 
              << " elements with std::vector : " << vec_time << " us\n";
              
    std::cout << "Time to process a range of " << before.size() 
              << " elements with std::deque : " << deq_time << " us\n";
}
int main(int argc, char **arr)
{
    if ((argc == 1))
    {
        std::cout << "Error: enter at least one number !!\n";
        return 1;
    }
    std::vector<int> Numbers;
    std::deque<int> Numbers_Deque;
    int i = 1;
    while(arr[i])
    {
        std::stringstream N;
        N << arr[i];
        int N2;
        if (!(N >> N2) || N.fail() || !N.eof()) 
        {
            std::cerr << "Error: number not correct !!\n";
            return 1;
        }
        if (N2 < 0)
        {
            std::cerr << "Error: is is not positive number !!\n";
            return 1;
        }
        Numbers.push_back(N2);
        Numbers_Deque.push_back(N2);
        i++;
    }
    Pmergeme n;
    double startv, endv, startd, endd;
    startv = clock();
    n.apliqueAlgo(Numbers);
    endv = clock();
    startd = clock();
    n.apliqueAlgo(Numbers_Deque);
    endd = clock();
    printFinalResults(Numbers_Deque, n.Getmainchain_deque(),endv - startv,  endd - startd);
    return 0;
}