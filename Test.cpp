#include "doctest.h"
#include "sources/player.hpp"
#include "sources/game.hpp"
#include "sources/card.hpp"
#include <stdexcept>
#include <iostream>
#include <sstream>
using namespace ariel;

TEST_CASE("1.check players's stacks in the begging")
{
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2);
    CHECK(p1.stacksize() == 26);
    CHECK(p2.stacksize() == 26);
}

TEST_CASE("2.Two players have the same amount of cards in the stacks after playing a turn")
{
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2);

    game.playTurn();

    CHECK(p1.stacksize() == p2.stacksize());
}

TEST_CASE("3.Play turn after game over by playTurn only")
{
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2);
    int maxNumOfTurns = 26;
    // What will happen if the players keep playing after the end?
    for (int i = 0; i < maxNumOfTurns + 1; i++)
    {
        game.playTurn();
    }
    // The game over, which means the stacks is empty (not negative)
    CHECK(p1.stacksize() == 0);
    CHECK(p2.stacksize() == 0);
}

TEST_CASE("4.Play turn/All after game over2 by playAll")
{
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2);
    game.playAll();
    // Second time
    game.playAll();
    game.playTurn();
    // The game over which means one of the stack is empty (not negative)
    CHECK(p1.stacksize() == 0);
    CHECK(p2.stacksize() == 0);
}

TEST_CASE("5.Player can be in one game only")
{
    Player p1("Alice");
    Player p2("Bob");
    Player p3("Chloe");
    Game game1(p1, p2);
    CHECK_THROWS(Game(p2, p3));
}

TEST_CASE("6.Player cannot play with himself")
{
    Player p1("Alice");
    CHECK_THROWS(Game(p1, p1));
}

TEST_CASE("7.After one turn someone earned, and the second has 0 in cardTaken")
{
    Player p1("Alice");
    Player p2("Bob");
    Game game1(p1, p2);

    // One turn only
    game1.playTurn();
    CHECK(((p1.cardesTaken() > 0 && p2.cardesTaken() == 0) ||
           (p2.cardesTaken() > 0 && p1.cardesTaken() == 0)));
}

TEST_CASE("8.Check if printLastTurn() prints the names of the players to the terminal")
{
    Player p1("Alice");
    Player p2("Bob");
    Game game1(p1, p2);

    stringstream out;
    streambuf *old_cout = cout.rdbuf(out.rdbuf());

    // Call the function
    game1.printLastTurn();
    // Reset
    cout.rdbuf(old_cout);

    // Check that the output contains what we expect
    CHECK(((out.str().find("Alice") != string::npos) &&
           (out.str().find("Bob") != string::npos)));
}

TEST_CASE("9.Check if printWiner() prints the name of one of the players to the terminal")
{
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2);
    game.playAll();

    stringstream out;
    streambuf *old_cout = cout.rdbuf(out.rdbuf());

    // Call the function
    game.printWiner();

    cout.rdbuf(old_cout);

    // Check that the output contains what we expect
    CHECK(((out.str().find("Alice") != string::npos) ||
           (out.str().find("Bob") != string::npos)));
}

int is_draw_word_count_equal_to_26(const string &str)
{
    // Convert the string to lowercase
    string lowercase_str = str;
    transform(lowercase_str.begin(), lowercase_str.end(), lowercase_str.begin(), ::tolower);

    // Count the number of lines
    int num_lines = 1;
    for (char c : lowercase_str)
    {
        if (c == '\n')
        {
            num_lines++;
        }
    }

    // Count the number of occurrences of the word "draw"
    string draw_word = "draw";
    int num_draws = 0;
    size_t pos = lowercase_str.find(draw_word);
    while (pos != string::npos)
    {
        num_draws++;
        pos = lowercase_str.find(draw_word, pos + draw_word.length());
    }
    // Each draw is like 2 turns
    return (num_lines + (2 * num_draws));
}

TEST_CASE("10.Check if printLog() prints one line per turn to the terminal")
{
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2);
    game.playAll();
    stringstream out;
    streambuf *old_cout = cout.rdbuf(out.rdbuf());

    // Call the function
    game.printLog();

    cout.rdbuf(old_cout);

    // Check if the total count is equal to 26 which is the max num of turns
    CHECK(is_draw_word_count_equal_to_26(out.str()) == 26);
}

TEST_CASE("11.Check if printStats() prints something to the terminal")
{
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2);
    game.playAll();
    stringstream out;
    streambuf *old_cout = cout.rdbuf(out.rdbuf());

    // Call the function
    game.printStats();

    cout.rdbuf(old_cout);

    // Check that the output contains what we expect
    CHECK(out.str().length() > 0);
}

TEST_CASE("12.Check if stacks work fine")
{
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2);
    for (int i = 0; i < 5; i++)
    {
        game.playTurn();
    }
    CHECK(p1.stacksize() <= 21);
}

TEST_CASE("13.Check if cards taken works fine")
{
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2);
    for (int i = 0; i < 5; i++)
    {
        game.playTurn();
    }
    CHECK((p1.cardesTaken() != 0 || p2.cardesTaken() != 0));
}

TEST_CASE("14.Shuffle is fine, 2 games not the same")
{
    Player p1("Alice");
    Player p2("Bob");
    Game game1(p1, p2);
    game1.playAll();

    Player p3("Chloe");
    Player p4("David");
    Game game2(p3, p4);
    game2.playAll();

    stringstream out1, out2;
    streambuf *old_cout = cout.rdbuf(out1.rdbuf());

    game1.printStats();
    string game_1_stats = out1.str();
    cout.rdbuf(out2.rdbuf());

    game2.printStats();
    string game_2_stats = out2.str();
    cout.rdbuf(old_cout);
    // The probability of 2 identical games is almost zero
    CHECK(game_1_stats != game_2_stats);
}

// Keep playing until you have a draw at the last turn, 
// The probability is = 0.058823, so we will try 1000 times. 
TEST_CASE("15.Draw is happing at the last turn")
{
    int counter = 0;
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2);
    bool flag = true;
    while (flag && counter++ < 1000)
    {
        p1.~Player();
        new (&p1) Player("Alice");
        p2.~Player();
        new (&p2) Player("Bob");
        game.~Game();
        new (&game) Game(p1, p2);

        while (p1.stacksize() > 1)
        {
            game.playTurn();
            if (p1.stacksize() == 1)
            {
                // Check if the last turn is draw
                game.playTurn();
                stringstream out;
                streambuf *old_cout = cout.rdbuf(out.rdbuf());

                // Call the function
                game.printLastTurn();
                cout.rdbuf(old_cout);
                // Lower case the all string, maybe a student wrote DRaw, or drAW.
                string lowercase_str = out.str();
                transform(lowercase_str.begin(), lowercase_str.end(), lowercase_str.begin(), ::tolower);
                // The last turn was draw
                if (lowercase_str.find("draw") != string::npos)
                {
                    flag = false;
                    CHECK((p1.stacksize() == 0 == p2.stacksize()));
                }
                
            }
        }
    }
    // If the counter reached 550 
    CHECK(!flag);
}

TEST_CASE("16.Winner announced just after game over")
{
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2);
    CHECK_THROWS(game.printWiner());
}

TEST_CASE("17.Check if printLastTurn() prints the same as printLog() after one turn")
{
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2);

    stringstream out1, out2;
    streambuf *old_cout = cout.rdbuf(out1.rdbuf());

    game.printLastTurn();
    string game_lastTurn = out1.str();
    cout.rdbuf(out2.rdbuf());

    game.printLog();
    string game_log = out2.str();
    cout.rdbuf(old_cout);

    // Check that the output contains what we expect
    CHECK(out1.str() == out2.str());
}
