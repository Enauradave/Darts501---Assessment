#include "Board.h"

Board::Board()
{
	SetBoard();
}

Board::~Board()
{
}

int Board::GetScoreAtPosition(int x, int y)
{
	return bd[x][y];
}

void Board::SetBoard()
{
	const int X = 2;
	const int Y = 21;
	int bd[X][Y] = { { 0, 20, 15, 17, 18, 12, 13, 19, 16, 14, 6, 8, 9, 4, 11, 10, 7, 2, 1, 3, 5 },
					 { 0, 18, 17, 19, 13, 20, 10, 16, 11, 12, 15, 14, 5, 6, 9, 2, 8, 3, 4, 7, 1 } };

	for (int i = 0; i < X; i++)
	{
		for (int j = 0; j < Y; j++) 
		{
			bd[i][j] = bd[i][j];
		}
	}
}
