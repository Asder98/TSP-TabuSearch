#include <iostream>
#include <vector>
#include <utility>
#include <iterator>
#include "TabuList.h"

using namespace std;

TabuList::TabuList(int verN) {
	this->verN = verN;
	matrix = new int* [verN];
	for (int i = 0; i < verN; i++) {
		matrix[i] = new int[verN];
	}
	for (int i = 0; i < verN; i++) {
		for (int j = 0; j < verN; j++) {
			matrix[i][j] = 0;
			if (i == j) matrix[i][j] = -1;
		}
	}
	diver = false;
	diversificationCounter = 0;
	//cout << "Powstal nowy obiekt TabuList!\n";
	//----------------------------------------
	tabuNumber = 3 * verN;
	cadency = verN;
}

void TabuList::addTabu(int verS, int verE) {
	//int cadency = 0.2*verN;
	matrix[verS][verE] += cadency;
	matrix[verE][verS] += cadency;
	Move m;
	m.verS = verS;
	m.verE = verE;
	pair<Move, int> move;
	move = make_pair(m, cadency);
	if (list.size() <= tabuNumber) {
		list.push_back(move);
	}
	else {
		deleteYoungest();
		list.push_back(move);
	}

}

void TabuList::deleteYoungest() {
	int index, min = INT_MAX;
	for (int i = 0; i < list.size(); i++) {
		if (get<1>(list.at(i)) < min) {
			min = get<1>(list.at(i));
			index = i;
		}
	}
	list.erase(list.begin() + index);
}

void TabuList::decTabu() {
	vector<int> toDelete;
	for (int i = 0; i < list.size(); i++) {
		if ((list.at(i).second) >= 1) {
			list.at(i).second -= 1;
		}
		if ((list.at(i).second) == 0) {
			toDelete.push_back(i);
		}
	}
	for (int i = 0; i < toDelete.size(); i++) {
		list.erase(list.begin() + (toDelete.at(i) - i));
	}
}

/*void TabuList::diversification() {
vector<int> toDelete;
for (int i = 0; i<list.size(); i++) {
if ((list.at(i).second) >= 1) {
list.at(i).second = floor(list.at(i).second/2);
}
if ((list.at(i).second) == 0) {
toDelete.push_back(i);
}
}
for (int i = 0; i<toDelete.size(); i++) {
list.erase(list.begin() + (toDelete.at(i) - i));
}
cadency = floor(cadency / 2);
}*/

void TabuList::diversification() {
	vector<int> toDelete;
	for (int i = 0; i < list.size(); i++) {
		if ((list.at(i).second) >= 1) {
			list.at(i).second = -1;
		}
	}
	cadency = floor(cadency / 2);
	diver = true;
}

void TabuList::unDiversification() {
	for (auto it = list.begin(); it != list.end(); ++it)
	{
		it->second *= 2;
	}
	cadency *= 2;
}

bool TabuList::allowMove(int verS, int verE) {
	for (int i = 0; i < list.size(); i++) {
		if (((list.at(i).first).verS == verS && (list.at(i).first).verE == verE) || ((list.at(i).first).verS == verE && (list.at(i).first).verE == verS)) {
			//cout << "Ruch " << verS << " <-> " << verE << " znajduje sie na liscie!\n";
			return false;
		}
	}
	//cout << "Ruch " << verS << " <-> " << verE << " nie znajduje sie na liscie!\n";
	return true;
}

bool TabuList::dontAllowMove(int verS, int verE) {
	for (int i = 0; i < list.size(); i++) {
		if (((list.at(i).first).verS == verS && (list.at(i).first).verE == verE && (list.at(i).second == -1)
			|| ((list.at(i).first).verS == verE && (list.at(i).first).verE == verS && (list.at(i).second == -1)))) {
			//cout << "Ruch " << verS << " <-> " << verE << " ZABRONIONY!\n";
			return false;
		}
	}
	//cout << "Ruch " << verS << " <-> " << verE << " NIE ZABRONIONY!\n";
	return true;
}

void TabuList::decCadency() {
	for (int i = 0; i < verN; i++) {
		for (int j = 0; j < verN; j++) {
			if (matrix[i][j] != 0 && matrix[i][j] != -1) {
				matrix[i][j] -= 1;
			}
		}
	}
}

void TabuList::increaseDivC() {
	diversificationCounter++;
	if (diversificationCounter >= 5) {
		diversification();
		resetDivC();
	}
}

void TabuList::resetDivC() {
	diversificationCounter = 0;
}

//dywersufikacja polega na ograncizeniu obszarow ktore czesto sa brane pod uwage
/*void TabuList::diversification() {
cout << "Nastapila dywersyfikacja dla: \n";
for (int i = 0; i < verN; i++) {
for (int j = 0; j < verN; j++) {
if (matrix[i][j] == -1 && i != j) {
matrix[i][j] = 0;
}
if (matrix[i][j] != 0 && matrix[i][j] != -1) {
//blokujemy ruch poprzez zwiekszenie kadencji
matrix[i][j] = -1;
cout << "ruchu " << i << " -> " << j << endl;
}
}
}
diver = true;
}*/

void TabuList::printList() {
	/*for (int i = 0; i < verN; i++) {
	for (int j = 0; j < verN; j++) {
	cout << matrix[i][j] << " ";
	}
	cout << endl;
	}*/
	for (int i = 0; i < list.size(); i++) {
		cout << "Zabroniony ruch: " << list.at(i).first.verS << " <-> " << list.at(i).first.verE << " o kadencji: " << list.at(i).second << endl;
	}
}