#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>
#include <cassert>

#include "Constants.h"
#include "Neuron.h"
#include "Network.h"
#include "Simulation.h"


Simulation::Simulation()
	: Simulation(totalStep, "../res/data.dat") {}
	
////////////////////////////////////////////////////////////////////////
	
Simulation::Simulation(const Milliseconds& simulationTime, const std::string& storeName)
	: currentTime(0),
	  simulationTime(simulationTime/constants::H),
	  storingFile(storeName) {  
		assert(simulationTime>=0);
}

////////////////////////////////////////////////////////////////////////

Time Simulation::getCurrentTime() const {
	return currentTime;
}

////////////////////////////////////////////////////////////////////////

bool Simulation::isInInterval(Time toTest, Milliseconds min, Milliseconds max) {
	double test(toTest*constants::H);
	return (!(test < min) and test < max);
}

////////////////////////////////////////////////////////////////////////

void Simulation::simulateANeuron(const double& extI, const Milliseconds& extIBeginning, const Milliseconds& extIEnd) {
	Neuron neuron;
	double currentImput(0.0);
	
	std::ofstream file;
	file.open(storingFile);
	
	while (currentTime < simulationTime) {
		file << currentTime*constants::H << '\t' << neuron.getMbPotential() << std::endl;
		
		if (isInInterval(currentTime, extIBeginning, extIEnd)) {
			currentImput = extI;
		} else {
			currentImput = 0.0;
		}
		
		neuron.update(currentImput, currentTime+1, 0.0);

		++currentTime;
	}
	file.close();
}

////////////////////////////////////////////////////////////////////////

void Simulation::simulateTwoNeurons(const double& extI, const Milliseconds& extIBeginning, const Milliseconds& extIEnd) {
	Neuron n1;
	Neuron n2;
	
	double currentImput(0.0);
	
	std::ofstream file;
	file.open(storingFile);
	
	while (currentTime <= simulationTime) {
		file << currentTime*constants::H << '\t' << n1.getMbPotential() << '\t' << n2.getMbPotential() << std::endl;

		if (isInInterval(currentTime, extIBeginning, extIEnd)) {
			currentImput = extI;
		} else {
			currentImput = 0.0;
		}

		bool spike;
		spike = n1.update(currentImput, currentTime+1, 0.0);		
		if (spike) {
			n2.receiveSpike(n1.getJ(), constants::D_IN_STEP);
		}
		n2.update(0.0, currentTime+1, 0.0);
		
		++currentTime;
	}
	file.close();
}

////////////////////////////////////////////////////////////////////////

void Simulation::simulateNetwork() {
	
	std::cout << "Simulation of " << constants::N_TOTAL << " neurons for " << simulationTime*constants::H;
	std::cout << " ms with the following parameters :" << std::endl;
	std::cout << "G = " << constants::G << std::endl;
	std::cout << "ETA = " << constants::ETA << std::endl;
	
	std::vector<Neuron*> neur;
	assert(neur.size()==0);
	
	// Create the neurons (firstly the excitatory neurons)
	for (unsigned int i(0); i<constants::NE; ++i) {
		neur.push_back(new Neuron(true));
	}
	// Create the inhibitory neurons
	for (unsigned int i(0); i<constants::NI; ++i) {
		neur.push_back(new Neuron(false));
	}
	assert(neur.size()==constants::NE+constants::NI);
	assert(neur.size()==constants::N_TOTAL);

	// Create input and output connexoins between the neurons	
	std::cout << "Generating connexions..." << std::endl;
	Network net;
	net.generateConnexions(neur);
	std::cout << "Connexions generated" << std::endl;
	
	std::ofstream file;
	file.open(storingFile);

	// Start simulation
	std::cout << "Simulating the network..." << std::endl;
	while (currentTime < simulationTime) {
		bool spike;
		// update each Neuron
		for (size_t i(0); i<neur.size();++i) {
			assert(neur[i]!=nullptr);
			spike = false;
			spike = neur[i]->update(currentTime+1);
		
			if (spike) {
				net.sendSpike(neur[i]);
				// Collect data
				file << currentTime << '\t' << i;
				file << '\n';
			}
		}
		++currentTime;
	}
	assert(currentTime==simulationTime);
	file.close();
	
	std::cout << "End of the simulation" << std::endl;
	std::cout << "Results have been saved on this file : " << storingFile << std::endl;
}
