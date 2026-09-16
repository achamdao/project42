#include "PmergeMe.hpp"

Pmergeme::Pmergeme()
{

}
Pmergeme::Pmergeme(int size)
{
    Jacobsthal(size);
}
Pmergeme & Pmergeme::operator=(const std::vector<int> &meanchain)
{
    _meanchain = meanchain;
    return *this;
}

Pmergeme::~Pmergeme(){}

//vector

int Pmergeme::searcher(std::vector<std::pair<int, int> > &pairs, int first)
{
    size_t i = 0;
    while (i < pairs.size())
    {
        if (pairs[i].first == -1)
        {
            i++;
            continue;
        }
        if (pairs[i].first == first)
        {
            pairs[i].first = -1;
            return i;
        }
        i++;
    }
    return -1;
}

void Pmergeme::apliqueAlgo(const std::vector<int> &N)
{
    if (N.size() == 1)
    {
        _meanchain.push_back(N[0]);
        return ;
    }
    std::vector<std::pair<int, int> > pairs;
    std::vector<int> larger;
    size_t i = 0;
    int impair = -1;
    while (true)
    {
        i = i + 2;

        if(i == N.size())
        {
            std::pair<int, int> item;
            int index = i -1;
            if (N[index] < N[index -1])
            {
                
                item.first = N[index -1];
                item.second = N[index];
                
            }
            else
            {
                item.first = N[index];
                item.second = N[index -1];
            }
            pairs.push_back(item);
            break;
        }
        else if (i == N.size() + 1)
        {

            impair = N[N.size() -1];
            break;
        }
        else
        {
            std::pair<int, int> item;
            int index = i -1;
            if (N[index] < N[index -1])
            {
                
                item.first = N[index -1];
                item.second = N[index];
                
            }
            else
            {
                item.first = N[index];
                item.second = N[index -1];
            }
            pairs.push_back(item);
        }
    }
    i = 0;
    while ( i < pairs.size())
    {
        larger.push_back(pairs[i].first);
        i++;
    }
    apliqueAlgo(larger);
    _Jacobsthal.clear();
    Jacobsthal((int)larger.size());
    std::vector<int> copymainchain = _meanchain;

    i = 0;
    size_t state = 0;
    while (i < _Jacobsthal.size())
    {

        size_t sequence = _Jacobsthal[i];
        if ((sequence == 0))
        {
            _meanchain.insert(_meanchain.begin(), pairs[searcher(pairs, copymainchain[sequence])].second);
            state =  sequence;
        }
        else
        {
            sequence = (sequence == pairs.size())? sequence -1: sequence;
            for(size_t index = sequence; state != index; index--)
            {
                int search = searcher(pairs, copymainchain[index]);
                std::vector<int>::iterator mainchain_index = std::find(_meanchain.begin(), _meanchain.end(), copymainchain[index]);
                std::vector<int>::iterator it = std::lower_bound(_meanchain.begin(), mainchain_index,  pairs[search].second);
                _meanchain.insert(it, pairs[search].second);
            }
            state =  sequence;
        }
        i++;
    }
    for(size_t index = pairs.size() -1; state != index; index--)
    {
        int search = searcher(pairs, copymainchain[index]);
        std::vector<int>::iterator mainchain_index = std::find(_meanchain.begin(), _meanchain.end(), copymainchain[index]);
        std::vector<int>::iterator it = std::lower_bound(_meanchain.begin(), mainchain_index,  pairs[search].second);
        _meanchain.insert(it, pairs[search].second);
    }
    if (impair != -1)
    {
        std::vector<int>::iterator it = std::lower_bound(_meanchain.begin(), _meanchain.end(), impair);
        _meanchain.insert(it, impair);
    }
    
}

void Pmergeme::Jacobsthal(int size)
{
    int j0 = 0;
    int j1 = 1;
    int jn = 0;
   _Jacobsthal.push_back(j0);
   while(true)
   {
        jn = j1 + 2 * j0;

        if (jn > size)
            break;
        _Jacobsthal.push_back(jn);
        j0 = j1;
        j1 = jn;
   }
}


//deque


int Pmergeme::searcher(std::deque<std::pair<int, int> > &pairs, int first)
{
    size_t i = 0;
    while (i < pairs.size())
    {
        if (pairs[i].first == -1)
        {
            i++;
            continue;
        }
        if (pairs[i].first == first)
        {
            pairs[i].first = -1;
            return i;
        }
        i++;
    }
    return -1;
}

void Pmergeme::apliqueAlgo(const std::deque<int> &N)
{
    if (N.size() == 1)
    {
        _meanchain_deque.push_back(N[0]);
        return ;
    }
    std::deque<std::pair<int, int> > pairs;
    std::deque<int> larger;
    size_t i = 0;
    int impair = -1;
    while (true)
    {
        i = i + 2;

        if(i == N.size())
        {
            std::pair<int, int> item;
            int index = i -1;
            if (N[index] < N[index -1])
            {
                
                item.first = N[index -1];
                item.second = N[index];
                
            }
            else
            {
                item.first = N[index];
                item.second = N[index -1];
            }
            pairs.push_back(item);
            break;
        }
        else if (i == N.size() + 1)
        {

            impair = N[N.size() -1];
            break;
        }
        else
        {
            std::pair<int, int> item;
            int index = i -1;
            if (N[index] < N[index -1])
            {
                
                item.first = N[index -1];
                item.second = N[index];
                
            }
            else
            {
                item.first = N[index];
                item.second = N[index -1];
            }
            pairs.push_back(item);
        }
    }
    i = 0;
    while ( i < pairs.size())
    {
        larger.push_back(pairs[i].first);
        i++;
    }
    apliqueAlgo(larger);
    _Jacobsthal_deque.clear();
    Jacobsthal_deque((int)larger.size());
    std::deque<int> copymainchain = _meanchain_deque;

    i = 0;
    size_t state = 0;
    while (i < _Jacobsthal_deque.size())
    {

        size_t sequence = _Jacobsthal_deque[i];
        if ((sequence == 0))
        {
            _meanchain_deque.insert(_meanchain_deque.begin(), pairs[searcher(pairs, copymainchain[sequence])].second);
            state =  sequence;
        }
        else
        {
            sequence = (sequence == pairs.size())? sequence -1: sequence;
            for(size_t index = sequence; state != index; index--)
            {
                int search = searcher(pairs, copymainchain[index]);
                std::deque<int>::iterator mainchain_index = std::find(_meanchain_deque.begin(), _meanchain_deque.end(), copymainchain[index]);
                std::deque<int>::iterator it = std::lower_bound(_meanchain_deque.begin(), mainchain_index,  pairs[search].second);
                _meanchain_deque.insert(it, pairs[search].second);
            }
            state =  sequence;
        }
        i++;
    }
    for(size_t index = pairs.size() -1; state != index; index--)
    {
        int search = searcher(pairs, copymainchain[index]);
        std::deque<int>::iterator mainchain_index = std::find(_meanchain_deque.begin(), _meanchain_deque.end(), copymainchain[index]);
        std::deque<int>::iterator it = std::lower_bound(_meanchain_deque.begin(), mainchain_index,  pairs[search].second);
        _meanchain_deque.insert(it, pairs[search].second);
    }
    if (impair != -1)
    {
        std::deque<int>::iterator it = std::lower_bound(_meanchain_deque.begin(), _meanchain_deque.end(), impair);
        _meanchain_deque.insert(it, impair);
    }
    
}

void Pmergeme::Jacobsthal_deque(int size)
{
    int j0 = 0;
    int j1 = 1;
    int jn = 0;
   _Jacobsthal_deque.push_back(j0);
   while(true)
   {
        jn = j1 + 2 * j0;

        if (jn > size)
            break;
        _Jacobsthal_deque.push_back(jn);
        j0 = j1;
        j1 = jn;
   }
}

const std::deque<int> &Pmergeme::Getmainchain_deque() const
{
    return _meanchain_deque;
}

const std::vector<int> &Pmergeme::Getmainchain() const
{
    return _meanchain;
}