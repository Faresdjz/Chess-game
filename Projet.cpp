/**
* Fichier definissant les differentes fonctions de la classe Projet necessaires a la creation et l'affichage de l'interface du jeu d'echecs et a l'agencement et au bon fonctionnement des boutons presents sur cette derniere.

* \file   Projet.cpp
* \author Fares Laadjel 2297799 et Ayoub Marfouk 2295178
* \date   3 mai 2024
* Cree le 13 avril 2024
*/

#include "Projet.h"

namespace chessui {

    Projet::Projet(QWidget* parent)
        : QMainWindow(parent)
    {
        ui.setupUi(this);

        board_ = Board();
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
        firstLabel_ = new QLabel("WHITE <br> you can play!");
        secondLabel_ = new QLabel("");
        firstLabel_->setStyleSheet("color: rgba(255, 255, 255, 0.7); font-size: 11pt;");
        secondLabel_->setStyleSheet("color: rgba(180, 30, 30, 1); font-size: 12pt;");
        firstLabel_->setAlignment(Qt::AlignCenter); 
        secondLabel_->setAlignment(Qt::AlignCenter);
        textLayout->addWidget(firstLabel_);
        textLayout->addWidget(secondLabel_);

        //Game menu setup
        QComboBox* gameSelector = new QComboBox();
        gameSelector->addItem("Default Game", QVariant(0));
        gameSelector->addItem("Game One", QVariant(1));
        gameSelector->addItem("Game Two", QVariant(2));
        gameSelector->addItem("Game Three", QVariant(3));
        textLayout->addWidget(gameSelector);

        //Start button setup
        QPushButton* startButton = new QPushButton("Start Game");
        textLayout->addWidget(startButton);
        connect(startButton, &QPushButton::clicked, this, [this, gameSelector]() {setNewGame(gameSelector); });


        //Buttons setup
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                buttons_[i][j] = new QPushButton();
                buttons_[i][j]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
                buttons_[i][j]->setMinimumSize(50, 50);

                buttons_[i][j]->setStyleSheet((i + j) % 2 == 0 ? blackSquareSetUp : lightSquareSetUp);
                gridLayout->addWidget(buttons_[i][j], i, j);
                connect(buttons_[i][j], &QPushButton::clicked, [this, i, j] { play(i, j); });
            }
        }
    }

    void Projet::loadRessources() {

        //Attempt to reduce the lag on first input (preloading ressources)
        iconRessources_["BlackKing"] = QIcon(BlackKing);
        iconRessources_["BlackBishop"] = QIcon(BlackBishop);
        iconRessources_["BlackRook"] = QIcon(BlackRook);
        iconRessources_["WhiteKing"] = QIcon(WhiteKing);
        iconRessources_["WhiteBishop"] = QIcon(WhiteBishop);
        iconRessources_["WhiteRook"] = QIcon(WhiteRook);
    }

    void Projet::addPieceUi(int i, int j, Type type, bool color) {

        //color TRUE-->Black
        //color FALSE-->White
        board_.addPiece(i, j, type, color);
        if (color) {
            if (type == Type::king) {
                buttons_[i][j]->setIcon(iconRessources_["BlackKing"]);
            }
            if (type == Type::bishop) {
                buttons_[i][j]->setIcon(iconRessources_["BlackBishop"]);
            }
            if (type == Type::rook) {
                buttons_[i][j]->setIcon(iconRessources_["BlackRook"]);
            }
        }
        else {
            if (type == Type::king) {
                buttons_[i][j]->setIcon(iconRessources_["WhiteKing"]);
            }
            if (type == Type::bishop) {
                buttons_[i][j]->setIcon(iconRessources_["WhiteBishop"]);
            }
            if (type == Type::rook) {
                buttons_[i][j]->setIcon(iconRessources_["WhiteRook"]);
            }
        }
        buttons_[i][j]->setIconSize(QSize(40, 40));
    }

    void Projet::removePieceUi(int i, int j, Type type) {

        buttons_[i][j]->setIcon(QIcon(""));
        board_.removePiece(i, j, type);
    }


    void Projet::removeAllPieceUi() {

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (board_.getItem(i, j)->piece != nullptr) {
                    removePieceUi(i, j, board_.getItem(i, j)->piece->getType());
                }
            }
        }
    }

    void Projet::movePieceUi(int oldX, int oldY, int newX, int newY) {

        board_.movePiece(oldX, oldY, newX, newY);
        buttons_[oldX][oldY]->setIcon(QIcon(" "));
        buttons_[newX][newY]->setIcon(selectedIcon_);
        buttons_[newX][newY]->setIconSize(QSize(40, 40));
    }

    void Projet::swapPlayer() {

        playerTurn_ = !playerTurn_;
        if (playerTurn_) {
            firstLabel_->setText(QString("BLACK <br> you can play!"));
        }
        else {
            firstLabel_->setText(QString("WHITE <br> you can play!"));
        }
    }

    bool Projet::checkSituationUi() {

        if (board_.checkGameSituation(!playerTurn_)) {
            secondLabel_->setText(QString("CHECK"));
            return true;
        }
        secondLabel_->setText(QString(""));
        return false;
    }

    void Projet::buttonSelected(int row, int col) {

        //Boolean update for the selection of a piece
        selectedRow_ = row;
        selectedCol_ = col;
        selectedIcon_ = buttons_[row][col]->icon();
        isSelected_ = true;
    }

    void Projet::setDefaultGame() {

        removeAllPieceUi();
        addPieceUi(7, 3, Type::king, false);
        addPieceUi(0, 3, Type::king, true);
        addPieceUi(7, 2, Type::bishop, false);
        addPieceUi(0, 2, Type::bishop, true);
        addPieceUi(7, 4, Type::rook, false);
        addPieceUi(0, 4, Type::rook, true);

    }
    void Projet::setGameOne(){

        removeAllPieceUi();
        addPieceUi(7, 3, Type::king, false);
        addPieceUi(0, 3, Type::king, true);
        addPieceUi(7, 1, Type::bishop, false);
        addPieceUi(0, 1, Type::bishop, true);
        addPieceUi(7, 5, Type::rook, false);
        addPieceUi(0, 5, Type::rook, true);
    }

    void Projet::setGameTwo() {

        removeAllPieceUi();
        addPieceUi(7, 4, Type::king, false);
        addPieceUi(0, 2, Type::king, true);
        addPieceUi(7, 6, Type::bishop, false);
        addPieceUi(0, 5, Type::bishop, true);
        addPieceUi(7, 3, Type::rook, false);
        addPieceUi(0, 7, Type::rook, true);
    }

    void Projet::setGameThree() {

        removeAllPieceUi();
        addPieceUi(7, 4, Type::king, false);
        addPieceUi(0, 2, Type::king, true);
        addPieceUi(7, 7, Type::bishop, false);
        addPieceUi(0, 1, Type::bishop, true);
        addPieceUi(7, 3, Type::rook, false);
        addPieceUi(0, 5, Type::rook, true);
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
            std::cout << "Erreur lors de l'ajout des pieces: " << erreur.what() << " il y en a: " << board_.getnKings();
            setDefaultGame();
        }
    }

    void Projet::resetColorScheme() {

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                buttons_[i][j]->setStyleSheet((i + j) % 2 == 0 ? blackSquareSetUp : lightSquareSetUp);
            }
        }
    }


    void Projet::highlightPossiblePosition(int i, int j, bool isOn) {

        if (isOn) {
            for (const auto& elem : board_.getItem(i, j)->piece->possiblePosition) {
                buttons_[elem.first][elem.second]->setStyleSheet(highlightSetUp);
            }
        }
        else {
            for (const auto& elem : board_.getItem(i, j)->piece->possiblePosition) {
                buttons_[elem.first][elem.second]->setStyleSheet("");
            }
        }
    }


    void Projet::play(int row, int col) {


        /* README */
        /*  Le jeu fonctionne parfaitement, sauf pour une seule situation bien precise.Pour les pieces noires SEULEMENT, on peut bouger une piece qui mettra */
        /*  son roi en echec, alors que pour les pieces blanches, cette situation est pris en compte par le detecteur d'echec. Sinon, le reste marche comme prevu.*/

        if (!isSelected_) { //First click
            if (board_.getItem(row, col)->piece != nullptr && playerTurn_ == board_.getItem(row, col)->piece->getColor()) {
                buttonSelected(row, col);
                board_.updateGame(board_.getItem(row, col));

                buttons_[row][col]->setStyleSheet(highlightSetUp);
                highlightPossiblePosition(selectedRow_, selectedCol_, true);
            }
        }
        else { //Second click
            highlightPossiblePosition(selectedRow_, selectedCol_, false);
            if (board_.getItem(row, col)->isPlayable(board_.getItem(selectedRow_, selectedCol_)->piece->possiblePosition)) {

                movePieceUi(selectedRow_, selectedCol_, row, col);
                board_.updateGame(board_.getItem(row,col));
                if (checkSituationUi()) {

                    board_.updateGame(board_.getItem(row,col));
                    if (board_.getWasEmpty() == false) { //If a piece was eaten, we have to put it back
                        movePieceUi(row, col, selectedRow_, selectedCol_);
                        addPieceUi(board_.getSavedItem().getI(), board_.getSavedItem().getJ(), board_.getSavedItem().getType(), board_.getSavedItem().getColor());
                        swapPlayer();
                    }
                    else if(checkSituationUi()){
                        movePieceUi(row, col, selectedRow_, selectedCol_);
                        swapPlayer();
                    }
                }
            }

            //If we click on an invalid square, we can play again
            else {
                secondLabel_->setText(QString("INVALID"));
                swapPlayer();
            }

            //Setup for next play
            isSelected_ = false;
            swapPlayer();
            resetColorScheme();
        }
    }

}