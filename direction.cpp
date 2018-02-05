#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
using namespace std;

//g++ --std=c++14 test.cpp -o test
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
{
    int x = 0;
    int y = 0;
    
    int xrange = 10;
    int yrange = 10;
    
    int randomnumberX = 7; // use random but need to make sure room to get to bosses/exit 
    int randomnumberY = 4;
    
    
    while (!(x == 2 && y == 2))
    {
    string direction = "";
    cout << "Which direction would you like to go?: " ;
    cin >> direction;
        
    if (direction == "forwards")
    {
        y = checkingDirectionForwards(x,y, randomnumberX, randomnumberY, yrange); // call a checking function to see if you can move that way, then run the forwards function. 
    }
    if (direction == "backwards")
    {
        y = checkingDirectionBackwards(x,y, randomnumberX, randomnumberY, yrange); 
    }
    if (direction == "right")
    {
        x = checkingDirectionRight(x,y, randomnumberX, randomnumberY, xrange);  
    }
    if (direction == "left")
    {
        x = checkingDirectionLeft(x,y, randomnumberX, randomnumberY, xrange);  
    }
    }
 
}

