/**
* Fichier declarant la classe Piece ainsi que ses fonctions permettant de creer une piece et ses attributs et de definir ses potentiels mouvements dependamment de son type. 


* \file   Piece.h
* \author Fares Laadjel 2297799 et Ayoub Marfouk 2295178
* \date   21 avril 2024
* Cree le 13 avril 2024
*/

#pragma once
#include "IncludeFile.h"
#include "Check.h"
#include <string>

class Square;

namespace chesslogic {

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
		std::unique_ptr<Check> isCheck;
		TYPE type;
		int i_;
		int j_;
		std::vector<std::pair<int, int>> possiblePosition;
		std::vector <std::pair<int, int>> dangerousPosition;

	};
}
