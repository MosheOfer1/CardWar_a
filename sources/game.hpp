#pragma once

#include <iostream>
#include <stack>
#include "player.hpp"
namespace ariel
{
    class Game
    {
    private:
        Player &p1, &p2;
        std::vector<Card> m_deck;
        string m_suits[4] = {"Hearts", "Diamonds", "Clubs", "Spades"};
        std::stack<std::string> m_turnLog;
        int draws, firstWon, secondWon;
        int rates[13] = {0};
        
    public:
        Game(Player& player1, Player& player2);
        //~Game();
        void shuffleDeck();
        void createDeck();
        void dealCards();
        void playTurn();
        void printLastTurn();
        void playAll();
        void printWiner();
        void printLog();
        void printStats();
    };
}
