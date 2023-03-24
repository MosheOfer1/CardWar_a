#pragma once

#include <iostream>
#include "card.hpp"
namespace ariel
{
    class Player
    {
    private:
        string name;

    public:
        Player(string str);
        //~Player(){};
        int stacksize() ;
        int cardesTaken();
    };
}
