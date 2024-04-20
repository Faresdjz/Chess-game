#pragma once
#include "IncludeFile.h"
#include "Square.h"

class Board {
public:
	Board();

	void addPiece(int i, int j, TYPE type, bool color);

	void updateGame();

	void movePiece(int oldX, int oldY, int newX, int newY);

	int nKings;
	int nBishops;
	int nRooks;
	Square* items[8][8];
};
