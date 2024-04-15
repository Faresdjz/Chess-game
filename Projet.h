#pragma once
#include "IncludeFile.h"
#include "Board.h"

class Projet : public QMainWindow
{
    Q_OBJECT

public:

    Projet(QWidget *parent = nullptr);
    ~Projet();

    void loadRessources();

    void setNewGame();

    void movePiece(int row, int col);

    void updateText();

    QLabel* label;
    QPushButton* buttons[8][8];
    Board board;
    GAMESTATE gameState = GAMESTATE::blackTurn;
    bool playerTurn = false;
    bool isSelected = false;
    int selectedRow = -1;
    int selectedCol = -1;
    QIcon selectedIcon;
    QMap<string, QIcon> iconRessources;

private:
    Ui::ProjetClass ui;
};
