#include "Piece.h"
#include "Square.h"

namespace chesslogic {


	using namespace std;

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
			for (int i = -1; i <= 1; i++) {
				for (int j = -1; j <= 1; j++) {
					if (i != 0 || j != 0) {

						int newX = i_ + i;
						int newY = j_ + j;

						if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
							if (items[newX][newY]->piece == nullptr || items[newX][newY]->piece->color != color) {

								possiblePosition.push_back(make_pair(newX, newY));
							}
						}
					}
				}
			}
			//verifier les cases qui sont en mise en echec
			//on verifie si, pour tout possiblePosition, cette position n'est pas dans possiblePosition d'une autre piece quelconque
			for (const auto& elem : possiblePosition) {
				for (int i = 0; i < 8; i++) {
					for (int j = 0; j < 8; j++) {
						if (items[i][j]->piece != nullptr) {
							if (items[i][j]->piece->color != color) {
								if (find(items[i][j]->piece->possiblePosition.begin(), items[i][j]->piece->possiblePosition.end(), elem) != items[i][j]->piece->possiblePosition.end()) { //si on a trouve elem dans une des possibilite des pieces
									possiblePosition.erase(remove(possiblePosition.begin(), possiblePosition.end(), elem), possiblePosition.end());
								}
							}
						}
					}
				}
			}


			break;
		case TYPE::bishop: {
			vector<pair<int, int>> direction = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
			for (const auto& cod : direction) {
				for (int step = 1; step < 8; step++) {
					int newX = i_ + cod.first * step;
					int newY = j_ + cod.second * step;
					if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
						if (items[newX][newY]->piece) {
							if (items[newX][newY]->piece->color != color) {
								possiblePosition.push_back(make_pair(newX, newY)); // Capture possible
							}
							break; // Blocage par une pièce, arrêt dans cette direction
						}
						possiblePosition.push_back(make_pair(newX, newY));
					}
				}
			}
			break;
		}

		case TYPE::rook:
			vector<pair<int, int>> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
			for (const auto& coord : directions) {
				for (int step = 1; step < 8; step++) {
					int newX = i_ + coord.first * step;
					int newY = j_ + coord.second * step;
					if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
						if (items[newX][newY]->piece) {
							if (items[newX][newY]->piece->color != color) {
								possiblePosition.push_back(make_pair(newX, newY)); // Capture possible
							}
							break; // Blocage par une pièce, arrêt dans cette direction
						}
						possiblePosition.push_back(make_pair(newX, newY));
					}
				}
			}
			break;

		}
	}
}