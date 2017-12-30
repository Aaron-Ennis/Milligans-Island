/******************************************************************************
**	    Filename: Island.cpp
**		  Author: Aaron Ennis
**			Date: 30 November 2017
**	 Description: This is the implementation file for the Island class. This 
**				  class is used to create an object that holds the Island's
**				  Spaces and a Player as data members. It also contains member
**				  functions that allow the Player to move between Spaces.
******************************************************************************/

#include "Island.hpp"

/******************************************************************************
 * Function name: 	Island::Island
 *   Description:	This is the constructor for the Island class.
 *****************************************************************************/

Island::Island()
{
	// Initialize the spaces
	this->spaces = new Space*[6];

	// Create the player
	this->player = new Player;

	// Create the different parts of the island
	this->spaces[0] = new Boat();
	this->spaces[1] = new Beach();
	this->spaces[2] = new Jungle();
	this->spaces[3] = new Cove();
	this->spaces[4] = new Mountain();
	this->spaces[5] = new Lava();
	
	// Now that the spaces are created, we need to link them all togther
	// using the linkSpaces member function of each
	for (int i = 0; i < 6; i++)
	{
		this->spaces[i]->linkSpaces(spaces);
	}
}

/******************************************************************************
 * Function name: 	Island::playGame
 *   Description:	This void function takes no parameters. It controls the 
 *					basic flow of the Milligan's Island text-based adventure
 *					game. Basic control includes keeping track of the number
 *					of turns taken and the win/lose conditions.
 *****************************************************************************/

void Island::playGame()
{
	int turnCount = 15;
	// Set the starting Space and put the player in it.
	this->currentSpace = this->spaces[1];
	this->currentSpace->setPlayer(this->player);

	this->displayIntroduction();

	while (!this->spaces[0]->getRepairStatus() && turnCount >= 0)
	{
		cout << endl;
		cout << "*** " << turnCount << " hours until high tide! ***" << endl;
		this->currentSpace->displayDescription();
		this->currentSpace = this->currentSpace->chooseAction();
		this->currentSpace->setPlayer(this->player);
		turnCount--;
	}

	// If we exited because we ran out of time
	if (turnCount < 0)
	{
		cout << endl;
		cout << "I was not able to repair the hull in time. Now I am ";
		cout << "stranded here!" << endl;
	}
	// Otherwise, we exited because we repaired the ship
	else
	{
		cout << endl;
		cout << "Thank goodness I got off that island! Thanks for the help!";
		cout << endl;
	}
}

/******************************************************************************
 * Function name: 	Island::displayIntroduction
 *   Description:	This void function takes no parameters. It simply displays
 *					some basic information about the game and sets the stage.
 *****************************************************************************/

void Island::displayIntroduction()
{
	cout << "Welcome to Milligan's Island. I woke up shipwrecked, face ";
	cout << "down in the sand." << endl;
	cout << "There is a hole in the side of my boat, and the tide is ";
	cout << "coming in fast." << endl;
	cout << "I have about 15 hours to explore this island and find the ";
	cout << "items to fix my boat." << endl;
	cout << "It takes me an hour to move from one part of the island to ";
	cout << "another. I can't " << endl;
	cout << "swim, and I can only carry two items at a time. (I only ";
	cout << "have two hands!) " << endl;
}



/******************************************************************************
 * Function name: 	Island::~Island
 *   Description:	This is the destructor for the Island class.
 *****************************************************************************/

Island::~Island()
{
	for (int i = 0; i < 6; i++)
	{
		delete spaces[i];
	}

	delete [] spaces;

	delete player;
}
