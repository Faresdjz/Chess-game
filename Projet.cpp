/**
* Fichier definissant les differentes fonctions de la classe Projet necessaires a la creation et l'affichage de l'interface du jeu d'echecs et a l'agencement et au bon fonctionnement des boutons presents sur cette derniere.

* \file   Projet.cpp
* \author Fares Laadjel 2297799 et Ayoub Marfouk 2295178
* \date   21 avril 2024
* Cree le 13 avril 2024
*/

#include "Projet.h"

namespace chessui {

    Projet::Projet(QWidget* parent)
        : QMainWindow(parent)
    {
        ui.setupUi(this);

        board = Board();

        //creation dun widget
        QWidget* windowGrid = new QWidget;
        QWidget* windowText = new QWidget;



        label1 = new QLabel("WHITE, you can play!");
        label2 = new QLabel("");

        label1->setStyleSheet("color: rgba(255, 255, 255, 0.7); font-size: 11pt;");
        label2->setStyleSheet("color: rgba(180, 30, 30, 1); font-size: 12pt;");

        label1->setAlignment(Qt::AlignCenter); // Centre le texte horizontalement et verticalement
        label2->setAlignment(Qt::AlignCenter);

        //creation dun layout
        QHBoxLayout* box = new QHBoxLayout;
        QGridLayout* gridLayout = new QGridLayout;
        QVBoxLayout* textLayout = new QVBoxLayout;
        gridLayout->setSpacing(0);

        //je met le layout dans le widget
        ui.centralWidget->setLayout(box);
        windowGrid->setLayout(gridLayout);
        windowText->setLayout(textLayout);
        //windowGrid->setStyleSheet("background-color: #333333; border: 5px solid black; border-radius: 10px;");
        windowGrid->setContentsMargins(10, 10, 10, 10);
        //windowGrid->setStyleSheet("background-color: #333333; border: 5px solid #2a82da; border-radius: 10px;");

        //creation de la grille de boutton
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                buttons[i][j] = new QPushButton();
                buttons[i][j]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
                buttons[i][j]->setMinimumSize(50, 50); // Taille minimale pour chaque bouton

                // Alternance de couleurs pour les cases
                if ((i + j) % 2 == 0) {
                    buttons[i][j]->setStyleSheet("background-color: #333333; border: 0;");
                }
                else {
                    buttons[i][j]->setStyleSheet("background-color: #1C1C1E; border: 0;");
                }

                gridLayout->addWidget(buttons[i][j], i, j);
                connect(buttons[i][j], &QPushButton::clicked, [this, i, j] { play(i, j); });
            }
        }

        box->addWidget(windowGrid, 2);
        box->addWidget(windowText, 1);

        //windowText->setStyleSheet("border: 3px solid black; border-radius: 10px;");
        QString borderStyle = "border: 3px solid #202020; background-color: #333; ";

        // Appliquer le style à windowGrid
        windowGrid->setStyleSheet(QString("border: 7px solid #202020; background-color: #333; "));

        // Appliquer le style à windowText
        windowText->setStyleSheet(borderStyle);

        textLayout->addWidget(label1);
        textLayout->addWidget(label2);

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

    }

    void Projet::swapPlayer() {

        playerTurn = !playerTurn;
        if (playerTurn) {
            label1->setText(QString("BLACK, you can play!"));
        }
        else {
            label1->setText(QString("WHITE, you can play!"));
        }

    }

    bool Projet::checkSituationUi() {

        if (board.checkGameSituation(!playerTurn)) {
            label2->setText(QString("CHECK"));
            return true;
        }
        label2->setText(QString(""));
        return false;

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

    void Projet::resetColorScheme() {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if ((i + j) % 2 == 0) {
                    buttons[i][j]->setStyleSheet("background-color: #333333; border: 0;");
                }
                else {
                    buttons[i][j]->setStyleSheet("background-color: #1C1C1E; border: 0;");
                }
            }
        }
    }

    void Projet::play(int row, int col) {


        if (!isSelected) { //premier appui
            if (board.items[row][col]->piece != nullptr) {
                if (playerTurn == board.items[row][col]->piece->color) {

                    buttonSelected(row, col);
                    board.updateGame(board.items[row][col]);

                    //on highlight la case selectionne
                    buttons[row][col]->setStyleSheet("QPushButton { background-color: rgba(255, 255, 0, 0.5); border: 1px solid rgba(255, 255, 0, 0.5); }");


                    for (const auto& elem : board.items[selectedRow][selectedCol]->piece->possiblePosition) {
                        buttons[elem.first][elem.second]->setStyleSheet("QPushButton { background-color: rgba(255, 255, 0, 0.5); border: 1px solid rgba(255, 255, 0, 0.5); }");
                    }
                }
            }
        }

        else { //deuxieme appui



            for (const auto& elem : board.items[selectedRow][selectedCol]->piece->possiblePosition) {
                buttons[elem.first][elem.second]->setStyleSheet(" ");
            }

            if (board.items[row][col]->isPlayable(board.items[selectedRow][selectedCol]->piece->possiblePosition)) {
                
                movePieceUi(selectedRow, selectedCol, row, col);

                //verifier si le roi est en echec
                board.updateGame(board.items[row][col]);

                if (checkSituationUi()) {

                    movePieceUi(row, col, selectedRow, selectedCol);
                    swapPlayer();

                }
            }

            //si on rappuie sur une case invalide on peut rejouer
            else {
                swapPlayer();
            }

            //reset les couleurs par defaut pour le prochain tour
            isSelected = false;
            swapPlayer();
            resetColorScheme();
        }
    }

}