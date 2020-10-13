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
    
    // class having copy constructor 

    Player(const Player &player);
    
    //class having stream insertion operator
    
    friend istream & operator >> (istream &in ,Player &player);

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


//Player class stream insertion operator
istream  & operator >>(istream &in ,Player &player){
	cout<<"enter player name to create player";
	in>>player.name;
}


class Territory
{
    string name;
    Player *owner;
    int troops;
    list<Territory *> neighbour_territories;

public:
    Territory(string name, Player *owner)
    {
        this->name = name;
        this->owner = owner;
        this->troops = 0;
    }
    
    
    // copy constructor 
    Territory(const Territory &t){
    	this->name = t.name;
    	this->troops = t.troops;
    	this->owner = t.owner;
	}
    
    // stream insertion operator for territory class
    friend istream & operator >>(istream &in, Territory &t);

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

// stream insertion operator for territory class
istream & operator >>(istream &in, Territory &t){
	cout<<"enter territory name"<<endl;
	cin>>t.name;
	cout<<"enter troops"<<endl;
	cin>>t.troops;
	
}
