#pragma once
#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EWordStatus {
	Invalid,
	OK,
	Not_Isogram,
	Not_Lowercase,
	Wrong_Length
};

class FBullCow {
public:
	FBullCow();

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	bool IsWon() const;
	int32 GetHiddenWordLength() const;

	void Reset(); // TODO return value
	EWordStatus CheckGuessValidity(FString Guess) const;
	// counts bulls & cows and increasing turn # asuming valid guess
	FBullCowCount SubmitGuess(FString Guess);
private:
	FBullCowCount CountBullCow(FString Guess);
	void NextTry();
	bool IsIsogram(FString Word) const;
	bool IsLowerCase(FString Word) const;
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool Won;
};