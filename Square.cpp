/**
* Fichier définissant une fonction de la classe Square permettant de déterminer si l'une des case du plateau, un 'Square', est occupée par une pièce ou non.

* \file   Square.cpp
* \author Fares Laadjel 2297799 et Ayoub Marfouk 2295178
* \date   21 avril 2024
* Créé le 13 avril 2024
*/

#include "Square.h"

using namespace std;

bool Square::isPlayable(vector<pair<int, int>> possiblePosition) 
{	
	return find(possiblePosition.begin(), possiblePosition.end(), make_pair(i_, j_)) != possiblePosition.end();
}