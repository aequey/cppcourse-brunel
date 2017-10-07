#include <iostream>
#include <fstream>
#include <string>
#include "neuron.h"
#include "constants.h"

bool isInInterval(Time toTest, Time min, Time max);
void storeInFile(double toStore, std::ofstream& out);


int main() {
	
	const double extI(21.0);
	const Time extIBeginning(100);
	const Time extIEnd(900);
	
	Time currentTime(0.0);
	Neuron neuron;
	double currentImput(0.0);
	std::ofstream file;
	file.open("../res/potentials.txt");
	while (currentTime <= constants::SIM_TIME) {
		if (isInInterval(currentTime, extIBeginning, extIEnd)) {
			currentImput = extI;
		} else {
			currentImput = 0.0;
		}
		neuron.update(currentTime, currentImput);

		storeInFile(neuron.getMbPotential(), file);
		currentTime+=constants::H;
		
		

	}
	file.close();
	return 0;
}

bool isInInterval(Time toTest, Time min, Time max) {
	return (toTest >= min and toTest < max);
}

void storeInFile(double toStore, std::ofstream& out) {
	//~ std::ofstream out;
	//~ out.open(fileName);
	out << toStore <<std::endl;
	//~ out.close();
}



