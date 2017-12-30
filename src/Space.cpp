/******************************************************************************
**	    Filename: Space.cpp
**		  Author: Aaron Ennis
**			Date: 30 November 2017
**	 Description: This is the implementation file for the Space class. Space
**				  is an abstract base class used to create inherited objects
**				  that describe types of spaces for the Milligan's Island text-
**				  based adventure game.
******************************************************************************/

#include "Space.hpp"
#include "utilities.hpp"
#include <iostream>


/******************************************************************************
 * Function name: 	Space::Space
 *   Description:	This is the default constructor for the Space class.
 *****************************************************************************/

Space::Space()
{
	this->player = nullptr;
	this->boatRepaired = false;
}

/******************************************************************************
 * Function name: 	Space::setPlayer
 *   Description:	This void function is used to assign a pointer to a Player
 *					object to a Space class object. This is done so that the 
 *					Space class object has access to the Player object.
 *****************************************************************************/

void Space::setPlayer(Player* player)
{
	this->player = player;
}

/******************************************************************************
 * Function name: 	Space::addItem
 *   Description:	This void function is used to pick up an item from the
 *					Space the player is currently in. The function will display
 *					feedback appropriate to the conditions.
 *****************************************************************************/

void Space::takeItem()
{
	int itemCount = 1;

	// Check to see if there are any items to take
	if (this->items.empty())
	{
		cout << endl;
		cout << "There is nothing to take!" << endl;
		return;
	}

	// Only allow an item to be taken if the player has room in inventory
	if (this->player->getInventory().size() < 2)
	{
		int choice = 0;
		cout << endl;
		cout << "Items available to take:" << endl;

		// Display available items in Space
		for (string item : this->items)
		{
			cout << itemCount << ".  " << item << endl;
			itemCount++;
		}

		// Add one more option for player deciding not to take an item
		cout << itemCount << ".  Nothing (Go Back)" << endl;

		choice = getInt("Which item should I take? ");
		while (choice > itemCount || choice < 1)
		{
			cout << "Invalid entry. Enter 1 - " << itemCount << "." << endl;
			choice = getInt("Which item should I take? ");
		}

		// If player chooses to go back without taking an item, return 
		if (choice == itemCount)
		{
			cout << endl;
			cout << "Okay. Taking nothing." << endl;
			return;
		}

		// Otherwise put the item in the player's inventory, and remove it from
		// the ground.
		else
		{
			// Add the item to player inventory
			this->player->takeItem(this->items[choice - 1]);
			cout << endl;
			cout << "I picked up " << this->items[choice - 1] << endl;

			// Erase it from the Space items vector 
			this->items.erase(items.begin() + (choice - 1));
			return;
		}
	}
	else	// No room in inventory
	{
		cout << endl;
		cout << "I can't carry any more. My hands are full!" << endl;
		return;
	}
}

/******************************************************************************
 * Function name: 	Space::dropItem
 *   Description:	This void function is used to drop an item from the
 *					player's inventory. The function will display feedback
 *					appropriate to the conditions.
 *****************************************************************************/

void Space::dropItem()
{
	int itemCount = 1;

	// Need a local copy of the player's inventory
	vector<string> inventory(this->player->getInventory());

	// If player's inventory is not empty
	if (!inventory.empty())
	{
		int choice = 0;
		cout << endl;
		cout << "Items I can drop:" << endl;

		// Display player inventory
		for (string item : inventory)
		{
			cout << itemCount << ".  " << item << endl;
			itemCount++;
		}

		// Add one more option for player deciding not to drop an item
		cout << itemCount << ".  Nothing (Go Back)" << endl;

		choice = getInt("Which item should I drop? ");
		while (choice > itemCount || choice < 1)
		{
			cout << "Invalid entry. Enter 1 - " << itemCount << "." << endl;
			choice = getInt("Which item should I drop? ");
		}

		// If player chooses to go back without dropping an item, return
		if (choice == itemCount)
		{
			cout << endl;
			cout << "Okay. Dropping nothing." << endl;
			return;
		}

		// Otherwise put the item on the ground (items vector), and remove it
		// from the player's inventory.
		else
		{
			// Add the item to the ground (items vector)
			this->items.push_back(inventory[choice - 1]);

			cout << endl;
			cout << "I dropped " << inventory[choice - 1] << endl;

			// Erase it from the Space items vector 
			this->player->dropItem(choice - 1);
			return;
		}
	}
	else	// No room in inventory
	{
		cout << endl;
		cout << "I don't have anything to drop!" << endl;
		return;
	}
}

/******************************************************************************
 * Function name: 	Space::displayItems
 *   Description:	This void function takes no parameters. It merely displays
 *					the items available to pick up from the Space object.
 *****************************************************************************/

void Space::displayItems()
{
	// Display items in the Space
	cout << endl;
	cout << "On the ground I see:";
	
	if (!this->items.empty())
	{
		for (string item : this->items)
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
 * Function name: 	Space::getRepairStatus
 *   Description:	This accessor function returns the current repair status
 *					of the boat.
 *****************************************************************************/

bool Space::getRepairStatus()
{
	return this->boatRepaired;
}

/******************************************************************************
 * Function name: 	Space::~Space
 *   Description:	This is the destructor for the Space class.
 *****************************************************************************/

Space::~Space()
{
	
}

/******************************************************************************
*********************   Begin Boat Derived Class   ***************************
******************************************************************************/

/******************************************************************************
 * Function name: 	Boat::Boat
 *   Description:	This is the constructor for the Boat class.
 *****************************************************************************/

Boat::Boat()
{
	this->emergencyKitOpen = false;
}

/******************************************************************************
 * Function name: 	Boat::linkSpaces
 *   Description:	This void function takes as a parameter a pointer to an 
 *					array of pointer to Spaces and uses it to link this Space
 *					to the Spaces around it.
 *****************************************************************************/

void Boat::linkSpaces(Space** spaces)
{
	this->north = nullptr;
	this->south = nullptr;
	this->east = spaces[1];		// Beach is to the east
	this->west = nullptr;
}


/******************************************************************************
 * Function name: 	Boat::doAction
 *   Description:	This void function takes no parameters. If it's not already
 *					open, it sets the emergencyKitOpen data member to true and
 *					adds "Water Wings" to the list of items available in the 
 *					Boat Space.
 *****************************************************************************/

void Boat::doAction()
{
	if (!this->emergencyKitOpen)
	{
		this->emergencyKitOpen = true;
		this->items.push_back("**Lifevest**");
		cout << endl;
		cout << "A **Lifevest** falls from the kit." << endl << endl;
	}
	else
	{
		cout << endl;
		cout << "The emergency kit is empty." << endl << endl;;
	}
}

/******************************************************************************
 * Function name: 	Boat::repairBoat
 *   Description:	This void function takes no parameters. If the player
 *					has the necessary items (plank of wood and tree sap) in 
 *					inventory, the boat is repaired.
 *****************************************************************************/

void Boat::repairBoat()
{
	bool hasPlank = false;
	bool hasSap = false;

	// Check to see if the player has a sharp rock and an empty bottle
	for (string item : this->player->getInventory())
	{
		if (item == "**Wooden Plank**")
		{
			hasPlank = true;
		}

		if (item == "**Bottle of Sap**")
		{
			hasSap = true;
		}
	}

	// If player is missing either item, display a message that the repair
	// cannot be made.
	if (!hasSap || !hasPlank)
	{
		cout << endl;
		cout << "I don't have the items needed to repair the boat!" << endl;
	}
	// Otherwise, set the boatRepaired value to true so the control functions
	// can proceed with win conditions.
	else if (hasSap && hasPlank)
	{
		this->boatRepaired = true;
		cout << endl;
		cout << "I patched the hole with the **Wooden Plank** and the ";
		cout << "**Bottle of Sap**!" << endl;
		cout << "I should be able to set sail now!" << endl;
	}
}


/******************************************************************************
 * Function name: 	Boat::displayDescription
 *   Description:	This void function takes no parameters. It simply displays
 *					a description of the Boat Space.
 *****************************************************************************/

void Boat::displayDescription()
{
	// Persistent description
	cout << endl;
	cout << "I am on my boat. I see my emergency kit and the hole in the ";
	cout << "boat's hull." << endl;
	cout << "I'll need to fix that hole before I can set sail." << endl;
	
	// Display the items available to pick up
	this->displayItems();

	// Display the contents of the player's inventory.
	this->player->displayInventory();
	
}


/******************************************************************************
 * Function name: 	Boat::chooseAction
 *   Description:	This function takes no parameters. It continues displaying
 *					this Space's options until one of the options to move to a
 *					different Space is chosen. The pointer to the chosen Space
 *					is then returned.
 *****************************************************************************/

Space* Boat::chooseAction()
{
	int choice;

	// Stay in this space unless an explicit return call is made.
	while (true)
	{
		// Display options for this Space.
		cout << endl;
		cout << "What shall I do now?" << endl;
		cout << "1.  Go east (Beach)" << endl;
		cout << "2.  Open emergency kit" << endl;
		cout << "3.  Repair the boat" << endl;
		cout << "4.  Take an item" << endl;
		cout << "5.  Drop an item" << endl;
		cout << "6.  Look around" << endl;
		cout << "7.  Set sail!!!" << endl;

		choice = getInt("Choose an action: ");
		while (choice < 0 || choice > 7)
		{
			cout << "Invalid choice. Please enter 1 - 6" << endl;
			choice = getInt("Choose an action: ");
		}

		// Determine path based on choice.
		switch (choice)
		{
			case 1:	return this->east;

			case 2:	this->doAction();
					break;

			case 3:	this->repairBoat();
					break;

			case 4:	this->takeItem();
					break;

			case 5:	this->dropItem();
					break;

			case 6:	this->displayDescription();
					break;

			case 7:	if (!this->boatRepaired)
					{
						cout << endl;
						cout << "Can't set sail. I must first fix the hole.";
					}
					else
					{
						return this->east;
					}
		}
	}
}



/******************************************************************************
 * Function name: 	Boat::~Boat
 *   Description:	Destructor for the Boat class.
 *
 *****************************************************************************/

Boat::~Boat()
{
	
}

/******************************************************************************
*********************   Begin Beach Derived Class   ***************************
******************************************************************************/

/******************************************************************************
 * Function name: 	Beach::Beach
 *   Description:	This is the constructor for the Beach class.
 *****************************************************************************/

Beach::Beach()
{
	this->sandOpen = false;
}

/******************************************************************************
 * Function name: 	Beach::linkSpaces
 *   Description:	This void function takes as a parameter a pointer to an 
 *					array of pointer to Spaces and uses it to link this Space
 *					to the Spaces around it.
 *****************************************************************************/

void Beach::linkSpaces(Space** spaces)
{
	this->north = nullptr;
	this->south = nullptr;
	this->east = spaces[2];		// Jungle is to the east
	this->west = spaces[0];		// Boat is to the west
}

/******************************************************************************
 * Function name: 	Beach::doAction
 *   Description:	This void function takes no parameters. If it's not already
 *					open, it sets the sandOpen data member to true and
 *					adds "Wooden Plank" to the list of items available in the 
 *					Beach Space.
 *****************************************************************************/

void Beach::doAction()
{
	if (!this->sandOpen)
	{
		this->sandOpen = true;
		this->items.push_back("**Wooden Plank**");
		cout << endl;
		cout << "I've uncovered a **Wooden Plank** a little bigger than the ";
		cout << "hole in my boat!" << endl;

	}
	else
	{
		cout << "I didn't find anything in the sand." << endl;
	}
}

/******************************************************************************
 * Function name: 	Beach::displayDescription
 *   Description:	This void function takes no parameters. It simply displays
 *					a description of the Beach Space.
 *****************************************************************************/

void Beach::displayDescription()
{
	// Persistent description
	cout << endl;
	cout << "I am on the beach. I see sand for miles and a path into the ";
	cout << "jungle to the east." << endl;
	cout << "My boat is to the west." << endl;
	
	// Display the items available to pick up
	this->displayItems();

	// Display the contents of the player's inventory.
	this->player->displayInventory();
}

/******************************************************************************
 * Function name: 	Beach::chooseAction
 *   Description:	This function takes no parameters. It continues displaying
 *					this Space's options until one of the options to move to a
 *					different Space is chosen. The pointer to the chosen Space
 *					is then returned.
 *****************************************************************************/

Space* Beach::chooseAction()
{
	int choice;

	// Stay in this space unless an explicit return call is made.
	while (true)
	{
		// Display options for this Space.
		cout << endl;
		cout << "What shall I do now?" << endl;
		cout << "1.  Go east (Jungle)" << endl;
		cout << "2.  Go west (Boat)" << endl;
		cout << "3.  Dig in the sand" << endl;
		cout << "4.  Take an item" << endl;
		cout << "5.  Drop an item" << endl;
		cout << "6.  Look around" << endl;

		choice = getInt("Choose an action: ");
		while (choice < 0 || choice > 6)
		{
			cout << "Invalid choice. Please enter 1 - 6" << endl;
			choice = getInt("Choose an action: ");
		}

		// Proceed based on choice.
		switch (choice)
		{
			case 1:	return this->east;

			case 2:	return this->west;

			case 3:	this->doAction();
					break;

			case 4:	this->takeItem();
					break;

			case 5:	this->dropItem();
					break;

			case 6:	this->displayDescription();
					break;
		}
	}
}

/******************************************************************************
 * Function name: 	Beach::~Beach
 *   Description:	Destructor for the Beach class
 *
 *****************************************************************************/

Beach::~Beach()
{
	
}

/******************************************************************************
*********************   Begin Jungle Derived Class  ***************************
******************************************************************************/

/******************************************************************************
 * Function name: 	Jungle::Jungle
 *   Description:	This is the constructor for the Jungle class.
 *****************************************************************************/

Jungle::Jungle()
{
	this->vinesDown = false;
}

/******************************************************************************
 * Function name: 	Jungle::linkSpaces
 *   Description:	This void function takes as a parameter a pointer to an 
 *					array of pointer to Spaces and uses it to link this Space
 *					to the Spaces around it.
 *****************************************************************************/

void Jungle::linkSpaces(Space** spaces)
{
	this->north = spaces[3];	// Cove is to the north
	this->south = spaces[5];	// Lava Rock is to the south
	this->east = spaces[4];		// Mountain is to the east
	this->west = spaces[1];		// Beach is to the west
}

/******************************************************************************
 * Function name: 	Jungle::doAction
 *   Description:	This void function takes no parameters. If the player has
 *					not already taken the vines down, the boolean is toggled to
 *					true and the vines are added to the items list for this
 *					Space.
 *****************************************************************************/

void Jungle::doAction()
{
	// If we haven't already pulled the vines down...
	if (!this->vinesDown)
	{
		this->vinesDown = true;				// Now we have
		this->items.push_back("**Vines**"); // Add to items list
		cout << endl;
		cout << "Some **Vines** fall to the jungle floor." << endl << endl;
	}
	else
	{
		cout << endl;
		cout << "I cannot reach any more vines." << endl;
	}
}

/******************************************************************************
 * Function name: 	Jungle::displayDescription
 *   Description:	This void function takes no parameters. It simply displays
 *					a description of the Jungle Space
 *****************************************************************************/

void Jungle::displayDescription()
{
	// Persistent description
	cout << endl;
	cout << "I am in the Jungle. I see some low-hanging vines. To the north ";
	cout << "I can see a cove " << endl;
	cout << "through the trees. To the south I see a field of cooled lava ";
	cout << "rock. To the east " << endl;
	cout << "I see a winding path up the mountain. To the west is a path to ";
	cout << "the beach." << endl;
	
	// Display the items available to pick up
	this->displayItems();

	// Display the contents of the player's inventory.
	this->player->displayInventory();
}

/******************************************************************************
 * Function name: 	Jungle::chooseAction
 *   Description:	This function takes no parameters. It continues displaying
 *					this Space's options until one of the options to move to a
 *					different Space is chosen. The pointer to the chosen Space
 *					is then returned.
 *****************************************************************************/

Space* Jungle::chooseAction()
{
	int choice;

	// Stay in this space unless an explicit return call is made.
	while (true)
	{
		// Display options
		cout << endl;
		cout << "What shall I do now?" << endl;
		cout << "1.  Go north (Cove)" << endl;
		cout << "2.  Go south (Lava Rock)" << endl;
		cout << "3.  Go east (Mountain)" << endl;
		cout << "4.  Go west (Beach)" << endl;
		cout << "5.  Pull the vines" << endl;
		cout << "6.  Take an item" << endl;
		cout << "7.  Drop an item" << endl;
		cout << "8.  Look around" << endl;

		choice = getInt("Choose an action: ");
		while (choice < 0 || choice > 8)
		{
			cout << "Invalid choice. Please enter 1 - 6" << endl;
			choice = getInt("Choose an action: ");
		}

		// Proceed based on choice.
		switch (choice)
		{
			case 1:	return this->north;

			case 2:	return this->south;

			case 3:	return this->east;

			case 4:	return this->west;

			case 5:	this->doAction();
					break;

			case 6:	this->takeItem();
					break;

			case 7:	this->dropItem();
					break;

			case 8:	this->displayDescription();
					break;
		}
	}
}

/******************************************************************************
 * Function name: 	Jungle::~Jungle
 *   Description:	Destructor for the Jungle class.
 *****************************************************************************/

Jungle::~Jungle()
{
	
}

/******************************************************************************
*********************   Begin Cove Derived Class  ***************************
******************************************************************************/

/******************************************************************************
 * Function name: 	Cove::Cove
 *   Description:	This is the constructor for the Cove class.
 *****************************************************************************/

Cove::Cove()
{
	this->bottleFound = false;
}

/******************************************************************************
 * Function name: 	Cove::linkSpaces
 *   Description:	This void function takes as a parameter a pointer to an 
 *					array of pointer to Spaces and uses it to link this Space
 *					to the Spaces around it.
 *****************************************************************************/

void Cove::linkSpaces(Space** spaces)
{
	this->north = nullptr;
	this->south = spaces[2];	// Jungle is to the south
	this->east = nullptr;
	this->west = nullptr;
}

/******************************************************************************
 * Function name: 	Cove::doAction
 *   Description:	This void function takes no parameters. It controls the
 *					flow of the unique action of the Cove space. In short, the
 *					player must have a lifevest to enter the water and find
 *					the empty bottle. The player must also have one hand free.
 *****************************************************************************/

void Cove::doAction()
{
	bool hasLifeVest = false;
	bool hasHandFree = false;

	// Check to see if the player has a lifevest
	for (string item : this->player->getInventory())
	{
		if (item == "**Lifevest**")
		{
			hasLifeVest = true;
		}
	}

	// Player needs can only be carrying the lifevest to get the bottle
	if (this->player->getInventory().size() == 1)
	{
		hasHandFree = true;
	}


	if (!hasLifeVest)	// Not carrying the lifevest
	{
		cout << endl;
		cout << "I can't swim. I need something to help me float." << endl;
	}
	else if (!hasHandFree)	// Has lifevest, but also carrying something else
	{
		cout << endl;
		cout << "I have my lifevest, but I need a hand free to swim." << endl;
	}
	else 	// Otherwise, player can enter the water
	{
		if (!this->bottleFound)	// If the bottle hasn't been found yet
		{
			// Add bottle to player inventory
			this->player->takeItem("**Empty Bottle**");
			cout << endl;
			cout << "I found an **Empty Bottle** and am now carrying it.";
			cout << endl;
			this->bottleFound = true;
		}
		else	// If the bottle has already been found
		{
			cout << endl;
			cout << "I swam around a bit, but didn't find anything." << endl;
		}
		
	}
}

/******************************************************************************
 * Function name: 	Cove::displayDescription
 *   Description:	This void function takes no parameters. It simply displays
 *					a description of the Cove Space.
 *****************************************************************************/

void Cove::displayDescription()
{
	// Persistent description
	cout << endl;
	cout << "I am standing next to a deep, clear cove. To the south is the ";
	cout << "path back into the jungle." << endl;
	
	// Display the items available to pick up
	this->displayItems();

	// Display the contents of the player's inventory.
	this->player->displayInventory();
}

/******************************************************************************
 * Function name: 	Cove::chooseAction
 *   Description:	This function takes no parameters. It continues displaying
 *					this Space's options until one of the options to move to a
 *					different Space is chosen. The pointer to the chosen Space
 *					is then returned.
 *****************************************************************************/

Space* Cove::chooseAction()
{
	int choice;

	// Stay in this space until explicit return statement
	while (true)
	{
		cout << endl;
		cout << "What shall I do now?" << endl;
		cout << "1.  Go south (Jungle)" << endl;
		cout << "2.  Enter the water" << endl;
		cout << "3.  Take an item" << endl;
		cout << "4.  Drop an item" << endl;
		cout << "5.  Look around" << endl;

		choice = getInt("Choose an action: ");
		while (choice < 0 || choice > 5)
		{
			cout << "Invalid choice. Please enter 1 - 6" << endl;
			choice = getInt("Choose an action: ");
		}

		switch (choice)
		{
			case 1:	return this->south;

			case 2:	this->doAction();
					break;

			case 3:	this->takeItem();
					break;

			case 4:	this->dropItem();
					break;

			case 5:	this->displayDescription();
					break;
		}
	}
}

/******************************************************************************
 * Function name: 	Cove::~Cove
 *   Description:	Destructor for the Cove class.
 *****************************************************************************/

Cove::~Cove()
{
	
}

/******************************************************************************
*********************   Begin Mountain Derived Class   ************************
******************************************************************************/

/******************************************************************************
 * Function name: 	Mountain::Mountain
 *   Description:	This is the constructor for the Mountain class.
 *****************************************************************************/

Mountain::Mountain()
{
	
}

/******************************************************************************
 * Function name: 	Mountain::linkSpaces
 *   Description:	This void function takes as a parameter a pointer to an 
 *					array of pointer to Spaces and uses it to link this Space
 *					to the Spaces around it.
 *****************************************************************************/

void Mountain::linkSpaces(Space** spaces)
{
	this->north = nullptr;
	this->south = nullptr;	
	this->east = nullptr;
	this->west = spaces[2];		// Jungle is to the west
}

/******************************************************************************
 * Function name: 	Mountain::doAction
 *   Description:	This void function takes no parameters. It controls the
 *					flow of the unique action of the Mountain space. In short,
 *					the player must have the empty bottle and the sharp rock
 *					in order to get the tree sap for repairing the boat.
 *****************************************************************************/

void Mountain::doAction()
{
	bool hasSharpRock = false;
	bool hasEmptyBottle = false;

	// Check to see if the player has a sharp rock and an empty bottle
	for (string item : this->player->getInventory())
	{
		if (item == "**Sharp Rock**")
		{
			hasSharpRock = true;
		}

		if (item == "**Empty Bottle**")
		{
			hasEmptyBottle = true;
		}
	}

	if (!hasSharpRock)
	{
		cout << endl;
		cout << "I have nothing sharp with which to cut the tree." << endl;
	}
	// If player has a sharp rock, but nothing to put the sap into right away
	else if (hasSharpRock && !hasEmptyBottle)
	{
		cout << endl;
		cout << "I cut into the tree and some sap oozed out, but I have ";
		cout << "nothing to store " << endl;
		cout << "it in. It's become hard and useless." << endl;
	}
	// If the player has both items...
	else if (hasSharpRock && hasEmptyBottle)
	{
		// ...clear the inventory to make room
		this->player->clearInventory();

		// ...add the bottle filled with sap and add the sharp rock back
		this->player->takeItem("**Bottle of Sap**");
		this->player->takeItem("**Sharp Rock**");
		cout << endl;
		cout << "I was able to catch the sap in my empty bottle. I should ";
		cout << "be able to use " << endl;
		cout << "this to seal up the hole in my boat." << endl;
		this->player->displayInventory();	
	}
	
}

/******************************************************************************
 * Function name: 	Mountain::displayDescription
 *   Description:	This void function takes no parameters. It simply displays
 *					a description of the Mountain Space.
 *****************************************************************************/

void Mountain::displayDescription()
{
	// Persistent description
	cout << endl;
	cout << "About halfway up the mountain, I found an old pine tree. To the ";
	cout << "west is the " << endl;
	cout << "path back down the mountain." << endl;
	
	// Display the items available to pick up
	this->displayItems();

	// Display the contents of the player's inventory.
	this->player->displayInventory();
}

/******************************************************************************
 * Function name: 	Mountain::chooseAction
 *   Description:	This function takes no parameters. It continues displaying
 *					this Space's options until one of the options to move to a
 *					different Space is chosen. The pointer to the chosen Space
 *					is then returned.
 *****************************************************************************/

Space* Mountain::chooseAction()
{
	int choice;

	// Stay in this space until explicit return statement
	while (true)
	{
		// Display options for this Space.
		cout << endl;
		cout << "What shall I do now?" << endl;
		cout << "1.  Go west (Jungle)" << endl;
		cout << "2.  Cut into tree" << endl;
		cout << "3.  Take an item" << endl;
		cout << "4.  Drop an item" << endl;
		cout << "5.  Look around" << endl;

		choice = getInt("Choose an action: ");
		while (choice < 0 || choice > 5)
		{
			cout << "Invalid choice. Please enter 1 - 6" << endl;
			choice = getInt("Choose an action: ");
		}

		// Proceed based on choice.
		switch (choice)
		{
			case 1:	return this->west;

			case 2:	this->doAction();
					break;

			case 3:	this->takeItem();
					break;

			case 4:	this->dropItem();
					break;

			case 5:	this->displayDescription();
					break;
		}
	}
}

/******************************************************************************
 * Function name: 	Mountain::~Mountain
 *   Description:	Destructor for the Mountain class.
 *****************************************************************************/

Mountain::~Mountain()
{
	
}

/******************************************************************************
***********************   Begin Lava Derived Class   **************************
******************************************************************************/

/******************************************************************************
 * Function name: 	Lava::Lava
 *   Description:	This is the constructor for the Lava class.
 *****************************************************************************/

Lava::Lava()
{
	this->bridgeRepaired = false;
}

/******************************************************************************
 * Function name: 	Lava::linkSpaces
 *   Description:	This void function takes as a parameter a pointer to an 
 *					array of pointer to Spaces and uses it to link this Space
 *					to the Spaces around it.
 *****************************************************************************/

void Lava::linkSpaces(Space** spaces)
{
	this->north = spaces[2];	// Jungle is to the north
	this->south = nullptr;	
	this->east = nullptr;
	this->west = nullptr;		
}

/******************************************************************************
 * Function name: 	Lava::doAction
 *   Description:	This void function takes no parameters. It controls the
 *					flow of the unique action of the Lava space. In short, the
 *					player needs to use the vines from the jungle to repair the
 *					rope bridge. This will reveal the sharp rock that is used
 *					to get sap out of the tree on the mountain.
 *****************************************************************************/

void Lava::doAction()
{
	bool hasVines = false;
	vector<string> inventory(this->player->getInventory());
	int inventoryIndex = 0;

	// Check to see if the player has vines. 
	for (int i = 0; i < inventory.size(); i++)
	{
		if (inventory[i] == "**Vines**")
		{
			hasVines = true;		// Player has vines
			inventoryIndex = i;		// Mark the index so we can remove them
		}
	}

	// Player has vines and the bridge has not already been repaired.
	if (hasVines && !this->bridgeRepaired)
	{
		this->items.push_back("**Sharp Rock**"); // Put rock on ground
		this->player->dropItem(inventoryIndex);	 // Remove vines
		this->bridgeRepaired = true;			 // Bridge is repaired now
		cout << endl;
		cout << "I was able to repair the bridge and look around on the ";
		cout << "other side of the lava " << endl;
		cout << "flow. I see a **Sharp Rock** that could be useful..." << endl;
	}
	// Player does not have vines and the bridge is broken
	else if (!hasVines && !this->bridgeRepaired)
	{
		cout << endl;
		cout << "I need something rope-like to repair the bridge." << endl;
	}
	else if (this->bridgeRepaired)
	{
		cout << endl;
		cout << "The bridge has already been repaired!" << endl;
	}	
}

/******************************************************************************
 * Function name: 	Lava::displayDescription
 *   Description:	This void function takes no parameters. It simply displays
 *					a description of the Lava Space.
 *****************************************************************************/

void Lava::displayDescription()
{
	// Persistent description
	if (!this->bridgeRepaired)
	{
		cout << endl;
		cout << "I am standing on a bed of lava rock. There is a rope bridge ";
		cout << "across a river of " << endl;
		cout << "molten lava, but it looks like it needs some repairs before ";
		cout << "I can use it." << endl;
		cout << "To the north is the path that leads to the jungle." << endl;
	}
	else
	{
		cout << "I am standing on a bed of lava rock. There is a rope bridge ";
		cout << "across a river of " << endl;
		cout << "molten lava. To the north is the path that leads to the ";
		cout << "jungle." << endl;
	}
	
	// Display the items available to pick up
	this->displayItems();

	// Display the contents of the player's inventory.
	this->player->displayInventory();
}

/******************************************************************************
 * Function name: 	Lava::chooseAction
 *   Description:	This function takes no parameters. It continues displaying
 *					this Space's options until one of the options to move to a
 *					different Space is chosen. The pointer to the chosen Space
 *					is then returned.
 *****************************************************************************/

Space* Lava::chooseAction()
{
	int choice;

	// Stay in this space until explicit return statement
	while (true)
	{
		// Display options.
		cout << endl;
		cout << "What shall I do now?" << endl;
		cout << "1.  Go north (Jungle)" << endl;
		cout << "2.  Repair bridge" << endl;
		cout << "3.  Take an item" << endl;
		cout << "4.  Drop an item" << endl;
		cout << "5.  Look around" << endl;

		choice = getInt("Choose an action: ");
		while (choice < 0 || choice > 5)
		{
			cout << "Invalid choice. Please enter 1 - 6" << endl;
			choice = getInt("Choose an action: ");
		}

		// Proceed based on choice.
		switch (choice)
		{
			case 1:	return this->north;

			case 2:	this->doAction();
					break;

			case 3:	this->takeItem();
					break;

			case 4:	this->dropItem();
					break;

			case 5:	this->displayDescription();
					break;
		}
	}
}

/******************************************************************************
 * Function name: 	Lava::~Lava
 *   Description:	Destructor for the Lava class.
 *****************************************************************************/

Lava::~Lava()
{
	
}


