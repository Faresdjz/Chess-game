/**
* Fichier déclarant la classe Projet etles différentes fonctions nécessaires à la création et l'affichage de l'interface du jeu d'échecs et à l'agencement et au bon fonctionnement des boutons présents sur cette dernière.

* \file   Projet.h
* \author Fares Laadjel 2297799 et Ayoub Marfouk 2295178
* \date   21 avril 2024
* Créé le 13 avril 2024
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