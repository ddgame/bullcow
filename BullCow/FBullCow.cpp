#include "FBullCow.h"
#include <map>

#define TMap std::map

constexpr int MAX_GUESSES = 5;
const FString HIDDEN_WORD = "planet";

FBullCow::FBullCow()
{
	Reset();
}

void FBullCow::Reset()
{
	Won = false;
	MyMaxTries = MAX_GUESSES;
	MyCurrentTry = 1;
	MyHiddenWord = HIDDEN_WORD;
}

int32 FBullCow::GetMaxTries() const
{
	TMap<int32, int32> WordLengthMaxTries{ {3, 5}, {4, 5}, {5, 5}, {6, 3} };

	return WordLengthMaxTries[GetHiddenWordLength()];
}

int32 FBullCow::GetCurrentTry() const
{
	return MyCurrentTry;
}

FBullCowCount FBullCow::SubmitGuess(FString Guess)
{
	NextTry();
	return CountBullCow(Guess);
}

void FBullCow::NextTry()
{
	MyCurrentTry++;
}

FBullCowCount FBullCow::CountBullCow(FString Guess)
{
	// setup return structure
	FBullCowCount BullCowCount;

	// check the guess againts the hidden word
	int32 GuessCount = Guess.length();
	for (int32 i = 0; i < MyHiddenWord.length(); i++) {
		// if Guess shorter then hidden word, end
		if (i > GuessCount) {
			break;
		}
		if (MyHiddenWord[i] == Guess[i]) {

			BullCowCount.Bulls++;
		} 
		else if (MyHiddenWord.find(Guess[i]) != std::string::npos) {
			BullCowCount.Cows++;
		}
	}

	if (BullCowCount.Bulls == GetHiddenWordLength())
		Won = true;

	return BullCowCount;
}

bool FBullCow::IsIsogram(FString Word) const
{
	bool isogram = true;
	/*for (int32 i = 0; i < Word.length(); i++) {
		size_t count = std::count(Word.begin(), Word.end(), Word[i]);
		if (count != 1) {
			isogram = false;
			break;
		}
	}*/

	TMap<char,bool> LetterSeen;
	
	for (auto Letter : Word) {
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) {
			isogram = false;
			break;
		}
		else {
			LetterSeen[Letter] = true;
		}
	}
	return isogram;
}

bool FBullCow::IsLowerCase(FString Word) const
{
	bool lower = true;

	for (auto Char : Word) {
		if (!islower(Char)) {
			lower = false;
			break;
		}
	}

	return lower;
}

bool FBullCow::IsWon() const
{
	return Won;
}

int32 FBullCow::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}

EWordStatus FBullCow::CheckGuessValidity(FString Guess) const
{
	EWordStatus status = EWordStatus::OK;
	if (Guess.length() != GetHiddenWordLength())
		status = EWordStatus::Wrong_Length;
	else if (!IsIsogram(Guess))
		status = EWordStatus::Not_Isogram;
	else if (!IsLowerCase(Guess))
		status = EWordStatus::Not_Lowercase;
	return status;
}