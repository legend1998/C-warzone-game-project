#include "temp.h"

// Player class constructor  with arguments name

Player::Player(string name)
{
    this->name = name;
}
// Player addcard functioin with card pointer arguments

void Player::AddCard(Card *card)
{
    this->cards.push_back(card);
}
// returns player's name

string Player::getName()
{
    return this->name;
}

// add territory to the player's list of territory

void Player::AddTerritory(Territory *territory){
    this->territories.push_back(territory);
	}

// return that neighbour territory which don't have current player;

list<Territory *> Player::ToAttack()
{
    // assume opposite territories are attacking territorries now is empty

    list<Territory *> opposite_territory;

    list<Territory *>::iterator it;

    // iterate through neighbour territories of player's territories and
    // if any adjacent territory is not in the list of player's territory
    // put it in the opposite territory

    for (it = this->territories.begin(); it != this->territories.end(); ++it)
    {
        Territory *mt = *it;

        list<Territory *> neighbours = mt->Neigbours();

        list<Territory *>::iterator ot;
        for (ot = neighbours.begin(); ot != neighbours.end(); ++ot)
        {

            Territory *at = *ot;
            if (mt->getOwner()->getName() != at->getOwner()->getName())
            {
                opposite_territory.push_back(at);
            }
        }
    }

    return opposite_territory;
}

// player has to defend it's own territories

list<Territory *> Player::ToDefend()
{

    return this->territories;
}

// any order generated by the player put it inside player's list of orders
void Player::IssueOrder(Order *order)
{
    this->orders.push_back(order);
}
