/******************************************************************************
**	    Filename: Island.hpp
**		  Author: Aaron Ennis
**			Date: 30 November 2017
**	 Description: This is the interface file for the Island class. This 
**				  class is used to create an object that holds the Island's
**				  Spaces and a Player as data members. It also contains member
**				  functions that allow the Player to move between Spaces.
******************************************************************************/

#ifndef Island_hpp
#define Island_hpp

#include "Space.hpp"
#include "Player.hpp"
#include <iostream>

using namespace std;

class Island
{
private:
 	Space** spaces;
 	Player* player;
 	Space* currentSpace;
public:
 	Island();
 	void playGame();
 	void displayIntroduction();
 	~Island();
 	
}; 
#endif // Island_hpp