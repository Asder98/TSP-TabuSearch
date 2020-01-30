#pragma once
#include "TabuSearch.h"
#include "TabuList.h"
#include <stdio.h>
#include <windows.h>
#include <fstream>
#include <chrono>
#include <string>

class Parser {
public:
	std::ifstream file;
	TabuSearch* problem;
	void doData(string txt);
	void doData();
	//void doData(string path);
	Parser();
	Parser(string txt);
	~Parser();
};

