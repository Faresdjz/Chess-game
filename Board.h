/**
* Fichier declarant la classe Board et ses differentes fonctions permettant de creer le plateau d'echecs et ses attributs et de gerer l'agencement des pieces entre elles.

* \file   Board.h
* \author Fares Laadjel 2297799 et Ayoub Marfouk 2295178
* \date   21 avril 2024
* Cree le 13 avril 2024
*/

#pragma once
#include "IncludeFile.h"
#include "Square.h"

class Board {
public:
	Board();

	void addPiece(int i, int j, TYPE type, bool color);

	void removePiece(int i, int j, TYPE type);

	void updateGame(std::shared_ptr<Square> square);

	void movePiece(int oldX, int oldY, int newX, int newY);

	bool checkGameSituation(bool color);

	int getnKings() {
		return nKings_;
	}

	int getWasEmpty() {
		return wasEmpty_;
	}

	chesslogic::Piece getSavedItem() {
		return savedItem_;
	}

	std::shared_ptr<Square> getItem(int i, int j) {
		return items[i][j];
	}

private:
	int nKings_ = 0;
	int nBishops_ = 0;
	int nRooks_ = 0;
	bool wasEmpty_ = true;
	chesslogic::Piece savedItem_;
	std::shared_ptr<Square> items[8][8];
};
