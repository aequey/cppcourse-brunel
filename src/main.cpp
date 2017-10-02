#include <iostream>
#include <fstream>
#include "neuron.h"
#include "constants.h"

bool isInInterval(Time toTest, Time min, Time max);


int main() {
	
	const double extI(7.0);
	const Time extIBeginning(100);
	const Time extIEnd(900);
	
	Time currentTime(0.0);
	Neuron neuron;
	double currentImput(0.0);
	while (currentTime <= constants::SIM_TIME) {
		if (isInInterval(currentTime, extIBeginning, extIEnd)) {
			currentImput = extI;
		} else {
			currentImput = 0.0;
		}
		//~ neuron.update();
		//~ storeInFile(neuron.getMbPotential(), "../res/potentials.txt");
		currentTime+=1;
	}
	return 0;
}

bool isInInterval(Time toTest, Time min, Time max) {
	return (toTest >= min and toTest < max);
}

