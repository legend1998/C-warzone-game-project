//  creates player objects

#include "Player.h"

using namespace std;

void show_territories(list<Territory> territories)
{
    list<Territory>::iterator it;
    for (it = territories.begin(); it != territories.end(); ++it)
    {
        cout << (*it).get_name() << " : " << (*it).getOwner()->getName() << endl;
    }
}

int main()
{
    Player player1("p1");
    Player player2("p2");

    list<Territory> territories;

    Territory territory1("terr:1", &player1);
    Territory territory2("terr:2", &player1);
    Territory territory3("terr:3", &player1);
    Territory territory4("terr:4", &player2);
    Territory territory5("terr:5", &player2);
    Territory territory6("terr:6", &player2);

    territory1.add_adjacent_country(territory2);
    territory1.add_adjacent_country(territory3);
    territory1.add_adjacent_country(territory4);
    territory1.add_adjacent_country(territory5);

    territory2.add_adjacent_country(territory1);
    territory2.add_adjacent_country(territory3);
    territory2.add_adjacent_country(territory4);

    territory5.add_adjacent_country(territory4);
    territory5.add_adjacent_country(territory1);
    territory5.add_adjacent_country(territory3);
    territory5.add_adjacent_country(territory6);

    territory4.add_adjacent_country(territory1);
    territory4.add_adjacent_country(territory2);
    territory4.add_adjacent_country(territory5);
    territory4.add_adjacent_country(territory6);

    territory3.add_adjacent_country(territory1);
    territory3.add_adjacent_country(territory2);
    territory3.add_adjacent_country(territory5);

    territory6.add_adjacent_country(territory4);
    territory6.add_adjacent_country(territory5);

    player1.addTerritory(territory1);
    player1.addTerritory(territory2);
    player1.addTerritory(territory3);
    player2.addTerritory(territory4);
    player2.addTerritory(territory5);
    player2.addTerritory(territory6);

    list<Territory> player1_owned = player1.toDefend();
    list<Territory> player2_owned = player2.toDefend();

    list<Territory> player1_attack = player1.toAttack();
    list<Territory> player2_attack = player2.toAttack();

    cout << "Territories owned by player 1" << endl;
    show_territories(player1_owned);

    cout << "Territories to attack by player 1" << endl;
    show_territories(player1_attack);

    cout << "Territories owned by player 2" << endl;
    show_territories(player2_owned);

    cout << "Territories to attack by player 2" << endl;
    show_territories(player2_attack);
}
