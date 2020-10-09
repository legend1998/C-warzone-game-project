#include<bits/stdc++.h> 
#include "Map.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


Map Map_Opener(string file)
{   
    Map NEW_MAP;
    Map *pNEW_MAP = &NEW_MAP;

    int Number_Of_Continents = 0;
    int Number_Of_Territories = 0;
    int Index_Of_Borders = 0;

    bool Counting_Continents = false;
    bool Counting_Countries = false;
    bool Calculating_Borders = false;
    bool NOT_VALID = false;

    vector <vector <int> > Borders_Connection;
    vector <string> Country_Names;

    string myText;

    ifstream MyReadFile(file);



  // Use a while loop together with the getline() function to read the file line by line
    while(getline (MyReadFile, myText)) 
    {

        //Searching for keyword "continents" and copy the names of continent into the Map
        //When "continents" is first seen
        if(myText.find("[continents]") != std::string::npos)
        {
            Counting_Continents = true;
        }
        //Reaches the end of the "continents" section
        else if(myText.empty() && Counting_Continents == true)
        {
            Counting_Continents = false;
        }
        //After seeing "continents" and before reaching the end of the section
        else if(Counting_Continents == true)
        {
            int position;
            string temp;
            Continent new_continent;

            temp = myText;
            position = myText.find(' ', 0);
            myText = myText.substr(position + 1);
            temp = temp.substr(0, position);

            new_continent.name = temp;
            pNEW_MAP -> pList_of_Continents -> push_back(new_continent);
            Number_Of_Continents = Number_Of_Continents + 1;
        }
        ///////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////

        //Searching for keyword "countries" and copy the names of country into the Map
        //When "countries" is first seen
        if(myText.find("[countries]") != std::string::npos)
        {
            Counting_Countries = true;
        }
        //Reaches the end of the "countries" section
        else if(myText.empty() && Counting_Countries == true)
        {
            Counting_Countries = false;
        }
        //After seeing "countries" and before reaching the end of the section
        else if(Counting_Countries == true)
        {
            int position;
            int index = -1;
            string temp;
            string country;
            Territory new_territory;


            //A for-loop to check different information of a line
            for(int i = 0; i < 3; i++)
            {
                temp = myText;
                position = myText.find(' ', 0);
                myText = myText.substr(position + 1);
                temp = temp.substr(0, position);

                //copy the name of the country
                if(i == 1)
                {
                    new_territory.name = temp;
                    Country_Names.push_back(temp);
                }   
                //get the index of the country
                if(i == 2)
                {
                    index = index + stoi(temp);
                }
            }

          
            
            pNEW_MAP -> List_of_Continents[index].List_of_Countries.push_back(new_territory) ;
            Number_Of_Territories = Number_Of_Territories + 1;
        }
        ///////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////
        
        //Searching for keyword "borders" and build the connections between them
        //When "borders" is first seen
        if(myText.find("[borders]") != std::string::npos)
        {
            Calculating_Borders = true;
           
        }
        //Reaches the end of the section
        else if(myText.empty() && Calculating_Borders == true)
        {
            Calculating_Borders = false;
        }
        //After seeing "borders" and before reaching the end of the section
        else if(Calculating_Borders == true)
        {
        
            vector <string> arr;
            int position;
            string temp;
            string temp2;
            int i = 0;
        //loop through diffrenet parts of the line
        while ( myText.find(" ") != std::string::npos)
        {
            temp = myText;
           
            position = myText.find(' ', 0);
            myText = myText.substr(position + 1);
            temp = temp.substr(0, position);
              
            if(i != 0)
            {  
                temp2 = Country_Names[stoi(temp)];
                arr.push_back(Country_Names[stoi(temp) - 1]);

            }
        
            i++;

            }

            temp = myText;
            position = myText.find(' ', 0);
            myText = myText.substr(position + 1);
            temp = temp.substr(0, position);

            arr.push_back(Country_Names[stoi(temp) - 1]);

            pNEW_MAP -> Adj_of_Countries.push_back(arr);
        }
    }

  pNEW_MAP -> Countries_by_Index = Country_Names;
  
  NOT_VALID = validate(pNEW_MAP);

  if(NOT_VALID == true)
  {
    pNEW_MAP -> Adj_of_Countries.clear();
    pNEW_MAP -> List_of_Continents.clear();
    pNEW_MAP -> Countries_by_Index.clear();  
  }

  MyReadFile.close();
  return *pNEW_MAP;
};

void PrintMap(Map m)
{

    cout << "\n" << endl;
    cout << "\n" << endl;

    for(int i = 0; i < m.List_of_Continents.size(); i++)
    {
        cout << "Continent: " <<m.List_of_Continents[i].name << endl;
        cout << "Territories in " << m.List_of_Continents[i].name << ":  ";

        for(int j = 0; j < m.List_of_Continents[i].List_of_Countries.size(); j++)
        {
            cout << m.List_of_Continents[i].List_of_Countries[j].name << "  ";
        }

        cout << "\n" << endl;
    } 

    for(int i = 0; i < m.Adj_of_Countries.size(); i++)
    {
        cout << "Connected Countries of " << m.Countries_by_Index[i]  << ":  " ;

        for(int j = 0; j < m.Adj_of_Countries[i].size(); j++)
        {
            cout << m.Adj_of_Countries[i][j] << "  ";
        }

        cout << "\n" << endl;
    }


};

