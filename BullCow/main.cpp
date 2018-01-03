/* This is the console executable, that makes use of the bullcow class

This acts as the view in MVC pattern and is responsible for all user interaction.
For game logic see the FBullGame class.
*/
#include <iostream>
#include <string>
#include "FBullCow.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetGuess();
bool AskToPlayAgain();
void PrintBullCowCount(FBullCowCount BullCowCount);
void PrintError(FText msg);
void PrintGameSummary();

FBullCow Game = FBullCow();

int main()
{
	do {
		PrintIntro();
		PlayGame();		
	} while (AskToPlayAgain());

	return 0;
}

void PlayGame()
{
	Game.Reset();

	while (!Game.IsWon() && Game.GetCurrentTry() <= Game.GetMaxTries()) {
		FText Guess = GetGuess();
		// submit guess to the game
		FBullCowCount BullCowCount = Game.SubmitGuess(Guess);
		// print32 bulls and cows
		PrintBullCowCount(BullCowCount);
		std::cout << std::endl;
	}

	PrintGameSummary();
}

// int32roduce the game
void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word guessing game.\n";
	std::cout << "Can you guess " << Game.GetHiddenWordLength() << " letter isogram I'am thinking of?\n";
	std::cout << "You have " << Game.GetMaxTries() << " tries.\n";
}

// get a guess from player
FText GetGuess()
{
	EWordStatus status = EWordStatus::Invalid;
	FText Guess = "";

	do {
		int32 CurrentTry = Game.GetCurrentTry();
		std::cout << "You have " << Game.GetMaxTries() - CurrentTry + 1 << " tries left. Enter you guess: ";
		std::getline(std::cin, Guess);

		// validate guess
		status = Game.CheckGuessValidity(Guess);
		switch (status) {
		case EWordStatus::Wrong_Length:
			PrintError("Guess needs to be " + std::to_string(Game.GetHiddenWordLength()) + " character long");
			break;
		case EWordStatus::Not_Isogram:
			PrintError("Guess is not isogram");
			break;
		case EWordStatus::Not_Lowercase:
			PrintError("Guess is not lowercase");

		}
	} while (status != EWordStatus::OK);

	return Guess;
}

bool AskToPlayAgain()
{
	FText playAgain = "";
	std::cout << "Do you want to play again (y/n)?";
	std::getline(std::cin, playAgain);
	return playAgain[0] == 'y' || playAgain[0] == 'Y';
}

void PrintBullCowCount(FBullCowCount BullCowCount) {
	std::cout << "Bulls: " << BullCowCount.Bulls << " Cows: " << BullCowCount.Cows << std::endl;
}

void PrintError(FText msg) {
	std::cout << "Error: " << msg << std::endl << std::endl;
}

void PrintGameSummary() {
	FText summary = "";
	if (Game.IsWon())
		summary = "CONGRATULATIONS YOU WIN!";
	else
		summary = "Sorry, better luck next time.";
	std::cout << summary << std::endl;
}