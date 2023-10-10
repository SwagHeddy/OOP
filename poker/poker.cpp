#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <random>

// Определяем класс карты
class Card {
public:
    enum Rank { ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };
    enum Suit { CLUBS, DIAMONDS, HEARTS, SPADES };

    Card(Rank rank = ACE, Suit suit = SPADES) : m_Rank(rank), m_Suit(suit) {}

    int getValue() const {
        return m_Rank;
    }

    void display() const {
        std::string rankStr = "";
        std::string suitStr = "";

        switch (m_Rank) {
        case ACE:
            rankStr = "A";
            break;
        case JACK:
            rankStr = "J";
            break;
        case QUEEN:
            rankStr = "Q";
            break;
        case KING:
            rankStr = "K";
            break;
        default:
            rankStr = std::to_string(m_Rank);
            break;
        }

        switch (m_Suit) {
        case CLUBS:
            suitStr = "C";
            break;
        case DIAMONDS:
            suitStr = "D";
            break;
        case HEARTS:
            suitStr = "H";
            break;
        case SPADES:
            suitStr = "S";
            break;
        }

        std::cout << rankStr << suitStr << " ";
    }

private:
    Rank m_Rank;
    Suit m_Suit;
};

// Определяем класс колоды карт
class Deck {
public:
    Deck() {
        for (int suit = Card::CLUBS; suit <= Card::SPADES; ++suit) {
            for (int rank = Card::ACE; rank <= Card::KING; ++rank) {
                m_Cards.push_back(Card(static_cast<Card::Rank>(rank), static_cast<Card::Suit>(suit)));
            }
        }
    }

    void generateDeck() {
        std::random_device rd;
        std::mt19937 eng(rd());
        std::shuffle(m_Cards.begin(), m_Cards.end(), eng);
    }

    const Card& draw() {
        // Удаление карты из колоды
        const Card& card = m_Cards.back();
        m_Cards.pop_back();

        return card;
    }

    class iterator : public std::iterator<std::input_iterator_tag, Card> {
    public:
        iterator(std::vector<Card>::iterator it) : m_Iterator(it) {}

        iterator operator+(int n) const {
            iterator temp = *this;
            for (int i = 0; i < n; i++) {
                ++temp; // Перемещаем итератор вперед
            }
            return temp;
        }

        iterator& operator++() {
            ++m_Iterator;
            return *this;
        }

        bool operator!=(const iterator& other) const {
            return m_Iterator != other.m_Iterator;
        }

        const Card& operator*() const {
            return *m_Iterator;
        }

    private:
        std::vector<Card>::iterator m_Iterator;
    };

    iterator begin() {
        return iterator(m_Cards.begin());
    }

    iterator end() {
        return iterator(m_Cards.end());
    }

private:
    std::vector<Card> m_Cards;
};

// Определяем класс адаптера для итератора колоды карт
class DeckIteratorAdapter {
public:
    DeckIteratorAdapter(Deck::iterator iterator) : m_Iterator(iterator) {}

    DeckIteratorAdapter& operator++() {
        ++m_Iterator;
        return *this;
    }

    bool operator!=(const DeckIteratorAdapter& other) const {
        return m_Iterator != other.m_Iterator;
    }

    const Card& operator*() const {
        return *m_Iterator;
    }

private:
    Deck::iterator m_Iterator;
};


// Функция подсчета очков игрока
int calculatePoints(const std::vector<Card>& hand) {
    int points = 0;
    std::map<int, int> rankCounts;

    for (const Card& card : hand) {
        rankCounts[card.getValue()]++;
    }

    for (const auto& count : rankCounts) {
        if (count.second >= 2) { // Изменить условие на count.second >= 2
            points += count.second; // Добавить количество карт к points
        }
    }

    return points;
}

// Функция объявления победителя
void determineWinner(int player1Points, int player2Points) {
    if (player1Points > player2Points) {
        std::cout << "Player 1 wins!" << std::endl;
    }
    else if (player2Points > player1Points) {
        std::cout << "Player 2 wins!" << std::endl;
    }
    else {
        std::cout << "It's a tie!" << std::endl;
    }
}

// Основная функция игры
void playPoker() {
    Deck deck;
    deck.generateDeck();

    int handSize = 5;

    std::vector<Card> player1Hand;
    std::vector<Card> player2Hand;

    std::cout << "Player 1 cards: ";
    for (DeckIteratorAdapter it = deck.begin(); it != deck.begin() + handSize; ++it) {
        const Card& card = *it;
        card.display();
        player1Hand.push_back(card);
    }
    std::cout << std::endl;

    std::cout << "Player 2 cards: ";
    for (DeckIteratorAdapter it = deck.begin() + handSize; it != deck.begin() + (2 * handSize); ++it) {
        const Card& card = *it;
        card.display();
        player2Hand.push_back(card);
    }
    std::cout << std::endl;

    int player1Points = calculatePoints(player1Hand);
    int player2Points = calculatePoints(player2Hand);

    std::cout << "Player 1 points: " << player1Points << std::endl;
    std::cout << "Player 2 points: " << player2Points << std::endl;

    determineWinner(player1Points, player2Points);
}

int main() {
    playPoker();
    system("pause");
}
