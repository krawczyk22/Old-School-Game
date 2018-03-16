#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <algorithm>
#include "protoMove.h"

#include <stdio.h>
#include <sqlite3.h>
#include "libsqlite.hpp"

using namespace std;

//g++ --std=c++14 movement.cpp -o movement -lsqlite3
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
      //Relational database (Enemy, Weapons and Save tables) - Gavaskar 
    string name, gender, character_class, menu_choice;
    int user_choice, level, strenght, magic_points, armour, hp, hp_max, exp, exp_max, xlocation, ylocation;
    int menu_check = 0;
    string sqliteFile = "databaseALL.sqlite3";
        //Main menu - Suraj
        cout << "Press a number to choose" << endl;
        cout << "1. Play new game" << endl;
        cout << "2. Load the game" << endl;
        cout << "3. Authors" << endl;
        cout << "4. Exit" << endl;
        cin >> user_choice;
        switch(user_choice)
        {
            case 1 :
            {
                //Initialising the hero - Michal Krawczykowski
                cout << "What is the name of your hero? " << endl;
                cin >> name;
                character_class = whatClass();
                gender = whatGender();
                Hero hero;
                hero.name = name;
                hero.gender = gender;
                hero.class_choose(character_class);
                  
                // Instructions - Gavaskar
                cout << " " << endl;
                cout << "-------------------------------------------------------------- " << endl;
                cout << "You're ending up in a forest full of monsters. " << endl;
                cout << "You need to get out of here by finding the exit. " << endl;
                cout << "The exit is located behind the boss so you need to beat him. " << endl;
                cout << "Good luck! " << endl;
                cout << " " << endl;
                cout << "-------------------------------------------------------------- " << endl;
                cout << "Type 'left', 'right', 'forwards' or 'backwards' to move." << endl;
                cout << "Type 'quit' to quit the game " << endl;
                cout << "Type 'save' to save the game " << endl;
                
                // Executing instructions - Gavaskar (not finished)
                 int x = 0;
    int y = 0;
    
    int xrange = 10;
    int yrange = 10;
    
    
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
        
    vector<string> forwardList ={"forwards","forward","north","ahead","onwards"};
    if (find(forwardList.begin(), forwardList.end(), direction) != forwardList.end())
    {
        y = checkingDirectionForwards(x,y, randomnumberX, randomnumberY, yrange); // call a checking function to see if you can move that way, then run the forwards function. 
    }
    vector<string> backwardsList ={"backwards","backward","south","down","downward","downwards","back"};
    if (find(backwardsList.begin(), backwardsList.end(), direction) != backwardsList.end())
    {
        y = checkingDirectionBackwards(x,y, randomnumberX, randomnumberY, yrange); 
    }
    vector<string> rightList ={"right","east"};
    if (find(rightList.begin(), rightList.end(), direction) != rightList.end())
    {
        x = checkingDirectionRight(x,y, randomnumberX, randomnumberY, xrange);  
    }
    vector<string> leftList ={"left","west"};
    if (find(leftList.begin(), leftList.end(), direction) != leftList.end())
    {
        x = checkingDirectionLeft(x,y, randomnumberX, randomnumberY, xrange);  
    }
    if (direction == "weast")
    {
        cout << "Weast? What kind of compass are you reading?" << endl;
    }
    vector<string> saveList ={"save"};
    if (find(saveList.begin(), saveList.end(), direction) != saveList.end())
    {
      save_the_game(name, gender, character_class, hero.level, hero.health_points, hero.health_points_max, hero.strenght, hero.armour, hero.magic_points, hero.experience, hero.level_up_experience, xlocation, ylocation);
    }
    vector<string> quitList ={"quit"};
    if (find(quitList.begin(), quitList.end(), direction) != quitList.end())
    {
      menu_check = 1;
    }
                      auto result_combat = combat(2, hero.strenght, hero.magic_points, hero.armour, hero.health_points);
                hero.update_hp(result_combat.first);
                hero.add_experience(result_combat.second);
                break;
    }
               
}
                
                // Combat (5 is the ID of the monster in the database. 15th ID is the boss) - Suraj (not finished)

            
            
            case 2 :
            {   //Loading the game - Abdullah
                cout << "Press a number to load the game: " << endl;
                try 
                {
                    sqlite::sqlite db( sqliteFile );
                    auto cur = db.get_statement();
                    auto cur2 = db.get_statement();
                    cur->set_sql("SELECT * FROM Save;");
                    cur->prepare();

                    while(cur->step())
                    {
                        cout << cur->get_int(0) << " " << cur->get_text(1) << " " 
                             << cur->get_text(2) << " " << cur->get_text(3) << " " 
                             << cur->get_int(10) << endl;
                    }
                    
                    int save_choose;
                    cin >> save_choose;
                    cur2->set_sql("SELECT * FROM Save WHERE id_save = ?;");
                    cur2->prepare();
                    cur2->bind(1, save_choose);
                    cur2->step();
                  
                    Hero hero;
                    hero.name = cur2->get_text(1);
                    hero.gender = cur2->get_text(2);
                    hero.character_class = cur2->get_text(3);
                    hero.health_points = cur2->get_int(4);
                    hero.health_points_max = cur2->get_int(5);
                    hero.strenght = cur2->get_int(6);
                    hero.armour = cur2->get_int(7);
                    hero.magic_points = cur2->get_int(8);
                    hero.experience = cur2->get_int(9);
                    hero.level = cur2->get_int(10);
                    hero.level_up_experience = cur2->get_int(11);
                    xlocation = cur2->get_int(12);
                    ylocation = cur2->get_int(13);
                    
                    // not finished. will be similar to the case 1
                }
                catch( sqlite::exception e )      // catch all sql issues
                {
                    std::cerr << e.what() << std::endl;
                    return 0;
                }
                break;
            }
            
            case 3 :
                cout << "The game has been made by:" << endl;
                cout << "Michal Krawczykowski" << endl;
                cout << "Charlie Evans" << endl;
                cout << "Abdullah Islam" << endl;
                cout << "Suraj Choli" << endl;
                cout << "Gavaskar GL;1I3BRI;ANWIUSDKFJ" << endl;

            case 4 :
                return 0;
        }
    

 
}
