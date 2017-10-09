#include <fstream>
#include "neuron.h"
#include "simulation.h"

int main() {
	
	const double extI(10);
	const Time extIBeginning(100);
	const Time extIEnd(400);
	
	Simulation sim;
	//~ sim.simulateANeuron(extI, extIBeginning, extIEnd);
	sim.simulateTwoNeurons(extI, extIBeginning, extIEnd);
	
	return 0;
}
