/**
* Fichier declarant la classe Square permettant de creer un square (une case) et ses attributs et de determiner si l'une des case du platea est occupee par une piece ou non.

* \file   Square.h
* \author Fares Laadjel 2297799 et Ayoub Marfouk 2295178
* \date   3 mai 2024
* Cree le 13 avril 2024
*/

#pragma once
#include "IncludeFile.h"
#include "Piece.h"

class Square {
public:
	Square(int i, int j): i_(i), j_(j){};

	bool isPlayable(std::vector <std::pair<int, int>> possiblePosition);

	std::shared_ptr<chesslogic::Piece> piece;

private:
	int i_ = -1;
	int j_ = -1;
};