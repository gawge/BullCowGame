#include "FBullCowGame.h"
#include <map>
#include <ctime>												// time lib used for "random" value generation
#include <cstdlib>												// lib that includes rand and srand func
#define TMap std::map

using int32 = int;	

int32 FBullCowGame::GetMaxTries() const 
{
	TMap <int32, int32> WordLengthToMaxTries{ {6,10}, {4,8}, {5,9}, {7,11}, {8,12} };	// map with word length as key and max tries as element
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

int32 FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const
{	
	return MyHiddenWord.length();		
}

bool FBullCowGame::IsGameWon() const
{
	return bGameIsWon;						// the program is dependant on this variable as it decides whether the gameplay loop runs or not
}

FBullCowGame::FBullCowGame()
{
	Reset();							// constructor - when instantiated, the game is reset
}

void FBullCowGame::Reset()							// member variables of the class that determine game state are reset to these values when called
{
	MyCurrentTry = 1;
	MyHiddenWord = NewHiddenWord();
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValid(FString Guess) const
{
	if (!IsIsogram(Guess))											// if guess isn't an isogram then return error
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess))									// if guess isn't all lowercase return error
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength())				// if guess isn't right length then return error
	{
		return EGuessStatus::Wrong_Length;			
	}
	else
	{
		return EGuessStatus::OK;									// if no errors then guess is valid
	}
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) 
{
	MyCurrentTry++;										
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length();
	
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)		/* in each iteration of this loop, another 
																		loop runs to check every letter of the 
																		guess against each letter of the hidden word */
	{													
		for (int32 GChar = 0; GChar < WordLength; GChar++)		
		{
			if (Guess[GChar] == MyHiddenWord[MHWChar])				// checking that the letters match 
			{
				if (MHWChar == GChar)								// checking that the letters are in the same place
				{
					BullCowCount.Bulls++;			
				}
				else 
				{								
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength)							// if all letters are bulls then the game is won
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}

	return BullCowCount;
}

FString FBullCowGame::NewHiddenWord()
{
	TMap <int32, FString> KeyToHiddenWord{ {1,"planet"},{2,"debt"},{3,"scale"},{4,"glacier"},{5,"launcher"}, {6, "hack"}, {7, "knife"}, {8, "radius"}, {9, "tendril"}, {10, "obstacle"} };

	int no_of_numbers = 10;
	int first_number = 1;
																			/*MY FAVOURITE BIT - this function creates a map with our hidden words as the elements
																			then generates a "random" value 1-10 which represents a key in the map*/ 
	std::srand(std::time(0));
																			/*the value is generated using the rand func and i used the local system time as the seed
																					for the number generation*/
	int random_number = std::rand() % no_of_numbers + first_number;			//the func rand returns MAX_RAND, mod the range of the map keys, added to the value of the first key in the map 

	for (int i = 1; i <= 1; i++) {											// the for loop iterates once at the start of the program, generating one value
		int random_number = std::rand() % no_of_numbers + first_number;
	}


	return KeyToHiddenWord[random_number];									// the func returns the element of the map indexed by the "randomly" generated value
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() < 2) {return true;} 									// treat 0 and 1 letter words as isograms

	TMap<char, bool> LetterSeen;											//setup map
	for (auto Letter : Word)												// for all letters of the word
	{
		Letter = tolower(Letter);											// store only lowercase letters
		if (LetterSeen[Letter]) { return false; }							// it is not an isogram
		else if (!LetterSeen[Letter]) {LetterSeen[Letter] = true;}			// add letter to map
	}
	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto WLetter : Word)								// for the letters in the word
	{
		if (!islower(WLetter))								// if not a lowercase letter
		{
			return false;									// return false
		}
	}
	return true;											// otherwise return true
}


