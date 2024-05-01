/**
* Programme permettant de lancer un jeu d'echecs comportant 3 pieces, soient un roi, un fou et une tour de chaque couleur. 

* \file   main.cpp
* \author Fares Laadjel 2297799 et Ayoub Marfouk 2295178
* \date   21 avril 2024
* Cree le 13 avril 2024
*/

#include "Projet.h"
#include <QtWidgets/QApplication>


#include "bibliotheque_cours.hpp"
#include "verification_allocation.hpp"
#include "debogage_memoire.hpp"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);



    chessui::Projet w;
    //w.setNewGame();
    w.show();
    return a.exec();
}
