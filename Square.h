/**
* Fichier d�clarant la classe Square permettant de cr�er un square (une case) et ses attributs et de d�terminer si l'une des case du platea est occup�e par une pi�ce ou non.

* \file   Square.h
* \author Fares Laadjel 2297799 et Ayoub Marfouk 2295178
* \date   21 avril 2024
* Cr�� le 13 avril 2024
*/

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


	bool isPlayable(std::vector <std::pair<int, int>> possiblePosition);

	chesslogic::Piece* piece = nullptr;
	int i_ = -1;
	int j_ = -1;
};