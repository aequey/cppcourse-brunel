#include <fstream>
#include "neuron.h"
#include "simulation.h"

int main() {
	
	const double extI(1.0001);
	const Time extIBeginning(100);
	const Time extIEnd(900);
	
	Simulation sim;
	sim.simulateANeuron(extI, extIBeginning, extIEnd);
	
	return 0;
}
