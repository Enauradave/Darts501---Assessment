#pragma once
class Game
{
public:
	Game();
	~Game();

	void Play(); // Plays the simulation
	void Display(); // Display the results

protected:

	int noOfMatches;
	int setsWonJoe;
	int setsWonSid;
	int accJoe;
	int accSid;
	int playerTurn;
	int joeWins;
	int sidWins;
	int joeWinsTotal;
	int sidWinsTotal;
	int joeBusts;
	int sidBusts;
	int counter[14] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	float freq;
	bool bust;
};

