#ifndef IO_HPP
define IO_HPP

#include <iostream>
#include <array>
#include <random>
#include <utility>
#include "enums.hpp"
#include "structs.hpp"

std::array<Card, 52> getShuffledDeck();
int getRandomNum(int min, int max);

int getCardValue(Card card);
Rank getRank(Card card);
Suit getSuit(Card card);
std::string stringRank(Rank rank);
std::string stringSuit(Suit suit);

void printCard(const Card &card);
void printDeck(std::array<Card, 52> &deck);
void swapCard(Card &a, Card &b);
void shuffleDeck(std::array<Card, 52> &deck);

bool blackjackWin(Card);
bool playBlackjack(std::array<Card, 52> deck);

void mainLoop();

#endif // IO_HPP
