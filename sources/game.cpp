#include "game.hpp"
#include "card.hpp"
#include <random>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace ariel;
using namespace std;

Game::Game(Player &player1, Player &player2) : p1(player1), p2(player2)
{
    if (&player1 == &player2)
    {
        throw logic_error("One cannot play with himself!");
    }
    else if (p1.is_in_game() || p2.is_in_game())
    {
        throw logic_error("One cannot play in couple of games!");
    }
    p1.join_game();
    p2.join_game();
    draws = firstWon = secondWon = 0;
    createDeck();
    shuffleDeck();
    dealCards();
}

void Game::createDeck()
{
    // Create a deck of cards with all possible suit and rank combinations
    const std::string suits[] = {"Spades", "Hearts", "Diamonds", "Clubs"};
    const int ranks[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

    for (const std::string &suit : suits)
    {
        for (int rank : ranks)
        {
            m_deck.emplace_back(suit, rank);
        }
    }
}

void Game::shuffleDeck()
{
    std::random_device rd;
    std::mt19937 g(rd());
    // Use std::shuffle to randomly shuffle the cards in the deck
    std::shuffle(std::begin(m_deck), std::end(m_deck), g);
}

void Game::dealCards()
{
    // Divide the shuffled deck of cards equally between the two players
    for (size_t i = 0; i < m_deck.size(); i++)
    {
        if (i % 2 == 0)
        {
            p1.addCardToStack(m_deck[i]);
        }
        else
        {
            p2.addCardToStack(m_deck[i]);
        }
    }
}

// Game::~Game()
// {

// }
void Game::playTurn()
{
    bool flag = true;
    string log = "";
    std::vector<Card> deck;
    while (flag)
    {
        Card c1 = p1.poolCard();
        Card c2 = p2.poolCard();
        deck.emplace_back(c1);
        deck.emplace_back(c2);
        log += p1.getName() + " played " + c1.getRankStr() + " of " + c1.getSuit() + " " +
              p2.getName() + " played " + c2.getRankStr() + " of " + c2.getSuit() + ". ";
        if (c1.getRank() > c2.getRank())
        {
            // Player 1 won
            firstWon++;
            rates[c1.getRank()]++;
            log += p1.getName() + " wins.";
            p1.addCardsToTakenCards(deck);
            flag = false;
        }
        else if (c1.getRank() < c2.getRank())
        {
            // Player 2 won
            secondWon++;
            rates[c2.getRank()]++;
            log += p2.getName() + " wins.";
            p2.addCardsToTakenCards(deck);
            flag = false;
        }
        else
        {
            // Draw
            log += "draw. ";
            draws++;
            // Check whether it is the end of the stack
            if (p1.stacksize() != 0)
            {
                // The upside-down cards
                c1 = p1.poolCard();
                c2 = p2.poolCard();
                deck.emplace_back(c1);
                deck.emplace_back(c2);
            }
            if (p1.stacksize() == 0)
            {
                // Split the deck equally
                std::vector<Card> v1, v2;
                for (size_t i = 0; i < deck.size(); i++) {
                    if (i < deck.size() / 2) {
                        v1.push_back(deck[i]);
                    } else {
                        v2.push_back(deck[i]);
                    }
                } 
                p1.addCardsToTakenCards(v1);
                p2.addCardsToTakenCards(v2);
                flag = false;
            }
            
        }
    }
    m_turnLog.push(log);
}

void Game::printLastTurn()
{
    cout << m_turnLog.top() << endl;
}

void Game::playAll()
{
    if (p1.stacksize() == 0)
    {
        throw std::logic_error("Game is over!");
    }
    while (p1.stacksize() > 0)
    {
        playTurn();
    }
}

void Game::printWiner()
{
    if (p1.stacksize() != 0)
    {
        throw std::logic_error("The game is not over");
    }
    else
    {
        if (p1.cardesTaken() > p2.cardesTaken())
        {
            cout << p1.getName() + " won!" << endl;
        }
        else if (p1.cardesTaken() < p2.cardesTaken())
        {
            cout << p2.getName() + " won!" << endl;
        }
        else
            cout << "Draw!" << endl;   
    }
    
}

void Game::printLog()
{
    stack<string> temp;
    while (!m_turnLog.empty())
    {
        temp.push(m_turnLog.top());
        m_turnLog.pop();
    }

    while (!temp.empty())
    {
        cout << temp.top() << endl;
        m_turnLog.push(temp.top());
        temp.pop();
    }
}

void Game::printStats()
{
    cout << "Number of draws during all game is " + to_string(draws) << endl;
    cout << "First player won " + to_string(firstWon) + " times" << endl;
    cout << "Second player won " + to_string(secondWon) + " times" << endl;
    int n = sizeof(rates) / sizeof(rates[0]);
    int max_val = rates[0];
    for (size_t i = 1; i < n; i++) {
        if (rates[i] > max_val) {
            max_val = i;
        }
    }
    string strongest_card;
    if (max_val < 11 && max_val != 1)
    {
        strongest_card = to_string(max_val);
    }
    else if (max_val == 11)
    {
        strongest_card = "Jack";
    }
    else if (max_val == 12)
    {
        strongest_card = "Queen";
    }
    else if (max_val == 13)
    {
        strongest_card = "King";
    }
    else
    {
        strongest_card = "Ace";
    }
        
    cout << "The card which won most times is " + strongest_card + " which won " + to_string(rates[(size_t)max_val]) + " times"<< endl;
}
