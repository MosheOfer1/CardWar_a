#pragma once

#include <iostream>
using namespace std;

namespace ariel
{
    class Card
    {
    private:
        string m_suit;
        size_t m_rank;

    public:
        Card(string str, size_t num);
        //~Card();
        std::string getSuit() const;
        size_t getRank();
        std::string getRankStr() const;
    };
}
