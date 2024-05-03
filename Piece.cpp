/**
* Fichier definissant differentes fonctions de la classe Piece permettant de creer une piece et de definir ses potentiels mouvements dependamment de son type. 

* \file   Piece.cpp
* \author Fares Laadjel 2297799 et Ayoub Marfouk 2295178
* \date   21 avril 2024
* Cree le 13 avril 2024
*/

#include "Piece.h"
#include "Square.h"

namespace chesslogic {

	Piece::Piece(bool color, Type type, std::shared_ptr<Square> items[8][8]) {

		setPossiblePosition(items);
	}


	Piece::Piece(bool color, Type type, int i, int j, std::shared_ptr<Square>items[8][8])
		:color_(color), type_(type), i_(i), j_(j) {

		setPossiblePosition(items);
	}

	void Piece::setPossiblePosition(std::shared_ptr<Square> items[8][8]) {

		//Initialisation
		possiblePosition.clear();
		isCheck_ = false;

		switch (type_) {

			case Type::king: {
				for (int dx = -1; dx <= 1; dx++) {
					for (int dy = -1; dy <= 1; dy++) {
						int newX = i_ + dx;
						int newY = j_ + dy;

						if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
							if (items[newX][newY]->piece == nullptr || items[newX][newY]->piece->color_ != color_) {
								bool isSafe = true;
								for (int i = 0; i < 8; i++) {
									for (int j = 0; j < 8; j++) {
										if (items[i][j]->piece && items[i][j]->piece->color_ != color_) {
											auto enemyPositions = items[i][j]->piece->possiblePosition;
											possiblePosition.push_back(std::make_pair(newX, newY));
											if (std::find(enemyPositions.begin(), enemyPositions.end(), std::make_pair(i_, j_)) != enemyPositions.end()) {
												isCheck_ = true;
											}
										}
									}
								}
							}
						}
					}
				}

				break;
			}



			case Type::bishop: {
				std::vector<std::pair<int, int>> direction = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
				for (const auto& cod : direction) {
					for (int step = 1; step < 8; step++) {
						int newX = i_ + cod.first * step;
						int newY = j_ + cod.second * step;
						if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
							if (items[newX][newY]->piece) {
								if (items[newX][newY]->piece->color_ != color_) {
									possiblePosition.push_back(std::make_pair(newX, newY));
									if (items[newX][newY]->piece->type_ != Type::king) {
										break; //Direction is blocked by a piece
									}
								}
								else {
									break;
								}

							}
							possiblePosition.push_back(std::make_pair(newX, newY));
						}
					}
				}
				break;
			}


			case Type::rook: {
				std::vector<std::pair<int, int>> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
				for (const auto& coord : directions) {
					for (int step = 1; step < 8; step++) {
						int newX = i_ + coord.first * step;
						int newY = j_ + coord.second * step;
						if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
							if (items[newX][newY]->piece) {
								if (items[newX][newY]->piece->color_ != color_) {
									possiblePosition.push_back(std::make_pair(newX, newY));
									if (items[newX][newY]->piece->type_ != Type::king) {
										break; //Direction is blocked by a piece
									}
								}
								else {
									break;
								}

							}
							possiblePosition.push_back(std::make_pair(newX, newY));
						}
					}
				}
				break;
			}
		}
	}


	void Piece::setPosition(int i, int j, std::shared_ptr<Square> items[8][8]) {
		i_ = i;
		j_ = j;
		setPossiblePosition(items);
	}

	int Piece::getI() {
		return i_;
	}

	int Piece::getJ() {
		return j_;
	}

	bool Piece::getColor() {
		return color_;
	}

	Type Piece::getType() {
		return type_;
	}

	bool Piece::getIsCheck() {
		return isCheck_;
	}

}

