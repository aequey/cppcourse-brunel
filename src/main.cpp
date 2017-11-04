#include "Neuron.h"
#include "Simulation.h"

int main() {
	
	/// Create a Simulation 
	Simulation sim(600.0, "../res/data2.dat");

	/// Uncomment this if you want to simulate eiher one Neuron or two neurons with a connexion
	/*
	const double extI(1.01);
	const Milliseconds extIBeginning(0.0);
	const Milliseconds extIEnd(400.0);
	*/
	
	/// Uncomment this if you want to simulate one Neuron
	/*
	sim.simulateANeuron(extI, extIBeginning, extIEnd);
	*/
	
	/// Uncomment this if you want to simulate two neurons with one connexion
	/*
	sim.simulateTwoNeurons(extI, extIBeginning, extIEnd);
	*/
	
	/// Uncomment this if you want to simulate a complete Network with the constants given in Constants.h
	sim.simulateNetwork();
	return 0;
}
