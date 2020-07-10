#include "Game.h"
#include <iostream>
#include <time.h>
#include "Player.h"


Game::Game()
{
	noOfMatches = 10000;
	setsWonJoe = 0;
	setsWonSid = 0;
	accJoe = 81;
	accSid = 79;
	playerTurn = 0;
	joeWins = 0;
	sidWins = 0;
	joeWinsTotal = 0;
	sidWinsTotal = 0;
	joeBusts = 0;
	sidBusts = 0;
	freq = 0;
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

	cout << "Joe   :    Sid                           Frequency\n";

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
					//cout << "Joe's turn\n";

					// while Joe's turn
					while (Joe.GetThrowsLeft() > 1)
					{
						/*--------------------------------------THROWING LOGIC STARTS-----------------------------------------------*/
						
						
						if (Sid.GetScore() - set_score == 2)
						{
							throw_score = Sid.ThrowDouble(1);
						}
						else if ((Joe.GetScore() - set_score) < 20 && ((Joe.GetScore() - set_score) % 2 == 1) && (joeThrows == 3))
						{
							throw_score = Joe.ThrowSingle(1);
						}
						else if ((Joe.GetScore() - set_score == 181) && (joeThrows == 3))
						{
							throw_score = Joe.ThrowTreble(19, accJoe);
						}
						// if score is greater than 69 and has more than 1 throw left 
						if ((Joe.GetScore() - set_score > 199) && (joeThrows > 1))
						{
							//aim for 20
							throw_score = Joe.ThrowTreble(20, accJoe);
						}
						// if score is between 51 and 70 and have 2 throws left
						else if ((Joe.GetScore() - set_score) <= 70 && (Joe.GetScore() - set_score) > 50 && (joeThrows == 2))
						{
							// aim for the single to take them to 50.
							throw_score = Joe.ThrowSingle((Joe.GetScore() - set_score) - 50);
						}
						// if score is 50 and  has 1 throw left
						else if ((Joe.GetScore() - set_score == 50) && (joeThrows == 1))
						{
							// aim for bull
							throw_score = Joe.ThrowBull(accJoe);
						}
						// if score is less than or equal to 40 and is an even number and only has 1 throw left
						else if ((Joe.GetScore() - set_score <= 40) && ((Joe.GetScore() - set_score) % 2 == 0) && (joeThrows == 1))
						{
							// aim for the double that would win
							throw_score = Joe.ThrowDouble((Joe.GetScore() - set_score) / 2);
						}
						// if score is less or equal to 41 and is an odd number and only has 1 throw left
						else if ((Joe.GetScore() - set_score <= 41) && ((Joe.GetScore() - set_score) % 2 == 1) && (joeThrows == 1))
						{
							// is more than 20
							if ((Joe.GetScore() - set_score) > 20)
							{
								// aim for 3
								throw_score = Joe.ThrowSingle(3);
							}
							else
							{
								// aim for 1
								throw_score = Joe.ThrowSingle(1);
							}
						}
						// if score is less than 50 and has 2 or more throws
						else if ((Joe.GetScore() - set_score) < 50 && (joeThrows >= 2))
						{
							// if greater than 40 and even
							if (((Joe.GetScore() - set_score) > 40) && (Joe.GetScore() - set_score) % 2 == 0)
							{
								// aim for 12
								throw_score = Joe.ThrowSingle(12);
							}
							else if (((Joe.GetScore() - set_score) > 40) && (Joe.GetScore() - set_score) % 2 == 1)
							{
								// aim for 11
								throw_score = Joe.ThrowSingle(11);
							}
							else
							{
								// aim for 1
								throw_score = Joe.ThrowSingle(1);
							}
						}
						else
						{
							throw_score = Joe.ThrowTreble(20, accJoe);
						}

						/*-----------------------THROWING LOGIC ENDS---------------------------------*/


						//cout << "Throw: " << throw_score << "\n";

						// What is the running total this set?
						set_score = set_score + throw_score;

						// Display score and points accumulated in this set
						//cout << "Joe's score: " << Joe.GetScore() << " This set: " << set_score << "\n";

						score = Joe.GetScore();
						if (score == 2 && throw_score == 2 && joeThrows > 0)
						{
							set_score = 0;
							Joe.SetHasWon(true);
						}
						else if ((score - set_score) <= 1 && (score - set_score) != 0 && joeThrows > 0)
						{
							//cout << "BUST! \n";
							joeBusts++;
							set_score = 0;
							Joe.SetThrowsLeft(joeThrows = 0);
							playerTurn = 1;
						}
						else
						{
							// reduce throw's left.
							Joe.SetThrowsLeft(joeThrows--);
							//cout << "Throw's left: " << joeThrows << "\n";
						}

					}
					// when out of throws do
					if (joeThrows <= 0)
					{
						score = Joe.GetScore();
						new_score = score - set_score;

						if (new_score == 1)
						{
							//cout << "BUST! \n";
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

						//cout << "" << "\n";

					}
				}
			}
			while (playerTurn == 1)
			{
				if (Sid.GetScore() != 0)
				{
					sidThrows = 3;
					Sid.SetThrowsLeft(sidThrows);
					//cout << "Sid's turn \n";

					// while sid's turn
					while (Sid.GetThrowsLeft() > 1)
					{
						/*-----------------------SID'S THROWING LOGIC STARTS--------------------*/

						// writing new logic here
						if (Sid.GetScore() - set_score == 2)
						{
							throw_score = Sid.ThrowDouble(1);
						}					
						else if ((Sid.GetScore() - set_score) < 20 && ((Sid.GetScore() - set_score) % 2 == 1) && (sidThrows == 3))
						{
							throw_score = Sid.ThrowSingle(1);
						}
						else if ((Sid.GetScore() - set_score == 181) && (sidThrows == 3))
						{
							throw_score = Sid.ThrowTreble(19, accSid);
						}
						// if score is greater than 69 and has more than 1 throw left 
						if ((Sid.GetScore() - set_score > 199) && (sidThrows > 1))
						{
							//aim for 20
							throw_score = Sid.ThrowTreble(20, accSid);
						}
						// if score is between 51 and 70 and have 2 throws left
						else if ((Sid.GetScore() - set_score) <= 70 && (Sid.GetScore() - set_score) > 50 && (sidThrows == 2))
						{
							// aim for the single to take them to 50.
							throw_score = Sid.ThrowSingle((Sid.GetScore() - set_score) - 50);
						}
						// if score is 50 and  has 1 throw left
						else if ((Sid.GetScore() - set_score == 50) && (sidThrows == 1))
						{
							// aim for bull
							throw_score = Sid.ThrowBull(accSid);
						}
						// if score is less than or equal to 40 and is an even number and only has 1 throw left
						else if ((Sid.GetScore() - set_score <= 40) && ((Sid.GetScore() - set_score) % 2 == 0) && (sidThrows == 1))
						{
							// aim for the double that would win
							throw_score = Sid.ThrowDouble((Sid.GetScore() - set_score) / 2);
						}
						// if score is less or equal to 41 and is an odd number and only has 1 throw left
						else if ((Sid.GetScore() - set_score <= 41) && ((Sid.GetScore() - set_score) % 2 == 1) && (sidThrows == 1))
						{
							// is more than 20
							if ((Sid.GetScore() - set_score) > 20)
							{
								// aim for 3
								throw_score = Sid.ThrowSingle(3);
							}
							else
							{
								// aim for 1
								throw_score = Sid.ThrowSingle(1);
							}
						}
						// if score is less than 50 and has 2 or more throws
						else if ((Sid.GetScore() - set_score) < 50 && (sidThrows >= 2))
						{
							// if greater than 40 and even
							if (((Sid.GetScore() - set_score) > 40) && (Sid.GetScore() - set_score) % 2 == 0)
							{
								// aim for 12
								throw_score = Sid.ThrowSingle(12);
							}
							else if (((Sid.GetScore() - set_score) > 40) && (Sid.GetScore() - set_score) % 2 == 1)
							{
								// aim for 11
								throw_score = Sid.ThrowSingle(11);
							}
							else
							{
								// aim for 1
								throw_score = Sid.ThrowSingle(1);
							}
						}
						else
						{
							throw_score = Sid.ThrowTreble(20, accSid);
						}

						/*---------------------THROWING LOGIC ENDS-----------------------*/

						//cout << "Throw: " << throw_score << "\n";

						// What is the running total this set?
						set_score = set_score + throw_score;

						// Display score and points accumulated in this set
						//cout << "Sid's score: " << Sid.GetScore() << " This set: " << set_score << "\n";

						score = Sid.GetScore();
						if (score == 2 && throw_score == 2 && sidThrows > 0)
						{
							set_score = 0;
							Sid.SetHasWon(true);
						}
						if ((score - set_score) <= 1 && (score - set_score) != 0 && sidThrows > 0)
						{
							//cout << "BUST! \n";
							sidBusts++;
							set_score = 0;
							Sid.SetThrowsLeft(sidThrows = 0);
							playerTurn = 0;
						}
						else 
						{
							// reduce throw's left.
							Sid.SetThrowsLeft(sidThrows--);
							//cout << "Throw's left: " << sidThrows << "\n";
						}
						
					}

					// when out of throws do
					if (sidThrows <= 0)
					{
						score = Sid.GetScore();
						new_score = score - set_score;

						if (new_score == 1)
						{
							//cout << "BUST! \n";
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

						//cout << "" << "\n";

					}
				}
			}
		}
		// collect the data of the matches
		if(Joe.GetHasWon() == true)
		{
			joeWins++;
			joeWinsTotal++;

			// if wins equals 7 compare scores through if statements increment the element in the correct array location and reset the Win counters to 0.
			if (joeWins == 7 && sidWins == 0)
			{
				counter[0]++;
				setsWonJoe++;
				joeWins = 0;
				sidWins = 0;
			}
			else if (joeWins == 7 && sidWins == 1)
			{
				counter[1]++;
				setsWonJoe++;
				joeWins = 0;
				sidWins = 0;
			}
			else if (joeWins == 7 && sidWins == 2)
			{
				counter[2]++;
				setsWonJoe++;
				joeWins = 0;
				sidWins = 0;
			}
			else if (joeWins == 7 && sidWins == 3)
			{
				counter[3]++;
				setsWonJoe++;
				joeWins = 0;
				sidWins = 0;
			}
			else if (joeWins == 7 && sidWins == 4)
			{
				counter[4]++;
				setsWonJoe++;
				joeWins = 0;
				sidWins = 0;
			}
			else if (joeWins == 7 && sidWins == 5)
			{
				counter[5]++;
				setsWonJoe++;
				joeWins = 0;
				sidWins = 0;
			}
			else if (joeWins == 7 && sidWins == 6)
			{
				counter[6]++;
				setsWonJoe++;
				joeWins = 0;
				sidWins = 0;
			}

			//cout << " Joe's Wins: " << joeWinsTotal << "\n";
			//cout << " Sid's Wins: " << sidWinsTotal << "\n";
			
		}
		else if (Sid.GetHasWon() == true)
		{
			sidWins++;
			sidWinsTotal++;

			if (sidWins == 7 && joeWins == 0)
			{
				counter[7]++;
				setsWonSid++;
				sidWins = 0;
				joeWins = 0;
			}
			else if (sidWins == 7 && joeWins == 1)
			{
				counter[8]++;
				setsWonSid++;
				sidWins = 0;
				joeWins = 0;
			}
			else if (sidWins == 7 && joeWins == 2)
			{
				counter[9]++;
				setsWonSid++;
				sidWins = 0;
				joeWins = 0;
			}
			else if (sidWins == 7 && joeWins == 3)
			{
				counter[10]++;
				setsWonSid++;
				sidWins = 0;
				joeWins = 0;
			}
			else if (sidWins == 7 && joeWins == 4)
			{
				counter[11]++;
				setsWonSid++;
				sidWins = 0;
				joeWins = 0;
			}
			else if (sidWins == 7 && joeWins == 5)
			{
				counter[12]++;
				setsWonSid++;
				sidWins = 0;
				joeWins = 0;
			}
			else if (sidWins == 7 && joeWins == 6)
			{
				counter[13]++;
				setsWonSid++;
				sidWins = 0;
				joeWins = 0;
			}

			//cout << " Joe's Wins: " << joeWinsTotal << "\n";
			//cout << " Sid's Wins: " << sidWinsTotal << "\n";
		}
	}
	// display the collected data
	Display();
}

// displaying the data collected in the simulation
void Game::Display()
{
	cout << "  7   :    0                                 " << (float)((counter[0] / ((float)setsWonJoe + (float)setsWonSid)) * 100) << "%\n";
	cout << "  7   :    1                                 " << (float)((counter[1] / ((float)setsWonJoe + (float)setsWonSid)) * 100) << "%\n";
	cout << "  7   :    2                                 " << (float)((counter[2] / ((float)setsWonJoe + (float)setsWonSid)) * 100) << "%\n";
	cout << "  7   :    3                                 " << (float)((counter[3] / ((float)setsWonJoe + (float)setsWonSid)) * 100) << "%\n";
	cout << "  7   :    4                                 " << (float)((counter[4] / ((float)setsWonJoe + (float)setsWonSid)) * 100) << "%\n";
	cout << "  7   :    5                                 " << (float)((counter[5] / ((float)setsWonJoe + (float)setsWonSid)) * 100) << "%\n";
	cout << "  7   :    6                                 " << (float)((counter[6] / ((float)setsWonJoe + (float)setsWonSid)) * 100) << "%\n";
	cout << "  0   :    7                                 " << (float)((counter[7] / ((float)setsWonJoe + (float)setsWonSid)) * 100) << "%\n";
	cout << "  1   :    7                                 " << (float)((counter[8] / ((float)setsWonJoe + (float)setsWonSid)) * 100) << "%\n";
	cout << "  2   :    7                                 " << (float)((counter[9] / ((float)setsWonJoe + (float)setsWonSid)) * 100) << "%\n";
	cout << "  3   :    7                                 " << (float)((counter[10] / ((float)setsWonJoe + (float)setsWonSid)) * 100) << "%\n";
	cout << "  4   :    7                                 " << (float)((counter[11] / ((float)setsWonJoe + (float)setsWonSid)) * 100) << "%\n";
	cout << "  5   :    7                                 " << (float)((counter[12] / ((float)setsWonJoe + (float)setsWonSid)) * 100) << "%\n";
	cout << "  6   :    7                                 " << (float)((counter[13] / ((float)setsWonJoe + (float)setsWonSid)) * 100) << "%\n";

	cout << "Number of wins - Joe: " << joeWinsTotal << "  Sid: " << sidWinsTotal << "\n";
	//cout << "Number of busts - Joe: " << joeBusts << "  Sid: " << sidBusts << "\n";
	cout << "Sets won - Joe: " << setsWonJoe << "  Sid: " << setsWonSid << "\n";
}
