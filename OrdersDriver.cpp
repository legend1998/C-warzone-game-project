

#include "orders.h"

// print territory
void printTerritory(Territory *territory)
{

	cout << territory->getName() << endl
		 << territory->troops << endl;
	if (territory->owner != NULL)
	{
		cout << territory->owner->getname() << endl
			 << endl;
	}
	else
	{
		cout << "no owner" << endl
			 << endl;
	}
}

int main()
{
	//make players
	Player p1("player 1");
	Player p2("player 2");
	Player p3("player 3");

	// make territory
	Territory territory1("territory1");
	Territory territory2("territory2");
	Territory territory3("territory3");

	// add adjacent territory
	territory1.addAdjacentTerritory(&territory2);
	territory1.addAdjacentTerritory(&territory3);

	territory2.addAdjacentTerritory(&territory1);
	territory2.addAdjacentTerritory(&territory3);

	territory3.addAdjacentTerritory(&territory1);
	territory3.addAdjacentTerritory(&territory2);

	//assign territory to the players

	p1.addTerritory(&territory1);

	//	p2.addTerritory(&territory2);

	p3.addTerritory(&territory3);

	//create instance of orderlist
	Orderlist myorders;

	//create order list by the players and print the order

	cout << p1.issueOrder("deploy", &territory1, NULL, &p1, NULL, 5, &myorders) << endl;

	//	cout<<p2.issueOrder("deploy",&territory2,NULL,&p2,NULL,5,&myorders)<<endl;

	cout << p3.issueOrder("deploy", &territory3, NULL, &p3, NULL, 5, &myorders) << endl;

	cout << p1.issueOrder("advance", &territory1, &territory2, &p1, NULL, 5, &myorders) << endl;

	cout << p1.issueOrder("negotiate", NULL, NULL, &p1, &p2, 0, &myorders) << endl;

	cout << p1.issueOrder("bomb", &territory2, NULL, &p1, NULL, 0, &myorders) << endl;

	//	cout<<p2.issueOrder("advance",&territory2,&territory1,&p2,NULL,5,&myorders)<<endl;

	cout << p3.issueOrder("airlift", &territory3, &territory1, &p3, NULL, 2, &myorders) << endl;

	//	cout<<p2.issueOrder("blockade",&territory2,NULL,&p2,NULL,0,&myorders)<<endl;

	//check the statistics

	printTerritory(&territory1);
	printTerritory(&territory2);
	printTerritory(&territory3);

	//execute orders from orderlist

	list<Order *> orders = myorders.getOrders();
	list<Order *>::iterator it;
	for (it = orders.begin(); it != orders.end(); ++it)
	{
		Order *mOrder = *it;
		if (mOrder->validate())
		{
			mOrder->execute();
		}
	}

	//check the result

	printTerritory(&territory1);
	printTerritory(&territory2);
	printTerritory(&territory3);

	// to hold the output in devc++

	int a;
	cin >> a;
	return 0;
}
