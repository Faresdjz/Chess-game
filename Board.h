/**
* Fichier declarant la classe Board et ses differentes fonctions permettant de creer le plateau d'echecs et ses attributs et de gerer l'agencement des pieces entre elles.

* \file   Board.h
* \author Fares Laadjel 2297799 et Ayoub Marfouk 2295178
* \date   3 mai 2024
* Cree le 13 avril 2024
*/

#pragma once
#include "IncludeFile.h"
#include "Square.h"

class Board {
public:
	Board();

	void addPiece(int i, int j, Type type, bool color);

	void removePiece(int i, int j, Type type);

	void updateGame(std::shared_ptr<Square> square);

	void movePiece(int oldX, int oldY, int newX, int newY);

	bool checkGameSituation(bool color);

	int getnKings();

	int getWasEmpty();

	chesslogic::Piece getSavedItem();

	std::shared_ptr<Square> getItem(int i, int j);

private:
	int nKings_ = 0;
	int nBishops_ = 0;
	int nRooks_ = 0;
	bool wasEmpty_ = true;
	chesslogic::Piece savedItem_;
	std::shared_ptr<Square> items_[8][8];
};
