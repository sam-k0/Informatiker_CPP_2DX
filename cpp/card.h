#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED
#include "gms.h"
enum Color
{
    Spade,
    Heart,
    Clover,
    Diamond
};


class Card
{
public:
    gmsprite sprite; // The sprite index (Currently not used)
    Color color;     // The color of the card
    int value;       // The value (1-14?)


    Card(gmsprite spr, Color col, int val)
    {
        sprite = spr;
        color = col;
        value = val;
    }

};

#endif // CARD_H_INCLUDED
