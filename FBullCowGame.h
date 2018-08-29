#pragma once
#include <string>

using FString = std::string;		
using int32 = int; 

struct FBullCowCount												// data structure - like a class but all members are public, used for holding simple data types i.e. bulls and cows 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus												// user defined data type with constants - scope to the whole file and including files - used here for error checking
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame {
public:
	
	FBullCowGame();													 // constructor

	void Reset();									
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;

	EGuessStatus CheckGuessValid(FString) const; 
	FBullCowCount SubmitValidGuess(FString Guess); 

private: 

	int32 MyCurrentTry = 1;
	FString MyHiddenWord; 
	bool bGameIsWon = false;
	FString NewHiddenWord();

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};