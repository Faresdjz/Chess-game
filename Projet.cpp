#include "Projet.h"


namespace chessui {


    Projet::Projet(QWidget* parent)
        : QMainWindow(parent)
    {
        ui.setupUi(this);

        board = Board();

        //creation d'un widget
        QWidget* windowGrid = new QWidget;
        QWidget* windowText = new QWidget;

        label = new QLabel("Player 1's turn");

        //creation d'un layout
        QHBoxLayout* box = new QHBoxLayout;
        QGridLayout* gridLayout = new QGridLayout;
        QVBoxLayout* textLayout = new QVBoxLayout;
        gridLayout->setSpacing(0);

        //je met le layout dans le widget
        ui.centralWidget->setLayout(box);
        windowGrid->setLayout(gridLayout);
        windowText->setLayout(textLayout);


        //cr�ation de la grille de boutton
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

        //tentative pour �viter de load les icons durant le code
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

    void Projet::setNewGame() {

        loadRessources();

        try {
            addPieceUi(7, 4, TYPE::king, false);
            addPieceUi(0, 4, TYPE::king, true);
            addPieceUi(7, 2, TYPE::bishop, false);
            addPieceUi(0, 2, TYPE::bishop, true);
            addPieceUi(7, 3, TYPE::rook, false);
            addPieceUi(0, 3, TYPE::rook, true);
        }
        catch (const std::runtime_error& erreur) {
            cout << "Erreur lors de l'ajout des pieces: " << erreur.what() << " il y en a: " << board.nKings;
        }

    }

    void Projet::play(int row, int col) {



        if (!isSelected) { //premier appui
            if (board.items[row][col]->piece != nullptr) {

                if (playerTurn == board.items[row][col]->piece->color) {


                    board.updateGame(board.items[row][col]);

                    selectedRow = row;
                    selectedCol = col;
                    selectedIcon = buttons[row][col]->icon();
                    isSelected = true;
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

            //on eteint les cases jaunes propos�es
            for (const auto& elem : board.items[selectedRow][selectedCol]->piece->possiblePosition) {
                buttons[elem.first][elem.second]->setStyleSheet(" ");
            }

            board.updateGame(board.items[selectedRow][selectedCol]);


            //si la case correspond a une position dans le vecteur de position
            if (board.items[row][col]->isPlayable(board.items[selectedRow][selectedCol]->piece->possiblePosition)) {

                //on swap, donc delete un et deplacer lautre
                board.movePiece(selectedRow, selectedCol, row, col);

                //on reset le boutton initiale
                buttons[selectedRow][selectedCol]->setIcon(QIcon(" "));

                //on set le boutton de la case choisi
                buttons[row][col]->setIcon(selectedIcon);
                board.items[row][col]->piece->setPosition(row, col, board.items);

                board.items[row][col]->piece->dangerousPosition.clear();
                board.updateGame(board.items[row][col]);

                //si c'est un roi et qu'il est en echec, on fait le raii
                if (board.items[row][col]->piece->isCheck) {

                    //on deplace la piece vers sa position original
                    board.movePiece(row, col, selectedRow, selectedCol);

                    //on supprime les icones
                    buttons[row][col]->setIcon(QIcon(" "));
                    buttons[selectedRow][selectedCol]->setIcon(selectedIcon);

                    //on rejoue
                    playerTurn = !playerTurn;

                    //on renitialise le bool check
                    board.items[selectedRow][selectedCol]->piece->dangerousPosition.clear();
                    board.updateGame(board.items[selectedRow][selectedCol]);
                    board.items[selectedRow][selectedCol]->piece->isCheck.reset();

                    for (const auto& elem : board.items[selectedRow][selectedCol]->piece->dangerousPosition) {
                        buttons[elem.first][elem.second]->setStyleSheet("QPushButton { background-color: red; }");
                    }
                }
            }



            //si on rappuie sur une case invalide, on peut rejouer
            else {
                playerTurn = !playerTurn;
            }


            buttons[selectedRow][selectedCol]->setStyleSheet("");
            isSelected = false;

        }
    }



}