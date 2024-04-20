#pragma once
#include "IncludeFile.h"
#include "Piece.h"

class Square {
public:
	Square() {};

	Square(int i, int j)
		: i_(i), j_(j){};

	void setPosition(int i, int j) {
		i_ = i;
		j_ = j;
	}


	bool isPlayable(vector <pair<int, int>> possiblePosition);

	chesslogic::Piece* piece = nullptr;
	int i_ = -1;
	int j_ = -1;
};