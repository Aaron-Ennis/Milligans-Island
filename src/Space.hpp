/******************************************************************************
**	    Filename: Space.hpp
**		  Author: Aaron Ennis
**			Date: 30 November 2017
**	 Description: This is the interface file for the Space class. Space
**				  is an abstract base class used to create inherited objects
**				  that describe types of spaces for the Milligan's Island text-
**				  based adventure game.
******************************************************************************/

#ifndef Space_hpp
#define Space_hpp 

#include <vector>
#include <string>
#include "Player.hpp"

using namespace std;

class Space
{
protected:
	Space* north;
	Space* south;
	Space* east;
	Space* west;
	vector<string> items;
	Player* player;
	bool boatRepaired;
public:
	Space();
	void setPlayer(Player* player);
	void takeItem();
	void dropItem();
	void displayItems();
	bool getRepairStatus();
	virtual void linkSpaces(Space** spaces) = 0;
	virtual void doAction() = 0;
	virtual void displayDescription() = 0;
	virtual Space* chooseAction() = 0;
	~Space();
};

class Boat : public Space
{
private:
	bool emergencyKitOpen;
public:
	Boat();
	void linkSpaces(Space** spaces);
	void doAction();
	void repairBoat();
	void displayDescription();
	Space* chooseAction();

	~Boat();
	
};

class Beach : public Space
{
private:
	bool sandOpen;
public:
	Beach();
	void linkSpaces(Space** spaces);
	void doAction();
	void displayDescription();
	Space* chooseAction();
	~Beach();
	
};

class Jungle : public Space
{
private:
	bool vinesDown;
public:
	Jungle();
	void linkSpaces(Space** spaces);
	void doAction();
	void displayDescription();
	Space* chooseAction();
	~Jungle();
};

class Cove : public Space
{
private:
	bool bottleFound;
public:
	Cove();
	void linkSpaces(Space** spaces);
	void doAction();
	void displayDescription();
	Space* chooseAction();
	~Cove();
};

class Mountain : public Space
{
public:
	Mountain();
	void linkSpaces(Space** spaces);
	void doAction();
	void displayDescription();
	Space* chooseAction();
	~Mountain();
	
};

class Lava : public Space
{
private:
	bool bridgeRepaired;
public:
	Lava();
	void linkSpaces(Space** spaces);
	void doAction();
	void displayDescription();
	Space* chooseAction();
	~Lava();
	
};

#endif // Space_hpp