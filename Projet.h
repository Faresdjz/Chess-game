#pragma once
#include "IncludeFile.h"
#include "Board.h"

namespace chessui {



    class Projet : public QMainWindow
    {
        Q_OBJECT

    public:

        Projet(QWidget* parent = nullptr);
        ~Projet();

        void loadRessources();

        void setNewGame();

        void play(int row, int col);

        void addPieceUi(int i, int j, TYPE type, bool color );


        QLabel* label;
        QPushButton* buttons[8][8];
        Board board;
        bool playerTurn = false;
        bool isSelected = false;
        int selectedRow = -1;
        int selectedCol = -1;
        QIcon selectedIcon;
        QMap<std::string, QIcon> iconRessources;

    private:
        Ui::ProjetClass ui;
    };
}