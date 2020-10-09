#include <bits/stdc++.h>
#include "MapLoader.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    string file;
    Map Map1;

    file = "europe.map";
    Map1 = Map_Opener(file);

    file = "france.map";
    Map1 = Map_Opener(file);

    file = "artic.map";
    Map1 = Map_Opener(file);
        return 0;
}
