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

    //throw
    switch (type) {
    case TYPE::king:
        nKings++;
        break;
    case TYPE::bishop:
        nBishops++;
        break;
    case TYPE::rook:
        nRooks;
        break;
    }
}

void Board::updateGame() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (items[i][j]->piece != nullptr) {
                items[i][j]->piece->setPossiblePosition(items);
            }
        }
    }
}

void Board::moveP(int oldX, int oldY, int newX, int newY) {

    //board.items[row][col]->piece = board.items[selectedRow][selectedCol]->piece;
    //board.items[selectedRow][selectedCol]->piece = nullptr;
    items[newX][newY]->piece = items[oldX][oldY]->piece;
    items[oldX][oldY]->piece = nullptr;
}