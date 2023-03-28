#include "card.hpp"
using namespace ariel;

Card::Card(std::string suit, size_t rank)
{
    m_suit = suit;
    m_rank = rank;
}
// Card::~Card()
// {
//     // To be implemented
// }
std::string Card::getSuit() const
{
    return m_suit;
}
size_t Card::getRank()
{
    return m_rank;
} 
std::string Card::getRankStr() const
{
    if (m_rank < 11 && m_rank != 1)
    {
        return std::to_string(m_rank);
    }
    else if (m_rank == 11)
    {
        return "Jack";
    }
    else if (m_rank == 12)
    {
        return "Queen";
    }
    else if (m_rank == 13)
    {
        return "King";
    }
    return "Ace";
}
