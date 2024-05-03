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
            items_[i][j] = std::make_shared<Square>(Square(i, j));
        }
    }
}

void Board::addPiece(int i, int j, Type type, bool color) {

    items_[i][j].get()->piece = std::make_shared<chesslogic::Piece> (chesslogic::Piece(color, type, i, j, items_));

    switch (type) {
    case Type::king:
        nKings_++;
        break;
    case Type::bishop:
        nBishops_++;
        break;
    case Type::rook:
        nRooks_++;
        break;
    }

    if (nKings_ > 2) {
        throw std::runtime_error("trop de roi");
    }
}

void Board::removePiece(int i, int j, Type type) {

    items_[i][j]->piece = nullptr;

    switch (type) {
    case Type::king:
        nKings_--;
        break;
    case Type::bishop:
        nBishops_--;
        break;
    case Type::rook:
        nRooks_--;
        break;
    }
}

void Board::updateGame(std::shared_ptr<Square> square) {

    //Update the game around a single piece
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (items_[i][j]->piece != nullptr && items_[i][j].get() != square.get()) {
             items_[i][j]->piece->setPossiblePosition(items_);
            }
        }
    }
    square->piece->setPossiblePosition(items_);
}

void Board::movePiece(int oldX, int oldY, int newX, int newY) {

    //Logic for being able to put back a piece that was eaten
    if (items_[newX][newY].get()->piece.get() != nullptr) {
        savedItem_ = (*(items_[newX][newY].get()->piece.get()));
        wasEmpty_ = false;
    }
    else {
        wasEmpty_ = true;
    }

    items_[newX][newY]->piece = items_[oldX][oldY]->piece;
    items_[oldX][oldY]->piece = nullptr;
    items_[newX][newY]->piece->setPosition(newX, newY, items_);
}

bool Board::checkGameSituation(bool color) {

    //Checking if the piece's king is in check
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if(items_[i][j]->piece && items_[i][j]->piece->getColor() != color && items_[i][j]->piece->getIsCheck() == true) {
                return true;
            }
        }
    }
    return false;
}

std::shared_ptr<Square> Board::getItem(int i, int j) {
    return items_[i][j];
}

chesslogic::Piece Board::getSavedItem() {
    return savedItem_;
}

int Board::getnKings() {
    return nKings_;
}

int Board::getWasEmpty() {
    return wasEmpty_;
}

