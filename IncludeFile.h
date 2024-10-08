/**
* Fichier incluant toutes les bibliotheques necessaires a la realisation du programme et declarant l'enum class des types de pieces.

* \file   IncludeFile.h
* \author Fares Laadjel 2297799 et Ayoub Marfouk 2295178
* \date   3 mai 2024
* Cree le 13 avril 2024
*/

#pragma once

#include <iostream>
#include <vector>
#include <utility>
#include <string.h>
#include <memory>

#include <QtWidgets/QApplication>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSizePolicy>
#include <QIcon>
#include <Qstring>
#include <QMap>
#include <QStyleFactory>
#include <QMenu>
#include <QAction>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <qfontdatabase.h>
#include <qcombobox.h> 

#include "ui_Projet.h"

#include "bibliotheque_cours.hpp"
#include "verification_allocation.hpp"
#include "debogage_memoire.hpp"

enum class Type {
	king, bishop, rook, none
};

//IMAGE SOURCE:
//https://commons.wikimedia.org/wiki/Category:PNG_chess_pieces/Standard_transparent

const QString BlackKing = ":/Projet/image echec/Chess_kdt60.png";
const QString BlackRook = ":/Projet/image echec/Chess_rdt60.png";
const QString BlackBishop = ":/Projet/image echec/Chess_bdt60.png";
const QString WhiteKing = ":/Projet/image echec/Chess_klt60.png";
const QString WhiteRook = ":/Projet/image echec/Chess_rlt60.png";
const QString WhiteBishop = ":/Projet/image echec/Chess_blt60.png";

const QString highlightSetUp = "QPushButton { background-color: rgba(255, 255, 0, 0.5); border: 1px solid rgba(255, 255, 0, 0.5); }";
const QString blackSquareSetUp = "background-color: #333333; border: 0;";
const QString lightSquareSetUp = "background-color: #1C1C1E; border: 0;";




