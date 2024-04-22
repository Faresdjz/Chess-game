/**
* Fichier d�finissant une fonction de la classe Square permettant de d�terminer si l'une des case du plateau, un 'Square', est occup�e par une pi�ce ou non.

* \file   Square.cpp
* \author Fares Laadjel 2297799 et Ayoub Marfouk 2295178
* \date   21 avril 2024
* Cr�� le 13 avril 2024
*/

#include "Square.h"

using namespace std;

bool Square::isPlayable(vector<pair<int, int>> possiblePosition) 
{	
	return find(possiblePosition.begin(), possiblePosition.end(), make_pair(i_, j_)) != possiblePosition.end();
}