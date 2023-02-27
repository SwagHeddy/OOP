#include <iostream>
#include <string>
#include <ctime>
#include "card.h"

int main()
{
    srand(time(0));
    logic card;
    card.health = 5;
    std::cout << "card health is: " << card.health << std::endl;
    card.attack = 5;
    std::cout << "card attack is: " << card.attack << std::endl;
    card.cost = 5;
    std::cout << "card cost is:  " << card.cost << std::endl;
    card.status = card.WhoWin(card);
    std::cout << "status is " << card.status << std::endl;
    std::cout << card.NumberofCards() << " cards in this collection" << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    logic card2;
    card2.health = 6;
    std::cout << "card health is: " << card2.health << std::endl;
    card2.attack = 6;
    std::cout << "card attack is: " << card2.attack << std::endl;
    card2.cost = 6;
    std::cout << "card cost is:  " << card2.cost << std::endl;
    std::cout << card2.NumberofCards() << " cards in this collection" << std::endl;
    card2.status = card2.WhoWin(card2);
    std::cout << "status is " << card.status << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    if (card < card2)
    {
        std::cout << "second card is stronger than first card" << std::endl;
    }
    if (card > card2)
    {
        std::cout << "first card is stronger than second card" << std::endl;
    }
    if (card == card2)
    {
        std::cout << "the parameters of cards is similar" << std::endl;
    }
    std::cout << "Is " << card.cost << " more expensive than " << card2.cost << "?" << std::endl;
    std::cout << card.cost << more_expensive(card, card2) << card2.cost << std::endl;

}
