#include <iostream>
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
class Hero
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
    
    void class_choose(string class_input)
    {
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
  
    void add_hp(int hp)
    {
        health_points += hp;
        if(health_points >= health_points_max)
        {
            health_points_max = health_points;
        }
    }
    
    void update_hp(int hp)
    {
        health_points = hp;
        if(health_points >= health_points_max)
        {
            health_points_max = health_points;
        }
    }
};

string whatGender()
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

string whatClass()
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
//Combat - Suraj
pair<int, int> combat(int id_monster, int strenght, int magic_points, int armour, int hp)
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
      
        cout << "You defeated the monster and gained " << exp << " experience" << endl;
     
        if(tot <= 0)
        {
            throw invalid_argument( "YOU DIED :)" );
        }
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

int main()
{   //Relational database (Enemy, Weapons and Save tables) - Gavaskar 
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
                while(menu_check == 0)
                {
                    cin >> menu_choice;
                    if(menu_choice == "save" || menu_choice == "Save")
                    {
                        // Saving - Abdullah
                        save_the_game(name, gender, character_class, hero.level, hero.health_points, hero.health_points_max, hero.strenght, hero.armour, hero.magic_points, hero.experience, hero.level_up_experience, xlocation, ylocation);
                    }
                    else if(menu_choice == "quit" || menu_choice == "Quit")
                    {
                        menu_check = 1;
                    }
                }
                
                // Combat (5 is the ID of the monster in the database. 15th ID is the boss) - Suraj (not finished)
                auto result_combat = combat(2, hero.strenght, hero.magic_points, hero.armour, hero.health_points);
                hero.update_hp(result_combat.first);
                hero.add_experience(result_combat.second);
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
                cout << "Michal Krawczykowski" << endl;
                cout << "Charlie Evans" << endl;
                cout << "Abdullah Islam" << endl;
                cout << "Suraj Choli" << endl;
                cout << "Gavaskar GL;1I3BRI;ANWIUSDKFJ" << endl;

            case 4 :
                return 0;
        }
}
