/**
* Fichier declarant la classe Projet et les differentes fonctions necessaires a la creation et l'affichage de l'interface du jeu d'echecs et a l'agencement et au bon fonctionnement des boutons presents sur cette derniere.

* \file   Projet.h
* \author Fares Laadjel 2297799 et Ayoub Marfouk 2295178
* \date   21 avril 2024
* Cree le 13 avril 2024
*/

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

        void removePieceUi(int i, int j, TYPE type);

        void removeAllPieceUi();

        void movePieceUi(int oldX, int oldY, int newX, int newY);

        void buttonSelected(int row, int col);

        void setDefaultGame();

        void swapPlayer();

        bool checkSituationUi();

        void resetColorScheme();


        QLabel* label1;
        QLabel* label2;
        QPushButton* buttons[8][8];
        Board board;
        QIcon selectedIcon;
        QMap<std::string, QIcon> iconRessources;
        bool playerTurn = false;
        bool isSelected = false;
        int selectedRow = -1;
        int selectedCol = -1;

    private:
        Ui::ProjetClass ui;
    };
}