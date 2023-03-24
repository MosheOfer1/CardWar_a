#include "game.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace ariel;
using namespace std;

Game::Game(Player player1, Player player2) : p1(player1),p2(player2)
{
    for (size_t i = 1; i <= 13; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
        }
    }
}
// Game::~Game()
// {

// }
void Game::playTurn()
{
    // To be implemented
}

void Game::printLastTurn()
{
    // To be implemented
    cout << "Hello, World!" << endl;
}

void Game::playAll()
{
    // To be implemented
}

void Game::printWiner()
{
    // To be implemented
}

void Game::printLog()
{
    // To be implemented
}

void Game::printStats()
{
    // To be implemented
}
