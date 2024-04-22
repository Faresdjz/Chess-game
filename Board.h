/**
* Fichier d�clarant la classe Board et ses diff�rentes fonctions permettant de cr�er le plateau d'�checs et ses attributs et de g�rer l'agencement des pi�ces entre elles.

* \file   Board.h
* \author Fares Laadjel 2297799 et Ayoub Marfouk 2295178
* \date   21 avril 2024
* Cr�� le 13 avril 2024
*/

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
