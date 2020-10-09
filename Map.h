#include<bits/stdc++.h> 
#include <iostream>
#include <fstream>
#include <string>

using namespace std; 
  
// A utility function to add an edge in an 
// undirected graph. 

struct Territory
{
    string name;
    string owner;
    int armies;
};

struct Continent
{
    string name;
    vector<Territory> List_of_Countries;
    vector<Territory>* pList_of_Countries = &List_of_Countries;
};

struct Map
{
    vector <Continent>  List_of_Continents;
    vector <Continent> * pList_of_Continents = &List_of_Continents;
    vector <vector<string> > Adj_of_Countries;
    vector <string> Countries_by_Index;
};

bool validate(Map *check)
{
    check;
    string cont;
    string terr;
    string bor;
    bool NOT_VALID = false;
    
    //Checking if there are duplicate Continent 
    for(int i = 0; i < check -> List_of_Continents.size(); i++)
    {
        cont = check -> List_of_Continents[i].name;

        for(int j = i + 1; j < check -> List_of_Continents.size(); j++)
        {
            if(check -> List_of_Continents[j].name == cont)
            {
                NOT_VALID = true;
            }       
        }
    }
    ////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////

    //Checking if there are duplicate Countries(Are they belong to one continent) 
    for(int i = 0; i < check ->Countries_by_Index.size(); i++)
    {
        terr = check -> Countries_by_Index[i];

       for(int j = i + 1; j < check -> Countries_by_Index.size(); j++)
       {
           if(check -> Countries_by_Index[j] == terr)
           {
                NOT_VALID = true;
           }
       }
    }
    ////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////

    //Checking if there are Countries that are not connected to anything 
    for(int i = 0; i < check -> Adj_of_Countries.size(); i++)
    {
        bor = check -> Countries_by_Index[i];
        if(check -> Adj_of_Countries[i][0] == bor)
        {
                    NOT_VALID = true;
        }

    }
    ////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////

    if(NOT_VALID == true)
    {
        cout << "THE FILE IS INVALID" << endl;
    }
    else
    {
        cout << "THE FILE IS VALID" << endl;
    }
    
    return NOT_VALID;

};
  
