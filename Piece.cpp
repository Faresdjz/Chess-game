#include "Piece.h"
#include "Square.h"

namespace chesslogic {

	Piece::Piece(bool color, TYPE type, Square* items[8][8]) {

		setPossiblePosition(items);
	}


	Piece::Piece(bool color, TYPE type, int i, int j, Square* items[8][8])
		:color(color), type(type), i_(i), j_(j) {

		setPossiblePosition(items);
	}

	void Piece::setPossiblePosition(Square* items[8][8]) {

		possiblePosition.clear();

		switch (type) {
		case TYPE::king:
			// Le roi peut se deplacer dans un rayon de 1 case dans toutes les directions
			for (int dx = -1; dx <= 1; dx++) {
				for (int dy = -1; dy <= 1; dy++) {
					if (dx == 0 && dy == 0) {
						continue; // Ignorer la position actuelle du roi
					}

					int newX = i_ + dx;
					int newY = j_ + dy;

					if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
						if (items[newX][newY]->piece == nullptr || items[newX][newY]->piece->color != color) {
							// Verifiez que la position ne met pas le roi en echec
							bool isSafe = true;
							for (int i = 0; i < 8; i++) {
								for (int j = 0; j < 8; j++) {
									if (items[i][j]->piece && items[i][j]->piece->color != color) {
										auto& enemyPositions = items[i][j]->piece->possiblePosition;
										if (std::find(enemyPositions.begin(), enemyPositions.end(), std::make_pair(newX, newY)) != enemyPositions.end()) {
											isSafe = false; // La position est dangereuse
											break;
										}
									}
								}
							}
							if (isSafe) {
								possiblePosition.push_back(std::make_pair(newX, newY));
							}
							else {
								possiblePosition.push_back(std::make_pair(newX, newY));
								dangerousPosition.push_back(std::make_pair(newX, newY));
							}
							
						}
					}
				}
			}

			if (std::find(dangerousPosition.begin(), dangerousPosition.end(), std::make_pair(i_, j_)) != dangerousPosition.end()) {
				isCheck = std::make_unique<Check>();
			}
			break;

		case TYPE::bishop: {
			std::vector<std::pair<int, int>> direction = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
			for (const auto& cod : direction) {
				for (int step = 1; step < 8; step++) {
					int newX = i_ + cod.first * step;
					int newY = j_ + cod.second * step;
					if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
						if (items[newX][newY]->piece) {
							if (items[newX][newY]->piece->color != color) {
								possiblePosition.push_back(std::make_pair(newX, newY)); // Capture possible
							}
							break; // Blocage par une piece, arret dans cette direction
						}
						possiblePosition.push_back(std::make_pair(newX, newY));
					}
				}
			}
			break;
		}

		case TYPE::rook:
			std::vector<std::pair<int, int>> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
			for (const auto& coord : directions) {
				for (int step = 1; step < 8; step++) {
					int newX = i_ + coord.first * step;
					int newY = j_ + coord.second * step;
					if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
						if (items[newX][newY]->piece) {
							if (items[newX][newY]->piece->color != color) {
								possiblePosition.push_back(std::make_pair(newX, newY)); // Capture possible
							}
							break; // Blocage par une piece, arret dans cette direction
						}
						possiblePosition.push_back(std::make_pair(newX, newY));
					}
				}
			}
			break;

		}
	}
}