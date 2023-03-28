#pragma once

#include <iostream>
using namespace std;

namespace ariel
{
    class Card
    {
    private:
        string m_suit;
        int m_rank;

    public:
        Card() = default;
        Card(string str, int num);
        //~Card();
        std::string getSuit() const;
        int getRank();
        std::string getRankStr() const;
    };
}
