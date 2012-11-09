#include "Starbucks.h"
#include "rileycrStarbucks.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(){
	Entry* dataFile = new Entry[8000];
	ifstream in("Starbucks_2006.csv");

	for(int i = 0; i < 7655; i++){
		getline(in, dataFile[i].identifier, ',');

		in >> dataFile[i].x;
		in.get();

		in >> dataFile[i].y;
		in.get();

		//cout << dataFile[i].identifier << " " << dataFile[i].x << " " << dataFile[i].y << endl;
	}

	rileycrStarbucks* unsortedData = new rileycrStarbucks();

	unsortedData -> build(dataFile, 7655);
	Entry* nearest = unsortedData -> getNearest(.5,.5);

	cout << nearest -> identifier << " " << nearest -> x << " " << nearest -> y << endl;
};