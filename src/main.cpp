#include <fstream>
#include "neuron.h"
#include "simulation.h"

int main() {
	
	const double extI(0.0);
	const Milliseconds extIBeginning(0.0);
	const Milliseconds extIEnd(400.0);
	
	Simulation sim;
	sim.simulateTwoNeurons(extI, extIBeginning, extIEnd);
	
	return 0;
}


//~ void testWithoutBuffer() {
	//~ const double extI(10);
	//~ const Milliseconds extIBeginning(100);
	//~ const Milliseconds extIEnd(400);
	
	//~ Simulation sim;	
	//~ sim.simulateTwoNeurons(extI, extIBeginning, extIEnd);

//~ }
