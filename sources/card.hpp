#pragma once

#include <iostream>
using namespace std;

namespace ariel
{
    class Card
    {
    private:
        string suit;
        int rank;

    public:
        Card(string str, int num);
        //~Card();
        string get_suit();
        int get_rank();
    };
}
