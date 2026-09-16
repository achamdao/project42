#ifndef PMERGEME_HPP
#define PMERGEME_HPP
#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <sstream>
#include <algorithm>

class Pmergeme 
{

    std::vector<int> _Jacobsthal;
    std::vector<int> _meanchain;
    std::deque<int> _Jacobsthal_deque;
    std::deque<int> _meanchain_deque;
    public:
    Pmergeme();
    Pmergeme(int size);
    Pmergeme & operator=(const std::vector<int> &meanchain);
    ~Pmergeme();

    void apliqueAlgo(const std::vector<int> &N);
    void apliqueAlgo(const std::deque<int> &N);
    void Jacobsthal(int size);
    void Jacobsthal_deque(int size);
    const std::vector<int> &Getmainchain() const;
    const std::deque<int> &Getmainchain_deque() const;
    int searcher(std::vector<std::pair<int, int> > &pairs, int first);
    int searcher(std::deque<std::pair<int, int> > &pairs, int first);
};

template <typename cData>
void Print_Vector(const cData &  Data)
{
    typename cData::const_iterator it ;
    for (it = Data.begin() ; it != Data.end();it++)
        std::cout << *it << " " ;
    
    std::cout << "\n" ;
}

#endif