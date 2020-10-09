#include "Map.h"
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    Map m1;

    Territory t1, t2, t3, t4, t5, t6, t7;
    Continent c1, c2;

    t1.name = "t1";
    t2.name = "t2";
    t3.name = "t3";
    t4.name = "t4";
    t5.name = "t5";
    t6.name = "t6";
    t7.name = "t7";

    c1.name = "c1";
    c2.name = "c2";

    c1.List_of_Countries.push_back(t1);
    c1.List_of_Countries.push_back(t3);
    c1.List_of_Countries.push_back(t5);

    c2.List_of_Countries.push_back(t2);
    c2.List_of_Countries.push_back(t4);
    c2.List_of_Countries.push_back(t6);
    c2.List_of_Countries.push_back(t7);

    m1.List_of_Continents.push_back(c1);
    m1.List_of_Continents.push_back(c2);

    for (int i = 0; i < m1.List_of_Continents.size(); i++)
    {
        cout << "Continent: " << m1.List_of_Continents[i].name << endl;
        cout << "Territories of " << m1.List_of_Continents[i].name << ": ";
        for (int j = 0; j < m1.List_of_Continents[i].List_of_Countries.size(); j++)
        {
            cout << m1.List_of_Continents[i].List_of_Countries[j].name << "  ";
        }

        cout << "\n"
             << endl;
    }

    return 0;
};