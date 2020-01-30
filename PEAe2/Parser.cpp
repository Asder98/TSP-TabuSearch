#include "Parser.h"
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <conio.h>
#include <list>
#include <chrono>
#include <string>
#include <ctime>
#include <sstream>
#include <utility>
#include <vector>
#include <math.h>

using namespace std;

Parser::Parser()
{
	doData();
	//problem->tabuAlgorythm();
}

Parser::Parser(string txt)
{
	doData(txt);
	//problem->tabuAlgorythm();
}


Parser::~Parser()
{
	delete problem;
}

void Parser::doData(string txt) {	//do pomiarów
	//ifstream file;
	//string txt;
	//cout << "Podaj nazwe pliku: ";
	//cin >> txt;
	cout << endl;
	string a;
	string b;
	string treeType = "atsp";
	problem = NULL;
	int z = 0;
	int stop = 0;
	int counter = 0;
	string line;
	istringstream iss;
	file.open(txt.c_str());
	while (file.good()) {
		file >> a;
		cout << "Nazwa pliku: " << endl;
		cout << a << endl;
		file >> a;
		cout << "Wierzcholki: " << a << endl;
		z = stoi(a);
		problem = new TabuSearch(z);
		z = 0;

		while (a != "EOF") {
			for (int i = 0; i < problem->verN; i++) {
				file >> a;
				if (a != "EOF") {
					problem->matrix[counter][i] = stoi(a);
				}
			}
			counter++;
		}

	}
	//cout << "Udalo sie utworzyc tablice elementow. \n";
	//problem->printMatrix();
	cout << endl;
	file.close();
}


void Parser::doData() {	//do manualnego wprowadzania
	//ifstream file;
	string txt;
	cout << "Podaj nazwe pliku: ";
	cin >> txt;
	cout << endl;
	string a;
	string b;
	string treeType = "NULL";
	problem = NULL;
	int z = 0;
	int stop = 0;
	int counter = 0;
	string line;
	istringstream iss;
	file.open(txt.c_str());
	while (file.good()) {
		file >> a;
		cout << "Nazwa pliku: " << endl;
		cout << a << endl;
		file >> a;
		cout << a << " to nasze wierzcholki" << endl;
		z = stoi(a);
		problem = new TabuSearch(z);
		z = 0;

		while (a != "EOF") {
				for (int i = 0; i < problem->verN; i++) {
					file >> a;
					if (a != "EOF") {
						problem->matrix[counter][i] = stoi(a);
					}
				}
				counter++;
		}
		
	}
	cout << "Udalo sie utworzyc tablice elementow. \n";
	problem->printMatrix();
	cout << endl;
	file.close();
}