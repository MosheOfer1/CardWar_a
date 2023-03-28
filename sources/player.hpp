#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "card.hpp"
namespace ariel
{
    class Player
    {
    private:
        std::string m_name;
        std::vector<Card> m_cardStack;
        std::vector<Card> m_takenCards;
        bool in_game;
    public:
        Player(string str);
        //~Player(){};
        void addCardToStack(Card& card);
        void addCardsToTakenCards(std::vector<Card>& deck);
        Card poolCard();
        int stacksize();
        int cardesTaken();
        std::string getName();
        bool is_in_game();
        void join_game();
    };
}
