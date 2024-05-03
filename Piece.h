/**
* Fichier declarant la classe Piece ainsi que ses fonctions permettant de creer une piece et ses attributs et de definir ses potentiels mouvements dependamment de son type. 


* \file   Piece.h
* \author Fares Laadjel 2297799 et Ayoub Marfouk 2295178
* \date   21 avril 2024
* Cree le 13 avril 2024
*/

#pragma once
#include "IncludeFile.h"
#include <string>

class Square;

namespace chesslogic {

	class Piece {

	public:
		Piece() {};

		Piece(const Piece& piece) : color_(piece.color_), type_(piece.type_), i_(piece.i_), j_(piece.j_), possiblePosition(piece.possiblePosition) {};

		Piece(bool color, TYPE type, std::shared_ptr<Square> items[8][8]);

		Piece(bool color, TYPE type, int i, int j, std::shared_ptr<Square> items[8][8]);

		void setPosition(int i, int j, std::shared_ptr<Square> items[8][8]) {
			i_ = i;
			j_ = j;
			setPossiblePosition(items);
		}

		void setPossiblePosition(std::shared_ptr<Square> items[8][8]);

		int getI() {
			return i_;
		}

		int getJ() {
			return j_;
		}

		bool getColor() {
			return color_;
		}

		TYPE getType() {
			return type_;
		}

		bool getIsCheck() {
			return isCheck_;
		}
		
		std::vector<std::pair<int, int>> possiblePosition;

	private:
		bool isCheck_ = false;
		int i_ = -1;
		int j_ = -1;
		bool color_ = false;
		TYPE type_ = TYPE::none;
	};
}
