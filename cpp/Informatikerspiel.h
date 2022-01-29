#ifndef INFORMATIKERSPIEL_H_INCLUDED
#define INFORMATIKERSPIEL_H_INCLUDED
#include <vector>
#include <algorithm>
#include "card.h"

enum PlayerPrediction
{
    Lower,
    Higher
};

class Informatikerspiel
{
private:
    std::vector<Card*> cardStaple; // Holds all cards on staple
    std::vector<Card*> usedCards;
    Card* enemyCard = nullptr;
    Card* playerCard = nullptr;
    PlayerPrediction prediction;

public:
    Informatikerspiel()
    {

    }

    void init() // Fill arrays
    {
        // Hearts
        for(int i = 2; i < 14; i++)
        {
            cardStaple.push_back(new Card(-1, Color::Heart, i));
        }

        // Spades
        for(int i = 2; i < 14; i++)
        {
            cardStaple.push_back(new Card(-1, Color::Spade, i));
        }

        // Clover
        for(int i = 2; i < 14; i++)
        {
            cardStaple.push_back(new Card(-1, Color::Clover, i));
        }

        // Diamond
        for(int i = 2; i < 14; i++)
        {
            cardStaple.push_back(new Card(-1, Color::Diamond, i));
        }

        // Shuffle the cards
        std::random_shuffle(cardStaple.begin(), cardStaple.end());
    }

    void clean() // cleans all cards from memory
    {
        for(auto card : usedCards)
        {
            cardStaple.push_back(card);
        }
        usedCards.clear();

        enemyCard = nullptr;
        playerCard = nullptr;
    }

    bool giveCards() // Give the two players the cards / Returns false when empty
    {

        if(cardStaple.empty()) // Return false on empty
        {
            return false;
        }

        enemyCard = cardStaple.front(); // set enemy card
        cardStaple.erase(cardStaple.begin());
        usedCards.push_back(enemyCard);
        playerCard = cardStaple.front(); // set player card
        cardStaple.erase(cardStaple.begin());
        usedCards.push_back(playerCard);
        return true;
    }


    void setPlayerPrediction(int pred) // 0 = lower, 1 = higher
    {
        if((bool)pred)
        {
            prediction = PlayerPrediction::Higher;
        }
        else
        {
            prediction = PlayerPrediction::Lower;
        }
    }

    bool compareCards() // returns true if player won, false if lost
    {
        if(enemyCard->value == playerCard->value) // Same cards
        {
            return true;
        }

        return (bool(enemyCard->value < playerCard->value) == (bool)prediction);
    }

    Card* getEnemyCard()
    {
        return enemyCard;
    }

    Card* getPlayerCard()
    {
        return playerCard;
    }
};


#endif // INFORMATIKERSPIEL_H_INCLUDED
