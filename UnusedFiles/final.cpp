#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <stdio.h>
#include <sqlite3.h>
#include <string>
#include <iomanip>
#include <stdexcept>
#include <tuple>
#include "libsqlite.hpp"

/* The game is called (name of the game) and is about a hero trying to
 * find the escape from the forest. The game allows the user to choose
 * one character from three. Each of the has got different statistics.
 * The hero will be encountering monsters, fighting with them, gaining
 * experience and leveling up. The game can be saved in every part of the
 * game. Loading is available from the main menu. Monsters are encountered
 * randomly. In one part of the game the boss is located. The game is
 * finished after beating up the boss.
 */

using namespace std;
//Class, statistics, experience, health points, gender function, 
//class function - Michal Krawczykowski
class Hero  //defining class which stores data about the hero
{
public:
    string name;
    string gender;
    string character_class;
    int health_points = 100;
    int health_points_max = 100;
    int strenght = 0;
    int armour = 0;
    int magic_points = 0;
    int experience = 0;
    int level = 1;
    int level_up_experience = 100;
    
    void class_choose(string class_input)  //function updating statistics depending on
    {                                      //chosen class of the hero
        if (class_input == "Warrior")
        {
            character_class = class_input;
            strenght += 30;
            armour += 30;
            magic_points += 10;
        }
        else if (class_input == "Archer")
        {
            character_class = class_input;
            strenght += 20;
            armour += 40;
            magic_points += 10;
        }
        else if (class_input == "Mage")
        {
            character_class = class_input;
            strenght += 10;
            armour += 20;
            magic_points += 40;
        }
    }
    
    void print_stats()
    {
        cout << "--------STATISTICS--------" << endl;
        cout << "Your name is: " << name << endl;
        cout << "Your gender is: " << gender << endl;
        cout << "Your class is: " << character_class << endl;
        cout << "Your level is: " << level << endl;
        cout << "Your HP is: " << health_points << "/" << health_points_max << endl;
        cout << "Your strenght is: " << strenght << endl;
        cout << "Your armour is: " << armour << endl;
        cout << "Your magic points is: " << magic_points << endl;
        cout << "Your experience is: " << experience << endl;
        cout << "Your need to have: " << level_up_experience << " overall experience to level up" << endl;
    }
    
    void add_experience(int new_experience)
    {
        experience = experience + new_experience;
        if (experience >= level_up_experience)
        {
            while (experience >= level_up_experience)
            {
                level += 1;
                health_points_max += 100;
                health_points = health_points_max;
                experience -= level_up_experience;
                level_up_experience +=  100;
                
                if (character_class == "Warrior")
                {
                    strenght += 15;
                    armour += 10;
                }
                else if (character_class == "Archer")
                {
                    strenght += 10;
                    armour += 15;
                }
                else if (character_class == "Mage")
                {
                    armour += 10;
                    magic_points += 15;
                }
            }
            cout << "You level up! Your level is: " << level << endl;
        }
    }
  
    void add_hp(int hp)  //function adding health points
    {
        health_points += hp;
        if(health_points >= health_points_max)
        {
            health_points_max = health_points;
        }
    }
    
    void update_hp(int hp)  //function updating health points
    {
        health_points = hp;
        if(health_points >= health_points_max)
        {
            health_points_max = health_points;
        }
    }
};

string whatGender()  //function for choosing gender of the hero
{
    int check_gender = 0;
    string gender;
    while (check_gender == 0)
    {
        cout << "Is your hero a male of female? " << endl;
        cin >> gender;
        if (gender == "Male" || gender == "male")
        {
            check_gender = 1;
            return ("Male");
        }
        else if (gender == "Female" || gender == "female")
        {
            check_gender = 1;
            return("Female");
        }
        else
        {
            cout << "Wrong value, please choose the gender" << endl;
        }
    }
}

string whatClass()  //function for choosing class of the hero
{
    int check_class = 0;
    string character_class;
    while (check_class == 0)
    {
        cout << "Is your hero a Warrior, Archer or Mage? " << endl;
        cin >> character_class;
        if (character_class == "Warrior" || character_class == "warrior")
        {
            check_class = 1;
            return ("Warrior");
        }
        else if (character_class == "Archer" || character_class == "archer")
        {
            check_class = 1;
            return ("Archer");
        }
        else if (character_class == "Mage" || character_class == "mage")
        {
            check_class = 1;
            return("Mage");
        }
        else
        {
            cout << "Wrong value, please choose your class" << endl;
        }
    }
}
//Combat - Suraj + Charlie
pair<int, int> combat(int id_monster, int strenght, int magic_points, int armour, int hp, int x, int y)
{
    int damage, shield, exp;
    int tot = armour + hp;
    string sqliteFile = "databaseALL.sqlite3";
    try 
    {
        sqlite::sqlite db( sqliteFile );
        auto cur = db.get_statement(); 
        cur->set_sql( "SELECT Enemy.name, Enemy.damage, Enemy.shield, Enemy.experience, Weapons.name_weapon, Weapons.damage_weapon " 
                      "FROM Enemy INNER JOIN Weapons "
                      "ON Enemy.id_weapon = Weapons.id_weapon " 
                      "WHERE Enemy.id_enemy=?;" );
        cur->prepare();
        cur->bind(1, id_monster);
        cur->step();

        cout << "You're encountering a " << cur->get_text(0) << " who's got a " << cur->get_text(4) << endl;
        damage = cur->get_int(1) + cur->get_int(5);
        shield = cur->get_int(2);
        exp = cur->get_int(3);
        string monName = cur->get_text(0);
      
      auto cur4 = db.get_statement();
        cur4->set_sql("INSERT INTO SaveMonsters " 
          "(monName, damage, shield, exp, x, y) " 
          "VALUES (?, ?, ?, ?, ?, ?);" );
        
        cur4->prepare();
        cur4->bind(1, monName);
        cur4->bind(2, damage);
        cur4->bind(3, shield);
        cur4->bind(4, exp);
        cur4->bind(5, x);
        cur4->bind(6, y);

      
        cur4->step();
      
      string combatOption = "";
      cout << "Would you like to Run, Fight or use an Item?" ;
      cin >> combatOption;
      transform(combatOption.begin(), combatOption.end(), combatOption.begin(), ::tolower);

      vector<string> fightList ={"fight"};
      if (find(fightList.begin(), fightList.end(), combatOption) != fightList.end())
      {
        // run michal code
             while(shield > 0)
            {
                tot = tot - damage;
                if(strenght > magic_points)
                {
                    shield -= strenght;
                }
                else
                {
                    shield -= magic_points;
                }
            }
      
                  if(tot <= 0)
        {
            throw invalid_argument( "YOU DIED :)" );
        }
      }
      
      else
      {
        return make_pair(0, 0);
      }
      
      cout << "You defeated the monster and gained " << exp << " experience" << endl;
        return make_pair(hp, exp);
    }
    catch( sqlite::exception e )      // catch all sql issues
    {
        std::cerr << e.what() << std::endl;
        return make_pair(0, 0);
    }
}
//Saving the game - Abdullah
int save_the_game(string name, string gender, string character_class, int level, int hp, int hp_max, int strenght, int armour, int magic_points, int experience, int experience_lvl, int xlocation, int ylocation)
{
    string save;
    cout << "Do you want to save the game? " << endl;
    cin >> save;
    try 
    {
        if(save == "yes" || save == "Yes")
        {
        string sqliteFile = "databaseALL.sqlite3";
        sqlite::sqlite db( sqliteFile );
        auto cur3 = db.get_statement();
        cur3->set_sql("INSERT INTO Save " 
                      "(name, gender, class, hp, hp_max, strenght, armour, magic, experience, level, level_up_exp, xlocation, ylocation) " 
                      "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);" );
        cur3->prepare();
        cur3->bind(1, name);
        cur3->bind(2, gender);
        cur3->bind(3, character_class);
        cur3->bind(4, hp);
        cur3->bind(5, hp_max);
        cur3->bind(6, strenght);
        cur3->bind(7, armour);
        cur3->bind(8, magic_points);
        cur3->bind(9, experience);
        cur3->bind(10, level);
        cur3->bind(11, experience_lvl);
        cur3->bind(12, xlocation);
        cur3->bind(13, ylocation);
        cur3->step();
        cout << "Your game has been saved" << endl;
        }

        else
        {
            cout << "Continue the game" << endl;
        }
    }
    catch( sqlite::exception e )      // catch all sql issues
    {
        std::cerr << e.what() << std::endl;
        return 0;
    }
}

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

int main()
{   //Relational database (Enemy, Weapons and Save tables) - Gavaskar 
    string name, gender, character_class, menu_choice;
    int user_choice, level, strenght, magic_points, armour, hp, hp_max, exp, exp_max, xlocation, ylocation;
    int menu_check = 0;
    int x = 0;
    int y = 0;   
    int xrange = 10;
    int yrange = 10;    
    vector <string> visitedList{};
    srand (time(NULL));
    int randomnumberX = rand() % 10; 
    int ID = rand() % 9999;
    int randomnumberY = rand() % 10; 
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
                
                // Map + movement - Charlie
                while (!(x == 2 && y == 2))
                {
                        string direction = "";
                        cout << "Which direction would you like to go?: " ;
                        cin >> direction;
                        transform(direction.begin(), direction.end(), direction.begin(), ::tolower);
                        string stringX = to_string(x);
                        string stringY = to_string(y);
                        int previousX = x;
                        int previousY = y;
                        string xy = stringX + stringY;
                  
                        

                        vector<string> forwardList ={"forwards","forward","north","ahead","onwards"};
                        vector<string> backwardsList ={"backwards","backward","south","down","downward","downwards","back"};
                        vector<string> rightList ={"right","east"};
                        vector<string> leftList ={"left","west"};
                  
                        if (find(forwardList.begin(), forwardList.end(), direction) != forwardList.end())
                        {
                            y = checkingDirectionForwards(x,y, randomnumberX, randomnumberY, yrange); // call a checking function to see if you can move that way, then run the forwards function.
                            if (!(find(visitedList.begin(), visitedList.end(), xy) != visitedList.end()))
                            {
                                visitedList.push_back(xy);
                            }
                            for(int i=0; i<visitedList.size(); ++i)
                            cout << visitedList[i] << ' ';
                        }
                    
                        else if (find(backwardsList.begin(), backwardsList.end(), direction) != backwardsList.end())
                        {

                            y = checkingDirectionBackwards(x,y, randomnumberX, randomnumberY, yrange); 
                                    if (!(find(visitedList.begin(), visitedList.end(), xy) != visitedList.end()))
                            {
                                visitedList.push_back(xy);
                            }
                        }
                    
                        else if (find(rightList.begin(), rightList.end(), direction) != rightList.end())
                        {
                            x = checkingDirectionRight(x,y, randomnumberX, randomnumberY, xrange); 
                                    if (!(find(visitedList.begin(), visitedList.end(), xy) != visitedList.end()))
                            {
                                visitedList.push_back(xy);
                            }
                        }
                       
                        else if (find(leftList.begin(), leftList.end(), direction) != leftList.end())
                        {
                            x = checkingDirectionLeft(x,y, randomnumberX, randomnumberY, xrange); 
                                    if (!(find(visitedList.begin(), visitedList.end(), xy) != visitedList.end()))
                            {
                                visitedList.push_back(xy);
                            }
                        }
                    
                        else if (direction == "weast")
                        {
                            cout << "Weast? What kind of compass are you reading?" << endl;
                        }
                    
                        else if (direction == "save") // Gavaskar - saving
                        {
                            save_the_game(name, gender, character_class, hero.level, hero.health_points, hero.health_points_max, hero.strenght, hero.armour, hero.magic_points, hero.experience, hero.level_up_experience, xlocation, ylocation);
                        }
                        
                        else if (direction == "quit")
                        {
                            return 0;
                        }
                  
                        else 
                        {
                            cout << "Wrong value" << endl;
                        }
                  
                  int monRand;
                  if (monRand == 0)
                  {
                    monRand = 14;
                  }
                  if (level == 1)
                  {
                    monRand = rand() % 4;
                  }
                  if (level == 2)
                  {
                    monRand = rand() % 6;
                  }
                  if (level == 3)
                  {
                    monRand = rand() % 8;
                  }
                  if (level > 8)
                  {
                    monRand = rand() % 13;
                  }
                  if (x == 2 && y == 2) // change to variable for exit
                  {
                    monRand = 15;
                  }
                  
                        auto result_combat = combat(monRand, hero.strenght, hero.magic_points, hero.armour, hero.health_points, x, y);
                    if (result_combat.first == 0 && result_combat.second == 0)
                    {
                        visitedList.pop_back();
                      cout << x << y << endl;
                      x = previousX;
                      y = previousY;
                      cout << x << y << endl;
                    }
                        hero.update_hp(result_combat.first);
                        hero.add_experience(result_combat.second);
                }
                
                cout << "Congratulations! You finished the game" << endl;
                break;
            }
            
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
                cout << "Michal 'Not Micheal' Krawczykowski" << endl;
                cout << "Charlie 'Jack' Evans" << endl;
                cout << "Abdullah 'Christian' Islam" << endl;
                cout << "Suraj 'Yes' Choli" << endl;
                cout << "Gavaskar 'Absent Manager' GL;1I3BRI;ANWIUSDKFJ" << endl;

            case 4 :
                return 0;
        }
}
