#include <fstream>
#include "neuron.h"
#include "simulation.h"

int main() {
	
	const double extI(10);
	const Milliseconds extIBeginning(100);
	const Milliseconds extIEnd(400);
	
	Simulation sim;
	//~ sim.simulateANeuron(extI, extIBeginning, extIEnd);
	sim.simulateTwoNeurons(extI, extIBeginning, extIEnd);
	
	return 0;
}
