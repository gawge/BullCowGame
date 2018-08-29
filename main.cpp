/*

THIS IS THE CONSOLE EXECUTABLE THAT MAKES USE OF THE FBullCowGame CLASS. THIS ACTS AS THE VIEW IN AN MCV PATTERN AND IS RESPONSIBLE FOR ALL USER INTERACTION. FOR GAME LOGIC SEE FBullCowGame CLASS.

*/


#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;																	// type alias for standard strings
using int32 = int;																			// type alias for standard int

void PrintIntro();
void Gameplay();
FText GetValidGuess();	
void PrintGameSummary();
bool AskToPlayAgain();	

FBullCowGame BCGame = FBullCowGame();														// create game instance

int main()	
{	
	do 
	{
		PrintIntro();
		Gameplay();
	}

	while (AskToPlayAgain() == true);														// the game runs through this loop which will continue until the play again bool becomes false (player says no)

	return 0;
}

void Gameplay()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)						/*	 while loop asking for guesses while the game is not won
																								 and there are still tries remaining				*/
	{
		FText Guess = GetValidGuess();
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
	return;
}

void PrintIntro()																			 // intro text
{
	std::cout << std::endl;
	std::cout << "Welcome to Bulls and Cows, a fun word game." << std::endl;
	std::cout << std::endl;

	std::cout << "     \\__/             __           " << std::endl;
	std::cout << "     (__)            (__)        " << std::endl;
	std::cout << "    /  \\            /  \\       " << std::endl;
	std::cout << "   |    |           |   |      " << std::endl;
	std::cout << std::endl;

	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter hidden word that I'm thinking of?" << std::endl;
	std::cout << std::endl;
	return;
}

FText GetValidGuess() 
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";

	do {																													/*switch statement nested in do while loop constantly
																															checks player's guess for validity by using these enumerators*/
		std::cout << "Try " << BCGame.GetCurrentTry() << " of " << BCGame.GetMaxTries() << ". Please enter guess : ";
		getline(std::cin, Guess);

		EGuessStatus Status = BCGame.CheckGuessValid(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Lowercase:																		
			std::cout << "Please enter your guess in lowercase.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word with no repeating letters.\n";
			break;
		default:
			return Guess;																									// assuming the guess is valid
			break;
		}

		std::cout << std::endl;

	} while (Status != EGuessStatus::OK);																					 // keep looping until we have no errors
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon() == true)
	{
		std::cout << "Congratulations! You got the correct guess! ";
	}
	else
	{
		std::cout << "You ran out of tries :( Better luck next time! ";
	}
	return;
}

bool AskToPlayAgain()																		// Whether the player wants to play again or not determines whether the program will loop 
{
	std::cout << "Do you want to play again with the same word? (Restart program for new word) (y/n)\n";
	FText Response = "";
	getline(std::cin, Response);
	std::cout << std::endl;
	return (Response[0] == 'Y') || (Response[0] == 'y');
}
