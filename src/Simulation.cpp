#include "Simulation.h"
#include "Constants.h"
#include "Neuron.h"
#include "Network.h"
#include <fstream>
#include <vector>
#include <cmath>
#include <cassert>
#include <iostream>

Simulation::Simulation()
	: Simulation(totalStep, "../res/data.dat") {}
	
Simulation::Simulation(const Milliseconds& simulationTime, const std::string& storeName)
	: currentTime(0),
	  simulationTime(simulationTime/constants::H),
	  storingFile(storeName) {
		  
	  assert(simulationTime>=0);
}

Time Simulation::getCurrentTime() const {
	return currentTime;
}

bool Simulation::isInInterval(Time toTest, Milliseconds min, Milliseconds max) {
	double test(toTest*constants::H);
	return (!(test < min) and test < max);
}

void Simulation::storeInFile(double toStore, std::ofstream& out) {
	out << toStore <<std::endl;
}

void Simulation::storeInFile(const std::vector<Neuron*>& neurons, std::ofstream& out) {
	for (const auto& neur:neurons) {
		out << neur->getMbPotential() << '\t';
	}
	out << '\n';
}

void Simulation::simulateANeuron(const double& extI, const Milliseconds& extIBeginning, const Milliseconds& extIEnd) {
	Neuron neuron;
	double currentImput(0.0);
	std::ofstream file;
	file.open(storingFile);
	while (currentTime <= simulationTime) {
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

void Simulation::simulateNetwork() {
	Network net;
	
	std::vector<Neuron*> neur;
	assert(neur.size()==0);
	for (unsigned int i(0); i<constants::NE; ++i) {
		neur.push_back(new Neuron(true));
	}
	
	for (unsigned int i(0); i<constants::NI; ++i) {
		neur.push_back(new Neuron(false));
	}
	assert(neur.size()==constants::NE+constants::NI);
	
	std::cout << "Generating connexions..." << std::endl;
	net.generateConnexions(neur);
	std::cout << "Connexions generated" << std::endl;
	
	std::ofstream file;
	file.open(storingFile);

	std::cout << "Starting simulation..." << std::endl;
	while (currentTime <= simulationTime) {
		
		bool spike;
		for (size_t i(0); i<neur.size();++i) {
			spike = neur[i]->update(currentTime+1);
		
			if (spike) {
				net.sendSpike(neur[i]);
					file << currentTime << '\t' << i;
					file << '\n';

			}
		}
		std::cout << currentTime*0.1 << " ms" << std::endl;
		++currentTime;

	}
	
	file.close();
}
