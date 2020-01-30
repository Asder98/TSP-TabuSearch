#include "TabuList.h"
#include "TabuSearch.h"
#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <utility>
#include <vector>
#include <time.h>


using namespace std;

TabuSearch::TabuSearch() {
	verN = 0;
	matrix = NULL;
	finalCost = 0;
	finalPath = NULL;
	list = NULL;
}

TabuSearch::TabuSearch(int ver) {
	verN = 0;
	matrix = NULL;
	finalCost = 0;
	finalPath = NULL;
	list = NULL;
	verN = ver;
	matrix = new int* [ver];
	for (int i = 0; i < verN; i++) {
		matrix[i] = new int[verN];
	}
	finalCost = 0;
	finalPath = new int[verN];
	list = new TabuList(verN);
	iterationN = 1000;
}

void TabuSearch::swapVer(int verS, int verE, int* pathFrom, int* pathTo) {
	pathTo[verS] = pathFrom[verE];
	pathTo[verE] = pathFrom[verS];
}

void TabuSearch::swapVer(int verS, int verE, int* path) {
	int temp = 0;;
	temp = path[verS];
	path[verS] = path[verE];
	path[verE] = temp;
}

void TabuSearch::TS() {
	//wybranie najlepszej sciezki algorytmem zachlannym
	//przypisanie kosztu sciezki do najlepszego oraz do najlepszej sciezki
	greedy();
	finalCost = getPathCost(finalPath);
	/*cout << "Algorytm zachlanny wyznaczyl sciezke:\n";
	printPath();
	cout << "Jej koszt to: " << finalCost << endl;*/
	int* newFinalPath = NULL;
	int* bestToCopy = NULL;
	int newFinalCost = 0, iterrationN = 1000;
	newFinalPath = new int[verN];
	bestToCopy = new int[verN];
	copyPaths(finalPath, bestToCopy);
	copyPaths(finalPath, newFinalPath);
	newFinalCost = getPathCost(finalPath);
	for (int i = 0; i < iterrationN; i++) {
		cout << "przejscie: " << i + 1 << endl;
		newFinalPath = getBestNeighbour(list, newFinalPath);
		newFinalCost = getPathCost(newFinalPath);
		if (newFinalCost < finalCost) {
			//copyPaths(newFinalPath, finalPath);
			finalCost = newFinalCost;
			//cout << "Znaleziono lepsze rozwiazanie: " << newFinalCost << endl;
			//cout << "Sciezka: ";
			//printPath(newFinalPath);
			//cout << endl;
			//cout << endl << "Lista Tabu:\n";
			//list->printList();
			//cout << endl;
		}
		if (list->diver) {
			if (getPathCost(bestToCopy) > getPathCost(newFinalPath)) {
				bestToCopy = NULL;
				bestToCopy = new int[verN];
				copyPaths(newFinalPath, bestToCopy);
			}
			copyPaths(finalPath, newFinalPath);
			finalCost = getPathCost(finalPath);
			list->diver = false;
		}
		//cout << endl;
		//printPath();
		//cout << endl;
		//list->printList();
	}
	if (getPathCost(finalPath) > getPathCost(bestToCopy)) {
		copyPaths(bestToCopy, finalPath);
		finalCost = getPathCost(finalPath);
	}
	cout << endl << "Algorytm Tabu Search znalazl wynik: " << finalCost << endl;
	cout << "Sciezka: ";
	printPath();
}

int* TabuSearch::getBestNeighbour(TabuList* list, int* bestPath) {
	int* newBestPath = new int[verN];
	copyPaths(bestPath, newBestPath);
	//cout << endl;
	//printPath(newBestPath);
	int newBestCost = getPathCost(bestPath);
	int verS = 0, verE = 0;
	int* afterSwapPath = NULL;
	int afterSwapCost = 0, selectionResult = 0;
	//bool firstChange = true;
	for (int i = 1; i < verN - 1; i++) {
		for (int j = i + 1; j < verN - 1; j++) {
			//jezeli nie idziemy po krawedzi macierzy
			if (i != j) {
				afterSwapPath = new int[verN];
				copyPaths(bestPath, afterSwapPath);
				//cout << endl;
				//printPath(afterSwapPath);
				swapVer(i, j, bestPath, afterSwapPath);
				//cout << endl;
				//printPath(afterSwapPath);
				afterSwapCost = getPathCost(afterSwapPath);
				//kryterium doboru jesli funkcja f(x0) - f(x) dodatnia i ruch nie jest na tabu liscie
				if (((getPathCost(bestPath) - afterSwapCost) > selectionResult) && list->matrix[i][j] == 0) {
					//przypisujemy wierzcholek startowy i koncowy
					//firstChange = false;
					cout << "Zmiana najlepszego rozwiazania\n";
					verS = i;
					verE = j;
					//selectionResult ma teraz wartosc roznicy starego rozwianzania i nowego
					selectionResult = getPathCost(bestPath) - afterSwapCost;
					//nowy koszt najlepszej sciezki
					newBestCost = afterSwapCost;
					//kopiujemy nowo zanleziona do zwracanej
					copyPaths(afterSwapPath, newBestPath);
					//cout << endl;
					//printPath(newBestPath);
				}
				else {
					//chyba ze spelnione jest kryterium aspiracji ale ruch nie jest w przestrzeni zabronionej
					if (afterSwapCost < finalCost && list->matrix[i][j] != -1) {
						//przypisujemy wierzcholek startowy i koncowy
						//firstChange = false;
						cout << "Zmiana najlepszego rozwiazania\n";
						verS = i;
						verE = j;
						//selectionResult ma teraz wartosc roznicy starego rozwianzania i nowego
						selectionResult = getPathCost(bestPath) - afterSwapCost;
						//nowy koszt najlepszej sciezki
						newBestCost = afterSwapCost;
						//kopiujemy nowo zanleziona do zwracanej
						copyPaths(afterSwapPath, newBestPath);
						//cout << endl;
						//printPath(newBestPath);
					}
				}
			}
		}
	}
	//teraz sprawddzamy czy znaleziono lepsze rozwiazanie
	//jesli tak to ruch dodajemy do listy Tabu i dekremetujemy Tabu liste
	//jesli nie to algorytm musi stweirdzic czy zaszla zmiana, jesli nie to zwiekszamy licznik dywersyfikacji
	if (verS != 0) {
		list->decCadency();
		list->addTabu(verS, verE);
		list->resetDivC();
	}
	else {
		list->increaseDivC();
	}
	delete[] afterSwapPath;
	return newBestPath;
}

void TabuSearch::copyPaths(int* from, int* to) {
	for (int i = 0; i < verN; i++) {
		to[i] = from[i];
	}
}

int TabuSearch::getPathCost(int* path) {
	int cost = 0;
	for (int i = 0; i < verN - 1; i++) {
		cost += matrix[path[i]][path[i + 1]];
	}
	cost += matrix[path[verN - 1]][0];
	return cost;
}

void TabuSearch::printPath() {
	for (int i = 0; i < verN; i++) {
		if (i == verN - 1) {
			cout << finalPath[i] << " ---> 0" << endl;
		}
		else {
			cout << finalPath[i] << " ---> ";
		}
	}
}

void TabuSearch::printPath(int* path) {
	for (int i = 0; i < verN; i++) {
		if (i == verN - 1) {
			cout << path[i] << " ---> 0" << endl;
		}
		else {
			cout << path[i] << " ---> ";
		}
	}
}

void TabuSearch::printMatrix() {
	for (int i = 0; i < verN; i++) {
		for (int j = 0; j < verN; j++) {
			if (matrix[i][j] == -1) {
				cout << matrix[i][j] << " ";
			}
			else {
				if (matrix[i][j] < 10 && matrix[i][j] >= 0) cout << matrix[i][j] << "  ";
				if (matrix[i][j] < 100 && matrix[i][j]>9) cout << matrix[i][j] << " ";
				if (matrix[i][j] < 1000 && matrix[i][j]>99) cout << matrix[i][j];
			}
			cout << " ";
		}
		cout << endl;
	}
}

void TabuSearch::greedy() {
	bool* vertices = new bool[verN];
	for (int i = 0; i < verN; i++) {
		vertices[i] = false;
	}
	vertices[0] = true;
	bool stop = false;
	int* min = new int[2];
	finalPath[0] = 0;
	int counter = 0;
	min[1] = 0;
	while (!stop) {

		min[0] = 999999;
		counter++;
		for (int j = 0; j < verN; j++) {
			if (matrix[min[1]][j] != -1 && matrix[min[1]][j] < min[0] && vertices[j] == false) {
				finalPath[counter] = j;
				min[0] = matrix[min[1]][j];

			}
		}
		vertices[finalPath[counter]] = true;
		min[1] = finalPath[counter];
		if (greedyAll(vertices)) stop = true;
	}
	delete[] vertices;
	delete[] min;
}

void TabuSearch::random() {
	for (int i = 0; i <= verN+1; i++) {
		finalPath[i] = i;
	}
	// Seed our random number generator.
	srand((int)time(NULL));
	int size = verN;
	// Create large number of swaps 
	// This example takes the size and times it by 20 for the number of swaps
	for (int i = 0; i < (size); i++) {
		// Generate random values for subscripts, not values!
		int randvalue1 = (rand() % (size-1)) + 1;
		int randvalue2 = (rand() % (size-1)) + 1;

		int temp = finalPath[randvalue1];
		finalPath[randvalue1] = finalPath[randvalue2];
		finalPath[randvalue2] = temp;
	}
	
}

bool TabuSearch::greedyAll(bool* vertices) {
	for (int i = 0; i < verN; i++) {
		if (vertices[i] == false) return false;
	}
	return true;
}

void TabuSearch::tabuAlgorythm() {
	//wyznaczamy algorytmem zachlannym sciezka poczatkowa i jej koszt
	greedy();
	//random();
	finalCost = getPathCost(finalPath);
	cout << "Algorytm zachlanny wyznaczyl sciezke:\n";
	printPath();
	cout << "Jej koszt to: " << finalCost << endl;
	int* rememberFinalPath = NULL;
	rememberFinalPath = new int[verN];
	int* bestFianlPath;
	bestFianlPath = new int[verN];
	copyPaths(finalPath, bestFianlPath);
	copyPaths(finalPath, rememberFinalPath);
	//powolujemy sciezki pomocnicze
	//int *bestPath = NULL;
	//bestPath = new int[verN];
	//copyPaths(finalPath, bestPath);
	int* newBestPath = NULL;
	newBestPath = new int[verN];
	int newBestCost;
	copyPaths(finalPath, newBestPath);
	newBestCost = getPathCost(newBestPath);
	//miasta potrzebne do tabu listy
	int ver1 = 0, ver2 = 0, min = 0;
	//wykonuje sie iteracji razy
	while (iterationN > 0) {
		ver1 = 0;
		ver2 = 0;
		min = MAXINT;
		list->decTabu();
		//cout << "Do kolejnej iteracji wchodzi sciezka: ";
		//printPath(finalPath);
		//cout << endl;
		//copyPaths(bestPath, newBestPath);
		//printPath(newBestPath);
		for (int i = 1; i < verN; i++) {
			for (int j = i + 1; j < verN; j++) {
				if (i != j) {	//wywaiæ, bez sensu
					//copyPaths(finalPath, newBestPath);
					//zamiana kolejnosci miast
					//swapVer(i, j, newBestPath);
					//newBestCost = getPathCost(newBestPath);
					//sprawdzenie zamianay i wyliczenie sciezki

					swapVer(i, j, newBestPath);
					newBestCost = getPathCost(newBestPath);
					swapVer(j, i, newBestPath);
					//KRYTERIUM ASPIRACJI
					//chyba ze wynik jest najlepszy z dotychczas znalezionych
					if (newBestCost < finalCost && list->dontAllowMove(i, j)) {
						//cout << "Znaleziona droga lepsza od najlepszej\n";
						ver1 = i;
						ver2 = j;
						min = newBestCost;
						//finalCost = newBestCost;
						//copyPaths(newBestPath, finalPath);
						if (list->cadency == 0) {
							list->cadency = verN;
						}
					}
					//TABU LISTA
					//jesli udalo sie znalezc lepszy wynik i ruch nie jest zabroniony
					if (newBestCost < min && list->allowMove(i, j)) {
						//cout << "mniejsze znalezione nie zabronione " << ver1 << " " << ver2 << endl;
						ver1 = i;
						ver2 = j;
						min = newBestCost;
						//bestCost = newBestCost;
						//copyPaths(newBestPath, bestPath);
					}
				}
			}
		}
		//cout << "Po iteracji zostala wyznaczona sciezka: ";
		//printPath(bestPath);
		//cout << endl;
		//Po przejsciu przez dwie petle for mamy najlepszego znalezionego sasiada

		if (ver1 != 0) {
			//cout << "Do tabu dodajemy " << ver1 << " oraz " << ver2 << endl;
			swapVer(ver1, ver2, newBestPath);
			list->addTabu(ver1, ver2);
			//copyPaths(newBestPath, bestPath);
			//printPath(newBestPath);
			//bestCost = getPathCost(bestPath);
		}
		//Licznik dywersyfikacji
		if (min < finalCost) {
			list->resetDivC();
			copyPaths(newBestPath, finalPath);
			finalCost = getPathCost(finalPath);
			list->unDiversification();
		}
		else {
			list->increaseDivC();
		}
		//Ewentualna dywersyfiakcja
		if (list->diver) {
			//cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n!!!!!!!!!!!!!!!!!!!!DYWERSYFIKACJA!!!!!!!!!!!!!!!!!!!!!!!\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
			//powrot do poprzedniej najlepszej sciezki
			if (getPathCost(finalPath) < getPathCost(bestFianlPath)) {
				copyPaths(finalPath, bestFianlPath);
			}
			copyPaths(rememberFinalPath, finalPath);
			finalCost = getPathCost(finalPath);
			copyPaths(finalPath, newBestPath);
			list->diver = false;
		}
		//list->printList();
		iterationN--;
		//newBestPath = NULL;
	}
	if (finalCost > getPathCost(bestFianlPath)) {
		copyPaths(bestFianlPath, finalPath);
		finalCost = getPathCost(finalPath);
	}
	//cout << endl << "Algorytm zachlanny znalazl rozwiazanie o wyniku: " << getPathCost(rememberFinalPath) << endl;
	//cout << "Sciezka: ";
	//printPath(rememberFinalPath);
	//cout << endl;
	cout << endl << "Algorytm TabuSearch znalazl rozwiazanie o wyniku: " << finalCost << endl;
	//cout << "Sciezka: ";
	//printPath();
	delete rememberFinalPath;
	delete bestFianlPath;
	//delete bestPath;
	delete newBestPath;
}