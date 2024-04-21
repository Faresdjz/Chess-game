#pragma once

#include <iostream>
#include <vector>
#include <utility>
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
#include <string.h>
#include <memory>
#include "ui_Projet.h"

using namespace std;

enum class TYPE {
	king, bishop, rook
};

enum class GAMESTATE {
	whiteTurn, blackTurn
};



const QString BlackKing = ":/Projet/image echec/Chess_kdt60.png";
const QString BlackRook = ":/Projet/image echec/Chess_rdt60.png";
const QString BlackBishop = ":/Projet/image echec/Chess_pdt60.png";
const QString WhiteKing = ":/Projet/image echec/Chess_klt60.png";
const QString WhiteRook = ":/Projet/image echec/Chess_rlt60.png";
const QString WhiteBishop = ":/Projet/image echec/Chess_plt60.png";

//
//const QIcon BlackKingIcon = QIcon(QString::fromStdString(":/Projet/image echec/Chess_kdt60.png"));
//const QIcon BlackRookIcon = QIcon(QString::fromStdString(":/Projet/image echec/Chess_rdt60.png"));
//const QIcon BlackBishopIcon = QIcon(QString::fromStdString(":/Projet/image echec/Chess_pdt60.png"));
//const QIcon WhiteKingIcon = QIcon(QString::fromStdString(":/Projet/image echec/Chess_klt60.png"));
//const QIcon WhiteRookIcon = QIcon(QString::fromStdString(":/Projet/image echec/Chess_rlt60.png"));
//const QIcon WhiteBishopIcon = QIcon(QString::fromStdString(":/Projet/image echec/Chess_plt60.png"));
//const QIcon EmptyIcon = QIcon(QString::fromStdString(" "));




