/******************************************************************************
**	    Filename: main.cpp
**		  Author: Aaron Ennis
**			Date: 30 November 2017
**	 Description: This main program contains a simple menu to play or quit the
**				  Milligan's Island text-based adventure game.
******************************************************************************/

#include <iostream>
#include <string>
#include "Island.hpp"
#include "Space.hpp"
#include "Player.hpp"
#include "utilities.hpp"

using namespace std;

int main()
{
	int choice;
	
	displayMenu();
	choice = getMenuChoice(2);

	while (choice != 2)
	{
		Island myIsland;
		myIsland.playGame();

		displayMenu();
		choice = getMenuChoice(2);
	}
	
	return 0;
}