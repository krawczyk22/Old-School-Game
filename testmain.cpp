#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <algorithm>
#include "testclass.h"

#include <stdio.h>
#include <sqlite3.h>
using namespace std;

//g++ --std=c++14 direction.cpp -o direction
int checkingDirectionForwards(int x,int y, int randomnumberX, int randomnumberY,int yrange)
{
    if (y == yrange || (x == randomnumberX && y == randomnumberY))
    {
    cout << "You cannot go forwards, try another direction" << endl;
    }
    if (y < yrange)
    {
        if (x != randomnumberX || y != randomnumberY)
        {
        y=y+1;
        }
        cout << "You have moved forwards" << endl;
    }
    return y;
}
int checkingDirectionBackwards(int x,int y, int randomnumberX, int randomnumberY,int yrange)
{
    if (y == 0 || (x == randomnumberX && y == randomnumberY))
    {
    cout << "You cannot go backwards, try another direction" << endl;
    }
    if (y > 0)
    {
        if (x != randomnumberX || y != randomnumberY)
        {
        y=y-1;
        }
        cout << "You have moved backwards" << endl;
    }
    return y;
}
int checkingDirectionRight(int x,int y, int randomnumberX, int randomnumberY,int xrange)
{
    if (x == xrange || (x == randomnumberX && y == randomnumberY))
    {
    cout << "You cannot go right, try another direction" << endl;
    }
    if (x < xrange)
    {
        if (x != randomnumberX || y != randomnumberY)
        {
        x=x+1;
        }
        cout << "You have moved right"<< endl;
    }
    return x;
}

int checkingDirectionLeft(int x,int y, int randomnumberX, int randomnumberY,int xrange)
{
    if (x == 0 || (x == randomnumberX && y == randomnumberY))
    {
    cout << "You cannot go left, try another direction" <<  endl;
    }
    if (x > 0)
    {
        if (x != randomnumberX || y != randomnumberY)
        {
        x=x-1;      
        }
        cout << "You have moved left" << endl;
    }
    return x;
}
/*
int roomEnter(int x, int y)
{
    int monsterNum = rand() % 100;
    if (monsterNum % 2 == 0)
    {
        int monsterChoose = rand() % 10; //number of monsters

        string sqliteFile = "monsterInfo.sqlite";

    try
    {
        sqlite::sqlite db( sqliteFile );
        auto cur = db.get_statement(); 

        cur->set_sql( "select * "
                      "from monsters "
                      "where monsterID = ?" );
        cur->prepare();
        cur->bind( 1, monsterChoose );
        
while( cur->step() ) // loop over results 
{
  cout << cur->get_int(0) << " " << cur->get_text(1) << endl;
}

      
    }
    catch( sqlite::exception e )      // catch all sql issues
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    }
    cout << "You enter the room and find " << endl;
}

int saveFunction(//int ID, string name, string gender, string character_class
)
{
    //INSERT INTO hero 
    //VALUES (ID, name, gender, character_class);
}*/
int main()
{
    
    int x = 0;
    int y = 0;
    
    int xrange = 10;
    int yrange = 10;
    
    vector <string> visitedList{};
    srand (time(NULL));
    int randomnumberX = rand() % 10; 
    int ID = rand() % 9999;
    
    

    int randomnumberY = rand() % 10; 



    
    
    while (!(x == 2 && y == 2))
    {
    string direction = "";
    cout << "Which direction would you like to go?: " ;
    cin >> direction;
    transform(direction.begin(), direction.end(), direction.begin(), ::tolower);
    string stringX = to_string(x);
    string stringY = to_string(y);
    string xy = stringX + stringY;
        
    vector<string> forwardList ={"forwards","forward","north","ahead","onwards"};
    if (find(forwardList.begin(), forwardList.end(), direction) != forwardList.end())
    {
        y = checkingDirectionForwards(x,y, randomnumberX, randomnumberY, yrange); // call a checking function to see if you can move that way, then run the forwards function.
        if (!(find(visitedList.begin(), visitedList.end(), xy) != visitedList.end()))
        {
            visitedList.push_back(xy);
        }
        //for(int i=0; i<visitedList.size(); ++i)
        //cout << visitedList[i] << ' ';
    }
    vector<string> backwardsList ={"backwards","backward","south","down","downward","downwards","back"};
    if (find(backwardsList.begin(), backwardsList.end(), direction) != backwardsList.end())
    {
        
        y = checkingDirectionBackwards(x,y, randomnumberX, randomnumberY, yrange); 
                if (!(find(visitedList.begin(), visitedList.end(), xy) != visitedList.end()))
        {
            visitedList.push_back(xy);
        }
    }
    vector<string> rightList ={"right","east"};
    if (find(rightList.begin(), rightList.end(), direction) != rightList.end())
    {
        x = checkingDirectionRight(x,y, randomnumberX, randomnumberY, xrange); 
                if (!(find(visitedList.begin(), visitedList.end(), xy) != visitedList.end()))
        {
            visitedList.push_back(xy);
        }
    }
    vector<string> leftList ={"left","west"};
    if (find(leftList.begin(), leftList.end(), direction) != leftList.end())
    {
        x = checkingDirectionLeft(x,y, randomnumberX, randomnumberY, xrange); 
                if (!(find(visitedList.begin(), visitedList.end(), xy) != visitedList.end()))
        {
            visitedList.push_back(xy);
        }
    }
    if (direction == "weast")
    {
        cout << "Weast? What kind of compass are you reading?" << endl;
    }
    }
 
}

