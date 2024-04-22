/**
* Fichier déclarant la classe Board et ses différentes fonctions permettant de créer le plateau d'échecs et ses attributs et de gérer l'agencement des pièces entre elles.

* \file   Board.h
* \author Fares Laadjel 2297799 et Ayoub Marfouk 2295178
* \date   21 avril 2024
* Créé le 13 avril 2024
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
