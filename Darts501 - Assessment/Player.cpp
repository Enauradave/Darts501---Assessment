#include "Player.h"

Player::Player(int accuracy, bool won, string name, int score)
{
	
}

Player::~Player()
{
}

string Player::GetName()
{
	return playerName;
}

void Player::SetName(string name)
{
	playerName = name;
}

void Player::SetScore(int score)
{
	playerScore = score;
}

void Player::SubScore(int points)
{
	playerScore -= points;
}

int Player::GetScore()
{
	return playerScore;
}

void Player::SetAccuracy(int accuracy)
{
	playerAccuracy = accuracy;
}

int Player::GetAccuracy()
{
	return playerAccuracy;
}

int Player::ThrowBull(int p)
{
	//  Throw for the bull with accuracy p%  (20<p<85)

	int r = rand() % 100;

	if (r < (p - 20))
		return 50;
	else if (r < 85)
		return 25;
	else
		return 1 + rand() % 20;
}

int Player::ThrowTreble(int d, int p)
{	
	// return result of throwing for treble d with accuracy p%  (p<90)

	// Board neighbours ignoring slot zero
	int bd[2][21] = { {0,20,15,17,18,12,13,19,16,14,6,8,9,4,11,10,7,2,1,3,5},
					  {0,18,17,19,13,20,10,16,11,12,15,14,5,6,9,2,8,3,4,7,1} };

	int r = rand() % 100;

	if (r < p)
		return 3 * d;
	else if (r < 90)
		return d;
	else if (r < 93)
		return 3 * bd[0][d];
	else if (r < 96)
		return 3 * bd[1][d];
	else if (r < 98)
		return bd[0][d];
	else
		return bd[1][d];
}

int Player::ThrowDouble(int d)
{
	// return result of throwing for double d with accuracy 80%

	// Board neighbours ignoring slot zero
	int bd[2][21] = { {0,20,15,17,18,12,13,19,16,14,6,8,9,4,11,10,7,2,1,3,5},
					  {0,18,17,19,13,20,10,16,11,12,15,14,5,6,9,2,8,3,4,7,1} };
	int r = rand() % 100;

	if (r < 80)
		return 2 * d;
	else if (r < 85)
		return 0;
	else if (r < 90)
		return d;
	else if (r < 93)
		return 2 * bd[0][d];
	else if (r < 96)
		return 2 * bd[1][d];
	else if (r < 98)
		return bd[0][d];
	else
		return bd[1][d];
}

int Player::ThrowSingle(int d)
{
	// return result of throwing for single d with accuracy 88% (or 80% for the outer)

	// Board neighbours ignoring slot zero
	int bd[2][21] = { {0,20,15,17,18,12,13,19,16,14,6,8,9,4,11,10,7,2,1,3,5},
					  {0,18,17,19,13,20,10,16,11,12,15,14,5,6,9,2,8,3,4,7,1} };
	int r = rand() % 100;

	if (d == 25) {		// outer  80%
		if (r < 80)
			return 25;
		else if (r < 90)
			return 50;
		else
			return 1 + rand() % 20;
	}
	else			// 1 to 20 single
		if (r < 88)
			return d;
		else if (r < 92)
			return bd[0][d];
		else if (r < 96)
			return bd[1][d];
		else if (r < 98)
			return 3 * d;
		else
			return 2 * d;
}

int Player::GetThrowsLeft()
{
	return throwsLeft;
}

void Player::SetThrowsLeft(int throws)
{
	throwsLeft = throws;
}

bool Player::GetHasWon()
{
	return hasWon;
}

void Player::SetHasWon(bool won)
{
	hasWon = won;
}
