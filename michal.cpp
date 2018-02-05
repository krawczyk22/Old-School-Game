#include <iostream>
#include <string>

using namespace std;

class Hero
{
    public:
    string name;
    string gender;
    string character_class;
    int strenght = 0;
    int armour = 0;
    int magic_points = 0;
    int experience = 0;
    int level = 1;
    int level_up_experience = 100;
  
    string class_choose(string class_input)
    {
       if (class_input == "Warrior")
       {
          character_class = class_input;
          strenght = strenght + 30;
          armour = armour + 30;
          magic_points = magic_points + 10;
       }
       else if (class_input == "Archer")
       {
          character_class = class_input;
          strenght = strenght + 20;
          armour = armour + 40;
          magic_points = magic_points + 10;
       }
       else if (class_input == "Mage")
       {
          character_class = class_input;
          strenght = strenght + 10;
          armour = armour + 20;
          magic_points = magic_points + 40;
       }
    }
     
    void print_stats()
    {
        cout << "--------STATISTICS--------" << endl;
        cout << "Your name is: " << name << endl;
        cout << "Your gender is: " << gender << endl;
        cout << "Your class is: " << character_class << endl;
        cout << "Your level is: " << level << endl;
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
               level = level + 1;
               experience = experience - level_up_experience;
               level_up_experience = level_up_experience + 100;
                
               if (character_class == "Warrior")
               {
                   strenght = strenght + 15;
                   armour = armour + 10;
               }
               else if (character_class == "Archer")
               {
                   strenght = strenght + 10;
                   armour = armour + 15;
               }
               else if (character_class == "Mage")
               {
                   armour = armour + 10;
                   magic_points = magic_points + 15;
               }
            }
            cout << "You level up! Your level is: " << level << endl;
        }
    }
  
    int return_strenght()
    {
        return strenght;
    }
  
    int return_armour()
    {
        return armour;
    }
  
    int return_magic_points()
    {
        return magic_points;
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

int main()
{
    string name, gender, character_class;
    int user_choice;
    
    cout << "Press a number to choose" << endl;
    cout << "1. Play the game" << endl;
    cout << "2. Load the game" << endl;
    cout << "3. Authors" << endl;
    cout << "4. Exit" << endl;
    cin >> user_choice;
    switch(user_choice)
    {
      case 1 :
        {
            cout << "What is the name of your hero? " << endl;
            cin >> name; 
            character_class = whatClass();
            gender = whatGender();
            Hero hero;
            hero.name = name;
            hero.gender = gender;
            hero.class_choose(character_class);
            hero.print_stats();
            hero.add_experience(500);
            hero.print_stats();
            break;
        }
        
      case 2 :
        cout << "not finished" << endl;
        break;
        
      case 3 :
        cout << "not finished" << endl;
        cout << "not finished" << endl;
        cout << "not finished" << endl;
        cout << "not finished" << endl;
        cout << "not finished" << endl;
        cout << "not finished" << endl;
        break;
        
      case 4 :
        return 0;
    }
  
}
