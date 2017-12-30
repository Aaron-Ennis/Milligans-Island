/******************************************************************************
**	    Filename: utilities.cpp
**		  Author: Aaron Ennis
**			Date: 28 Septemeber 2017
**	 Description: This is the implementation file for a set of utilities that
**				  are designed to help with input validation.
******************************************************************************/

#include "utilities.hpp"
#include <string>
#include <iostream>
#include <cctype>
#include <ctime>

/******************************************************************************
**	Function Name: getAlphaChar
**	  Description: This function takes a prompt for input as a string from the
**				   client code. The input is evaluated to see if it is a single
**				   alphabetic character. If it is not, the user will be
**				   re-prompted until a valid value is entered. That valid value
**				   is then returned.
**	    Arguments: string
**		  Returns: char
******************************************************************************/

char getAlphaChar(std::string charPrompt)
{
	std::string value;
	std::cout << charPrompt;
	getline(std::cin, value);
	while(value.length() > 1 || value.empty() || !isalpha(value[0]))
	{
		std::cout << "Invalid entry. Please try again." << std::endl;
		std::cout << charPrompt;
		getline(std::cin, value);
	}
	return value[0];
}

/******************************************************************************
**	Function Name: getInt
**	  Description: This function takes a prompt for input as a string from the
**				   client code. The input is evaluated to see if it is an 
**				   integer. If it is not, the user will be re-prompted until
**				   a valid value is entered. That valid value is then 
**				   returned.   
**	    Arguments: string
**		  Returns: int
******************************************************************************/

int getInt(std::string intPrompt)
{
	std::string value;
	int flag = 0;
	std::cout << intPrompt;
	getline(std::cin, value);
	for (int i = 0; i < value.length(); i++)
		{
			if (!isdigit(value[i]))
			{
				flag = 1;
			}
		}
	while(flag == 1 || value.empty())
	{
		flag = 0;
		std::cout << "Invalid entry. Please try again." << std::endl;
		std::cout << intPrompt;
		getline(std::cin, value);
		for (int i = 0; i < value.length(); i++)
		{
			if (!isdigit(value[i]))
			{
				flag = 1;
			}
		}
	}
	return stoi(value);
}

/******************************************************************************
 * Function name: 	displayMenu
 *   Description:	This utility function displays a simple menu for selection.
 *					It is easily editable to make it easy to reuse.
 *****************************************************************************/

void displayMenu()
{
	std::cout << std::endl;
	std::cout << "1.  Play Game" << std::endl;
	std::cout << "2.  Exit Game" << std::endl << std::endl;
}

/******************************************************************************
 * Function name: 	getMenuChoice
 *   Description:	This utility function is used to get the menu choice from 
 *					a displayed menu. It takes an integer representing the
 *					maximum number of choices in the menu, and returns an
 *					integer representing the user's choice.
 *****************************************************************************/

int getMenuChoice(int maxChoice)
{
	int choice;
	choice = getInt("Enter your choice: ");
	while (choice < 1 || choice > maxChoice)
	{
		std::cout << "Valid choices are between 1 and " << maxChoice
					<< ". Please re-enter." << std::endl;
		choice = getInt("Enter your choice: ");
	}
	return choice;
}

/******************************************************************************
 * Function name: 	seedRandom
 *   Description:	
 *
 *****************************************************************************/

void seedRandom()
{
	// Seed srand using call to time() 
	int randomSeed;	// To hold a seed number for random generator
	randomSeed = std::time(0);
	std::srand(randomSeed);
}

