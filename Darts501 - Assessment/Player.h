#pragma once
#include <string>

using namespace std;

class Player
{

public:
	Player(int accuracy, bool won, string name = "", int score = 501);
	~Player();

	string GetName();
	void SetName(string name);
	void SetScore(int score);
	void SubScore(int points);
	int GetScore();
	void SetAccuracy(int accuracy);
	int GetAccuracy();
	int ThrowBull(int p);
	int ThrowTreble(int d, int p);
	int ThrowDouble(int d);
	int ThrowSingle(int d);
	int GetThrowsLeft();
	void SetThrowsLeft(int throws);
	bool GetHasWon();
	void SetHasWon(bool won);

protected:
	int playerScore;
	int playerAccuracy;
	int throwsLeft;
	string playerName;
	bool hasWon = false;
};

