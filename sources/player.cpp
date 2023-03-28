#include "player.hpp"
#include <stack>
using namespace ariel;

Player::Player(std::string name) : m_name(name) {in_game = false;}

void Player::addCardToStack(Card& card)
{
    m_cardStack.emplace_back(card);
}
void Player::addCardsToTakenCards(std::vector<Card>& deck)
{
    m_takenCards.insert(m_takenCards.end(), deck.begin(), deck.end());
}

Card Player::poolCard()
{
    if (m_cardStack.empty())
    {
        throw std::out_of_range("Player's stack is empty");
    }

    Card card = m_cardStack.front();
    m_cardStack.erase(m_cardStack.begin());
    return card;
}

int Player::stacksize()
{
    return m_cardStack.size();
}

int Player::cardesTaken()
{
    return m_takenCards.size();
}
std::string Player::getName()
{
    return m_name;
}

bool Player::is_in_game(){
    return in_game;
}
void Player::join_game() 
{
    if (in_game) {
        throw std::logic_error("Player is already in a game");
    }
    // set the in_game flag to true
    in_game = true;
}