#pragma once
#include "TabuList.h"

class TabuSearch {
public:
	int** matrix;
	int verN;
	int finalCost;
	int* finalPath;
	TabuList* list;
	int iterationN;

	TabuSearch();
	TabuSearch(int verN);
	//void start();
	int getPathCost(int* path);
	void swapVer(int ver1, int ver2, int* pathFrom, int* pathTo);
	void printPath();
	void printPath(int* path);
	void copyPaths(int* from, int* to);
	void greedy();
	void random();
	bool greedyAll(bool* vertices);
	void printMatrix();
	//-------------
	void tabuAlgorythm();
	//-------------
	void TS();
	int* getBestNeighbour(TabuList* list, int* bestPath);
	void swapVer(int verS, int verE, int* path);
};
