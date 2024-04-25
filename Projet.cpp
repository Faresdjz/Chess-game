/**
* Fichier definissant les differentes fonctions de la classe Projet necessaires a la creation et l'affichage de l'interface du jeu d'echecs et a l'agencement et au bon fonctionnement des boutons presents sur cette derniere.

* \file   Projet.cpp
* \author Fares Laadjel 2297799 et Ayoub Marfouk 2295178
* \date   21 avril 2024
* Cree le 13 avril 2024
*/

#include "Projet.h"

namespace chessui{

    Projet::Projet(QWidget* parent)
        : QMainWindow(parent)
    {
        ui.setupUi(this);

        board = Board();

        //creation dun widget
        QWidget* windowGrid = new QWidget;
        QWidget* windowText = new QWidget;

        label = new QLabel("Player 1's turn");

        //creation dun layout
        QHBoxLayout* box = new QHBoxLayout;
        QGridLayout* gridLayout = new QGridLayout;
        QVBoxLayout* textLayout = new QVBoxLayout;
        gridLayout->setSpacing(0);

        //je met le layout dans le widget
        ui.centralWidget->setLayout(box);
        windowGrid->setLayout(gridLayout);
        windowText->setLayout(textLayout);


        //creation de la grille de boutton
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                buttons[i][j] = new QPushButton();
                buttons[i][j]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
                gridLayout->addWidget(buttons[i][j], i, j);
                connect(buttons[i][j], &QPushButton::clicked, [this, i, j] {play(i, j); });

            }
        }

        box->addWidget(windowGrid, 2);
        box->addWidget(windowText, 1);

        textLayout->addWidget(label);

    }

    Projet::~Projet()
    {}

    void Projet::loadRessources() {

        //tentative pour eviter de load les icons durant le code
        iconRessources["BlackKing"] = QIcon(BlackKing);
        iconRessources["BlackBishop"] = QIcon(BlackBishop);
        iconRessources["BlackRook"] = QIcon(BlackRook);
        iconRessources["WhiteKing"] = QIcon(WhiteKing);
        iconRessources["WhiteBishop"] = QIcon(WhiteBishop);
        iconRessources["WhiteRook"] = QIcon(WhiteRook);
    }

    void Projet::addPieceUi(int i, int j, TYPE type, bool color) {


        board.addPiece(i, j, type, color);

        if (color) {
            if (type == TYPE::king) {
                buttons[i][j]->setIcon(iconRessources["BlackKing"]);
            }
            if (type == TYPE::bishop) {
                buttons[i][j]->setIcon(iconRessources["BlackBishop"]);
            }
            if (type == TYPE::rook) {
                buttons[i][j]->setIcon(iconRessources["BlackRook"]);
            }
        }
        else {
            if (type == TYPE::king) {
                buttons[i][j]->setIcon(iconRessources["WhiteKing"]);
            }
            if (type == TYPE::bishop) {
                buttons[i][j]->setIcon(iconRessources["WhiteBishop"]);
            }
            if (type == TYPE::rook) {
                buttons[i][j]->setIcon(iconRessources["WhiteRook"]);
            }
        }

        
    }

    void Projet::removePieceUi(int i, int j, TYPE type) {

        buttons[i][j]->setIcon(QIcon(""));
        board.removePiece(i, j, type);
    }


    void Projet::removeAllPieceUi() {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (board.items[i][j]->piece != nullptr) {
                    removePieceUi(i, j, board.items[i][j]->piece->type);
                }
            }
        }
    }

    void Projet::movePieceUi(int oldX, int oldY, int newX, int newY) {
        board.movePiece(oldX, oldY, newX, newY);
        buttons[oldX][oldY]->setIcon(QIcon(" "));
        buttons[newX][newY]->setIcon(selectedIcon);
        board.items[newX][newY]->piece->dangerousPosition.clear();
        board.items[newX][newY]->piece->setPossiblePosition(board.items);

    }

    void Projet::buttonSelected(int row, int col) {
        selectedRow = row;
        selectedCol = col;
        selectedIcon = buttons[row][col]->icon();
        isSelected = true;
    }

    void Projet::setDefaultGame() {

        removeAllPieceUi();
            
        addPieceUi(7, 4, TYPE::king, false);
        addPieceUi(0, 4, TYPE::king, true);
        addPieceUi(7, 2, TYPE::bishop, false);
        addPieceUi(0, 2, TYPE::bishop, true);
        addPieceUi(7, 3, TYPE::rook, false);
        addPieceUi(0, 3, TYPE::rook, true);

    }


    void Projet::setNewGame() {

        loadRessources();

        try {
            addPieceUi(7, 4, TYPE::king, false);
            addPieceUi(0, 4, TYPE::king, true);
            addPieceUi(7, 2, TYPE::bishop, false);
            addPieceUi(0, 2, TYPE::bishop, true);
            addPieceUi(7, 3, TYPE::rook, false);
            addPieceUi(0, 3, TYPE::rook, true);
            addPieceUi(0, 7, TYPE::king, true);
        }
        catch (const std::runtime_error& erreur) {
            std::cout << "Erreur lors de l'ajout des pieces: " << erreur.what() << " il y en a: " << board.nKings;
            setDefaultGame();
        }

    }

    void Projet::play(int row, int col) {

        if (!isSelected) { //premier appui
            if (board.items[row][col]->piece != nullptr) {
                if (playerTurn == board.items[row][col]->piece->color) {

                    buttonSelected(row, col);
                    board.updateGame(board.items[row][col]);
                    playerTurn = !playerTurn;

                    //on highlight la case selectionne
                    buttons[row][col]->setStyleSheet("QPushButton { background-color: yellow; }");


                    for (const auto& elem : board.items[selectedRow][selectedCol]->piece->possiblePosition) {
                        buttons[elem.first][elem.second]->setStyleSheet("QPushButton { background-color: yellow; }");
                    }
                }
            }
        }
        else { //deuxieme appui

            for (const auto& elem : board.items[selectedRow][selectedCol]->piece->possiblePosition) {
                buttons[elem.first][elem.second]->setStyleSheet(" ");
            }

            if (board.items[row][col]->isPlayable(board.items[selectedRow][selectedCol]->piece->dangerousPosition)) {

                for (const auto& elem : board.items[selectedRow][selectedCol]->piece->dangerousPosition) {
                    buttons[elem.first][elem.second]->setStyleSheet("QPushButton { background-color: red; }");
                }
                playerTurn = !playerTurn;
            }

            else if (board.items[row][col]->isPlayable(board.items[selectedRow][selectedCol]->piece->possiblePosition)) {
                movePieceUi(selectedRow, selectedCol, row, col);
            }

            //si on rappuie sur une case invalide on peut rejouer
            else {
                playerTurn = !playerTurn;
            }

            //reset les couleurs par defaut pour le prochain tour
            buttons[selectedRow][selectedCol]->setStyleSheet("");
            isSelected = false;

        }
    }

}