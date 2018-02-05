#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
using namespace std;

int forwards(int x,int y, int randomnumberX, int randomnumberY)
{
    if (x != randomnumberX || y != randomnumberY)
    {
        y=y+1;
    }
    return y;
}

int backwards(int x,int y, int randomnumberX, int randomnumberY)
{

    if (x != randomnumberX || y != randomnumberY)
    {
        y=y-1;
    }
    return y;
}

int right(int x,int y, int randomnumberX, int randomnumberY)
{
    if (x != randomnumberX || y != randomnumberY)
    {
        x=x+1;
    }
    
    return x;
}

int left(int x,int y, int randomnumberX, int randomnumberY)
{

    if (x != randomnumberX || y != randomnumberY)
    {
        x=x-1;
    }


    return x;
}

int checkingDirectionForwards(int x,int y, int randomnumberX, int randomnumberY)
{
    if (y == 10 || (x == randomnumberX && y == randomnumberY))
    {
        cout << "You cannot go forwards, try another direction";
        //explanationDirectionForward();
    }
    if (y < 10)
    {
        forwards(x,y,randomnumberX, randomnumberY);
        cout << "You have moved forwards";
    }
    return y;
}
void explanationDirectionForward()
{
    cout << "You cannot go forwards, try another direction";
}
int main()
{
    int x = 0;
    int y = 10;
    
    int xrange = 10;
    int yrange = 10;
    
    int randomnumberX = 7; // use random but need to make sure room to get to bosses/exit 
    int randomnumberY = 4;
    
    string direction = "";
    cout << "Which direction would you like to go?: " ;
    cin >> direction;
    
    if (direction == "forwards")
    {
        checkingDirectionForwards(x,y, randomnumberX, randomnumberY); // call a checking function to see if you can move that way, then run the forwards function.
        
    }

}

