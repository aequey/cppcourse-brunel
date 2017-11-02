#include <iostream>
#include "Neuron.h"
#include "Simulation.h"

int main() {
	
	
	//~ const double extI(0.0);
	//~ const Milliseconds extIBeginning(0.0);
	//~ const Milliseconds extIEnd(400.0);
	
	Simulation sim(600.0, "../res/data2.dat");
	//~ sim.simulateANeuron(extI, extIBeginning, extIEnd);
	//~ sim.simulateTwoNeurons(extI, extIBeginning, extIEnd);
	sim.simulateNetwork();
	//~ Neuron n;
	//~ for (int i(0);i<100;++i) {
		//~ n.update(i);
		//~ std::cout << n.getMbPotential() << std::endl;
	//~ }
	return 0;
}
