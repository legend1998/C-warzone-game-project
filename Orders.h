#include <iostream>
#include <list>
#include <string>
#include <algorithm>

using namespace std;

class Player;
// territory

class Territory;

// class order as base class
class Order
{
public:
    virtual bool validate() = 0;

    virtual void execute() = 0;
};

// deploy as subclass of order class

class Deploy : public Order
{

public:
    int num_of_troops;
    Territory *territory;
    Player *player;

    Deploy(Territory *territory, Player *player, int num);

    bool validate();

    void execute();
};

// advance as subclass of order class

class Advance : public Order
{

public:
    Territory *src, *dest;
    int no_of_troops;
    Player *player;

    Advance(Territory *src, Territory *dest, Player *player, int no_of_troops);

    bool validate();

    void execute();
};

// bomb as subclass of order class

class Bomb : public Order
{

public:
    Territory *dest;
    Player *player;

    Bomb(Territory *dest, Player *player);

    bool validate();

    void execute();
};

// airlift as subclass of order class

class Airlift : public Order
{

public:
    Territory *src, *dest;
    Player *player;
    int no_of_troops;

    Airlift(Territory *src, Territory *dest, Player *player, int no_of_troops);

    bool validate();

    void execute();
};

// Negotiate as subclass of order class

class Negotiate : public Order
{
public:
    Player *me, *negotiate_with;
    Negotiate(Player *me, Player *foy);

    bool validate();

    void execute();
};

// blockade as subclass of order class

class Blockade : public Order
{
public:
    Territory *src;
    Player *player;

    Blockade(Territory *territory, Player *player);

    bool validate();

    void execute();
};

// orderlist class

class Orderlist
{
    //list of orders

    list<Order *> orders;

public:
    // add order to the list
    void addOrder(Order *order)
    {

        this->orders.push_back(order);
    }

    //get list of orders
    list<Order *> getOrders()
    {
        return this->orders;
    }

    //delete given order
    void Delete(Order *order)
    {
        list<Order *>::iterator finditr = find(this->orders.begin(), this->orders.end(), order);
        this->orders.erase(finditr);
    };

    // move order up or down with arguments direction
    void Move(string direction, Order *order)
    {

        // find pointer of order
        list<Order *>::iterator ftr = find(this->orders.begin(), this->orders.end(), order);

        // delete this order from the list
        this->orders.erase(ftr);

        // if orders need to move upward

        if (direction == "up")
        {
            // move pointer to up
            advance(ftr, -1);
        }
        // else means downward
        else
        {
            //increase pointer
            advance(ftr, 1);
        }
        //insert at this pointer
        this->orders.insert(ftr, order);
    };
};

class Territory
{

public:
    string name;
    Player *owner = NULL;
    int troops;
    list<Territory *> adjacent_territory;

    // constructor with no arguments
    Territory()
    {
        this->troops = 0;
    };

    //constructor with arguments name
    Territory(string name)
    {
        this->name = name;
        this->troops = 0;
    }

    //constructor with argument name and pointer player ,set name and player
    Territory(string name, Player *player)
    {
        this->name = name;
        this->owner = player;
        this->troops = 0;
    }
    // increase army with num
    void Addarmy(int num)
    {

        this->troops += num;
    }

    // setarmy with num

    void setArmy(int num)
    {
        if (num > 0)
        {
            this->troops = num;
        }
        else
        {
            this->troops = 0;
        }
    }

    string getName()
    {
        return this->name;
    }

    Player *getOwner()
    {
        return this->owner;
    }

    // set owner of the territory as after attack or defend
    void setOwner(Player *player)
    {
        if (player == NULL)
        {
            this->owner = NULL;
        }
        else
        {
            this->owner = player;
        }
    }

    // add adjacent territory of territory

    void addAdjacentTerritory(Territory *territory)
    {
        this->adjacent_territory.push_back(territory);
    }

    // get list of all adjacent territory of this territory

    list<Territory *> get_adjacent_territory()
    {
        return this->adjacent_territory;
    }

    //check is given territory is adjacent to this territory or not

    bool is_adjacent(Territory *t)
    {
        //iterate through adjacent territories if matches return true else false
        list<Territory *>::iterator it;
        for (it = this->adjacent_territory.begin(); it != this->adjacent_territory.end(); ++it)
        {
            Territory *territory = *it;
            if (t->getName() == territory->getName())
            {
                return true;
            }
        }
        return false;
    }
};

// player for this OrderList

class Player
{

public:
    string name;

    list<Territory *> territories;

    //this data member is for negotiate order
    Player *negotiate_with = NULL;

    Player();

    Player(string name)
    {
        this->name = name;
    }

    list<Territory *> getTerritories()
    {
        return this->territories;
    }
    string getname()
    {
        return this->name;
    }

    // set player to negotiate with to prevent attacks
    void setNegotiate(Player *player)
    {
        this->negotiate_with = player;
    }

    // after turn remove negotiate using this method
    void removeNegotiate()
    {
        this->negotiate_with = NULL;
    }

    void addTerritory(Territory *territory)
    {
        if (territory->getOwner() == NULL)
        {
            territory->setOwner(this);
            cout << "owner set to " << this->getname() << endl;
        }
        this->territories.push_back(territory);
    }

    // this method is responsible for issuing orders
    //it takes orderType arguments which is string type
    // and it can be deploy, advance, bomb,airlift,negotiate
    //every method requires data
    //provide necessory data and remain keep null,
    //as deploy needs ordertype ,territory t1 ,player p1, num,orderlist for

    string issueOrder(string orderType, Territory *t1, Territory *t2, Player *p1, Player *p2, int num, Orderlist *orderlist)
    {

        if (orderType == "deploy")
        {
            // issue deploy order - p1 player deploy num troops in t1 territory
            orderlist->addOrder(new Deploy(t1, p1, num));
            return "deploy order issued.";
        }

        else if (orderType == "advance")
        {
            //issue advance order - p1 player deploy num troops from t1 territory to t2 territory
            orderlist->addOrder(new Advance(t1, t2, p1, num));
            return "advance order issued";
        }

        else if (orderType == "bomb")
        {
            // issue bomb order - p1 player bomb t1 territory
            orderlist->addOrder(new Bomb(t1, p1));
            return "bomb order issued";
        }

        else if (orderType == "airlift")
        {
            //issue airlift order - p1 player airlift num troops from t1 territory to t2 territory
            orderlist->addOrder(new Airlift(t1, t2, p1, num));
            return "airlift order issued";
        }

        else if (orderType == "negotiate")
        {
            //issue negotiate order - player p1 negotiate with p2 player
            orderlist->addOrder(new Negotiate(p1, p2));
            return "negotiate order issued";
        }

        else if (orderType == "blockade")
        { //issue blockade order - player p1 blocks t1 territory
            orderlist->addOrder(new Blockade(t1, p1));
            return "blockade order issued";
        }

        else
        {
            return "invalid order type choose correct order type.";
        }
    }
};
