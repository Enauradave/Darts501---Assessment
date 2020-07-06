#include "Game.h"
#include <iostream>
#include <time.h>
#include "Player.h"


Game::Game()
{
	noOfMatches = 10;
	accJoe = 81;
	accSid = 79;
	playerTurn = 0;
	joeWins = 0;
	sidWins = 0;
	joeBusts = 0;
	sidBusts = 0;
	joeFrq = 0;
	sidFrq = 0;
	bust = false;
}

Game::~Game()
{
}

void Game::Play()
{
	srand(time(NULL));

	Player Joe(accJoe, false, "Joe", 501); // initialize Joe + accuracy, name, score
	Player Sid(accSid, false, "Sid", 501); // initialize Sid + accuracy, name, score

	int score = 0;
	int throw_score = 0;
	int new_score = 0;
	int set_score = 0;
	int initThrowJ = 0;
	int initThrowS = 0;

	// Looping for 10,000 matches
	for (int i = 0; i < noOfMatches; i++)
	{
		int joeThrows = 0;
		int sidThrows = 0;

		Joe.SetThrowsLeft(joeThrows);
		Sid.SetThrowsLeft(sidThrows);
		Joe.SetScore(501);
		Sid.SetScore(501);

		Joe.SetHasWon(false);
		Sid.SetHasWon(false);

		// Play a match. 
		while ((Joe.GetHasWon() == false) && (Sid.GetHasWon() == false))
		{
			while (initThrowJ != initThrowS)
			{
				// who goes first?
				initThrowJ = Joe.ThrowBull(accJoe);
				initThrowS = Sid.ThrowBull(accSid);

				if (initThrowJ > initThrowS)
				{
					playerTurn = 1;
				}
				else if (initThrowS > initThrowJ)
				{
					playerTurn = 2;
				}
			}

			// if it's Joe's turn throw three darts
			while (playerTurn == 0)
			{
				if (Joe.GetScore() != 0)
				{
					joeThrows = 3;
					throw_score = 0;
					Joe.SetThrowsLeft(joeThrows);
					cout << "Joe's turn\n";

					// while Joe's turn
					while (Joe.GetThrowsLeft() > 1)
					{
						// Throw a dart based on some logic
						if ((Joe.GetScore() == 50) && (joeThrows == 1))
						{
							throw_score = Joe.ThrowBull(accJoe);
						}
						if ((Joe.GetScore() <= 40) && (joeThrows == 1))
						{
							throw_score = Joe.ThrowDouble(((Joe.GetScore() - set_score) / 2));
						}
						// if score is less then 62, figure out what single is needed to make it possible to throw a double to win on last throw.
						else if ((Joe.GetScore() - set_score) < 62)
						{
							throw_score = Joe.ThrowSingle((Joe.GetScore() - set_score)); //this overflows because of the ThrowSingle player function, the d being passed in to the function.
							// and goes out of bounds as d should only be a maximum value of 20 so when going out of bounds returns a number like 85million.
						}
						else
						{
							throw_score = Joe.ThrowTreble(20, accJoe);
							if (throw_score > 60)
							{
								throw_score = 60;
							}
						}

						cout << "Throw: " << throw_score << "\n";

						// What is the running total this set?
						set_score = set_score + throw_score;

						// Display score and points accumulated in this set
						cout << "Joe's score: " << Joe.GetScore() << " This set: " << set_score << "\n";

						score = Joe.GetScore();
						if ((score - set_score) <= 1)
						{
							cout << "BUST! \n";
							joeBusts++;
							set_score = 0;
							Joe.SetThrowsLeft(joeThrows = 0);
							playerTurn = 1;
						}
						else 
						{
							// reduce throw's left.
							Joe.SetThrowsLeft(joeThrows--);
							cout << "Throw's left: " << joeThrows << "\n";
						}

					}
					// when out of throws do
					if (joeThrows <= 0)
					{
						score = Joe.GetScore();
						new_score = score - set_score;

						if (new_score < 1)
						{
							cout << "BUST! \n";
							joeBusts++;
							playerTurn = 1;
						}
						else if (new_score == 0)
						{
							set_score = 0;
							Joe.SetHasWon(true);
						}
						else
						{
							Joe.SetScore(new_score);
							playerTurn = 1; //change who's turn it is.
							set_score = 0;
						}

						cout << "" << "\n";

					}
				}
			}
			while (playerTurn == 1)
			{
				if (Sid.GetScore() != 0)
				{
					sidThrows = 3;
					Sid.SetThrowsLeft(sidThrows);
					cout << "Sid's turn \n";

					// while sid's turn
					while (Sid.GetThrowsLeft() > 1)
					{
						// Throw a dart
						if ((Sid.GetScore() == 50) && (sidThrows == 1))
						{
							throw_score = Sid.ThrowBull(accSid);
						}
						if ((Sid.GetScore() <= 40) && (sidThrows == 1))
						{
							throw_score = Sid.ThrowDouble(((Sid.GetScore() - set_score) / 2));
						}
						else if ((Sid.GetScore() - set_score) < 62)
						{
							throw_score = Sid.ThrowSingle((Sid.GetScore() - set_score));//this overflows because of the ThrowSingle player function, the d being passed in to the function.
							// and goes out of bounds as d should only be a maximum value of 20 so when going out of bounds returns a number like 85million.
						}
						else
						{
							throw_score = Sid.ThrowTreble(20, accSid);
							if (throw_score > 60)
							{
								throw_score = 60;
							}
						}

						cout << "Throw: " << throw_score << "\n";

						// What is the running total this set?
						set_score = set_score + throw_score;

						// Display score and points accumulated in this set
						cout << "Sid's score: " << Sid.GetScore() << " This set: " << set_score << "\n";

						score = Sid.GetScore();
						if ((score - set_score) <= 1)
						{
							cout << "BUST! \n";
							sidBusts++;
							set_score = 0;
							Sid.SetThrowsLeft(sidThrows = 0);
							playerTurn = 0;
						}
						else 
						{
						// reduce throw's left.
						Sid.SetThrowsLeft(sidThrows--);
						cout << "Throw's left: " << sidThrows << "\n";
						}
						
					}

					// when out of throws do
					if (sidThrows <= 0)
					{
						score = Sid.GetScore();
						new_score = score - set_score;

						if (new_score < 1)
						{
							cout << "BUST! \n";
							sidBusts++;
							set_score = 0;
							playerTurn = 0;

						}
						else if (new_score == 0)
						{
							set_score = 0;
							Sid.SetHasWon(true);
						}
						else
						{
							Sid.SetScore(new_score);
							playerTurn = 0; //change who's turn it is.
							set_score = 0;
						}

						cout << "" << "\n";

					}
				}
			}
		}
		// collect the data of the match
		if(Joe.GetHasWon() == true)
		{
			joeWins++;
			cout << " Joe's Wins: " << joeWins << "\n";
			cout << " Sid's Wins: " << sidWins << "\n";
			
		}
		else if (Sid.GetHasWon() == true)
		{
			sidWins++;
			cout << " Joe's Wins: " << joeWins << "\n";
			cout << " Sid's Wins: " << sidWins << "\n";
		}
	}
	// display the collected data
	Display();
}

// displaying the data collected in the simulation
void Game::Display()
{
	joeFrq = ((joeWins / noOfMatches) * 100);
	sidFrq = ((sidWins / noOfMatches) * 100);

	cout << "Number of wins - Joe: " << joeWins << "  Sid: " << sidWins << "\n";
	cout << "Number of busts - Joe: " << joeBusts << "  Sid: " << sidBusts << "\n";
	cout << "Win Frequencies - Joe: " << joeFrq << "%  Sid: " << sidFrq << "%\n";
}
