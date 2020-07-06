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
	int accJoe;
	int accSid;
	int playerTurn;
	int joeWins;
	int sidWins;
	int joeBusts;
	int sidBusts;
	int joeFrq;
	int sidFrq;
	bool bust;
};

