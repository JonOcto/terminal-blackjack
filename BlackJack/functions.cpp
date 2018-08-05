#include "io.hpp"

/* TODO:
 * - Make cards "visible" for player to see
 * - Allow for Aces to change value to optimise outcome
 * - Implement "Blackjack draw" victory
 * - Allow for draws
*/


/** void mainLoop()
 * @return void
 * @call getShuffledDeck(), playBlackjack()
 * @desc Game main loop
 */

void mainLoop()
{
    for (std::string choice = "y"; choice == "y";)
    {
        std::array<Card, 52> deck = getShuffledDeck();

        if (playBlackjack(deck))
        {
            std::cout << "You win!\n\n";
        }
        else
        {
            std::cout << "You lose!\n\n";
        }

        choice = "";

        while (!(choice == "y" || choice == "n"))
        {
            std::cout << "Would you like to play again? (y/n): ";
            std::cin >> choice;
            std::cin.ignore(32767, '\n');
        }
    }

    std::cout << "\n";
}

bool playBlackjack(std::array<Card, 52> deck)
{
    // TODO: implement playerHand using a dynamic array
    int turnNum = 1;
    Card playerHand[10];

    Card* cardPtr = &deck[0];

    int playerScore = 0;
    int dealerScore = 0;

    /*
    playerScore += getCardValue(*cardPtr);
    playerHand[turnNum - 1].rank = getRank(*cardPtr);
    playerHand[turnNum - 1].suit = getSuit(*cardPtr);
    ++cardPtr;

    dealerScore += getCardValue(*cardPtr);
    ++cardPtr;
    */

    while (playerScore < 21 && dealerScore < 21)
    {
        playerScore += getCardValue(*cardPtr);
        playerHand[turnNum - 1].rank = getRank(*cardPtr);
        playerHand[turnNum - 1].suit = getSuit(*cardPtr);
        ++cardPtr;

        dealerScore += getCardValue(*cardPtr);
        ++cardPtr;

        std::cout << "Your score: " << playerScore << "\n";
        std::cout << "Dealer score: " << dealerScore << "\n\n";

        std::string choice = "";

        for (int i = 0; i < turnNum; i++)
        {
            std::string rank = stringRank(getRank(playerHand[i]));
            std::string suit = stringSuit(getSuit(playerHand[i]));
            std::cout << i + 1 << ": " << rank << " of " << suit << std::endl;
        }

        std::cout << "\n"; // formatting whitespace

        std::cout << "Hit or stand? (h/s): ";
        std::cin >> choice;
        std::cin.ignore(32767, '\n');

        while (!(choice == "h") && !(choice == "s"))
        {
            std::cout << "Hit or stand? (h/s): ";
            std::cin >> choice;
            std::cin.ignore(32767, '\n');
        }

        if (choice == "h")
        {
            std::cout << "\n"; // formatting whitespace
        }
        else // stand
        {
           while (dealerScore < 21)
           {
               std::cout << "\n"; // formatting whitespace

               dealerScore += getCardValue(*cardPtr++);

               std::cout << "Dealer score: " << dealerScore << "\n";
           }
        }

        ++turnNum;
    }

    if ((dealerScore > 21 && playerScore <= 21) || playerScore > dealerScore)
    {
        if (dealerScore == playerScore)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    else
    {
        return false;
    }
}

std::string stringRank(Rank rank)
{
    switch (rank)
    {
    case ACE:
        return "Ace";
    case TWO:
        return "Two";
    case THREE:
        return "Three";
    case FOUR:
        return "Four";
    case FIVE:
        return "Five";
    case SIX:
        return "Six";
    case SEVEN:
        return "Seven";
    case EIGHT:
        return "Eight";
    case NINE:
        return "Nine";
    case TEN:
        return "Ten";
    case JACK:
        return "Jack";
    case QUEEN:
        return "Queen";
    case KING:
        return "King";
    }
}

std::string stringSuit(Suit suit)
{
    switch (suit)
    {
    case SPADES:
        return "Spades";
    case CLUBS:
        return "Clubs";
    case DIAMONDS:
        return "Diamonds";
    case HEARTS:
        return "Hearts";
    }
}

Rank getRank(Card card)
{
    return card.rank;
}

Suit getSuit(Card card)
{
    return card.suit;
}

// Check if a player has drawn a blackjack
// (NOT SURE IF THIS IS AN ACTUAL RULE)
bool blackjackWin(Card card)
{
    if (card.rank == ACE && card.suit == CLUBS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::array<Card, 52> getShuffledDeck()
{
    std::array<Card, 52> deck;

    int cardIndex = 0; // Tracks card index

    for (int i = 0; i < MAX_SUIT; ++i)
    for (int j = 0; j < MAX_RANK; ++j)
    {
        deck[cardIndex].suit = static_cast<Suit>(i);
        deck[cardIndex].rank = static_cast<Rank>(j);
        ++cardIndex;
    }

    shuffleDeck(deck);

    return deck;
}

void printCard(const Card &card)
{
    switch (card.rank) {
        case TWO:           std::cout << "2"; break;
        case THREE:         std::cout << "3"; break;
        case FOUR:          std::cout << "4"; break;
        case FIVE:          std::cout << "5"; break;
        case SIX:           std::cout << "6"; break;
        case SEVEN:         std::cout << "7"; break;
        case EIGHT:         std::cout << "8"; break;
        case NINE:          std::cout << "9"; break;
        case TEN:           std::cout << "T"; break;
        case JACK:          std::cout << "J"; break;
        case QUEEN:         std::cout << "Q"; break;
        case KING:          std::cout << "K"; break;
        case ACE:           std::cout << "A"; break;
    }

    switch (card.suit) {
        case CLUBS:         std::cout << "C"; break;
        case SPADES:        std::cout << "S"; break;
        case HEARTS:        std::cout << "H"; break;
        case DIAMONDS:      std::cout << "D"; break;
    }

    std::cout << "\n";
}

void printDeck(std::array<Card, 52> &deck)
{
    for (const Card &card : deck) { // for-each loop
        printCard(card);
    }
}

void swapCard(Card &a, Card &b)
{
    std::swap(a, b);
}

// Assumes that srand has already been called with a time seed
int getRandomNum(int min, int max)
{
    std::random_device rd;
    std::mt19937 mersenne(rd());

    int randNum = mersenne() % (max + 1) + min;
    return randNum;
}

int getCardValue(Card card)
{
    switch (card.rank) {
        case TWO:     return 2;
        case THREE:   return 3;
        case FOUR:    return 4;
        case FIVE:    return 5;
        case SIX:     return 6;
        case SEVEN:   return 7;
        case EIGHT:   return 8;
        case NINE:    return 9;
        case TEN:     return 10;
        case JACK:    return 10;
        case QUEEN:   return 10;
        case KING:    return 10;
        case ACE:     return 11;
        default:      exit(-1);
    } // `break;` not required as function returns
}

void shuffleDeck(std::array<Card, 52> &deck)
{
    for (int index = 0; index < 51; ++index) {
        int randIndex = getRandomNum(0, 51);
        swapCard(deck[index], deck[randIndex]);
    }
}
