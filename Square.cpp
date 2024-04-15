#include "Square.h"

using namespace std;


bool Square::isPlayable(vector<pair<int, int>> possiblePosition) {
	
	return find(possiblePosition.begin(), possiblePosition.end(), make_pair(i_, j_)) != possiblePosition.end();

}