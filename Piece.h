/**
* Fichier declarant la classe Piece ainsi que ses fonctions permettant de creer une piece et ses attributs et de definir ses potentiels mouvements dependamment de son type. 


* \file   Piece.h
* \author Fares Laadjel 2297799 et Ayoub Marfouk 2295178
* \date   21 avril 2024
* Cree le 13 avril 2024
*/

#pragma once
#include "IncludeFile.h"

class Square;

namespace chesslogic {

	class Piece {

	public:
		Piece() {};

		Piece(const Piece& piece) : color_(piece.color_), type_(piece.type_), i_(piece.i_), j_(piece.j_), possiblePosition(piece.possiblePosition) {};

		Piece(bool color, Type type, std::shared_ptr<Square> items[8][8]);

		Piece(bool color, Type type, int i, int j, std::shared_ptr<Square> items[8][8]);

		void setPosition(int i, int j, std::shared_ptr<Square> items[8][8]);

		void setPossiblePosition(std::shared_ptr<Square> items[8][8]);

		int getI();

		int getJ();

		bool getColor();

		Type getType();

		bool getIsCheck();
		
		//This is in public, because it makes it more readable
		std::vector<std::pair<int, int>> possiblePosition;

	private:
		bool isCheck_ = false;
		int i_ = -1;
		int j_ = -1;
		bool color_ = false;
		Type type_ = Type::none;
	};
}
