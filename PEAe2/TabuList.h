#pragma once
#include <utility>
#include <vector>

//Nasza TabuLista bedzie wielkosciowo taka sama macierza jak macierz przejsc
using namespace std;

struct Move {
	int verS;
	int verE;
};

class TabuList {
public:
	vector<pair<Move, int>> list;
	int tabuNumber;
	int** matrix;
	int verN;
	int diversificationCounter;
	bool diver;
	TabuList(int verN);
	void addTabu(int verS, int verE);
	void decCadency();
	void increaseDivC();
	void resetDivC();
	//void diversification();
	void printList();
	//-------------------
	int cadency;
	void deleteYoungest();
	void decTabu();
	void diversification();
	bool allowMove(int verS, int verE);
	bool dontAllowMove(int verS, int verE);
	void unDiversification();
};
