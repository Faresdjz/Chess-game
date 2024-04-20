#include "Projet.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
    chessui::Projet w;
    w.setNewGame();
    //w.rolePlay();
    w.show();
    return a.exec();
}
