#pragma once

class card
{
    friend std::string more_expensive(card, card);
public:
    int health;
    int attack;
    int cost;
};

class logic : public card
{
public:
    std::string status;
    std::string WhoWin(logic object) 
    {
        if (attack > health)
            return object.status = "Not Balanced";
        if (attack <= health)
            return object.status = "Balanced!";
    }
    bool operator<(const logic& object)
    {
        return object.status > status;
    }
    bool operator>(const logic& object)
    {
        return object.status < status;
    }
    bool operator==(const logic& object)
    {
        return object.status == status;
    }
    int NumberofCards()
    {
        return number = rand() % 3;
    }
private:
    int number;
};


std::string more_expensive(card object, card object1)
{
    if (object.attack < object1.attack)
        return " is more expensive! ";
    else
        return " is less expensive! ";
}