#pragma once
#include "IncludeFile.h"
#include "Square.h"

class Board {
public:
	Board();

	void addPiece(int i, int j, TYPE type, bool color);

	void updateGame(Square* square);

	void movePiece(int oldX, int oldY, int newX, int newY);

	int nKings=0;
	int nBishops=0;
	int nRooks=0;
	Square* items[8][8];
};
