#ifndef CAFE_H
#define CAFE_H

#include <string>
#include <fstream>
#include "Barista.h"
using namespace std;

// RNG
void seedRng(unsigned s);
int  nextInt(int minIncl, int maxIncl);

// File I/O & menu
bool openMenu(ifstream& fin, const string& path);
bool readMenuLine(istream& in, string& item, int& weight); // parse "ITEM,weight"
string chooseItemWeighted(ifstream& fin); // re-scans file; uses static spot-check

// Simulation
void processOrder(Barista& worker, const string& menuPath);
void summarizeShift(const Barista& worker);

// (Optional) extern demo; define in AppConfig.cpp if you want
extern string APP_VERSION;

#endif
