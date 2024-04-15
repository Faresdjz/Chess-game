#include "Projet.h"

Projet::Projet(QWidget *parent)
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


    //création de la grille de boutton
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            buttons[i][j] = new QPushButton();
            buttons[i][j]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            gridLayout->addWidget(buttons[i][j], i, j);
            connect(buttons[i][j], &QPushButton::clicked, [this, i, j] {movePiece(i, j); });

        }
    }

    box->addWidget(windowGrid, 2);
    box->addWidget(windowText, 1);

    textLayout->addWidget(label);
    
}

Projet::~Projet()
{}

void Projet::loadRessources() {

    //tentative pour éviter de load les icons durant le code
    iconRessources["BlackKing"] = QIcon(BlackKing);
    iconRessources["BlackBishop"] = QIcon(BlackBishop);
    iconRessources["BlackRook"] = QIcon(BlackRook);
    iconRessources["WhiteKing"] = QIcon(WhiteKing);
    iconRessources["WhiteBishop"] = QIcon(WhiteBishop);
    iconRessources["WhiteRook"] = QIcon(WhiteRook);
}

void Projet::setNewGame() {

    loadRessources();

    //try catch

    buttons[7][3]->setIcon(iconRessources["BlackKing"]);
    board.addPiece(7, 3, TYPE::king, false);

    buttons[7][4]->setIcon(iconRessources["BlackBishop"]);
    board.addPiece(7, 4, TYPE::bishop, false);

    buttons[7][2]->setIcon(iconRessources["BlackRook"]);
    board.addPiece(7, 2, TYPE::rook, false);

    buttons[0][3]->setIcon(iconRessources["WhiteKing"]);
    board.addPiece(0, 3, TYPE::king, true);

    buttons[0][4]->setIcon(iconRessources["WhiteBishop"]);
    board.addPiece(0, 4, TYPE::bishop, true);

    buttons[0][2]->setIcon(iconRessources["WhiteRook"]);
    board.addPiece(0, 2, TYPE::rook, true);


}

void Projet::movePiece(int row, int col) {

    if (!isSelected) { //premier appui
        board.updateGame();
        if (board.items[row][col]->piece!=nullptr) {
            if (playerTurn == board.items[row][col]->piece->color) {

                selectedRow = row;
                selectedCol = col;
                selectedIcon = buttons[row][col]->icon();
                isSelected = true;
                playerTurn = !playerTurn;
                updateText();
                

                

                //on highlight la case selectionne
                buttons[row][col]->setStyleSheet("QPushButton { background-color: yellow; }");

                for (const auto& elem : board.items[selectedRow][selectedCol]->piece->possiblePosition) {
                    buttons[elem.first][elem.second]->setStyleSheet("QPushButton { background-color: yellow; }");
                }

            }

        }
    }
    else { //deuxieme appui

        //on eteint les cases jaunes proposées
        for (const auto& elem : board.items[selectedRow][selectedCol]->piece->possiblePosition) {
            buttons[elem.first][elem.second]->setStyleSheet(" ");
        }

        //si on rappuie sur notre case, on peut rejouer
        if (board.items[row][col] == board.items[selectedRow][selectedCol]) {
            playerTurn = !playerTurn;
        }

        //si la case est vide ou si la case correspond a une position dans le vecteur de position
        if (board.items[row][col]->isPlayable(board.items[selectedRow][selectedCol]->piece->possiblePosition)) {

            //on swap, donc delete un et deplacer lautre
            board.items[row][col]->piece = board.items[selectedRow][selectedCol]->piece;
            board.items[selectedRow][selectedCol]->piece = nullptr;

            //on reset le boutton initiale
            buttons[selectedRow][selectedCol]->setIcon(QIcon(" "));

            //on set le boutton de la case choisi
            buttons[row][col]->setIcon(selectedIcon);
            board.items[row][col]->piece->setPosition(row, col, board.items);

        }

        buttons[selectedRow][selectedCol]->setStyleSheet("");
        isSelected = false;

    }
}


void Projet::updateText() {
    if (playerTurn == true) {
        delete label;
        label = new QLabel("white's turn");
    }
    else {
        delete label;
        label = new QLabel("black's turn");
    }
}