#include <iostream>
#include "Neuron.h"
#include "Simulation.h"

int main() {
	
	/*
	const double extI(0.0);
	const Milliseconds extIBeginning(0.0);
	const Milliseconds extIEnd(400.0);
	*/
	Simulation sim(100.0, "../res/data.dat");
	//~ sim.simulateTwoNeurons(extI, extIBeginning, extIEnd);
	sim.simulateNetwork();
	return 0;
}
