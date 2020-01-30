// pea_2.cpp : Defines the entry point for the console application.
//

#include "TabuList.h"
#include "TabuSearch.h"
#include "Parser.h"
#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <cstdio>
#include <utility>
#include <vector>
#include <chrono>
#include <thread>


using namespace std;

int main() {
	//Parser* prog = new Parser();
	//auto start_time = chrono::high_resolution_clock::now();
	//prog->problem->tabuAlgorythm();
	//auto end_time = chrono::high_resolution_clock::now();
	//auto time = end_time - start_time;
	//cout << "Czas wykonania algorytmu: " << time / chrono::milliseconds(1) << "ms" << endl;
	//prog->problem->tabuAlgorythm();
	//delete prog;

	//for (int i = 0; i < 5; i++) {
	//	//this_thread::sleep_until(chrono::system_clock::now() + chrono::seconds(1));
	//	Parser* prog = new Parser("data171.txt");
	//	auto start_time = chrono::high_resolution_clock::now();
	//	prog->problem->tabuAlgorythm();
	//	auto end_time = chrono::high_resolution_clock::now();
	//	auto time = end_time - start_time;
	//	cout << "Czas wykonania algorytmu: " << time / chrono::milliseconds(1) << "ms" << endl;
	//	delete prog;
	//}

		Parser* prog = new Parser("datatsp42.txt");
		auto start_time = chrono::high_resolution_clock::now();
		prog->problem->tabuAlgorythm();
		auto end_time = chrono::high_resolution_clock::now();
		auto time = end_time - start_time;
		cout << "Czas wykonania algorytmu: " << time / chrono::milliseconds(1) << "ms" << endl;
		delete prog;

	//prog = new Parser("datatsp42.txt");
	//start_time = chrono::high_resolution_clock::now();
	//prog->problem->tabuAlgorythm();
	//end_time = chrono::high_resolution_clock::now();
	//time = end_time - start_time;
	//cout << "Czas wykonania algorytmu: " << time / chrono::milliseconds(1) << "ms" << endl;
	//delete prog;

	//prog = new Parser("datatsp120.txt");
	//start_time = chrono::high_resolution_clock::now();
	//prog->problem->tabuAlgorythm();
	//end_time = chrono::high_resolution_clock::now();
	//time = end_time - start_time;
	//cout << "Czas wykonania algorytmu: " << time / chrono::milliseconds(1) << "ms" << endl;

	//prog = new Parser("data17.txt");
	//start_time = chrono::high_resolution_clock::now();
	//prog->problem->tabuAlgorythm();
	//end_time = chrono::high_resolution_clock::now();
	//time = end_time - start_time;
	//cout << "Czas wykonania algorytmu: " << time / chrono::milliseconds(1) << "ms" << endl;
	//delete prog;

	//prog = new Parser("data43.txt");
	//start_time = chrono::high_resolution_clock::now();
	//prog->problem->tabuAlgorythm();
	//end_time = chrono::high_resolution_clock::now();
	//time = end_time - start_time;
	//cout << "Czas wykonania algorytmu: " << time / chrono::milliseconds(1) << "ms" << endl;
	//delete prog;

	//prog = new Parser("data100.txt");
	//start_time = chrono::high_resolution_clock::now();
	//prog->problem->tabuAlgorythm();
	//end_time = chrono::high_resolution_clock::now();
	//time = end_time - start_time;
	//cout << "Czas wykonania algorytmu: " << time / chrono::milliseconds(1) << "ms" << endl;

	//delete prog;
	/*string const path1 = "C:/Filip/proj/pea2/TSPgr17_4_100.txt";
	ofstream plik1(path1.c_str());
	TSP p;
	p.doDataTSP3("gr17.tsp");
	srand(time(NULL));
	if (plik1) {
		for (int j = 0; j < 1; j++) {
			clock_t start = clock();
			prog->problem->tabuAlgorythm();
			clock_t end = clock();
			double time = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;
			plik1 << time << endl;
			prog = NULL;
			prog = new Parser("C:\Filip\proj\pea2\TSPgr17_2_100.txt");
		}

	}
	plik1.close();
	prog = NULL;
	prog = new Parser("gr21.tsp");
	string const path2 = "C:/Filip/proj/pea2/TSPgr21_4_100.txt";
	ofstream plik2(path2.c_str());
	p.doDataTSP3("gr21.tsp");
	srand(time(NULL));
	if (plik2) {
		for (int j = 0; j < 1; j++) {
			clock_t start = clock();
			prog->problem->tabuAlgorythm();
			clock_t end = clock();
			double time = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;
			plik2 << time << endl;
			delete prog;
			prog = new Parser("ftv33.atsp");
		}

	}
	plik2.close();
	prog = NULL;;
	prog = new Parser("gr24.tsp");
	string const path3 = "C:/Filip/proj/pea2/TSPgr24_4_100.txt";
	ofstream plik3(path3.c_str());
	p.doDataTSP3("gr24.tsp");
	srand(time(NULL));
	if (plik3) {
		for (int j = 0; j < 1; j++) {
			clock_t start = clock();
			prog->problem->tabuAlgorythm();
			clock_t end = clock();
			double time = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;
			plik3 << time << endl;
			delete prog;
			prog = new Parser("ftv44.atsp");
		}

	}
	plik3.close();
	prog = NULL;
	prog = new Parser("br17.atsp");
	string const path4 = "C:/Filip/proj/pea2/ATSPbr17_4_100.txt";
	ofstream plik4(path4.c_str());
	TSP p;
	p.doDataTSP3("gr17.tsp");
	srand(time(NULL));
	if (plik4) {
		for (int j = 0; j < 1; j++) {

			clock_t start = clock();
			prog->problem->tabuAlgorythm();
			clock_t end = clock();
			double time = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;
			plik4 << time << endl;
			prog = NULL;
			prog = new Parser("br17.atsp");
		}

	}
	plik4.close();
	prog = NULL;
	prog = new Parser("ftv33.atsp");
	string const path5 = "C:/Filip/proj/pea2/ATSPftv33_4_100.txt";
	ofstream plik5(path5.c_str());
	p.doDataTSP3("gr21.tsp");
	srand(time(NULL));
	if (plik5) {
		for (int j = 0; j < 1; j++) {
			clock_t start = clock();
			prog->problem->tabuAlgorythm();
			clock_t end = clock();
			double time = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;
			plik5 << time << endl;
			delete prog;
			prog = new Parser("ftv33.atsp");
		}

	}
	plik5.close();
	prog = NULL;;
	prog = new Parser("ftv44.atsp");
	string const path6 = "C:/Filip/proj/pea2/ATSPftv44_4_100.txt";
	ofstream plik6(path6.c_str());
	p.doDataTSP3("gr24.tsp");
	srand(time(NULL));
	if (plik6) {
		for (int j = 0; j < 1; j++) {
			clock_t start = clock();
			prog->problem->tabuAlgorythm();
			clock_t end = clock();
			double time = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;
			plik6 << time << endl;
			delete prog;
			prog = new Parser("ftv44.atsp");
		}

	}
	plik6.close();*/
	//delete prog;
	_getch();
	//exit(10000);
	return 0;
}

