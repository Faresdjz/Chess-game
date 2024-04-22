/**
* Fichier d�crivant diff�rentes fonctions permettant de cr�er le plateau d'�checs � partir d'une matrice de cases 'Square' et de g�rer l'agencement des pi�ces entre elles. 

* \file   Board.cpp
* \author Fares Laadjel 2297799 et Ayoub Marfouk 2295178
* \date   21 avril 2024
* Cr�� le 13 avril 2024
*/

#include "Board.h"


Board::Board() {

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            items[i][j] = new Square(i, j);

        }
    }
}

void Board::addPiece(int i, int j, TYPE type, bool color) {

    items[i][j]->piece = new chesslogic::Piece(color, type, i, j, items);

    switch (type) {
    case TYPE::king:
        nKings++;
        break;
    case TYPE::bishop:
        nBishops++;
        break;
    case TYPE::rook:
        nRooks++;
        break;
    }

    if (nKings > 3) {
        throw std::runtime_error("trop de roi");
    }
}

void Board::updateGame(Square* square) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (items[i][j]->piece != nullptr) {
                if (items[i][j] != square) {
                    items[i][j]->piece->setPossiblePosition(items);
                }
            }
        }
    }
    square->piece->setPossiblePosition(items);
}

void Board::movePiece(int oldX, int oldY, int newX, int newY) {

    items[newX][newY]->piece = items[oldX][oldY]->piece;
    items[oldX][oldY]->piece = nullptr;
    items[newX][newY]->piece->setPosition(newX, newY, items);
}