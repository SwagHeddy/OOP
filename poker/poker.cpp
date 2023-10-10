#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>

struct Card {
    std::string suit;
    std::string value;
};

std::vector<Card> generateDeck() {
    std::vector<Card> deck;
    std::string suits[] = { "C", "D", "H", "S" };
    std::string values[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };

    for (const auto& suit : suits) {
        for (const auto& value : values) {
            deck.push_back({ suit, value });
        }
    }

    return deck;
}

std::vector<Card> generatePlayerCards(std::vector<Card>& deck, int numCards) {
    std::vector<Card> playerCards;

    std::random_device rd;
    std::mt19937 generator(rd());

    for (int i = 0; i < numCards; i++) {
        std::uniform_int_distribution<int> distribution(0, deck.size() - 1);
        int randomIndex = distribution(generator);

        playerCards.push_back(deck[randomIndex]);
        deck.erase(deck.begin() + randomIndex);
    }

    return playerCards;
}

int calculatePoints(const std::vector<Card>& playerCards) {
    int points = 0;
    for (const auto& card : playerCards) {
        if (card.value == "A") {
            points += 1;
        }
        else if (card.value == "J" || card.value == "Q" || card.value == "K") {
            points += 10;
        }
        else {
            points += stoi(card.value);
        }
    }
    return points;
}

void printPlayerCards(const std::vector<Card>& playerCards, int playerNumber) {
    std::cout << "Player " << playerNumber << " cards: ";
    for (const auto& card : playerCards) {
        std::cout << card.value << card.suit << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<Card> deck = generateDeck();
    std::vector<Card> player1Cards = generatePlayerCards(deck, 5);
    std::vector<Card> player2Cards = generatePlayerCards(deck, 5);

    printPlayerCards(player1Cards, 1);
    printPlayerCards(player2Cards, 2);

    int player1Points = calculatePoints(player1Cards);
    int player2Points = calculatePoints(player2Cards);

    std::cout << "Player 1 points: " << player1Points << std::endl;
    std::cout << "Player 2 points: " << player2Points << std::endl;

    if (player1Points > player2Points) {
        std::cout << "Player 1 wins!" << std::endl;
    }
    else if (player1Points < player2Points) {
        std::cout << "Player 2 wins!" << std::endl;
    }
    else {
        std::cout << "It's a tie!" << std::endl;
    }

    return 0;
}
