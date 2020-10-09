#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>

using namespace std;

class Territory;

class Card;

class Order;

class Player
{
    // player's territories

    list<Territory *> territories;
    // player have cards

    list<Card *> cards;

    //player's list of order
    list<Order *> orders;

    string name;

public:
    Player(string name);
    
    void AddCard(Card *card);
    
    void AddTerritory(Territory *territory);
    
    string getName();

    // Player have own territories to defend
    list<Territory *> ToDefend();

    //Player have list of territories to attack
    list<Territory *> ToAttack();

    // player can issue order  using order pointer type
	void IssueOrder(Order *order);
};

class Territory
{
    string name;
    Player *owner;
    int troops;
    list<Territory *> neighbour_territories;

public:
    Territory(string name, Player * owner)
    {
        this->name = name;
        this->owner = owner;
        this->troops = 0;
    }

    Player *getOwner()
    {
        return this->owner;
    }

    string GetName()
    {
        return this->name;
    }

    list<Territory *> Neigbours()
    {
        return this->neighbour_territories;
    }

    void AddNeighbour(Territory *territory)
    {
        list<Territory *>::iterator it;
        for (it = this->neighbour_territories.begin(); it != this->neighbour_territories.end(); ++it)
        {
            Territory *temp = *it;
            if (temp->getOwner()->getName() == territory->getOwner()->getName())
            {
                return;
            }
        }
        this->neighbour_territories.push_back(territory);
    }
};
