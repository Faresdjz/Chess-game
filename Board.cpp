/**
* Fichier decrivant differentes fonctions permettant de creer le plateau d'echecs a partir d'une matrice de cases 'Square' et de gerer l'agencement des pieces entre elles. 

* \file   Board.cpp
* \author Fares Laadjel 2297799 et Ayoub Marfouk 2295178
* \date   21 avril 2024
* Cree le 13 avril 2024
*/

#include "Board.h"


Board::Board() {

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            items[i][j] = std::make_shared<Square>(Square(i, j));
        }
    }
}

void Board::addPiece(int i, int j, TYPE type, bool color) {

    items[i][j].get()->piece = std::make_shared<chesslogic::Piece> (chesslogic::Piece(color, type, i, j, items));

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

    if (nKings > 2) {
        throw std::runtime_error("trop de roi");
    }
}

void Board::removePiece(int i, int j, TYPE type) {

    items[i][j]->piece = nullptr;

    switch (type) {
    case TYPE::king:
        nKings--;
        break;
    case TYPE::bishop:
        nBishops--;
        break;
    case TYPE::rook:
        nRooks--;
        break;
    }
}

void Board::updateGame(std::shared_ptr<Square> square) {

    //Update the game around a single piece
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (items[i][j]->piece != nullptr && items[i][j].get() != square.get()) {
             items[i][j]->piece->setPossiblePosition(items);
            }
        }
    }
    square->piece->setPossiblePosition(items);
}

void Board::movePiece(int oldX, int oldY, int newX, int newY) {

    //Logic for being able to put back a piece that was eaten
    if (items[newX][newY].get()->piece.get() != nullptr) {
        savedItem = (*(items[newX][newY].get()->piece.get()));
        wasEmpty = false;
    }
    else {
        wasEmpty = true;
    }

    items[newX][newY]->piece = items[oldX][oldY]->piece;
    items[oldX][oldY]->piece = nullptr;
    items[newX][newY]->piece->setPosition(newX, newY, items);
}

bool Board::checkGameSituation(bool color) {

    //Checking if the piece's king is in check
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if(items[i][j]->piece && items[i][j]->piece->color != color && items[i][j]->piece->isCheck == true) {
                return true;
            }
        }
    }
    return false;
}