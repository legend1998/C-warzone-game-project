#include "Player.h"

Player::Player(string name)
{
    this->playerName = name;
}

void Player::addCard(Card card)
{
    cards.push_back(card);
}

void Player::addTerritory(Territory territory)
{
    owned_territories.push_back(territory);
}

string Player::getName()
{
    return this->playerName;
}

// arbitrary returns a list of territories that are to be defended
list<Territory> Player::toDefend()
{
    return owned_territories;
}

// arbitrary returns a list of territories that are to be attacked
list<Territory> Player::toAttack()
{
    // Return UnOwned Territory
    list<Territory> rt;

    typename list<Territory>::iterator it;
    for (it = owned_territories.begin(); it != owned_territories.end(); ++it)
    {
        list<Territory> adjacentCountries = it->get_adjacent_territories();

        typename list<Territory>::iterator adja_it;
        for (adja_it = adjacentCountries.begin(); adja_it != adjacentCountries.end(); ++adja_it)
        {
            bool found = false;
            list<Territory>::iterator to_attack_it;

            for (to_attack_it = rt.begin(); to_attack_it != rt.end(); ++to_attack_it)
            {
                if ((*adja_it).is_match(*to_attack_it) == true)
                {
                    found = true;
                }
            }

            if (found == false)
            {
                Territory tmp = *adja_it;
                if (tmp.getOwner() != this)
                {
                    rt.push_back(tmp);
                }
            }
        }
    }

    return rt;
}

// creates an Order object and puts it in the player’s list of orders
void Player::issueOrder(Order order)
{
    orders.push_back(order); // Push at last
}