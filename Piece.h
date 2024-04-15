#pragma once
#include "IncludeFile.h"
#include <string>

using namespace std;

class Square;

class Piece {
public:
	Piece(bool color, TYPE type, Square* items[8][8]);

	Piece(bool color, TYPE type, int i, int j, Square* items[8][8]);

	void setPosition(int i, int j, Square* items[8][8]) {
		i_ = i;
		j_ = j;
		setPossiblePosition(items);
	}

	void setPossiblePosition(Square* items[8][8]);

	bool color;
	TYPE type;
	int i_;
	int j_;
	vector<pair<int, int>> possiblePosition;

};
