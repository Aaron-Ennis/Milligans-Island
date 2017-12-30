/******************************************************************************
**	    Filename: Player.cpp
**		  Author: Aaron Ennis
**			Date: 30 November 2017
**	 Description: This is the implementation file for the Player class used in 
**				  the Milligan's Island text-based game. The Player object
**				  contains two pointers to string objects that each represent 
**				  an item carried in the Player's right and left hands. It also
**				  defines a few member functions to manipulate and display the
**				  Player's inventory.
******************************************************************************/

#include <iostream>
#include "Player.hpp"

/******************************************************************************
 * Function name: 	Player::Player
 *   Description:	This is the constructor for the Player object. It initial-
 *					izes the Player rightHand and leftHand string pointers to
 *					nullptr.
 *****************************************************************************/

Player::Player()
{

}

/******************************************************************************
 * Function name: 	Player::takeItem
 *   Description:	This function takes a string parameter and adds it to the
 *					vector representing the player's inventory. The player has
 *					only two hands, so can only carry two items in inventory at
 *					a time.
 *****************************************************************************/

void Player::takeItem(string item)
{

	if (this->inventory.size() < 2)
	{
		this->inventory.push_back(item);
	}
	else
	{
		cout << "I can't carry that! My hands are full!" << endl;
	}
	
}

/******************************************************************************
 * Function name: 	Player::dropItem
 *   Description:	This function takes a string parameter representing an item
 *					in the player's inventory. 
 *****************************************************************************/

void Player::dropItem(int index)
{
	if (!this->inventory.empty())
	{
		this->inventory.erase(inventory.begin() + index);
	}
	else
	{
		cout << "I am not carrying anything!" << endl;
	}
}

/******************************************************************************
 * Function name: 	Player::getInventory
 *   Description:	This accessor function returns the vector of strings that
 *					represent the player's inventory.
 *****************************************************************************/

vector<string> Player::getInventory()
{
	return this->inventory;
}

/******************************************************************************
 * Function name: 	Player::displayInventory
 *   Description:	This void function takes no parameters. It only displays
 *					the player's inventory.
 *****************************************************************************/

void Player::displayInventory()
{
	// Display player's inventory
	cout << "I am holding:";

	if (!this->inventory.empty())
	{
		for (string item : this->inventory)
		{
			cout << " " << item;
		}
	}
	else
	{
		cout << " Nothing!";
	}
	cout << endl;
}

/******************************************************************************
 * Function name: 	Player::clearInventory
 *   Description:	This function is simply used to clear the player's
 *					inventory through an accessor.
 *****************************************************************************/

void Player::clearInventory()
{
	this->inventory.clear();
}


/******************************************************************************
 * Function name: 	Player::~Player
 *   Description:	This is the destructor for the Player class.
 *****************************************************************************/

 Player::~Player()
{
	
}




