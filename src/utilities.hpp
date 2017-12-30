/******************************************************************************
**	    Filename: utilities.hpp
**		  Author: Aaron Ennis
**			Date: 28 Septemeber 2017
**	 Description: This is the interface file for a set of utilities that
**				  are designed to help with input validation. It also contains
**				  an enumerated data type that can be used to track directions
**				  on a square game board.
******************************************************************************/

#ifndef utilities_hpp
#define utilities_hpp

#include <string>

int getInt(std::string);
char getAlphaChar(std::string);
enum Direction {Up = 1, Right, Down, Left};
void displayMenu();
int getMenuChoice(int maxChoice);
void seedRandom();

#endif // utilities_hpp