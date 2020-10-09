#include "Orders.h"

// deploy no_of_troops in selected territory

Deploy::Deploy(Territory *territory, Player *player, int num)
{
    this->num_of_troops = num;
    this->player = player;
    this->territory = territory;
}

// validate if this territory belongs to the player or not

bool Deploy::validate()
{
    if (this->territory->owner->getname() == this->player->getname())
    {
        return true;
    }
    else
    {
        return false;
    }
};

void Deploy::execute()
{
    this->territory->Addarmy(this->num_of_troops);

    //output of execution
    cout << "deploy " << this->num_of_troops << " in " << this->territory->getName() << " by " << this->player->getname() << endl;
};

// advance number of troops from one place to another place
Advance::Advance(Territory *src, Territory *dest, Player *player, int no_of_troops)
{
    this->no_of_troops = no_of_troops;
    this->src = src;
    this->dest = dest;
    this->player = player;
}

bool Advance::validate()
{ //return false if both territories are same
    if (this->src->getName() == this->dest->getName())
    {
        return false;
    }
    //return false if territories are not adjacent
    else if (!src->is_adjacent(this->dest))
    {
        return false;
    }
    //return false if player is negotiated with another player
    else if (this->player->negotiate_with != NULL && this->player->negotiate_with == this->dest->getOwner())
    {
        return false;
    }
    else
    {
        return true;
    }
};

void Advance::execute()
{
    //check if territory has owner or not if not then attack
    if (this->dest->getOwner() != NULL)
    {
        //if territory belongs to owner then transfer troops
        if (this->src->owner->getname() == this->dest->owner->getname())
        {
            this->src->setArmy(this->src->troops - this->no_of_troops);
            this->dest->Addarmy(this->no_of_troops);
        }
    }
    else
    {
        //if our army is greather than enemy then we win an take over the territory else we loose troops
        if (this->no_of_troops > this->dest->troops)
        {
            //own territory
            this->src->setArmy(this->src->troops - this->no_of_troops);
            this->dest->setArmy(this->no_of_troops - this->dest->troops);
            this->dest->setOwner(this->src->getOwner());
        }
        else
        { //loose troops
            this->src->setArmy(this->src->troops - this->no_of_troops);
            this->dest->setArmy(this->dest->troops - this->no_of_troops);
        }
    };
    //output of execution
    cout << "advanced/attacked " << this->dest->getName() << " with " << this->no_of_troops << " troops by " << this->player->getname() << endl;
}

// Bomb operation

Bomb::Bomb(Territory *dest, Player *player)
{
    this->dest = dest;
    this->player = player;
}

bool Bomb::validate()
{
    //if territory has owner or not
    if (this->dest->getOwner() != NULL)
    {
        // return false if owner is same
        if (this->dest->getOwner()->getname() == player->getname())
        {
            return false;
        }
    }
    // return false if player is negotiated with another player
    else if (this->player->negotiate_with != NULL && this->player->negotiate_with == this->dest->getOwner())
    {

        return false;
    }
    //check territory is adjacent or not
    list<Territory *> players_territory;
    players_territory = this->player->getTerritories();

    list<Territory *>::iterator it;
    for (it = players_territory.begin(); it != players_territory.end(); ++it)
    {
        Territory *territory = *it;
        list<Territory *> temp = territory->get_adjacent_territory();

        list<Territory *>::iterator nt;
        for (nt = temp.begin(); nt != temp.end(); ++nt)
        {
            Territory *newterritory = *nt;
            if (this->dest->getName() == newterritory->getName())
            {
                // if adjacent return true else false
                return true;
            }
        }
    }
    return false;
}

void Bomb::execute()
{
    this->dest->setArmy(this->dest->troops / 2);

    //output of execution
    cout << "bombed " << this->dest->getName() << " by " << this->player->getname() << endl;
}

//airlift operation
Airlift::Airlift(Territory *src, Territory *dest, Player *player, int no_of_troops)
{
    this->player = player;
    this->src = src;
    this->dest = dest;
    this->no_of_troops = no_of_troops;
}

bool Airlift::validate()
{
    //return false if both territory are same
    if (this->src->getName() == this->dest->getName())
    {
        return false;
    }
    else
    {
        return true;
    }
}

void Airlift::execute()
{
    //check if territory has owner or not if not then attack if yes then check for owner is me or not
    if (this->src->owner->getname() == this->dest->owner->getname())
    {
        this->src->setArmy(this->src->troops - this->no_of_troops);
        this->dest->Addarmy(this->no_of_troops);
    }
    else
    { //attack if we have troops greater than opposition else loose troops

        if (this->no_of_troops > this->dest->troops)
        {
            //we win and take over the territory
            this->src->setArmy(this->src->troops - this->no_of_troops);
            this->dest->setArmy(this->no_of_troops - this->dest->troops);
            this->dest->setOwner(this->src->getOwner());
        }
        else
        { //loose troops
            this->src->setArmy(this->src->troops - this->no_of_troops);
            this->dest->setArmy(this->dest->troops - this->no_of_troops);
        }
    }
    //output of execution
    cout << "airlift " << this->no_of_troops << " troops to " << this->dest->getName() << " by " << this->player->getname() << endl;
}

// negotiate operation
Negotiate::Negotiate(Player *me, Player *foy)
{
    this->me = me;
    this->negotiate_with = foy;
}

bool Negotiate::validate()
{
    //return false if both player are same
    if (this->me->getname() == this->negotiate_with->getname())
    {
        return false;
    }
    else
        return true;
}

void Negotiate::execute()
{
    this->negotiate_with->setNegotiate(this->me);

    //output of execution
    cout << this->me->getname() << " negotiated with " << this->negotiate_with->getname() << "for this turn" << endl;
}

// blockade operation

Blockade::Blockade(Territory *territory, Player *player)
{
    this->src = territory;
    this->player = player;
}

bool Blockade::validate()
{
    //return false if the territory not belongs to me
    if (this->src->getOwner()->getname() != this->player->getname())
    {
        return false;
    }
    else
    {
        return true;
    }
}

void Blockade::execute()
{
    this->src->setArmy(this->src->troops * 3);
    this->src->setOwner(NULL);

    //output of execution

    cout << this->src->getName() << " is blocked by " << this->player->getname() << endl;
}
