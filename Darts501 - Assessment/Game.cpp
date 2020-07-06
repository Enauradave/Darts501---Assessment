#include "Game.h"
#include <iostream>
#include <time.h>
#include "Player.h"


Game::Game()
{
	noOfMatches = 1;
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
						/*--------------------------------------THROWING LOGIC STARTS-----------------------------------------------*/
						if (Joe.GetScore() >= 63) //if score is over 183.
						{
							throw_score = Joe.ThrowTreble(20, accJoe); //throw for treble 20.
							if (throw_score > 60) // this block of code exists because sometimes the ThrowTreble function returned values higher than 60.
							{
								throw_score = 60;
							}
						}
						else if ((Joe.GetScore() == 50) && (joeThrows == 1)) // If player can throw a bullseye to win try.
						{
							throw_score = Joe.ThrowBull(accJoe);
						}
						else if (Joe.GetScore() <= 40 && (Joe.GetScore() % 2 == 0) && (joeThrows == 1)) // If player can throw a Double to win try
						{
							throw_score = Joe.ThrowDouble(Joe.GetScore() / 2);
						}
						else if (Joe.GetScore() <= 40 && (Joe.GetScore() % 2 == 1) && (joeThrows == 2)) // If player can throw a Single to make it possible to win on next throw try.
						{
							if (Joe.GetScore() > 3) // if greater than 3 throw for a 3
							{
								throw_score = Joe.ThrowSingle(3);
							}
							else
							{
								throw_score = Joe.ThrowSingle(1); // else throw for a 1
							}
						}
						else if ((Joe.GetScore() - set_score) < 60 && (Joe.GetScore() - set_score) > 40) // If player's score is less than 60 but greater than 40 throw a single.
						{
							throw_score = Joe.ThrowSingle((Joe.GetScore() - set_score - 40));  // to bring it below 40.
						}
						else if ((Joe.GetScore() - set_score) > 63 && joeThrows == 3) // if score is above 63 and has three throws left.
						{
							throw_score = Joe.ThrowTreble(20, accJoe); //throw for treble 20.
							if (throw_score > 60) // this block of code exists because sometimes the ThrowTreble function returned values higher than 60.
							{
								throw_score = 60;
							}
						}
						else if ((Joe.GetScore() - set_score) < 63 && (Joe.GetScore() % 3 == 1))
						{
							throw_score = Joe.ThrowTreble(((Joe.GetScore() / 3) + 2), accJoe);
						}
						else // else throw for a 1.
						{
							throw_score = Joe.ThrowSingle(1);
						}

						/*-----------------------THROWING LOGIC ENDS---------------------------------*/


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
						/*THROWING LOGIC STARTS*/

						if (Sid.GetScore() > 63)
						{
							throw_score = Sid.ThrowTreble(20, accSid); //throw for treble 20.
							if (throw_score > 60) // this block of code exists because sometimes the ThrowTreble function returned values higher than 60.
							{
								throw_score = 60;
							}
						}
						else if ((Sid.GetScore() == 50) && (sidThrows == 1))
						{
							throw_score = Sid.ThrowBull(accSid);
						}
						else if (Sid.GetScore() <= 40 && (Sid.GetScore() % 2 == 0) && (sidThrows == 1))
						{
							throw_score = Sid.ThrowDouble(Sid.GetScore() / 2);
						}
						else if (Sid.GetScore() < 40 && (Sid.GetScore() % 2 == 1) && (sidThrows > 2))
						{
							if (Sid.GetScore() > 5)
							{
								throw_score = Sid.ThrowSingle(3);
							}
							else
							{
								throw_score = Sid.ThrowSingle(1);
							}

						}
						else if (Sid.GetScore() < 40 && (Sid.GetScore() % 2 == 1) && (sidThrows > 1))
						{
							if (Sid.GetScore() > 3)
							{
								throw_score = Sid.ThrowSingle(3);
							}
							else
							{
								throw_score = Sid.ThrowSingle(1);
							}

						}
						else if ((Sid.GetScore() - set_score) < 60 && (Sid.GetScore() - set_score) > 40)
						{
							throw_score = Sid.ThrowSingle((Sid.GetScore() - set_score - 40));
						}
						else if ((Sid.GetScore() - set_score) > 63 && sidThrows == 3) // if score is above 63 and has three throws left.
						{
							throw_score = Sid.ThrowTreble(20, accSid); //throw for treble 20.
							if (throw_score > 60) // this block of code exists because sometimes the ThrowTreble function returned values higher than 60.
							{
								throw_score = 60;
							}
						}
						else if ((Sid.GetScore() - set_score) < 63 && (Sid.GetScore() % 3 == 1))
						{
							throw_score = Sid.ThrowTreble(((Sid.GetScore() / 3) + 2), accSid);
						}
						else // else throw for a 1.
						{
							throw_score = Sid.ThrowSingle(1);
						}

						/*THROWING LOGIC ENDS*/

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
