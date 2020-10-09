#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>

using namespace std;

class Territory;

class Card
{
};

class Order
{
};

class Player
{
    // owns territories
    list<Territory> owned_territories;

    // owns a hand of Cards
    list<Card> cards;

    // own list of orders to be created and executed in the current turn
    list<Order> orders;

    string playerName;

public:
    Player(string name);
    void addCard(Card card);
    void addTerritory(Territory territory);
    string getName();

    // arbitrary returns a list of territories that are to be defended
    list<Territory> toDefend();

    // arbitrary returns a list of territories that are to be attacked
    list<Territory> toAttack();

    // creates an Order object and puts it in the player’s list of orders
    void issueOrder(Order order);
};

// owns a collection of territories

class Territory
{
    string name;
    Player *owner;
    int armies;
    list<Territory> adjacent_territories;

public:
    Territory(string name, Player *owner)
    {
        this->name = name;
        this->owner = owner;
    }

    Player *getOwner()
    {
        return owner;
    }

    string get_name()
    {
        return name;
    }

    list<Territory> get_adjacent_territories()
    {
        return adjacent_territories;
    }

    bool is_match(Territory tmp)
    {

        if (!((tmp.get_name().compare(this->get_name())) == 0))
        {
            return false;
        }

        if ((tmp.getOwner()->getName().compare(this->getOwner()->getName()) == 0))
        {
            return true;
        }

        return false;
    }

    void add_adjacent_country(Territory territory)
    {
        list<Territory>::iterator it;
        for (it = adjacent_territories.begin(); it != adjacent_territories.end(); ++it)
        {
            if (territory.is_match(*it) == true)
            {
                return;
            }
        }
        adjacent_territories.push_back(territory);
    }
};
