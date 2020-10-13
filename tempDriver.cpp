#include "player.h"

void printTerritory(list<Territory *> territory)
{
    list<Territory *>::iterator it;
    for (it = territory.begin(); it != territory.end(); ++it)
    {
        Territory *t = *it;
        cout << t->GetName() << endl
             << t->getOwner()->getName() << endl;
    }
}

int main()
{
	// make player with argument name;
	
    Player p1("player 1");
    Player p2("player 2");

    Player p3("player 3");
    
    //using stream insertion operator change player name from player 3 to player three
    
    cin>>p3;
    
    cout<<"after changing"<<endl;
    cout<<p3.getName()<<endl;
    
	system("pause");
    
    // make territory with arguemnt name and owner
    

    Territory territory1("terr:1", &p1);
    Territory territory2("terr:2", &p2);
    Territory territory3("terr:3", &p3);

// make adjacent territors or neighbour

    territory1.AddNeighbour(&territory2);
    territory1.AddNeighbour(&territory3);
    
    
    territory2.AddNeighbour(&territory1);
    territory2.AddNeighbour(&territory3);
    
    territory3.AddNeighbour(&territory1);
    territory3.AddNeighbour(&territory2);
    
    // assign territories to player 
    
    p1.AddTerritory(&territory1);
    p2.AddTerritory(&territory2);
    p3.AddTerritory(&territory3);
    
    // print territory to attack for player 2
    
    printTerritory(p2.ToAttack());
    
    //print territory to defend for player 1
    printTerritory(p1.ToDefend());

    int a;
    cin >> a;
    return 0;
}
