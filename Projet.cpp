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
        setWindowTitle("CHESS");

        //Widget
        QWidget* windowGrid = new QWidget;
        QWidget* windowText = new QWidget;

        //Layout
        QHBoxLayout* box = new QHBoxLayout;
        QGridLayout* gridLayout = new QGridLayout;
        QVBoxLayout* textLayout = new QVBoxLayout;
        gridLayout->setSpacing(0);

        //Layout and widget settings
        ui.centralWidget->setLayout(box);
        windowGrid->setLayout(gridLayout);
        windowText->setLayout(textLayout);
        windowGrid->setContentsMargins(10, 10, 10, 10);
        box->addWidget(windowGrid, 2);
        box->addWidget(windowText, 1);
        windowGrid->setStyleSheet(QString("border: 7px solid #202020; background-color: #333; "));
        windowText->setStyleSheet(QString("border: 3px solid #202020; background-color: #333; "));

        //Label settings
        label1 = new QLabel("WHITE <br> you can play!");
        label2 = new QLabel("");
        label1->setStyleSheet("color: rgba(255, 255, 255, 0.7); font-size: 11pt;");
        label2->setStyleSheet("color: rgba(180, 30, 30, 1); font-size: 12pt;");
        label1->setAlignment(Qt::AlignCenter); 
        label2->setAlignment(Qt::AlignCenter);
        textLayout->addWidget(label1);
        textLayout->addWidget(label2);

        //Game menu setup
        QComboBox* gameSelector = new QComboBox();
        gameSelector->addItem("Default Game", QVariant(0));
        gameSelector->addItem("Game One", QVariant(1));
        gameSelector->addItem("Game Two", QVariant(2));
        gameSelector->addItem("Game Three", QVariant(3));
        textLayout->addWidget(gameSelector);

        QPushButton* startButton = new QPushButton("Start Game");
        textLayout->addWidget(startButton);
        connect(startButton, &QPushButton::clicked, this, [this, gameSelector]() {setNewGame(gameSelector); });


        //Buttons setup
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                buttons[i][j] = new QPushButton();
                buttons[i][j]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
                buttons[i][j]->setMinimumSize(50, 50);

                if ((i + j) % 2 == 0) {
                    buttons[i][j]->setStyleSheet(blackSquareSetUp);
                }
                else {
                    buttons[i][j]->setStyleSheet(lightSquareSetUp);
                }
                gridLayout->addWidget(buttons[i][j], i, j);
                connect(buttons[i][j], &QPushButton::clicked, [this, i, j] { play(i, j); });
            }
        }



    }

    void Projet::playMusic() {


    }

    void Projet::loadRessources() {

        //Attempt to reduce the lag on first input (preloading ressources)
        iconRessources["BlackKing"] = QIcon(BlackKing);
        iconRessources["BlackBishop"] = QIcon(BlackBishop);
        iconRessources["BlackRook"] = QIcon(BlackRook);
        iconRessources["WhiteKing"] = QIcon(WhiteKing);
        iconRessources["WhiteBishop"] = QIcon(WhiteBishop);
        iconRessources["WhiteRook"] = QIcon(WhiteRook);
    }

    void Projet::addPieceUi(int i, int j, TYPE type, bool color) {

        //color TRUE-->Black
        //color FALSE-->White
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
        buttons[i][j]->setIconSize(QSize(40, 40));

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
        buttons[newX][newY]->setIconSize(QSize(40, 40));
    }

    void Projet::swapPlayer() {
        playerTurn = !playerTurn;
        if (playerTurn) {
            label1->setText(QString("BLACK <br> you can play!"));
        }
        else {
            label1->setText(QString("WHITE <br> you can play!"));
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
        //Boolean update for the selection of a piece
        selectedRow = row;
        selectedCol = col;
        selectedIcon = buttons[row][col]->icon();
        isSelected = true;
    }

    void Projet::setDefaultGame() {
        removeAllPieceUi();

        addPieceUi(7, 3, TYPE::king, false);
        addPieceUi(0, 3, TYPE::king, true);
        addPieceUi(7, 2, TYPE::bishop, false);
        addPieceUi(0, 2, TYPE::bishop, true);
        addPieceUi(7, 4, TYPE::rook, false);
        addPieceUi(0, 4, TYPE::rook, true);

    }
    void Projet::setGameOne(){
        removeAllPieceUi();

        addPieceUi(7, 3, TYPE::king, false);
        addPieceUi(0, 3, TYPE::king, true);
        addPieceUi(7, 1, TYPE::bishop, false);
        addPieceUi(0, 1, TYPE::bishop, true);
        addPieceUi(7, 5, TYPE::rook, false);
        addPieceUi(0, 5, TYPE::rook, true);
    }

    void Projet::setGameTwo() {
        removeAllPieceUi();

        addPieceUi(7, 4, TYPE::king, false);
        addPieceUi(0, 2, TYPE::king, true);
        addPieceUi(7, 6, TYPE::bishop, false);
        addPieceUi(0, 5, TYPE::bishop, true);
        addPieceUi(7, 3, TYPE::rook, false);
        addPieceUi(0, 7, TYPE::rook, true);
    }

    void Projet::setGameThree() {
        removeAllPieceUi();

        addPieceUi(7, 4, TYPE::king, false);
        addPieceUi(0, 2, TYPE::king, true);
        addPieceUi(7, 7, TYPE::bishop, false);
        addPieceUi(0, 1, TYPE::bishop, true);
        addPieceUi(7, 3, TYPE::rook, false);
        addPieceUi(0, 5, TYPE::rook, true);
    };


    void Projet::setNewGame(QComboBox* option) {

        loadRessources();

        try {
            switch (option->currentData().toInt()) {
            case 1:
                setGameOne();
                break;
            case 2:
                setGameTwo();
                break;
            case 3:
                setGameThree();
                break;
            default:
                setDefaultGame();
            }
        }
        catch (const std::runtime_error& erreur) {
            std::cout << "Erreur lors de l'ajout des pieces: " << erreur.what() << " il y en a: " << board.getnKings();
            setDefaultGame();
        }

    }

    void Projet::resetColorScheme() {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if ((i + j) % 2 == 0) {
                    buttons[i][j]->setStyleSheet(blackSquareSetUp);
                }
                else {
                    buttons[i][j]->setStyleSheet(lightSquareSetUp);
                }
            }
        }
    }


    void Projet::highlightPossiblePosition(int i, int j, bool isOn) {
        if (isOn) {
            for (const auto& elem : board.items[i][j]->piece->possiblePosition) {
                buttons[elem.first][elem.second]->setStyleSheet(highlightSetUp);
            }
        }
        else {
            for (const auto& elem : board.items[i][j]->piece->possiblePosition) {
                buttons[elem.first][elem.second]->setStyleSheet("");
            }
        }

    }


    void Projet::play(int row, int col) {

        if (!isSelected) { //First click
            if (board.items[row][col]->piece != nullptr && playerTurn == board.items[row][col]->piece->color) {
                buttonSelected(row, col);
                board.updateGame(board.items[row][col]);

                buttons[row][col]->setStyleSheet(highlightSetUp);
                highlightPossiblePosition(selectedRow, selectedCol, true);
            }
        }
        else { //Second click
            highlightPossiblePosition(selectedRow, selectedCol, false);

            if (board.items[row][col]->isPlayable(board.items[selectedRow][selectedCol]->piece->possiblePosition)) {

                movePieceUi(selectedRow, selectedCol, row, col);
                board.updateGame(board.items[row][col]);

                if (checkSituationUi()) {

                    board.updateGame(board.items[row][col]);

                    if (board.getWasEmpty() == false) { //If a piece was eaten, we have to put it back
                        movePieceUi(row, col, selectedRow, selectedCol);
                        addPieceUi(board.savedItem.i_, board.savedItem.j_, board.savedItem.type, board.savedItem.color);
                        swapPlayer();
                    }
                    else if(checkSituationUi()){
                        movePieceUi(row, col, selectedRow, selectedCol);
                        swapPlayer();
                    }
                }
            }

            //If we click on an invalid square, we can play again
            else {
                swapPlayer();
            }

            //Setup for next play
            isSelected = false;
            swapPlayer();
            resetColorScheme();
        }
    }

}