#pragma once
class Board
{

public:
	Board();
	~Board();

	int GetScoreAtPosition(int x, int y);

	void SetBoard();

protected:
	int bd[2][21];

};