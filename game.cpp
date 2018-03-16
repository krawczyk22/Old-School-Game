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
             health_points = health_points_max;
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

// Potions - Michal
int potion(int potion_number)
{
    try 
    {
        string sqliteFile = "databaseALL.sqlite3";
        sqlite::sqlite db( sqliteFile );
        auto cur4 = db.get_statement();
        cur4->set_sql("SELECT name, value "
                      "FROM Potions "
                      "WHERE id_potion = ?");
        cur4->prepare();
        cur4->bind(1, potion_number);
        cur4->step();
      
        cout << "You've found a " << cur4->get_text(0) << " which adds " << cur4->get_int(1) << " points to your health" << endl;
        return(cur4->get_int(1));
    }
    catch( sqlite::exception e )      // catch all sql issues
    {
        std::cerr << e.what() << std::endl;
        return 0;
    }
}


int monsterReset() //Charlie
{
      string sqliteFile = "databaseALL.sqlite3";
      sqlite::sqlite db( sqliteFile );
      auto cur5 = db.get_statement();
      cur5->set_sql("DELETE FROM SaveMonster;");
      cur5->prepare();
      cur5->step();
}
pair<int, int> combatAgain(int id_monster, int strenght, int magic_points, int armour, int hp, int x, int y, string xy, vector <string> visitedList, vector <string> potionList)
{
      int damage, shield, exp;
    int tot = armour + hp;


    string sqliteFile = "databaseALL.sqlite3";
  {
       try 
    {
        sqlite::sqlite db( sqliteFile );
        auto cur6 = db.get_statement(); 
        cur6->set_sql("SELECT Enemy.name, Enemy.damage, Enemy.shield, Enemy.experience, Weapons.name_weapon, Weapons.damage_weapon, SaveMonster.x, SaveMonster.y " 
                      "FROM (Enemy INNER JOIN Weapons "
                      "ON Enemy.id_weapon = Weapons.id_weapon) INNER JOIN SaveMonster ON Enemy.id_enemy = SaveMonster.id_enemy " 
                      "WHERE SaveMonster.x=? AND SaveMonster.y=?;" );
        cur6->prepare();
        cur6->bind(1, x);
        cur6->bind(2, y);
        cur6->step();  
         
        cout << "You're encountering a " << cur6->get_text(0) << " who's got a " << cur6->get_text(4) << endl;
        damage = cur6->get_int(1) + cur6->get_int(5);
        shield = cur6->get_int(2);
        exp = cur6->get_int(3);
        string monName = cur6->get_text(0);
        
          while(shield > 0)
      {
      string combatOption = "";
      cout << "Would you like to Run, Fight or use an Item?" ;
      cin >> combatOption;
      transform(combatOption.begin(), combatOption.end(), combatOption.begin(), ::tolower);

      
      vector<string> fightList ={"fight"};
      if (find(fightList.begin(), fightList.end(), combatOption) != fightList.end())
      {
        cout << "Your health points have dropped from " << tot;
                tot = tot - damage*0.8;
        if (tot < 1)
        {
          tot = 0;
        }
        cout << " to " << tot << endl;
        
        cout << "The " << monName << "'s health points have dropped from " << shield;
                if(strenght > magic_points)
                {
                    shield -= strenght;
                }
                else
                {
                    shield -= magic_points;
                }
        if (shield < 1)
        {
          shield = 0;
        }
        cout << " to " << shield << endl;
        if(tot <= 0)
        {        
            throw invalid_argument( "YOU DIED :)" );
        }
        if (shield <= 0)
        {
          int healing = rand() % 25;
          cout << "You defeated the monster and gained " << exp << " experience points as well as " << healing << " health points!" << endl;
          hp = tot;
          hp = hp + healing;
          return make_pair(hp, exp);
        }
            
      }


      vector<string> runList ={"run"};
      if (find(runList.begin(), runList.end(), combatOption) != runList.end())
      {
        hp = tot;
        return make_pair(0, 0);
      }
      }
       }
        catch( sqlite::exception e )      // catch all sql issues
    {
        cerr << e.what() << endl;
        return make_pair(0, 0);
    }
  }
}

//Combat - Suraj
pair<int, int> combat(int id_monster, int strenght, int magic_points, int armour, int hp, int x, int y, string xy, vector <string> visitedList, vector <string> potionList)

{
  int damage, shield, exp;
  int tot = armour + hp;

  string sqliteFile = "databaseALL.sqlite3";
  {
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
        cur4->set_sql("INSERT INTO SaveMonster " 
          "(id_enemy, x, y) " 
          "VALUES (?, ?, ?);" );
        
        cur4->prepare();
        cur4->bind(1, id_monster);
        cur4->bind(2, x);
        cur4->bind(3, y);
      
        cur4->step();
       
      while(shield > 0)
      {
      string combatOption = "";
      cout << "Would you like to Fight or Run?" ;
      cin >> combatOption;
      transform(combatOption.begin(), combatOption.end(), combatOption.begin(), ::tolower);

      
      vector<string> fightList ={"fight"};
      if (find(fightList.begin(), fightList.end(), combatOption) != fightList.end())
      {
        cout << "Your health points have dropped from " << tot;
                tot = tot - damage*0.8;
        if (tot < 1)
        {
          tot = 0;
        }
        cout << " to " << tot << endl;
        
        cout << "The " << monName << "'s health points have dropped from " << shield;
                if(strenght > magic_points)
                {
                    shield -= strenght;
                }
                else
                {
                    shield -= magic_points;
                }
        if (shield < 1)
        {
          shield = 0;
        }
        cout << " to " << shield << endl;
        if(tot <= 0)
        {        
            throw invalid_argument( "YOU DIED :)" );
        }
        if (shield <= 0)
        {
          int healing = rand() % 25;
          cout << "You defeated the monster and gained " << exp << " experience points as well as " << healing << " health points!" << endl;
          hp = tot;
          hp = hp + healing;
          return make_pair(hp, exp);
        }
            
      }

      vector<string> runList ={"run"};
      if (find(runList.begin(), runList.end(), combatOption) != runList.end())
      {
        hp = tot;
        return make_pair(0, 0);
      }
      }
    }
    catch( sqlite::exception e )      // catch all sql issues
    {
        cerr << e.what() << endl;
        return make_pair(0, 0);
    }
}
  }
string updateXY(int x,int y)
{
  string stringX = to_string(x);
  string stringY = to_string(y);
  string xy = stringX + stringY;
  return xy;
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
//direction functions - Charlie
int checkingDirectionForwards(int x,int y, int yrange)
{
    if (y == yrange)
    {
    cout << "You cannot go forwards, try another direction" << endl;
    }
    if (y < yrange)
    {

        y=y+1;

        cout << "You have moved forwards" << endl;
    }
    return y;
}
int checkingDirectionBackwards(int x,int y, int yrange)
{
    if (y == 0)
    {
    cout << "You cannot go backwards, try another direction" << endl;
    }
    if (y > 0)
    {

        y=y-1;

        cout << "You have moved backwards" << endl;
    }
    return y;
}
int checkingDirectionRight(int x,int y, int xrange)
{
    if (x == xrange)
    {
    cout << "You cannot go right, try another direction" << endl;
    }
    if (x < xrange)
    {

        x=x+1;
        
        cout << "You have moved right"<< endl;
    }
    return x;
}

int checkingDirectionLeft(int x,int y, int xrange)
{
    if (x == 0)
    {
    cout << "You cannot go left, try another direction" <<  endl;
    }
    if (x > 0)
    {
        x=x-1;      
        cout << "You have moved left" << endl;
    }
    return x;
}

int main()
{   
    monsterReset();
    string name, gender, character_class, menu_choice;
    int user_choice, level, strenght, magic_points, armour, hp, hp_max, exp, exp_max;
    int menu_check = 0;
    int x = 0;
    int y = 0; 
    srand (time(NULL));

    int xrange = 10;
    int yrange = 10;    
    vector <string> visitedList{"00"};
    vector <string> potionList{};
    vector<string> CompletedList ={"00"};
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
                  
                // Instractions - Michal Krawczykowski
                cout << " " << endl;
                cout << "-------------------------------------------------------------- " << endl;
                cout << "You have found yourself in a forest full of monsters. " << endl;
                cout << "You need to get out of here by finding the exit. " << endl;
                cout << "Good luck! " << endl;
                cout << " " << endl;
                cout << "-------------------------------------------------------------- " << endl;
                cout << "Type 'left', 'right', 'forwards' or 'backwards' to move." << endl;
                cout << "Type 'quit' to quit the game " << endl;
                cout << "Type 'save' to save the game " << endl;
                
                // Executing instructions and the actual maze - Charlie
                while (!(x == 10 && y == 10))
                {
                  
                        string direction = "";
                        cout << "Which direction would you like to go?: " ;
                        cin >> direction;
                        transform(direction.begin(), direction.end(), direction.begin(), ::tolower);
                        string stringX = to_string(x);
                        string stringY = to_string(y);
                        string xy = stringX + stringY;
                        int previousX = x;
                        int previousY = y;
                      int number_monster = rand() % 15;
                      if (number_monster == 0)
                      {
                        number_monster = 1;
                      }

                        vector<string> forwardList ={"forwards","forward","north","ahead","onwards"};
                        vector<string> backwardsList ={"backwards","backward","south","down","downward","downwards","back"};
                        vector<string> rightList ={"right","east"};
                        vector<string> leftList ={"left","west"};
                        
                        if (find(forwardList.begin(), forwardList.end(), direction) != forwardList.end())
                        {
                            y = checkingDirectionForwards(x, y, yrange); // call a checking function to see if you can move that way, then run the forwards function.
                           xy = updateXY(x,y);
                          if (!(find(CompletedList.begin(), CompletedList.end(), xy) != CompletedList.end()))
                          {
                          if (y != previousY)
                          {
                            if (find(visitedList.begin(), visitedList.end(), xy) != visitedList.end())
                            {
                               auto result_combatAgain = combatAgain(number_monster, hero.strenght, hero.magic_points, hero.armour, hero.health_points, x, y, xy, visitedList, potionList);
                               if (result_combatAgain.first == 0 && result_combatAgain.second == 0)
                                 {
                                   x = previousX;
                                   y = previousY;
                                 }
                               if (result_combatAgain.first != 0)
                                 {
                                   hero.update_hp(result_combatAgain.first);
                                   CompletedList.push_back(xy);
                                 }
                                 hero.add_experience(result_combatAgain.second);
                                    }
                           if (!(find(visitedList.begin(), visitedList.end(), xy) != visitedList.end()))
                            {
                                visitedList.push_back(xy);
                                int random_thing = rand() % 100;
                                int number_potion = rand() % 2;
                                if (number_potion == 0)
                                {
                                  number_potion = 3;
                                }
                                if (random_thing < 90)
                                {
                                    if (random_thing < 60)
                                    {
                                        auto result_combat = combat(number_monster, hero.strenght, hero.magic_points, hero.armour, hero.health_points, x, y, xy, visitedList, potionList);
                                        if (result_combat.first == 0 && result_combat.second == 0)
                                        {
                                          
                                          x = previousX;
                                          y = previousY;
                                        }
                                        if (result_combat.first != 0)
                                        {
                                        hero.update_hp(result_combat.first);
                                          CompletedList.push_back(xy);
                                        }
                                        hero.add_experience(result_combat.second);
                                    }
                                    else
                                    {
                                      hero.add_hp(potion(number_potion));
                                      CompletedList.push_back(xy);

                                    }
                                }
                                else
                                {
                                    cout << "You didn't find anything" << endl;
                                  CompletedList.push_back(xy);
                                }
                            }
                          }
                          }
                }
                        
                    
                       else if (find(backwardsList.begin(), backwardsList.end(), direction) != backwardsList.end())
                        {
                            y = checkingDirectionBackwards(x, y, yrange); // call a checking function to see if you can move that way, then run the forwards function.
                           xy = updateXY(x,y);
                          if (!(find(CompletedList.begin(), CompletedList.end(), xy) != CompletedList.end()))
                          {
                           if (y != previousY)
                          {
                                  if (find(visitedList.begin(), visitedList.end(), xy) != visitedList.end())
                            {
                                        auto result_combatAgain = combatAgain(number_monster, hero.strenght, hero.magic_points, hero.armour, hero.health_points, x, y, xy, visitedList, potionList);
                                        if (result_combatAgain.first == 0 && result_combatAgain.second == 0)
                                        {
                                          x = previousX;
                                          y = previousY;
                                        }
                                        if (result_combatAgain.first != 0)
                                        {
                                        hero.update_hp(result_combatAgain.first);
                                          CompletedList.push_back(xy);
                                        }
                                        hero.add_experience(result_combatAgain.second);
                                    }
                           if (!(find(visitedList.begin(), visitedList.end(), xy) != visitedList.end()))
                            {
                                visitedList.push_back(xy);
                                int random_thing = rand() % 100;
                                int number_potion = rand() % 2;
                                if (number_potion == 0)
                                {
                                  number_potion = 3;
                                }
                                if (random_thing < 90)
                                {
                                    if (random_thing < 60)
                                    {
                                        auto result_combat = combat(number_monster, hero.strenght, hero.magic_points, hero.armour, hero.health_points, x, y, xy, visitedList, potionList);
                                        if (result_combat.first == 0 && result_combat.second == 0)
                                        {
                                          
                                          x = previousX;
                                          y = previousY;
                                        }
                                        if (result_combat.first != 0)
                                        {
                                        hero.update_hp(result_combat.first);
                                          CompletedList.push_back(xy);
                                        }
                                        hero.add_experience(result_combat.second);
                                    }
                                    else
                                    {
                                        //hero.add_hp(potion(number_potion));
                                      CompletedList.push_back(xy);

                                    }
                                }
                                else
                                {
                                    cout << "You didn't find anything" << endl;
                                  CompletedList.push_back(xy);
                                }
                            }
                          }
                          }
                }
                 else if (find(rightList.begin(), rightList.end(), direction) != rightList.end())
                        {
                            x = checkingDirectionRight(x, y, yrange); // call a checking function to see if you can move that way, then run the forwards function.
                           xy = updateXY(x,y);
                        if (!(find(CompletedList.begin(), CompletedList.end(), xy) != CompletedList.end()))
                          {
                            if (x != previousX)
                          {
                                  if (find(visitedList.begin(), visitedList.end(), xy) != visitedList.end())
                            {
                                        auto result_combatAgain = combatAgain(number_monster, hero.strenght, hero.magic_points, hero.armour, hero.health_points, x, y, xy, visitedList, potionList);
                                        if (result_combatAgain.first == 0 && result_combatAgain.second == 0)
                                        {
                                          x = previousX;
                                          y = previousY;
                                        }
                                        if (result_combatAgain.first != 0)
                                        {
                                        hero.update_hp(result_combatAgain.first);
                                          CompletedList.push_back(xy);
                                        }
                                        hero.add_experience(result_combatAgain.second);
                                    }
                           if (!(find(visitedList.begin(), visitedList.end(), xy) != visitedList.end()))
                            {
                                visitedList.push_back(xy);
                                int random_thing = rand() % 100;
                                int number_potion = rand() % 2;
                                if (number_potion == 0)
                                {
                                  number_potion = 3;
                                }
                                if (random_thing < 90)
                                {
                                    if (random_thing < 60)
                                    {
                                        auto result_combat = combat(number_monster, hero.strenght, hero.magic_points, hero.armour, hero.health_points, x, y, xy, visitedList, potionList);
                                        if (result_combat.first == 0 && result_combat.second == 0)
                                        {
                                          
                                          x = previousX;
                                          y = previousY;
                                        }
                                        if (result_combat.first != 0)
                                        {
                                        hero.update_hp(result_combat.first);
                                          CompletedList.push_back(xy);
                                        }
                                        hero.add_experience(result_combat.second);
                                    }
                                    else
                                    {
                                        hero.add_hp(potion(number_potion));
                                        CompletedList.push_back(xy);

                                    }
                                }
                                else
                                {
                                    cout << "You didn't find anything" << endl;
                                  CompletedList.push_back(xy);
                                }
                            }
                          }
                        }
                }
                 else if (find(leftList.begin(), leftList.end(), direction) != leftList.end())
                        {
                            x = checkingDirectionLeft(x, y, yrange); // call a checking function to see if you can move that way, then run the forwards function.
                           xy = updateXY(x,y);
                          if (!(find(CompletedList.begin(), CompletedList.end(), xy) != CompletedList.end()))
                          {
                            if (x != previousX)
                          {
                                  if (find(visitedList.begin(), visitedList.end(), xy) != visitedList.end())
                            {
                                        auto result_combatAgain = combatAgain(number_monster, hero.strenght, hero.magic_points, hero.armour, hero.health_points, x, y, xy, visitedList, potionList);
                                        if (result_combatAgain.first == 0 && result_combatAgain.second == 0)
                                        {
                                          x = previousX;
                                          y = previousY;
                                        }
                                        if (result_combatAgain.first != 0)
                                        {
                                        hero.update_hp(result_combatAgain.first);
                                          CompletedList.push_back(xy);
                                        }
                                        hero.add_experience(result_combatAgain.second);
                                    }
                           if (!(find(visitedList.begin(), visitedList.end(), xy) != visitedList.end()))
                            {
                                visitedList.push_back(xy);
                                int random_thing = rand() % 100;
                                int number_potion = rand() % 2;
                                if (number_potion == 0)
                                {
                                  number_potion = 3;
                                }
                                if (random_thing < 90)
                                {
                                    if (random_thing < 60)
                                    {
                                        auto result_combat = combat(number_monster, hero.strenght, hero.magic_points, hero.armour, hero.health_points, x, y, xy, visitedList, potionList);
                                        if (result_combat.first == 0 && result_combat.second == 0)
                                        {
                                          
                                          x = previousX;
                                          y = previousY;
                                        }
                                        if (result_combat.first != 0)
                                        {
                                        hero.update_hp(result_combat.first);
                                          CompletedList.push_back(xy);
                                        }
                                        hero.add_experience(result_combat.second);
                                    }
                                    else
                                    {
                                        hero.add_hp(potion(number_potion));
                                      CompletedList.push_back(xy);

                                    }
                                }
                                else
                                {
                                    cout << "You didn't find anything" << endl;
                                  CompletedList.push_back(xy);
                                }
                            }
                          }
                          }
                }
                    
                        else if (direction == "weast")
                        {
                            cout << "Weast? What kind of compass are you reading?" << endl;
                        }
                    
                        else if (direction == "save")
                        {
                            save_the_game(name, gender, character_class, hero.level, hero.health_points, hero.health_points_max, hero.strenght, hero.armour, hero.magic_points, hero.experience, hero.level_up_experience, x, y);
                        }
                        
                        else if (direction == "stats")
                        {
                            hero.print_stats();
                        }
                        
                        else if (direction == "quit")
                        {
                            return 0;
                        }
                  
                        else 
                        {
                            cout << "Wrong value" << endl;
                        }
                }
                
                cout << "Congratulations! You finished the game" << endl;
                break;
            }
            
            case 2 :
            {   //Loading the game - Gavaskar
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
                    x = cur2->get_int(12);
                    y = cur2->get_int(13);
                    
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
