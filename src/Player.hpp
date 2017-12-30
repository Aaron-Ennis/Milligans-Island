/******************************************************************************
**	    Filename: Player.hpp
**		  Author: Aaron Ennis
**			Date: 30 November 2017
**	 Description: This is the implementation file for the Player class used in 
**				  the Milligan's Island text-based game. The Player object
**				  contains two pointers to string objects that each represent 
**				  an item carried in the Player's right and left hands. It also
**				  defines a few member functions to manipulate and display the
**				  Player's inventory.
******************************************************************************/

#ifndef Player_hpp
#define Player_hpp

#include <string>
#include <vector>

using namespace std;

class Player
 {
 private:
 	vector<string> inventory;
 public:
 	Player();
 	void takeItem(string item);
 	void dropItem(int index);
 	vector<string> getInventory();
 	void displayInventory();
 	void clearInventory();
 	~Player();
 	
 }; 
#endif // Player_hpp