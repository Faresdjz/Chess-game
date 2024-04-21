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


enum class TYPE {
	king, bishop, rook
};



const QString BlackKing = ":/Projet/image echec/Chess_kdt60.png";
const QString BlackRook = ":/Projet/image echec/Chess_rdt60.png";
const QString BlackBishop = ":/Projet/image echec/Chess_pdt60.png";
const QString WhiteKing = ":/Projet/image echec/Chess_klt60.png";
const QString WhiteRook = ":/Projet/image echec/Chess_rlt60.png";
const QString WhiteBishop = ":/Projet/image echec/Chess_plt60.png";




