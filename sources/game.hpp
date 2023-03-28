#pragma once

#include <iostream>
#include <stack>
#include <array>
#include "player.hpp"
size_t const NUM_OF_RANKS = 13;
namespace ariel
{
    class Game
    {
    private:
        Player &p1, &p2;
        std::vector<Card> m_deck;
        array<string, 4> m_suits = {"Hearts", "Diamonds", "Clubs", "Spades"};
        std::stack<std::string> m_turnLog;
        int draws, firstWon, secondWon;
        array<int, NUM_OF_RANKS> rates = {0};
        
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
